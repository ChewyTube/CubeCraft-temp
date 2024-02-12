#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <unordered_map>
#include <iostream>

#include "../../Maths/Croods.h"
#include "VerticesData.h"

#include "Mesh.h"
#include "../Block/Block.h"

#include "../../Texture/TextureSegmentation.h"

// @TODO 生成Mesh时顶点去重
// 去重方法为XXXPointXXX函数，但是效果不好，跨区快有bug

namespace cubecraft {
	class World;

	using chunkDataType = std::unordered_map<BlockCroodInChunk, Block, CroodHash, CroodEqual>;
	using Vertices = std::unordered_map<Vertex, GLuint, VertexHash, VertexEqual>;

	enum Direction
	{
		up,
		down,
		left,
		right,
		front,
		back,
	};
	// 获取相邻坐标
	struct Adjacent
	{
		int x, y, z;
		BlockCroodInChunk up, down, left, right, front, back;
		void update(BlockCroodInChunk p) {
			x = p.x; 
			y = p.y; 
			z = p.z;//刷新xyz数据

			up = { x, y + 1 , z };
			down = { x, y - 1 , z };
			left = { x - 1, y , z };
			right = { x + 1, y , z };
			front = { x, y , z - 1 };
			back = { x, y , z + 1 };
		}
	};

	class ChunkMeshBuilder {
	public:
		ChunkMeshBuilder(World* p, ChunkCroodInWorld c) {
			mp_world = p;
			m_crood = c;
		}
		Mesh buildMesh(chunkDataType data);
		Mesh buildMeshwithPoint(chunkDataType data);
	private:
		Adjacent adj;

		int getBlock(chunkDataType& data, BlockCroodInChunk crood);
		void addFace(
			std::vector<GLfloat>&	vertices, 
			std::vector<GLuint>&	vIndices,
			std::vector<GLfloat>&	tIndices,
			Direction				dir, 
			BlockCroodInChunk		pos, 
			int&					addedFaces
		);
		void addFaceWithPoint(
			Vertices&				verticesPoints,
			std::vector<GLuint>&	vIndices,
			Direction				dir,
			BlockCroodInChunk		pos,
			int&					addedFaces
		);
		std::vector<GLfloat> getVerticesfromPoints(Vertices& verticesPoints);
		std::vector<GLfloat> getTIndicesfromPoints(Vertices& verticesPoints);

		World* mp_world;
		ChunkCroodInWorld m_crood;
		TextureSegmentation segmenter;
	};
}


