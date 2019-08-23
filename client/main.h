#pragma once


#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h> 
#include <process.h>

#include "..\shared\d3d\d3dx9.h"
#include "..\shared\Detours\detours.h"

void Log(const char * fmt, ...);


void Unprotect(DWORD addr, int size);