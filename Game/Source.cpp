//	Ask the compiler to include minimal header files for our program.
#define WIN32_LEAN_AND_MEAN
#define _USE_MATH_DEFINES 

#include <cmath>
#include <Windows.h>
#include <Windowsx.h>
#include <iostream>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include "FrameTimer.h"
#include "player.h"
#include "ball.h"


#define WINDOW_CLASS_NAME "Ping Pang"
#define WINDOWWIDTH 800
#define WINDOWHEIGHT 600

using namespace std;

HWND g_hWnd = NULL;
WNDCLASS wndClass;

int red, green, blue;


HRESULT hr = NULL;
IDirect3DDevice9* d3dDevice;


LPD3DXSPRITE sprite = NULL;

boolean gameStart = false;

player player1;
player player2;
ball ball1;

LPD3DXLINE line = NULL;
D3DXVECTOR2 lineVertices[] = { D3DXVECTOR2((WINDOWWIDTH / 2) - 1,0), D3DXVECTOR2(WINDOWWIDTH / 2 - 1, WINDOWHEIGHT) };
D3DXVECTOR2 lineVertices2[] = { D3DXVECTOR2((WINDOWWIDTH / 2) + 1,0), D3DXVECTOR2(WINDOWWIDTH / 2 + 1, WINDOWHEIGHT) };

//inputs
LPDIRECTINPUT8 dInput; //	Direct Input object.
LPDIRECTINPUTDEVICE8  dInputKeyboardDevice; //	Direct Input keyboard device.
LPDIRECTINPUTDEVICE8  dInputMouseDevice; //	Direct Input mouse device.

BYTE diKeys[256];
bool upKey = false;
bool downKey = false;
bool leftKey = false;
bool rightKey = false;
bool wKey = false;
bool aKey = false;
bool sKey = false;
bool dKey = false;
bool enterKey = false;

DIMOUSESTATE mouseState;

float xMouse = 300, yMouse = 400;

int counter = 0;


//	Window Procedure, for event handling
//hWnd - handle the windows that sent this message
//message - title of the email
//wParam - attachment in the email
//lParam - 2nd attachment in the email
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		//	The message is post when we destroy the window.
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
		//task2
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) {
			PostQuitMessage(0);
			break;
		}

		//if (wParam == 0x52) //R
		//{
		//	red += 5;
		//}

		//if (wParam == 0x47) //G
		//{
		//	green += 5;
		//}

		//if (wParam == 0x42) //B
		//{
		//	blue += 5;
		//}

	case WM_MOUSEMOVE:{ //get mouse pos
		/*xMouse = (float)GET_X_LPARAM(lParam);
		yMouse = (float)GET_Y_LPARAM(lParam);

		position.x = xMouse;
		position.y = yMouse;*/

	}


		/*
			Write your code here...
		*/

		//	Default handling for other messages.
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
//--------------------------------------------------------------------

//	Window's structure data structure which stores how we want our to be //moved from createWindow to global 
//only exists once for the entire program, makes sense to make it global


void createWindow() {

	

	//create box 


	//clear box

	//	Set all members in wndClass to 0.
	ZeroMemory(&wndClass, sizeof(wndClass));

	//define class

	//	Filling wndClass. You are to refer to MSDN for each of the members details.
	//	These are the fundamental structure members to be specify, in order to create your window.
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hInstance = GetModuleHandle(NULL);//Instance;	//	
	wndClass.lpfnWndProc = WindowProcedure;
	wndClass.lpszClassName = "Ping Pang";
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	//registers window

	//	Register the window.
	RegisterClass(&wndClass);


	
	//	Create the Window.
	
	//	You are to refer to MSDN for each of the parameters details.
	g_hWnd = CreateWindowEx(0, wndClass.lpszClassName, "Ping Pang", WS_OVERLAPPEDWINDOW, 0, 100, WINDOWWIDTH, WINDOWHEIGHT, NULL, NULL, GetModuleHandle(NULL), NULL);
	ShowWindow(g_hWnd, 1);
	ShowCursor(true);

	//	Some interesting function to try out.
	//	ShowCursor(false);


}

