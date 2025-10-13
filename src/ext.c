#include "raylib.h"
#include "ext.h"
#include "config.h"

void InitCamera(Camera *camera) {
	camera->position = (Vector3){5.0f, 1.0f, 5.0f};
	camera->target = (Vector3){0.0f, 0.0f, 0.0f};
	camera->up = (Vector3){0.0f, 1.0f, 0.0f};
	camera->fovy = 65.0f;
	camera->projection = CAMERA_PERSPECTIVE;
}

void DrawMinecraftText(Font font, const char *text, float posX, float posY, float fontSize, float spacing, Color color, bool shadow, int align, int alignv) {
	float posX_, posY_;
	int sw, sh;
	
	Font font_;

	float offset = fontSize / 10;
	Color color_shadow = {color.r / 4, color.g / 4, color.b / 4, color.a};

	if (!IsWindowReady() ) {
		TraceLog(LOG_ERROR, "Window is not initialized and DrawMinecraftText was called!");
		return;
	} else {
		sw = GetScreenWidth();
		sh = GetScreenHeight();
	}

	if (font.baseSize == 0)
		font_ = GetFontDefault();
	else
		font_ = font;

	Vector2 fw = MeasureTextEx(font_, text, fontSize, spacing);

	switch (align) {
		case 1: {
			posX_ = (sw / 2 - fw.x / 2) + posX;
			break;
		}
		case 2: {
			posX_ = (sw - fw.x) + posX;
			break;
		}
		default: {
			posX_ = posX;
			break;
		}
	}

	switch (alignv) {
		case 1:	{
			posY_ = (sh / 2 - fw.y / 2) + posY;
			break;
		}
		case 2: {
			posY_ = (sh - fw.y) + posY;
			break;
		}
		default: {
			posY_ = posY;
			break;
		}
	}

#ifdef DEBUG_MODE
	printf("DrawMinecraftText > args: text: %s, posx: %.3f, posy: %.3f, fontSize: %.3f, spacing: %.3f, align: %d %d\n", text, posX, posY, fontSize, spacing, align, alignv);
	printf("DrawMinecraftText > Calculated offset = posx > %.3f, posy > %.3f, offset > %.3f\n", posX_, posY_, offset);
	printf("DrawMinecraftText > Miscellaneous informations: screen: %d, %d, textbox: %.3f, %.3f\n\n", sw, sh, fw.x, fw.y);
#endif

	if (shadow)
		DrawTextEx(font_, text, (Vector2) { posX_ + offset, posY_ + offset}, fontSize, spacing, color_shadow);

	DrawTextEx(font_, text, (Vector2) { posX_, posY_ }, fontSize, spacing, color);
}
