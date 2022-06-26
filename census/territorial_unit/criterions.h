#pragma once


#include "../../implementation/criterion.h"
#include "territorial_unit.h"
#include "../types.h"


template<typename ResultType>
class CriterionTerritorialUnit
    : public Criterion<TerritorialUnit*, ResultType>
{
public:
    virtual ResultType evaluate(TerritorialUnit*& object) = 0;
};


class CriterionTitle
    : public CriterionTerritorialUnit<std::string>
{
public:
    std::string evaluate(TerritorialUnit*& object) override
    {
        return object->title();
    };
};


class CriterionCode
    : public CriterionTerritorialUnit<std::string>
{
public:
    std::string evaluate(TerritorialUnit*& object) override
    {
        return object->code();
    };
};


class CriterionPopulation
    : public CriterionTerritorialUnit<int>
{
public:
    int evaluate(TerritorialUnit*& object) override
    {
        return object->population();
    };
};


class CriterionType
    : public CriterionTerritorialUnit<TerritorialUnitType>
{
public:
    TerritorialUnitType evaluate(TerritorialUnit*& object) override
    {
        return object->type();
    };
};


class CriterionSuperior // Patri object do vyssieho celku superiorUnit?
    : public CriterionTerritorialUnit<bool>
{
public:
    CriterionSuperior(TerritorialUnit* superiorUnit) :
        superiorUnitCode_(superiorUnit->code()),
        superiorUnitCodeLength_(superiorUnitCode_.length())
    {
    };

    bool evaluate(TerritorialUnit*& object) override
    {
        std::string unitCode = object->code();

        return superiorUnitCode_ ==
            unitCode.substr(0, superiorUnitCodeLength_) &&
            unitCode != superiorUnitCode_;
    };

private:
    std::string superiorUnitCode_;
    int superiorUnitCodeLength_;
};


class CriterionInferior // Obsahuje object nizsi celok inferiorUnit?
    : public CriterionTerritorialUnit<bool>
{
public:
    CriterionInferior(TerritorialUnit* inferiorUnit) :
        inferiorUnitCode_(inferiorUnit->code())
    {
    };

    bool evaluate(TerritorialUnit*& object) override
    {
        std::string unitCode = object->code();
        int unitCodeLength = unitCode.length();

        return unitCode ==
            inferiorUnitCode_.substr(0, unitCodeLength) &&
            inferiorUnitCode_ != unitCode;
    };

private:
    std::string inferiorUnitCode_;
};


class CriterionEducationCount
    : public CriterionTerritorialUnit<int>
{
public:
    CriterionEducationCount(Education education) :
        education_(education)
    {
    };

    int evaluate(TerritorialUnit*& object) override
    {
        return object->education(education_);
    };

private:
    Education education_;
};


class CriterionAgeCount
    : public CriterionTerritorialUnit<int>
{
public:
    CriterionAgeCount(int age, Gender gender) :
        age_(age),
        gender_(gender)
    {
    };

    int evaluate(TerritorialUnit*& object) override
    {
        return object->age(gender_, age_);
    };

private:
    int age_;
    Gender gender_;
};
