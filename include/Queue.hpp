#ifndef __CALC_QUEUE_HPP__
#define __CALC_QUEUE_HPP__

#include "uninit_mem.hpp"

template<class T>
class Queue {
private:
	uninit_mem<T> m;
	int start;
	int end;

	int next(int x) const { return (x + 1) % m.size; }

	bool full() const { return next(next(end)) == start; }

	void double_size() {
		uninit_mem<T> temp{ 2 * m.size };

		int last = next(end);
		int t = start, u = 0;
		try {
			for (; t != last; t = next(t), ++u) {
				new(temp.p + u) T{ std::move(m.p[t]) };
				(m.p + t)->~T();
			}
		}
		catch (...) {
			for (int x = 0; x != u; ++x)
				(temp.p + x)->~T();
			throw;
		}
		
		start = 0;
		end = u - 1;

		swap(m, temp);
	}

public:
	Queue() : m{ 3 }, start{ 1 }, end{ 0 } {}

	~Queue() {
		int last = next(end);
		for (int t = start; t != last; t = next(t))
			(m.p + t)->~T();
	}

	bool empty() const { return next(end) == start; }

	T pop() {
		if (empty())
			throw -1;
		T t{ std::move(m.p[start]) };
		(m.p + start)->~T();
		start = next(start);
		return t;
	}

	void push(const T& x) {
		if (full()) double_size();
		new(static_cast<void*>(m.p + next(end))) T{ x };
		end = next(end);
	}

	void push(T&& x) {
		if (full()) double_size();
		new(static_cast<void*>(m.p + next(end))) T{ x };
		end = next(end);
	}

};

#endif // !__CALC_QUEUE_HPP__
