#pragma once

#include "sort.h"
#include "../unsorted_sequence_table.h"

namespace structures
{
	/// <summary> Triedenie Quick sort. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class QuickSort : public SortWithCriterion<K, T>
	{
	public:
		/// <summary> Utriedi tabulku triedenim Quick sort. </summary>
		/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
		void sort(UnsortedSequenceTable<K, T>& table) override;

	private:
		void quick(UnsortedSequenceTable<K, T>& table, int step, int min, int max);
	};

	template<typename K, typename T>
	inline void QuickSort<K, T>::sort(UnsortedSequenceTable<K, T>& table)
	{
		quick(table, 0, table.size() - 1);
	}

	template<typename K, typename T>
	inline void QuickSort<K, T>::quick(UnsortedSequenceTable<K, T>& table, int step, int min, int max)
	{
		auto pivot = table.getItemAtIndex((min + max) / 2);

		int indexLeft = min;
		int indexRight = max;

		do
		{
			while (table.getItemAtIndex(indexLeft).getKey() < pivot.getKey())
				indexLeft++;
			
			while (table.getItemAtIndex(indexRight).getKey() > pivot.getKey())
				indexRight--;

			if (indexLeft <= indexRight)
				table.swap(indexLeft++, indexRight--);

		} while (indexLeft <= indexRight);

		if (min < indexRight)
			quick(table, min, indexRight);

		if (indexLeft < max)
			quick(table, indexLeft, max);
	}
}