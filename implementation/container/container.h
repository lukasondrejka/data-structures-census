#pragma once

#include "../../structures/structure.h"
#include "../../structures/structure_iterator.h"
#include "../sorting/sortable.h"


using structures::Structure;
using structures::Iterable;


template<typename T>
class Container
	: public Structure, public Iterable<T>, public Sortable<T>
{
public:
    virtual ~Container();
    virtual Structure& assign(Structure& other) override;
    virtual bool equals(Structure& other) override;
    virtual size_t size() override = 0;
    virtual void clear() = 0;
    T& operator[](int index);
    virtual T& at(int index) = 0;
    virtual void add(T& data) = 0;
    virtual bool tryRemove(T& data) = 0;
};


template<typename T>
inline Container<T>::~Container()
{
}

template<typename T>
inline Structure& Container<T>::assign(Structure& other)
{
    throw std::logic_error("Container cannot be assigned");
}

template<typename T>
inline bool Container<T>::equals(Structure& other)
{
    throw std::logic_error("Container cannot be equaled");
}

template<typename T>
inline T& Container<T>::operator[](int index)
{
    return at(index);
}
