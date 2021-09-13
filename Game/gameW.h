#ifndef GAMEWIN_H
#define GAMEWIN_H

#include "states.h"

class gameW :
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

	static gameW* instance() {
		return &gameWinState;
	}

protected:
	gameW() { }

private:
	static gameW gameWinState;

	LPD3DXSPRITE sprite = NULL;
	LPD3DXLINE line = NULL;
	BYTE diKeys[256];
	RECT rect;
	text gameW1Text;
	text gameW2Text;
	Audio* sounds;
};
#endif