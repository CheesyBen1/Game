#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "states.h"



class menu :public states
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

	static menu* instance() {
		return &menuState;
	}

protected:
	menu() { }

private:
	static menu menuState;
	LPD3DXSPRITE sprite = NULL;
	LPD3DXLINE line = NULL;
	BYTE diKeys[256];
	
	D3DXVECTOR3 mousePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	LPDIRECT3DTEXTURE9 mouseCursorTexture = NULL;

	DIMOUSESTATE mouseState;
	RECT rect;
	Audio* sounds;

	player cursor;

	text titleText;
	text startText;
	text endText;

};
#endif