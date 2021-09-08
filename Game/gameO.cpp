#include "gameO.h"

bool escOverKey = false;
bool spaceOverKey = false;

using namespace std;

gameO::gameO() {
}

void gameO::getInput(LPDIRECTINPUTDEVICE8 dInputKeyboardDevice, BYTE diKeys[256])
{
	dInputKeyboardDevice->GetDeviceState(256, diKeys);
	if (diKeys[DIK_ESCAPE] & 0x80) {
		escOverKey = true;
	}
	if (diKeys[DIK_SPACE] & 0x80) {
		spaceOverKey = true;
	}
}

int gameO::update(int framesToUpdate, int* scoreP1, int* scoreP2)
{
	int& score1 = *scoreP1;
	int& score2 = *scoreP2;
	if (escOverKey) {
		PostQuitMessage(0);

		escOverKey = false;
	}

	if (score1 < 5 && score2 < 5) {
		cout << "Player 1 score: " << score1 << " Player 2 score: " << score2 << "\tPlay till 5. Press SPACE to continue." << endl;
		if (spaceOverKey) {
			spaceOverKey = false;
			return 2;
		}
	}
	else {
		cout << "Game Over! ";
		if (score1 == 5) {
			cout << "Player 1 wins! ";
		}
		else if (score2 == 5) {
			cout << "Player 2 wins! ";
		}
		if (spaceOverKey) {
			spaceOverKey = false;
			score1 = 0;
			score2 = 0;
			return 1;
		}
		cout << "Player 1 score: " << score1 << " Player 2 score: " << score2 << " Press SPACE to restart game." << endl;
	}

	//std::cout << "Game Over. Player " << result << " wins. Press Enter to Retart" << std::endl;
	return 3;
}

void gameO::render(IDirect3DDevice9* d3dDevice)
{
	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	d3dDevice->BeginScene();

	//	End the scene
	d3dDevice->EndScene();

	//	Present the back buffer to screen
	d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void gameO::playSound()
{
}