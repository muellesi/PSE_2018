///////////////////////////////////////////////////////////
//  FindMarkerModule.cpp
//  Implementation of the Class FindMarkerModule
//  Created on:      05-Jun-2018 14:42:04
//  Original author: student
///////////////////////////////////////////////////////////
#include <thread>

#include "FindMarkerModule.hpp"
#include "Logging.hpp"

FindMarkerModule::FindMarkerModule() : DriveCommandPublisher(FIND_MARKER), m_maxDuration(0), m_stop(false) {}

FindMarkerModule::~FindMarkerModule() = default;

void FindMarkerModule::abort() { m_stop = true; }

void FindMarkerModule::processData()
{
  if (!foundMarker())
  {
    updateSubscribers(SEARCH_SPEED, 100);
  }
}

void FindMarkerModule::searchBlocking()
{
  m_stop                                                   = false;
  std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

  while (!m_stop)
  {
    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start) >= m_maxDuration)
    {
      DIAG_WARNING("Stopped Marker Searching because maximum drive time has exceeded!");
      break;
    }

    SensorManager::getInstance()->runOnce();

    if (!foundMarker() && !m_stop)
    {
      forceSubscribers(SEARCH_SPEED, 100);
    }
    else
    {
      break;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(5));
  }

  forceSubscribers(0, 0);
}

void FindMarkerModule::setMaxDriveDuration(std::chrono::milliseconds duration) { m_maxDuration = duration; }

bool FindMarkerModule::foundMarker()
{
  bool found = false;
  if (!SensorManager::getInstance()->getMarkerList().empty())
  {
    for (auto marker : SensorManager::getInstance()->getMarkerList())
    {
      if (marker.m_Confidence >= MINIMUM_CONFIDENT)
      {
        found = true;
      }
    }
  }

  return found;
}
