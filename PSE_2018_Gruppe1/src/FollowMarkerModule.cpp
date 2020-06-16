///////////////////////////////////////////////////////////
//  FollowMarkerModule.cpp
//  Implementation of the Class FollowMarkerModule
//  Created on:      05-Jun-2018 14:42:04
//  Original author: student
///////////////////////////////////////////////////////////

#include <vector>

#include "SensorManager.hpp"

#include "FollowMarkerModule.hpp"
#include "MathFunctions.hpp"

FollowMarkerModule::FollowMarkerModule() :
  DriveCommandPublisher(FOLLOW_MARKER),
  m_setDistance(0),
  m_followsMarker(false),
  m_currentMarkerId(0),
  m_distanceController(30.0, 0.01, 0.5),  // TODO: set correct params
  m_steeringController(0.3, 0.0, 0.5)     // TODO: set correct params
{
}

FollowMarkerModule::~FollowMarkerModule() = default;

/**
 * \brief gets a list of markers and steers towards the marker with the highest confidence value
 */
void FollowMarkerModule::processData()
{
  std::vector<MarkerInfo> markerList = SensorManager::getInstance()->getMarkerList();

  // No markers available, nothing to do!
  if (markerList.empty())
  {
    m_followsMarker = false;
    return;
  }

  MarkerInfo targetMarker;

  // Are we already following a marker? Try to find it in the marker list
  if (m_followsMarker)
  {
    for (auto marker : markerList)
    {
      if (marker.m_Marker.getRegionID() == m_currentMarkerId)
      {
        targetMarker = marker;
      }
    }
    // Our marker was not in the list so we need to find a new one to follow
    m_followsMarker = false;
  }

  // In case we don't have a marker we are currently following, try to find a new one
  if (!m_followsMarker)
  {
    targetMarker = markerList[0];

    for (auto marker : markerList)
    {
      if (marker.m_Confidence > targetMarker.m_Confidence)
      {
        targetMarker    = marker;
        m_followsMarker = true;
        break;  // for more performance over 9000
      }
    }
  }

  // Use center of marker bounding box as "marker position"
  double markerCenterX = static_cast<double>(targetMarker.m_Marker.x()) + (static_cast<double>(targetMarker.m_Marker.getWidth()) / 2.0);
  double markerCenterY = static_cast<double>(targetMarker.m_Marker.y()) + (static_cast<double>(targetMarker.m_Marker.getHeight()) / 2.0);

  // calculate error of steering
  double steerSetX   = static_cast<double>(SensorManager::getInstance()->getSensorWidth()) / 2.0;
  double steerErrorX = markerCenterX - steerSetX;

  // now calculate distance error
  double markerDepthDist = SensorManager::getInstance()->getDepth(static_cast<int>(markerCenterX), static_cast<int>(markerCenterY));
  double distErrorDepth  = markerDepthDist - m_setDistance;

  double steerCtrl = LimitBetween(m_steeringController.calculate(steerErrorX), -100.0, 100.0);
  double distCtrl  = LimitBetween(m_distanceController.calculate(distErrorDepth), -100.0, 100.0);

  this->updateSubscribers(static_cast<int>(distCtrl), static_cast<int>(steerCtrl));
}

void FollowMarkerModule::setDistance(double distance) { this->m_setDistance = distance; }

void FollowMarkerModule::setMarkerId(int markerId) { this->m_currentMarkerId = markerId; }

void FollowMarkerModule::abort()
{
  m_distanceController.reset();
  m_steeringController.reset();
}
