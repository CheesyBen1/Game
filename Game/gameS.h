#ifndef GAMESTARTSTATE_H
#define GAMESTARTSTATE_H

#include "ball.h"
#include <iostream>
#include "states.h"

#define WINDOWWIDTH 800
#define WINDOWHEIGHT 600

class gameS :
	public states
{
public:
	void init(IDirect3DDevice9* d3dDevice);
	void cleanup();

	void pause();
	void resume();

	void getInput(game* games, LPDIRECTINPUTDEVICE8& dInputKeyboardDevice, LPDIRECTINPUTDEVICE8& dInputMouseDevice);
	void update(game* games, int framesToUpdate, int& scoreOne, int& scoreTwo);
	void render(game* games, IDirect3DDevice9* d3dDevice);
	void playSound(game* games);

	static gameS* instance() {
		return &gameStartState;
	}

protected:
	gameS() { }

private:
	static gameS gameStartState;

	RECT setRECT(int left, int top, int right, int bottom) {
		RECT setRect;

		setRect.left = left;
		setRect.top = top;
		setRect.right = right;
		setRect.bottom = bottom;

		return setRect;
	}

	LPD3DXSPRITE sprite = NULL;
	LPD3DXLINE line = NULL;
	BYTE diKeys[256];

	Audio* sounds;

	ball player1;
	ball player2;
	ball ball1;
};
#endif