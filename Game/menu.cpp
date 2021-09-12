#include "menu.h"
#include "game.h"
#include "states.h"
#include "gameS.h"

bool enterMenuKey = false;
bool escMenuKey = false;

menu menu::menuState;

void menu::init(IDirect3DDevice9* d3dDevice)
{
}

void menu::cleanup()
{
	mouseCursorTexture->Release();
	mouseCursorTexture = NULL;

	font->Release();
	font = NULL;

	startFont->Release();
	startFont = NULL;

	endFont->Release();
	endFont = NULL;

	line->Release();
	line = NULL;
}

void menu::pause()
{
}

void menu::resume()
{
}

void menu::getInput(game* games, LPDIRECTINPUTDEVICE8& dInputKeyboardDevice, LPDIRECTINPUTDEVICE8& dInputMouseDevice) {
	dInputKeyboardDevice->GetDeviceState(256, diKeys);
	if (diKeys[DIK_ESCAPE] & 0x80) {
		escMenuKey = true;
	}
	if (diKeys[DIK_RETURN] & 0x80) {
		enterMenuKey = true;
	}
}

void menu::update(game* games, int framesToUpdate, int& scoreOne, int& scoreTwo) {
	if (escMenuKey) {
		PostQuitMessage(0);

		escMenuKey = false;
	}

	if (enterMenuKey) {
		enterMenuKey = false;
		games->changeState(gameS::instance());
	}

	std::cout << "Menu (add UI, start exit buttons), Press Enter to start" << std::endl;
}
void menu::render(game* games, IDirect3DDevice9* d3dDevice) {
	
	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	d3dDevice->BeginScene();

	//	End the scene
	d3dDevice->EndScene();

	//	Present the back buffer to screen
	d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void menu::playSound(game* games) {
}