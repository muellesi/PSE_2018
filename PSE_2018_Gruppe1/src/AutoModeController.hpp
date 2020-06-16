///////////////////////////////////////////////////////////
//  AutoModeController.h
//  Implementation of the Class AutoModeController
//  Created on:      05-Jun-2018 14:42:01
//  Original author: student
///////////////////////////////////////////////////////////

#pragma once

#include "DriveCommandHandler.hpp"
#include "AbstractModeController.hpp"
#include "ObstacleAvoidanceModule.hpp"
#include "FollowMarkerModule.hpp"
#include "FindMarkerModule.hpp"

/**
 * \brief Controls the execution of all three submodules in automatic driving mode.
 */
class AutoModeController : public AbstractModeController
{
public:
  ~AutoModeController() override;

  /**
   * \brief Constructs a new AutoModeController.
   * \param driveCommandHandler Is needed to wire up the three submodules to publish DriveCommands.
   */
  explicit AutoModeController(std::shared_ptr<DriveCommandHandler> driveCommandHandler);

  /**
   * \brief Sets the desired distance for the MarkerFollowModule.
   * \param distance Desired distance value in [m].
   */
  void setDistance(double distance);

  /**
   * \brief Has to be called in a loop for continuous execution of the controller.
   */
  void step() override;

  /**
   * \brief Implements the abort() method from AbstractModeController and calls FollowMarkerModule::abort()
   */
  void abort() override;

protected:
  FindMarkerModule m_findMarkerModule;
  FollowMarkerModule m_followMarkerModule;
  ObstacleAvoidanceModule m_obstacleAvoidanceModule;

  static constexpr double DEFAULT_DISTANCE = 0.3;
};
