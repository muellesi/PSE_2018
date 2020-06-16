#include <gtest/gtest.h>
#include <DriveCommandSubscriberMock.hpp>
#include "../FindMarkerModule.hpp"

/**
 * \brief Tests whether FindMarkerModule correctly recognizes a marker that is supplied via the MarkerList
 */
TEST(FindMarkerModuleTest, findMarkerTest)
{
  DriveController driveControllerMock;
  std::shared_ptr<DriveCommandHandler> handler = std::make_shared<DriveCommandHandler>();
  FindMarkerModule findMarkerModule;

  std::shared_ptr<DriveCommandSubscriberMock> driveCommandSubscriberMock = std::make_shared<DriveCommandSubscriberMock>();
  findMarkerModule.addSubscriber(driveCommandSubscriberMock);

  // set command to no drive
  DriveCommand noDrive(NO_COMMAND, 0, 0);
  driveCommandSubscriberMock->trySetDriveCommand(noDrive);

  std::vector<MarkerInfo> markerInfoList;  // first empty marker info list
  SensorManager::getInstance()->setDebugMarkerInfoList(markerInfoList);

  findMarkerModule.processData();

  ASSERT_EQ(driveCommandSubscriberMock->getLastDriveCommand().source, FIND_MARKER);
  ASSERT_EQ(driveCommandSubscriberMock->getLastDriveCommand().speed, 15);
  ASSERT_EQ(driveCommandSubscriberMock->getLastDriveCommand().steering, 100);

  // reset
  driveCommandSubscriberMock->trySetDriveCommand(noDrive);

  BoundingBox boundingBox(1, 2, 3, 4, 5);
  MarkerInfo markerInfo;
  markerInfo.m_Marker     = boundingBox;
  markerInfo.m_Confidence = 50;

  markerInfoList.push_back(markerInfo);
  SensorManager::getInstance()->setDebugMarkerInfoList(markerInfoList);

  findMarkerModule.processData();

  ASSERT_EQ(driveCommandSubscriberMock->getLastDriveCommand().source, NO_COMMAND);
  ASSERT_EQ(driveCommandSubscriberMock->getLastDriveCommand().speed, 0);
  ASSERT_EQ(driveCommandSubscriberMock->getLastDriveCommand().steering, 0);
}

/**
 * \brief Same as above but for the manual mode blocking version
 */
TEST(FindMarkerModuleTest, findMarkerBlockingTest)
{
  DriveController driveControllerMock;
  std::shared_ptr<DriveCommandHandler> handler = std::make_shared<DriveCommandHandler>();
  FindMarkerModule findMarkerModule;

  std::shared_ptr<DriveCommandSubscriberMock> driveCommandSubscriberMock = std::make_shared<DriveCommandSubscriberMock>();
  findMarkerModule.addSubscriber(driveCommandSubscriberMock);

  // set command to no drive
  DriveCommand noDrive(NO_COMMAND, 0, 0);
  driveCommandSubscriberMock->trySetDriveCommand(noDrive);

  std::vector<MarkerInfo> markerInfoList;  // first empty marker info list
  SensorManager::getInstance()->setDebugMarkerInfoList(markerInfoList);

  // No marker available so the search should should run longer than or exactly 100ms
  findMarkerModule.setMaxDriveDuration(std::chrono::milliseconds(100));
  std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
  findMarkerModule.searchBlocking();

  ASSERT_GE(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start), std::chrono::milliseconds(100));

  ASSERT_EQ(driveCommandSubscriberMock->getLastDriveCommand().source, FIND_MARKER);
  ASSERT_EQ(driveCommandSubscriberMock->getLastDriveCommand().speed, 0);  // 0 because motor has to be stopped!
  ASSERT_EQ(driveCommandSubscriberMock->getLastDriveCommand().steering, 0);

  // reset
  driveCommandSubscriberMock->trySetDriveCommand(noDrive);

  BoundingBox boundingBox(1, 2, 3, 4, 5);
  MarkerInfo markerInfo;
  markerInfo.m_Marker     = boundingBox;
  markerInfo.m_Confidence = 50;

  markerInfoList.push_back(markerInfo);
  SensorManager::getInstance()->setDebugMarkerInfoList(markerInfoList);

  // Now a marker is available so the marker search should abort pretty fast
  start = std::chrono::system_clock::now();
  findMarkerModule.searchBlocking();
  ASSERT_LE(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start), std::chrono::milliseconds(10));

  ASSERT_EQ(driveCommandSubscriberMock->getLastDriveCommand().source, FIND_MARKER);
  ASSERT_EQ(driveCommandSubscriberMock->getLastDriveCommand().speed, 0);
  ASSERT_EQ(driveCommandSubscriberMock->getLastDriveCommand().steering, 0);
}
