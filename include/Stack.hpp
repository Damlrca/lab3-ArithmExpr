#ifndef __STACK_HPP__
#define __STACK_HPP__

template<class T>
class Stack {
private:
	T *p;
	int top;
	int size;
public:
	Stack(int _size) : size{ _size }, top{-1} {
		if (size <= 0)
			throw -1;
		p = new T[size];
	}

	bool is_empty() { return top == -1; }
	bool is_full() { return top + 1 >= size; }

	int pop() {
		if (is_empty())
			throw -1;
		return p[top--];
	}

	void push(int x) {
		if (is_full())
			throw -1;
		p[++top] = x;
	}

	~Stack() {
		delete[] p;
	}
};

#endif // !__STACK_HPP__
