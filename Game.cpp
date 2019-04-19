#include "Game.h"
#include "Vertex.h"
#include "Mesh.h"
#include "Entity.h"
#include "Camera.h"
#include "Material.h"

// For the DirectX Math library
using namespace DirectX;

// --------------------------------------------------------
// Constructor
//
// DXCore (base class) constructor will set up underlying fields.
// DirectX itself, and our window, are not ready yet!
//
// hInstance - the application's OS-level handle (unique ID)
// --------------------------------------------------------
Game::Game(HINSTANCE hInstance)
	: DXCore( 
		hInstance,		   // The application's handle
		"DirectX Game",	   // Text for the window's title bar
		1280,			   // Width of the window's client area
		720,			   // Height of the window's client area
		true)			   // Show extra stats (fps) in title bar?
{
	// Initialize fields
	vertexShader = 0;
	pixelShader = 0;
	entityCount = 0;
	camera = new Camera();

#if defined(DEBUG) || defined(_DEBUG)
	// Do we want a console window?  Probably only in debug mode
	CreateConsoleWindow(500, 120, 32, 120);
	printf("Console window created successfully.  Feel free to printf() here.");
#endif
}

// --------------------------------------------------------
// Destructor - Clean up anything our game has created:
//  - Release all DirectX objects created here
//  - Delete any objects to prevent memory leaks
// --------------------------------------------------------
Game::~Game()
{
	// Delete our simple shader objects, which
	// will clean up their own internal DirectX stuff
	delete vertexShader;
	delete pixelShader;

	if (material)
	{
		delete material;
	}
	
	if (camera)
	{
		delete camera;
	}
	
	// Delete Mesh objects as we created them on heap;
	delete MeshOne;
	delete MeshTwo;
	delete MeshThree;

	// Delete Entities
	for (size_t i = 0; i < entityCount; ++i)
	{
		Entity* currentEntity = entities[i];
		if (currentEntity != nullptr)
		{
			delete currentEntity;
		}
	}
	entities.clear();
	entityCount = 0;

}

