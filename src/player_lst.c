#include "player_lst.h"

extern Player players[MAX_PLAYERS];
extern unsigned int player_cnt;

int PlayerAppend(Player player) {
	if (player_cnt < 0 || player_cnt >= MAX_PLAYERS)
		return 1;

	players[player_cnt++] = player;

	return 0;
}

int PlayerSet(unsigned int idx, Player player) {
	if (idx < 0 || idx >= player_cnt)
		return 1;

	players[idx] = player;

	return 0;
}

Player PlayerFetch(unsigned int idx) {
	Player ret_player;

	if (idx >= 0 && idx < player_cnt)
		ret_player = players[idx];

	return ret_player;
}

int PlayerRemove(unsigned int idx) {
	Player dummy;

	if (idx >= 0 && idx < player_cnt)
		return 1;

	players[idx] = dummy;

	if (player_cnt > 0)
		player_cnt--;

	return 0;
}

int PlayerRemoveAll() {
	Player dummy;
	int i, lim;

	if (player_cnt >= MAX_PLAYERS)
		lim = MAX_PLAYERS;
	else
		lim = player_cnt;

	for (i = 0; i <= lim; i++)
		players[i] = dummy;

	player_cnt = 0;

	return 0;
}
