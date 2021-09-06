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

bool menu::update(int framesToUpdate) {
	if (escMenuKey) {
		PostQuitMessage(0);

		escMenuKey = false;
	}

	if (enterMenuKey) {
		enterMenuKey = false;

		return true;
	}
}
void menu::render() {
}

void menu::playSound() {
}