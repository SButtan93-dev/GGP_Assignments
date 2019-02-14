#include "Game.h"
#include "Vertex.h"
#include "GameEntity.h"
// For the DirectX Math library
using namespace DirectX;

// --------------------------------------------------------
// Constructor
//
// DXCore (base class) constructor will set up underlying fields.
// DirectX itself, and our window, are not ready yet!
//
// hInstance - the application's OS-level handle (unique ID)
// --------------------------------------------------------
Game::Game(HINSTANCE hInstance)
	: DXCore(
		hInstance,		// The application's handle
		"DirectX Game",	   	// Text for the window's title bar
		1280,			// Width of the window's client area
		720,			// Height of the window's client area
		true)			// Show extra stats (fps) in title bar?
{

	

#if defined(DEBUG) || defined(_DEBUG)
	// Do we want a console window?  Probably only in debug mode
	CreateConsoleWindow(500, 120, 32, 120);
	printf("Console window created successfully.  Feel free to printf() here.\n");
#endif
	
}

// --------------------------------------------------------
// Destructor - Clean up anything our game has created:
//  - Release all DirectX objects created here
//  - Delete any objects to prevent memory leaks
// --------------------------------------------------------
Game::~Game()
{

	
	// Delete our simple shader objects, which
	// will clean up their own internal DirectX stuff

	delete MyGameEntity1;
	delete MyGameEntity2;
	delete MyGameEntity3;
	delete MyGameEntity4;
	delete MyGameEntity5;
	delete MyMesh1;
	delete MyMesh2;
	delete MyMesh3;
	delete MyCamera;
	delete MyMaterial;

}

// --------------------------------------------------------
// Called once per program, after DirectX and the window
// are initialized but before the game loop.
// --------------------------------------------------------
void Game::Init()
{
	// Helper methods for loading shaders, creating some basic
	// geometry to draw and some simple camera matrices.
	//  - You'll be expanding and/or replacing these later
	MyMaterial->LoadShaders(device, context);
	CreateMatrices();
	//MyMesh1->GetVertexData();
	CreateBasicGeometry();
	//MyMesh1->CreateBasicGeometry1();
	// Tell the input assembler stage of the pipeline what kind of
	// geometric primitives (points, lines or triangles) we want to draw.  
	// Essentially: "What kind of shape should the GPU draw with our data?"
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}





// --------------------------------------------------------
// Initializes the matrices necessary to represent our geometry's 
// transformations and our 3D camera
// --------------------------------------------------------
void Game::CreateMatrices()
{
	// Set up world matrix
	// - In an actual game, each object will need one of these and they should
	//    update when/if the object moves (every frame)
	// - You'll notice a "transpose" happening below, which is redundant for
	//    an identity matrix.  This is just to show that HLSL expects a different
	//    matrix (column major vs row major) than the DirectX Math library
	MyGameEntity1->GetWorldMatrix();
	XMMATRIX W = XMMatrixIdentity();
	XMStoreFloat4x4(&worldMatrix, XMMatrixTranspose(W)); // Transpose for HLSL!


	//call and set my projection matrix
	MyCamera->SetProjectionMatrix(width, height);

}


// --------------------------------------------------------
// Creates the geometry we're going to draw - a single triangle for now
// --------------------------------------------------------
void Game::CreateBasicGeometry()
{
	XMFLOAT4 red = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	XMFLOAT4 green = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	XMFLOAT4 blue = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);

	Vertex vertices1[] = {
	{ XMFLOAT3(1.0f,1.0f , +0.0f), red },
	{ XMFLOAT3(1.5f,1.0f , +0.0f), blue },

	{ XMFLOAT3(1.5f,0.5f , +0.0f), red },

	{ XMFLOAT3(1.5f,0.0f , +0.0f), blue },
	{ XMFLOAT3(1.0f,0.0f , +0.0f), green },
	{ XMFLOAT3(0.5f,0.5f , +0.0f), green },
	};

	
	Vertex vertices2[] =
	{
		{ XMFLOAT3(-.25f, +.25f, +0.0f), red },
		{ XMFLOAT3(+0.25f, -0.25f, +0.0f), blue },
		{ XMFLOAT3(-0.25f, -0.25f, +0.0f), green },
		{ XMFLOAT3(+0.25f, +0.25f, +0.0f), red },

	};
	Vertex vertices3[] =
	{
	{ XMFLOAT3(-1.5f, 1.5f, +0.0f), red },
	{ XMFLOAT3(-1.5f, 0.0f, +0.0f), blue },
	{ XMFLOAT3(-2.5f, 0.0f, +0.0f), green },
	};


	int indices[] = { 0, 1, 2, 0, 3, 2 };
	


	//Mesh 1

	MyMesh1->GetVertexData(sizeof(vertices2));

	MyMesh1->GetResourceVertexData(vertices2);

	MyMesh1->DeviceCallForVertex(device);



	MyMesh1->GetIndexData(sizeof(indices));

	MyMesh1->GetResourceIndexData(indices);

	MyMesh1->DeviceCallForIndex(device);





	

	//Mesh 2
	MyMesh2->GetVertexData(sizeof(vertices1));

	MyMesh2->GetResourceVertexData(vertices1);

	MyMesh2->DeviceCallForVertex(device);

	int indices1[] = { 0,1,3,1,2,3,0,3,4,0,4,5 };
	MyMesh2->GetIndexData(sizeof(indices1));

	MyMesh2->GetResourceIndexData(indices1);

	MyMesh2->DeviceCallForIndex(device);

	//Mesh 3
	MyMesh3->GetVertexData(sizeof(vertices3));
		  
	MyMesh3->GetResourceVertexData(vertices3);
		  
	MyMesh3->DeviceCallForVertex(device);


	int indices3[] = { 0, 1, 2 };
	MyMesh3->GetIndexData(sizeof(indices3));

	MyMesh3->GetResourceIndexData(indices3);

	MyMesh3->DeviceCallForIndex(device);

	

}


