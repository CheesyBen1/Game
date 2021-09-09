#ifndef GAME_H
#define GAME_H

#define WIN32_LEAN_AND_MEAN
#define _USE_MATH_DEFINES

#include "ball.h"
#include <cmath>
#include <Windows.h>
#include <Windowsx.h>
#include <iostream>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <vector>
#include "FrameTimer.h"

using namespace std;

class states;

class game
{
private:

public:
	void init(LPCSTR Title, int WINDOWWIDTH, int WINDOWHEIGHT);
	void cleanup();

	void changeState(states* state);
	void pushState(states* state);
	void popState();

	void getInput();
	void update();
	void render();
	void playSound();

	bool running();

private:
	vector<states*>stateStack;

	int scoreOne = 0;
	int scoreTwo = 0;

	FrameTimer myTimer;
};

#endif
