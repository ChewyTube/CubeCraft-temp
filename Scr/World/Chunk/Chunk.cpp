#include "Chunk.h"

namespace cubecraft {
	std::unordered_map<BlockCroodInChunk, int, CroodHash, CroodEqual>& Chunk::getBlockData() {
		return blockData;
	}
	void Chunk::setBlock(BlockCroodInChunk crood, int block) {
		blockData.insert({ crood, block });
	}
	
	void Chunk::buildMesh() {
		//mesh = builder.buildMeshwithPoint(blockData);
		mesh = builder.buildMesh(blockData);
	}
	Mesh Chunk::getMesh() {
		return mesh;
	}
	
	
}