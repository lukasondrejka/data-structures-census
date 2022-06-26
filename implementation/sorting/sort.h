#pragma once

#include "../sorting/sortable.h"
#include "../criterion.h"


enum SortOrder;


template<typename ObjectType>
class Sort
{
public:
	virtual ~Sort()
	{
	};

	void operator()(Sortable<ObjectType>& structure)
	{
		this->sort(structure);
	};

	virtual void sort(Sortable<ObjectType>& structure) = 0;
};


template<typename ObjectType, typename CriterionResultType>
class SortWithCriterion : public Sort<ObjectType>
{
public:
	SortWithCriterion(Criterion<ObjectType, CriterionResultType>* criterion, SortOrder order) :
		criterion_(criterion),
		order_(order)
	{
	};

	SortWithCriterion(Criterion<ObjectType, CriterionResultType>* criterion) :
		SortWithCriterion(criterion, SortOrder::ASC)
	{
	};

	SortWithCriterion() :
		SortWithCriterion(new DefaultCriterion<ObjectType>(), SortOrder::ASC)
	{
	};

	~SortWithCriterion()
	{
		delete criterion_;
		criterion_ = nullptr;
		order_ = {};
	}

	virtual void sort(Sortable<ObjectType>& structure) = 0;

protected:
	Criterion<ObjectType, CriterionResultType>* criterion_;
	SortOrder order_;
};


enum SortOrder : bool
{
	ASC = 0,
	DESC = 1
};