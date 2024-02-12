#pragma once

#include <glad/glad.h>
#include <array>
namespace cubecraft {
	struct Point
	{
		Point() = default;
		Point(GLfloat x, GLfloat y, GLfloat z) {
			this->x = x;
			this->y = y;
			this->z = z;
		}
		GLfloat x, y, z;
	};
	struct TextureCrood
	{
		GLfloat x, y;
	};
	struct Vertex
	{
		Point p;
		TextureCrood t;
	};

	struct VertexEqual
	{

		bool operator()(const Vertex& v1, const Vertex& v2) const {
			return v1.p.x == v2.p.x && v1.p.y == v2.p.y && v1.p.z == v2.p.z &&
				v1.t.x == v2.t.x && v1.t.y == v2.t.y;
		}
	}; 
	struct VertexHash
	{
		std::size_t operator()(const Vertex& v) const {
			std::hash<decltype(v.p.x)> hasher1;
			auto hash1 = hasher1(v.p.x);
			auto hash2 = hasher1(v.p.y);
			auto hash3 = hasher1(v.p.z);

			std::hash<decltype(v.t.x)> hasher2;
			auto hash4 = hasher1(v.t.x);
			auto hash5 = hasher1(v.t.y);

			return std::hash<decltype(v.p.x)>{}(
				(hash1 ^ (hash2 >> hash3) ^ hash3) ^ (hash4 >> hash5)
			);
		}
	};

	extern std::array<GLuint, 6> blockIndices;

	extern std::array<GLfloat, 12> frontFace;
	extern std::array<GLfloat, 12> backFace;
	extern std::array<GLfloat, 12> leftFace;
	extern std::array<GLfloat, 12> rightFace;
	extern std::array<GLfloat, 12> topFace;
	extern std::array<GLfloat, 12> bottomFace;

	extern std::array<Point, 4> backPoint;
	extern std::array<Point, 4> frontPoint;
	extern std::array<Point, 4> leftPoint;
	extern std::array<Point, 4> rightPoint;
	extern std::array<Point, 4> topPoint;
	extern std::array<Point, 4> bottomPoint;

	extern std::array<GLfloat, 8> _textureIndices;
	extern std::array<std::array<GLfloat, 2>, 4> texturePoints;
}