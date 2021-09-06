
//#ifndef menu
//#define MENU

#include "menu.h"

bool enterMenuKey;


LPDIRECTINPUTDEVICE8 dInputKeyboardDeviceMenu;




menu::menu()
{


}

void menu::getInput(LPDIRECTINPUTDEVICE8 dInputKeyboardDevice, BYTE diKeys[256]) {
	dInputKeyboardDevice->GetDeviceState(256, diKeys);
	if (diKeys[DIK_RETURN] & 0x80) {
		enterMenuKey = true;
	}
}

bool menu::update() {

	

	if (enterMenuKey) {
		


		enterMenuKey = false;

		return true;
	}

	

}
void menu::render() {

}

void menu::playSound() {

}
//#endif