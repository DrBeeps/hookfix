#include <windows.h>
#include <TlHelp32.h> // CreateToolhelp32Snapshot
#include <iostream> // std::cout
#include <vector> // std::vector
#include <cstddef> // std::pntrdiff_t
#include <stdint.h> // uintptr_t
#include <tchar.h>    //_tcscmp
#include <Psapi.h>    //GetModuleInformation

#include "cheats.h"
#include "hooks.h"
#include "traceline.h"

DWORD WINAPI Thread(HMODULE hModule)
{
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);


	cheatToggles cheatStates;
	cheatStates = { false, false, false, false, false, false, false };
	cheatStates.bTriggerTest = true;

	uintptr_t moduleBase = (uintptr_t)GetModuleHandle(NULL);

	playerEnt* localPlayer = *(playerEnt**)0x50f4f4;

	int* playerNum = (int*)(0x50f500);
	int* gameMode = (int*)(0x50F49C);

	entityList* entList = *(entityList**)0x50f4f8;


	while (!GetAsyncKeyState(VK_END) & 1)
	{
		// === Main Loop === //
		if (cheatStates.bTriggerTest)
		{
			for (int i = 0; i < *playerNum; i++)
			{
				if (helpers::isValidEnt(entList->ents[i]))
				{
					if (IsVisible(localPlayer, entList->ents[i]))
					{
						std::cout << entList->ents[i]->name << std::endl;
					}
					else
					{
						std::cout << "Not Visible!" << std::endl;
					}
				}
			}
		}

		if (cheatStates.bTriggerbot)
		{
			playerEnt* crosshairEnt = localPlayer->getPlayerCross();
			if (helpers::isValidEnt(crosshairEnt))
			{
				localPlayer->bAttacking = 1;
			}
		}


		Sleep(5);
	}

	fclose(f);
	FreeConsole();
	FreeLibraryAndExitThread(hModule, 0);
	return 0;
}



BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Thread, hModule, 0, nullptr));

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

