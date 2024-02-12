#pragma once

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../Maths/Croods.h"

#include "../Enum/BlockType.h"
#include "../Enum/Direction.h"

namespace cubecraft {
	GLuint LoadTexture(std::string filePath);
	TexRelCrood getTexCrood(BlockType block, Direction dir);
}