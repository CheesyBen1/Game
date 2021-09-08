#include "gameO.h"

bool escOverKey = false;
bool enterOverKey = false;

using namespace std;

gameO::gameO() {
}

void gameO::getInput(LPDIRECTINPUTDEVICE8 dInputKeyboardDevice, BYTE diKeys[256])
{
	dInputKeyboardDevice->GetDeviceState(256, diKeys);
	if (diKeys[DIK_ESCAPE] & 0x80) {
		escOverKey = true;
	}
	if (diKeys[DIK_RETURN] & 0x80) {
		enterOverKey = true;
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
		cout << "Player 1 score: " << score1 << "\tPlayer 2 score: " << score2 << "\tPlay till 5" << endl;
		if (enterOverKey) {
			enterOverKey = false;
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
		cout << "Player 1 score: " << score1 << " Player 2 score: " << score2 << " Press Enter to restart game." << endl;
		if (enterOverKey) {
			enterOverKey = false;

			score1 = 0;
			score2 = 0;

			return 1;
		}
	}

	//std::cout << "Game Over. Player " << result << " wins. Press Enter to Retart" << std::endl;
	return 3;
}

void gameO::render()
{
}

void gameO::playSound()
{
}