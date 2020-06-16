#include <gtest/gtest.h>

#include "../MathFunctions.hpp"

TEST(MathFunctionsTest, LIMITRANGE)
{
  double val = 4.126654676989243760939674697;

  ASSERT_DOUBLE_EQ(LimitBetween(val, 2.0, 5.0), val);

  ASSERT_DOUBLE_EQ(LimitBetween(val, 2.0, 4.0), 4.0);

  ASSERT_DOUBLE_EQ(LimitBetween(val, 5.0, 6.0), 5.0);

  ASSERT_DOUBLE_EQ(LimitBetween(val, val, 10.0), val);

  ASSERT_DOUBLE_EQ(LimitBetween(val, 0.0, val), val);
}

TEST(MathFunctionsTest, CHECKLIMITS)
{
  double val = 4.126654676989243760939674697;

  ASSERT_EQ(CheckLimits(val, 2.0, 5.0), true);

  ASSERT_EQ(CheckLimits(val, 2.0, 4.0), false);

  ASSERT_EQ(CheckLimits(val, 5.0, 6.0), false);

  ASSERT_EQ(CheckLimits(val, val, 10.0), true);

  ASSERT_EQ(CheckLimits(val, 0.0, val), true);
}