#pragma once

#include <cstring>

template<typename T>
class SmartPtr
{
protected:
	SmartPtr(T* ptr) :
		ptr_(ptr)
	{
	};

public:

	virtual ~SmartPtr() 
	{
	};

	T* operator->()
	{
		return this->ptr_;
	};

	T& operator*()
	{
		return *this->ptr_;
	};

protected:
	T* ptr_;
};


template<typename T>
class UniquePtr : public SmartPtr<T>
{
public:
	UniquePtr(T* ptr) :
		SmartPtr<T>::SmartPtr(ptr)
	{
	};

	UniquePtr() :
		UniquePtr(nullptr)
	{
	};

	UniquePtr(const UniquePtr<T>& other) :
		UniquePtr(reinterpret_cast<T*>(std::malloc(sizeof(*other.ptr_))))
	{
		std::memcpy(SmartPtr<T>::ptr_, other.ptr_, sizeof(*other.ptr_) + 1);
	};

	~UniquePtr()
	{
		if (SmartPtr<T>::ptr_ != nullptr)
		{
			delete SmartPtr<T>::ptr_;
			SmartPtr<T>::ptr_ = nullptr;
		}
	};

	UniquePtr<T>& operator=(UniquePtr<T>& other)
	{
		if (this != &other)
		{
			if (SmartPtr<T>::ptr_ != nullptr)
			{
				delete SmartPtr<T>::ptr_;
			}

			SmartPtr<T>::ptr_ = reinterpret_cast<T*>(std::malloc(sizeof(*other.ptr_)));
			std::memcpy(SmartPtr<T>::ptr_, other.ptr_, sizeof(*other.ptr_) + 1);
		}

		return *this;
	};
};


template<typename T>
class SharedPtr : public SmartPtr<T>
{
public:
	SharedPtr(T* ptr) :
		SmartPtr<T>::SmartPtr(ptr),
		referencesCount_(new size_t(ptr == nullptr ? 0 : 1))
	{
	};

	SharedPtr() :
		SharedPtr(nullptr)
	{
	};

	SharedPtr(const SharedPtr<T>& other) :
		SmartPtr<T>::SmartPtr(other.ptr_),
		referencesCount_(other.referencesCount_)
	{
		(*referencesCount_)++;
	};

	~SharedPtr() override
	{
		if (referencesCount_ != nullptr)
		{
			(*referencesCount_)--;

			if (*referencesCount_ == 0)
			{
				delete SmartPtr<T>::ptr_;
				delete referencesCount_;
				SmartPtr<T>::ptr_ = nullptr;
				referencesCount_ = nullptr;
			}
		}
	}

	SharedPtr<T>& operator=(SharedPtr<T>& other) {
		
		if (this != &other)
		{
			if (referencesCount_ != nullptr)
			{
				(*referencesCount_)--;

				if (*referencesCount_ == 0) 
				{
					delete SmartPtr<T>::ptr_;
					delete referencesCount_;
				}
			}

			SmartPtr<T>::ptr_ = other.ptr_;
			referencesCount_ = other.referencesCount_;
			(*referencesCount_)++;
		}

		return *this;
	};

private:
	size_t* referencesCount_;
};
