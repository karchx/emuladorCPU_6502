#include <gtest/gtest.h>

TEST(HelloTest, BasicAssertons) {
  EXPECT_STRNE("hello", "world");

  EXPECT_EQ(7 * 6, 42);
}
