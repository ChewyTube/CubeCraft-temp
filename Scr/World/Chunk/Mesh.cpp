#include "Mesh.h"

namespace cubecraft {
	std::vector<GLfloat> Mesh::getVertices() {
		return vertices;
	}
	std::vector<GLuint> Mesh::getVer_Indices() {
		return vIndices;
	}
	std::vector<GLuint> Mesh::getTex_Indices() {
		return tIndices;
	}
}