#include "world.h"
/*
int WorldInit(int type, long seed, Vector3 size) {
	switch (type) {
		case 1:
		{
			WorldInitFlat(DEFAULT_BLOCKS, size);
			break;
		}

		case 2:
		{
			// Not implemented
			
			WorldInitFlat(DEFAULT_BLOCKS, size);
			break;
		}

		default:
		{
			WorldInitFlat(EMPTY_BLOCKS, size);
			break;
		}
	}
}

int WorldInitFlat(short *blocks, Vector3 size) {
}

void WorldSetBorder(Vector2 border) {
	world.boundary.x = border.x;
	world.boundary.z = border.y;
}

void WorldSetHeight(unsigned int height) {
	world.boundary.y = (float) height;
}

int WorldValidateCoord(Vector3 boundary, int x, int y, int z) {
	if (y > boundary.y || y < 0)
		return 0;

	if (x > boundary.x || x < boundary.x * -1)
		return 0;

	if (z > boundary.z || z < boundary.z * -1)
		return 0;

	return 1;
}


short WorldGetBlockAt(Chunk chunk, int x, int y, int z) {
	short *CurrentChunk = chunk->data;

	if (!WorldValidateCoord(world.boundary, x, y, z) )
		return 1; // Error if the coord is invalid

	return CurrentChunk[x + z * 16 + y * 256];
}

int WorldPutBlockAt(Chunk chunk, int x, int y, int z, short block) {
	short *CurrentChunk = chunk->data;

	if (!WorldValidateCoord(world.boundary, x, y, z) )
		return 1; // Error if the coord is invalid

	CurrentChunk[x + z * 16 + y * 256] = block;
}
*/
