#pragma once
#include <Windows.h>

void InstallJmpHook(DWORD address, DWORD function);
BYTE *InstallHook(BYTE * byteAddress, BYTE * byteFuncAddress);
BOOL BreakHook(BYTE * pbTrampoline,  BYTE * pbDetour);
