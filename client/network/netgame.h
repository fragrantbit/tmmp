#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "..\..\shared\librg.h"

#undef cast

void OnGameTick();
void NetLaunch(VOID * daco);

class CNet
{
private:

	static void ConnectAccepted(librg_event_t * evnt);
	static void EntityCreate(librg_event_t * evnt);
	static void EntityUpdate(librg_event_t * evnt);
	static void EntityRemove(librg_event_t * evnt);
	static void ClientStream(librg_event_t * evnt);
	static void UpdateHealth(librg_message_t * msg);
	static void NonPlayerCharactersInit(librg_message_t * msg); // ?
	static void NonPlayerCharacterSyncAccept(librg_message_t * msg); // ?
	char *m_iHost;
	int m_iPort;
	// static librg_ctx_t ctx;

public:

	enum networks {
		MESSAGE_ID_PLAYERMODEL = 12,
		MESSAGE_ID_NPCSYNC
	};

	CNet(char * host, int port);
	~CNet();

	void Initialize();

	librg_ctx_t ctx;
	
	static float data_readf32(librg_data_t * netdata) { return librg_data_rf32(netdata); }
	static int data_readi32(librg_data_t * netdata)   { return librg_data_ri32(netdata); }

	static void data_writef32(librg_data_t * netdata, float fValue) { librg_data_wf32(netdata,fValue); }
	static void data_writei32(librg_data_t * netdata, int iValue) { librg_data_wi32(netdata,iValue); }

	// static librg_ctx_t GetCtx() {return ctx;}

	char *GetHost() { return m_iHost; }
	int GetPort() { return m_iPort; }

	static bool ClientIsStarted();
};

//----------------------------------------------------------------------
