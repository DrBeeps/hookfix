#ifndef RECLASS_H
#define RECLASS_H 

#include "math.h"
#include <windows.h>

// Test Hook //
typedef int(__cdecl* _getCrossHairEntity)();
_getCrossHairEntity getCrossEntity = (_getCrossHairEntity)0x4607C0;


class playerEnt;

class Weapon
{
public:
    char pad_0x0000[0x4]; //0x0000
    __int32 ID; //0x0004
    playerEnt* owner; //0x0008
    uintptr_t* guninfo; //0x000C
    int* ammo2; //0x0010
    int* ammo; //0x0014
    int* gunWait;
    int shots;
    int breload;
};

class playerEnt
{
public:
    DWORD vTable; //0x0
    Vec3 head; //0x0004
    char _0x0010[36];
    Vec3 pos; //0x0034
    Vec3 angle; //0x0040
    char _0x004C[37];
    BYTE bScoping; //0x0071
    char _0x0072[134];
    __int32 health; //0x00F8
    __int32 armor; //0x00FC
    char _0x0100[292];
    BYTE bAttacking; //0x0224
    char name[16]; //0x0225
    char _0x0235[247];
    BYTE team; //0x032C
    char _0x032D[11];
    BYTE state; //0x0338
    char _0x0339[59];
    Weapon* weapon; //0x0374
    char _0x0378[520];

    playerEnt* getPlayerCross()
    {
        return (playerEnt*)getCrossEntity;
    }

    uintptr_t* GetCurrentWeapon()
    {
        return weapon->guninfo;
    }
};

struct entityList
{
    playerEnt* ents[31];
};

#endif