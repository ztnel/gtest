#include "gtest/gtest.h"

extern "C" {
#include "if2.h"
}

TEST(sf2, ok) {
  ASSERT_EQ(ccheck(5), 1);
}

TEST(unit, not_ok) {
  ASSERT_EQ(ccheck(0), 0);  
}