#include "census.h"

#include "../structures/matrix/coherent_matrix.h"




Census::Census() :
	units_(new UnsortedSequenceTable<TerritorialUnitContainerType, TerritorialUnitSearchContainer*>())
{
	units_->insert(MUNICIPALITIES, new TerritorialUnitSearchContainer());
	units_->insert(DISTRICTS, new TerritorialUnitSearchContainer());
	units_->insert(REGIONS, new TerritorialUnitSearchContainer());
	units_->insert(STATES, new TerritorialUnitSearchContainer());
	units_->insert(ALL_UNITS, new TerritorialUnitSearchContainer());
}

Census::~Census()
{
	for (auto unit : *units_->find(ALL_UNITS))
		delete unit;

	for (auto item : *units_)
	{
		item->accessData()->clear();
		delete item->accessData();
	}


	delete units_;
	units_ = nullptr;
}

TerritorialUnitSearchContainer* Census::units(TerritorialUnitContainerType type)
{
	return units_->find(type);
}

void Census::load()
{
	loadStates("");
	loadRegions("data/kraje.csv");
	loadDistricts("data/okresy.csv");
	loadMunicipalities("data/obce.csv");
	loadAge("data/vek.csv");
	loadEducation("data/vzdelanie.csv");
}

void Census::loadStates(std::string fileName)
{
	TerritorialUnit* unit = new TerritorialUnit("SK", STATE, "Slovensko", nullptr);
	units(STATES)->add(unit);
	units(ALL_UNITS)->add(unit);
}

void Census::loadRegions(std::string fileName)
{
	TerritorialUnit* superiorUnit = units(STATES)->unitByCode("SK");

	CSVLoader loader = CSVLoader(fileName);
	loader.open();
	loader.nextLine();

	while (loader.nextLine())
	{
		TerritorialUnit* unit = new TerritorialUnit(
			loader[1], REGION, loader[2], superiorUnit);

		superiorUnit->insertInferiorUnit(unit);

		units(REGIONS)->add(unit);
		units(ALL_UNITS)->add(unit);
	}
}


void Census::loadDistricts(std::string fileName)
{
	TerritorialUnit* superiorUnit = nullptr;

	CSVLoader loader = CSVLoader(fileName);
	loader.open();
	loader.nextLine();

	while (loader.nextLine())
	{
		superiorUnit =
			units(REGIONS)->unitByCode(loader[1].substr(0, 5));

		TerritorialUnit* unit = new TerritorialUnit(
			loader[1], DISTRICT, loader[2], superiorUnit);

		superiorUnit->insertInferiorUnit(unit);

		units(DISTRICTS)->add(unit);
		units(ALL_UNITS)->add(unit);
	}
}

void Census::loadMunicipalities(std::string fileName)
{
	TerritorialUnit* superiorUnit = nullptr;

	CSVLoader loader = CSVLoader(fileName);
	loader.open();
	loader.nextLine();

	while (loader.nextLine())
	{
		superiorUnit =
			units(DISTRICTS)->unitByCode(loader[1].substr(0, 6));

		TerritorialUnit* unit = new TerritorialUnit(
			loader[1], MUNICIPALITY, loader[2], superiorUnit);

		superiorUnit->insertInferiorUnit(unit);

		units(MUNICIPALITIES)->add(unit);
		units(ALL_UNITS)->add(unit);
	}
}

void Census::loadAge(std::string fileName)
{
	CSVLoader loader = CSVLoader(fileName);
	loader.open();
	loader.nextLine();

	const int offset = 2;

	TerritorialUnit* unit;

	int ageMale, ageFemale;

	while (loader.nextLine())
	{
		unit = units(MUNICIPALITIES)->unitByCode(loader[0]);

		while (unit != nullptr)
		{
			for (int i = 0; i < 101; i++)
			{
				ageMale = std::stoi(loader[i + offset]);
				ageFemale = std::stoi(loader[i + offset + 101]);

				unit->age(MALE, i) += ageMale;
				unit->age(FEMALE, i) += ageFemale;
			}

			unit = unit->superiorUnit_;
		}
	}
}

void Census::loadEducation(std::string fileName)
{
	CSVLoader loader = CSVLoader(fileName);
	loader.open();
	loader.nextLine();

	const int offset = 2;

	TerritorialUnit* unit;

	int education, population;

	while (loader.nextLine())
	{
		unit = units(MUNICIPALITIES)->unitByCode(loader[0]);

		while (unit != nullptr)
		{
			population = 0;

			for (int i = 0; i < 8; i++)
			{
				education = std::stoi(loader[i + offset]);
				unit->education(static_cast<Education>(i)) += education;

				population += education;
			}

			unit->population_ += population;

			unit = unit->superiorUnit_;
		}
	}
};

