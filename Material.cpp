#include "Material.h"
#include "SimpleShader.h"

Material::Material(SimpleVertexShader* t_vertex_shader, SimplePixelShader* t_pixel_shader) :
	vertexShader(t_vertex_shader), pixelShader(t_pixel_shader)
{
}

Material::~Material()
{
	vertexShader = nullptr;
	pixelShader = nullptr;
}

SimpleVertexShader* Material::getVertexShader() const
{
	return vertexShader;
}

SimplePixelShader* Material::getPixelShader() const
{
	return pixelShader;
}
