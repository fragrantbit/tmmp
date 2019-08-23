#pragma once



#include <Windows.h>
#include <string>
#include "entity.h"
#include "common.h"
#include "body.h"


#define _ACTOR_ALREADY_EXISTS 0xFF 


class CActorPed : public CEntity
{

public:

	CActorPed(int iModel);
	~CActorPed();

	ACTORPED *m_pActorPed;
	CBody *pBody;

	void *actorped_global_ptr;
	entity *m_pEntity; // ?
	bool m_bIsSpawned;

	void Destroy(void * thiscall, int iParam);
	void SetActorID(int id);
	void SetActorPosition(v3 * vectorc);
	void SetAngle(float fRotation);
	void SetActorHealth(float fHealth);
	void SetActorHealthMax(float fHealthMax);
	void ApplyJump(float f);
	void ApplyAnimation(int iAction, int iParam);
	void ApplyAirLevel(float f); // ?
	void TurnToRotation(float fRotation);
	void Up(float f);
	void WrapPed(); // ?
	void Update();
	void GetNewPlayer(int iModel);
	v3 *GetActorPosition();
	int GetActorID();
	float GetActorHealth();
	float GetActorHealthMax();

	void KillActor();

	PACTORPED GetActorPed() { return m_pActorPed; }
	PACTORPED GetLocalActor();
};


//----------------------------------------------------------
