#include "gameS.h"



bool upStartKey = false;
bool downStartKey = false;

bool wStartKey = false;
bool sStartKey = false;

bool enterStartKey = false;

D3DXVECTOR2 lineVertices[] = { D3DXVECTOR2((WINDOWWIDTH / 2) - 1,0), D3DXVECTOR2(WINDOWWIDTH / 2 - 1, WINDOWHEIGHT) };
D3DXVECTOR2 lineVertices2[] = { D3DXVECTOR2((WINDOWWIDTH / 2) + 1,0), D3DXVECTOR2(WINDOWWIDTH / 2 + 1, WINDOWHEIGHT) };

gameS::gameS(IDirect3DDevice9* d3dDeviceStart1, LPD3DXSPRITE* spriteStart1, LPDIRECTINPUTDEVICE8* dInputKeyboardDevice1, player* playerr1, player* playerr2, ball* balll1)
{
	
	
	

}

void gameS::getInput(LPDIRECTINPUTDEVICE8 dInputKeyboardDevice, BYTE diKeys[256])
{
	dInputKeyboardDevice->GetDeviceState(256, diKeys);

	if (diKeys[DIK_UP] & 0x80)
	{
		upStartKey = true;
	}
	if (diKeys[DIK_DOWN] & 0x80)
	{
		downStartKey = true;
	}
	if (diKeys[DIK_W] & 0x80)
	{
		wStartKey = true;
	}
	if (diKeys[DIK_S] & 0x80)
	{
		sStartKey = true;
	}
	if (diKeys[DIK_RETURN] & 0x80) {
		enterStartKey = true;
	}
}

int aPosXL, aPosXR, aPosYU, aPosYD, bPosXL, bPosXR, bPosYU, bPosYD;

bool checkCol(D3DXVECTOR2 aPos, int aHeight, int aWidth, D3DXVECTOR2 bPos, int bHeight, int bWidth) {

	aPosXL = aPos.x;
	aPosXR = aPos.x + aWidth;
	aPosYU = aPos.y;
	aPosYD = aPos.y + aHeight;

	bPosXL = bPos.x;
	bPosXR = bPos.x + bWidth;
	bPosYU = bPos.y;
	bPosYD = bPos.y + bHeight;


	if (aPosXR < bPosXL) {
		return false;
	}
	else if (aPosXL > bPosXR) {
		return false;
	}
	else if (aPosYD < bPosYU) {
		return false;
	}
	else if (aPosYU > bPosYD) {
		return false;
	}
	else {
		return true;
	}

}



