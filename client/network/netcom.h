#pragma once

#include "..\game\common.h"


typedef struct ped_data
{
	float rotation;
	float health;
	v3 position;
}pdata;

struct matrix_ped 
{
	void *ped_ptr;
	void *ped_model_ptr;
	int model_identifier;
};

struct matrix_npc
{
	int model;
};

struct npcs_store
{
	CActorPed *npc[70];
};
