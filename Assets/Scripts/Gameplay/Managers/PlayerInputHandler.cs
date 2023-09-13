using Game;
using System.Collections;
using System.Collections.Generic;
using System.Net.Sockets;
using UnityEngine;

namespace Gameplay
{
    public class PlayerInputHandler : MonoBehaviour
    {
        [Tooltip("Sensitivity multiplier for moving the camera around")]
        public float LookSensitivity = 1f;

        [Tooltip("Used to flip the vertical input axis")]
        public bool InvertYAxis = false;

        [Tooltip("Used to flip the horizontal input axis")]
        public bool InvertXAxis = false;

        PlayerCharacterController m_PlayerCharacterController;

        // Start is called before the first frame update
        void Start() {
            m_PlayerCharacterController = GetComponent<PlayerCharacterController>();

            Cursor.lockState = CursorLockMode.Locked;
            Cursor.visible = false;
        }

        public bool CanProcessInput() {
            //
            // Summary:
            //     Cursor behavior is unmodified.
            // None,
            //
            // Summary:
            //     Locks the cursor to the center of the Game view.
            // Locked,
            //
            // Summary:
            //     Confine cursor to the game window.
            // Confined
            return Cursor.lockState == CursorLockMode.Locked;
        }

        public float GetLookInputsHorizontal() {
            return GetMouseOrStickLookAxis(GameConstants.k_MouseAxisNameHorizontal,
                GameConstants.k_AxisNameJoystickLookHorizontal);
        }

        public float GetLookInputsVertical() {
            return GetMouseOrStickLookAxis(GameConstants.k_MouseAxisNameVertical,
                GameConstants.k_AxisNameJoystickLookVertical);
        }

        public float GetMouseOrStickLookAxis(string mouseInputName, string stickInputName) {
            if (CanProcessInput()) {
                // Check if this look input is coming from the mouse
                bool isGamepad = Input.GetAxis(stickInputName) != 0f;
                float i = isGamepad ? Input.GetAxis(stickInputName) : Input.GetAxisRaw(mouseInputName);

                // handle inverting vertical input
                if (InvertYAxis)
                    i *= -1f;

                // apply sensitivity multiplier
                i *= LookSensitivity;

                if (isGamepad) {
                    // since mouse input is already deltaTime-dependant, only scale input with frame time if it's coming from sticks
                    i *= Time.deltaTime;
                } else {
                    // reduce mouse input amount to be equivalent to stick movement
                    i *= 0.01f;
#if UNITY_WEBGL
                    // Mouse tends to be even more sensitive in WebGL due to mouse acceleration, so reduce it even more
                    i *= WebglLookSensitivityMultiplier;
#endif
                }

                return i;
            }

            return 0f;
        }
    }
}