#pragma once
#include "gameState.h"

class menu :
	public gameState
{
public:
	menu();
	void getInput(LPDIRECTINPUTDEVICE8 dInputKeyboardDevice1, BYTE diKeys[256]);
	int update(int framesToUpdate);
	void render(IDirect3DDevice9* d3dDevice);
	void playSound();
};
