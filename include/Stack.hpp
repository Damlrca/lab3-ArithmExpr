#ifndef __CALC_STACK_HPP__
#define __CALC_STACK_HPP__

#include <utility>
#include "uninit_mem.hpp"

template<class T>
class Stack {
private:
	uninit_mem<T> m;
	int top;

	void destroy_elements() {
		T* last = m.ptr() + (top + 1);
		for (T* t = m.ptr(); t != last; ++t)
			t->~T();
	}

	bool full() const { return top + 1 >= m.size(); }

	void double_size() {
		uninit_mem<T> temp{ 2 * m.size() };

		T* t = m.ptr();
		T* u = temp.ptr();
		T* last = t + (top + 1);
		try {
			for (; t != last; ++t, ++u)
				new(static_cast<void*>(u)) T{ std::move(*t) };
		}
		catch (...) {
			for (T* x = temp.ptr(); x != u; ++x)
				x->~T();
			throw;
		}

		destroy_elements();

		m = std::move(temp);
	}

public:
	Stack() : m{ 1 }, top{ -1 } {}
	
	~Stack() { destroy_elements(); }

	bool empty() const { return top == -1; }

	T pop() {
		if (empty())
			throw -1;
		T temp{ std::move(m.ptr()[top]) };
		(m.ptr() + top)->~T();
		top--;
		return temp;
	}

	void push(const T& x) {
		if (full()) double_size();
		new(static_cast<void*>(m.ptr() + (top + 1))) T{ x };
		top++;
	}

	void push(T&& x) {
		if (full()) double_size();
		new(static_cast<void*>(m.ptr() + (top + 1))) T{ x };
		top++;
	}

};

#endif // !__CALC_STACK_HPP__
