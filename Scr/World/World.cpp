#include "World.h"

namespace cubecraft {
	void World::setBlock(BlockCroodInWorld crood, Block block) {
		auto chunkcrood = getChunkCrood(crood);
		auto blockcrood = getBlockChunkCrood(crood);

		auto& chunk = getChunk(chunkcrood, set);
		chunk.setBlock(blockcrood, block);
	}

	WorldDataType World::getWorldData() {
		return worldData;
	}

	void World::buildMesh() {
		for (auto& chunk : worldData) {
			chunk.second.buildMesh();
		}
	}
	void World::buildWorldMesh() {
		buildMesh();
		float startTime = static_cast<float>(glfwGetTime());
		// @TODO 去重！！！
		std::vector<GLfloat> vertices; // 顶点
		std::vector<GLuint> vIndices; // 顶点索引
		std::vector<GLfloat> tIndices; // 纹理索引

		for (auto& chunk : worldData) {
			Mesh chunkMesh = chunk.second.getMesh();
			auto chunkVertices = chunkMesh.getVertices();
			auto chunkVIndices = chunkMesh.getVer_Indices();
			auto chunkTIndices = chunkMesh.getTex_Indices();
			vertices.insert(vertices.begin(), chunkVertices.begin(), chunkVertices.end());
			vIndices.insert(vIndices.begin(), chunkVIndices.begin(), chunkVIndices.end());
			tIndices.insert(tIndices.begin(), chunkTIndices.begin(), chunkTIndices.end());

			// 一点也不优雅，以后一定要该！ TODO
			for (int i = 0; i < chunkVertices.size(); i++) {
				if (i % 3 == 0) { vertices[i] += chunk.first.x * 16; }
				if (i % 3 == 1) { vertices[i] += chunk.first.y * 16; }
				if (i % 3 == 2) { vertices[i] += chunk.first.z * 16; }
			}
			for (int i = 0; i < chunkVIndices.size(); i++) {
				vIndices[i] += (int)((float)(vIndices.size() - chunkVIndices.size())*2/3);
				//一个面的索引有013123六个，但是只用了4个数，因此乘2/3进行修正
			}
		}

		worldMesh = Mesh(vertices, vIndices, tIndices);
		float endTime = static_cast<float>(glfwGetTime());
		std::cout << "Successfully build world mesh. Use time:" << (endTime - startTime) * 1000 << "ms";
		std::cout << "	World pointer:" << p_world << std::endl;
		std::cout << "Total vertices: " << vertices.size()/3 << std::endl;
	}
	Mesh World::getMesh() {
		return worldMesh;
	}
	Block World::getBlock(BlockCroodInWorld crood, usage u) {
		ChunkCroodInWorld chunkcrood = getChunkCrood(crood);
		BlockCroodInChunk blockcrood = getBlockChunkCrood(crood);

		auto& chunk = getChunk(chunkcrood, u);
		if (chunk.empty()) {
			return Block(None);
		}
		auto block = chunk.getBlock(blockcrood);

		return block;
	}
	Chunk& World::getChunk(ChunkCroodInWorld crood, usage u) {
		auto it = worldData.find(crood);
		if (it == worldData.end()) {
			if (u == get) {
				Chunk chunk(nullptr, {});
				return chunk;
			}
			if (u == set) {
				auto chunk = worldData.insert({ crood, Chunk(p_world, crood) });
			}
			
		}
		return worldData.find(crood)->second;
	}
}