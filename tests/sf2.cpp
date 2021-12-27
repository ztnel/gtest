#include "gtest/gtest.h"

extern "C" {
#include "if2.h"
}

TEST(sf2, ok) {
  ASSERT_EQ(ccheck(5), 1);
}
