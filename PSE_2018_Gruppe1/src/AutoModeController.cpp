///////////////////////////////////////////////////////////
//  AutoModeController.cpp
//  Implementation of the Class AutoModeController
//  Created on:      05-Jun-2018 14:42:01
//  Original author: student
///////////////////////////////////////////////////////////

#include "AutoModeController.hpp"

AutoModeController::~AutoModeController() = default;

AutoModeController::AutoModeController(std::shared_ptr<DriveCommandHandler> driveCommandHandler) :
  AbstractModeController(driveCommandHandler),
  m_findMarkerModule(),
  m_followMarkerModule(),
  m_obstacleAvoidanceModule()
{
  setDistance(DEFAULT_DISTANCE);

  m_findMarkerModule.addSubscriber(driveCommandHandler);
  m_followMarkerModule.addSubscriber(driveCommandHandler);
  m_obstacleAvoidanceModule.addSubscriber(driveCommandHandler);
}

/**
 * Sets the desired distance to the followed marker
 * \param distance
 */
void AutoModeController::setDistance(double distance) { m_followMarkerModule.setDistance(distance); }

/**
 * Triggers all DriveCommandModules to process the Sensor-Data
 */
void AutoModeController::step()
{
  m_findMarkerModule.processData();
  m_followMarkerModule.processData();
  m_obstacleAvoidanceModule.processData();

  m_driveCommandHandler->updateMotor();
}

void AutoModeController::abort()
{
  m_followMarkerModule.abort();
  AbstractModeController::abort();
}