// --------------------------------------------------------
// Handle resizing DirectX "stuff" to match the new window size.
// For instance, updating our projection matrix's aspect ratio.
// --------------------------------------------------------
void Game::OnResize()
{
	// Handle base-level DX resize stuff
	DXCore::OnResize();

	// Update our projection matrix since the window size changed
	XMMATRIX P = XMMatrixPerspectiveFovLH(
		0.25f * 3.1415926535f,	// Field of View Angle
		(float)width / height,	// Aspect ratio
		0.1f,				  	// Near clip plane distance
		100.0f);			  	// Far clip plane distance
	XMStoreFloat4x4(MyCamera->GetProjectionMatrix(), XMMatrixTranspose(P)); // Transpose for HLSL!
}

// --------------------------------------------------------
// Update your game here - user input, move objects, AI, etc.
// --------------------------------------------------------
void Game::Update(float deltaTime, float totalTime)
{
	// Quit if the escape key is pressed
	if (GetAsyncKeyState(VK_ESCAPE))
		Quit();
	


	// Make a value that goes up and down
	float sinTime = (sin(totalTime * 10) + 2.0f) / 10.0f;
	float cosTime = (cos(totalTime * 10) + 2.0f) / 10.0f;

	//for entity 1
	MyGameEntity1->SetMyTrans(1.f, 0.f, 0.f);
	MyGameEntity1->SetMyRot(totalTime);
	MyGameEntity1->SetMyScale(sinTime);

	//for entity 2
	MyGameEntity2->SetMyTrans(1.f, 0.f, 0.f);
	MyGameEntity2->SetMyRot(1-totalTime);
	MyGameEntity2->SetMyScale(0.7f);

	//for entity 3
	float MyLocalCountForScale=totalTime / 10;

	if (MyLocalCountForScale < 0.5f)
	{
		MyGameEntity3->SetMyTrans(1.f, 0.f, 0.f);
		MyGameEntity3->SetMyRot((1 - totalTime) * 10);
		MyGameEntity3->SetMyScale(MyLocalCountForScale);
	}
	else
	{
		MyGameEntity3->SetMyTrans(1.f, 0.f, 0.f);
		MyGameEntity3->SetMyRot((1 - totalTime) * 10);
		MyGameEntity3->SetMyScale(0.5f);
	}
	//for entity 4
	MyGameEntity4->SetMyTrans(1.f, 0.f, 0.f);
	MyGameEntity4->SetMyRot(totalTime);
	MyGameEntity4->SetMyScale(sinTime*2);

	//for entity 5
	MyGameEntity5->SetMyTrans(1.f, 0.f, 0.f);
	MyGameEntity5->SetMyRot(totalTime);
	MyGameEntity5->SetMyScale(0.8f);
	
	//get viewmatrix from camera class
	*&viewMatrix1 = MyCamera->Update(deltaTime,totalTime);
	viewMatrix = *viewMatrix1;

}

