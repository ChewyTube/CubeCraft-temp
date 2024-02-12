#include "TextureSegmentation.h"

namespace cubecraft {
	std::array<GLfloat, 8> TextureSegmentation::getTexIndices(TexRelCrood crood) {
		int width  = TotalTexWidth  / singleTexWidth;
		if (crood.x > width || crood.y > width) {
			throw "illegal texture coordinates";
		}

		GLfloat _left  =  crood.x    * singleTexWidth;
		GLfloat _right = (crood.x+1) * singleTexWidth;
		GLfloat _up    =  crood.y    * singleTexWidth;
		GLfloat _down  = (crood.y+1) * singleTexWidth;

		GLfloat left  = _left  / TotalTexWidth;
		GLfloat right = _right / TotalTexWidth;
		// 加载图像时y轴反转，这里返回来
		GLfloat up    = _down  / TotalTexWidth;
		GLfloat down  = _up    / TotalTexWidth;

		return { left, up, right, up, right, down, left, down };
	}
}