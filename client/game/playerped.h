#pragma once



#include <windows.h>
#include <string>
#include "entity.h"
#include "address.h"

#define _pad(x,y) BYTE x[y]

typedef struct _PLAYER
{
	_pad(_pad0,0x540); // 0-540
	float fHealth; // 540-544
	_pad(_pad1,0x544); // 544-A88
	float fHealthMax; // A88-A8C

}PLAYER, *PPLAYER;

//----------------------------------------------------------

class CPlayerPed : public CEntity
{
public:

	void ApplyAnimation(int iAction, int iParam);
	void ApplyJump(float f);
	void SetAngle(float fRotation);
	void ApplyAirLevelToPlayer(float f);
	void SetMoveSpeed(float fSpeed);
	void SetPlayerPosition(v3 * fPos);
	void SetPlayerMaxHealth(float fHealthMax);
	void SetPlayerHealth(float fHealth);
	void TakePlayerPedOut(float f = -128);
	void Up(float f);


	PPLAYER GetPlayer() {
		return *(PLAYER **)(*(DWORD *)0x9DB1C4 + 0x144);
	}
	DWORD GetPlayerModelID() {
		if(PlayerIsLoaded() != NULL) {
			DWORD dwLocalPleyaPtr = *(DWORD *)(0x9DB1C4);
			DWORD loc0 = *(DWORD *)(dwLocalPleyaPtr + 0x144);
			DWORD dwModelID = *(DWORD *)(loc0 + 0x148);
			return dwModelID;
		}
		return 0x0; // return the default model, which is swat model
	}

	v3 GetPlayerHead();
	float GetMaxHealth();
	float GetHealth();

	bool CheckIfPlayerSpawnedByHealth() {

		if(GetPlayer()->fHealth == 0)
			return false;

		if(GetPlayer()->fHealth > 0)
			return true;
	}

	bool PlayerIsAlive();
	void KillPlayer();
	void UpdateLocalPlayer();
};

// EOF
