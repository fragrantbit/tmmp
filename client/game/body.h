#pragma once

#include "common.h"
#include <stdio.h>

class CBody
{
public:

	CBody(int iTypeOrID);
	~CBody();
	newBody *pBody;
	typedef struct bodydata
	{
		void *vBodyPtr;

	}bodydata;

	bodydata bd;
	void CreateBody();
	DWORD GetBodyPtr() { return (DWORD)bd.vBodyPtr; }
};