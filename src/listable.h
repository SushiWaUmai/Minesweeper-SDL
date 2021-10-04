#pragma once
#include <list>

template<typename T>
class Listable {
protected:
	Listable();
	~Listable();

	static std::list<T*> instances;
};
