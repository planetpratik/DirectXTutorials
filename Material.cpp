#include "Material.h"
#include "SimpleShader.h"

Material::Material(SimpleVertexShader* t_vertex_shader, SimplePixelShader* t_pixel_shader, ID3D11ShaderResourceView* t_diffused_srv, ID3D11ShaderResourceView* t_normal_srv, ID3D11SamplerState* t_sampler) :
	vertexShader(t_vertex_shader), pixelShader(t_pixel_shader), diffused_srv(t_diffused_srv), normal_srv(t_normal_srv), sampler(t_sampler)
{
}

Material::~Material()
{
	vertexShader = nullptr;
	pixelShader = nullptr;
	diffused_srv = nullptr;
	normal_srv = nullptr;
	sampler = nullptr;
}

SimpleVertexShader* Material::getVertexShader() const
{
	return vertexShader;
}

SimplePixelShader* Material::getPixelShader() const
{
	return pixelShader;
}

ID3D11ShaderResourceView* Material::getdiffusedSRV() const
{
	return diffused_srv;
}

ID3D11ShaderResourceView* Material::getNormalSRV() const
{
	return normal_srv;
}



ID3D11SamplerState* Material::getSamplerState() const
{
	return sampler;
}
