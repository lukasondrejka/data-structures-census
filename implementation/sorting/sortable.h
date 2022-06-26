#pragma once


#include "../../structures/array/array.h"
#include "../../structures/list/array_list.h"
#include "../../structures/table/unsorted_sequence_table.h"


template<typename T>
class Sortable
{
public:
	virtual T& at(int index) = 0;
	virtual size_t size() = 0;
	void swap(int indexFirst, int indexSecond);
};


template<typename T>
inline void Sortable<T>::swap(int indexFirst, int indexSecond)
{
	T temp = at(indexFirst);
	at(indexFirst) = at(indexSecond);
	at(indexSecond) = temp;
}

template<typename T>
class SortableArray
	: public structures::Array<T>, Sortable<T>
{
public:
	using structures::Array<T>::Array;
};


template<typename T>
class SortableArrayList
	: public structures::ArrayList<T>, Sortable<T>
{
public:
	using structures::ArrayList<T>::ArrayList;
};


template<typename K, typename T>
class SortableTable
	: public structures::UnsortedSequenceTable<K,T>, Sortable<T>
{
public:
	using structures::UnsortedSequenceTable<K, T>::UnsortedSequenceTable;

	T& at(int index)
	{
		return structures::UnsortedSequenceTable<K, T>::getItemAtIndex(index).accessData();
	};
};