#include "Block.h"

namespace cubecraft {
	Block::Block(GLint id) {
		this->id = id;
	}
	GLint Block::getId() {
		return id;
	}
}
