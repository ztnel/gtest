#include "gtest/gtest.h"

extern "C" {
#include "if1.h"
}

TEST(sf1, ok) {
  ASSERT_EQ(checksum(1, 1), 1);
}

TEST(unit, not_ok) {
  ASSERT_EQ(checksum(1, 2), 0);
}