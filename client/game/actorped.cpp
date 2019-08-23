//-----------------------------
// *
// * Actor ped entity
// * 
//-----------------------------


#include "actorped.h"
#include "address.h"
#include "common.h"

//-----------------------------------------------------------

void CActorPed::Update()
{
	if(GetActorHealth() == 0 || GetActorHealth() == -1) 
		KillActor();
}

//-----------------------------------------------------------

CActorPed::CActorPed(int iModel)
{
	pBody = NULL;
	GetNewPlayer(iModel);
}

//-----------------------------------------------------------

CActorPed::~CActorPed() {

}

//-----------------------------------------------------------

void CActorPed::GetNewPlayer(int iModel)
{
	pBody = new CBody(iModel);
	pBody->CreateBody();

	actorped_global_ptr = pBody->bd.vBodyPtr;
	
	if(actorped_global_ptr == 0) 
		return;
	
	m_pActorPed = *(ACTORPED **)((DWORD)actorped_global_ptr + 0x178);

	if(m_pActorPed == 0)
		return;

	m_bIsSpawned = true;
}

//-----------------------------------------------------------

void CActorPed::Destroy(void * thiscall, int iParam)
{
	__asm
	{
		mov ecx, dword ptr ds:0x006D3CD0
		push 0
		push 0
		push thiscall
		mov edx, 0x00426F80
		call edx
	}
}

//-----------------------------------------------------------

void CActorPed::ApplyAnimation(int iAction, int iParam)
{
	DWORD dwPed = (DWORD)(actorped_global_ptr);
	__asm
	{
		push iParam
		push iAction
		push dword ptr ds : [dwPed]
		mov edx, 0x453E80
		call edx
		add esp, 0xC
	}
}

//-----------------------------------------------------------

/*void CActorPed::ApplyAirLevel(float f)
{
	if(!m_pPed) return;

	ACTORPED *m_ActorPtr = *(ACTORPED **)((DWORD *)vActorPed + 0x178 + 0x60);
	m_ActorPtr->m_fActorAirLevel = f;
}*/

//-----------------------------------------------------------

void CActorPed::ApplyJump(float f)
{
	m_pActorPed->fJumpEmulate = f;
}

//-----------------------------------------------------------

pv3 CActorPed::GetActorPosition() 
{
	DWORD dwActor = *(DWORD *)((DWORD *)actorped_global_ptr + 0x280 + 0x60);
	pv3 coords = (pv3)(dwActor + 0x1B0);

	return coords;
}

//-----------------------------------------------------------

int CActorPed::GetActorID()
{
	return (int)m_pActorPed->iPedID;
}

//-----------------------------------------------------------

PACTORPED CActorPed::GetLocalActor()
{
	return *(ACTORPED **)(0x9E4BA8);
}

//-----------------------------------------------------------

float CActorPed::GetActorHealth()
{
	return *(float *)((DWORD)actorped_global_ptr + 0x540);
}

//-----------------------------------------------------------

float CActorPed::GetActorHealthMax()
{
	return *(float *)((DWORD)m_pActorPed + 0x544);
}

//-----------------------------------------------------------

void CActorPed::SetActorID(int id)
{
	m_pActorPed->iPedID = id;
}

//-----------------------------------------------------------

void CActorPed::SetAngle(float fRotation)
{
	DWORD dwPed = (DWORD)(actorped_global_ptr);
	__asm 
	{
		push 1
		push 1
		push fRotation
		push dword ptr ds : [dwPed]
		mov edx, 0x4544E0
		call edx
		add esp, 0x14
	}
}

//-----------------------------------------------------------

void CActorPed::SetActorPosition(v3 * vectorc)
{
	m_pActorPed->actorPos = *vectorc;
}

//-----------------------------------------------------------

void CActorPed::SetActorHealth(float fHealth)
{
	m_pActorPed->fHealth = fHealth;
}

//-----------------------------------------------------------

void CActorPed::SetActorHealthMax(float fHealth)
{
	m_pActorPed->fHealthMax = fHealth;
}

//-----------------------------------------------------------

void CActorPed::TurnToRotation(float fRotation)
{
	_asm
	{

	}
}

//-----------------------------------------------------------

void CActorPed::Up(float f)
{
	*(float *)((DWORD)actorped_global_ptr + 0x144 + 0x970) = f;
}

//-----------------------------------------------------------

void CActorPed::KillActor()
{
	if(m_bIsSpawned) {

		DWORD dwPed = (DWORD)(actorped_global_ptr);
		_asm 
		{
			mov ecx, dword ptr ds : [dwPed]
			mov eax, [ecx + 178h]
			mov dword ptr [eax + 5D4h], -1 ; 0xFFFFFFFF
		}
	}
}
// EOF
