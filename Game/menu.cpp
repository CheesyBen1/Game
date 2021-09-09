
//#ifndef menu
//#define MENU

#include "menu.h"
#define WINDOWHEIGHT 600
#define WINDOWWIDTH 800
bool enterMenuKey;

IDirect3DDevice9* d3dDevice;
LPD3DXSPRITE sprite = NULL;

LPDIRECTINPUTDEVICE8 dInputKeyboardDeviceMenu;
LPD3DXLINE line = NULL;
D3DXVECTOR2 lineVertices[] = { D3DXVECTOR2(WINDOWWIDTH / 4, WINDOWHEIGHT / 3), D3DXVECTOR2(WINDOWWIDTH / 4, WINDOWWIDTH / 2),D3DXVECTOR2(WINDOWHEIGHT, WINDOWWIDTH / 2),D3DXVECTOR2(WINDOWHEIGHT, WINDOWWIDTH / 4), D3DXVECTOR2(WINDOWWIDTH / 4,  WINDOWWIDTH / 4) };

LPD3DXFONT font = NULL;
LPD3DXFONT startFont = NULL;
LPD3DXFONT endFont = NULL;

RECT textRect;
RECT startTextRect;
RECT endTextRect;


menu::menu()
{


}

void menu::getInput(LPDIRECTINPUTDEVICE8 dInputKeyboardDevice, BYTE diKeys[256]) {
	dInputKeyboardDevice->GetDeviceState(256, diKeys);
	if (diKeys[DIK_RETURN] & 0x80) {
		enterMenuKey = true;
	}
}

bool menu::update(int framesToUpdate) {

	

	if (enterMenuKey) {
		


		enterMenuKey = false;

		return true;
	}

	

}

void menu::initialize() {
	//Tittle text
	textRect.left = 50;
	textRect.top = -80;
	textRect.right = 250;
	textRect.bottom = 50;

	//Start text
	startTextRect.left = 50;
	startTextRect.top = -20;
	startTextRect.right = 250;
	startTextRect.bottom = 200;

	//Quit text
	endTextRect.left = 50;
	endTextRect.top = 40;
	endTextRect.right = 250;
	endTextRect.bottom = 200;
}
void menu::render() {

	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	d3dDevice->BeginScene();


	line->Begin();
	line->Draw(lineVertices, 5, D3DCOLOR_XRGB(255, 255, 255));

	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	HRESULT hr = D3DXCreateFont(d3dDevice, 30, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Arial", &font);

	hr = D3DXCreateFont(d3dDevice, 25, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Arial", &startFont);

	hr = D3DXCreateFont(d3dDevice, 25, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Arial", &endFont);

	font->DrawText(sprite, "Ping Pang", 9, &textRect, 0, D3DCOLOR_XRGB(255, 255, 255));
	startFont->DrawText(sprite, "Start Game", 12, &startTextRect, 0, D3DCOLOR_XRGB(255, 255, 255));
	endFont->DrawText(sprite, "Quit Game", 9, &endTextRect, 0, D3DCOLOR_XRGB(255, 255, 255));

	sprite->End();
	line->End();
	d3dDevice->EndScene();
	d3dDevice->Present(NULL, NULL, NULL, NULL);

	font->Release();
	font = NULL;

	startFont->Release();
	startFont = NULL;

	endFont->Release();
	endFont = NULL;

	line->Release();
	line = NULL;
}

void menu::playSound() {

}
//#endif