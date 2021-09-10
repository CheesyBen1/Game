#include "gameO.h"
#include "game.h"
#include "gameS.h"
#include "menu.h"

gameO gameO::gameOverState;

bool escOverKey = false;
bool spaceOverKey = false;

void gameO::init(IDirect3DDevice9* d3dDevice)
{
}

void gameO::cleanup()
{
}

void gameO::pause()
{
}

void gameO::resume()
{
}

void gameO::getInput(game* games, LPDIRECTINPUTDEVICE8& dInputKeyboardDevice)
{
	dInputKeyboardDevice->GetDeviceState(256, diKeys);
	if (diKeys[DIK_ESCAPE] & 0x80) {
		escOverKey = true;
	}
	if (diKeys[DIK_SPACE] & 0x80) {
		spaceOverKey = true;
	}
}

void gameO::update(game* games, int framesToUpdate, int& scoreOne, int& scoreTwo)
{
	if (escOverKey) {
		PostQuitMessage(0);

		escOverKey = false;
	}

	cout << "Player 1 score: " << scoreOne << " Player 2 score: " << scoreTwo << "\tPlay till 5. Press SPACE to continue." << endl;
	if (spaceOverKey) {
		spaceOverKey = false;
		games->changeState(gameS::instance());
	}

	//std::cout << "Game Over. Player " << result << " wins. Press Enter to Retart" << std::endl;
	/*return 3;*/
}

void gameO::render(game* games, IDirect3DDevice9* d3dDevice)
{
	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	d3dDevice->BeginScene();

	//	End the scene
	d3dDevice->EndScene();

	//	Present the back buffer to screen
	d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void gameO::playSound(game* games)
{
}