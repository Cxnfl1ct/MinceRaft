#include "player.h"
#include "ext.h"
#include "keywords.h"

extern int sw;
extern int sh;
extern Camera camera;

Player NewPlayer(Vector3 pos, char name[17]) {
    Player tmp;

    tmp.pos = pos;
    TextCopy(tmp.name, name);

    return tmp;
}

void DrawPlayer(Player *player) {
	Vector2 name_pos;
	Vector2 name_boundary;
	Vector3 ppos = player->pos;

	float name_size, name_dist;
	float dx, dy, dz;

	// Prepare variables

	dx = camera.position.x - player->pos.x;
	dy = camera.position.y - player->pos.y;
	dz = camera.position.z - player->pos.z;

	name_dist = sqrt(dx*dx + dy*dy + dz*dz) / 8;
	name_size = 15.0f / name_dist;
	name_boundary = MeasureTextEx(GetFontDefault(), player->name, name_size, TXT_SP);

	ppos.y += 1.6f;

	name_pos = GetWorldToScreen(ppos, camera);
	name_pos.x -= name_boundary.x / 2;

	printf("%.3f, %.3f\n", ppos.x, name_boundary.x);

	// Render the player

	DrawModelEx(niko, player->pos, (Vector3) {player->pitch, player->yaw, 0.0f}, 0.0f, (Vector3) {1.0f, 1.0f, 1.0f}, WHITE);

	EndMode3D(); // Ad-hoc solution, this will be replaced by a proper render queue system later

	DrawRectangleV((Vector2) {name_pos.x, name_pos.y}, name_boundary, (Color) {0, 0, 0, 127});
	DrawMinecraftText(NOFONT, player->name, name_pos.x, name_pos.y, name_size, TXT_SP, WHITE, true, 0, 0);

	BeginMode3D(camera); // Ad-hoc solution, this will be replaced by a proper render queue system later
}
