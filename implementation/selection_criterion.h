#pragma once

#include "criterion.h"
#include "container/container.h"


template<typename ObjectType, typename CriterionResultType>
class SelectionCriterion
{
public:
    SelectionCriterion(Criterion<ObjectType, CriterionResultType>* criterion) :
        criterion_(criterion)
    {
    };

    virtual ~SelectionCriterion()
    {
        delete criterion_;
        criterion_ = nullptr;
    };

    ObjectType& selectBest(Container<ObjectType>& container)
    {
        if (!container.isEmpty())
        {
            int bestObjectIndex = 0;
            CriterionResultType bestValue = 
                criterion_->evaluate(container.at(bestObjectIndex));

            int index = 0;
            for (ObjectType object : container)
            {
                CriterionResultType testedValue = criterion_->evaluate(object);

                if (isTestedValueBetter(bestValue, testedValue))
                {
                    bestObjectIndex = index;
                    bestValue = testedValue;
                }

                index++;
            }

            return container.at(bestObjectIndex);
        }

        throw std::logic_error("Container is empty");
    };

protected:
    virtual bool isTestedValueBetter(CriterionResultType bestNow, CriterionResultType bestTested) = 0;

private:
    Criterion<ObjectType, CriterionResultType>* criterion_;
};


template<typename ObjectType, typename CriterionResultType>
class SelectionCriterionMin
    : public SelectionCriterion<ObjectType, CriterionResultType>
{
public:
    SelectionCriterionMin(Criterion<ObjectType, CriterionResultType>* criterion) :
        SelectionCriterion<ObjectType, CriterionResultType>(criterion)
    {
    };

protected:
    bool isTestedValueBetter(CriterionResultType bestNow, CriterionResultType bestTested) override
    {
        return bestTested < bestNow;
    };
};


template<typename ObjectType, typename CriterionResultType>
class SelectionCriterionMax
    : public SelectionCriterion<ObjectType, CriterionResultType>
{
public:
    SelectionCriterionMax(Criterion<ObjectType, CriterionResultType>* criterion) :
        SelectionCriterion<ObjectType, CriterionResultType>(criterion)
    {
    };

protected:
    bool isTestedValueBetter(CriterionResultType bestNow, CriterionResultType bestTested) override
    {
        return bestTested > bestNow;
    };
};
