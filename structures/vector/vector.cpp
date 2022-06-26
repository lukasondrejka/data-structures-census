#include "vector.h"
#include "../utils.h"
#include <cstdlib>
#include <cstring>

namespace structures
{
	Vector::Vector(size_t size) :
		memory_(std::calloc(size, 1)),
		size_(size)
	{	
	}

	Vector::Vector(Vector& other) :
		Vector(other.size_)
	{
		std::memmove(memory_, other.memory_, other.size_);
	}

	Vector::~Vector()
	{
		std::free(memory_);
		memory_ = nullptr;
		size_ = 0;
	}

	size_t Vector::size()
	{
		return size_;
	}

	Structure& Vector::assign(Structure& other)
	{
		if (this != &other)
		{
			Vector& otherVector = dynamic_cast<Vector&>(other);

			size_ = otherVector.size_;
			memory_ = std::realloc(memory_, size_);
			std::memcpy(memory_, otherVector.memory_, size_);
		}

		return *this;
	}

	bool Vector::equals(Structure& other)
	{
		if (this == &other)
			return true;
		
		Vector* otherVector = dynamic_cast<Vector*>(&other);

		if (otherVector != nullptr)
		{
			return size_ == otherVector->size_ && 
				std::memcmp(memory_, otherVector->memory_, size_) == 0;
		}

		return false;
	}

	byte& Vector::operator[](int index)
	{
		return at(index);
	}

	byte& Vector::at(int index)
	{
		return *getBytePointer(index);
	}

	void Vector::copy(Vector& src, int srcStartIndex, Vector& dest, int destStartIndex, int length)
	{
		/*if (srcStartIndex < 0 || srcStartIndex + length > src.size_ || destStartIndex < 0 || destStartIndex + length > dest.size_)
		{
			throw std::out_of_range("Index out of range");
		}*/

		if (&src == &dest && std::abs(srcStartIndex - destStartIndex) < length)
		{
			std::memmove(dest.getBytePointer(destStartIndex), src.getBytePointer(srcStartIndex), length);
		}
		else
		{
			std::memcpy(dest.getBytePointer(destStartIndex), src.getBytePointer(srcStartIndex), length);
		}
	}

	byte* Vector::getBytePointer(int index)
	{
		//Utils::rangeCheckExcept(index, size_);

		return reinterpret_cast<byte*>(memory_) + index;
	}
}