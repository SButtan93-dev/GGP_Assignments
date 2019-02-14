#pragma once

#include "DXCore.h"
#include "SimpleShader.h"
#include <DirectXMath.h>
#include "Mesh.h"
#include "Material.h"
using namespace DirectX;

class GameEntity
{
public:
	GameEntity();
	~GameEntity();


	
	//Pass world, view and projection matrix as 1st 3 arguments. 4th parameter is referenced object that calls material class vertex and pixel shader functions. All are called from game.cpp 
	void PrepareMaterial(XMFLOAT4X4 worldMatrix, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, Material* &mynewobj);
	

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

