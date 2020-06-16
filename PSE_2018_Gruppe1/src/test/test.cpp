#include <gtest/gtest.h>

#include "../Logging.hpp"

TEST(EmptyTest, TrueAndFalse)
{
  bool b = true;
  EXPECT_EQ(b, true);
  EXPECT_NE(b, false);
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  // When testing, we want the maximum available log output
  Logging::setMaxLevel(DIAG_VERBOSE);

  return RUN_ALL_TESTS();
}
