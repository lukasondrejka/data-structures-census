#pragma once

#include "criterion.h"


template<typename ObjectType>
class Filter
{
public:
    virtual ~Filter()
    {
    };

    bool operator()(ObjectType& object)
    {
        return pass(object);
    };

    virtual bool pass(ObjectType& object) = 0;
};


template<typename ObjectType, typename ValueType>
class FilterWithCriterion 
    : public Filter<ObjectType>
{
public:
    FilterWithCriterion(Criterion<ObjectType, ValueType>* criterion) :
        criterion_(criterion)
    {
    };

    virtual ~FilterWithCriterion()
    {
        delete criterion_;
        criterion_ = nullptr;
    };

    bool pass(ObjectType& object) override
    {
        return passFilter(criterion_->evaluate(object));
    };

    Criterion<ObjectType, ValueType>* criterion()
    {
        return criterion_;
    }

protected:
    virtual bool passFilter(ValueType value) = 0;

private:
    Criterion<ObjectType, ValueType>* criterion_;
};


template<typename ObjectType, typename ValueType>
class Filter_fi 
    : public FilterWithCriterion<ObjectType, ValueType>
{
public:
    Filter_fi(Criterion<ObjectType, ValueType>* criterion, ValueType value) :
        FilterWithCriterion<ObjectType, ValueType>(criterion),
        value_(value)
    {
    };

protected:
    bool passFilter(ValueType value) override
    {
        return value == value_;
    };

private:
    ValueType value_;
};


template<typename ObjectType, typename ValueType>
class Filter_FI
    : public FilterWithCriterion<ObjectType, ValueType>
{
public:
    Filter_FI(Criterion<ObjectType, ValueType>* criterion, ValueType valueMin, ValueType valueMax) :
        FilterWithCriterion<ObjectType, ValueType>(criterion),
        valueMin_(valueMin),
        valueMax_(valueMax)
    {
    };

protected:
    bool passFilter(ValueType value) override
    {
        return valueMin_ <= value && value <= valueMax_;
    };

private:
    ValueType valueMin_;
    ValueType valueMax_;
};
