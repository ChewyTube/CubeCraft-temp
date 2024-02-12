#pragma once

#include "array"
#include <glad/glad.h>

#include "../Config.h"
#include "../Maths/Croods.h"

namespace cubecraft {
	class TextureSegmentation {
	public:
		std::array<GLfloat, 8> getTexIndices(TexRelCrood crood);
	private:
		
	};
}