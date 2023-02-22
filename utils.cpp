#include "utils.h"

bool utils::isValidEnt(playerEnt* ent)
{
	if (!ent) return false;
	if (ent->vTable == 0x4E4AA8 || ent->vTable == 0x4E4AC0) // points to playerent or botent vtables 
	{
		return true;
	}
	else
		return false;
}