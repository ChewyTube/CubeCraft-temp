#include "VerticesData.h"

namespace cubecraft {
	std::array<GLuint, 6> blockIndices = {
		0, 1, 3,
		1, 2, 3,
	};
	std::array<GLfloat, 12> frontFace = {
		0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1,
	};
	std::array<GLfloat, 12> backFace = {
		1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0,
	};
	std::array<GLfloat, 12> leftFace = {
		0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0,
	};
	std::array<GLfloat, 12> rightFace = {
		1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1,
	};
	std::array<GLfloat, 12> topFace = {
		0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0,
	};
	std::array<GLfloat, 12> bottomFace = {
		0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1,
	};
	std::array<GLuint, 8> textureIndices = {
		0, 0, 1, 0, 1, 1, 0, 1,
	};
}