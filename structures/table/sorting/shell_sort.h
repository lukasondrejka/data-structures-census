#pragma once

#include "sort.h"
#include "../unsorted_sequence_table.h"
#include <math.h>

namespace structures
{
	/// <summary> Triedenie Shell sort. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class ShellSort : public SortWithCriterion<K, T>
	{
	public:
		/// <summary> Utriedi tabulku triedenim Shell sort. </summary>
		/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
		void sort(UnsortedSequenceTable<K, T>& table) override;

	private:
		void shell(UnsortedSequenceTable<K, T>& table, int step);
	};

	template<typename K, typename T>
	inline void ShellSort<K, T>::sort(UnsortedSequenceTable<K, T>& table)
	{
		shell(table, max(ceil(log10(table.size())), 1));
	}

	template<typename K, typename T>
	inline void ShellSort<K, T>::shell(UnsortedSequenceTable<K, T>& table, int step)
	{
		int delta, i, j;

		for (delta = 0; delta < step; delta++)
		{
			for (i = delta; i < table.size(); i += step)
			{
				j = i;

				while(j - step >= delta &&
					table.getItemAtIndex(j).getKey() < table.getItemAtIndex(j - step).getKey())
				{
					table.swap(j, j - step);
					j -= step;
				}
			}
		}

		if (step > 1)
			shell(table, step - 1);
	}
}