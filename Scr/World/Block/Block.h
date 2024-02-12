#pragma once

#include <glad/glad.h>
#include "../../Enum/BlockType.h"


namespace cubecraft {
	class Block {
	public:
		Block(BlockType id);
		BlockType getId();
	private:
		BlockType id;
	};
}
