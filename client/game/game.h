#pragma once

#define MAX_OBJECTS_COUNT 3500 

#include <Windows.h>
#include "patches.h"
#include "actorped.h"

#define _GL_B3_Dojo			0x8044 // levels\B3_Dojo.3d2
#define hook_disable(x,a) BreakHook((BYTE *)x,(BYTE *)a);
#define hook_enable(x,a) InstallHook((BYTE *)x,(BYTE *)a);

extern BYTE bModelCodes[50];

typedef struct stObject
{
	int a;
	char *szName;
	int a0;
	int a1;
	int iVertexCount;
	int a2;
	float f0;
	int a3;
	int a4;
	int a5;
	int a6;
	int a7;
	int a8;
	int a9;
	int aa;
	int ab;
	int ac;
	double d0;

}object;


class CGame
{
private:

	static void *_gameinterface;

public:

	CActorPed *SetupActor();
	void DisablePlayerMoves();

	static void Patches()
	{
		ApplyGamePatches();
	}
	void NimModeControl(int iMode);
	void InitGame();
	void SetupObject(); // ?
	void sgProcessMasterObject(object * m_pObject);

	typedef void(__thiscall * FUNC_LevelSetup)(void *thisptr);

	void LoadGameLevel(int a, int b);
	void StartLoadingScreen();
	void LoadData();
	bool GameBaseIsLoaded();

	void GameScenes(int param);
	void invulnerableMode(int i); // ?

	void HackGame(int iMethod);
	void InstallHooks();

	static char GameMenuTick_hook(char * tf);

	static bool bGameMenuTick;
};


// EOF