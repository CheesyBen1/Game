#include "menu.h"
#include "game.h"
#include "states.h"
#include "gameS.h"

bool enterMenuKey = false;
bool leftClick = false;
bool escMenuKey = false;
bool mouseHover = false;
int mousex = 400;
int mousey = 300;
D3DXVECTOR2 menuLineVertices[] = { D3DXVECTOR2(WINDOWWIDTH / 4, WINDOWHEIGHT / 3), D3DXVECTOR2(WINDOWWIDTH / 4, WINDOWWIDTH / 2),D3DXVECTOR2(WINDOWHEIGHT, WINDOWWIDTH / 2),D3DXVECTOR2(WINDOWHEIGHT, WINDOWWIDTH / 4), D3DXVECTOR2(WINDOWWIDTH / 4,  WINDOWWIDTH / 4) };

menu menu::menuState;

using namespace std;
void menu::init(IDirect3DDevice9* d3dDevice)
{
	HRESULT hr;

	hr = D3DXCreateLine(d3dDevice, &line);
	testFail(hr, "line");

	hr = D3DXCreateTextureFromFile(d3dDevice, "pointer.png", &mouseCursorTexture);
	testFail(hr, "Mouse Pointer");

	hr = D3DXCreateSprite(d3dDevice, &textSprite);

	hr = D3DXCreateFont(d3dDevice, 30, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Arial", &font);

	hr = D3DXCreateFont(d3dDevice, 25, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Arial", &startFont);

	hr = D3DXCreateFont(d3dDevice, 25, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Arial", &endFont);

	//Tittle text
	textRect.left = WINDOWWIDTH / 2.3;
	textRect.top = 0;
	textRect.right = WINDOWWIDTH;
	textRect.bottom = WINDOWWIDTH;

	//Start text
	startTextRect.left = WINDOWWIDTH / 2.3;
	startTextRect.top = WINDOWWIDTH / 3.2;
	startTextRect.right = WINDOWWIDTH;
	startTextRect.bottom = WINDOWWIDTH;

	//Quit text
	endTextRect.left = WINDOWWIDTH / 2.3;
	endTextRect.top = WINDOWHEIGHT / 1.9;
	endTextRect.right = WINDOWWIDTH;
	endTextRect.bottom = WINDOWWIDTH;

}

void menu::cleanup()
{
	/*mouseCursorTexture->Release();
	mouseCursorTexture = NULL;

	font->Release();
	font = NULL;

	startFont->Release();
	startFont = NULL;

	endFont->Release();
	endFont = NULL;

	line->Release();
	line = NULL;*/
}

void menu::pause()
{
}

void menu::resume()
{
}

void menu::getInput(game* games, LPDIRECTINPUTDEVICE8& dInputKeyboardDevice, LPDIRECTINPUTDEVICE8& dInputMouseDevice) {
	dInputKeyboardDevice->GetDeviceState(256, diKeys);
	if (diKeys[DIK_ESCAPE] & 0x80) 
	{
		escMenuKey = true;
	}
	if (diKeys[DIK_RETURN] & 0x80) 
	{
		enterMenuKey = true;
	}
	dInputMouseDevice->GetDeviceState(sizeof(mouseState), &mouseState);
	if (mouseClick[MK_LBUTTON] & 0x0001)
	{
		leftClick = true;
	}

	/*if (mouseClick[WM_MOUSEMOVE] & 0x0200)
	{
		mousex = (short)LOWORD(lParam);
		mousey = (short)HIWORD(lParam);

		mousePos.x = mousex;
		mousePos.y = mousey;

		cout << mousePos.x << " ," << mousePos.y << endl;
	}*/
}

void menu::update(game* games, int framesToUpdate, int& scoreOne, int& scoreTwo) {
	if (escMenuKey) {
		PostQuitMessage(0);

		escMenuKey = false;
	}

	if (enterMenuKey) {
		enterMenuKey = false;
		games->changeState(gameS::instance());
	}

	std::cout << "Menu (add UI, start exit buttons), Press Enter to start" << std::endl;
}
void menu::render(game* games, IDirect3DDevice9* d3dDevice) {
	ShowCursor(false);
	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	d3dDevice->BeginScene();
	textSprite->Begin(D3DXSPRITE_ALPHABLEND);
	textSprite->Draw(mouseCursorTexture, NULL, NULL, &mousePos, D3DCOLOR_XRGB(255, 255, 255));

	font->DrawText(textSprite, "Ping Pang", 9, &textRect, 0, D3DCOLOR_XRGB(255, 255, 255));
	startFont->DrawText(textSprite, "Start Game", 12, &startTextRect, 0, D3DCOLOR_XRGB(255, 255, 255));
	endFont->DrawText(textSprite, "Quit Game", 9, &endTextRect, 0, D3DCOLOR_XRGB(255, 255, 255));
	textSprite->End();

	line->Begin();
	line->Draw(menuLineVertices, 5, D3DCOLOR_XRGB(255, 255, 255));
	line->End();
	//	End the scene
	d3dDevice->EndScene();

	//	Present the back buffer to screen
	d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void menu::playSound(game* games) {
}