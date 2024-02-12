#include "Block.h"

namespace cubecraft {
	Block::Block(BlockType id) {
		this->id = id;
	}
	BlockType Block::getId() {
		return id;
	}
}
