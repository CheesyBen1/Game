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
	hr = D3DXCreateSprite(d3dDevice, &sprite);
	testFail(hr, "sprite");

	gameW1Text.fontSize = 50;
	gameOverText.fontSize = 60;
	toMenuText.fontSize = 30;

	hr = D3DXCreateFont(d3dDevice, gameW1Text.fontSize, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Arial", &gameW1Text.d3dFont);
	testFail(hr, "gamW1Text");

	hr = D3DXCreateFont(d3dDevice, gameOverText.fontSize, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Arial", &gameOverText.d3dFont);
	testFail(hr, "gameOverText");

	hr = D3DXCreateFont(d3dDevice, toMenuText.fontSize, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Arial", &toMenuText.d3dFont);
	testFail(hr, "toMenuText");

	gameW1Text.rect = setRECT(280, 250, 650, 380);
	gameW1Text.textSize = 14;

	gameOverText.rect = setRECT(280, 100, 800, 600);
	gameOverText.content = "Game Over";
	gameOverText.textSize = 9;

	toMenuText.rect = setRECT(220, 550, 800, 660);
	toMenuText.content = "Press SPACE to go back to Menu";
	toMenuText.textSize = 30;
}

void gameW::cleanup()
{
	sprite->Release();
	sprite = NULL;

	gameW1Text.d3dFont->Release();
	gameW1Text.d3dFont = NULL;

	gameOverText.d3dFont->Release();
	gameOverText.d3dFont = NULL;

	toMenuText.d3dFont->Release();
	toMenuText.d3dFont = NULL;
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

	if (spaceWinKey) {
		spaceWinKey = false;
		scoreOne = 0;
		scoreTwo = 0;
		games->changeState(menu::instance());
	}

	if (scoreOne == 5) {
		player1Win = true;
		gameW1Text.content = "Player 1 Wins!";
	}
	else if (scoreTwo == 5) {
		player2Win = true;
		gameW1Text.content = "player 2 Wins!";
	}
}

void gameW::render(game* games, IDirect3DDevice9* d3dDevice)
{
	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	d3dDevice->BeginScene();

	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	gameOverText.d3dFont->DrawText(sprite, gameOverText.content, gameOverText.textSize, &gameOverText.rect, 0, D3DCOLOR_XRGB(gameOverText.red, gameOverText.green, gameOverText.blue));
	gameW1Text.d3dFont->DrawText(sprite, gameW1Text.content, gameW1Text.textSize, &gameW1Text.rect, 0, D3DCOLOR_XRGB(gameW1Text.red, gameW1Text.green, gameW1Text.blue));
	toMenuText.d3dFont->DrawText(sprite, toMenuText.content, toMenuText.textSize, &toMenuText.rect, 0, D3DCOLOR_XRGB(toMenuText.red, toMenuText.green, toMenuText.blue));

	sprite->End();

	//	End the scene
	d3dDevice->EndScene();

	//	Present the back buffer to screen
	d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void gameW::playSound(game* games)
{
}