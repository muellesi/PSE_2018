///////////////////////////////////////////////////////////
//  ObstacleAvoidanceModule.h
//  Implementation of the Class ObstacleAvoidanceModule
//  Created on:      05-Jun-2018 14:42:05
//  Original author: student
///////////////////////////////////////////////////////////

#pragma once

#include "DriveCommandPublisher.hpp"
#include "DataProcessModule.hpp"

/**
 * \brief Used in automatic mode to detect and avoid obstacles during automatic driving operations.
 * Publishes DriveCommands if an obstacle is detected and actively tries to turn away from the obstacle.
 */
class ObstacleAvoidanceModule : public DriveCommandPublisher, public DataProcessModule
{
public:
  /**
   * \brief Constructs a new ObstacleAvoidanceModule.
   */
  ObstacleAvoidanceModule();

  ~ObstacleAvoidanceModule() override;

  /**
   * \brief Triggers input data processing.
   */
  void processData() override;

private:
  static constexpr double MIN_DISTANCE = 0.6;
};
