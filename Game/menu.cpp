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

	hr = D3DXCreateTextureFromFile(d3dDevice, "pointer.png", &cursor.texture);
	testFail(hr, "Mouse Pointer");

	hr = D3DXCreateSprite(d3dDevice, &sprite);
	titleText.fontSize = 30;
	startText.fontSize = 25;
	endText.fontSize = 25;

	titleText.fontStyle = "Arial";
	startText.fontStyle = "Arial";
	endText.fontStyle = "Arial";

	hr = D3DXCreateFont(d3dDevice, titleText.fontSize, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, titleText.fontStyle, &titleText.d3dFont);
	testFail(hr,"titleFont");

	hr = D3DXCreateFont(d3dDevice, startText.fontSize, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, startText.fontStyle, &startText.d3dFont);
	testFail(hr, "startFont");

	hr = D3DXCreateFont(d3dDevice, endText.fontSize, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, endText.fontStyle, &endText.d3dFont);
	testFail(hr, "endFont");

	//Tittle text
	titleText.content = "Ping Pang";
	titleText.textSize = 12;

	startText.content = "Start Game";
	startText.textSize = 10;

	endText.content = "Quit Game";
	endText.textSize = 10;

	titleText.rect = setRECT(347, 100, 800, 600);
	startText.rect = setRECT(347, 250, 465, 280);
	endText.rect = setRECT(347, 315, 458, 350);

	cursor.position3= D3DXVECTOR3(400, 300, 0);

	//textRect.left = WINDOWWIDTH / 2.3;
	//textRect.top = 0;
	//textRect.right = WINDOWWIDTH;
	//textRect.bottom = WINDOWWIDTH;

	////Start text
	//startTextRect.left = WINDOWWIDTH / 2.3;
	//startTextRect.top = WINDOWWIDTH / 3.2;
	//startTextRect.right = WINDOWWIDTH;
	//startTextRect.bottom = WINDOWWIDTH;

	////Quit text
	//endTextRect.left = WINDOWWIDTH / 2.3;
	//endTextRect.top = WINDOWHEIGHT / 1.9;
	//endTextRect.right = WINDOWWIDTH;
	//endTextRect.bottom = WINDOWWIDTH;

}

void menu::cleanup()
{
	sprite->Release();
	sprite = NULL;

	cursor.texture->Release();
	cursor.texture = NULL;

	titleText.d3dFont->Release();
	titleText.d3dFont = NULL;

	startText.d3dFont->Release();
	startText.d3dFont = NULL;

	endText.d3dFont->Release();
	endText.d3dFont = NULL;

	line->Release();
	line = NULL;
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
	if (BUTTONDOWN(mouseState, 0))
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
	if (cursor.position3.x < 0) {
		cursor.position3.x = 0;
	}
	if (cursor.position3.x > 760) {
		cursor.position3.x = 760;
	}
	if (cursor.position3.y > 567) {
		cursor.position3.y = 567;
	}
	if (cursor.position3.y < 0) {
		cursor.position3.y = 0;
	}

	cursor.position3.x += mouseState.lX;
	cursor.position3.y += mouseState.lY;
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

	if(leftClick){

		leftClick = false;

		if(cursorCol(cursor, startText)){
			games->changeState(gameS::instance());
		}
		else if(cursorCol(cursor, endText)){
			PostQuitMessage(0);
		}
		
	}

	if(cursorCol(cursor, startText)){
	
		startText.blue = 0;
	}else{
		startText.blue = 255;
	}
	if(cursorCol(cursor, endText)){
		
		endText.blue = 0;
	}else{
		endText.blue = 255;
	}

	//if (BUTTONDOWN(mouseState, 0) && (mousePos.y > startTextRect.top && mousePos.y <startTextRect.bottom && mousePos.x>startTextRect.left && mousePos.x < startTextRect.right)) {
	//	//cout << "click" << endl;
	//	leftClick = false;

	//}

	//if (BUTTONDOWN(mouseState, 0) && (mousePos.y > endTextRect.top && mousePos.y <endTextRect.bottom && mousePos.x>endTextRect.left && mousePos.x < endTextRect.right)) {
	//	cout << "click" << endl;
	//	leftClick = false;

	//}

	cout << "mouse X" << cursor.position3.x << "mouse Y" << cursor.position3.y << endl;

	//std::cout << "Menu (add UI, start exit buttons), Press Enter to start" << std::endl;
}
void menu::render(game* games, IDirect3DDevice9* d3dDevice) {
	//ShowCursor(false);
	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	d3dDevice->BeginScene();

	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	sprite->Draw(cursor.texture, NULL, NULL, &cursor.position3, D3DCOLOR_XRGB(255, 255, 255));

	titleText.d3dFont->DrawText(sprite, titleText.content, titleText.textSize, &titleText.rect, 0, D3DCOLOR_XRGB(titleText.red, titleText.green, titleText.blue));
	startText.d3dFont->DrawText(sprite, startText.content, startText.textSize, &startText.rect, 0, D3DCOLOR_XRGB(startText.red, startText.green, startText.blue));
	endText.d3dFont->DrawText(sprite, endText.content, endText.textSize, &endText.rect, 0, D3DCOLOR_XRGB(endText.red, endText.green, endText.blue));

	sprite->End();

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