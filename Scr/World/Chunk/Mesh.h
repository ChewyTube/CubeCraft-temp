﻿#pragma once

#include <glad/glad.h>
#include <vector>

namespace cubecraft {
	class Mesh {
	public:
		Mesh() = default;
		Mesh(
			std::vector<GLfloat>	_vertices,
			std::vector<GLuint>		_vIndices,
			std::vector<GLfloat>	_tIndices) {
			vertices = _vertices;
			vIndices = _vIndices;
			tIndices = _tIndices;
		}
		std::vector<GLfloat> getVertices();
		std::vector<GLuint> getVer_Indices();
		std::vector<GLfloat> getTex_Indices();
	private:
		std::vector<GLfloat> vertices; // 顶点
		std::vector<GLuint> vIndices; // 顶点索引
		std::vector<GLfloat> tIndices; // 纹理索引
	};
}