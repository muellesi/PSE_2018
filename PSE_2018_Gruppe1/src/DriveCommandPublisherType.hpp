///////////////////////////////////////////////////////////
//  DriveCommandPublisherType.h
//  Implementation of the Enumeration DriveCommandPublisherType
//  Created on:      05-Jun-2018 14:42:03
//  Original author: student
///////////////////////////////////////////////////////////

#pragma once

/**
 * \brief The DriveCommand types, with following priorities
 * low:     FIND_MARKER
 *          FOLLOW_MARKER
 *          OBSTACLE_AVOIDANCE
 * high:    MANUAL_COMMAND
 */
enum DriveCommandPublisherType
{
  NO_COMMAND         = 0x0,
  FIND_MARKER        = 0x1,
  FOLLOW_MARKER      = 0x2,
  OBSTACLE_AVOIDANCE = 0x3,
  MANUAL_COMMAND     = 0x4
};
