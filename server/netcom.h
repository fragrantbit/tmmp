#ifndef _netcom_h
#define _netcom_h
#include "ven/librg/librg.h"
#undef cast

typedef librg_event_t event_t;
typedef librg_message_t message_t;
typedef librg_ctx_t ctx_t;
typedef librg_data_t netdata_t;

typedef struct matrix_ped {
	float angle;
	float fHealth;
	float fHealthMax;
	int iModel;
}matrix_ped;

struct matrix_npc
{
	int model;
};

typedef struct VECTOR3
{
	float x;
	float y;
	float z;
}v3;

#endif
