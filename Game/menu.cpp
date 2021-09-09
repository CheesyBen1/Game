#include "menu.h"

bool enterMenuKey = false;
bool escMenuKey = false;

LPDIRECTINPUTDEVICE8 dInputKeyboardDeviceMenu;

menu::menu()
{
}

void menu::getInput(LPDIRECTINPUTDEVICE8 dInputKeyboardDevice, BYTE diKeys[256]) {
	dInputKeyboardDevice->GetDeviceState(256, diKeys);
	if (diKeys[DIK_ESCAPE] & 0x80) {
		escMenuKey = true;
	}
	if (diKeys[DIK_RETURN] & 0x80) {
		enterMenuKey = true;
	}
}

int menu::update(int framesToUpdate, player* playerP1, player* playerP2, ball* ballP, int* scoreOne, int* scoreTwo) {
	if (escMenuKey) {
		PostQuitMessage(0);

		escMenuKey = false;
	}

	if (enterMenuKey) {
		enterMenuKey = false;

		return 2;
	}

	std::cout << "Menu (add UI, start exit buttons), Press Enter to start" << std::endl;

	return 1;
}
void menu::render(IDirect3DDevice9* d3dDevice, LPD3DXSPRITE* spriteP, LPD3DXLINE* lineP, player* playerP1, player* playerP2, ball* ballP) {
	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	d3dDevice->BeginScene();

	//	End the scene
	d3dDevice->EndScene();

	//	Present the back buffer to screen
	d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void menu::playSound() {
}