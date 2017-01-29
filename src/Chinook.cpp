
#include "Chinook.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
/* settings */
const static double global_speed_limit = 0.8;


/* utils */
void reportMsg(std::string msg){
    FRC_NetworkCommunication_sendConsoleLine(msg.c_str());
}

std::vector<double> updateRemoteDriveTrain() {
    double a = 0.0;
    std::vector<double > v;
    RECV(&a, sizeof(double));
    v.push_back(a);
    RECV(&a, sizeof(double));
    v.push_back(a);
    return v;
}

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
    JoystickLeftStickDown = 1,

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

class DriveTrain {
public:
    /**
     * Constructor for DriveTrain
     * @param speedLimit double The Speed Limit
     */
    explicit DriveTrain(double speedLimit) : speedLimit(speedLimit),
                                    leftFront(LeftPortFront),
                                    leftBack(LeftPortBack),
                                    rightFront(RightPortFront),
                                    rightBack(RightPortBack),
                                    drive(leftFront, leftBack, rightFront, rightBack) {}

    /**
     * ArcadeDrive method
     * @param x double rotation
     * @param y double drive
     */
    void ArcadeDrive(double x, double y) { drive.ArcadeDrive(-limitSpeed(y), -(limitSpeed(std::abs(y) >= 0.5 ? x * 0.6 : x))); }

    /**
     * TankDrive method
     * @param left double left-stick
     * @param right double right-stick
     */
    void TankDrive(double left, double right) { drive.TankDrive(limitSpeed(left), limitSpeed(right)); }

    /**
     * Updates the speed limit
     * @param speedLimit double renews speed limit to a new one
     */
    void Update(double speedLimit) { this->speedLimit = speedLimit; }

    /**
     * Change by a speed limit
     * @param speedLimit  double increases/decreases speedLimit
     */
    void ChangeBy(double speedLimit) {
        this->speedLimit += ((this->speedLimit + speedLimit > 1.0000000001) ||
                (this->speedLimit + speedLimit < -0.0000000001) ) ? 0: speedLimit;
        reportMsg("\rNewSpeedLimit" + std::to_string(this->speedLimit) + "     ");
        std::cout << "New Limit: " << this->speedLimit << std::endl;
    }

private:
    double speedLimit;
    Victor leftFront, leftBack, rightFront, rightBack;
    RobotDrive drive;

    /**
     * The devised algorithm for limiting the speed.
     * @param a
     * @return
     */
    double limitSpeed(double a) { return a/std::abs(a) * (std::abs(a) > speedLimit ? speedLimit : std::abs(a)); }

};

class Robot: public frc::IterativeRobot {
public:

    DriveTrain drive;

    Robot() : drive( global_speed_limit ) {}

    /**
     * @Override
     */
    void RobotInit()  {
        std::cout << "Chinook: RobotInit VER " << VERSION << std::endl;
        accept_init();
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
        std::vector<double> v = updateRemoteDriveTrain();
        reportMsg(v.pop_back() + " " +v.pop_back());
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

    void DisabledInit() override {
        CLOSE();
    }

private:

};



START_ROBOT_CLASS(Robot)

#pragma clang diagnostic pop