bool gameS::update(int framesToUpdate, int* counterP , player* playerP1, player* playerP2, ball* ballP)
{
	player &player1 = *playerP1;
	player &player2 = *playerP2;
	ball &ball1 = *ballP;
	int counter = *counterP;
	/*if (enterStartKey) {
		if (gameStart == false) {


			ball1.rotation = random(6);
			ball1.position = D3DXVECTOR2((WINDOWWIDTH / 2) - ball1.width / 2 * ball1.scaling.x, (WINDOWHEIGHT / 2) - ball1.height / 2 * ball1.scaling.y);
			player1.position = D3DXVECTOR2(50 - player1.width * player1.scaling.x, WINDOWHEIGHT / 2 - (player1.height / 2) * player1.scaling.x);
			player2.position = D3DXVECTOR2(WINDOWWIDTH - 50, WINDOWHEIGHT / 2 - (player2.height / 2) * player2.scaling.x);

			ball1.force.x = ball1.forceMagnitude * sin(ball1.rotation);
			ball1.force.y = ball1.forceMagnitude * -cos(ball1.rotation);

			ball1.velocity = ball1.force / ball1.mass;

			gameStart = true;


		}
		enterStartKey = false;
	}*/

	//if (gameStart == true) {

		if (upStartKey) {

			if (player2.position.y >= 0) {
				player2.moveY -= player2.speed;
			}
			else {
				if (player2.position.y <= 0) {
					player2.position.y = 0;
				}
			}



			upStartKey = false;

		}

		if (downStartKey) {
			if (player2.position.y <= (WINDOWHEIGHT - player2.height * player2.scaling.x)) {
				player2.moveY += player2.speed;
			}
			else {
				if (player2.position.y <= (WINDOWHEIGHT - player2.height * player2.scaling.x)) {
					player2.position.y = (WINDOWHEIGHT - player2.height * player2.scaling.x);
				}
			}

			downStartKey = false;
		}
		if (wStartKey) {

			if (player1.position.y >= 0) {

				player1.moveY -= player1.speed;
			}
			else {
				if (player1.position.y <= 0) {
					player1.position.y = 0;
				}
			}


			wStartKey = false;
		}
		if (sStartKey) {

			if (player1.position.y <= (WINDOWHEIGHT - player1.height * player1.scaling.x)) {
				player1.moveY += player1.speed;
			}
			else {
				if (player1.position.y <= (WINDOWHEIGHT - player1.height * player1.scaling.x)) {
					player1.position.y = (WINDOWHEIGHT - player1.height * player1.scaling.x);
				}
			}


			sStartKey = false;
		}

		if (ball1.position.x < 0 || ball1.position.x > WINDOWWIDTH - ball1.width * ball1.scaling.x) {

			if (ball1.position.x < 0) {
				ball1.velocity = D3DXVECTOR2(0, 0);
				return false;
			}
			if (ball1.position.x > WINDOWWIDTH - ball1.width * ball1.scaling.x) {
				ball1.velocity = D3DXVECTOR2(0, 0);
				return false;
			}
		}

		if (ball1.position.y < 0 || ball1.position.y > WINDOWHEIGHT - ball1.height * ball1.scaling.y) {

			ball1.velocity.y *= -0.95;


			if (ball1.position.y < 0) {
				ball1.position.y = 0;
				ball1.velocity.y *= 1.05;
			}
			if (ball1.position.y > WINDOWHEIGHT - ball1.height * ball1.scaling.y) {
				ball1.position.y = WINDOWHEIGHT - ball1.height * ball1.scaling.y;
				ball1.velocity.y *= 1.05;
			}

		}


		if (checkCol(player1.position, 128, 32, ball1.position, 32, 32)) {
			ball1.position.x = player1.position.x + 33;
			ball1.velocity.x *= -1;
			if (pow(ball1.velocity.x, 2) > 1) {
				ball1.velocity.x *= 1.05;

			}
			else {
				ball1.velocity.x += 1;
			}


		}

		if (checkCol(player2.position, 128, 32, ball1.position, 32, 32)) {
			ball1.position.x = player2.position.x - 33;
			ball1.velocity.x *= -1;
			if (pow(ball1.velocity.x, 2) > 1) {
				ball1.velocity.x *= 1.05;

			}
			else {
				ball1.velocity.x += 1;
			}

		}

		if (pow(ball1.velocity.x * 10, 2) < 100) {
			if (ball1.velocity >= 0) {
				ball1.velocity.x += 10;

			}
			else {
				ball1.velocity.x -= 10;
			}
		}



	//}


	for (int frame = 0; frame < framesToUpdate; frame++) {

		//if (gameStart == true) {
			player1.position.y += player1.moveY;
			player1.moveY = 0;
			player2.position.y += player2.moveY;
			player2.moveY = 0;

			//ball1.velocity += ball1.acceleration;		
			ball1.position += ball1.velocity;
		//}

	}
	

	counter++;
}

void gameS::render(IDirect3DDevice9* d3dDevice, LPD3DXSPRITE* spriteP, LPD3DXLINE* lineP, player* playerP1, player* playerP2, ball* ballP)
{
	player &player1 = *playerP1;
	player &player2 = *playerP2;
	ball &ball1 = *ballP;
	LPD3DXSPRITE& sprite = *spriteP;
	LPD3DXLINE& line = *lineP;


	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 1.0f, 0);

	d3dDevice->BeginScene();


	line->Begin();
	line->Draw(lineVertices, 2, D3DCOLOR_XRGB(255, 255, 255));
	line->Draw(lineVertices2, 2, D3DCOLOR_XRGB(255, 255, 255));
	line->End();


	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	D3DXMATRIX mat;

	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &player1.scaling, &player1.spriteCenter, player1.rotation, &player1.position);
	sprite->SetTransform(&mat);

	sprite->Draw(player1.texture, &player1.rect, NULL, NULL, D3DCOLOR_XRGB(255, 0, 0));

	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &player2.scaling, &player2.spriteCenter, player2.rotation, &player2.position);
	sprite->SetTransform(&mat);

	sprite->Draw(player2.texture, &player2.rect, NULL, NULL, D3DCOLOR_XRGB(0, 0, 255));

	ball1.spriteCenter = D3DXVECTOR2(8, 8);

	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &ball1.scaling, &ball1.spriteCenter, ball1.rotation, &ball1.position);
	sprite->SetTransform(&mat);

	sprite->Draw(ball1.texture, &ball1.rect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));

	sprite->End();


	//	End the scene
	d3dDevice->EndScene();

	//	Present the back buffer to screen
	d3dDevice->Present(NULL, NULL, NULL, NULL);


}

void gameS::playSound()
{
}
