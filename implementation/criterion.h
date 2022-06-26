#pragma once


template<typename ObjectType, typename ResultType>
class Criterion
{
public:
     virtual ResultType evaluate(ObjectType& object) = 0;
     ResultType operator()(ObjectType& object)
     {
         return evaluate(object);
     };
};


template<typename ObjectType>
class DefaultCriterion : public Criterion<ObjectType, ObjectType>
{
public:
    ObjectType evaluate(ObjectType& object) override
    {
        return object;
    };
};