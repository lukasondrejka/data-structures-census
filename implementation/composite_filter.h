#pragma once

#include "filter.h"
#include "../structures/list/array_list.h"

template<typename ObjectType>
class CompositeFilter
    : public Filter<ObjectType>
{
public:
    CompositeFilter() :
        filters_(new structures::ArrayList<Filter<ObjectType>*>())
    {
    };

    ~CompositeFilter()
    {
        for (auto filter : *filters_)
            delete filter;

        delete filters_;
        filters_ = nullptr;
    };

    void registerFilter(Filter<ObjectType>* filter)
    {
        filters_->add(filter);
    };

    virtual bool pass(ObjectType& object) = 0;

protected:
    structures::ArrayList<Filter<ObjectType>*>* filters_;
};


template<typename ObjectType>
class Filter_AND
    : public CompositeFilter<ObjectType>
{
public:
    bool pass(ObjectType& object) override
    {
        for (Filter<ObjectType>* filter : *CompositeFilter<ObjectType>::filters_)
            if (!filter->pass(object))
                return false;

        return true;
    };
};


template<typename ObjectType>
class Filter_OR
    : public CompositeFilter<ObjectType>
{
public:
    bool pass(ObjectType& object) override
    {
        for (Filter<ObjectType>* filter : *CompositeFilter<ObjectType>::filters_)
            if (filter->pass(object))
                return true;

        return false;
    };
};
