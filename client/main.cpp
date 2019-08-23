

#define LIBRG_IMPLEMENTATION
#include "network\netgame.h"

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Winmm.lib")

#include "main.h"
#include "game/game.h"
#include "game/playerped.h"
#include "d3d/CDirect3D9Hook.h"

extern CActorPed *pActor;

FILE *flLog = 0;
CGame *pGame = 0;
CPlayerPed *pPlayerPed = 0;

// test monitor
void test(void *)
{
	pGame->InstallHooks();
	pGame->LoadGameLevel(5,5);
}

// entry point
void LaunchMonitor()
{

}

//----------------------------------------------------------

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
	if(DLL_PROCESS_ATTACH == fdwReason)
	{
		pGame = new CGame;
		pGame->Patches();
		AllocConsole();
		freopen("CONIN$","r",stdin);
		freopen("CONOUT$","w",stdout);
		freopen("CONOUT$","w",stderr);
		_beginthread(test,0,0);
	}
	return TRUE;
}

//----------------------------------------------------------

void Log(const char * fmt,...)
{
	flLog = fopen("blackpill.log","a");

	SYSTEMTIME time;
	GetLocalTime(&time);

	fprintf(flLog,"[%02d:%02d:%02d.%03d] ",time.wHour,time.wMinute,time.wSecond,time.wMilliseconds);

	char buffer[512];
	memset(buffer,0,512);

	va_list args;
	va_start(args,fmt);
	vsprintf_s(buffer,512,fmt,args);
	va_end(args);

	fprintf(flLog,buffer);

	printf(buffer);

	fprintf(flLog,"\n");

	printf("\n");

	fflush(flLog);
}

// EOF