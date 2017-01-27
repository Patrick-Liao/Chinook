#ifndef DRIVE_H
#define DRIVE_H

#include "util.h"
#include "ChinookTest.h"
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

#endif /*drive.h*/
