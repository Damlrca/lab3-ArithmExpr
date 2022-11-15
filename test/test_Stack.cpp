#include <gtest.h>

#include <cstdlib>
#include <stack>
#include "Stack.hpp"

TEST(test_Stack, first_test) {
	Stack<int> s;
	for (int i = 0; i < 10; i++)
		s.push(i);
	for (int i = 9; i >= 0; i--)
		EXPECT_EQ(i, s.pop());
}

TEST(test_Stack, second_test) {
	std::stack<int> t;
	Stack<int> s;
	for (int i = 0; i < 10; i++) {
		s.push(i);
		t.push(i);
	}
	for (int i = 0; i < 100000; i++) {
		EXPECT_EQ(t.empty(), s.empty());
		if (std::rand() % 2 && !t.empty()) {
			EXPECT_EQ(t.top(), s.pop());
			t.pop();
		}
		else {
			int k = i * (std::rand() % 24);
			t.push(k);
			s.push(k);
		}
	}
}
