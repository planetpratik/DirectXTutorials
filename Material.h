#pragma once

// Forward Declarations
class SimpleVertexShader;
class SimplePixelShader;

class Material
{
public:

	// Parameterised Constructor for Material
	Material(SimpleVertexShader* t_vertex_shader, SimplePixelShader* t_pixel_shader);

	// Destructor for Material
	~Material();

	// Get Vertex Shader of the Material
	SimpleVertexShader* getVertexShader() const;

	// Get Pixel Shader of the Material
	SimplePixelShader* getPixelShader() const;

private:
	SimpleVertexShader* vertexShader = nullptr;
	SimplePixelShader* pixelShader = nullptr;

};