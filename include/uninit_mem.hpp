#ifndef __CALC_UNINIT_MEM_HPP__
#define __CALC_UNINIT_MEM_HPP__

#include <memory>

template<class T>
struct uninit_mem {
	std::allocator<T> a;
	T* p;
	int size;
	uninit_mem(int sz) : a{}, p{ a.allocate(sz) }, size{ sz } {}
	uninit_mem(const uninit_mem&) = delete;
	uninit_mem& operator=(const uninit_mem&) = delete;
	uninit_mem(uninit_mem&&) = delete;
	uninit_mem& operator=(uninit_mem&&) = delete;
	~uninit_mem() { a.deallocate(p, size); }
	friend void swap(uninit_mem<T>& x, uninit_mem<T>& y) {
		std::swap(x.p, y.p);
		std::swap(x.size, y.size);
	}
};

#endif // !__CALC_UNINIT_MEM_HPP__
