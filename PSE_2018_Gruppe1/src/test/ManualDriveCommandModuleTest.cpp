#include <gtest/gtest.h>
#include <DriveCommandSubscriberMock.hpp>
#include <DriveController.hpp>
#include "../DriveCommandHandler.hpp"
#include "../ManualDriveCommandModule.hpp"

/**
 * \brief Tests execution of the blocking drive command that is used in manual mode. It should run at least until it
 * hits the timeout or alternatively as long as it was commanded
 */
TEST(ManualDriveCommandModuleTest, driveBlockingTest)
{
  DriveController driveControllerMock;
  std::shared_ptr<DriveCommandHandler> handler = std::make_shared<DriveCommandHandler>();
  ManualDriveCommandModule manualDriveCommandModule;

  std::shared_ptr<DriveCommandSubscriberMock> driveCommandSubscriberMock = std::make_shared<DriveCommandSubscriberMock>();
  manualDriveCommandModule.addSubscriber(driveCommandSubscriberMock);

  // set command to no drive
  DriveCommand noDrive(NO_COMMAND, 0, 0);
  driveCommandSubscriberMock->trySetDriveCommand(noDrive);

  // should run more than 100ms
  manualDriveCommandModule.setMaxDriveDuration(std::chrono::milliseconds(100));
  std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
  manualDriveCommandModule.driveBlocking(std::chrono::milliseconds(5), 55, -55);

  // The timeout value is higher than the commanded driving time -> we should drive about as long as commanded
  ASSERT_GE(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start), std::chrono::milliseconds(5));
  ASSERT_LE(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start), std::chrono::milliseconds(25));

  ASSERT_EQ(driveCommandSubscriberMock->getLastDriveCommand().source, MANUAL_COMMAND);
  ASSERT_EQ(driveCommandSubscriberMock->getLastDriveCommand().speed, 0);
  ASSERT_EQ(driveCommandSubscriberMock->getLastDriveCommand().steering, 0);

  // reset
  driveCommandSubscriberMock->trySetDriveCommand(noDrive);

  manualDriveCommandModule.setMaxDriveDuration(std::chrono::milliseconds(10));
  start = std::chrono::system_clock::now();
  manualDriveCommandModule.driveBlocking(std::chrono::milliseconds(50), -22, 40);

  // Since the timeout was set to 10ms, we should abort early -> time difference should be around 10ms
  ASSERT_GE(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start), std::chrono::milliseconds(10));
  ASSERT_LE(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start), std::chrono::milliseconds(30));

  ASSERT_EQ(driveCommandSubscriberMock->getLastDriveCommand().source, MANUAL_COMMAND);
  ASSERT_EQ(driveCommandSubscriberMock->getLastDriveCommand().speed, 0);
  ASSERT_EQ(driveCommandSubscriberMock->getLastDriveCommand().steering, 0);
}
