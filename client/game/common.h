#pragma once
#include <windows.h>

extern DWORD _PEDS_STORE[230];
extern int _PEDS_COUNT;

#define PAD(x,y) BYTE x[y]
#define DEADVAL -1

#define _ACTORPED_BUM 1
#define _ACTORPED_EAGLE 2
#define _ACTORPED_SERAPH 5
#define _BACKLIGHT_POINT 6
#define _ACTORPED_KEYMASTER 7
#define _ACTORPED_MEROVINGIAN_BOUNCER 12
#define _ACTORPED_NEO_OPENING 14 
#define _ACTORPED_NEOTRAINING_OLDFILM 18
#define _ACTORPED_MEROVINGIAN_BOUNCER_v2 25
#define _ACTORPED_DOBERMAN3 26
#define _ACTORPED_NEO_LAFAYETTE 38
#define _ACTORPED_NEO_Nebuchadnezzar 39
#define _ACTORPED_NEO_Ex 40


#pragma pack(1)
typedef struct _VECTOR3
{
	float x;
	float y;
	float z;
}v3, *pv3;

#pragma pack(1)
typedef struct _VECTOR2 
{
	float x;
	float y;
}v2, *pv2;

#pragma pack(1)
typedef struct _entity
{
	v3 pos;
	float rotation;
}entity;

#pragma pack(1)
typedef struct _ACTORPED
{	
	PAD(_pad0,0x214); // 0-214
	v3 actorPos; // 214-216
	PAD(_pad1,0x2CC); // 216-4E2
	float fJumpEmulate; // 4E2-4E6
	PAD(_pad2,0x5F4); // 4E6-ADA
	float fActorAirLevel; // ADA-ADE
	PAD(_pad3,0x144); // ADE-C22
	unsigned char *szModelName; // C22-C32
	int iAnimationID; // C32-C36
	PAD(_pad4,0x14C); // C36-D82
	int iPedID; // D82-D86
	PAD(_pad5,0x540); // D86-12C6
	float fHealth; // 12C6-12CA
	PAD(_pad6,0x544); // 12CA-180E
	float fHealthMax; // 180E-1812
	PAD(_pad7,0x5D4); // 1812-1DE6
	int isAlive; // 1DE6-1DEA

}ACTORPED, *PACTORPED;

// What is this supposed to mean?
#pragma pack(1)
typedef struct _NEW_BODY
{
	v3 v3_2 = {
		0,
		0,
		0
	};
	float m_fuf;
	int m_i1 = 0;
	int m_i2 = 0;
	int m_i3 = 0;
	double m_du = 0.0078125;
	int m_i4 = 0;
	int m_i5 = 0;
	int m_i6 = 0;
	double m_du2 = -0.0078125;
	int m_i7 = 0;
	v3 positions;
	float m_fuf2;
	int m_i8;
	int m_i9; 
	int m_i10; 
	int m_i11; 
	int m_i12;
	int m_i13; 
	int m_i14; 
	const char *szName; 
	int m_i15; 
	DWORD m_dw1;
	DWORD m_dw2;
	DWORD m_dw3;
	int m_i16;
	int m_i17;
	int m_i18;
	int m_i19;
	int m_i20;
	float m_fsf3; 
	const char *szS1; 
	BYTE m_byteS1;
	BYTE m_byteS2;
	BYTE m_byteS3; 

}newBody;

// EOF
