#include "gameS.h"

const double pi = 3.14159265358979323846;

bool upKey = false;
bool downKey = false;

bool wKey = false;
bool sKey = false;

bool enterStartKey = false;
bool escStartKey = false;

int red = 255;
int green = 255;
int blue = 255;

int reset = 0;

D3DXVECTOR2 lineVertices[] = { D3DXVECTOR2((WINDOWWIDTH / 2) - 1,0), D3DXVECTOR2(WINDOWWIDTH / 2 - 1, WINDOWHEIGHT) };
D3DXVECTOR2 lineVertices2[] = { D3DXVECTOR2((WINDOWWIDTH / 2) + 1,0), D3DXVECTOR2(WINDOWWIDTH / 2 + 1, WINDOWHEIGHT) };

gameS::gameS()
{
}

void gameS::getInput(LPDIRECTINPUTDEVICE8 dInputKeyboardDevice, BYTE diKeys[256])
{
	dInputKeyboardDevice->GetDeviceState(256, diKeys);

	if (diKeys[DIK_UP] & 0x80)
	{
		upKey = true;
	}
	if (diKeys[DIK_DOWN] & 0x80)
	{
		downKey = true;
	}
	if (diKeys[DIK_W] & 0x80)
	{
		wKey = true;
	}
	if (diKeys[DIK_S] & 0x80)
	{
		sKey = true;
	}
	if (diKeys[DIK_RETURN] & 0x80) {
		enterStartKey = true;
	}
	if (diKeys[DIK_ESCAPE] & 0x80) {
		escStartKey = true;
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

int gameS::update(int framesToUpdate, int* counterP, player* playerP1, player* playerP2, ball* ballP, int* scoreOne, int* scoreTwo)
{
	player& player1 = *playerP1;
	player& player2 = *playerP2;
	ball& ball1 = *ballP;
	int& counter = *counterP;

	int& score1 = *scoreOne;
	int& score2 = *scoreTwo;

	if (reset == 0) {
		srand(time(NULL));

		ball1.rotation = ((rand() % 101) * 0.01) * (pi / 2) + pi / 4;
		if (rand() % 2 == 0) {
			ball1.rotation *= -1;
		}
		ball1.position = D3DXVECTOR2((WINDOWWIDTH / 2) - ball1.width / 2 * ball1.scaling.x, (WINDOWHEIGHT / 2) - ball1.height / 2 * ball1.scaling.y);
		player1.position = D3DXVECTOR2(50 - player1.width * player1.scaling.x, WINDOWHEIGHT / 2 - (player1.height / 2) * player1.scaling.x);
		player2.position = D3DXVECTOR2(WINDOWWIDTH - 50, WINDOWHEIGHT / 2 - (player2.height / 2) * player2.scaling.x);

		ball1.force.x = ball1.forceMagnitude * sin(ball1.rotation);
		ball1.force.y = ball1.forceMagnitude * -cos(ball1.rotation);

		ball1.velocity = ball1.force / ball1.mass;

		red = 255;
		green = 255;
		blue = 255;

		reset++;
	}

	if (escStartKey) {
		PostQuitMessage(0);

		escStartKey = false;
	}

	if (upKey) {
		if (player2.position.y >= 0) {
			player2.moveY -= player2.speed;
		}
		else {
			if (player2.position.y <= 0) {
				player2.position.y = 0;
			}
		}

		upKey = false;
	}

	if (downKey) {
		if (player2.position.y <= (WINDOWHEIGHT - player2.height * player2.scaling.x)) {
			player2.moveY += player2.speed;
		}
		else {
			if (player2.position.y <= (WINDOWHEIGHT - player2.height * player2.scaling.x)) {
				player2.position.y = (WINDOWHEIGHT - player2.height * player2.scaling.x);
			}
		}

		downKey = false;
	}
	if (wKey) {
		if (player1.position.y >= 0) {
			player1.moveY -= player1.speed;
		}
		else {
			if (player1.position.y <= 0) {
				player1.position.y = 0;
			}
		}

		wKey = false;
	}
	if (sKey) {
		if (player1.position.y <= (WINDOWHEIGHT - player1.height * player1.scaling.x)) {
			player1.moveY += player1.speed;
		}
		else {
			if (player1.position.y <= (WINDOWHEIGHT - player1.height * player1.scaling.x)) {
				player1.position.y = (WINDOWHEIGHT - player1.height * player1.scaling.x);
			}
		}

		sKey = false;
	}

	if (ball1.position.x < 0 || ball1.position.x > WINDOWWIDTH - ball1.width * ball1.scaling.x) {
		if (ball1.position.x < 0) {
			ball1.velocity = D3DXVECTOR2(0, 0);

			score2++;
			reset = 0;

			return 3;
		}
		if (ball1.position.x > WINDOWWIDTH - ball1.width * ball1.scaling.x) {
			ball1.velocity = D3DXVECTOR2(0, 0);

			score1++;
			reset = 0;

			return 3;
		}
	}

	if (ball1.position.y < 0 || ball1.position.y > WINDOWHEIGHT - ball1.height * ball1.scaling.y) {
		ball1.velocity.y *= -1;
		ball1.velocity *= 1.05;
		ball1.velocity.x *= 1.02;

		if (ball1.position.y < 0) {
			ball1.position.y = 0;
		}
		if (ball1.position.y > WINDOWHEIGHT - ball1.height * ball1.scaling.y) {
			ball1.position.y = WINDOWHEIGHT - ball1.height * ball1.scaling.y;
		}
	}

	if (checkCol(player1.position, 128, 32, ball1.position, 32, 32)) {
		ball1.position.x = player1.position.x + 33;
		ball1.velocity.x *= -1;
		ball1.velocity *= 1.05;
		ball1.velocity.y *= 1.02;

		red = 255;
		green = 0;
		blue = 0;

		if (pow(ball1.velocity.x, 2) > 1) {
			ball1.velocity *= 1.05;
		}
		else {
			ball1.velocity.x += 1;
		}
	}

	if (checkCol(player2.position, 128, 32, ball1.position, 32, 32)) {
		ball1.position.x = player2.position.x - 33;
		ball1.velocity.x *= -1;
		ball1.velocity *= 1.05;
		ball1.velocity.x *= 1.02;

		red = 0;
		green = 0;
		blue = 255;

		if (pow(ball1.velocity.x, 2) > 1) {
			ball1.velocity *= 1.05;
		}
		else {
			ball1.velocity.y += 1;
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

	/*cout << "ball1x: " << ball1.velocity.x << " ball1y: " << ball1.velocity.y << endl;*/

	cout << "rotation: " << ball1.rotation << endl;

	counter++;

	return 2;
}

void gameS::render(IDirect3DDevice9* d3dDevice, LPD3DXSPRITE* spriteP, LPD3DXLINE* lineP, player* playerP1, player* playerP2, ball* ballP)
{
	player& player1 = *playerP1;
	player& player2 = *playerP2;
	ball& ball1 = *ballP;
	LPD3DXSPRITE& sprite = *spriteP;
	LPD3DXLINE& line = *lineP;

	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

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

	sprite->Draw(ball1.texture, &ball1.rect, NULL, NULL, D3DCOLOR_XRGB(red, green, blue));

	sprite->End();

	//	End the scene
	d3dDevice->EndScene();

	//	Present the back buffer to screen
	d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void gameS::playSound()
{
}