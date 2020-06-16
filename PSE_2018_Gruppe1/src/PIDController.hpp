///////////////////////////////////////////////////////////
//  PIDController.h
//  Implementation of the Class PIDController
//  Created on:      05-Jun-2018 14:42:05
//  Original author: student
///////////////////////////////////////////////////////////

#pragma once

/**
 * \brief Basic universal PID controller implementation
 */
class PIDController
{
public:
  /**
   * \brief Constructs a new PID controller object.
   * \param P Proportional factor.
   * \param I Integral factor.
   * \param D Differential factor.
   * \param dt Time delta between calls to calculate().
   * \param min Minimal output of controller.
   * \param max Maximal output of controller.
   * \return A new PIDController object.
   */
  PIDController(double P, double I, double D, double dt = 0.001, double min = -100.0, double max = 100.0);

  /**
   * \brief main calc function of the PIDController
   * \param error difference between target and actual values
   * \return controller output
   */
  double calculate(double error);

  /**
   * \brief Resets all errors to 0.0
   */
  void reset();

  virtual ~PIDController();

private:
  double m_d;
  double m_error;
  double m_errorDot;
  double m_i;
  double m_integralError;
  double m_p;
  double m_dt;
  double m_minVal;
  double m_maxVal;
};
