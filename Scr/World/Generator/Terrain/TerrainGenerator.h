#pragma once

#include "../../../Maths/Noise.h"

#include <glad/glad.h>
#include <vector>

#include "../../World.h"
#include "../Features/Tree.h"

#include <random>

namespace cubecraft {
	class TerrainGenerator {
	public:
		TerrainGenerator(
			GLfloat _amplitude,
			GLfloat _frequency,
			GLfloat _substrate,
			GLfloat _persistence,
			GLuint  _octaves,
			World*  _p_world
			);
		void generateWorld(GLint64 xmin, GLint64 xmax, GLint64 zmin, GLint64 zmax);
	private:
		GLint64 seed = 1145141919810;
		PerlinNoise noise = PerlinNoise(seed);
		GLfloat amplitude = 1.0f;	// 振幅
		GLfloat frequency = 1.0f;	// 频率
		GLfloat substrate = 64.0f;	// 基底

		GLfloat persistence = 0.5f; // 持续度 每次频率翻倍时，振幅的衰减比例
		GLuint  octaves     = 4;	// 八度数 叠加的柏林噪声的个数

		World* mp_world = nullptr;

		GLint getHeight(GLfloat x, GLfloat z);
		void setTree(GLint64 x, GLint64 y, GLint64 z);
	};
}