///////////////////////////////////////////////////////////
//  DriveCommand.h
//  Implementation of the Class DriveCommand
//  Created on:      05-Jun-2018 14:42:02
//  Original author: student
///////////////////////////////////////////////////////////

#pragma once

#include "DriveCommandPublisherType.hpp"

/**
 * \brief This struct is used during communication between DriveCommandPublishers and DriveCommandSubscribers
 */
struct DriveCommand
{
public:
  /**
   * \brief Constructs a new DriveCommand for publishing to a DriveCommandSubscriber.
   * \param source The DriveCommandPublisherType of the publishing object.
   * \param speed The desired speed (range: -100...100).
   * \param steering The desired ratio between left and right motor speed (range: -100...100).
   */
  DriveCommand(DriveCommandPublisherType source, int speed, int steering) :
    source(source),
    speed(speed),
    steering(steering)
  {
  }

  DriveCommandPublisherType source;  /// the DriveCommandSubscriber can use this to assign priorities to the modules
  int speed;
  int steering;
};
