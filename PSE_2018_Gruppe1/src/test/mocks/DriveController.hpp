/*
 * \brief Mock for the library class "DriveController". Can report the last set commands back to the test.
 *
 *  Created on: 12.06.2018
 *      Author: student
 */

#pragma once

#include "../../Logging.hpp"


class DriveController {
public:

    /// Get the singleton instance of the drive controller.
    static DriveController *getInstance() {
        static DriveController driveController;
        return &driveController;
    }


    virtual ~DriveController() = default;;

    bool updateDirect(int speed, int steering) {
        motor_speed = speed;
        motor_steering = steering;
        DIAG_ERROR("In Mock !!!!!!!!");
        return true;
    }


    bool updateDirectMotor(int speedLeft, int speedRight){return true;}


    bool updateController(int speed, int steering) {
        motor_speed = speed;
        motor_steering = steering;
        DIAG_ERROR("In Mock !!!!!!!!");
        return true;
    }

    int getSpeed() const {
        return motor_speed;
    }

    int getSteering() const {
        return motor_steering;
    }

    void setTestMode(bool) const {
        //nothing to see here only mock :(
    }

private:
    int motor_speed;
    int motor_steering;

};


