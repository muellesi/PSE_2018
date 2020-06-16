///////////////////////////////////////////////////////////
//  DriveCommandPublisher.cpp
//  Implementation of the Class DriveCommandPublisher
//  Created on:      05-Jun-2018 14:42:03
//  Original author: student
///////////////////////////////////////////////////////////

#include "DriveCommandPublisher.hpp"

DriveCommandPublisher::~DriveCommandPublisher() = default;

DriveCommandPublisher::DriveCommandPublisher(DriveCommandPublisherType type) : m_driveCommandPublisherType(type), m_subscribers() {}

void DriveCommandPublisher::addSubscriber(std::shared_ptr<DriveCommandSubscriber> subscriber) { m_subscribers.emplace_back(subscriber); }

void DriveCommandPublisher::updateSubscribers(int speed, int steering)
{
  DriveCommand command(m_driveCommandPublisherType, speed, steering);

  for (const auto& subscriber : m_subscribers)
  {
    subscriber->trySetDriveCommand(command);
  }
}

void DriveCommandPublisher::forceSubscribers(int speed, int steering)
{
  DriveCommand command(m_driveCommandPublisherType, speed, steering);

  for (const auto& subscriber : m_subscribers)
  {
    subscriber->forceDriveCommand(command);
  }
}
