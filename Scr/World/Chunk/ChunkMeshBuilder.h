#pragma once

#include "VerticesData.h"

#include <vector>
#include <unordered_map>

#include "../../Maths/Croods.h"
#include "VerticesData.h"

#include "Mesh.h"

namespace cubecraft {
	using chunkDataType = std::unordered_map<BlockCroodInChunk, int, CroodHash, CroodEqual>;
	
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
		Mesh buildMesh(chunkDataType data);
	private:
		Adjacent adj;

		int getBlock(chunkDataType& data, BlockCroodInChunk crood);
		void addFace(std::vector<GLfloat>& vertices, 
			std::vector<GLuint>& vIndices,std::vector<GLuint>& tIndices, 
			Direction dir, BlockCroodInChunk pos, int& addedFaces);
	};
}


