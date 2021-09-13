#include "game.h"
#include "gameW.h"
#include "menu.h"

gameW gameW::gameWinState;

bool escWinKey = false;
bool spaceWinKey = false;
bool player1Win = false;
bool player2Win = false;

void gameW::init(IDirect3DDevice9* d3dDevice)
{
	HRESULT hr;
	gameW1Text.fontSize = 55;
	gameW2Text.fontSize = 55;
	hr = D3DXCreateFont(d3dDevice, gameW1Text.fontSize, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Arial", &gameW1Text.d3dFont);
	testFail(hr, "gamW1Text");

	hr = D3DXCreateFont(d3dDevice, gameW2Text.fontSize, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Arial", &gameW2Text.d3dFont);
	testFail(hr, "gamW2Text");

	gameW1Text.rect = setRECT(300, 250, 558, 340);
	gameW1Text.content = "Player 1 Win !";
	gameW1Text.textSize = 14;

	gameW2Text.rect = setRECT(300, 250, 558, 340);
	gameW2Text.content = "Player 2 Win !";
	gameW1Text.textSize = 14;
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
		player1Win = true;
		//cout << "Player 1 wins! ";
	}
	else if (scoreTwo == 5) {
		player2Win = true;
		//cout << "Player 2 wins! ";
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
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	if (player1Win) {
		gameW1Text.d3dFont->DrawText(sprite, gameW1Text.content, gameW1Text.textSize, &gameW1Text.rect, 0, D3DCOLOR_XRGB(gameW1Text.red, gameW1Text.green, gameW1Text.blue));
	}
	else if (player2Win) {
		gameW2Text.d3dFont->DrawText(sprite, gameW2Text.content, gameW2Text.textSize, &gameW2Text.rect, 0, D3DCOLOR_XRGB(gameW2Text.red, gameW2Text.green, gameW2Text.blue));
	}
	
	//	End the scene
	d3dDevice->EndScene();

	//	Present the back buffer to screen
	d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void gameW::playSound(game* games)
{
}