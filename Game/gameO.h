#pragma once
#include "gameState.h"
class gameO :
	public gameState
{
public:
	gameO();

	void getInput(LPDIRECTINPUTDEVICE8 dInputKeyboardDevice, BYTE diKeys[256]);
	int update(int framesToUpdate, int* scoreP1, int* scoreP2);
	void render();
	void playSound();
};
