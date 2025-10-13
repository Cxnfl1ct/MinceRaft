#ifndef _TEXTURES_H
#define _TEXTURES_H

#include "raylib.h"
#include "config.h"

int TextureAppend(Texture2D model);
int TextureSet(unsigned int idx, Texture2D model);
Texture2D TextureFetch(unsigned int idx);
int TextureRemove(unsigned int idx);
int TextureRemoveAll();

#endif
