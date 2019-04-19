#pragma once
#include <DirectXMath.h>

// Directional Light with Ambient and Diffuse Colors.

struct DirectionalLight
{
	DirectX::XMFLOAT4 AmbientColor;
	DirectX::XMFLOAT4 DiffuseColor;
	DirectX::XMFLOAT3 Direction;
};