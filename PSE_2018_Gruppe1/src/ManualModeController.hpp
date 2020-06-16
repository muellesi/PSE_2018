///////////////////////////////////////////////////////////
//  ManualModeController.h
//  Implementation of the Class ManualModeController
//  Created on:      05-Jun-2018 14:42:04
//  Original author: student
///////////////////////////////////////////////////////////

#pragma once

#include "DriveCommandHandler.hpp"
#include "ManualDriveCommandModule.hpp"
#include "AbstractModeController.hpp"
#include "FindMarkerModule.hpp"

/**
 * brief Child of AbstractModeController that is used for manual operation.
 */
class ManualModeController : public AbstractModeController
{
public:
  ~ManualModeController() override;

  /**
   * \brief Constructs a new ManualModeController.
   * \param driveCommandHandler Used to wire up publishers in manual mode (publish-subscribe).
   */
  explicit ManualModeController(std::shared_ptr<DriveCommandHandler> driveCommandHandler);

  /**
   * \brief Drives for the given time with the given parameters.
   * \param duration Duration in milliseconds for the drive operation.
   * \param velocity Desired velocity for the drive operation (range: -100...100).
   * \param steering Desired direction for the drive operation as a ratio between left and right motor speeds (range:
   * -100...100).
   */
  void driveBlocking(std::chrono::milliseconds duration, double velocity, double steering);

  /**
   * \brief Triggers a search for a Marker. Returns, when marker has found or maximum time has exceeded.
   */
  void searchMarkerBlocking();

  /**
   * \brief Sets the maximum duration this module is allowed to execute operations without user interaction.
   * \param maxDriveDuration Duration in milliseconds.
   */
  void setMaxDriveDuration(std::chrono::milliseconds maxDriveDuration);

  /**
   * \brief Aborts all currently running operations.
   */
  void abort() override;

  /**
   * \brief Has to be called in a loop for continuous execution of the controller.
   */
  void step() override;

private:
  ManualDriveCommandModule m_manualDriveCommandModule;
  FindMarkerModule m_findMarkerModule;
  std::atomic<bool> m_isInBlockingCall;

  static constexpr int DEFAULT_MAX_DRIVE_DURATION = 10;
};
