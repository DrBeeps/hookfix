#include "hooks.h"

namespace hooks
{
	bool Detour32(BYTE* src, BYTE* dst, const uintptr_t len)
	{
		if (len < 5) return false;

		DWORD oldProtect;
		VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &oldProtect);

		memset(src, 0x90, len);

		uintptr_t relativeAddr = dst - (src + 5);

		*src = 0xE9;

		*(uintptr_t*)(src + 1) = relativeAddr;

		VirtualProtect(src, len, oldProtect, &oldProtect);

		return true;
	}

	BYTE* TrampHook(BYTE* src, BYTE* dst, const uintptr_t len)
	{
		if (len < 5) return nullptr;

		BYTE* gateway = (BYTE*)VirtualAlloc(0, len + 5, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

		memcpy_s(gateway, len, src, len);

		uintptr_t gatewayRelativeAddr = src - gateway - 5;

		*(gateway + len) = 0xE9;

		*(uintptr_t*)((uintptr_t)gateway + len + 1) = gatewayRelativeAddr;

		hooks::Detour32(src, dst, len);

		return gateway;
	}
};