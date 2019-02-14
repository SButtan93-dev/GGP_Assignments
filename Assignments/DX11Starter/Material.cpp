#include "Material.h"
#include "Vertex.h"
using namespace DirectX;

Material::Material()
{
	vertexShader = 0;
	pixelShader = 0;

}


Material::~Material()
{
	delete vertexShader;
	delete pixelShader;
}
// --------------------------------------------------------
// Loads shaders from compiled shader object (.cso) files using
// my SimpleShader wrapper for DirectX shader manipulation.
// - SimpleShader provides helpful methods for sending
//   data to individual variables on the GPU
// --------------------------------------------------------
void Material::LoadShaders(ID3D11Device* & device, ID3D11DeviceContext* &context)
{
	vertexShader = new SimpleVertexShader(device, context);
	vertexShader->LoadShaderFile(L"VertexShader.cso");

	pixelShader = new SimplePixelShader(device, context);
	pixelShader->LoadShaderFile(L"PixelShader.cso");
}