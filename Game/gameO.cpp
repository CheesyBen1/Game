#include "gameO.h"
#include "game.h"
#include "gameS.h"
#include "menu.h"

gameO gameO::gameOverState;

bool escOverKey = false;
bool spaceOverKey = false;
int tempscore1 = 0;
int tempscore = 0;

void gameO::init(IDirect3DDevice9* d3dDevice)
{
	HRESULT hr;

	hr = D3DXCreateSprite(d3dDevice, &sprite);

	gameO1Text.fontSize = 35;
	gameO1Text.fontStyle = "Arial";

	gameO2Text.fontSize = 35;
	gameO2Text.fontStyle = "Arial";

	player1TemScore.fontSize = 35;
	player1TemScore.fontStyle = "Arial";

	player2TemScore.fontSize = 35;
	player2TemScore.fontStyle = "Arial";

	conText.fontSize = 30;
	conText.fontStyle = "Arial";

	hr = D3DXCreateFont(d3dDevice, gameO1Text.fontSize, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, gameO1Text.fontStyle, &gameO1Text.d3dFont);
	testFail(hr, "gameO1Text");

	hr = D3DXCreateFont(d3dDevice, gameO2Text.fontSize, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, gameO2Text.fontStyle, &gameO2Text.d3dFont);
	testFail(hr, "gameO1Text");

	hr = D3DXCreateFont(d3dDevice, player1TemScore.fontSize, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, player1TemScore.fontStyle, &player1TemScore.d3dFont);
	testFail(hr, "player1TemScore");

	hr = D3DXCreateFont(d3dDevice, player2TemScore.fontSize, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, player2TemScore.fontStyle, &player2TemScore.d3dFont);
	testFail(hr, "player2TemScore");

	hr = D3DXCreateFont(d3dDevice, conText.fontSize, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Arial", &conText.d3dFont);
	testFail(hr, "continueText");

	gameO1Text.content = "Player 1 score:";
	gameO1Text.textSize = 15;

	gameO2Text.content = "Player 2 score:";
	gameO2Text.textSize = 15;

	player1TemScore.textSize = 2;

	player2TemScore.textSize = 2;

	conText.content = "Play till 5. Press SPACE to continue";
	conText.textSize = 36;

	gameO1Text.rect = setRECT(260, 200, 650, 500);
	gameO2Text.rect = setRECT(260, 400, 650, 500);
	player1TemScore.rect = setRECT(480, 200, 800, 600);
	player2TemScore.rect = setRECT(480, 400, 800, 600);
	conText.rect = setRECT(200, 550, 800, 660);
}

void gameO::cleanup()
{
	sprite->Release();
	sprite = NULL;

	gameO1Text.d3dFont->Release();
	gameO1Text.d3dFont = NULL;

	gameO2Text.d3dFont->Release();
	gameO2Text.d3dFont = NULL;

	player1TemScore.d3dFont->Release();
	player1TemScore.d3dFont = NULL;

	player2TemScore.d3dFont->Release();
	player2TemScore.d3dFont = NULL;

	conText.d3dFont->Release();
	conText.d3dFont = NULL;
}

void gameO::pause()
{
}

void gameO::resume()
{
}

void gameO::getInput(game* games, LPDIRECTINPUTDEVICE8& dInputKeyboardDevice, LPDIRECTINPUTDEVICE8& dInputMouseDevice)
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

	char buffer1[50];
	sprintf_s(buffer1, "%d", scoreOne);
	player1TemScore.content = buffer1;

	char buffer2[50];
	sprintf_s(buffer2, "%d", scoreTwo);
	player2TemScore.content = buffer2;

	cout << "Player 1 score: " << scoreOne << " Player 2 score: " << scoreTwo << "\tPlay till 5. Press SPACE to continue." << endl;
	if (spaceOverKey) {
		spaceOverKey = false;
		games->changeState(gameS::instance());
	}
}

void gameO::render(game* games, IDirect3DDevice9* d3dDevice)
{
	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	d3dDevice->BeginScene();

	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	gameO1Text.d3dFont->DrawText(sprite, gameO1Text.content, gameO1Text.textSize, &gameO1Text.rect, 0, D3DCOLOR_XRGB(gameO1Text.red, gameO1Text.green, gameO1Text.blue));
	player1TemScore.d3dFont->DrawText(sprite, player1TemScore.content, player1TemScore.textSize, &player1TemScore.rect, 0, D3DCOLOR_XRGB(player1TemScore.red, player1TemScore.green, player1TemScore.blue));
	gameO2Text.d3dFont->DrawText(sprite, gameO2Text.content, gameO2Text.textSize, &gameO2Text.rect, 0, D3DCOLOR_XRGB(gameO2Text.red, gameO2Text.green, gameO2Text.blue));
	player2TemScore.d3dFont->DrawText(sprite, player2TemScore.content, player2TemScore.textSize, &player2TemScore.rect, 0, D3DCOLOR_XRGB(player2TemScore.red, player2TemScore.green, player2TemScore.blue));
	conText.d3dFont->DrawText(sprite, conText.content, conText.textSize, &conText.rect, 0, D3DCOLOR_XRGB(conText.red, conText.green, conText.blue));

	sprite->End();

	//	End the scene
	d3dDevice->EndScene();

	//	Present the back buffer to screen
	d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void gameO::playSound(game* games)
{
}