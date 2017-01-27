
#include "ChinookTest.h"

/* settings */
const static double global_speed_limit = 0.8;

struct {
    // button
    bool jsIsAButtonPressed = false;
    bool gpIsBButtonPressed = false;
    bool gpIsXButtonPressed = false;
    bool jsIsYButtonPressed = false;
    bool gpIsLeftBumperPressed = false;
    bool gpIsRightBumperPressed = false;
    bool gpIsBackPressed = false;
    bool gpIsStartPressed = false;
    bool jsIsLeftStickDown = false;
    bool gpIsRightStickDown = false;
    bool jsIsTriggered = false;

    // axis
    double jsLeftStickX = .0;
    double jsLeftStickY = .0;
    double gpLeftTrigger = .0;
    double gpRightTrigger = .0;
    double gpRightStickX = .0;
    double gpRightStickY = .0;

    // DPAD
    double gpDpad = -1.0;
} OpState;

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

class Robot: public frc::IterativeRobot {
public:

    DriveTrain drive;

    Robot() : drive( global_speed_limit ) {}

    /**
     * @Override
     */
    void RobotInit()  {
        std::cout << "Chinook: RobotInit VER " << VERSION << std::endl;
    }

    /**
     * @Override
     */
    void AutonomousInit() override {
        std::cout << "Chinook: Called AutonomousInit\nChinook: Warning: Autonomous is yet to be implemented." << std::endl;
    }

    /**
     * @Override
     */
    void AutonomousPeriodic() {
        std::cout << "Chinook: Called AutonomousPeriodic" << std::endl;
    }

    /**
     * @Override
     */
    void TeleopInit() {
        std::cout << "Chinook: Called TeleopInit" << std::endl;

    }

    /**
     * @Override
     */
    void TeleopPeriodic() {
       // std::cout << "Chinook: Called TeleopPeriodic" << std::endl;
        setOpState();
        if(OpState.gpIsRightBumperPressed) drive.ChangeBy(0.01);
        if(OpState.gpIsLeftBumperPressed) drive.ChangeBy(-0.01);
        drive.ArcadeDrive(OpState.gpRightStickX, OpState.gpRightStickY);
    }

    /**
     * @Override
     */
    void TestPeriodic() {
        std::cout << "Chinook: Called TestPeriodic()\nChinook: TestPeriodic is not implemented." << std::endl;
    }


private:

};



START_ROBOT_CLASS(Robot)
