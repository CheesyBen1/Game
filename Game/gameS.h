#pragma once
#include "gameState.h"
#include "ball.h"
#include <iostream>
#define WINDOWWIDTH 800
#define WINDOWHEIGHT 600

using namespace std;

class gameS :
	public gameState
{
public:

	gameS();

	void getInput(LPDIRECTINPUTDEVICE8 dInputKeyboardDevice, BYTE diKeys[256]);
	bool update(int framesToUpdate, int* counterP, player* playerP1, player* playerP2, ball* ballP);
	void render(IDirect3DDevice9* d3dDevice, LPD3DXSPRITE* spriteP, LPD3DXLINE* lineP, player* playerP1, player* playerP2, ball* ballP);
	void playSound();
};
