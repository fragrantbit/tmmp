//-----------------------------
// *
// * Game patches
// * 
//-----------------------------



#include "patches.h"

//---------------------------------------------------

void Unprotect(DWORD addr, int size)
{
	DWORD d;
	VirtualProtect((PVOID)addr,size,PAGE_EXECUTE_READWRITE,&d);
}

//---------------------------------------------------

void ApplyGamePatches()
{
	// CNP3ResourceMan::requestLoad() 
	Unprotect(0x4D5D8E,0x2);
	memset((PVOID)0x4D5D8E,0x90,0x2); // nop * 2

	// CNP3ResourceRequest::stateLoaded()
	Unprotect(0x4D6598,0x2);
	memset((PVOID)0x4D6598,0x90,0x2); // nop * 2

	// CNP3ResourceManRequest::stateCapturing() 
	Unprotect(0x4D61EE,0x2);
	memset((PVOID)0x4D61EE,0x90,0x2); // nop * 2

	Unprotect(0x4D61F8,0x2);
	memset((PVOID)0x4D61F8,0x90,0x2); // nop * 2

	Unprotect(0x4D61FF,0x2);
	memset((PVOID)0x4D61FF,0x90,0x2); // nop * 2

	Unprotect(0x56E259,0x2); 
	memset((PVOID)0x56E259,0x90,0x2); // nop * 2

	Unprotect(0x56E253,0x2); 
	memset((PVOID)0x56E253,0x90,0x2); // nop * 2
	
	Unprotect(0x587BE3,0x1);
	memcpy((PVOID)0x587BE3,"\x90",0x1); // nop 

	Unprotect(0x587BE4,0x1);
	memcpy((PVOID)0x587BE4,"\x90",0x1); // nop 

	Unprotect(0x587BE5,0x5);
	memset((PVOID)0x587BE5,0x90,0x5);  // nop * 5

	Unprotect(0x546074,0x5);
	memset((PVOID)0x546074,0x90,0x5); // nop * 5

	//---------------------------------

	// lights
	Unprotect(0x40F484,0x4);
	memset((PVOID)0x40F484,0x90,0x4); // nop * 4

	// CNP3ResourceManRequest::stateCapturing()
	Unprotect(0x4D66F7,0x5);
	memset((PVOID)0x4D66F7,0x90,0x5); // nop * 5

	Unprotect(0x4D66E5,0x5);
	memset((PVOID)0x004D66E5,0x90,0x5); // nop * 5

	// CStaticPromptOverlay::ShowStaticPopupMessage() 
	Unprotect(0x55ED21,0x5);
	memset((PVOID)0x55ED21,0x90,0x5); // nop * 5

	// tests
	/*Unprotect(0x00505AC2, 5);
	memcpy((PVOID)0x00505AC2, "\xC2\x04\x00\x90\x90", 5);*/
}

//---------------------------------------------------

DWORD dwCNP3ResourceManRequestLoad[5] = { 0xE8, 0x3E, 0xD4, 0x00, 0x00 };
DWORD dwCNP3ResourceManRequestLoad__Test[3] = { 0x85, 0xC0 };
DWORD dwCNP3ResourceManRequestLoad__Jumping[3] = { 0x75, 0x12 };
void RestoreAfterLoadLevel()
{
	Unprotect(0x4C885D,5);
	memcpy((PVOID)0x4C885D,dwCNP3ResourceManRequestLoad,sizeof(dwCNP3ResourceManRequestLoad));
	Unprotect(0x4C8862,2);
	memcpy((PVOID)0x4C8862,dwCNP3ResourceManRequestLoad__Test,sizeof(dwCNP3ResourceManRequestLoad__Test));
	Unprotect(0x4C8864,2);
	memcpy((PVOID)0x4C8864,dwCNP3ResourceManRequestLoad__Jumping,sizeof(dwCNP3ResourceManRequestLoad__Jumping));
}

//---------------------------------------------------
