#pragma once

#include "../Core.h"



namespace Engine
{
	struct ENGINE_API Mesh
	{
		enum class Primitive
		{
			Point,
			Line,
			Triangle,
		};


		struct Vertex
		{
			Vector3 position;
			Vector3 normal;
			Vector2 uv;
		};


		// Used to apply different materials on the same mesh(break up a mesh to some submeshes)
		struct Slice
		{
			SizeType firstIndex;
			SizeType count;
		};
		

		Array<Vertex>	vertices;
		Array<UInt32>	indices;
		Array<Slice>	slices;
		Primitive		primitive;


		Mesh();
		Mesh(const Mesh& other);
		Mesh(Mesh&& other);
		~Mesh();


		Mesh& operator=(const Mesh& other);
		Mesh& operator=(Mesh&& other);
	private:
		Void CopyFrom(const Mesh& other);
	};
}