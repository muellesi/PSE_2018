///////////////////////////////////////////////////////////
//  ManualModeController.cpp
//  Implementation of the Class ManualModeController
//  Created on:      05-Jun-2018 14:42:05
//  Original author: student
///////////////////////////////////////////////////////////

#include "ManualModeController.hpp"

ManualModeController::~ManualModeController() = default;

ManualModeController::ManualModeController(std::shared_ptr<DriveCommandHandler> driveCommandHandler) :
  AbstractModeController(driveCommandHandler),
  m_manualDriveCommandModule(),
  m_findMarkerModule(),
  m_isInBlockingCall(false)
{
  setMaxDriveDuration(std::chrono::milliseconds(DEFAULT_MAX_DRIVE_DURATION * 1000));

  m_manualDriveCommandModule.addSubscriber(driveCommandHandler);
  m_findMarkerModule.addSubscriber(driveCommandHandler);
}

void ManualModeController::driveBlocking(std::chrono::milliseconds duration, double velocity, double steering)
{
  m_isInBlockingCall = true;
  m_manualDriveCommandModule.driveBlocking(duration, static_cast<int>(velocity), static_cast<int>(steering));
  m_isInBlockingCall = false;
}

void ManualModeController::searchMarkerBlocking()
{
  m_isInBlockingCall = true;
  m_findMarkerModule.searchBlocking();
  m_isInBlockingCall = false;
}

void ManualModeController::setMaxDriveDuration(std::chrono::milliseconds maxDriveDuration)
{
  m_manualDriveCommandModule.setMaxDriveDuration(maxDriveDuration);
  m_findMarkerModule.setMaxDriveDuration(maxDriveDuration);
}

void ManualModeController::abort()
{
  m_manualDriveCommandModule.abort();
  m_findMarkerModule.abort();
  AbstractModeController::abort();
}

/**
 * Triggers all DriveCommandModules to process the Sensor-Data
 */
void ManualModeController::step()
{
  if (!m_isInBlockingCall)
  {
    m_driveCommandHandler->updateMotor();
  }
}
