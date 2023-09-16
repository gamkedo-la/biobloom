using System;
using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.UIElements;

namespace Gameplay
{
    public class PlayerCharacterController : MonoBehaviour
    {
        [Header("References")]
        [Tooltip("Reference to the main camera used for the player")]
        public Camera PlayerCamera;


        [Header("Rotation")]
        [Tooltip("Rotation speed for moving the camera")]
        public float RotationSpeed = 200f;

        [Range(0.1f, 1f)]
        [Tooltip("Rotation speed multiplier when aiming")]
        public float AimingRotationMultiplier = 0.4f;

        [Header("Rotation")]
        [Tooltip("Maximum Vertical Look Angle")]
        float MaximumVerticalLookAngle = 89;

        [Header("Rotation")]
        [Tooltip("Minimum Vertical Look Angle")]
        float MinimumVerticalLookAngle = -89;

        [Tooltip("Multiplicator for the sprint speed (based on grounded speed)")]
        public float SprintSpeedModifier = 2f;

        [Header("Movement")]
        [Tooltip("Max movement speed when grounded (when not sprinting)")]
        public float MaxSpeedOnGround = 10f;

        [Tooltip("Physic layers checked to consider the player grounded")]
        public LayerMask GroundCheckLayers = 0;

        [Tooltip("distance from the bottom of the character controller capsule to test for grounded")]
        public float GroundCheckDistance = 0.05f;

        [Tooltip(
            "Sharpness for the movement when grounded, a low value will make the player accelerate and decelerate slowly, a high value will do the opposite")]
        public float MovementSharpnessOnGround = 15;

        [Header("Jump")]
        [Tooltip("Force applied upward when jumping")]
        public float JumpForce = 9f;

        CharacterController m_Controller;
        PlayerInputHandler m_InputHandler;
        Vector3 m_GroundNormal;
        Vector3 m_CharacterVelocity;
        float m_LastTimeJumped = 0f;

        float m_CameraVerticalAngle;
        public int[] CapsuleCollection;
        public string[] CapsuleColors;

        public TMP_Text CountDisplay;
        private Vector3 m_LatestImpactSpeed;
        const float k_JumpGroundingPreventionTime = 0.2f;
        const float k_GroundCheckDistanceInAir = 0.07f;
        public Vector3 CharacterVelocity { get; set; }

        public bool IsGrounded { get; private set; }
        public bool HasJumpedThisFrame { get; private set; }

        public float RotationMultiplier
        {
           get
            {
                // TODO: Handle when the player is aiming down the sights to slow down aim)
                return 1f;
            } 
        }

        // Start is called before the first frame update
        void Start() {
            // fetch components on the same gameObject
            m_Controller = GetComponent<CharacterController>();
            m_InputHandler = GetComponent<PlayerInputHandler>();
            RefreshUI();
        }

        // Update is called once per frame
        void Update() {
            bool wasGrounded = IsGrounded;
            GroundCheck();
            HandleCharacterMovement();
            if (Input.GetButtonDown("Fire1")) {
                Debug.Log("Fire");
                RaycastHit hit; 
                if (Physics.Raycast(PlayerCamera.transform.position, PlayerCamera.transform.forward, out hit)) {
                    Debug.Log(hit.collider.gameObject.name);
                    CapsuleData data = hit.collider.gameObject.GetComponent<CapsuleData>();
                    if (data) {
                        CapsuleCollection[data.colorType] ++;
                        Debug.Log(data.colorType);
                        Debug.Log(CapsuleCollection[data.colorType]);
                        RefreshUI();
                    }
                    Destroy(hit.collider.gameObject);

                }
            }
        }

        private void RefreshUI() {
            String output = "";
            for (int i = 0; i < CapsuleCollection.Length; i++) {
                output += CapsuleColors[i] + ": " + CapsuleCollection[i] + "\n";
            }
            CountDisplay.text = output;
        }

        private void HandleCharacterMovement() {
            HandleCharacterRotation();
            HandleCharacterPositionAndSpeed();
        }


        void GroundCheck() {
            // Make sure that the ground check distance while already in air is very small, to prevent suddenly snapping to ground
            float chosenGroundCheckDistance =
                IsGrounded ? (m_Controller.skinWidth + GroundCheckDistance) : k_GroundCheckDistanceInAir;

            // reset values before the ground check
            IsGrounded = false;
            m_GroundNormal = Vector3.up;

            // only try to detect ground if it's been a short amount of time since last jump; otherwise we may snap to the ground instantly after we try jumping
            if (Time.time >= m_LastTimeJumped + k_JumpGroundingPreventionTime) {
                // if we're grounded, collect info about the ground normal with a downward capsule cast representing our character capsule
                if (Physics.CapsuleCast(GetCapsuleBottomHemisphere(), GetCapsuleTopHemisphere(m_Controller.height),
                    m_Controller.radius, Vector3.down, out RaycastHit hit, chosenGroundCheckDistance, GroundCheckLayers,
                    QueryTriggerInteraction.Ignore)) {
                    // storing the upward direction for the surface found
                    m_GroundNormal = hit.normal;

                    // Only consider this a valid ground hit if the ground normal goes in the same direction as the character up
                    // and if the slope angle is lower than the character controller's limit
                    if (Vector3.Dot(hit.normal, transform.up) > 0f &&
                        IsNormalUnderSlopeLimit(m_GroundNormal)) {
                        IsGrounded = true;

                        // handle snapping to the ground
                        if (hit.distance > m_Controller.skinWidth) {
                            m_Controller.Move(Vector3.down * hit.distance);
                        }
                    }
                }
            }
        }

