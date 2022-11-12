#include <gtest.h>

#include "Queue.hpp"

TEST(test_Queue, first_test) {
	Queue<int> q;
	for (int i = 0; i < 10; i++)
		q.push(i);
	for (int i = 0; i < 10; i++)
		EXPECT_EQ(i, q.pop());
}
