#pragma once
#include <d3d11.h>
#include <vector>

// Forward Declarations.
class Entity;
class Mesh;
struct Vertex;


class RenderManager
{
public:
	// Default Constructor for RenderManager
	RenderManager();

	// Destructor for RenderManager
	~RenderManager();

	// Update all current Entities
	void update(float deltaTime);

	// Draw all entities in the Scene
	void drawEntities();

	// Add an Entity to RenderManager
	void addEntity(Mesh* entityMesh);

	// Create a Mesh and add it to our Mesh Vector.
	void addMesh(ID3D11Device* pDevice, struct Vertex* pVerts, UINT numVerts, UINT* pIndices, UINT numIndices);
private:
	void initializeMeshes();
	void initializeEntities();
	size_t entityCount = 0;
	size_t meshCount = 0;
	std::vector<Mesh*> Meshes;
	std::vector<Entity*> Entities;
};