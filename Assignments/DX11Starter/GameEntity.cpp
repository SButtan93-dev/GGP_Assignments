#include "GameEntity.h"
#include "Material.h"

//constructor
GameEntity::GameEntity()
{
	trans.x = 1.f;
	trans.y = 0.f;
	trans.z = 0.f;

	rotation = 0.3f;
	
	scale1 = 0.8f;

}

//Destructor
GameEntity::~GameEntity()
{

	
	
}

//Pass world, view and projection matrix as 1st 3 arguments. 4th parameter is referenced object that calls material class vertex and pixel shader functions. All are called from game.cpp 
void GameEntity::PrepareMaterial(XMFLOAT4X4 worldMatrix, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, Material* &mynewobj)
{
	mynewobj->vertexShader->SetMatrix4x4("world", worldMatrix);
	mynewobj->vertexShader->SetMatrix4x4("view", viewMatrix);
	mynewobj->vertexShader->SetMatrix4x4("projection", projectionMatrix);
	// Once you've set all of the data you care to change for
	// the next draw call, you need to actually send it to the GPU
	//  - If you skip this, the "SetMatrix" calls above won't make it to the GPU!
	mynewobj->vertexShader->CopyAllBufferData();

	// Set the vertex and pixel shaders to use for the next Draw() command
	//  - These don't technically need to be set every frame...YET
	//  - Once you start applying different shaders to different objects,
	//    you'll need to swap the current shaders before each draw
	mynewobj->vertexShader->SetShader();
	mynewobj->pixelShader->SetShader();

}





//return XMMATRIX to update in game class. Order is S-R-T.
DirectX::XMMATRIX GameEntity::GetWorldMatrix()
{
	XMMATRIX trans = XMMatrixTranslation(2, 0, 0);
	XMMATRIX rot = XMMatrixRotationZ(rotation);
	XMMATRIX scale = XMMatrixScaling(scale1,scale1,scale1);

	return (scale*rot*trans);
}

//Translation vector
float GameEntity::SetMyTrans(float x, float y, float z)
{
	trans.x = x;
	trans.y = y;
	trans.z = z;

	return 0.0f;
}

//Rotation 
float GameEntity::SetMyRot(float totalTime)
{
	rotation = totalTime;

	return 0.0f;
}

//Scale
float GameEntity::SetMyScale(float sinTime)
{
	scale1 = sinTime;

	return 0.0f;
}

