/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include <stdio.h>

#include "raylib.h"
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

#include "ext.h"
#include "config.h"
#include "keywords.h"
#include "player.h"

Model models[MAX_MODELS];
unsigned int models_cnt = 0;

Texture2D textures[MAX_TEXTURES];
unsigned int tex_cnt = 0;

Player players[MAX_PLAYERS];
unsigned int player_cnt = 0;

Mesh grass_msh;

Music bg;

float playSound;
float volume;

Camera camera = { 0 };

float rotation = 0;

bool pause;

int sw, sh;

extern Font dummy;

#include "models.h"
#include "textures.h"
#include "player_lst.h"

void InitGame();

void TestStub();

void EndGame();

void UpdateDrawFrame();

void UpdateGame();
void DrawGame();

void ProcessInput();

void DrawMap();
void DrawBG();
void DrawObjects();
void DrawOverlay();
void DrawPauseOverlay();

int main() {
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitGame();

	while (!WindowShouldClose()) {
		UpdateDrawFrame();
	}

	EndGame();

	return 0;
}

void InitGame() {
	Model niko_mod, grass_mod;
	Texture2D niko_tex, grass_tex;
//	Mesh grass_msh;

	// Initialize game runtime

	InitWindow(1280, 800, "MinceRaft - OneShot Niko");
	SetTargetFPS(60);

	sw = GetScreenWidth();
	sh = GetScreenHeight();

	SearchAndSetResourceDir("resources");

	// Initialize audio

	InitAudioDevice();

	if (!IsAudioDeviceReady()) {
		TraceLog(0, "Initializing audio device failed!");
	}

	niko_mod = LoadModel("niko.obj");
	niko_tex = LoadTexture("niko.png");
	grass_tex = LoadTexture("grass.png");

	grass_msh = GenMeshCube(1.0f, 1.0f, 1.0f);
	grass_mod = LoadModelFromMesh(grass_msh);

	if (!IsModelValid(niko_mod)) {
		TraceLog(0, "Failed to load <niko.obj>!");
	}

	if (!IsMusicValid(bg)) {
		TraceLog(0, "Failed to load <bg.mp3>!");
	}

	// Append models to global model storage

	ModelAppend(niko_mod);
	ModelAppend(grass_mod);

	TextureAppend(niko_tex);
	TextureAppend(grass_tex);

	// Apply textures to models

	SetMaterialTexture(&models[0].materials[0], MATERIAL_MAP_DIFFUSE, textures[0]);
	SetMaterialTexture(&models[1].materials[0], MATERIAL_MAP_DIFFUSE, textures[1]);

	// Initialize audio

	bg = LoadMusicStream("bg.mp3");

	playSound = 1;
	volume = 0.50f;

	pause = false;

	// Initialize viewport

	DisableCursor();

	InitCamera(&camera);

	TestStub();
}

void TestStub() {
	Player test;

	// Initialize player 'test'
	test.pos = (Vector3) {0.0f, 0.0f, 0.0f};
	test.pitch = 0.0f;
	test.yaw = 0.0f;
	test.hp = 20.0f;
	test.hunger = 20.0f;
	test.dead = false;
	TextCopy(test.name, "nikoOneshot123_");

	PlayerAppend(test);
}

void EndGame() {
	StopMusicStream(bg);

	ModelRemoveAll();
	TextureRemoveAll();

	UnloadMusicStream(bg);

	CloseAudioDevice();

	CloseWindow();
}

void UpdateDrawFrame() {
	UpdateGame();
	DrawGame();
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

		UpdateCameraPro(&camera, (Vector3){
                	(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))*0.1f -      // Move forward-backward
                	(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))*0.1f,
                	(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))*0.1f -   // Move right-left
                	(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))*0.1f,
                	0.0f                                                // Move up-down
            	},
            	(Vector3){
                	GetMouseDelta().x*0.05f,                            // Rotation: yaw
                	GetMouseDelta().y*0.05f,                            // Rotation: pitch
                	0.0f                                                // Rotation: roll
            	},
	    	0.0f);
	}

	if (IsMusicStreamPlaying(bg) )
		SetMasterVolume( (float) volume * playSound );

	if (!IsMusicStreamPlaying(bg) ) {
		PlayMusicStream(bg);
	}
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
		InitCamera(&camera);
}

// Draw

void DrawBG() {
	ClearBackground((Color) {170, 225, 255, 255});
	DrawGrid(50, 1);
}

void DrawMap() {
	int i, j;
	float k, l;

	k = -50;
	l = -50;

	for (i=0; i<100; i++) {	
		for (j=0; j<100; j++) {
			k += 1;
			DrawModel(grass, (Vector3) {k, -0.5f, l}, 1, WHITE);
		}

		k = -50;
		l += 1;
	}
}

void DrawObjects() {
	DrawPlayer(&players[0]);
//	DrawModelEx(niko, (Vector3) {0.0f, 0.0f, 0.0f}, (Vector3) {0, 0, rotation}, 0.0f, (Vector3) {1.2f, 1.2f, 1.2f}, WHITE);
}

void DrawOverlay() {
	char debug_txt[256];
	char volume_txt[64];

	sprintf(debug_txt, "%dFPS - Frame render took %.3fs - Program Uptime: %.f", GetFPS(), GetFrameTime(), GetTime() );
	sprintf(volume_txt, "Current volume: %.f%%", volume * 100);

	DrawMinecraftText(NOFONT, BRAND_TXT, 5, 5, 20, TXT_SP, WHITE, true, 0, 0);
	DrawMinecraftText(NOFONT, debug_txt, 5, 0, 20, TXT_SP, WHITE, true, 0, 2);
	DrawMinecraftText(NOFONT, volume_txt, -5, 5, 20, TXT_SP, WHITE, true, 2, 0);

	if (!playSound)
		DrawMinecraftText(NOFONT, "MUTED", -5, 30, 20, TXT_SP, WHITE, true, 1, 0);
}

void DrawPauseOverlay() {
	DrawRectangle(0, 0, sw, sh, (Color) {0, 0, 0, 127} );
	DrawMinecraftText(NOFONT, "PAUSED", COORD_HOME, 80, TXT_SP, WHITE, true, 1, 1);
}

void DrawDeadOverlay() {
	DrawRectangle(0, 0, sw, sh, (Color) {127, 0, 0, 127} );
	DrawMinecraftText(NOFONT, "You died!", COORD_HOME, 60, TXT_SP, WHITE, true, 1, 1);
}
