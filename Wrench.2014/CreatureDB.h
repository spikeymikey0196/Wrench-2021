#ifndef CREATUREDB_H
#define CREATUREDB_H

#include "Wrench.h"
#include "Stats.h"
#include <map>
#include <string>

using namespace std;
using namespace Wrench;

class CreatureDBEntry
{
friend class CreatureDB;

protected:
	//

	float defaultScale;
	Stats stats;
	string modelName;

public:
	//
};

class CreatureDB
{
protected:
	ContentManager *content;
	map<string, CreatureDBEntry *> entries;

public:
	//
};


#endif
