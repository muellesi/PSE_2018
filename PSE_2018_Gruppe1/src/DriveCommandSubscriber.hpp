///////////////////////////////////////////////////////////
//  DriveCommandSubscriber.h
//  Implementation of the Class DriveCommandSubscriber
//  Created on:      05-Jun-2018 14:42:03
//  Original author: student
///////////////////////////////////////////////////////////

#pragma once

#include "DriveCommand.hpp"

/**
 * \brief DriveCommandSubscribers can receive DriveCommand structs from objects that are derived from
 * DriveCommandPublisher.
 */
class DriveCommandSubscriber
{
public:
  /**
   * \brief Creates a new DriveCommandSubscriber.
   */
  DriveCommandSubscriber() = default;

  virtual ~DriveCommandSubscriber() = default;

  /**
   * \brief "Receive handler" that gets called from all DriveCommandPublishers that this DriveCommandSubscriber is
   * subscribed to.
   * \param command The DriveCommand that has to be handled.
   */
  virtual void trySetDriveCommand(DriveCommand command) = 0;

  /**
   * \brief "Receive handler" that gets called from a DriveCommandPublisher. Forces the MotorController to execute the command.
   * \param command The DriveCommand that has to be handled.
   */
  virtual void forceDriveCommand(DriveCommand command) = 0;
};
