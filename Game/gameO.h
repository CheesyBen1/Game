#pragma once
#include "gameState.h"
#include "game.h"
class gameO :
	public game
{
public:
	gameO();

	void getInput(LPDIRECTINPUTDEVICE8 dInputKeyboardDevice, BYTE diKeys[256]);
	int update(int framesToUpdate, player* playerP1, player* playerP2, ball* ballP, int* scoreOne, int* scoreTwo);
	void render(IDirect3DDevice9* d3dDevice, LPD3DXSPRITE* spriteP, LPD3DXLINE* lineP, player* playerP1, player* playerP2, ball* ballP);
	void playSound();
};
