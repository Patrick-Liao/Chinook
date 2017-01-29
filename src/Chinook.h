//
// Created by explorer on 1/14/17.
//

#ifndef CHINOOKTEST1_CHINOOKTEST_H
#define CHINOOKTEST1_CHINOOKTEST_H

#define VERSION 0.6

#include <iostream>
#include <memory>
#include <string>

#include "WPILib.h"
#include "IterativeRobot.h"
#include "DriverStation.h"
#include "RobotDrive.h"
#include "Victor.h"
#include "Joystick.h"
#include "HAL/HAL.h"
#include "FRC_NetworkCommunication/FRCComm.h"
#include "server.h"

// Networking stuffs

#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#define AUTON_INIT_CONN 0x0a
#define AUTON_ABORT_CONN 0x0b
#define AUTON_ACCEPT_CONN 0x0c
#define AUTON_CONN_BYE 0x0d
#define AUTON_CONN_ACK 0x0e
#define AUTON_READY_SEND_DATA 0x0f
#define AUTON_IS_READY 0x10
#define AUTON_SEND_DRIVETRAIN 0x01
#define AUTON_SEND_LIDAR_COORDS 0x02
#define AUTON_SEND_DOUBLE 0x03
#define AUTON_DEFAULT_SEND_FLAG 0
#define AUTON_DEFAULT_RECV_FLAG 0

#endif /*CHINOOKTEST1_CHINOOKTEST_H*/
