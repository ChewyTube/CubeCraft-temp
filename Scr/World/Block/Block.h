#pragma once

#include <glad/glad.h>

namespace cubecraft {
	class Block {
	public:
		Block(GLint id);
		GLint getId();
	private:
		GLint id;
	};
}
