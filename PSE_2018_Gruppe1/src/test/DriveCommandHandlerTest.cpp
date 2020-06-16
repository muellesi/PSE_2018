#include <gtest/gtest.h>
#include "../DriveCommandHandler.hpp"

/**
 * \brief checks whether the DriveCommandHandler correctly handles commands with differing priorities
 */
TEST(DriveCommandHandler, commandPriorities)
{
  DriveController* driveControllerMock = DriveController::getInstance();
  DriveCommandHandler handler;

  // begin with lowest priority
  DriveCommand command(FIND_MARKER, 1, 1);

  handler.trySetDriveCommand(command);
  handler.updateMotor();
  // check if the right commands are set
  ASSERT_EQ(1, driveControllerMock->getSpeed());
  ASSERT_EQ(1, driveControllerMock->getSteering());

  // next prio
  command.source   = FOLLOW_MARKER;
  command.speed    = 2;
  command.steering = 2;

  handler.trySetDriveCommand(command);

  // next lower should be ignored
  command.source   = FIND_MARKER;
  command.speed    = 1;
  command.steering = 1;

  handler.trySetDriveCommand(command);
  handler.updateMotor();
  // check if the right commands are set
  ASSERT_EQ(2, driveControllerMock->getSpeed());
  ASSERT_EQ(2, driveControllerMock->getSteering());

  // next prio
  command.source   = OBSTACLE_AVOIDANCE;
  command.speed    = 3;
  command.steering = 3;

  handler.trySetDriveCommand(command);

  // next lower should be ignored
  command.source   = FOLLOW_MARKER;
  command.speed    = 2;
  command.steering = 2;

  handler.trySetDriveCommand(command);
  handler.updateMotor();
  // check if the right commands are set
  ASSERT_EQ(3, driveControllerMock->getSpeed());
  ASSERT_EQ(3, driveControllerMock->getSteering());

  // next prio
  command.source   = MANUAL_COMMAND;
  command.speed    = 4;
  command.steering = 4;

  handler.trySetDriveCommand(command);

  // next lower should be ignored
  command.source   = OBSTACLE_AVOIDANCE;
  command.speed    = 3;
  command.steering = 3;

  handler.trySetDriveCommand(command);
  handler.updateMotor();
  // check if the right commands are set
  ASSERT_EQ(4, driveControllerMock->getSpeed());
  ASSERT_EQ(4, driveControllerMock->getSteering());
}
