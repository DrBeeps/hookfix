#ifndef TRACELINE_H
#define TRACELINE_H

#include "reclass.h"

struct traceresult_s;

bool IsVisible(playerEnt* localPlayer, playerEnt* enemy);

namespace helpers
{
	bool isValidEnt(playerEnt* ent);
}

#endif