#pragma once

#include <glad/glad.h>
#include "../../World.h"

namespace cubecraft {
	void generateTree(World* p_world, GLint64 x, GLint64 y, GLint64 z, GLint64 seed);
}