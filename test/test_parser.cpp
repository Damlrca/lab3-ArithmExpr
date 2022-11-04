#include "parser.hpp"
#include <gtest.h>

TEST(test_parser, test1) {
	A<int> a(10);
	EXPECT_EQ(10, a.get());
}