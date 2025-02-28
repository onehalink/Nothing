#include "Mesh.h"



namespace Engine
{
	Mesh::Mesh()
	{
		Memory::Clear( this, sizeof(Mesh) );
	}

	Mesh::Mesh(const Mesh& other)
	{
		CopyFrom(other);
	}

	Mesh::Mesh(Mesh&& other)
	{
		vertices	= Move( other.vertices );
		indices		= Move( other.indices );
		slices		= Move( other.slices );

		primitive	= other.primitive;
	}

	Mesh::~Mesh()
	{

	}

	Mesh& Mesh::operator=(const Mesh& other)
	{
		CopyFrom(other);

		return *this;
	}

	Mesh& Mesh::operator=(Mesh&& other)
	{
		vertices	= Move( other.vertices );
		indices		= Move( other.indices );
		slices		= Move( other.slices );

		Swap( &primitive, &other.primitive );

		return *this;
	}

	Void Mesh::CopyFrom(const Mesh& other)
	{
		vertices	= other.vertices;
		indices		= other.indices;
		slices		= other.slices;
		primitive	= other.primitive;
	}
}