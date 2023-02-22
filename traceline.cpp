#include "traceline.h"

struct traceresult_s
{
    Vec3 end;
    bool collided;
};

bool helpers::isValidEnt(playerEnt* ent)
{
    if (!ent) return false;
    if (ent->vTable == 0x4E4AA8 || ent->vTable == 0x4E4AC0) // points to playerent or botent vtables 
    {
        return true;
    }
    else
        return false;
}

bool IsVisible(playerEnt* localPlayer, playerEnt* ent)
{
    DWORD traceLine = 0x048a310;
    traceresult_s traceResult;
    traceResult.collided = false;
    Vec3 from = localPlayer->head;
    Vec3 to = ent->head;

    __asm
    {
        push 0; bSkipTags
        push 0; bCheckPlayers
        push localPlayer
        push to.z
        push to.y
        push to.x
        push from.z
        push from.y
        push from.x
        lea eax, [traceResult]
        call traceLine;
        add esp, 36
    }
    return !traceResult.collided;
}