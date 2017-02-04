#ifndef OPSTATE_H
#define OPSTATE_H
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

void setOpState();

void resetOpState();
#endif