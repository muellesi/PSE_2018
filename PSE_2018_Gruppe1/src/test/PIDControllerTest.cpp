#include <iostream>

#include <gtest/gtest.h>

#include "../PIDController.hpp"

TEST(PIDControllerTest, PID)
{
  double currValue = 0.0;
  double setValue  = 0.0;

  PIDController testController(1.0, 1.0, 0.1);

  // run for 200 cycles - at cycle 100, apply a set value of 1.0
  // run for another 100 cycles and check whether the controller was able to stabilize the set value
  for (int i = 0; i < 200; i++)
  {
    if (i == 100)
      setValue = 1.0;

    double error = setValue - currValue;

    currValue += testController.calculate(error);
  }

  ASSERT_DOUBLE_EQ(currValue, setValue);
}
