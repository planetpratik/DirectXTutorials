#include "RenderManager.h"
#include "Entity.h"
#include "Mesh.h"

RenderManager::RenderManager()
{
	initializeMeshes();
	initializeEntities();
}

RenderManager::~RenderManager()
{
	for (size_t i = 0; i < entityCount; ++i)
	{
		Entity* currentEntity = Entities[i];
		if (currentEntity != nullptr)
		{
			delete currentEntity;
		}
	}
	Entities.clear();
	entityCount = 0;
	for (size_t i = 0; i < meshCount; ++i)
	{
		Mesh* currentMesh = Meshes[i];
		if (currentMesh != nullptr)
		{
			delete currentMesh;
		}
	}
	Meshes.clear();
	meshCount = 0;
}

void RenderManager::update(float deltaTime)
{
}

void RenderManager::drawEntities()
{
}

void RenderManager::addEntity(Mesh* entityMesh)
{
	if (entityMesh != nullptr)
	{
		Entities.push_back(new Entity(entityMesh));
		++entityCount;
	}
}

void RenderManager::addMesh(ID3D11Device* pDevice, Vertex* pVerts, UINT numVerts, UINT* pIndices, UINT numIndices)
{
	Mesh* currentMesh = new Mesh(pDevice, pVerts, numVerts, pIndices, numIndices);
	Meshes.push_back(currentMesh);
	++currentMesh;
}

void RenderManager::initializeMeshes()
{
}

void RenderManager::initializeEntities()
{
}
