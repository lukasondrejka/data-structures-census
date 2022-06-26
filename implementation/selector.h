#pragma once


#include "filter.h"
#include "container/array_list_container.h"


template<typename ObjectType>
class Selector
{
public:
    Selector(Filter<ObjectType>* filter) :
        filter_(filter)
    {
    };

    ~Selector()
    {
        delete filter_;
        filter_ = nullptr;
    };

    void select(Container<ObjectType>& container, Container<ObjectType>& outputContainer)
    {
        if (filter_ != nullptr)
            for (ObjectType object : container)
                if (filter_->pass(object))
                    outputContainer.add(object);
    };

    Container<ObjectType>* select(Container<ObjectType>& container)
    {
        Container<ObjectType>* outputContainer = new ArrayListContainer<ObjectType>();

        select(container, *outputContainer);

        return outputContainer;
    };

    void operator()(Container<ObjectType>& container, Container<ObjectType>& outputContainer)
    {
        select(container, outputContainer);
    };

    Container<ObjectType>* operator()(Container<ObjectType>& container)
    {
        return select(container);
    };

private:
    Filter<ObjectType>* filter_;
};
