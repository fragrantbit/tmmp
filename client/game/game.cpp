//-----------------------------
// *
// * Base game logic
// * 
//-----------------------------


#include "game.h"
#include "patches.h"
#include "playerped.h"
#include "address.h"
#include "..\main.h"
#include "..\hook.h"

char (__thiscall *menuGameTickFunc)(char *);
void (_cdecl *RequestActorFunc)(int, int, int);

void *CGame::_gameinterface=0;
bool CGame::bGameMenuTick=false;


BYTE bModelCodes[50] = {
	0x08185EAA
};

// Todo
char CGame::GameMenuTick_hook(char * tf)
{
	BreakHook((BYTE *)menuGameTickFunc,(BYTE *)GameMenuTick_hook);
	Log("0x%X\n",tf);
	__asm mov ecx, tf;
	__asm mov edx, 0x57BD40;
	__asm call edx;

	_gameinterface = (int *)tf;
	bGameMenuTick = true;
	// return 0;
}

//----------------------------------------------------------

void RequestActor_hook(int ident0, int ident1, int ident2);
void RequestActor_hook(int ident0, int ident1, int ident2)
{
	hook_disable(RequestActorFunc,RequestActor_hook);

	// Get actor's base and figure out which model id was assigned to them.
	// If the identifier is one of these that can be assigned to any actor, 
	// the actor ped will not be created, but there will be created something else, which is necessary for the game.
	/*_asm {
		pushad
		mov eax, dword ptr ds : [dwFParam]
		mov eax, [eax+0x4C]

		jmp makeit_compared

		makeit_compared:
			mov [iModelIdentifier], eax
					
		popad
	}*/

	RequestActorFunc = (void(_cdecl *)(int,int,int))hook_enable(0x553E90,RequestActor_hook);
	return void(NULL);
}

//----------------------------------------------------------

void CGame::InstallHooks()
{
	// menuGameTickFunc = (char(__thiscall *)(char *))InstallHook((BYTE *)0x57BD40,(BYTE *)GameMenuTick_hook);
	RequestActorFunc = (void(_cdecl *)(int,int,int))InstallHook((BYTE *)0x553E90,(BYTE *)RequestActor_hook);
}

//----------------------------------------------------------

CActorPed *CGame::SetupActor()
{
	//CActorPed *pActorNew = new CActorPed(NULL);
	//return pActorNew;
}

//----------------------------------------------------------

void CGame::LoadGameLevel(int a, int b)
{
	_asm 
	{
		push 0
		push 0
		push b
		push a
		mov edx, 0x569E60
		call edx
		add esp, 10h
	}
}

//----------------------------------------------------------

FARPROC dwLockPlayerMovesFunc = (FARPROC)0x415CD0;
void __declspec(naked) LockAllPlayerMoves()
{
	_asm
	{
		mov ecx, ds : [0x6D3CD0]
		add ecx, 98h
		call dwLockPlayerMovesFunc
	}
	//mov al, 1
	// ret
}

//-----------------------------------------------------------

void CGame::InitGame()
{
	Patches();
}

//-----------------------------------------------------------

void CGame::NimModeControl(int iMode)
{
	_asm
	{
		push 0
		push iMode
		mov edx, 0x553250
		call edx
		add esp, 0x8
	}
}

//----------------------------------------------------------

void CGame::sgProcessMasterObject(object * m_pObject)
{
	DWORD dwNewObject = (DWORD)m_pObject;
	_asm
	{
		push dwNewObject
		mov edx, 0x537040
		call edx
		add esp, 14h
	}
}

//----------------------------------------------------------

void CGame::GameScenes(int param)
{
	NimModeControl(param);
}

//----------------------------------------------------------

void CGame::DisablePlayerMoves()
{
	LockAllPlayerMoves();
}

//----------------------------------------------------------

bool CGame::GameBaseIsLoaded()
{
	void *gameptr = 0;

	__asm
	{
		pushad
		mov ecx, dword ptr ds : [0x9DB1C4]
		mov gameptr, ecx
		popad
	}

	if(gameptr)
		return TRUE;
	else
		return FALSE;
}

//----------------------------------------------------------
bool g_matrixScreen = false;
void CGame::StartLoadingScreen()
{
	if(!GameBaseIsLoaded()) return;

	DWORD dwGameBase = *(DWORD *)(0x9DB1C4); 

	int x = 0;
	float fx;

	// forceful 
	if(g_matrixScreen == true) {
		x = *(int *)(dwGameBase + 4);
		fx = *(float *)(dwGameBase + 8);

		*(DWORD *)(dwGameBase) = 0x8024;

		*(int *)(dwGameBase + 4) = x + 0x1;
		*(float *)(dwGameBase + 8) = fx + 0x1;
		strcpy((PCHAR)(dwGameBase + 0xC),"levels\\StartScreen.3d2");
		g_matrixScreen = false;
	}

	if(g_matrixScreen == false) {
		*(DWORD *)(dwGameBase) = 0x702c; // loading screen
		g_matrixScreen = true;
	}
}

//-------------------------------------------------------
// todo
void CGame::HackGame(int iMethod)
{
	if(!_gameinterface) {
		printf("%p\n", _gameinterface);
		return;
	}

	// DWORD m_dw = (DWORD)_gameinterface; /*(void *)0x0495CAA8*/
	switch(iMethod) {	
		case 0: return; 
		case 1: {
		/*	_asm {
				mov ecx, dword ptr ds : m_dw
				mov edx, 0x4197D0
				call edx
			}*/
		}
	}
}

//-------------------------------------------------------

DWORD m_dwHealthManager[] = {
	0xD9, 
	0x9E, 
	0x40, 
	0x05,
	0x00, 
	0x00 
};
void CGame::invulnerableMode(INT i)
{
	///.text:0045D0E1                 fstp    dword ptr [esi+540h]

	//if(i == 1) patch((void *)0x0045D0E1,(void *)0x90,6);
	//if(i == 0) patch((void *)0x0045D0E1,dwHealthEngine,6); ?

}

// EOF