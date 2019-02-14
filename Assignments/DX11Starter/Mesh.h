#pragma once
#include "DXCore.h"
#include "SimpleShader.h"
#include <DirectXMath.h>
#include "Vertex.h"
class Mesh

{
public:
	Mesh();
	~Mesh();


	
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;




	D3D11_BUFFER_DESC * GetIndexData(int count);

	// create vertex buffer
	int GetVertexData(int count);

	//set subresource data
	int GetResourceVertexData(Vertex vertices[]);

	// set index buffer
	int GetResourceIndexData(int indices[]);

// call draw function for IA
	int CallDrawMethodFunction(ID3D11DeviceContext* &context);

	//call draw methods from context
	int DeviceCallForVertex(ID3D11Device* &device);
	int DeviceCallForIndex(ID3D11Device* &device);
	
	
	int CallMyDrawFunc(ID3D11DeviceContext* &context, int count);
	// Buffers to hold actual geometry data

	//get vertexbuffer and indexbuffer
	ID3D11Buffer* GetVertexBuffer() { return vertexBuffer; }
	ID3D11Buffer* GetIndexBuffer() { return indexBuffer; }
	
	


};

