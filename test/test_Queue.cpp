#include <gtest.h>

#include <cstdlib>
#include <queue>
#include "Queue.hpp"

TEST(test_Queue, a_lot_of_push_test) {
	constexpr int N = 100000;
	Queue<int> q;
	for (int i = 0; i < N; i++)
		q.push(i);
	for (int i = 0; i < N; i++)
		EXPECT_EQ(i, q.pop());
}

TEST(test_Queue, a_lot_of_push_and_pop_test) {
	std::queue<int> t;
	Queue<int> q;
	for (int i = 0; i < 10; i++) {
		q.push(i);
		t.push(i);
	}
	for (int i = 0; i < 100000; i++) {
		EXPECT_EQ(t.empty(), q.empty());
		if (std::rand() % 2 && !t.empty()) {
			EXPECT_EQ(t.front(), q.pop());
			t.pop();
		}
		else {
			int k = i * (std::rand() % 24);
			t.push(k);
			q.push(k);
		}
	}
}

TEST(test_Queue, pop_empty_test) {
	Queue<int> q;
	ASSERT_ANY_THROW(q.pop());
}

TEST(test_Queue, push_then_pop_empty_test) {
	Queue<int> q;
	q.push(1);
	q.pop();
	ASSERT_ANY_THROW(q.pop());
}

TEST(test_Queue, front_test) {
	std::queue<int> t;
	Queue<int> q;
	for (int i = 0; i < 10; i++) {
		q.push(i);
		t.push(i);
	}
	for (int i = 0; i < 100000; i++) {
		EXPECT_EQ(t.empty(), q.empty());
		if (std::rand() % 2 && !t.empty()) {
			EXPECT_EQ(t.front(), q.front());
			q.pop();
			t.pop();
		}
		else {
			int k = i * (std::rand() % 24);
			t.push(k);
			q.push(k);
		}
	}
}
