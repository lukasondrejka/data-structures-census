#pragma once

#include "sort.h"
#include <math.h>

template<typename ObjectType, typename CriterionResultType>
class ShellSort : public SortWithCriterion<ObjectType, CriterionResultType>
{
public:
	using SortWithCriterion<ObjectType, CriterionResultType>::SortWithCriterion;

	void sort(Sortable<ObjectType>& structure) override;

private:
	void shell(Sortable<ObjectType>& structure, int step);
};

template<typename ObjectType, typename CriterionResultType>
void ShellSort<ObjectType, CriterionResultType>::sort(Sortable<ObjectType>& structure)
{
	shell(structure, max(ceil(log10(structure.size())), 1));
}

template<typename ObjectType, typename CriterionResultType>
inline void ShellSort<ObjectType, CriterionResultType>::shell(Sortable<ObjectType>& structure, int step)
{
	Criterion<ObjectType, CriterionResultType>& criterion = *SortWithCriterion<ObjectType, CriterionResultType>::criterion_;
	SortOrder order = SortWithCriterion<ObjectType, CriterionResultType>::order_;

	int delta, i, j;

	for (delta = 0; delta < step; delta++)
	{
		for (i = delta; i < structure.size(); i += step)
		{
			j = i;

			while ((j - step >= delta) &&
				((order == ASC) ?
					criterion(structure.at(j)) < criterion(structure.at(j - step)) :
					criterion(structure.at(j)) > criterion(structure.at(j - step))))
			{
				structure.swap(j, j - step);
				j -= step;
			}
		}
	}

	if (step > 1)
		shell(structure, step - 1);
}
