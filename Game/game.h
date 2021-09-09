#define WIN32_LEAN_AND_MEAN
#define _USE_MATH_DEFINES
#pragma once
#include "ball.h"
#include <cmath>
#include <Windows.h>
#include <Windowsx.h>
#include <iostream>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

class game
{
private:

public:
	game() {};
	virtual void getInput(LPDIRECTINPUTDEVICE8 dInputKeyboardDevice, BYTE diKeys[256]) = 0;
	virtual int update(int framesToUpdate, player* playerP1, player* playerP2, ball* ballP, int* scoreOne, int* scoreTwo) = 0;
	virtual void render(IDirect3DDevice9* d3dDevice, LPD3DXSPRITE* spriteP, LPD3DXLINE* lineP, player* playerP1, player* playerP2, ball* ballP) = 0;
	virtual void playSound() = 0;
};
