/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

#include <stdio.h>
#include <stdint.h>

Model niko;
Model grass;

Mesh grass_;

Texture2D niko_texture;
Texture2D grass_texture;

Music bg;

float playSound;
float volume;

Camera camera = { 0 };

float rotation = 0;

bool pause;

typedef struct {
	Vector3 pos;

	float pitch;
	float yaw;

	float hp;
	float hunger;

	unsigned short inventory[3];
	bool dead;

	char name[17];
} Player;

Player players[5];

void InitGame();
void EndGame();
void UpdateGame();
void DrawGame();
void UpdateDrawFrame();

void InitCamera();

void DrawBG();
void DrawObjects();
void DrawOverlay();
void DrawPauseOverlay();

void ProcessInput();

void DrawMinecraftText(const char *text, int posX, int posY, int fontSize, Color color, bool shadow);

int main() {
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(1280, 800, "MinceRaft - OneShot Niko");
	InitGame();

	while (!WindowShouldClose()) {
		UpdateDrawFrame();
	}

	EndGame();

	return 0;
}

void InitGame() {
	grass_ = GenMeshCube(1.0f, 1.0f, 1.0f);

	SearchAndSetResourceDir("resources");

	niko = LoadModel("niko.obj");
	niko_texture = LoadTexture("niko.png");
	grass_texture = LoadTexture("grass.png");

	grass = LoadModelFromMesh(grass_);

	if (!IsModelValid(niko)) {
		TraceLog(0, "Failed to load <niko.obj>!");
	}

	if (!IsMusicValid(bg)) {
		TraceLog(0, "Failed to load <bg.mp3>!");
	}

	SetMaterialTexture(&niko.materials[0], MATERIAL_MAP_DIFFUSE, niko_texture);
	SetMaterialTexture(&grass.materials[0], MATERIAL_MAP_DIFFUSE, grass_texture);

	InitAudioDevice();

	if (!IsAudioDeviceReady()) {
		TraceLog(0, "Initializing audio device failed!");
	}

	bg = LoadMusicStream("bg.mp3");

	playSound = 1;
	volume = 0.50f;

	pause = false;

	DisableCursor();
	SetTargetFPS(60);

	InitCamera();
}

void EndGame() {
	StopMusicStream(bg);

	UnloadTexture(niko_texture);
	UnloadTexture(grass_texture);

	UnloadModel(niko);
	UnloadModel(grass);

//	UnloadMesh(grass_);

	UnloadMusicStream(bg);

	CloseAudioDevice();

	CloseWindow();
}

void ProcessInput() {
	if (IsKeyReleased('I') && volume < 1)
		volume += 0.05f;

	if (IsKeyReleased('K') && volume > 0)
		volume -= 0.05f;

	if (IsKeyReleased('M') ) {
		playSound++;

		if (playSound >= 2.0f) 
			playSound = 0.0f;
	}

	if (IsKeyReleased('R') )
		InitCamera();
}

void UpdateGame() {
	if (IsKeyReleased('P') ) {
		pause = !pause;
	
		if (pause) {
			PauseMusicStream(bg);
			EnableCursor();
		} else {
			ResumeMusicStream(bg);
			DisableCursor();
		}
	}

	if (!pause) {
		ProcessInput();

		UpdateMusicStream(bg);

		UpdateCamera(&camera, CAMERA_FIRST_PERSON);
	}

	if (IsMusicStreamPlaying(bg) )
		SetMasterVolume( (float) volume * playSound );

	if (!IsMusicStreamPlaying(bg) ) {
		PlayMusicStream(bg);
	}
}

void DrawBG() {
	ClearBackground((Color) {170, 225, 255, 255});
	DrawGrid(50, 1.0f);
}

void DrawMap() {
	int i, j;
	float k, l;

	k = -50.0f;
	l = -50.0f;

	for (i=0; i<100; i++) {	
		for (j=0; j<100; j++) {
			k += 1.0f;
			DrawModel(grass, (Vector3) {k, -0.5f, l}, 1.0f, WHITE);
		}

		k = -50.0f;
		l += 1.0f;
	}
}

void DrawPlayer(Player *player) {
	DrawModelEx(niko, player.pos, (Vector3) {player.pitch, player.yaw, 0.0f}, 0.0f, (Vector3) {1.0f, 1.0f, 1.0f}, WHITE);
}

void DrawObjects() {
	DrawModelEx(niko, (Vector3) {0.0f, 0.0f, 0.0f}, (Vector3) {0, 0, rotation}, 0.0f, (Vector3) {1.2f, 1.2f, 1.2f}, WHITE);

	DrawModelEx(niko, (Vector3) {0.0f, 0.0f, 0.0f}, (Vector3) {0, 0, rotation}, 0.0f, (Vector3) {1.2f, 1.2f, 1.2f}, WHITE);
}

void DrawOverlay() {
	char debug_txt[256];
	char volume_txt[64];

	int sw = GetScreenWidth();
	int sh = GetScreenHeight();

	sprintf(debug_txt, "%dFPS - Frame render took %.3fs - Program Uptime: %.f", GetFPS(), GetFrameTime(), GetTime() );
	sprintf(volume_txt, "Current volume: %.f%%", volume * 100);

	DrawMinecraftText("TEST - OneShot Niko", 5, 5, 20, WHITE, true);
	DrawMinecraftText(debug_txt, 5, sh - 20, 20, WHITE, true);
	DrawMinecraftText(volume_txt, sw - MeasureText(volume_txt, 20) - 5, 5, 20, WHITE, true);

	if (!playSound)
		DrawMinecraftText("MUTED", sw - MeasureText("MUTED", 20) - 5, 30, 20, WHITE, true);
}

void DrawPauseOverlay() {
	int sw = GetScreenWidth();
	int sh = GetScreenHeight();

	DrawRectangle(0, 0, sw, sh, (Color) {0, 0, 0, 127} );
	DrawMinecraftText("PAUSED", sw / 2 - MeasureText("PAUSED", 80 / 2), sh / 2 - MeasureText("PAUSED", 80) / 2, 80, WHITE, true);
}

void DrawGame() {
	BeginDrawing();

	DrawBG();
	
	BeginMode3D(camera);

	DrawMap();
	DrawObjects();

	EndMode3D();

	DrawOverlay();
	
	if (pause)
		DrawPauseOverlay();

	EndDrawing();
}

void UpdateDrawFrame() {
	UpdateGame();
	DrawGame();
}

void InitCamera() {
	camera.position = (Vector3){5.0f, 1.0f, 5.0f};
	camera.target = (Vector3){0.0f, 0.0f, 0.0f};
	camera.up = (Vector3){0.0f, 1.0f, 0.0f};
	camera.fovy = 45.0f;
	camera.projection = CAMERA_PERSPECTIVE;
}

void DrawMinecraftText(const char *text, int posX, int posY, int fontSize, Color color, bool shadow) {
	int offset = fontSize / 10;

	Color color_shadow = {color.r / 4, color.g / 4, color.b / 4, color.a};

	if (shadow)
		DrawText(text, posX + offset, posY + offset, fontSize, color_shadow);

	DrawText(text, posX, posY, fontSize, color);
}
