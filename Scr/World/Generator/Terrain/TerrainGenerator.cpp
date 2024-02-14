#include "TerrainGenerator.h"

namespace cubecraft {
	TerrainGenerator::TerrainGenerator(
		GLfloat _amplitude,			GLfloat _frequency,		GLfloat _substrate,
		GLfloat _persistence,		GLuint  _octaves,		World* _p_world
	):
		amplitude(_amplitude),		frequency(_frequency),	substrate(_substrate),
		persistence(_persistence),	octaves(_octaves),		mp_world(_p_world){}

	GLint TerrainGenerator::getHeight(GLfloat x, GLfloat z) {
		GLfloat height = 0;
		auto f = frequency;
		auto a = amplitude;
		for (int i = 0; i < octaves; i++) {
			auto h = noise.noise(x * f, z * f) * a;
			height += h;
			f *= persistence;
			a /= persistence;
		}

		return static_cast<int>(height) + substrate;
		//return static_cast<int>(noise.noise(x * frequency, z * frequency) * amplitude + substrate);

	}
	void TerrainGenerator::generateWorld(GLint64 xmin, GLint64 xmax, GLint64 zmin, GLint64 zmax){
		std::vector<BlockCroodInWorld> trees;

		
		std::default_random_engine eng(seed);
		std::uniform_int_distribution<int> x_random(xmin, xmax - 1);
		std::uniform_int_distribution<int> z_random(zmin, zmax - 1);

		for (float x = xmin; x < xmax; x += 1) {
			for (float z = zmin; z < zmax; z += 1) {
				auto h = getHeight(x, z);
				if (h < 0) {
					continue;
				}
				mp_world->setBlock({ (int)x, (int)h, (int)z }, Block(Grass));
				for (int y = 0; y < h; y++) {
					mp_world->setBlock({ (int)x, (int)y, (int)z }, Block(Dirt));
				}
 				if (x_random(eng) % 12 == 0 && z_random(eng) % 12 == 0) {
					trees.push_back({ (int)x, (int)h, (int)z});
				}
			}
		}
		for (auto c : trees) {
			setTree(c.x, c.y, c.z);
		}
	}
	void TerrainGenerator::setTree(GLint64 x, GLint64 y, GLint64 z) {
		generateTree(mp_world, x, y, z, seed);
	}
}