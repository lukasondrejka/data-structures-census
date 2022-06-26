#pragma once


#include "../../implementation/filter.h"
#include "criterions.h"
#include "territorial_unit.h"
#include "../types.h"


using FilterTerritorialUnit = Filter<TerritorialUnit*>;


class FilterTitle
    : public Filter_fi<TerritorialUnit*, std::string>
{
public:
    FilterTitle(std::string title) :
        Filter_fi(new CriterionTitle(), title)
    {
    };
};


class FilterCode
    : public Filter_fi<TerritorialUnit*, std::string>
{
public:
    FilterCode(std::string code) :
        Filter_fi(new CriterionCode(), code)
    {
    };
};


class FilterPopulation
    : public Filter_FI<TerritorialUnit*, int>
{
public:
    FilterPopulation(int min, int max) :
        Filter_FI(new CriterionPopulation(), min, max)
    {
    };
};


class FilterType
    : public Filter_fi<TerritorialUnit*, TerritorialUnitType>
{
public:
    FilterType(TerritorialUnitType type) :
        Filter_fi(new CriterionType(), type)
    {
    };
};


class FilterSuperior
    : public Filter_fi<TerritorialUnit*, bool>
{
public:
    FilterSuperior(TerritorialUnit* superiorUnit) :
        Filter_fi(new CriterionSuperior(superiorUnit), true)
    {
    };
};


class FilterInferior
    : public Filter_fi<TerritorialUnit*, bool>
{
public:
    FilterInferior(TerritorialUnit* inferiorUnit) :
        Filter_fi(new CriterionInferior(inferiorUnit), true)
    {
    };
};


class FilterEducationCount
    : public Filter_FI<TerritorialUnit*, int>
{
public:
    FilterEducationCount(Education education, int min, int max) :
        Filter_FI(new CriterionEducationCount(education), min, max)
    {
    };
};


class FilterAgeCount
    : public Filter_FI<TerritorialUnit*, int>
{
public:
    FilterAgeCount(int age, Gender gender, int min, int max) :
        Filter_FI(new CriterionAgeCount(age, gender), min, max)
    {
    };
};
