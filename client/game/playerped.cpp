//-----------------------------
// *
// * Player ped entity
// * 
//-----------------------------



#include "playerped.h"
#include "game.h"
#include "address.h"
#include "..\main.h"

extern void Log(const char * fmt,...);

PLAYER *pPlayerData = 0;

//----------------------------------------------------------

void CPlayerPed::SetPlayerHealth(float fHealth)
{
	GetPlayer()->fHealth = fHealth;

	if(GetPlayer()->fHealth == 0)
		UpdateLocalPlayer();
}

//----------------------------------------------------------

void CPlayerPed::TakePlayerPedOut(float f)
{
	*(float *)(*(DWORD *)0x9DB1C4 + 0x144 + 0x140) = f;
}

//----------------------------------------------------------

void CPlayerPed::SetPlayerMaxHealth(float fHealthMax)
{
	GetPlayer()->fHealth = fHealthMax;
}

//----------------------------------------------------------

void CPlayerPed::ApplyAnimation(int iAction, int iParam)
{
	_asm 
	{
		push iParam
		push iAction
		push dword ptr ds : [0xA09614]
		mov edx, 0x453E80
		call edx
		add esp, 0xC ; 12h
	}
}

//----------------------------------------------------------

void CPlayerPed::SetAngle(float fRotation)
{
	_asm
	{
		push 1
		push 1
		push fRotation
		push dword ptr ds : [0xA09614]
		mov eax, 0x4544E0
		call eax
		add esp, 14h ; 16h
	}
}

//----------------------------------------------------------

v3 CPlayerPed::GetPlayerHead()
{
	DWORD dwLocalPleyaPtr = *(DWORD *)(0x9DB1C4 + 0x144);
	v3 playerHead = {
		*(float *)(dwLocalPleyaPtr + 0xCC),
		*(float *)(dwLocalPleyaPtr + 0xD0),
		*(float *)(dwLocalPleyaPtr + 0xD4)
	};

	return playerHead;
}

//----------------------------------------------------------

void CPlayerPed::ApplyAirLevelToPlayer(float f)
{
	if(!PlayerIsLoaded()) return;

	DWORD dwGameBase = *(DWORD *)(GAME_BASE);
	DWORD dwPlayerPtr = *(DWORD *)(dwGameBase + PLAYER_BASE_OFFSET);
	*(float *)(dwPlayerPtr + 0x1AC) = f;
}

//----------------------------------------------------------

void CPlayerPed::SetMoveSpeed(float fSpeed)
{
	if(!PlayerIsLoaded()) return;

	DWORD dwLocalPleyaPtr = *(DWORD *)(0x9E4A2C + 0x8 + 0x20);
	*(float *)(dwLocalPleyaPtr + 0x40 + 0x14) = fSpeed;
}

//----------------------------------------------------------

void CPlayerPed::SetPlayerPosition(v3 * fPos)
{
	if(!PlayerIsLoaded()) return;

	DWORD dwLocalPleyaPtr = *(DWORD *)(0x9E4BA8);

	*(float *)(dwLocalPleyaPtr + 0x214) = fPos->x;
	*(float *)(dwLocalPleyaPtr + 0x21E) = fPos->y;
}

//----------------------------------------------------------

void CPlayerPed::ApplyJump(float f)
{
	if(!PlayerIsLoaded()) return;

	DWORD dwLocalPleyaPtr = *(DWORD *)(0x9E4BA8);
	DWORD loc0 = *(DWORD *)(dwLocalPleyaPtr + 0x178);
	*(float *)(loc0 + 0x22C) = f;
}

//----------------------------------------------------------

float CPlayerPed::GetHealth()
{
	return (GetPlayer()->fHealth);
}

//----------------------------------------------------------

float CPlayerPed::GetMaxHealth()
{
	return (GetPlayer()->fHealthMax);
}

//----------------------------------------------------------

void CPlayerPed::UpdateLocalPlayer()
{
	if(GetHealth() == 0 || GetHealth() == -1)
		KillPlayer();
}

//-----------------------------------------------------------

void CPlayerPed::Up(float f)
{
	*(float *)((DWORD)0x9DB1C4 + 0x144 + 0x970) = f;
}

//-----------------------------------------------------------

bool CPlayerPed::PlayerIsAlive()
{
	DWORD dwLocalPleyaPtr = (DWORD)GetPlayer();
	DWORD loc0 = *(DWORD *)(dwLocalPleyaPtr + 0x178 + 0x5D4);

	if(loc0 == 1) 
		return true;

	if(loc0 == DEADVAL || loc0 == 0) 
		return false;

	if(loc0 != DEADVAL && loc0 != 0 && loc0 != 1)
		Log("isPlayerAlive: could not check the player");
}

//-----------------------------------------------------------

void CPlayerPed::KillPlayer()
{
	/*
		.text:00552646                 mov     eax, [edi+178h]
		.text:0055264C                 mov     ecx, [eax+5D4h]
		.text:00552652                 test    ch, 2

	*/

	if(GetPlayer()->fHealth != 0 || GetPlayer()->fHealth > 0) return;

	_asm 
	{
		mov ecx, dword ptr ds : [0x9DB1C4]
		mov edx, [ecx+144h]
		mov eax, [edx+178h]
		mov dword ptr [eax + 5D4h], -1 ; 0xFFFFFFFF
	}
}

// EOF