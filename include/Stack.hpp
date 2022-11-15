#ifndef __CALC_STACK_HPP__
#define __CALC_STACK_HPP__

#include "uninit_mem.hpp"

template<class T>
class Stack {
private:
	uninit_mem<T> m;
	int top;

	bool full() const { return top + 1 >= m.size; }

	void double_size() {
		uninit_mem<T> temp{ 2 * m.size };

		T* t = m.p;
		T* u = temp.p;
		T* last = t + (top + 1);
		for (; t != last; t++, u++) {
			new(static_cast<void*>(u)) T(std::move(*t));
			t->~T();
		}

		swap(m, temp);
	}

public:
	Stack() : m{ 1 }, top{ -1 } {}

	~Stack() {
		T* last = m.p + (top + 1);
		for (T* t = m.p; t != last; t++)
			t->~T();
	}

	bool empty() const { return top == -1; }

	T pop() {
		if (empty())
			throw -1;
		T temp{ std::move(m.p[top]) };
		(m.p + top)->~T();
		top--;
		return temp;
	}

	void push(const T& x) {
		if (full()) double_size();
		new(static_cast<void*>(m.p + (top + 1))) T{ x };
		top++;
	}

	void push(T&& x) {
		if (full()) double_size();
		new(static_cast<void*>(m.p + (top + 1))) T{ x };
		top++;
	}

};

#endif // !__CALC_STACK_HPP__
