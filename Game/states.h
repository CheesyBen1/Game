#ifndef STATES_H
#define STATES_H

#define WIN32_LEAN_AND_MEAN
#define _USE_MATH_DEFINES
#define BUTTONDOWN(name, key) (name.rgbButtons[key] & 0x80)

#include "game.h"
#include "ball.h"
#include <cmath>
#include <Windows.h>
#include <Windowsx.h>
#include <iostream>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include "audio.h"
#include "text.h"
#include <vector>
#include "FrameTimer.h"

class states
{
public:

	virtual void init(IDirect3DDevice9* d3dDevice) = 0;
	virtual void cleanup() = 0;

	virtual void pause() = 0;
	virtual void resume() = 0;

	virtual void getInput(game* games, LPDIRECTINPUTDEVICE8& dInputKeyboardDevice, LPDIRECTINPUTDEVICE8& dInputMouseDevice) = 0;
	virtual void update(game* games, int framesToUpdate, int& scoreOne, int& scoreTwo) = 0;
	virtual void render(game* games, IDirect3DDevice9* d3dDevice) = 0;
	virtual void playSound(game* games) = 0;
	//check no collision bool

	void changeState(game* game, states* state) {
		game->changeState(state);
	}

	void testFail(HRESULT hr, string message) {
		const char* str = message.c_str();
		if (FAILED(hr)) {
			MessageBox(NULL,
				TEXT(str),
				TEXT("Error!"),
				MB_OK);
		}
	}

	RECT setRECT(int left, int top, int right, int bottom) {
		RECT setRect;

		setRect.left = left;
		setRect.top = top;
		setRect.right = right;
		setRect.bottom = bottom;

		return setRect;
	}

	bool cursorCol(player& cursor, text& hover) {
		if (cursor.position3.x < hover.rect.left) {
			return false;
		}
		else if (cursor.position3.x > hover.rect.right) {
			return false;
		}
		else if (cursor.position3.y < hover.rect.top) {
			return false;
		}
		else if (cursor.position3.y > hover.rect.bottom) {
			return false;
		}
		else {
			return true;
		}
	}

protected:
	states() { }
};

#endif
