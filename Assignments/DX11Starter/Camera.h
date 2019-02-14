#pragma once
#include <DirectXMath.h>

using namespace DirectX;
class Camera
{
public:
	Camera();

	~Camera();





	XMVECTOR MoveForward();

	XMVECTOR MoveBackward();

	XMVECTOR MoveRight();

	XMVECTOR MoveLeft();

	//biond by spacebar
	XMVECTOR MoveUp();
	//bind by x
	XMVECTOR MoveDown();
	XMFLOAT4X4* GetProjectionMatrix();
	//Return view matrix in update of game.cpp and before draw()
	XMFLOAT4X4* Update(float deltaTime, float totalTime);
	XMFLOAT4X4 viewMatrix;
	void SetProjectionMatrix(int width, int height);

	void SetMyRotation(float x, float y);

private:


	XMVECTOR ReturnMyPos();

	XMVECTOR ReturnMyDir();


	XMFLOAT4X4 projectionMatrix;

	

	XMVECTOR pos;
		XMVECTOR dir;
		XMVECTOR up;
		XMMATRIX V;

	
};


