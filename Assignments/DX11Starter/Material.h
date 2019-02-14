#pragma once
#include "DXCore.h"
#include "SimpleShader.h"
class Material
{
public:
	Material();

	// Wrappers for DirectX shaders to provide simplified functionality
	SimpleVertexShader* vertexShader;
	SimplePixelShader* pixelShader;
	
	~Material();
	void LoadShaders(ID3D11Device *& device, ID3D11DeviceContext *& context);
	
};

