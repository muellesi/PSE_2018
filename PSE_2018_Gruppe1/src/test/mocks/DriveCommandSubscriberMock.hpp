/**
 * \brief Emulates a DriveCommandSubscriber. This is a DIY solution because we cannot use gmock
 */

#pragma once

#include "../../DriveCommandSubscriber.hpp"

class DriveCommandSubscriberMock : public DriveCommandSubscriber {
public:
    void trySetDriveCommand(DriveCommand command) override {
        lastDriveCommand = command;
    }

    void forceDriveCommand(DriveCommand command) override {
        lastDriveCommand = command;
    }

    DriveCommand getLastDriveCommand() {
        return lastDriveCommand;
    }

    DriveCommandSubscriberMock() : lastDriveCommand(NO_COMMAND, 0, 0) {};
private:
    DriveCommand lastDriveCommand;
};