void cleanupWindow() {

	UnregisterClass(wndClass.lpszClassName, GetModuleHandle(NULL));

}

bool windowsRunning() {

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	int count = 0;

	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		//	Receive a quit message
		if (msg.message == WM_QUIT) {
			return false;
		}
		//	Translate the message, converts the message format back to the correct one
		TranslateMessage(&msg);
		//	Send message to your window procedure
		DispatchMessage(&msg);




	}
	return true;
	
}

bool createDirectX() {
	//	Define Direct3D 9.
	IDirect3D9* direct3D9 = Direct3DCreate9(D3D_SDK_VERSION);

	//	Define how the screen presents.
	D3DPRESENT_PARAMETERS d3dPP;
	ZeroMemory(&d3dPP, sizeof(d3dPP));

	//	Refer to Direct3D 9 documentation for the meaning of the members.
	d3dPP.Windowed = true;
	d3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dPP.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dPP.BackBufferCount = 1;
	d3dPP.BackBufferWidth = WINDOWWIDTH;
	d3dPP.BackBufferHeight = WINDOWHEIGHT;
	d3dPP.hDeviceWindow = g_hWnd;

	
	//	Create a Direct3D 9 device.
	hr = direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dPP, &d3dDevice);

	return true;
}



void cleanupDirectX() {



	sprite->Release();
	sprite = NULL;

	
	player1.texture -> Release();
	player1.texture = NULL;

	player2.texture->Release();
	player2.texture = NULL;


	ball1.texture->Release();
	ball1.texture = NULL;




	//	Release the device when exiting.
	d3dDevice->Release();
	//	Reset pointer to NULL, a good practice.
	d3dDevice = NULL;


	//	Release keyboard mouse device.
	dInputKeyboardDevice->Unacquire();
	dInputKeyboardDevice->Release();
	dInputKeyboardDevice = NULL;

	dInputMouseDevice->Unacquire();
	dInputMouseDevice->Release();
	dInputMouseDevice = NULL;

	//	Release DirectInput.
	dInput->Release();
	dInput = NULL;

	//cleanup text
	/*font->Release();
	font = NULL;*/


}

