///////////////////////////////////////////////////////////
//  DataProcessModule.h
//  Implementation of the Class DataProcessModule
//  Created on:      05-Jun-2018 14:42:02
//  Original author: student
///////////////////////////////////////////////////////////

#pragma once

#include "SensorManager.hpp"

/**
 * \brief All automatic mode modules that have to work with data from the SensorManager use this base class as their
 * interface.
 */
class DataProcessModule
{
public:
  /**
   * \brief Pure virtual interface method that has to be implemented by every module that uses the SensorManager.
   * Caller must ensure that SensorManager::runOnce() has been called before.
   */
  virtual void processData() = 0;

private:
};
