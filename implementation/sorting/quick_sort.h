#pragma once

#include "sort.h"

template<typename ObjectType, typename CriterionResultType>
class QuickSort : public SortWithCriterion<ObjectType, CriterionResultType>
{
public:
	using SortWithCriterion<ObjectType, CriterionResultType>::SortWithCriterion;

	void sort(Sortable<ObjectType>& structure) override;

private:
	void quick(Sortable<ObjectType>& structure, int min, int max);
};

template<typename ObjectType, typename CriterionResultType>
void QuickSort<ObjectType, CriterionResultType>::sort(Sortable<ObjectType>& structure)
{
	quick(structure, 0, structure.size() - 1);
}

template<typename ObjectType, typename CriterionResultType>
inline void QuickSort<ObjectType, CriterionResultType>::quick(Sortable<ObjectType>& structure, int min, int max)
{
	Criterion<ObjectType, CriterionResultType>& criterion = *SortWithCriterion<ObjectType, CriterionResultType>::criterion_;
	SortOrder order = SortWithCriterion<ObjectType, CriterionResultType>::order_;

	CriterionResultType pivotCriterionResult = criterion(structure.at((min + max) / 2));

	int indexLeft = min;
	int indexRight = max;

	do
	{
		if (order == ASC)
		{
			while (criterion(structure.at(indexLeft)) < pivotCriterionResult)
				indexLeft++;

			while (criterion(structure.at(indexRight)) > pivotCriterionResult)
				indexRight--;
		}
		else
		{
			while (criterion(structure.at(indexLeft)) > pivotCriterionResult)
				indexLeft++;

			while (criterion(structure.at(indexRight)) < pivotCriterionResult)
				indexRight--;
		}

		if (indexLeft <= indexRight)
			structure.swap(indexLeft++, indexRight--);

	} while (indexLeft <= indexRight);

	if (min < indexRight)
		quick(structure, min, indexRight);

	if (indexLeft < max)
		quick(structure, indexLeft, max);
}