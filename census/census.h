#pragma once


#include "types.h"
#include "territorial_unit/territorial_unit.h"

#include "../structures/list/array_list.h"
#include "../structures/table/sorted_sequence_table.h"

#include "../csv_loader/csv_loader.h"
#include "territorial_unit/territorial_unit_search_container.h"


class Census
{
public:
	Census();
	~Census();

	TerritorialUnitSearchContainer* units(TerritorialUnitContainerType type);

	void load();

private:
	void loadStates(std::string fileName);
	void loadRegions(std::string fileName);
	void loadDistricts(std::string fileName);
	void loadMunicipalities(std::string fileName);
	void loadAge(std::string fileName);
	void loadEducation(std::string fileName);

private:
	Table<TerritorialUnitContainerType, TerritorialUnitSearchContainer*>* units_;
};