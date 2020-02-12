//-----------------------------
// *
// * Body manager
// * 
//-----------------------------


#include "body.h"


CBody::CBody(int iTypeOrID)
{
	pBody = new newBody;

	/* Available skins begin from at least 0 identifier, otherwise game's crash is guaranteed. 
	   It's hard or most likely not possible to make the game be loading a < 0 identifier actor model over the multiplayer net mechanism, 
	   so it's not sensible to let it happen.
	*/
	if(iTypeOrID < 0)
		iTypeOrID = 0; 
	
	pBody->m_fuf = 14335;
	pBody->positions = { 
		0, 
		0, 
		0 
	};
	pBody->m_fuf2 = 1;
	pBody->m_i8 = iTypeOrID;
	pBody->m_i9 = (DWORD)0xFFF0000;
	pBody->m_i10 = 1;
	pBody->m_i11 = 6;
	pBody->m_i12 = 4294967295;
	pBody->m_i13 = NULL;
	pBody->m_i14 = NULL;
	pBody->szName = "ACTOR";
	pBody->m_i15 = 14335;
	pBody->m_dw1 = NULL;
	pBody->m_dw2 = NULL;
	pBody->m_dw3 = NULL;
	pBody->m_i16 = 1;
	pBody->m_i17 = 8;
	pBody->m_i18 = NULL;
	pBody->m_i19 = NULL;
	pBody->m_i20 = NULL;
	pBody->m_fsf3 = 1012.067566f;
	pBody->szS1 = ":[r@8"; // ???
	pBody->m_byteS1 = NULL;
	pBody->m_byteS2 = NULL;
	pBody->m_byteS3 = NULL;
}

//-----------------------------------------------------------

CBody::~CBody()
{
	// ?
}

//-----------------------------------------------------------

void CBody::CreateBody()
{
	DWORD dwNewAP = (DWORD)pBody;
	void *actor_box_ptr = 0;

	_asm
	{
		push 0x1
		mov esi, dwNewAP
		lea ebx, [esi]
		push ebx

		mov edx, 0x45A8C0
		call edx

		mov ecx, eax
		mov actor_box_ptr, ecx
		add esp, 0x8
	}

	bd.vBodyPtr = actor_box_ptr;
}

// EOF
