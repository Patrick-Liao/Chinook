#include "opState.h"

void setOpState() {
    try {
        Joystick gamepad(GamepadPort);
        Joystick joystick(JoystickPort);

        joystick.SetAxisChannel(Joystick::kTwistAxis, LeftStickX);
        gamepad.SetAxisChannel(Joystick::kXAxis, RightStickX);
        gamepad.SetAxisChannel(Joystick::kYAxis, RightStickY);

        switch (joystick.GetPOV()) {
            case 100:
                OpState.jsIsAButtonPressed = true;
                break;
            case 0:
                OpState.jsIsYButtonPressed = true;
                break;
            default:
                // reset to natural state
                OpState.jsIsAButtonPressed = false;
                OpState.jsIsYButtonPressed = false;
        }

        OpState.gpIsBButtonPressed = gamepad.GetRawButton(GamepadBButton);
        OpState.gpIsXButtonPressed = gamepad.GetRawButton(GamepadXButton);
        OpState.gpIsLeftBumperPressed = gamepad.GetRawButton(GamepadLeftBumper);
        OpState.gpIsRightBumperPressed = gamepad.GetRawButton(GamepadRightBumper);
        OpState.gpIsBackPressed = gamepad.GetRawButton(GamepadBack);
        OpState.gpIsStartPressed = gamepad.GetRawButton(GamepadStart);
        OpState.jsIsLeftStickDown = joystick.GetRawButton(JoystickLeftStickDown);
        OpState.gpIsRightStickDown = gamepad.GetRawButton(GamepadRightStickDown);
        OpState.jsIsTriggered = joystick.GetRawButton(JoystickTrigger);

        // Axis
        OpState.jsLeftStickX = joystick.GetRawAxis(LeftStickX);
        OpState.jsLeftStickY = joystick.GetRawAxis(RightStickY);
        OpState.gpLeftTrigger = gamepad.GetRawAxis(LeftTrigger);
        OpState.gpRightTrigger = gamepad.GetRawAxis(RightTrigger);
        OpState.gpRightStickX = gamepad.GetRawAxis(RightStickX);
        OpState.gpRightStickY = gamepad.GetRawAxis(RightStickY);

        // DPAD

        OpState.gpDpad = (joystick.GetRawButton(MaxPower)) ? 0 : -1;

    } catch(int exception) {
        std::cout << "Chinook: setOpState() caught Exception:" << exception << std::endl;
    }
}

void resetOpState() {
    OpState.jsIsAButtonPressed = false;
    OpState.gpIsBButtonPressed = false;
    OpState.gpIsXButtonPressed = false;
    OpState.jsIsYButtonPressed = false;
    OpState.gpIsLeftBumperPressed = false;
    OpState.gpIsRightBumperPressed = false;
    OpState.gpIsBackPressed = false;
    OpState.gpIsStartPressed = false;
    OpState.jsIsLeftStickDown = false;
    OpState.gpIsRightStickDown = false;
    OpState.jsIsTriggered = false;

    // axis
    OpState.jsLeftStickX = .0;
    OpState.jsLeftStickY = .0;
    OpState.gpLeftTrigger = .0;
    OpState.gpRightTrigger = .0;
    OpState.gpRightStickX = .0;
    OpState.gpRightStickY = .0;

    // DPAD
    OpState.gpDpad = -1.0;
}