void createInput() {
	//	Create the Direct Input object.
	hr = DirectInput8Create(GetModuleHandle(NULL), 0x0800, IID_IDirectInput8, (void**)&dInput, NULL);

	//	Create the keyboard device.
	hr = dInput->CreateDevice(GUID_SysKeyboard, &dInputKeyboardDevice, NULL);
	hr = dInput->CreateDevice(GUID_SysMouse, &dInputMouseDevice, NULL);

	//	Set the input data format.
	dInputKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);
	dInputMouseDevice->SetDataFormat(&c_dfDIMouse);

	//	Set the cooperative level.
	//	To Do:
	//	Try with different combination.
	dInputKeyboardDevice->SetCooperativeLevel(g_hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
	dInputMouseDevice->SetCooperativeLevel(g_hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
}

void getInput() {
	//	Get immediate Keyboard Data.
	dInputKeyboardDevice->GetDeviceState(256, diKeys);

	if (diKeys[DIK_UP] & 0x80)
	{
		upKey = true;
	}
	if (diKeys[DIK_DOWN] & 0x80)
	{
		downKey = true;
	}
	if (diKeys[DIK_LEFT] & 0x80)
	{
		leftKey = true;

	}
	if (diKeys[DIK_RIGHT] & 0x80)
	{
		rightKey = true;
	}
	if (diKeys[DIK_W] & 0x80)
	{
		wKey = true;
	}
	if (diKeys[DIK_A] & 0x80)
	{
		aKey = true;
	}
	if (diKeys[DIK_S] & 0x80)
	{
		sKey = true;
	}
	if (diKeys[DIK_D] & 0x80)
	{
		dKey = true;
	}
	if (diKeys[DIK_RETURN] & 0x80) {
		enterKey = true;
	}

	dInputMouseDevice->GetDeviceState(sizeof(mouseState), &mouseState);

	xMouse = mouseState.lX;
	yMouse = mouseState.lY;
}

void testFail(HRESULT hr) {

	if (FAILED(hr)) {
		MessageBox(NULL,
			TEXT("Failed to load something lol idk\n"),
			TEXT("Error!"),
			MB_OK);

	}

}

RECT setRECT(int left, int top, int right, int bottom) {

	RECT setRect;

	setRect.left = left;
	setRect.top = top;
	setRect.right = right;
	setRect.bottom = bottom;

	return setRect;
}

float random(int i) {
	srand((unsigned)time(NULL));
	return rand() % i + 1.28;
}

void initialize() {

	

	hr = D3DXCreateSprite(d3dDevice, &sprite);
	testFail(hr);

	ball1.mass = 10;
	ball1.forceMagnitude = 100;

	ball1.rotation = random(6);

	player1.speed = 10;
	player2.speed = 10;


	player1.height = 256;
	player1.width = 32;

	player2.height = 256;
	player2.width = 32;

	ball1.height = 64;
	ball1.width = 64;

	//ball1.velocity = ball1.acceleration;

	ball1.force.x = ball1.forceMagnitude * sin(ball1.rotation);
	ball1.force.y = ball1.forceMagnitude * -cos(ball1.rotation);

	ball1.velocity = ball1.force / ball1.mass;


	//default position///
	///
	///


	player1.scaling = D3DXVECTOR2(0.5f, 0.5f);
	player1.position = D3DXVECTOR2(50 - player1.width*player1.scaling.x, WINDOWHEIGHT/2 - (player1.height/2)*player1.scaling.x);


	player2.scaling = D3DXVECTOR2(0.5f, 0.5f);
	player2.position = D3DXVECTOR2(WINDOWWIDTH - 50, WINDOWHEIGHT / 2 - (player2.height / 2) * player2.scaling.x);

	ball1.scaling = D3DXVECTOR2(0.3f, 0.3f);
	ball1.position = D3DXVECTOR2((WINDOWWIDTH / 2) - ball1.width/2 * ball1.scaling.x, (WINDOWHEIGHT / 2) - ball1.height/2 * ball1.scaling.y);


	//RECT//
	////////////////
	/////////////////
	
	player2.rect = setRECT( 0, 0, 32, 256);
	player1.rect = setRECT(32, 0, 64, 256);
	ball1.rect = setRECT(0, 0, 64, 64);
	


	//sprites//
	///////////////////////
	////////////////////////
	

	hr = D3DXCreateTextureFromFile(d3dDevice, "bars.png", &player1.texture);
	testFail(hr);

	hr = D3DXCreateTextureFromFile(d3dDevice, "bars.png", &player2.texture);
	testFail(hr);

	hr = D3DXCreateTextureFromFile(d3dDevice, "ball.png", &ball1.texture);
	testFail(hr);

	hr = D3DXCreateLine(d3dDevice, &line);
	testFail(hr);

	//	Create texture. Study the documentation.
}



void render() {
	//	Clear the back buffer.
	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(red, green, blue), 1.0f, 0);

	d3dDevice->BeginScene();



	line->Begin();
	line->Draw(lineVertices, 2, D3DCOLOR_XRGB(255, 255, 255));
	line->Draw(lineVertices2, 2, D3DCOLOR_XRGB(255, 255, 255));
	line->End();


	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	D3DXMATRIX mat;
	
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &player1.scaling, &player1.spriteCenter, player1.rotation, &player1.position);
	sprite->SetTransform(&mat);

	sprite->Draw(player1.texture, &player1.rect, NULL, NULL, D3DCOLOR_XRGB(255, 0, 0));

	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &player2.scaling, &player2.spriteCenter, player2.rotation, &player2.position);
	sprite->SetTransform(&mat);
	
	sprite->Draw(player2.texture, &player2.rect, NULL, NULL, D3DCOLOR_XRGB(0, 0, 255));

	ball1.spriteCenter = D3DXVECTOR2 (8, 8);

	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &ball1.scaling, &ball1.spriteCenter, ball1.rotation, &ball1.position);
	sprite->SetTransform(&mat);

	sprite->Draw(ball1.texture, &ball1.rect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));

	sprite->End();


	//	End the scene
	d3dDevice->EndScene();

	//	Present the back buffer to screen
	d3dDevice->Present(NULL, NULL, NULL, NULL);


}

