#include "Stack.hpp"

template<class T>
class A {
	T a;
	Stack s;
public:
	A(int _a) : a(_a) {
		for (int i = 0; i < 10; i++)
			s.push(i);
	}
	T get() { return a; }
	int pop() { return s.pop(); }
};
