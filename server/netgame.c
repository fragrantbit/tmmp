#include "netgame.h"
#include <stdio.h>
#include <stdlib.h>

static ctx_t *sCtx=0;
matrix_ped *ped=0;
static ctx_t ctx;
int model=0;


//-----------------------------------------------

void connection_request_accepted(event_t *evnt)
{
	librg_entity_control_set(evnt->ctx,evnt->entity->id,evnt->peer);
	matrix_ped *ped1 = malloc(sizeof(matrix_ped));
	ped1->angle = 0.0f;
	evnt->entity->user_data = ped1;
	printf("New connection attempt\n");
	ped = malloc(sizeof(matrix_ped));
}

//-----------------------------------------------

void client_streamer_update(event_t *evnt)
{
	matrix_ped *ped = (matrix_ped *)evnt->entity->user_data;
	if(ped == NULL) return;
	ped->angle = librg_data_rf32(evnt->data);
	ped->fHealth = librg_data_rf32(evnt->data);
	ped->fHealthMax = librg_data_rf32(evnt->data);
}

//-----------------------------------------------

void entity_update(event_t *evnt)
{
	matrix_ped *ped = (matrix_ped *)evnt->entity->user_data;
	if(ped == NULL) return;
	librg_data_wf32(evnt->data,ped->angle);
	librg_data_wf32(evnt->data,ped->fHealth);
	librg_data_wf32(evnt->data,ped->fHealthMax);
}

//-----------------------------------------------

void entity_create(event_t *evnt)
{
	/*if(!ped->iModel) {
		printf("There is no playermodel\n");
		netEvent_reject(evnt);
		return;
	}*/
	//printf("Playermodel has been accepted: %d\n",ped->iModel);
	//data_writei32(evnt->data,ped->iModel);
}

//-----------------------------------------------

void net_player_model(message_t *msg)
{
	// if(ped == NULL) return; ?
	ped->iModel = librg_data_ri32(msg->data);
	model = 1;
	printf("New attempt to join the game with %d player model\n",ped->iModel);
}

//-----------------------------------------------

void initialize()
{
	// Install
	ctx.max_entities = 16;
	ctx.max_connections = 16;
	ctx.mode = LIBRG_MODE_SERVER;
	ctx.tick_delay = 32;
	ctx.world_size = (zplm_vec3_t){ 5000.0f, 5000.0f, 0.0f};
	librg_init(&ctx);

	printf("Gameserver was initialized\n");

	librg_event_add(&ctx,LIBRG_CONNECTION_ACCEPT,connection_request_accepted);
	librg_event_add(&ctx,LIBRG_CLIENT_STREAMER_UPDATE,client_streamer_update);
	librg_event_add(&ctx,LIBRG_ENTITY_UPDATE,entity_update);
	librg_event_add(&ctx,LIBRG_ENTITY_CREATE,entity_create);

	librg_network_add(&ctx,MESSAGE_ID_PLAYERMODEL,net_player_model);

	librg_address_t addr = { 
		1337, 
		(char *)"127.0.0.1" 
	};

	librg_network_start(&ctx,addr);
	sCtx = &ctx;
	int running = 1;

	while(running) {
		librg_tick(&ctx);
		zpl_sleep_ms(2);
	}

	librg_network_stop(&ctx);
	librg_free(&ctx);
}
