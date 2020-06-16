///////////////////////////////////////////////////////////
//  AbstractModeController.cpp
//  Implementation of the Class AbstractModeController
//  Created on:      05-Jun-2018 14:42:01
//  Original author: student
///////////////////////////////////////////////////////////

#include "AbstractModeController.hpp"

AbstractModeController::~AbstractModeController() = default;

AbstractModeController::AbstractModeController(std::shared_ptr<DriveCommandHandler> driveCommandHandler) : m_driveCommandHandler(driveCommandHandler)
{
}

void AbstractModeController::abort()
{
  DriveCommand abortCommand(MANUAL_COMMAND, 0, 0);
  m_driveCommandHandler->forceDriveCommand(abortCommand);
}
