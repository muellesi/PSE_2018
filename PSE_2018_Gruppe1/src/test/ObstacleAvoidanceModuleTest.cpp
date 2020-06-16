#include <gtest/gtest.h>
#include <DriveCommandSubscriberMock.hpp>
#include "../ObstacleAvoidanceModule.hpp"

/**
 * \brief Tests whether ObstacleAvoidance correctly stops when it encounters an obstacle that is closer than the
 * configured safety distance
 */
TEST(ObstacleAvoidanceModuleTest, obstacleTest)
{
  ObstacleAvoidanceModule obstacleAvoidanceModule;
  std::shared_ptr<DriveCommandSubscriberMock> driveCommandSubscriberMock = std::make_shared<DriveCommandSubscriberMock>();
  obstacleAvoidanceModule.addSubscriber(driveCommandSubscriberMock);

  // set command to no drive
  DriveCommand noDrive(NO_COMMAND, 10, 10);
  driveCommandSubscriberMock->trySetDriveCommand(noDrive);

  SensorManager::getInstance()->setDepth(2);  // SensorManager mock will now always return 2.0 for getDepth()

  obstacleAvoidanceModule.processData();

  // Depth is not yet critical -> ObstacleAvoidance should not send any commands
  ASSERT_EQ(driveCommandSubscriberMock->getLastDriveCommand().source, NO_COMMAND);
  ASSERT_EQ(driveCommandSubscriberMock->getLastDriveCommand().speed, 10);
  ASSERT_EQ(driveCommandSubscriberMock->getLastDriveCommand().steering, 10);

  SensorManager::getInstance()->setDepth(0.2);
  obstacleAvoidanceModule.processData();

  // Depth is now critical - ObstacleAvoidance should continuously send stop command
  ASSERT_EQ(driveCommandSubscriberMock->getLastDriveCommand().source, OBSTACLE_AVOIDANCE);
  ASSERT_EQ(driveCommandSubscriberMock->getLastDriveCommand().speed, 0);
  ASSERT_EQ(driveCommandSubscriberMock->getLastDriveCommand().steering, 0);
}
