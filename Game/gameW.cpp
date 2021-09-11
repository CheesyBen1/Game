#include "game.h"
#include "gameW.h"
#include "menu.h"

gameW gameW::gameWinState;

bool escWinKey = false;
bool spaceWinKey = false;

void gameW::init(IDirect3DDevice9* d3dDevice)
{
}

void gameW::cleanup()
{
}

void gameW::pause()
{
}

void gameW::resume()
{
}

void gameW::getInput(game* games, LPDIRECTINPUTDEVICE8& dInputKeyboardDevice, LPDIRECTINPUTDEVICE8& dInputMouseDevice)
{
	dInputKeyboardDevice->GetDeviceState(256, diKeys);
	if (diKeys[DIK_ESCAPE] & 0x80) {
		escWinKey = true;
	}
	if (diKeys[DIK_SPACE] & 0x80) {
		spaceWinKey = true;
	}
}

void gameW::update(game* games, int framesToUpdate, int& scoreOne, int& scoreTwo)
{
	if (escWinKey) {
		PostQuitMessage(0);

		escWinKey = false;
	}

	cout << "Game Over! ";
	if (scoreOne == 5) {
		cout << "Player 1 wins! ";
	}
	else if (scoreTwo == 5) {
		cout << "Player 2 wins! ";
	}
	if (spaceWinKey) {
		spaceWinKey = false;
		scoreOne = 0;
		scoreTwo = 0;
		games->changeState(menu::instance());
	}
	cout << "Player 1 score: " << scoreOne << " Player 2 score: " << scoreTwo << " Press SPACE to restart game." << endl;

	//std::cout << "Game Over. Player " << result << " wins. Press Enter to Retart" << std::endl;
	/*return 3;*/
}

void gameW::render(game* games, IDirect3DDevice9* d3dDevice)
{
	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	d3dDevice->BeginScene();

	//	End the scene
	d3dDevice->EndScene();

	//	Present the back buffer to screen
	d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void gameW::playSound(game* games)
{
}