#include <gtest/gtest.h>
#include <DriveCommandSubscriberMock.hpp>

#include "../FollowMarkerModule.hpp"

/**
 * \brief If there is no marker for the FollowMarkerModule to find, it should not send any commands
 */
TEST(FollowMarkerModuleTest, no_marker)
{
  std::shared_ptr<DriveCommandSubscriberMock> driveCommandSubscriberMock = std::make_shared<DriveCommandSubscriberMock>();
  FollowMarkerModule followMarkerModule;

  followMarkerModule.addSubscriber(driveCommandSubscriberMock);
  followMarkerModule.setDistance(1.0);

  std::vector<MarkerInfo> mockMarkerList;
  SensorManager::getInstance()->setDebugMarkerInfoList(mockMarkerList);

  followMarkerModule.processData();

  ASSERT_EQ(driveCommandSubscriberMock->getLastDriveCommand().source, NO_COMMAND);
  ASSERT_EQ(driveCommandSubscriberMock->getLastDriveCommand().speed, 0);
  ASSERT_EQ(driveCommandSubscriberMock->getLastDriveCommand().steering, 0);
}

/**
 * \brief If the marker is to the right of the sensor's center, FindMarkerModule should
 * start commanding values that make the robot steer right
 */
TEST(FollowMarkerModuleTest, marker_right)
{
  std::shared_ptr<DriveCommandSubscriberMock> driveCommandSubscriberMock = std::make_shared<DriveCommandSubscriberMock>();
  FollowMarkerModule followMarkerModule;

  int imageCenterX = SensorManager::getInstance()->getSensorWidth() / 2;
  int imageCenterY = SensorManager::getInstance()->getSensorHeight() / 2;

  MarkerInfo mockMarker;
  mockMarker.m_Confidence = 50;
  mockMarker.m_Marker     = BoundingBox(imageCenterX + 40, imageCenterY, 10, 10, 1);  // marker 10px to the right of center

  std::vector<MarkerInfo> mockMarkerList;
  mockMarkerList.emplace_back(mockMarker);

  SensorManager::getInstance()->setDebugMarkerInfoList(mockMarkerList);
  SensorManager::getInstance()->setDepth(2);

  followMarkerModule.addSubscriber(driveCommandSubscriberMock);
  followMarkerModule.setDistance(1.0);

  followMarkerModule.processData();

  ASSERT_EQ(driveCommandSubscriberMock->getLastDriveCommand().source, FOLLOW_MARKER);
  ASSERT_GT(driveCommandSubscriberMock->getLastDriveCommand().speed, 0);
  ASSERT_GT(driveCommandSubscriberMock->getLastDriveCommand().steering, 0);  // steering > 0 --> steer to the right
}

/**
 * \brief Check whether the FollowMarkerModule correctly commands negative
 * steering values if we have a marker to the left
 */
TEST(FollowMarkerModuleTest, marker_left)
{
  std::shared_ptr<DriveCommandSubscriberMock> driveCommandSubscriberMock = std::make_shared<DriveCommandSubscriberMock>();
  FollowMarkerModule followMarkerModule;

  int imageCenterX = SensorManager::getInstance()->getSensorWidth() / 2;
  int imageCenterY = SensorManager::getInstance()->getSensorHeight() / 2;

  MarkerInfo mockMarker;
  mockMarker.m_Confidence = 50;
  mockMarker.m_Marker     = BoundingBox(imageCenterX - 40, imageCenterY, 10, 10, 1);  // set marker 40px to the left

  std::vector<MarkerInfo> mockMarkerList;
  mockMarkerList.emplace_back(mockMarker);

  SensorManager::getInstance()->setDebugMarkerInfoList(mockMarkerList);
  SensorManager::getInstance()->setDepth(2);

  followMarkerModule.addSubscriber(driveCommandSubscriberMock);
  followMarkerModule.setDistance(1.0);

  followMarkerModule.processData();

  ASSERT_EQ(driveCommandSubscriberMock->getLastDriveCommand().source, FOLLOW_MARKER);
  ASSERT_GT(driveCommandSubscriberMock->getLastDriveCommand().speed, 0);
  ASSERT_LT(driveCommandSubscriberMock->getLastDriveCommand().steering, 0);  // we should now steer left (steer < 0)
}

/**
 * \brief If we are closer to the marker than we should be, FollowMarkerModeul should emit commands
 * that make the robot drive back
 */
TEST(FollowMarkerModuleTest, marker_near)
{
  std::shared_ptr<DriveCommandSubscriberMock> driveCommandSubscriberMock = std::make_shared<DriveCommandSubscriberMock>();
  FollowMarkerModule followMarkerModule;

  int imageCenterX = SensorManager::getInstance()->getSensorWidth() / 2;
  int imageCenterY = SensorManager::getInstance()->getSensorHeight() / 2;

  MarkerInfo mockMarker;
  mockMarker.m_Confidence = 50;
  mockMarker.m_Marker     = BoundingBox(imageCenterX - 5, imageCenterY - 5, 10, 10, 1);

  std::vector<MarkerInfo> mockMarkerList;
  mockMarkerList.emplace_back(mockMarker);

  SensorManager::getInstance()->setDebugMarkerInfoList(mockMarkerList);
  SensorManager::getInstance()->setDepth(0.5);  // mock a marker that is 0.5m away

  followMarkerModule.addSubscriber(driveCommandSubscriberMock);
  followMarkerModule.setDistance(1.0);  // we want it to be 1m away so the module should command negative speed

  followMarkerModule.processData();

  ASSERT_EQ(driveCommandSubscriberMock->getLastDriveCommand().source, FOLLOW_MARKER);
  ASSERT_LT(driveCommandSubscriberMock->getLastDriveCommand().speed, 0);  // speed < 0 --> move backwards
  ASSERT_EQ(driveCommandSubscriberMock->getLastDriveCommand().steering, 0);
}

/**
 * \brief Check whether the FollowMarkerModule correctly drives towards a marker
 * if the desired distance has not yet been reached
 */
TEST(FollowMarkerModuleTest, marker_far)
{
  std::shared_ptr<DriveCommandSubscriberMock> driveCommandSubscriberMock = std::make_shared<DriveCommandSubscriberMock>();
  FollowMarkerModule followMarkerModule;

  int imageCenterX = SensorManager::getInstance()->getSensorWidth() / 2;
  int imageCenterY = SensorManager::getInstance()->getSensorHeight() / 2;

  MarkerInfo mockMarker;
  mockMarker.m_Confidence = 50;
  mockMarker.m_Marker     = BoundingBox(imageCenterX - 5, imageCenterY - 5, 10, 10, 1);

  std::vector<MarkerInfo> mockMarkerList;
  mockMarkerList.emplace_back(mockMarker);

  SensorManager::getInstance()->setDebugMarkerInfoList(mockMarkerList);
  SensorManager::getInstance()->setDepth(5);  // mock a marker that is 5m away

  followMarkerModule.addSubscriber(driveCommandSubscriberMock);
  followMarkerModule.setDistance(1.0);  // we want it to be 1m away so the module should command positive speed

  followMarkerModule.processData();

  ASSERT_EQ(driveCommandSubscriberMock->getLastDriveCommand().source, FOLLOW_MARKER);
  ASSERT_GT(driveCommandSubscriberMock->getLastDriveCommand().speed, 0);
  ASSERT_EQ(driveCommandSubscriberMock->getLastDriveCommand().steering, 0);
}
