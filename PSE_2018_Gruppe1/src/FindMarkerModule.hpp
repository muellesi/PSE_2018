///////////////////////////////////////////////////////////
//  FindMarkerModule.h
//  Implementation of the Class FindMarkerModule
//  Created on:      05-Jun-2018 14:42:04
//  Original author: student
///////////////////////////////////////////////////////////

#pragma once

#include <atomic>
#include <chrono>
#include "DriveCommandPublisher.hpp"
#include "DataProcessModule.hpp"
#include "DriveCommandHandler.hpp"

/**
 * \brief This module can be active in manual and in auto mode.
 * It rotates the TivSeg until it detects at least one marker.
 */
class FindMarkerModule : public DriveCommandPublisher, public DataProcessModule
{
public:
  /**
   * \brief Constructs a new FindMarkerModule.
   */
  FindMarkerModule();

  ~FindMarkerModule() override;

  /**
   * \brief Aborts execution of the currently running blocking marker search.
   */
  void abort();

  /**
   * \brief Main update function that gets called from mainloop.
   */
  void processData() override;

  /**
   * \brief Triggers a blocking marker search.
   * Returns if a Marker has been found or maximum drive duration has exceeded.
   */
  void searchBlocking();

  /**
   * \brief Sets the maximum duration.
   * \param duration The allowed duration in milliseconds.
   */
  void setMaxDriveDuration(std::chrono::milliseconds duration);

private:
  /**
   * \brief Retrieves the sensorList from SensorManager and checks whether it is not empty.
   * \return Marker list not empty? -> At least one marker was found -> true. Marker list empty? -> No marker -> false.
   */
  static bool foundMarker();

  std::chrono::milliseconds m_maxDuration;  /// Maximum time this module can work in blocking mode until it aborts.
  std::atomic<bool> m_stop;                 /// Used in blocking mode to abort operation.

  static const int SEARCH_SPEED      = 15;
  static const int MINIMUM_CONFIDENT = 50;
};
