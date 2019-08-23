//-----------------------------
// *
// * Base entity
// * 
//-----------------------------


#include "entity.h"
#include "address.h"
#include "game.h"
#include "playerped.h"

//----------------------------------------------------------

void CEntity::SetAmmoCount(int iCount)
{

}

//----------------------------------------------------------

v3* CEntity::GetPlayerPosition()
{
	if(!PlayerIsLoaded()) return NULL;

	DWORD m_dwGamePointer = *(DWORD *)(GAME_BASE);
	DWORD m_dwPlayerPtr = *(DWORD *)(m_dwGamePointer + PLAYER_BASE_OFFSET);
	return *(v3 **)(m_dwPlayerPtr + 0x1B0);
}

//-----------------------------------------------------------

float CEntity::GetPlayerAngle()
{
	DWORD m_PlayerPointer = *(DWORD *)(0x009E4AF8);
	if(!m_PlayerPointer) return 0.0f;

	return *(float *)(m_PlayerPointer + 0x20);
}

//----------------------------------------------------------

BOOL CEntity::PlayerIsLoaded()
{
	void *playerptr = 0;

	_asm pushad
	_asm mov ecx, dword ptr ds : [0x9DB1C4 + 0x144]
	_asm mov playerptr, ecx
	_asm popad

	if(playerptr == 0) return false;

	return true;
}

//----------------------------------------------------------

void CEntity::SetSkin(int skin)
{

}

// EOF