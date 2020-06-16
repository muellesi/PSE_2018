///////////////////////////////////////////////////////////
//  ObstacleAvoidanceModule.cpp
//  Implementation of the Class ObstacleAvoidanceModule
//  Created on:      05-Jun-2018 14:42:05
//  Original author: student
///////////////////////////////////////////////////////////

#include "ObstacleAvoidanceModule.hpp"

#include "Logging.hpp"

ObstacleAvoidanceModule::ObstacleAvoidanceModule() : DriveCommandPublisher(OBSTACLE_AVOIDANCE) {}

ObstacleAvoidanceModule::~ObstacleAvoidanceModule() = default;

void ObstacleAvoidanceModule::processData()
{
  SensorManager* sensorManager = SensorManager::getInstance();

  for (int y = 5; y < sensorManager->getSensorHeight() - 5; y += 10)
  {
    for (int x = 5; x < sensorManager->getSensorWidth() - 5; x += 10)
    {
      double depth = sensorManager->getDepth(x, y);

      if (depth != 0.0 && depth < MIN_DISTANCE)
      {
        updateSubscribers(0, 0);
        return;
      }
    }
  }
}
