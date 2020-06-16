///////////////////////////////////////////////////////////
//  PIDController.cpp
//  Implementation of the Class PIDController
//  Created on:      05-Jun-2018 14:42:05
//  Original author: student
///////////////////////////////////////////////////////////

#include <limits>

#include "MathFunctions.hpp"
#include "PIDController.hpp"

PIDController::PIDController(double P, double I, double D, double dt, double min, double max) :
  m_d(D),
  m_error(0.0),
  m_errorDot(0.0),
  m_i(I),
  m_integralError(0.0),
  m_p(P),
  m_dt(dt),
  m_minVal(min),
  m_maxVal(max)
{
}

PIDController::~PIDController() = default;

double PIDController::calculate(double error)
{
  m_integralError += error;
  m_integralError = LimitBetween(m_integralError,
                                 -100.0 * m_i,
                                 100.0 * m_i);  ///< Integrate errors as long as the result does not overflow
  m_errorDot      = error - m_error;
  m_error         = error;

  double res = m_p * m_error + m_i * m_integralError + m_d * m_errorDot;

  return LimitBetween(res, m_minVal, m_maxVal);
}

void PIDController::reset()
{
  m_error         = 0.0;
  m_errorDot      = 0.0;
  m_integralError = 0.0;
}
