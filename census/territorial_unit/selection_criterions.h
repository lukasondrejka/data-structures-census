#pragma once


#include "../../implementation/selection_criterion.h"
#include "territorial_unit.h"
#include "criterions.h"


class SelectionCriterionMinPopulation
    : public SelectionCriterionMin<TerritorialUnit*, int>
{
public:
    SelectionCriterionMinPopulation() :
        SelectionCriterionMin<TerritorialUnit*, int>(new CriterionPopulation())
    {
    };
};


class SelectionCriterionMaxPopulation
    : public SelectionCriterionMax<TerritorialUnit*, int>
{
public:
    SelectionCriterionMaxPopulation() :
        SelectionCriterionMax<TerritorialUnit*, int>(new CriterionPopulation())
    {
    };
};
