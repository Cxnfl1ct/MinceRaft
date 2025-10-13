#ifndef _EXT_H
#define _EXT_H

#include "raylib.h"
#include <stdio.h>

#define NOFONT (Font) { 0 }

void InitCamera(Camera *camera);
void DrawMinecraftText(Font font, const char *text, float posX, float posY, float fontSize, float spacing, Color color, bool shadow, int align, int alignv);

#endif
