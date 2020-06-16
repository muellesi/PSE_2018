///////////////////////////////////////////////////////////
//  DriveCommandHandler.cpp
//  Implementation of the Class DriveCommandHandler
//  Created on:      05-Jun-2018 14:42:03
//  Original author: student
///////////////////////////////////////////////////////////

#include "Logging.hpp"
#include "DriveCommandHandler.hpp"

DriveCommandHandler::DriveCommandHandler() : m_currentDriveCommand(NO_COMMAND, 0, 0)
{
#ifdef TEST_MODE
  DIAG_INFO("Test mode enabled! Drive commands will be sent to motors directly, motor controllers are disabled.");
#endif
}

DriveCommandHandler::~DriveCommandHandler() = default;

void DriveCommandHandler::trySetDriveCommand(DriveCommand command)
{
  if (command.source >= m_currentDriveCommand.source)
  {
    m_currentDriveCommand = command;
  }
}

void DriveCommandHandler::forceDriveCommand(DriveCommand command)
{
  m_currentDriveCommand = command;
  updateMotor();
}

void DriveCommandHandler::updateMotor()
{
#ifndef TEST_MODE
  DriveController::getInstance()->updateController(m_currentDriveCommand.speed, m_currentDriveCommand.steering);
  DIAG_VERBOSE("Sent Drivecommand to Controller (%d, %d)", m_currentDriveCommand.speed, m_currentDriveCommand.steering);
#else
  DriveController::getInstance()->updateDirect(m_currentDriveCommand.speed, m_currentDriveCommand.steering);
  DIAG_VERBOSE("Sent Drivecommand to Motor (no Controller!) (%d, %d)", m_currentDriveCommand.speed, m_currentDriveCommand.steering);
#endif

  m_currentDriveCommand.source = NO_COMMAND;
}
