#include "Camera.h"
#include "Windows.h"


Camera::Camera()
{
	pos = XMVectorSet(0, 0, -10, 0);

	XMVECTOR My = XMQuaternionRotationRollPitchYaw(0, 0, 1);
		dir = My;

	
	up = XMVectorSet(0, 1, 0, 0);
}

XMVECTOR Camera::ReturnMyPos()
{
	return pos;
}
XMVECTOR Camera::ReturnMyDir()
{
	return dir;
}


//Used with mouse input from game.cpp
void Camera::SetMyRotation(float x, float y)
{

	//rotate up and down.
	if (y == 0)
	{
		XMVECTOR rotquat = XMQuaternionRotationRollPitchYaw(x, 0, 0);
		this->dir = XMVector3Rotate(ReturnMyDir(), rotquat);
		this->dir = XMVector3Normalize(this->dir);

	}
	//rotate left and right
	else if (x == 0)
	{
		XMVECTOR rotquat = XMQuaternionRotationRollPitchYaw(0, y, 0);
		this->dir = XMVector3Rotate(ReturnMyDir(), rotquat);
		this->dir = XMVector3Normalize(this->dir);
		
	}
		
}

//Binded with 'W' key
XMVECTOR Camera::MoveForward()
{
	
	XMVECTOR MyTempDir = ReturnMyDir();
	XMVECTOR MyTempPos = ReturnMyPos();
	XMVECTOR local = XMVectorSet(0, 0, 0.001f, 0);
	//dir = MyTempDir;
	MyTempDir = XMVector3Normalize(MyTempDir);
	pos = MyTempPos+MyTempDir/200;
	
	return pos;

}

//Set projection matrix. based on resize
void Camera::SetProjectionMatrix(int width, int height)
{
	// Create the Projection matrix
// - This should match the window's aspect ratio, and also update anytime
//    the window resizes (which is already happening in OnResize() below)
	XMMATRIX P = XMMatrixPerspectiveFovLH(
		0.25f * 3.1415926535f,		// Field of View Angle
		(float)width / height,		// Aspect ratio
		0.1f,						// Near clip plane distance
		100.0f);					// Far clip plane distance
	XMStoreFloat4x4(&projectionMatrix, XMMatrixTranspose(P)); // Transpose for HLSL!
}

// return projection matrix in draw, game.cpp
XMFLOAT4X4 * Camera::GetProjectionMatrix()
{
	return &projectionMatrix;
}

//Bind with 'S' key
XMVECTOR Camera::MoveBackward()
{
	//dir=XMVector2Cross(dir, up);
	//dir = dir * up;
	XMVECTOR MyTempDir = ReturnMyDir();
	XMVECTOR MyTempPos = ReturnMyPos();
	XMVECTOR local = XMVectorSet(0, 0, 0.001f, 0);
	//dir = MyTempDir;
	MyTempDir = XMVector3Normalize(MyTempDir);
	pos = MyTempPos - MyTempDir/200;

	return pos;

}

//Bind with 'D' key
XMVECTOR Camera::MoveRight()
{

	XMVECTOR MyTempDir = ReturnMyDir();
	XMVECTOR MyTempPos = ReturnMyPos();
	XMVECTOR local = XMVectorSet(0.001f, 0, 0, 0);
	//dir = MyTempDir;
	pos = MyTempPos-local;

	return pos;

}

// Bind with 'A' key
XMVECTOR Camera::MoveLeft()
{
	XMVECTOR MyTempDir = ReturnMyDir();
	XMVECTOR MyTempPos = ReturnMyPos();
	XMVECTOR local = XMVectorSet(-0.001f, 0, 0, 0);
	//dir = MyTempDir;
	pos = MyTempPos - local;

	return pos;

}

XMVECTOR Camera::MoveUp()
{
	XMVECTOR MyTempDir = ReturnMyDir();
	XMVECTOR MyTempPos = ReturnMyPos();
	XMVECTOR local = XMVectorSet(0,-0.001f, 0, 0);
	//dir = MyTempDir;
	pos = MyTempPos - local;

	return pos;

}
XMVECTOR Camera::MoveDown()
{
	XMVECTOR MyTempDir = ReturnMyDir();
	XMVECTOR MyTempPos = ReturnMyPos();
	XMVECTOR local = XMVectorSet(0,-0.001f, 0, 0);
	//dir = MyTempDir;
	pos = MyTempPos + local;

	return pos;

}
//Return view matrix in update of game.cpp and before draw()
XMFLOAT4X4* Camera::Update(float deltaTime, float totalTime)
{

	if (GetAsyncKeyState('W') & 0x8000 ) 
	{ 
	
		pos = MoveForward();

	}
	else if(GetAsyncKeyState('S') & 0x8000)
	{
		pos = MoveBackward();
		
	}
	else if (GetAsyncKeyState('A') & 0x8000)
	{
		pos = MoveRight();

		
	}
	else if (GetAsyncKeyState('D') & 0x8000)
	{
		pos=MoveLeft();

		
	}
	else if (GetAsyncKeyState(VK_SPACE) & 0x80000000)
	{
		pos = MoveUp();
	}
	else if (GetAsyncKeyState('X') & 0x8000)
	{
		pos = MoveDown();
	}
	// Create the View matrix
// - In an actual game, recreate this matrix every time the camera 
//    moves (potentially every frame)
// - We're using the LOOK TO function, which takes the position of the
//    camera and the direction vector along which to look (as well as "up")
// - Another option is the LOOK AT function, to look towards a specific
//    point in 3D space
	
	V = XMMatrixLookToLH(
		pos,     // The position of the "camera"
		dir,     // Direction the camera is looking
		up);     // "Up" direction in 3D space (prevents roll)
 XMStoreFloat4x4(&viewMatrix, XMMatrixTranspose(V)); // Transpose for HLSL!

 return &viewMatrix;
}



Camera::~Camera()
{
}



