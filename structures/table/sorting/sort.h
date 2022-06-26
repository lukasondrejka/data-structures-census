#pragma once

#include "../unsorted_sequence_table.h"

namespace structures
{
	/// <summary> Triedenie NonortedSequenceTable navrhnuté ako funkèný objekt. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class SortWithCriterion
	{
	public:
		/// <summary> Destruktor. </summary>
		virtual ~SortWithCriterion();

		/// <summary> Funkcny operator utriedi tabulku. </summary>
		/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
		/// <remarks> Využíva metódu sort. </remarks>
		void operator()(UnsortedSequenceTable<K, T>& table);

		/// <summary> Utriedi utriedi tabulku. </summary>
		/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
		virtual void sort(UnsortedSequenceTable<K, T>& table) = 0;
	};

	template<typename K, typename T>
	inline SortWithCriterion<K, T>::~SortWithCriterion()
	{
	}

	template<typename K, typename T>
	inline void SortWithCriterion<K, T>::operator()(UnsortedSequenceTable<K, T>& table)
	{
		this->sort(table);
	}
}