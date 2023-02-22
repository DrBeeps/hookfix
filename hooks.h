#pragma once
#include <windows.h>
#include <stdint.h> // uintptr_t

namespace hooks
{
	bool Detour32(BYTE* src, BYTE* dst, const uintptr_t len);
	BYTE* TrampHook(BYTE* src, BYTE* dst, const uintptr_t len);
	// bool rmTrampHook(BYTE* src, BYTE* dst, const uintptr_t len);
};

