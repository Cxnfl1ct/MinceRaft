#include "textures.h"

Texture2D dummy_tex;

extern Texture2D textures[MAX_TEXTURES];
extern unsigned int tex_cnt;

int TextureAppend(Texture2D tex) {
	if (tex_cnt < 0 || tex_cnt >= MAX_TEXTURES)
		return 1;

	textures[tex_cnt++] = tex;

	return 0;
}

int TextureSet(unsigned int idx, Texture2D tex) {
	if (idx < 0 || idx >= tex_cnt)
		return 1;

	textures[idx] = tex;

	return 0;
}

Texture2D TextureFetch(unsigned int idx) {
	Texture2D ret_tex;

	if (idx >= 0 && idx < tex_cnt)
		ret_tex = textures[idx];

	return ret_tex;
}

int TextureRemove(unsigned int idx) {
	if (idx >= 0 && idx < tex_cnt)
		return 1;

	UnloadTexture(textures[idx]);

	if (tex_cnt > 0)
		tex_cnt--;

	return 0;
}

int TextureRemoveAll() {
	int i, lim;

	if (tex_cnt >= MAX_TEXTURES)
		lim = MAX_TEXTURES;
	else
		lim = tex_cnt;

	for (i = 0; i <= lim; i++)
		UnloadTexture(textures[i]);

	tex_cnt = 0;

	return 0;
}
