#pragma once
#include <cmath>
#include <Windows.h>
#include <Windowsx.h>
#include <iostream>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

class gameState
{
public:
	gameState();
	void getInput();
	void update();
	void render();
	void playSound();
};

