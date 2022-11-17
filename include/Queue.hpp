#ifndef __CALC_QUEUE_HPP__
#define __CALC_QUEUE_HPP__

#include <utility>
#include "uninit_mem.hpp"

template<class T>
class Queue {
private:
	uninit_mem<T> m;
	int start;
	int end;

	void destroy_elements() {
		int last = next(end);
		for (int t = start; t != last; t = next(t))
			(m.ptr() + t)->~T();
	}

	int next(int x) const { return (x + 1) % m.size(); }

	bool full() const { return next(next(end)) == start; }

	void double_size() {
		uninit_mem<T> temp{ 2 * m.size() };

		int last = next(end);
		int t = start, u = 0;
		try {
			for (; t != last; t = next(t), ++u)
				new(temp.ptr() + u) T{ std::move(m.ptr()[t]) };
		}
		catch (...) {
			for (int x = 0; x != u; ++x)
				(temp.ptr() + x)->~T();
			throw;
		}
		
		destroy_elements();

		m = std::move(temp);
		start = 0;
		end = u - 1;
	}

public:
	Queue() : m{ 3 }, start{ 1 }, end{ 0 } {}

	~Queue() { destroy_elements(); }

	bool empty() const { return next(end) == start; }

	T pop() {
		if (empty())
			throw -1;
		T t{ std::move(m.ptr()[start]) };
		(m.ptr() + start)->~T();
		start = next(start);
		return t;
	}

	void push(const T& x) {
		if (full()) double_size();
		new(static_cast<void*>(m.ptr() + next(end))) T{ x };
		end = next(end);
	}

	void push(T&& x) {
		if (full()) double_size();
		new(static_cast<void*>(m.ptr() + next(end))) T{ x };
		end = next(end);
	}

};

#endif // !__CALC_QUEUE_HPP__
