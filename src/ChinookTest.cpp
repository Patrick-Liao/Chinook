
#include "ChinookTest.h"

enum {
    // wheels
    LeftPortFront = 0,
    LeftPortBack = 2,
    RightPortFront = 1,
    RightPortBack = 3,
    // Ball pick up
    LeftBall = 4,
    RightBall = 5,
    // Gamepad Port Mappings
    GamepadPort = 3,
    GamepadAButton = 1,
    GamepadBButton = 2,
    GamepadXButton = 3,
    GamepadYButton = 4,
    GamepadLeftBumper = 5,
    GamepadRightBumper = 6,
    GamepadBack = 7,
    GamepadStart = 8,
    GamepadLeftStickDown = 1,
    GamepadRightStickDown = 10,
    JoystickTrigger = 1,
    // Max Power
    MaxPower = 2,
    // Axis
    LeftStickX = 0,
    LeftStickY = 1,
    LeftTrigger = 2,
    RightTrigger = 3,
    RightStickX = 4,
    RightStickY = 5,
    // Actuators
    BorisPort = 8,
    // Joystick
    JoystickPort = 3,
    JoystickAButton = 3,
    JoystickYButton = 4,
    JoystickLeftStickDown = 1
};

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
        Joystick *gamepad = new Joystick(GamepadPort);
        Joystick *joystick = new Joystick(JoystickPort);

        joystick->SetAxisChannel(Joystick::kTwistAxis, LeftStickX);
        gamepad->SetAxisChannel(Joystick::kXAxis, RightStickX);
        gamepad->SetAxisChannel(Joystick::kYAxis, RightStickY);

        switch (joystick->GetPOV()) {
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

        OpState.gpIsBButtonPressed = gamepad->GetRawButton(GamepadBButton);
        OpState.gpIsXButtonPressed = gamepad->GetRawButton(GamepadXButton);
        OpState.gpIsLeftBumperPressed = gamepad->GetRawButton(GamepadLeftBumper);
        OpState.gpIsRightBumperPressed = gamepad->GetRawButton(GamepadRightBumper);
        OpState.gpIsBackPressed = gamepad->GetRawButton(GamepadBack);
        OpState.gpIsStartPressed = gamepad->GetRawButton(GamepadStart);
        OpState.jsIsLeftStickDown = joystick->GetRawButton(JoystickLeftStickDown);
        OpState.gpIsRightStickDown = gamepad->GetRawButton(GamepadRightStickDown);
        OpState.jsIsTriggered = joystick->GetRawButton(JoystickTrigger);

        // Axis
        OpState.jsLeftStickX = joystick->GetRawAxis(LeftStickX);
        OpState.jsLeftStickY = joystick->GetRawAxis(RightStickY);
        OpState.gpLeftTrigger = gamepad->GetRawAxis(LeftTrigger);
        OpState.gpRightTrigger = gamepad->GetRawAxis(RightTrigger);
        OpState.gpRightStickX = gamepad->GetRawAxis(RightStickX);
        OpState.gpRightStickY = gamepad->GetRawAxis(RightStickY);

        // DPAD

        OpState.gpDpad = (joystick->GetRawButton(MaxPower)) ? 0 : -1;
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

class DriveTrain {
public:

    DriveTrain(double speedLimit) {
        this->speedLimit = speedLimit;
        leftFront = new Victor(LeftPortFront);
        leftBack = new Victor(LeftPortBack);
        rightFront = new Victor(RightPortFront);
        rightBack = new Victor(RightPortBack);
        drive = new RobotDrive(leftFront, leftBack, rightFront, rightBack);
    }

    void arcadeDrive(double x, double y) {
        int sign = y/std::abs(y);
        y = std::abs(y);
        drive->ArcadeDrive(-(sign) * (speedLimit > y ? speedLimit : y)),
                -(((std::abs(y >= 0.5 ? x * 0.6 : x)) >= speedLimit) ? (x/std::abs(x) ? -1 : 1) * speedLimit : (y >= 0.5 ? x * 0.6 : x)));
    }

    void tankDrive(double left, double right) {
        drive->TankDrive(((left >= speedLimit) ? speedLimit: left),
                         ((right >= speedLimit) ? speedLimit : right));
    }

    void update(double speedLimit) {
        this->speedLimit = speedLimit;
    }

    void increaseBy(double speedLimit) {
        this->speedLimit += speedLimit;
    }

    void decreaseBy(double speedLimit) {
        this->speedLimit -= speedLimit;
    }

private:
    double speedLimit;
    double speedBool;
    Victor *leftFront;
    Victor *leftBack;
    Victor *rightFront;
    Victor *rightBack;
    RobotDrive *drive;
};

class Robot: public frc::IterativeRobot {
public:

    DriveTrain *drive;

    void RobotInit() {
        std::cout << "Chinook: RobotInit" << std::endl;
        drive = new DriveTrain(speedLimit);
    }

    void AutonomousInit() override {
        std::cout << "Chinook: Called AutonomousInit" << std::endl;
        std::cout << "Chinook: Warning: Autonomous is yet to be implemented." << std::endl;
    }

    void AutonomousPeriodic() {
        std::cout << "Chinook: Called AutonomousPeriodic" << std::endl;
    }

    void TeleopInit() {
        std::cout << "Chinook: Called TeleopInit" << std::endl;

    }

    void TeleopPeriodic() {
        std::cout << "Chinook: Called TeleopPeriodic" << std::endl;
        setOpState();
        if(OpState.gpIsRightBumperPressed) drive->increaseBy(0.1);
        if(OpState.gpIsLeftBumperPressed) drive->decreaseBy(0.1);
        drive->arcadeDrive(OpState.gpRightStickX, OpState.gpRightStickY);
    }

    void TestPeriodic() {
        std::cout << "Chinook: Called TestPeriodic()" << std::endl << "Chinook: TestPeriodic is not implemented." << std::endl;
    }

private:
    double speedLimit = 0.8;
};

START_ROBOT_CLASS(Robot)
