///////////////////////////////////////////////////////////
//  AbstractModeController.h
//  Implementation of the Class AbstractModeController
//  Created on:      05-Jun-2018 14:42:01
//  Original author: student
///////////////////////////////////////////////////////////

#pragma once

#include "DriveCommandHandler.hpp"
#include "FindMarkerModule.hpp"
#include "FollowMarkerModule.hpp"
#include "ObstacleAvoidanceModule.hpp"
#include <memory>

/**
 * \brief Abstract base class for AutoModeController and ManualModeController.
 */
class AbstractModeController
{
public:
  virtual ~AbstractModeController();

  /**
   * \brief Constructor for AbstractModeController. All ModeControllers need a DriveCommandHandler
   * in order to wire up their submodules (publish-subscribe).
   * \param driveCommandHandler A pointer to the DriveCommandHandler that was instantiated in main.c.
   */
  explicit AbstractModeController(std::shared_ptr<DriveCommandHandler> driveCommandHandler);

  /**
   * \brief Aborts the execution of the AbstractModeController.
   * All ModeControllers have to be abortable in case that the user presses ctrl + c.
   */
  virtual void abort();

  /**
   * \brief Has to be called in a loop for continuous execution of the controller.
   */
  virtual void step() = 0;

protected:
  const std::shared_ptr<DriveCommandHandler> m_driveCommandHandler;
};
