#pragma once

#include "DXCore.h"
#include "SimpleShader.h"
#include <DirectXMath.h>
#include <vector>
#include "Lights.h"

// Forward Declaration
class Entity;
class Camera;
class Material;

class Game 
	: public DXCore
{

public:
	Game(HINSTANCE hInstance);
	~Game();

	// Overridden setup and game loop methods, which
	// will be called automatically
	void Init();
	void InitLights();
	void OnResize();
	void Update(float deltaTime, float totalTime);
	void Draw(float deltaTime, float totalTime);

	// Overridden mouse input helper methods
	void OnMouseDown (WPARAM buttonState, int x, int y);
	void OnMouseUp	 (WPARAM buttonState, int x, int y);
	void OnMouseMove (WPARAM buttonState, int x, int y);
	void OnMouseWheel(float wheelDelta,   int x, int y);
private:

	// Initialization helper methods - feel free to customize, combine, etc.
	void LoadShaders(); 
	void CreateMatrices();
	void CreateBasicGeometry();

	// Mesh Object to use with Mesh Class to draw 3 different shapes.
	class Mesh* MeshOne = nullptr;
	class Mesh* MeshTwo = nullptr;
	class Mesh* MeshThree = nullptr;

	// List of Entities used in our game.
	std::vector<Entity*> entities;

	size_t entityCount = 0;

	// Wrappers for DirectX shaders to provide simplified functionality
	SimpleVertexShader* vertexShader;
	SimplePixelShader* pixelShader;

	// Flying Camera to be used in our game.
	Camera* camera = nullptr;

	// Material dumb container.
	Material* material = nullptr;

	// Directional Light
	DirectionalLight directional_light;
	DirectionalLight directional_light_two;

	// The matrices to go from model space to screen space
	/*DirectX::XMFLOAT4X4 worldMatrix;
	DirectX::XMFLOAT4X4 viewMatrix;
	DirectX::XMFLOAT4X4 projectionMatrix;*/

	// Keeps track of the old mouse position.  Useful for 
	// determining how far the mouse moved in a single frame.
	POINT prevMousePos;
};

