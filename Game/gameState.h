#pragma once
#include <cmath>
#include <Windows.h>
#include <Windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <iostream>
#include <math.h>
class gameState
{
public:
	gameState();

	void getInput();
	void update();
	void render();
	void playSound();
};
