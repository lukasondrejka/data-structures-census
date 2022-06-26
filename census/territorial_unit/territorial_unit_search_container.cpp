#include "territorial_unit_search_container.h"


TerritorialUnitSearchContainer::TerritorialUnitSearchContainer() :
	unitsByCode_(new SortedSequenceTable<std::string, TerritorialUnit*>()),
	unitsByTitle_(new SortedSequenceTable<std::string, TerritorialUnitContainer*>())
{
}

TerritorialUnitSearchContainer::~TerritorialUnitSearchContainer()
{
	clear();

	delete unitsByTitle_;
	delete unitsByCode_;
}

void TerritorialUnitSearchContainer::clear()
{
	for (auto tableItem : *unitsByTitle_)
		delete tableItem->accessData();
	
	unitsByTitle_->clear();
	unitsByCode_->clear();

	TerritorialUnitContainer::clear();
}

TerritorialUnit* TerritorialUnitSearchContainer::unitByCode(std::string code)
{
	TerritorialUnit* unit = nullptr;
	unitsByCode_->tryFind(code, unit);
	return unit;
}

Container<TerritorialUnit*>* TerritorialUnitSearchContainer::unitsByTitle(std::string title)
{
	TerritorialUnitContainer* units = nullptr;
	unitsByTitle_->tryFind(title, units);
	return units;
}

void TerritorialUnitSearchContainer::add(TerritorialUnit*& data)
{
	TerritorialUnit*& unit = data;

	unitsByCode_->insert(unit->code(), unit);

	if (!unitsByTitle_->containsKey(unit->title()))
		unitsByTitle_->insert(unit->title(), new ArrayListContainer<TerritorialUnit*>());

	unitsByTitle_->find(unit->title())->add(unit);

	TerritorialUnitContainer::add(unit);
}

bool TerritorialUnitSearchContainer::tryRemove(TerritorialUnit*& data)
{
	TerritorialUnit*& unit = data;

	if (TerritorialUnitContainer::tryRemove(unit))
	{
		unitsByCode_->remove(unit->code());

		auto units = unitsByTitle_->find(unit->title());
		units->tryRemove(unit);
		if (units->isEmpty())
			delete unitsByTitle_->remove(unit->title());

		return true;
	}

	return false;
}
