#pragma once

#include <glm/glm.hpp>

using namespace glm;

struct VertexBase
{
	VertexBase() {}
	VertexBase(float x, float y, float z, float r, float g, float b)
		:position(x, y, z), color(r, g, b) {}

	vec3 position;
	vec3 color;
};

struct Vertex
{
	vec3 position;
	vec4 texCoord;
	vec3 normal;
	vec3 tangent;
};

struct VertexTex
{
	vec3 position;
	vec4 texCoord;
};