int aPosXL, aPosXR, aPosYU, aPosYD, bPosXL, bPosXR, bPosYU, bPosYD;

bool checkCol(D3DXVECTOR2 aPos, int aHeight, int aWidth, D3DXVECTOR2 bPos, int bHeight, int bWidth) {

	aPosXL = aPos.x ;
	aPosXR = aPos.x + aWidth;
	aPosYU = aPos.y;
	aPosYD = aPos.y + aHeight;

	bPosXL = bPos.x;
	bPosXR = bPos.x + bWidth;
	bPosYU = bPos.y;
	bPosYD = bPos.y + bHeight;


	if (aPosXR < bPosXL) {
		return false;
	}
	else if (aPosXL > bPosXR) {
		return false;
	}
	else if (aPosYD < bPosYU) {
		return false;
	}
	else if (aPosYU > bPosYD) {
		return false;
	}
	else {
		return true;
	}

}


double spriteHeight, spriteWidth;



RECT spriteOutputCycle (RECT &spriteRect,  int textureWidth, int textureHeight, int col, int row , int maxFrames, int& frameCount){
	
	spriteHeight = textureHeight / row;
	spriteWidth = textureWidth / col;

	

	if (counter % 1 == 0) {
		
		spriteRect.top = frameCount / row * spriteHeight;
		spriteRect.bottom = spriteRect.top + spriteHeight;

		spriteRect.left = frameCount % col * spriteWidth;
		spriteRect.right = spriteRect.left + spriteWidth;

		frameCount++;

		if (frameCount >= maxFrames) {
			frameCount = 0;
		}
		
	}
	

	return spriteRect;
}

RECT charSpriteOutputCycle(RECT& spriteRect, int textureWidth, int textureHeight, int col, int row, int charState, int maxFrames, int& frameCount) {

	spriteHeight = textureHeight / row;
	spriteWidth = textureWidth / col;


	if (counter % 1 == 0) {

		spriteRect.top = charState * spriteHeight;
		spriteRect.bottom = spriteRect.top + spriteHeight;

		spriteRect.left = frameCount % col * spriteWidth;
		spriteRect.right = spriteRect.left + spriteWidth;

		frameCount ++;

		if (frameCount >= maxFrames) {
			frameCount = 0;
		}

	}


	return spriteRect;
}


