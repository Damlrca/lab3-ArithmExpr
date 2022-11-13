#ifndef __CALC_STACK_HPP__
#define __CALC_STACK_HPP__

#include <memory>

template<class T>
class Stack {
private:
	T *p;
	std::allocator<T> a;
	int size;
	int top;

	bool full() const { return top + 1 >= size; }

	void double_size() {
		T* temp = a.allocate(2 * size);

		/*//requires c++17
		std::uninitialized_move(p, p + size, temp);
		T* last = p + size;
		for (T* t = p; t != next; t++)
			t->~T();
		*/

		T* last = p + (top + 1);
		for (T* t = p, *u = temp; t != last; t++, u++) {
			new(u) T(std::move(*t));
			t->~T();
		}

		a.deallocate(p, size);
		p = temp;
		size *= 2;
	}

public:
	Stack() : size{ 1 }, top{ -1 }, a{} {
		p = a.allocate(size);
	}

	~Stack() {
		T* last = p + (top + 1);
		for (T *t = p; t != last; t++)
			t->~T();
		a.deallocate(p, size);
	}

	bool empty() const { return top == -1; }

	T pop() {
		if (empty())
			throw -1;
		T temp{ std::move(p[top]) };
		(p + top)->~T();
		top--;
		return temp;
	}

	void push(const T& x) {
		if (full())
			double_size();
		new(p + (top + 1)) T{ x };
		top++;
	}

	void push(T&& x) {
		if (full())
			double_size();
		new(p + (top + 1)) T{ x };
		top++;
	}

};

#endif // !__CALC_STACK_HPP__
