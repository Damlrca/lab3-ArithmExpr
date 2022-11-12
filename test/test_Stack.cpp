#include <gtest.h>

#include "Stack.hpp"

TEST(test_Stack, first_test) {
	Stack<int> s;
	for (int i = 0; i < 10; i++)
		s.push(i);
	for (int i = 9; i >= 0; i--)
		EXPECT_EQ(i, s.pop());
}