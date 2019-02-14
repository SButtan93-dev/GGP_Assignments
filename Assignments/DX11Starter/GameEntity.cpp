#include "GameEntity.h"


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

