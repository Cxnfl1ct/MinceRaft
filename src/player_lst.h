#ifndef _PLAYER_LST_H
#define _PLAYER_LST_H

#include "raylib.h"
#include "player.h"
#include "config.h"

int PlayerAppend(Player player);
int PlayerSet(unsigned int idx, Player player);
Player PlayerFetch(unsigned int idx);
int PlayerRemove(unsigned int idx);
int PlayerRemoveAll();

#endif
