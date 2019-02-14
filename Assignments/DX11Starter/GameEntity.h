#pragma once

#include "DXCore.h"
#include "SimpleShader.h"
#include <DirectXMath.h>
#include "Mesh.h"
using namespace DirectX;

class GameEntity
{
public:
	GameEntity();
	~GameEntity();


	


	

	//return XMMATRIX to update in game class. Order is S-R-T.
	XMMATRIX GetWorldMatrix();
	//Translation of 3 floats x,y,z
	XMFLOAT3 trans;
	//to get rotation and scale
	float rotation, scale1;

	//translation from update
	float SetMyTrans(float x,float y, float z);
	//rotation from update
	float SetMyRot(float totalTime);
	//scale from update
	float SetMyScale(float sinTime);

};

