//	Ask the compiler to include minimal header files for our program.
#define WIN32_LEAN_AND_MEAN
#define _USE_MATH_DEFINES

#include <cmath>
#include <Windows.h>
#include <Windowsx.h>
#include <iostream>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

#include "FrameTimer.h"

#include "player.h"
#include "ball.h"

#include "menu.h"
#include "gameS.h"
#include "gameO.h"

#include "game.h"
#include "states.h"

//
//#define WINDOW_CLASS_NAME "Ping Pang"
//#define WINDOWWIDTH 800
//#define WINDOWHEIGHT 600

using namespace std;

//float random(int i) {
//	srand((unsigned)time(NULL));
//	return rand() % i + 1.28;
//}
//
//void initialize() {
//	hr = D3DXCreateSprite(d3dDevice, &sprite);
//	testFail(hr);
//
//	ball1.mass = 10;
//	ball1.forceMagnitude = 100;
//
//	//ball1.rotation = random(6);
//
//	player1.speed = 20;
//	player2.speed = 20;
//
//	player1.height = 256;
//	player1.width = 32;
//
//	player2.height = 256;
//	player2.width = 32;
//
//	ball1.height = 64;
//	ball1.width = 64;
//
//	//ball1.velocity = ball1.acceleration;
//
//	/*ball1.force.x = ball1.forceMagnitude * sin(ball1.rotation);
//	ball1.force.y = ball1.forceMagnitude * -cos(ball1.rotation);
//
//	ball1.velocity = ball1.force / ball1.mass;*/
//
//	//default position///
//	///
//	///
//
//	player1.scaling = D3DXVECTOR2(0.5f, 0.5f);
//	player1.position = D3DXVECTOR2(50 - player1.width * player1.scaling.x, WINDOWHEIGHT / 2 - (player1.height / 2) * player1.scaling.x);
//
//	player2.scaling = D3DXVECTOR2(0.5f, 0.5f);
//	player2.position = D3DXVECTOR2(WINDOWWIDTH - 50, WINDOWHEIGHT / 2 - (player2.height / 2) * player2.scaling.x);
//
//	ball1.scaling = D3DXVECTOR2(0.25f, 0.25f);
//	ball1.position = D3DXVECTOR2((WINDOWWIDTH / 2) - ball1.width / 2 * ball1.scaling.x, (WINDOWHEIGHT / 2) - ball1.height / 2 * ball1.scaling.y);
//
//	//RECT//
//	////////////////
//	/////////////////
//
//	player2.rect = setRECT(0, 0, 32, 256);
//	player1.rect = setRECT(32, 0, 64, 256);
//	ball1.rect = setRECT(0, 0, 64, 64);
//
//	//sprites//
//	///////////////////////
//	////////////////////////
//
//	hr = D3DXCreateTextureFromFile(d3dDevice, "bars.png", &player1.texture);
//	testFail(hr);
//
//	hr = D3DXCreateTextureFromFile(d3dDevice, "bars.png", &player2.texture);
//	testFail(hr);
//
//	hr = D3DXCreateTextureFromFile(d3dDevice, "ball.png", &ball1.texture);
//	testFail(hr);
//
//	hr = D3DXCreateLine(d3dDevice, &line);
//	testFail(hr);
//
//	//	Create texture. Study the documentation.
//}

//double spriteHeight, spriteWidth;
//
//RECT spriteOutputCycle(RECT& spriteRect, int textureWidth, int textureHeight, int col, int row, int maxFrames, int& frameCount) {
//	spriteHeight = textureHeight / row;
//	spriteWidth = textureWidth / col;
//
//	if (counter % 1 == 0) {
//		spriteRect.top = frameCount / row * spriteHeight;
//		spriteRect.bottom = spriteRect.top + spriteHeight;
//
//		spriteRect.left = frameCount % col * spriteWidth;
//		spriteRect.right = spriteRect.left + spriteWidth;
//
//		frameCount++;
//
//		if (frameCount >= maxFrames) {
//			frameCount = 0;
//		}
//	}
//
//	return spriteRect;
//}
//
//RECT charSpriteOutputCycle(RECT& spriteRect, int textureWidth, int textureHeight, int col, int row, int charState, int maxFrames, int& frameCount) {
//	spriteHeight = textureHeight / row;
//	spriteWidth = textureWidth / col;
//
//	if (counter % 1 == 0) {
//		spriteRect.top = charState * spriteHeight;
//		spriteRect.bottom = spriteRect.top + spriteHeight;
//
//		spriteRect.left = frameCount % col * spriteWidth;
//		spriteRect.right = spriteRect.left + spriteWidth;
//
//		frameCount++;
//
//		if (frameCount >= maxFrames) {
//			frameCount = 0;
//		}
//	}
//
//	return spriteRect;
//}

//	use int main if you want to have a console to print out message
//int main()

//	use WinMain if you don't want the console
//hInstance = ID number of the instance of this window
//hPrevInstance = ID number of the instance of the PARENT of this window (OBSOLETE)
//lp CmdLine = POINTER to a command line string
//nShowCmd = style

int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	game pang;

	pang.init("Ping Pang", 800, 600);
	//pang.initGame();

	pang.changeState(menu::instance());

	while (pang.running()) {
		/*
		Game ->
		GetInput()
		Update()
		Render()
		PlaySound()
		*/

		pang.getInput();
		pang.update();
		pang.render();
		pang.playSound();
	}

	//gameState.getInput(dInputKeyboardDevice, diKeys);
	//gameState.update(myTimer.framesToUpdate(), &player1, &player2, &ball1, &score1, &score2);
	//gameState.render(d3dDevice, &sprite, &line, &player1, &player2, &ball1);
	//gameState.playSound();
	/*switch (gameStage) {
	case 1: {
		start.getInput(dInputKeyboardDevice, diKeys);
		gameStage = start.update(myTimer.framesToUpdate());
		start.render(d3dDevice);
		start.playSound();
		break;
	}
	case 2: {
		startGame.getInput(dInputKeyboardDevice, diKeys);
		gameStage = startGame.update(myTimer.framesToUpdate(), &counter, &player1, &player2, &ball1, &score1, &score2);
		startGame.render(d3dDevice, &sprite, &line, &player1, &player2, &ball1);
		startGame.playSound();
		break;
	}
	case 3: {
		gameOver.getInput(dInputKeyboardDevice, diKeys);
		gameStage = gameOver.update(myTimer.framesToUpdate(), &score1, &score2);
		gameOver.render(d3dDevice);
		gameOver.playSound();
		break;
	}
	default: {
		cout << "No game??? How it skip the others, or maybe return gameStage error. Go check :)" << endl;
		break;
	}
	}
}

//cleanupDirectX();

////	Free up the memory.
//cleanupWindow();
pang.cleanup();

return 0;*/
}