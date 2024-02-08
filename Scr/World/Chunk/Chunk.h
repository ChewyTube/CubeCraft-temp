#pragma once
#include <array>
#include <unordered_map>

#include "../../Config.h"
#include "../../Maths/Croods.h"
#include "Mesh.h"
#include "ChunkMeshBuilder.h"

namespace cubecraft {
	class Chunk {
	public:
		std::unordered_map<BlockCroodInChunk, int, CroodHash, CroodEqual>& getBlockData();
		void setBlock(BlockCroodInChunk crood, int block);
		void buildMesh();
		Mesh getMesh();
	private:
		//暂定为0无方块 1有方块
		std::unordered_map<BlockCroodInChunk, int, CroodHash, CroodEqual> blockData;
		Mesh mesh;
		ChunkMeshBuilder builder;
	};
}
