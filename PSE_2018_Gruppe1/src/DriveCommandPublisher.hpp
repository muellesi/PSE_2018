///////////////////////////////////////////////////////////
//  DriveCommandPublisher.h
//  Implementation of the Class DriveCommandPublisher
//  Created on:      05-Jun-2018 14:42:03
//  Original author: student
///////////////////////////////////////////////////////////

#pragma once

#include <vector>
#include <memory>
#include "DriveCommandSubscriber.hpp"

/**
 * \brief Base class for all classes that are able to publish DriveCommands to a DriveCommandSubscriber.
 */
class DriveCommandPublisher
{
public:
  virtual ~DriveCommandPublisher();

  /**
   * \brief Constructs a new DriveCommandPublisher with a given Type.
   * \param type Will be used for the "source" field in the DriveCommand struct.
   * Subscribers may prioritize by source type.
   */
  explicit DriveCommandPublisher(DriveCommandPublisherType type);

  /**
   * \brief Adds a new subscriber to the list of DriveCommandSubscribers.
   * \param subscriber Which class to add to the list.
   */
  void addSubscriber(std::shared_ptr<DriveCommandSubscriber> subscriber);

protected:
  /**
   * \brief Pushes a new DriveCommand with this class' DriveCommandPublisherType, speed and steering to all registered.
   * subscribers.
   * \param speed The desired speed that this object wants to set.
   * \param steering The desired steering.
   */
  void updateSubscribers(int speed, int steering);

  /**
   * \brief Forces a new DriveCommand with this classes DriveCommandPublisherType, speed and steering to all registered
   * subscribers.
   * \param speed The desired speed that this object wants to set.
   * \param steering The desired steering.
   */
  void forceSubscribers(int speed, int steering);

private:
  const DriveCommandPublisherType m_driveCommandPublisherType;          /// Used for the source field in DriveCommand messages.
  std::vector<std::shared_ptr<DriveCommandSubscriber> > m_subscribers;  /// List of all DriveCommandSubscriber objects
                                                                        /// that want to receive data from us.
};
