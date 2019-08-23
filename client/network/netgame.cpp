//-----------------------------
// *
// * Net game logic
// * 
//-----------------------------



#include "netgame.h"

#include "..\game\entity.h"
#include "..\game\address.h"
#include "..\game\common.h"
#include "..\game\actorped.h"
#include "..\game\playerped.h"
#include "..\game\game.h"

#include "netcom.h"

#include "..\hook.h"
#include "..\d3d\CDirect3D9Hook.h"


CPlayerPed *pPlayer = 0;
CActorPed *pActor = 0;
CNet *pNet = 0;

extern CGame *pGame;

bool g_bPedExists = false;
bool g_bGameWasInited = false;
bool g_bNetPlayerModelSent = false;
bool g_bNetPlayerIsConnected = false;

static librg_ctx_t *sCtx = 0;
matrix_ped *matrix_struct = 0;
npcs_store *npcs = 0;


CNet::CNet(char * host, int port)
{
	m_iHost = host;
	m_iPort = port;
}

//-----------------------------------------------------------

CNet::~CNet()
{
	librg_network_stop(&ctx);
}

//-----------------------------------------------------------

void CNet::ConnectAccepted(librg_event_t * evnt)
{
	printf("You've joined the game.\n");

	// bNetPlayerIsConnected = true;
	npcs = new npcs_store;

	//int iModel = pPlayer->GetPlayerModelID();
	//librg_message_send_all(sCtx,PON_MODEL,&iModel,sizeof(iModel)); 
}

//-----------------------------------------------------------
// Two players only
// ** Add multiplayer support
void CNet::EntityCreate(librg_event_t * evnt)
{
	if(!ClientIsStarted()) return;
	if(g_bPedExists == FALSE) { 
		matrix_struct = new matrix_ped;

		// There's an issue--we choose model identifier only when creating a new actor ped
		// It's good to figure out how to change model identifier when actor was included to the game
		matrix_struct->model_identifier = 14; /*data_readi32(evnt->data);*/
		pActor = new CActorPed(matrix_struct->model_identifier);

		if(pActor->actorped_global_ptr == NULL)
			return;
		
		matrix_struct->ped_ptr = pActor->actorped_global_ptr;
		evnt->entity->user_data = (void *)matrix_struct;

		g_bPedExists = true;
	}
}

//-----------------------------------------------------------

void CNet::EntityUpdate(librg_event_t * evnt)
{
	if(!ClientIsStarted()) return;
	matrix_ped *casted_ped = (matrix_ped *)evnt->entity->user_data;

	float angle = data_readf32(evnt->data);
	float f_health = data_readf32(evnt->data);
	float f_healthMax = data_readf32(evnt->data);

	v3 position = { 
		evnt->entity->position.x, 
		evnt->entity->position.y,
		evnt->entity->position.z
	};
	// printf("New data for player: \nPosition: %f %f %f\nAngle: %f\nHealth: %f\n", position.x, position.y, position.z, angle, f_health);
	pActor->SetAngle(angle);
	pActor->SetActorHealth(f_health);
	pActor->SetActorHealthMax(f_healthMax);
	pActor->SetActorPosition(&position);
}

//-----------------------------------------------------------

void CNet::EntityRemove(librg_event_t * evnt)
{
	printf("Remove entity!\n");
}

//-----------------------------------------------------------

void CNet::ClientStream(librg_event_t * evnt)
{
	if(!ClientIsStarted()) return;
	v3 VecPlayerPosition = *pPlayer->GetPlayerPosition();

	// Get basic playerped data.
	float f_playerAngle = pPlayer->GetPlayerAngle();
	float f_playerHealth = pPlayer->GetHealth();
	float f_playerHealthMax = pPlayer->GetMaxHealth();

	// Write playerped's positions.
	evnt->entity->position = zplm_vec3(VecPlayerPosition.x,VecPlayerPosition.y,VecPlayerPosition.z);

	// Write the data to server.
	data_writef32(evnt->data,f_playerAngle);
	data_writef32(evnt->data,f_playerHealth);
	data_writef32(evnt->data,f_playerHealthMax);
}

