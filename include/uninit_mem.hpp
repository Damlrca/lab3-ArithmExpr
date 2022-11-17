#ifndef __CALC_UNINIT_MEM_HPP__
#define __CALC_UNINIT_MEM_HPP__

#include <utility>

template<class T>
class uninit_mem {
private:
	int sz;
	T* p;
public:
	uninit_mem(int _sz) : sz{ _sz }, p{ static_cast<T*>(::operator new(sizeof(T) * sz)) } {}
	~uninit_mem() { ::operator delete(static_cast<void*>(p)); }
	T* ptr() const { return p; }
	int size() const { return sz; }
	uninit_mem(const uninit_mem&) = delete;
	uninit_mem& operator=(const uninit_mem&) = delete;
	uninit_mem(uninit_mem&& x) : sz{ x.sz }, p{ x.p } {
		x.sz = 0;
		x.p = nullptr;
	}
	uninit_mem& operator=(uninit_mem&& x) {
		swap(*this, x);
		return *this;
	};
	friend void swap(uninit_mem<T>& x, uninit_mem<T>& y) {
		std::swap(x.p, y.p);
		std::swap(x.sz, y.sz);
	}
};

#endif // !__CALC_UNINIT_MEM_HPP__
