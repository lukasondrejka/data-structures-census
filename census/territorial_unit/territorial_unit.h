#pragma once

#include <string>
#include <iomanip>

#include "../types.h"
#include "../../structures/array/array.h"
#include "../../structures/matrix/coherent_matrix.h"
#include "../../implementation/container/array_list_container.h"
#include "../../cli/printable.h"


using structures::ArrayList;
using structures::CoherentMatrix;

class TerritorialUnit;

using TerritorialUnitContainer = ArrayListContainer<TerritorialUnit*>;


class TerritorialUnit
	: public Printable
{
public:
	TerritorialUnit(const std::string code, TerritorialUnitType type, std::string title, TerritorialUnit* superiorUnit);
	~TerritorialUnit();

	std::string code();
	std::string title();
	TerritorialUnitType type();
	int& population();
	int& education(Education education);
	int& age(Gender gender, int age);

	TerritorialUnit* superiorUnit();
	void insertInferiorUnit(TerritorialUnit* territorialUnit);
	TerritorialUnitContainer* inferiorUnits();

	std::string toString();

private:
	std::string code_;
	std::string title_;
	TerritorialUnitType type_;
	int population_;

	Array<int>* education_;
	Matrix<int>* age_;

	TerritorialUnit* superiorUnit_;
	TerritorialUnitContainer* inferiorUnits_;

private:
	friend class Census;
};
