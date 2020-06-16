///////////////////////////////////////////////////////////
//  MathFunctions.h
//  Implementation math functions
//  Created on:      12-Jun-2018 14:42:04
//  Original author: student
///////////////////////////////////////////////////////////

#pragma once

/**
 * \brief Limits two arbitrary values between lowerBound and upperBound (inclusive the borders).
 * \tparam t Value types (most of the time implicitly inferred by the compiler).
 * \param val Value that has to be limited.
 * \param lowerBound Lower boundary for the return value.
 * \param upperBound Upper boundary for the return value.
 * \return Returns the value val if it is within the bounds, otherwise lowerBound or upperBound will be returned.
 */
template <class t>
static t LimitBetween(t val, t lowerBound, t upperBound)
{
  if (val > lowerBound && val < upperBound)
    return val;
  else if (val <= lowerBound)
    return lowerBound;
  else if (val >= upperBound)
    return upperBound;

  return val;
}

/**
 * \brief Checks whether a specified value lies between two specified bounds.
 * \tparam t Value types (most of the time implicitly inferred by the compiler).
 * \param val Value to check.
 * \param lowerBound Lower bound for the value.
 * \param upperBound Upper bound for the value.
 * \return true if lowerBound <= val <= upperBound.
 */
template <class t>
static bool CheckLimits(t val, t lowerBound, t upperBound)
{
  return (val >= lowerBound && val <= upperBound);
}
