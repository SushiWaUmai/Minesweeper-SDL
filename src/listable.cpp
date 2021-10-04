#include "listable.h"
#include "clickable.h"
#include "renderable.h"

template<typename T>
std::list<T*> Listable<T>::instances;

template<typename T>
Listable<T>::Listable() {
	instances.push_back((T*)this);
}

template<typename T>
Listable<T>::~Listable() {
	instances.remove((T*)this);
}

template class Listable<Clickable>;
template class Listable<Renderable>;