//-----------------------------------------------------------

/*void CNet::UpdateHealth(librg_message_t *msg)
{
	float fHealth;
	librg_data_rptr(msg->data,&fHealth,sizeof(fHealth));
	printf("New health: %f\n", fHealth);
	pPlayer->SetPlayerHealth(fHealth);
	pPlayer->SetPlayerMaxHealth(fHealth);
	pPlayer->UpdateLocalPlayer();
}*/

//-----------------------------------------------------------

int GetNpcSlot()
{
	int i=0;
	for(i = 0; i < 70; i++) {
		if(npcs->npc[i]->m_bIsSpawned || npcs->npc[i]->m_pActorPed != NULL) 
			continue;

		if(!npcs->npc[i]->m_bIsSpawned || npcs->npc[i]->m_pActorPed == NULL) 
			break;
	}
	return i;
}

//-----------------------------------------------------------

bool CNet::ClientIsStarted()
{
	if((pPlayer->PlayerIsLoaded() != NULL && g_bGameWasInited)) 
		return true;
	else 
		return false;

	return false;
}

//-----------------------------------------------------------

void CNet::Initialize()
{
	ctx.mode			= LIBRG_MODE_CLIENT;
	ctx.max_entities	= 16;
	ctx.tick_delay		= 32;
	ctx.world_size = { 
		5000.0f, 
		5000.0f, 
		0.0f 
	};

	librg_init(&ctx);
	librg_event_add(&ctx,LIBRG_CONNECTION_ACCEPT,ConnectAccepted);
	librg_event_add(&ctx,LIBRG_ENTITY_CREATE,EntityCreate);
	librg_event_add(&ctx,LIBRG_ENTITY_UPDATE,EntityUpdate);
	// librg_event_add(&ctx,LIBRG_ENTITY_REMOVE,EntityRemove);
	librg_event_add(&ctx,LIBRG_CLIENT_STREAMER_UPDATE,ClientStream);

	librg_address_t addr = { 
		m_iPort, 
		(char *)m_iHost 
	};

	librg_network_start(&ctx,addr);
	sCtx = &ctx;
}


//-----------------------------------------------------------

DWORD tick = GetTickCount();
void OnGameTick()
{
	/*if(bNetPlayerIsConnected) {
		if(!bNetPlayerModelSent) {
			printf("Sending model...\n");
			int iModel = pPlayer->GetPlayerModelID();
			librg_message_send_all(sCtx,pNetGame->MESSAGE_ID_PLAYERMODEL,&iModel,sizeof(iModel)); 
			bNetPlayerModelSent = true;
		}
	}*/
	if(!g_bGameWasInited && pPlayer->PlayerIsLoaded() != NULL) {
		printf("Setting up network game...\n");
		pNet->Initialize();
		g_bGameWasInited = true;
	}
	if(pNet->ClientIsStarted()) 
		librg_tick(&pNet->ctx);
}

//-----------------------------------------------------------

__declspec(naked) void gTick()
{
	__asm
	{
		pushad

		call OnGameTick

		popad

		retn
	}
}

//-----------------------------------------------------------

void NetLaunch(VOID * daco)
{
	AllocConsole();

	freopen("CONIN$","r",stdin);
	freopen("CONOUT$","w",stdout);
	freopen("CONOUT$","w",stderr);

	InstallJmpHook(0x0041A1D3,(DWORD)&gTick); 

	pNet = new CNet((char *)"host",27010);
	printf("%s:%d\n",pNet->GetHost(),pNet->GetPort());
	pPlayer = new CPlayerPed();

	printf("Loading level..\n");

	pGame->LoadGameLevel(19,4); // ? 
}

//EOF
