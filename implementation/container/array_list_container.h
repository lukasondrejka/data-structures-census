#pragma once

#include "container.h"

using namespace structures;


template<typename T>
class ArrayListContainer
	: public Container<T>
{
public:
    ArrayListContainer();
    virtual ~ArrayListContainer();
    size_t size() override;
    virtual void clear() override;
    T& at(int index) override;
    virtual void add(T& data) override;
    virtual bool tryRemove(T& data) override;
    virtual Iterator<T>* getBeginIterator() override;
    virtual Iterator<T>* getEndIterator() override;

private:
    ArrayList<T>* arrayList_;
};

template<typename T>
inline ArrayListContainer<T>::ArrayListContainer() :
    arrayList_(new ArrayList<T>)
{
}

template<typename T>
inline ArrayListContainer<T>::~ArrayListContainer()
{
    delete arrayList_;
    arrayList_ = nullptr;
}

template<typename T>
inline size_t ArrayListContainer<T>::size()
{
    return arrayList_->size();
}

template<typename T>
inline void ArrayListContainer<T>::clear()
{
    arrayList_->clear();
}

template<typename T>
inline T& ArrayListContainer<T>::at(int index)
{
    return arrayList_->at(index);
}

template<typename T>
inline void ArrayListContainer<T>::add(T& data)
{
    arrayList_->add(data);
}

template<typename T>
inline bool ArrayListContainer<T>::tryRemove(T& data)
{
    return arrayList_->tryRemove(data);
}

template<typename T>
inline Iterator<T>* ArrayListContainer<T>::getBeginIterator()
{
    return arrayList_->getBeginIterator();
}

template<typename T>
inline Iterator<T>* ArrayListContainer<T>::getEndIterator()
{
    return arrayList_->getEndIterator();
}
