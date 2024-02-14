#include "Tree.h"

namespace cubecraft {
	void generateTree(World* p_world, GLint64 x, GLint64 y, GLint64 z, GLint64 seed) {
		srand(x * y * x + seed);
		int h = 7 + rand() % 4;
		for (int i = 1; i < h; i++) {
			p_world->setBlock({ x, y + i, z }, Log);
		}
		p_world->setBlock({ x, y + h, z }, Leave);
		for (int i = 0; i < rand()%3 + 1; i++) {
			p_world->setBlock({ x - 1, y + h - 1 - i, z }, Leave);
			p_world->setBlock({ x + 1, y + h - 1 - i, z }, Leave);
			p_world->setBlock({ x, y + h - 1 - i, z - 1 }, Leave);
			p_world->setBlock({ x, y + h - 1 - i, z + 1 }, Leave);
		}
	}
}