// --------------------------------------------------------
// Called once per program, after DirectX and the window
// are initialized but before the game loop.
// --------------------------------------------------------
void Game::Init()
{
	// Helper methods for loading shaders, creating some basic
	// geometry to draw and some simple camera matrices.
	//  - You'll be expanding and/or replacing these later
	LoadShaders();
	CreateMatrices();
	CreateBasicGeometry();

	InitLights();

	// Tell the input assembler stage of the pipeline what kind of
	// geometric primitives (points, lines or triangles) we want to draw.  
	// Essentially: "What kind of shape should the GPU draw with our data?"
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

// --------------------------------------------------------
// Loads shaders from compiled shader object (.cso) files using
// my SimpleShader wrapper for DirectX shader manipulation.
// - SimpleShader provides helpful methods for sending
//   data to individual variables on the GPU
// --------------------------------------------------------
void Game::LoadShaders()
{
	vertexShader = new SimpleVertexShader(device, context);
	if (!vertexShader->LoadShaderFile(L"Debug/VertexShader.cso"))
		vertexShader->LoadShaderFile(L"VertexShader.cso");		

	pixelShader = new SimplePixelShader(device, context);
	if(!pixelShader->LoadShaderFile(L"Debug/PixelShader.cso"))	
		pixelShader->LoadShaderFile(L"PixelShader.cso");

	// You'll notice that the code above attempts to load each
	// compiled shader file (.cso) from two different relative paths.

	// This is because the "working directory" (where relative paths begin)
	// will be different during the following two scenarios:
	//  - Debugging in VS: The "Project Directory" (where your .cpp files are) 
	//  - Run .exe directly: The "Output Directory" (where the .exe & .cso files are)

	// Checking both paths is the easiest way to ensure both 
	// scenarios work correctly, although others exist
}

void Game::InitLights()
{
	directional_light.AmbientColor = XMFLOAT4(0.1, 0.1, 0.1, 1.0);
	directional_light.DiffuseColor = XMFLOAT4(0.0, 0.0, 1.0, 1.0);
	directional_light.Direction = XMFLOAT3(1.0, -1.0, 0.0);

	directional_light_two.AmbientColor = XMFLOAT4(0.1, 0.1, 0.1, 1.0);
	directional_light_two.DiffuseColor = XMFLOAT4(1.0, 0.1, 0.1, 1.0);
	directional_light_two.Direction = XMFLOAT3(1.0, -1.0, 0.5);
}

// --------------------------------------------------------
// Initializes the matrices necessary to represent our geometry's 
// transformations and our 3D camera
// --------------------------------------------------------
void Game::CreateMatrices()
{
	camera->updateProjectionMatrix(width, height);
}


// --------------------------------------------------------
// Creates the geometry we're going to draw - a single triangle for now
// --------------------------------------------------------
void Game::CreateBasicGeometry()
{
	// Create some temporary variables to represent colors
	// - Not necessary, just makes things more readable
	XMFLOAT4 red	= XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	XMFLOAT4 green	= XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	XMFLOAT4 blue	= XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);

	// Set up the vertices of the triangle we would like to draw
	// - We're going to copy this array, exactly as it exists in memory
	//    over to a DirectX-controlled data structure (the vertex buffer)
	Vertex verticesOne[] = 
	{
		{ XMFLOAT3(+0.0f, +1.0f, +0.0f), XMFLOAT3(0,0,-1), XMFLOAT2(0,0) },
		{ XMFLOAT3(+1.5f, -1.0f, +0.0f), XMFLOAT3(0,0,-1), XMFLOAT2(0,0) },
		{ XMFLOAT3(-1.5f, -1.0f, +0.0f), XMFLOAT3(0,0,-1), XMFLOAT2(0,0) },
	};

	Vertex verticesTwo[] =
	{
		{ XMFLOAT3(+1.0f, +2.0f, +1.0f), XMFLOAT3(0,0,-1), XMFLOAT2(0,0) },
		{ XMFLOAT3(+2.5f, +0.0f, +1.0f), XMFLOAT3(0,0,-1), XMFLOAT2(0,0) },
		{ XMFLOAT3(-0.5f, +0.0f, +1.0f), XMFLOAT3(0,0,-1), XMFLOAT2(0,0) },
	};

	Vertex verticesThree[] =
	{
		{ XMFLOAT3(-1.0f, +0.0f, -1.0f), XMFLOAT3(0,0,-1), XMFLOAT2(0,0) },
		{ XMFLOAT3(+0.5f, -2.0f, -1.0f), XMFLOAT3(0,0,-1), XMFLOAT2(0,0) },
		{ XMFLOAT3(-2.5f, -2.0f, -1.0f), XMFLOAT3(0,0,-1), XMFLOAT2(0,0) },
	};

	// Set up the indices, which tell us which vertices to use and in which order
	// - This is somewhat redundant for just 3 vertices (it's a simple example)
	// - Indices are technically not required if the vertices are in the buffer 
	//    in the correct order and each one will be used exactly once
	// - But just to see how it's done...
	UINT indices[] = { 0, 1, 2 };

	MeshOne = new Mesh(device, "Assets/Models/helix.obj");
	MeshTwo = new Mesh(device, "Assets/Models/torus.obj");
	MeshThree = new Mesh(device, verticesThree, 3, indices, 3);

	material = new Material(vertexShader, pixelShader);

	// Create entities based on these Meshes
	entities.push_back(new Entity(MeshOne, material));
	++entityCount;
	entities.push_back(new Entity(MeshTwo, material));
	++entityCount;
	entities.push_back(new Entity(MeshThree, material));
	++entityCount;
	entities[entityCount - 1]->MoveAbsolute(-1.0f, -1.0f, 0.0f);

}


// --------------------------------------------------------
// Handle resizing DirectX "stuff" to match the new window size.
// For instance, updating our projection matrix's aspect ratio.
// --------------------------------------------------------
void Game::OnResize()
{
	// Handle base-level DX resize stuff
	DXCore::OnResize();

	camera->updateProjectionMatrix(width, height);
}

// --------------------------------------------------------
// Update your game here - user input, move objects, AI, etc.
// --------------------------------------------------------
void Game::Update(float deltaTime, float totalTime)
{
	// Quit if the escape key is pressed
	if (GetAsyncKeyState(VK_ESCAPE))
		Quit();

	camera->update(deltaTime);

	if (entityCount >= 0)
	{
		const float speed = 1.2f;
		float Sintime = (0.5f * sinf(0.5f * totalTime) + 0.8f);
		entities[0]->SetScale(Sintime, Sintime, Sintime);
		entities[0]->MoveAbsolute(
			speed * deltaTime,
			speed * deltaTime,
			speed * deltaTime
		);
	}

	for (size_t i = 0; i < entityCount; ++i)
	{
		XMFLOAT4 rotation = entities[i]->GetRotation();
		rotation.z = totalTime;
		//entities[i]->SetRotation(rotation);
	}
}

