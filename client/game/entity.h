#pragma once

//--------------/ ANIMATIONS /---------------

#define _ANIM__JUMP_HIDING				10323 
#define _ANIM__FIGHTING_STYLERACK_v1	14335
#define _ANIM__FIGHTING_STYLERACK_v2	14334
#define _ANIM__FIGHTING_STYLERACK_v3	11728 
#define _ANIM__WALKING					11200 
#define _ANIM__STAY						14437 
#define _ANIM__SITTING_POSITION			12018 
#define _ANIM__TOPEDFIX					16129
#define _ANIM__WARMUP					11223

#include "common.h"

//----------------------------------------------------------

class CEntity
{
public:

	BOOL PlayerIsLoaded();
	v3* GetPlayerPosition();
	float GetPlayerAngle();
	void SetAmmoCount(int iCount);
	void SetSkin(int skin);

	void *SearchEntity(int id); // ?
	void *m_pPed;
	void *m_entityBox;
};

//----------------------------------------------------------