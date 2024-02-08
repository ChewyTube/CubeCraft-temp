#pragma once

#include <glad/glad.h>
#include <array>
namespace cubecraft {
	extern std::array<GLuint, 6> blockIndices;
	extern std::array<GLfloat, 12> frontFace;
	extern std::array<GLfloat, 12> backFace;
	extern std::array<GLfloat, 12> leftFace;
	extern std::array<GLfloat, 12> rightFace;
	extern std::array<GLfloat, 12> topFace;
	extern std::array<GLfloat, 12> bottomFace;
	extern std::array<GLuint, 8> textureIndices;
}