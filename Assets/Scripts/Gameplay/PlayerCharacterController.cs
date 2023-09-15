using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

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

        CharacterController m_Controller;
        PlayerInputHandler m_InputHandler;

        float m_CameraVerticalAngle;

        [Header("Rotation")]
        [Tooltip("Maximum Vertical Look Angle")]
        float MaximumVerticalLookAngle = 89;

        [Header("Rotation")]
        [Tooltip("Minimum Vertical Look Angle")]
        float MinimumVerticalLookAngle = -89;

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

        }

        // Update is called once per frame
        void Update()
        {
            HandleCharacterMovement();
        }

        private void HandleCharacterMovement() {
            HandleCharacterRotation();
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
    }
}