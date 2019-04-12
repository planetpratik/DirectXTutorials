#pragma once
#include <DirectXMath.h>

// Forward Declaration of Mesh Class.
class Mesh;

class Entity
{
public:
	// Entity's Constructor - Construct Entity with Mesh.
	explicit Entity(Mesh* t_mesh);

	//Move Entity relative to the direction it is facing
	void MoveRelative(const float& t_X, const float& t_Y, const float& t_Z);
	
	// Absolute Movement of Entity in the direction it is facing.
	void MoveAbsolute(const float& t_X, const float& t_Y, const float& t_Z);
	
	// Get this Entity's Mesh
	const Mesh* GetEntityMesh() const;
	
	// Get this Entity's current position
	const DirectX::XMFLOAT3& GetPosition() const;
	
	// Set position for this Entity using float values.
	void SetPosition(const float& t_X, const float& t_Y, const float& t_Z);
	
	// Set position using DirectX Vector3.
	void SetPosition(const DirectX::XMFLOAT3& t_position);
	
	// Get this Entity's Scale.
	const DirectX::XMFLOAT3& GetScale() const;

	// Set Scale of this Entity.
	void SetScale(const float& t_X, const float& t_Y, const float& t_Z);
	
	// Get this Entity's Current Rotation.
	const DirectX::XMFLOAT4& GetRotation() const;
	
	// Set this Entity's current Rotation.
	void SetRotation(const DirectX::XMFLOAT4& t_rotation);
	
	// Destructor for Entity (Virtual)
	virtual ~Entity();

private:
	// Pointer to Entity's Mesh Object.
	Mesh* entity_mesh = nullptr;

	// Current Position of this Entity.
	DirectX::XMFLOAT3 position;

	// Current Scale of this Entity.
	DirectX::XMFLOAT3 scale;

	// Current Rotation of this Entity.
	DirectX::XMFLOAT4 rotation;
};