#ifndef __CALC_QUEUE_HPP__
#define __CALC_QUEUE_HPP__

#include <memory>

template<class T>
class Queue {
private:
	T* p;
	std::allocator<T> a;
	int size;
	int start;
	int end;

	int next(int x) { return (x + 1) % size; }

	bool full() { return next(next(end)) == start; }

	void double_size() {
		T* temp = a.allocate(2 * size);

		int last = next(end);
		int t = start, u = 0;
		for (; t != last; t = next(t), u = next(u)) {
			new(temp + u) T{ std::move(p[t]) };
			(p + t)->~T();
		}
		
		start = 0;
		end = u - 1;

		a.deallocate(p, size);
		p = temp;
		size *= 2;
	}

public:
	Queue() : size{ 3 }, start{ 1 }, end{ 0 }, a{} {
		p = a.allocate(size);
	}

	~Queue() {
		int last = next(end);
		for (int t = start; t != last; t = next(t))
			(p + t)->~T();
		a.deallocate(p, size);
	}

	bool empty() { return next(end) == start; }

	T pop() {
		if (empty())
			throw -1;
		T t{ std::move(p[start]) };
		(p + start)->~T();
		start = next(start);
		return t;
	}

	void push(const T& x) {
		if (full())
			double_size();
		end = next(end);
		new(p + end) T{ x };
	}

	void push(T&& x) {
		if (full())
			double_size();
		end = next(end);
		new(p + end) T{ x };
	}

};

#endif // !__CALC_QUEUE_HPP__