        private void HandleCharacterPositionAndSpeed() {
            // character movement handling
            bool isSprinting = m_InputHandler.GetSprintInputHeld();
            {
                float speedModifier = isSprinting ? SprintSpeedModifier : 1f;

                // converts move input to a worldspace vector based on our character's transform orientation
                Vector3 worldspaceMoveInput = transform.TransformVector(m_InputHandler.GetMoveInput());

                // calculate the desired velocity from inputs, max speed, and current slope
                Vector3 targetVelocity = worldspaceMoveInput * MaxSpeedOnGround * speedModifier;

                targetVelocity = GetDirectionReorientedOnSlope(targetVelocity.normalized, m_GroundNormal) *
                                    targetVelocity.magnitude;

                // smoothly interpolate between our current velocity and the target velocity based on acceleration speed
                CharacterVelocity = Vector3.Lerp(CharacterVelocity, targetVelocity,
                    MovementSharpnessOnGround * Time.deltaTime);

                // jumping
                if (IsGrounded && m_InputHandler.GetJumpInputDown()) {
                    // start by canceling out the vertical component of our velocity
                    CharacterVelocity = new Vector3(CharacterVelocity.x, 0f, CharacterVelocity.z);

                    // then, add the jumpSpeed value upwards
                    CharacterVelocity += Vector3.up * JumpForce;

                    // remember last time we jumped because we need to prevent snapping to ground for a short time
                    m_LastTimeJumped = Time.time;
                    HasJumpedThisFrame = true;

                    // Force grounding to false
                    IsGrounded = false;
                    m_GroundNormal = Vector3.up;
                }

                // apply the final calculated velocity value as a character movement
                Vector3 capsuleBottomBeforeMove = GetCapsuleBottomHemisphere();
                Vector3 capsuleTopBeforeMove = GetCapsuleTopHemisphere(m_Controller.height);

                // Move the character controller
                m_Controller.Move(CharacterVelocity * Time.deltaTime);

                // detect obstructions to adjust velocity accordingly
                m_LatestImpactSpeed = Vector3.zero;
                if (Physics.CapsuleCast(capsuleBottomBeforeMove, capsuleTopBeforeMove, m_Controller.radius,
                    CharacterVelocity.normalized, out RaycastHit hit, CharacterVelocity.magnitude * Time.deltaTime, -1,
                    QueryTriggerInteraction.Ignore)) {
                    // We remember the last impact speed because the fall damage logic might need it
                    m_LatestImpactSpeed = CharacterVelocity;

                    CharacterVelocity = Vector3.ProjectOnPlane(CharacterVelocity, hit.normal);
                }
            }
        }

        private void HandleCharacterRotation() {
            // horizontal character rotation
            {
                // rotate the transform with the input speed around its local Y axis
                //Vector3 eulers = new Vector3(0f, (m_InputHandler.GetLookInputsHorizontal() * RotationSpeed * RotationMultiplier), 0f);
                //transform.Rotate(eulers, Space.Self);

                //PlayerCamera.transform.localEulerAngles = new Vector3(m_CameraVerticalAngle, 0, 0);
                transform.Rotate(
                    new Vector3(0f, (m_InputHandler.GetLookInputsHorizontal() * RotationSpeed * RotationMultiplier),
                        0f), Space.Self);
            }
            // vertical camera rotation
            {
                // add vertical inputs to the cameras vertical angle
                m_CameraVerticalAngle += m_InputHandler.GetLookInputsVertical() * RotationSpeed * RotationMultiplier;

                // limit the cameras vertical angle to the min/max
                m_CameraVerticalAngle = Mathf.Clamp(m_CameraVerticalAngle, MinimumVerticalLookAngle, MaximumVerticalLookAngle);

                // apply the vertical angle as a local rotation to the camera transform along its right axis (makes it pivot up and down)
                PlayerCamera.transform.localEulerAngles = new Vector3(m_CameraVerticalAngle, 0, 0);
            }
        }

        // Gets the center point of the bottom hemisphere of the character controller capsule    
        Vector3 GetCapsuleBottomHemisphere() {
            return transform.position + (transform.up * m_Controller.radius);
        }

        // Gets the center point of the top hemisphere of the character controller capsule    
        Vector3 GetCapsuleTopHemisphere(float atHeight) {
            return transform.position + (transform.up * (atHeight - m_Controller.radius));
        }

        // Returns true if the slope angle represented by the given normal is under the slope angle limit of the character controller
        bool IsNormalUnderSlopeLimit(Vector3 normal) {
            return Vector3.Angle(transform.up, normal) <= m_Controller.slopeLimit;
        }
        // TODO: Test
        // Gets a reoriented direction that is tangent to a given slope
        public Vector3 GetDirectionReorientedOnSlope(Vector3 direction, Vector3 slopeNormal) {
            Vector3 directionRight = Vector3.Cross(direction, transform.up);
            return Vector3.Cross(slopeNormal, directionRight).normalized;
        }
    }
}