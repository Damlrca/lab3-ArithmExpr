#include <gtest.h>

#include <cstdlib>
#include <stack>
#include "Stack.hpp"

TEST(test_Stack, a_lot_of_push_test) {
	constexpr int N = 100000;
	Stack<int> s;
	for (int i = 0; i < N; i++)
		s.push(i);
	for (int i = N - 1; i >= 0; i--)
		EXPECT_EQ(i, s.pop());
}

TEST(test_Stack, a_lot_of_push_and_pop_test) {
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

TEST(test_Stack, pop_empty_test) {
	Stack<int> s;
	ASSERT_ANY_THROW(s.pop());
}

TEST(test_Stack, push_then_pop_empty_test) {
	Stack<int> s;
	s.push(1);
	s.pop();
	ASSERT_ANY_THROW(s.pop());
}

TEST(test_Stack, top_test) {
	std::stack<int> t;
	Stack<int> s;
	for (int i = 0; i < 10; i++) {
		s.push(i);
		t.push(i);
	}
	for (int i = 0; i < 100000; i++) {
		EXPECT_EQ(t.empty(), s.empty());
		if (std::rand() % 2 && !t.empty()) {
			EXPECT_EQ(t.top(), s.top());
			s.pop();
			t.pop();
		}
		else {
			int k = i * (std::rand() % 24);
			t.push(k);
			s.push(k);
		}
	}
}
