#ifndef __CALC_QUEUE_HPP__
#define __CALC_QUEUE_HPP__

#include <memory>

template<class T>
class Queue {
private:
	T* p;
	std::allocator<T> a;
	int size;
public:
	Queue() {

	}

	~Queue() {
		
	}
};

#endif // !__CALC_QUEUE_HPP__