void update(int framesToUpdate) {

	if (enterKey) {
		if (gameStart == false) {
		

			ball1.rotation = random(6);
			ball1.position = D3DXVECTOR2((WINDOWWIDTH / 2) - ball1.width / 2 * ball1.scaling.x, (WINDOWHEIGHT / 2) - ball1.height / 2 * ball1.scaling.y);
			player1.position = D3DXVECTOR2(50 - player1.width * player1.scaling.x, WINDOWHEIGHT / 2 - (player1.height / 2) * player1.scaling.x);
			player2.position = D3DXVECTOR2(WINDOWWIDTH - 50, WINDOWHEIGHT / 2 - (player2.height / 2) * player2.scaling.x);

			ball1.force.x = ball1.forceMagnitude * sin(ball1.rotation);
			ball1.force.y = ball1.forceMagnitude * -cos(ball1.rotation);

			ball1.velocity = ball1.force / ball1.mass;

			gameStart = true;			


		}
		enterKey = false;
	}

	if(gameStart==true){

	if (upKey) {

		if (player2.position.y >= 0) {
			player2.moveY -= player2.speed;
		}
		else {
			if (player2.position.y <= 0) {
				player2.position.y = 0;
			}
		}



		upKey = false;

	}

	if (downKey) {
		if (player2.position.y <= (WINDOWHEIGHT - player2.height * player2.scaling.x)) {
			player2.moveY += player2.speed;
		}
		else {
			if (player2.position.y <= (WINDOWHEIGHT - player2.height * player2.scaling.x)) {
				player2.position.y = (WINDOWHEIGHT - player2.height * player2.scaling.x);
			}
		}

		downKey = false;
	}
	if (wKey) {

		if (player1.position.y >= 0) {
			player1.moveY -= player1.speed;
		}
		else {
			if (player1.position.y <= 0) {
				player1.position.y = 0;
			}
		}


		wKey = false;
	}
	if (sKey) {

		if (player1.position.y <= (WINDOWHEIGHT - player1.height * player1.scaling.x)) {
			player1.moveY += player1.speed;
		}
		else {
			if (player1.position.y <= (WINDOWHEIGHT - player1.height * player1.scaling.x)) {
				player1.position.y = (WINDOWHEIGHT - player1.height * player1.scaling.x);
			}
		}


		sKey = false;
	}

	if (ball1.position.x < 0 || ball1.position.x > WINDOWWIDTH - ball1.width * ball1.scaling.x) {

		if (ball1.position.x < 0) {
			ball1.velocity = D3DXVECTOR2(0, 0);
			gameStart = false;
		}
		if (ball1.position.x > WINDOWWIDTH - ball1.width * ball1.scaling.x) {
			ball1.velocity = D3DXVECTOR2(0, 0);
			gameStart = false;
		}
	}

	if (ball1.position.y < 0 || ball1.position.y > WINDOWHEIGHT - ball1.height * ball1.scaling.y) {

		ball1.velocity.y *= -0.95;
		

		if (ball1.position.y < 0) {
			ball1.position.y = 0;
		}
		if (ball1.position.y > WINDOWHEIGHT - ball1.height * ball1.scaling.y) {
			ball1.position.y = WINDOWHEIGHT - ball1.height * ball1.scaling.y;
		}

	}


	if (checkCol(player1.position, 128, 32, ball1.position, 32, 32)) {
		ball1.velocity.x *= -1;
		
		
		
		
	}

	if (checkCol(player2.position, 128, 32, ball1.position, 32, 32)) {
		ball1.velocity.x *= -1 ;
		
		
		

	}


}


	for (int frame = 0; frame < framesToUpdate; frame++) {

		if (gameStart == true) {
			player1.position.y += player1.moveY;
			player1.moveY = 0;
			player2.position.y += player2.moveY;
			player2.moveY = 0;

			//ball1.velocity += ball1.acceleration;		
			ball1.position += ball1.velocity;
		}
		
	}



	cout << "player1x: " << player1.position.x << " player2: " << player1.position.y << endl;

	counter++;
}

//	use int main if you want to have a console to print out message
//int main()

//	use WinMain if you don't want the console
//hInstance = ID number of the instance of this window
//hPrevInstance = ID number of the instance of the PARENT of this window (OBSOLETE)
//lp CmdLine = POINTER to a command line string
//nShowCmd = style

int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	//POINT mouse;
	
	createWindow();

	createInput();

	if (!createDirectX())
		return 0;
	

	if (FAILED(hr))
		return 0;


	
	initialize();
	

	FrameTimer myTimer;
	myTimer.init(60);

	dInputKeyboardDevice->Acquire();
	dInputMouseDevice->Acquire();

	while (windowsRunning()) {


		/*
		Game ->
		GetInput()
		Update()
		Redner()
		PlaySound()
		*/

		getInput();

		
		update(myTimer.framesToUpdate());
		

		render();

	}

	
	
	cleanupDirectX();
	
	//	Free up the memory.
	cleanupWindow();

	return 0;
}
//--------------------------------------------------------------------