// --------------------------------------------------------
// Clear the screen, redraw everything, present to the user
// --------------------------------------------------------
void Game::Draw(float deltaTime, float totalTime)
{
	// Background color (Cornflower Blue in this case) for clearing
	const float color[4] = { 0.4f, 0.6f, 0.75f, 0.0f };

	// Clear the render target and depth buffer (erases what's on the screen)
	//  - Do this ONCE PER FRAME
	//  - At the beginning of Draw (before drawing *anything*)
	context->ClearRenderTargetView(backBufferRTV, color);
	context->ClearDepthStencilView(
		depthStencilView,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		1.0f,
		0);

	//Get Projection matrix from camera for all shader calls
	*&projectionMatrix = MyCamera->GetProjectionMatrix();
	
	
	//Set world matrix for Mesh 1, game entity 1

	XMStoreFloat4x4(&worldMatrix, XMMatrixTranspose(MyGameEntity1->GetWorldMatrix()));
	
	//set shaders
	MyGameEntity1->PrepareMaterial(worldMatrix, viewMatrix, *projectionMatrix, MyMaterial);


	


	//call draw functions for mesh 1

	MyMesh1->CallDrawMethodFunction(context);

	MyMesh1->CallMyDrawFunc(context,6);




	//Set world matrix for Mesh 2, game entity 2
	XMStoreFloat4x4(&worldMatrix, XMMatrixTranspose(MyGameEntity2->GetWorldMatrix()));
	//set shaders
	MyGameEntity2->PrepareMaterial(worldMatrix, viewMatrix, *projectionMatrix, MyMaterial);

	
	//call draw functions for mesh 2
	MyMesh2->CallDrawMethodFunction(context);

	MyMesh2->CallMyDrawFunc(context,12);

	//Set world matrix for Mesh 3, game entity 3

	XMStoreFloat4x4(&worldMatrix, XMMatrixTranspose(MyGameEntity3->GetWorldMatrix()));
	//set shaders
	MyGameEntity3->PrepareMaterial(worldMatrix, viewMatrix, *projectionMatrix, MyMaterial);


	//call draw functions for mesh 3
	MyMesh3->CallDrawMethodFunction(context);

	MyMesh3->CallMyDrawFunc(context, 3);

	//Set world matrix for Mesh 3, game entity 4
	XMStoreFloat4x4(&worldMatrix, XMMatrixTranspose(MyGameEntity4->GetWorldMatrix()));
	//set shaders
	MyGameEntity4->PrepareMaterial(worldMatrix, viewMatrix, *projectionMatrix, MyMaterial);

	//call draw functions for mesh 3
	MyMesh3->CallDrawMethodFunction(context);

	MyMesh3->CallMyDrawFunc(context, 3);



	//Set world matrix for Mesh 2, game entity 5
	XMStoreFloat4x4(&worldMatrix, XMMatrixTranspose(MyGameEntity5->GetWorldMatrix()));
	//set shaders
	MyGameEntity5->PrepareMaterial(worldMatrix, viewMatrix, *projectionMatrix, MyMaterial);



	//call draw functions for mesh 2
	MyMesh2->CallDrawMethodFunction(context);

	MyMesh2->CallMyDrawFunc(context, 12);
	// Present the back buffer to the user
	//  - Puts the final frame we're drawing into the window so the user can see it
	//  - Do this exactly ONCE PER FRAME (always at the very end of the frame)
	//swapChain->Present(0, 0);

	// Present the back buffer to the user
//  - Puts the final frame we're drawing into the window so the user can see it
//  - Do this exactly ONCE PER FRAME (always at the very end of the frame)
	swapChain->Present(0, 0);

}


#pragma region Mouse Input

// --------------------------------------------------------
// Helper method for mouse clicking.  We get this information
// from the OS-level messages anyway, so these helpers have
// been created to provide basic mouse input if you want it.
// --------------------------------------------------------
void Game::OnMouseDown(WPARAM buttonState, int x, int y)
{
	// Add any custom code here...
	
	// Save the previous mouse position, so we have it for the future
	prevMousePos.x = x;
	prevMousePos.y = y;

	


	// Caputure the mouse so we keep getting mouse move
	// events even if the mouse leaves the window.  we'll be
	// releasing the capture once a mouse button is released
	SetCapture(hWnd);
}

// --------------------------------------------------------
// Helper method for mouse release
// --------------------------------------------------------
void Game::OnMouseUp(WPARAM buttonState, int x, int y)
{
	// Add any custom code here...

	// We don't care about the tracking the cursor outside
	// the window anymore (we're not dragging if the mouse is up)
	ReleaseCapture();
}

// --------------------------------------------------------
// Helper method for mouse movement.  We only get this message
// if the mouse is currently over the window, or if we're 
// currently capturing the mouse.
// --------------------------------------------------------
void Game::OnMouseMove(WPARAM buttonState, int x, int y)
{
	// Add any custom code here...
	if (y > prevMousePos.y && (buttonState & 0x0001))
	{
		MyCamera->SetMyRotation((float)x*-0.00001f, 0);
	}
	else if (y < prevMousePos.y && (buttonState & 0x0001))
	{
		MyCamera->SetMyRotation((float)x*0.00001f, 0);
	}
	else if (x > prevMousePos.x && (buttonState & 0x0002))
	{
		MyCamera->SetMyRotation(0, (float)y*0.00001f);
	}
	else if (x < prevMousePos.x && (buttonState & 0x0002))
	{
		MyCamera->SetMyRotation(0, (float)y*-0.00001f);
	}
	// Save the previous mouse position, so we have it for the future
	prevMousePos.x = x;
	prevMousePos.y = y;
}

// --------------------------------------------------------
// Helper method for mouse wheel scrolling.  
// WheelDelta may be positive or negative, depending 
// on the direction of the scroll
// --------------------------------------------------------
void Game::OnMouseWheel(float wheelDelta, int x, int y)
{
	// Add any custom code here...
}
#pragma endregion