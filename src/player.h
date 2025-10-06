#ifndef _PLAYER_H
#define _PLAYER_H

typedef struct {
	Vector3 pos;

	float pitch;
	float yaw;

	float hp;
	float hunger;

	unsigned int inv[3];

	bool dead;

	char name[17];
}

Player newPlayer(Vector3 pos, char name[17]);

#endif
