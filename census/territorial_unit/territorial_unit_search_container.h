#pragma once


#include "territorial_unit.h"
#include "../../structures/table/sorted_sequence_table.h"

class TerritorialUnitSearchContainer
	: public TerritorialUnitContainer
{
public:
	TerritorialUnitSearchContainer();
	~TerritorialUnitSearchContainer();
	virtual void clear() override;
	TerritorialUnit* unitByCode(std::string code);
	Container<TerritorialUnit*>* unitsByTitle(std::string title);
	void add(TerritorialUnit*& data) override;
	bool tryRemove(TerritorialUnit*& data) override;

private:
	SequenceTable<std::string, TerritorialUnit*>* unitsByCode_;
	SequenceTable<std::string, TerritorialUnitContainer*>* unitsByTitle_;
};