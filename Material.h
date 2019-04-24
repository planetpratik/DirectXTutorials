#pragma once

// Forward Declarations
class SimpleVertexShader;
class SimplePixelShader;
struct ID3D11ShaderResourceView;
struct ID3D11SamplerState;

class Material
{
public:

	// Parameterised Constructor for Material
	Material(SimpleVertexShader* t_vertex_shader, SimplePixelShader* t_pixel_shader, ID3D11ShaderResourceView* t_diffused_srv, ID3D11ShaderResourceView* t_normal_srv, ID3D11SamplerState* t_sampler);

	// Destructor for Material
	~Material();

	// Get Vertex Shader of the Material
	SimpleVertexShader* getVertexShader() const;

	// Get Pixel Shader of the Material
	SimplePixelShader* getPixelShader() const;

	// Get this material's diffused texture SRV
	ID3D11ShaderResourceView* getdiffusedSRV() const;

	// Get this material's normal map SRV
	ID3D11ShaderResourceView* getNormalSRV() const;

	// Get Pixel Shader of the Material
	ID3D11SamplerState* getSamplerState() const;

private:
	SimpleVertexShader* vertexShader = nullptr;
	SimplePixelShader* pixelShader = nullptr;
	ID3D11ShaderResourceView* diffused_srv = nullptr;
	ID3D11ShaderResourceView* normal_srv = nullptr;
	ID3D11SamplerState* sampler = nullptr;

};