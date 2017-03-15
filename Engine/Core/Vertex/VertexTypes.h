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
	Vertex() {}
	Vertex(float x, float y, float z, float u, float v)
		:position(x, y, z), texCoord(u,v) {}

	vec3 position;
	vec2 texCoord;
	//vec3 normal;
	//vec3 tangent;
};

struct VertexTex
{
	vec3 position;
	vec4 texCoord;
};
