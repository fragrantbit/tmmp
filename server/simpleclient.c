#define LIBRG_IMPLEMENTATION
#include "ven/librg/librg.h"
#include <stdio.h>
#include <pthread.h>
#undef cast


typedef librg_event_t event_t;
typedef librg_message_t message_t;
typedef librg_data_t netdata_t;
static librg_ctx_t ctx;
static librg_ctx_t *sctx=0;

void ConnectAccepted(librg_event_t *evnt) 
{
    printf("Connection was accepted\n");
}

void Initialize()
{
	ctx.mode			= 1337;
	ctx.max_entities	= 16;
	ctx.tick_delay		= 32;

	librg_init(&ctx);
    librg_event_add(&ctx,LIBRG_CONNECTION_ACCEPT,ConnectAccepted);
	librg_address_t addr = { 
		1337, 
		(char *)"127.0.0.1"
	};

	librg_network_start(&ctx,addr);
    sctx=&ctx;
}

void tick() 
{
    while(1) {librg_tick(&ctx);}

}

int main() {

    printf("Connecting....\n");
    Initialize();
    pthread_t thread;

    pthread_create(&thread,0,(void *)tick,0);
    pthread_join(thread,0); 
}
