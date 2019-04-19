#pragma once
#include <d3d11.h>
#include <vector>
#include <iostream>
#include <fstream>

class Mesh
{
public:
	// Constructor for Mesh class.
	Mesh(ID3D11Device* pDevice, struct Vertex* pVerts, UINT numVerts, UINT* pIndices, UINT numIndices);

	// Create a Mesh from object data in file.
	Mesh(ID3D11Device* pDevice, char* objFile);

	// Destructor for Mesh class. Calls Release() on both Vertex & Index buffers.
	~Mesh();

	// Get Pointer to Vertex buffer object.
	ID3D11Buffer* const GetVertexBuffer() const;

	// Get Pointer to Index buffer object.
	ID3D11Buffer* const GetIndexBuffer() const;

	// Retrieve number of Vertices this Mesh contains.
	const UINT GetIndexCount() const;

private:

	// Vertex Buffer of this Mesh
	ID3D11Buffer* IndexBuffer = nullptr;

	// Index Buffer of this Mesh
	ID3D11Buffer* VertexBuffer = nullptr;

	// Specifies how many indices are there in Mesh's Index buffer.
	UINT IndexCount;

	void CreateBuffers(ID3D11Device* pDevice, Vertex* pVerts, UINT numVerts, UINT* pIndices, UINT numIndices);
};