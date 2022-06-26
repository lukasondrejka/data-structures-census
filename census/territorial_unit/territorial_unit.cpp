#include "territorial_unit.h"
#include <sstream>
#include <iomanip>


TerritorialUnit::TerritorialUnit(const std::string code, TerritorialUnitType type, std::string title, TerritorialUnit* superiorUnit) :
	code_(code),
	type_(type),
	title_(title),
	population_(0),
	superiorUnit_(superiorUnit),
	inferiorUnits_(new TerritorialUnitContainer()),
	education_(new Array<int>(8)),
	age_(new CoherentMatrix<int>(2, 101))
{
};

TerritorialUnit::~TerritorialUnit()
{
	delete education_;
	delete age_;
	delete inferiorUnits_;

	education_ = nullptr;
	age_ = nullptr;
	inferiorUnits_ = nullptr;
}

std::string TerritorialUnit::code()
{
	return std::string(code_);
}

std::string TerritorialUnit::title()
{
	return std::string(title_);
}

TerritorialUnitType TerritorialUnit::type()
{
	return type_;
}

int& TerritorialUnit::population()
{
	return population_;
}

int& TerritorialUnit::education(Education education)
{
	return education_->at(education);
}

int& TerritorialUnit::age(Gender gender, int age)
{
	return age_->at(gender, age);
}

TerritorialUnit* TerritorialUnit::superiorUnit()
{
	return superiorUnit_;
}

void TerritorialUnit::insertInferiorUnit(TerritorialUnit* territorialUnit)
{
	inferiorUnits_->add(territorialUnit);
}

TerritorialUnitContainer* TerritorialUnit::inferiorUnits()
{
	return inferiorUnits_;
}

std::string TerritorialUnit::toString()
{
	std::stringstream ss;

	ss << " " << std::left << std::setw(12) << code_;
	ss << " " << title_;

	ss << " (";
	switch (type_)
	{
		case MUNICIPALITY: ss << "Obec"; break;
		case DISTRICT: ss << "Okres"; break;
		case REGION: ss << "Kraj"; break;
		case STATE: ss << "Štát"; break;
	}
	ss << ")";

	return ss.str();
}
