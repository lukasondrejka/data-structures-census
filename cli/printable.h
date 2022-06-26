#pragma once

class Printable
{
public:
	virtual std::string toString() = 0;

	friend std::ostream& operator<<(std::ostream& os, Printable& object)
	{
		os << object.toString();
		return os;
	}
};