// --------------------------------------------------------
// Clear the screen, redraw everything, present to the user
// --------------------------------------------------------
void Game::Draw(float deltaTime, float totalTime)
{
	// Background color (Cornflower Blue in this case) for clearing
	const float color[4] = {0.4f, 0.6f, 0.75f, 0.0f};

	// Clear the render target and depth buffer (erases what's on the screen)
	//  - Do this ONCE PER FRAME
	//  - At the beginning of Draw (before drawing *anything*)
	context->ClearRenderTargetView(backBufferRTV, color);
	context->ClearDepthStencilView(
		depthStencilView, 
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		1.0f,
		0);

	// Set the vertex and pixel shaders to use for the next Draw() command
	//  - These don't technically need to be set every frame...YET
	//  - Once you start applying different shaders to different objects,
	//    you'll need to swap the current shaders before each draw
	//vertexShader->SetShader();
	//pixelShader->SetShader();

	// Set buffers in the input assembler
	//  - Do this ONCE PER OBJECT you're drawing, since each object might
	//    have different geometry.
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	
	const Mesh* entityMesh = nullptr;
	Entity* currentEntity = nullptr;
	ID3D11Buffer* meshVertexBuffer = nullptr;
	ID3D11Buffer* meshIndexBuffer = nullptr;
	// Draw Entities
	for (size_t i = 0; i < entityCount; ++i)
	{
		currentEntity = entities[i];
		// Set the pixel shader before we draw each entity
		pixelShader->SetData("green_light", &directional_light_two, sizeof(DirectionalLight));
		pixelShader->SetData("light", &directional_light, sizeof(DirectionalLight));
		currentEntity->prepareMaterial(camera->getViewMatrix(), camera->getProjectionMatrix());
		//vertexShader->SetMatrix4x4("world", currentEntity->GetWorldMatrix());
		//vertexShader->SetMatrix4x4("view", camera->getViewMatrix());
		//vertexShader->SetMatrix4x4("projection", camera->getProjectionMatrix());

		entityMesh = currentEntity->GetEntityMesh();
		meshVertexBuffer = entityMesh->GetVertexBuffer();
		meshIndexBuffer = entityMesh->GetIndexBuffer();

		context->IASetVertexBuffers(0, 1, &meshVertexBuffer, &stride, &offset);
		context->IASetIndexBuffer(meshIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

		// Finally do the actual drawing
		//  - Do this ONCE PER OBJECT you intend to draw
		//  - This will use all of the currently set DirectX "stuff" (shaders, buffers, etc)
		//  - DrawIndexed() uses the currently set INDEX BUFFER to look up corresponding
		//     vertices in the currently set VERTEX BUFFER
		context->DrawIndexed(
			entityMesh->GetIndexCount(),     // The number of indices to use (we could draw a subset if we wanted)
			0,     // Offset to the first index we want to use
			0);    // Offset to add to each index when looking up vertices

		//vertexShader->CopyAllBufferData();

		// Present the back buffer to the user
		//  - Puts the final frame we're drawing into the window so the user can see it
		//  - Do this exactly ONCE PER FRAME (always at the very end of the frame)
		swapChain->Present(0, 0);

	}
}


#pragma region Mouse Input

// --------------------------------------------------------
// Helper method for mouse clicking.  We get this information
// from the OS-level messages anyway, so these helpers have
// been created to provide basic mouse input if you want it.
// --------------------------------------------------------
void Game::OnMouseDown(WPARAM buttonState, int x, int y)
{
	// Add any custom code here...

	// Save the previous mouse position, so we have it for the future
	prevMousePos.x = x;
	prevMousePos.y = y;

	// Caputure the mouse so we keep getting mouse move
	// events even if the mouse leaves the window.  we'll be
	// releasing the capture once a mouse button is released
	SetCapture(hWnd);
}

// --------------------------------------------------------
// Helper method for mouse release
// --------------------------------------------------------
void Game::OnMouseUp(WPARAM buttonState, int x, int y)
{
	// Add any custom code here...

	// We don't care about the tracking the cursor outside
	// the window anymore (we're not dragging if the mouse is up)
	ReleaseCapture();
}

// --------------------------------------------------------
// Helper method for mouse movement.  We only get this message
// if the mouse is currently over the window, or if we're 
// currently capturing the mouse.
// --------------------------------------------------------
void Game::OnMouseMove(WPARAM buttonState, int x, int y)
{
	// Add any custom code here...
	camera->updateMouseInput(prevMousePos.x - x, prevMousePos.y - y);
	// Save the previous mouse position, so we have it for the future
	prevMousePos.x = x;
	prevMousePos.y = y;
}

// --------------------------------------------------------
// Helper method for mouse wheel scrolling.  
// WheelDelta may be positive or negative, depending 
// on the direction of the scroll
// --------------------------------------------------------
void Game::OnMouseWheel(float wheelDelta, int x, int y)
{
	// Add any custom code here...
}
#pragma endregion