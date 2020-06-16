///////////////////////////////////////////////////////////
//  FollowMarkerModule.h
//  Implementation of the Class FollowMarkerModule
//  Created on:      05-Jun-2018 14:42:04
//  Original author: student
///////////////////////////////////////////////////////////

#pragma once

#include "DriveCommandPublisher.hpp"
#include "DataProcessModule.hpp"
#include "PIDController.hpp"

/**
 * \brief This module retrieves the markerList from the SensorManager, checks for markers and tries to follow
 * the one with the best confidence until it loses track of it.
 * After that, it follows the next marker with the highest confidence.
 */
class FollowMarkerModule : public DriveCommandPublisher, public DataProcessModule
{
public:
  /**
   * \brief Constructs a new FollowMarkerModule.
   */
  FollowMarkerModule();

  ~FollowMarkerModule() override;

  /**
   * \brief Main update function that gets called periodically.
   */
  void processData() override;

  /**
   * \brief Sets the desired distance that will be used as for the distance PIDController.
   * \param distance Desired distance in [m].
   */
  void setDistance(double distance);

  /**
   * \brief CURRENTLEY NOT IN USE! Sets an ID for a marker that will be followed.
   */
  void setMarkerId(int markerId);

  /**
   * \brief Resets both PID controllers
   */
  void abort();

private:
  double m_setDistance;
  bool m_followsMarker;
  int m_currentMarkerId;

  PIDController m_distanceController;
  PIDController m_steeringController;
};
