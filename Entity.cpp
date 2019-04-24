#include "Entity.h"
#include "Material.h"
#include "SimpleShader.h"

struct ID3D11SamplerState;
struct ID3D11ShaderResourceView;
using namespace DirectX;

Entity::Entity(Mesh* t_mesh, Material* t_material) : 
	entity_mesh(t_mesh),
	entity_material(t_material),
	position(XMFLOAT3(0.0f, 0.0f, 0.0f)),
	scale(XMFLOAT3(1.0f, 1.0f, 1.0f)),
	rotation(XMFLOAT4())
{
}

Entity::Entity(const Entity& t_rhs)
{
	position = t_rhs.position;
	scale = t_rhs.scale;
	rotation = t_rhs.rotation;
	entity_mesh = t_rhs.entity_mesh;
}

void Entity::MoveRelative(const float& t_X, const float& t_Y, const float& t_Z)
{
	XMVECTOR direction = XMVector3Rotate(XMVectorSet(t_X, t_Y, t_Z, 0), XMLoadFloat4(&rotation));
	XMStoreFloat3(&position, XMLoadFloat3(&position) + direction);
}

void Entity::MoveAbsolute(const float& t_X, const float& t_Y, const float& t_Z)
{
	position.x += t_X;
	position.y += t_Y;
	position.z += t_Y;
}

Mesh* Entity::GetEntityMesh() const
{
	return entity_mesh;
}

const Material* Entity::GetEntityMaterial() const
{
	return entity_material;
}

const DirectX::XMFLOAT3& Entity::GetPosition() const
{
	return position;
}

void Entity::SetPosition(const float& t_X, const float& t_Y, const float& t_Z)
{
	position.x = t_X;
	position.y = t_Y;
	position.z = t_Y;
}

void Entity::SetPosition(const DirectX::XMFLOAT3& t_position)
{
	position = t_position;
}

const DirectX::XMFLOAT3& Entity::GetScale() const
{
	return scale;
}

void Entity::SetScale(const float& t_X, const float& t_Y, const float& t_Z)
{
	scale.x = t_X;
	scale.y = t_Y;
	scale.z = t_Z;
}

const DirectX::XMFLOAT4& Entity::GetRotation() const
{
	return rotation;
}

void Entity::SetRotation(const DirectX::XMFLOAT4& t_rotation)
{
	rotation = t_rotation;
}

DirectX::XMFLOAT4X4 Entity::GetWorldMatrix()
{
	XMMATRIX scaleMatrix = XMMatrixScaling(scale.x, scale.y, scale.z);
	XMMATRIX rotationMatrix = XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);
	XMMATRIX positionMatrix = XMMatrixTranslation(position.x, position.y, position.z);

	XMMATRIX world_matrix = scaleMatrix * rotationMatrix * positionMatrix;
	XMFLOAT4X4 world4x4;
	XMStoreFloat4x4(&world4x4, XMMatrixTranspose(world_matrix));
	return world4x4;
}

void Entity::prepareMaterial(const DirectX::XMFLOAT4X4& t_view_matrix, const DirectX::XMFLOAT4X4& t_projection_matrix)
{
	SimpleVertexShader* vertex_shader = entity_material->getVertexShader();
	SimplePixelShader* pixel_shader = entity_material->getPixelShader();

	vertex_shader->SetMatrix4x4("world", GetWorldMatrix());
	vertex_shader->SetMatrix4x4("view", t_view_matrix);
	vertex_shader->SetMatrix4x4("projection", t_projection_matrix);

	vertex_shader->SetShader();
	vertex_shader->CopyAllBufferData();
	pixel_shader->SetShader();
	pixel_shader->CopyAllBufferData();
}

Entity::~Entity()
{
	entity_mesh = nullptr;
	entity_material = nullptr;
}
