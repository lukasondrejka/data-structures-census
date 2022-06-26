#pragma once


enum TerritorialUnitType : int
{
	MUNICIPALITY,	// Obec
	DISTRICT,		// Okres
	REGION,			// Kraj
	STATE			// Stat
};


enum TerritorialUnitContainerType : int
{
	MUNICIPALITIES,	// Obce
	DISTRICTS,		// Okresy
	REGIONS,		// Kraje
	STATES,			// Staty
	ALL_UNITS		// Vsetky uzemne jednotky
};


enum Education : int
{
	BEZ_UKONCENEHO_VZDELANIA = 0,	// bez ukončeného vzdelania – osoby vo veku 0-14 rokov
	ZAKLADNE = 1,					// základné vzdelanie
	UCNOVSKE = 2,					// stredné odborné (učňovské) vzdelanie (bez maturity)
	STREDNE = 3,					// úplné stredné vzdelanie (s maturitou)
	VYSSIE = 4,						// vyššie odborné vzdelanie
	VYSOKOSKOLSKE = 5,				// vysokoškolské vzdelanie
	BEZ_VZDELANIA = 6,				// bez školského vzdelania – osoby vo veku 15 rokov a viac
	NEZISTENE = 7					// nezistené
};


enum Gender : int
{
	MALE = 0,
	FEMALE = 1
};
