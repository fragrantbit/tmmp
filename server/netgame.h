#pragma once
#include "netcom.h"

enum networks{
    MESSAGE_ID_PLAYERMODEL = 12,
};

void connection_request_accepted(event_t *evnt);
void client_streamer_update(event_t *evnt);
void entity_update(event_t *evnt);
void entity_create(event_t *evnt);
void net_player_model(message_t *msg);
void net_npc_sync(message_t *msg);

void initialize();

// void AppInstall();

