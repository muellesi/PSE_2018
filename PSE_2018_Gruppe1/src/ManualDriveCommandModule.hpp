///////////////////////////////////////////////////////////
//  ManualDriveCommandModule.h
//  Implementation of the Class ManualDriveCommandModule
//  Created on:      05-Jun-2018 14:42:04
//  Original author: student
///////////////////////////////////////////////////////////

#pragma once

#include <chrono>
#include <atomic>
#include <memory>

#include "DriveCommandPublisher.hpp"
#include "DriveCommandHandler.hpp"

/**
 * \brief This module is used for blocking drive operations via terminal command or script and can only be invoked via
 * terminal.
 */
class ManualDriveCommandModule : public DriveCommandPublisher
{
public:
  /**
   * \brief Constructs a new ManualDriveCommandModule.
   */
  ManualDriveCommandModule();

  ~ManualDriveCommandModule() override;

  /**
   * \brief Aborts all blocking operations that might still be running.
   */
  void abort();

  /**
   * \brief Sends DriveCommand structs for the given time and blocks the calling thread.
   * \param time Time to drive in milliseconds.
   * \param velocity Desired speed.
   * \param steering Desired direction (as ratio between left/right motor speed).
   */
  void driveBlocking(std::chrono::milliseconds time, int velocity, int steering);

  /**
   * \brief Sets the maximum duration this module is allowed to drive without user interaction.
   * \param duration Maximum allowed time for command execution in milliseconds.
   */
  void setMaxDriveDuration(std::chrono::milliseconds duration);

private:
  std::chrono::milliseconds m_maxDuration;
  std::atomic<bool> m_Stop;
};
