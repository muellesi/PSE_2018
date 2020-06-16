///////////////////////////////////////////////////////////
//  DriveCommandHandler.h
//  Implementation of the Class DriveCommandHandler
//  Created on:      05-Jun-2018 14:42:03
//  Original author: student
///////////////////////////////////////////////////////////

#pragma once

#include <chrono>

#include "DriveCommand.hpp"
#include "DriveCommandSubscriber.hpp"
#include "DriveController.hpp"

/**
 * \brief This class can receive DriveCommand structures, prioritizes them by their source.
 * and forwards the values to the DriveController once updateMotor() gets called.
 */
class DriveCommandHandler : public DriveCommandSubscriber
{
public:
  /**
   * \brief Initializes the currentDriveCommand with MANUAL_COMMAND, (speed)=0, (steering)=0.
   */
  DriveCommandHandler();

  ~DriveCommandHandler() override;

  /**
   * \brief Accepts a DriveCommand from a DriveCommandPublisher.
   * If its priority is higher than the last DriveCommand received after the last call to updateMotor(),
   * the old DriveCommand is discarded and the new one is saved instead.
   * \param command The DriveCommand as suggested by one of the DriveCommandPublishers.
   */
  void trySetDriveCommand(DriveCommand command) override;

  /**
   * \brief Flushes the currently held DriveCommand to the DriveController.
   */
  void updateMotor();

  /**
   * \brief Forces a specific drive command to be executed instead of suggesting it like in trySetDriveCommand().
   * \param command The DriveCommand to be executed.
   */
  void forceDriveCommand(DriveCommand command) override;

private:
  DriveCommand m_currentDriveCommand;  // Buffer for the drive command with the highest priority. Flushed by updateMotor()
};
