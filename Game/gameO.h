#ifndef GAMEOVER_H
#define GAMEOVER_H

#include "states.h"

class gameO :
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

	static gameO* instance() {
		return &gameOverState;
	}

protected:
	gameO() { }

private:
	static gameO gameOverState;

	LPD3DXSPRITE sprite = NULL;
	LPD3DXLINE line = NULL;
	BYTE diKeys[256];
	RECT rect;
	text gameO1Text;
	text gameO2Text;
	text player1TemScore;
	text player2TemScore;
	text conText;
	Audio* sounds;
};
#endif