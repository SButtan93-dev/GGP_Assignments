#include "Mesh.h"
#include "Vertex.h"

// For the DirectX Math library
using namespace DirectX;

D3D11_BUFFER_DESC vbd;
D3D11_BUFFER_DESC ibd;
D3D11_SUBRESOURCE_DATA initialVertexData;
D3D11_SUBRESOURCE_DATA initialIndexData;
Mesh::Mesh()
{
	vertexBuffer = 0;
	indexBuffer = 0;
//
	// Set up the indices, which tell us which vertices to use and in which order
	// - This is somewhat redundant for just 3 vertices (it's a simple example)
	// - Indices are technically not required if the vertices are in the buffer 
	//    in the correct order and each one will be used exactly once
	// - But just to see how it's done...
	


}


Mesh::~Mesh()
{
	if (vertexBuffer) { vertexBuffer->Release(); }
	if (indexBuffer) { indexBuffer->Release(); }

}




D3D11_BUFFER_DESC* Mesh::GetIndexData(int count)
{
	
	// Create the INDEX BUFFER description ------------------------------------
	// - The description is created on the stack because we only need
	//    it to create the buffer.  The description is then useless.
	
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(int) * count;         // 3 = number of indices in the buffer
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER; // Tells DirectX this is an index buffer
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;


	return &ibd;
	
	
}


int Mesh::GetVertexData(int count)
{

	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(Vertex) * count;       // 3 = number of vertices in the buffer
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER; // Tells DirectX this is a vertex buffer
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;


	return 0;


}

int Mesh::GetResourceVertexData(Vertex vertices[])
{

	initialVertexData.pSysMem = vertices;
	return 0;
}
int Mesh::GetResourceIndexData(int indices[])
{

	initialIndexData.pSysMem = indices;
	return 0;
}

int Mesh::CallDrawMethodFunction(ID3D11DeviceContext* &context)
{
	// Set buffers in the input assembler
//  - Do this ONCE PER OBJECT you're drawing, since each object might
//    have different geometry.
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	return 0;
}

int Mesh::DeviceCallForVertex(ID3D11Device *& device)
{

	device->CreateBuffer(&vbd, &initialVertexData, &vertexBuffer);
	return 0;
}

int Mesh::DeviceCallForIndex(ID3D11Device* &device)
{
	device->CreateBuffer(&ibd, &initialIndexData, &indexBuffer);
	return 0;
}

int Mesh::CallMyDrawFunc(ID3D11DeviceContext* &context,int count)
{

	// Finally do the actual drawing
	//  - Do this ONCE PER OBJECT you intend to draw
	//  - This will use all of the currently set DirectX "stuff" (shaders, buffers, etc)
	//  - DrawIndexed() uses the currently set INDEX BUFFER to look up corresponding
	//     vertices in the currently set VERTEX BUFFER
	context->DrawIndexed(
		count,     // The number of indices to use (we could draw a subset if we wanted)
		0,     // Offset to the first index we want to use
		0);    // Offset to add to each index when looking up vertices


	return 0;
}


