#ifndef _PLAYER_H
#define _PLAYER_H

#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
	Vector3 pos;

	float pitch;
	float yaw;

	float hp;
	float hunger;

	unsigned int inv[3];

	bool dead;

	char name[17];
} Player;

extern Player NewPlayer(Vector3 pos, char name[17]);
extern void DrawPlayer(Player *player);

#endif
