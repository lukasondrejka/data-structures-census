#pragma once

#include "sort.h"
#include "sortable.h"
#include <random>
#include <chrono>


template<typename ObjectType>
class Shuffle : public Sort<ObjectType>
{
public:
	void sort(Sortable<ObjectType>& structure) override;
};


template<typename ObjectType>
inline void Shuffle<ObjectType>::sort(Sortable<ObjectType>& structure)
{
	int size = static_cast<int>(structure.size());
	auto seed = std::random_device()();
	std::default_random_engine generator(seed);
	std::uniform_int_distribution<int> uniform(0, size - 1);

	for (int i = 0; i < size * 2; i++)
		structure.swap(uniform(generator), uniform(generator));
}
