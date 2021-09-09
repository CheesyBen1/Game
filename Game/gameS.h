#pragma once
#include "gameState.h"
#include "ball.h"
#include <iostream>
#include "game.h"
#define WINDOWWIDTH 800
#define WINDOWHEIGHT 600

using namespace std;

class gameS :
	public game
{
public:

	gameS();

	void getInput(LPDIRECTINPUTDEVICE8 dInputKeyboardDevice, BYTE diKeys[256]);
	int update(int framesToUpdate, player* playerP1, player* playerP2, ball* ballP, int* scoreOne, int* scoreTwo);
	void render(IDirect3DDevice9* d3dDevice, LPD3DXSPRITE* spriteP, LPD3DXLINE* lineP, player* playerP1, player* playerP2, ball* ballP);
	void playSound();
};
