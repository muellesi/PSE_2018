///////////////////////////////////////////////////////////
//  ManualDriveCommandModule.cpp
//  Implementation of the Class ManualDriveCommandModule
//  Created on:      05-Jun-2018 14:42:04
//  Original author: student
///////////////////////////////////////////////////////////

#include <thread>

#include "ManualDriveCommandModule.hpp"
#include "Logging.hpp"

ManualDriveCommandModule::ManualDriveCommandModule() : DriveCommandPublisher(MANUAL_COMMAND), m_maxDuration(0), m_Stop(false) {}

ManualDriveCommandModule::~ManualDriveCommandModule() = default;

void ManualDriveCommandModule::abort() { m_Stop = true; }

void ManualDriveCommandModule::driveBlocking(std::chrono::milliseconds time, int velocity, int steering)
{
  m_Stop = false;

  std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

  while (!m_Stop && std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start) < time)
  {
    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start) >= m_maxDuration)
    {
      DIAG_WARNING("Stopped manual driving because maximum drive time has exceeded!");
      break;
    }

    forceSubscribers(velocity, steering);

    std::this_thread::sleep_for(std::chrono::milliseconds(5));
  }

  forceSubscribers(0, 0);
}

void ManualDriveCommandModule::setMaxDriveDuration(std::chrono::milliseconds duration) { m_maxDuration = duration; }
