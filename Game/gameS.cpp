#include "gameS.h"
#include "gameO.h"
#include "gameW.h"

const double pi = 3.14159265358979323846;

bool upKey = false;
bool downKey = false;
bool leftKey = false;
bool rightKey = false;

bool wKey = false;
bool aKey = false;
bool sKey = false;
bool dKey = false;

bool enterStartKey = false;
bool escStartKey = false;

int red = 255;
int green = 255;
int blue = 255;

int reset = 0;

D3DXVECTOR2 lineVertices[] = { D3DXVECTOR2((WINDOWWIDTH / 2) - 1,0), D3DXVECTOR2(WINDOWWIDTH / 2 - 1, WINDOWHEIGHT) };
D3DXVECTOR2 lineVertices2[] = { D3DXVECTOR2((WINDOWWIDTH / 2) + 1,0), D3DXVECTOR2(WINDOWWIDTH / 2 + 1, WINDOWHEIGHT) };

gameS gameS::gameStartState;

using namespace std;

void gameS::init(IDirect3DDevice9* d3dDevice)
{
	HRESULT hr;

	hr = D3DXCreateSprite(d3dDevice, &sprite);
	testFail(hr, "sprite");

	ball1.mass = 5;
	ball1.forceMagnitude = 1;

	player1.mass = 10;
	player1.forceMagnitude = 1;
	player1.rotationSpeed = 0.08;

	player2.mass = 10;
	player2.forceMagnitude = 1;
	player2.rotationSpeed = 0.08;

	//ball1.rotation = random(6);

	//player1.speed = 20;
	//player2.speed = 20;

	player1.height = 64;
	player1.width = 64;

	player2.height = 64;
	player2.width = 64;

	ball1.height = 64;
	ball1.width = 64;

	//ball1.velocity = ball1.acceleration;

	/*ball1.force.x = ball1.forceMagnitude * sin(ball1.rotation);
	ball1.force.y = ball1.forceMagnitude * -cos(ball1.rotation);

	ball1.velocity = ball1.force / ball1.mass;*/

	ball1.velocity = D3DXVECTOR2(0, 0);
	player1.velocity = D3DXVECTOR2(0, 0);
	player2.velocity = D3DXVECTOR2(0, 0);

	//default position///
	///
	///
	///

	ball1.scaling = D3DXVECTOR2(1.0f, 1.0f);
	player1.scaling = D3DXVECTOR2(1.0f, 1.0f);
	player2.scaling = D3DXVECTOR2(1.0f, 1.0f);

	ball1.position = D3DXVECTOR2((WINDOWWIDTH / 2) - ball1.width / 2 * ball1.scaling.x, (WINDOWHEIGHT / 2) - ball1.height / 2 * ball1.scaling.y);

	player1.position = D3DXVECTOR2(150 - player1.width * player1.scaling.x, WINDOWHEIGHT / 2 - (player1.height / 2) * player1.scaling.x);
	player2.position = D3DXVECTOR2(WINDOWWIDTH - 150, WINDOWHEIGHT / 2 - (player2.height / 2) * player2.scaling.x);

	ball1.radius = ball1.height * ball1.scaling.y * 0.5;

	player1.radius = player1.height * player1.scaling.y * 0.5;
	player2.radius = player2.height * player2.scaling.y * 0.5;

	player1.friction = player2.friction = 0.01;
	ball1.friction = 0.01;

	player2.rotation = pi * 1.5;
	player1.rotation = pi * 0.5;

	//RECT//
	////////////////
	/////////////////

	player2.rect = setRECT(0, 0, 64, 64);
	player1.rect = setRECT(0, 0, 64, 64);
	ball1.rect = setRECT(0, 0, 64, 64);

	//sprites//
	///////////////////////
	////////////////////////

	hr = D3DXCreateTextureFromFile(d3dDevice, "ballarrow.png", &player1.texture);
	testFail(hr, "player1 texture");

	hr = D3DXCreateTextureFromFile(d3dDevice, "ballarrow.png", &player2.texture);
	testFail(hr, "player2 texture");

	hr = D3DXCreateTextureFromFile(d3dDevice, "ballarrow.png", &ball1.texture);
	testFail(hr, "ball texture");

	hr = D3DXCreateLine(d3dDevice, &line);
	testFail(hr, "line");
}

void gameS::cleanup()
{
	sprite->Release();
	sprite = NULL;

	player1.texture->Release();
	player1.texture = NULL;

	player2.texture->Release();
	player2.texture = NULL;

	ball1.texture->Release();
	ball1.texture = NULL;

	line->Release();
	line = NULL;
}

void gameS::pause()
{
}

void gameS::resume()
{
}

void gameS::getInput(game* games, LPDIRECTINPUTDEVICE8& dInputKeyboardDevice)
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
	if (diKeys[DIK_LEFT] & 0x80)
	{
		leftKey = true;
	}
	if (diKeys[DIK_RIGHT] & 0x80)
	{
		rightKey = true;
	}
	if (diKeys[DIK_W] & 0x80)
	{
		wKey = true;
	}
	if (diKeys[DIK_S] & 0x80)
	{
		sKey = true;
	}
	if (diKeys[DIK_A] & 0x80)
	{
		aKey = true;
	}
	if (diKeys[DIK_D] & 0x80)
	{
		dKey = true;
	}
	if (diKeys[DIK_RETURN] & 0x80) {
		enterStartKey = true;
	}
	if (diKeys[DIK_ESCAPE] & 0x80) {
		escStartKey = true;
	}
}

float aPosXL, aPosXR, aPosYU, aPosYD, bPosXL, bPosXR, bPosYU, bPosYD;

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

void colBox(ball& thing, float left, float right, float top, float bottom) {
	if (thing.position.y<top || thing.position.y>(bottom - thing.radius * 2))
	{
		thing.velocity.y *= -1;

		if (thing.position.y < top) {
			thing.position.y = top;
		}
		if (thing.position.y > bottom - thing.radius * 2) {
			thing.position.y = bottom - thing.radius * 2;
		}
	}

	if (thing.position.x < left || thing.position.x >(right - thing.radius * 2))
	{
		thing.velocity.x *= -1;

		if (thing.position.x < left) {
			thing.position.x = left;
		}
		if (thing.position.x > right - thing.radius * 2) {
			thing.position.x = right - thing.radius * 2;
		}
	}
}

void colCircle(ball& thing, ball& thingHit) {
	D3DXVECTOR2 distance = thing.position - thingHit.position;
	D3DXVECTOR2 surfaceNormal;
	D3DXVECTOR2 reflectionVector;
	if ((thing.radius + thingHit.radius) > D3DXVec2Length(&distance)) {
		D3DXVec2Normalize(&surfaceNormal, &distance);

		float overlap = thing.radius + thingHit.radius - D3DXVec2Length(&distance);

		if ((thing.radius + thingHit.radius) > D3DXVec2Length(&distance)) {
			D3DXVECTOR2 overlapVector;
			overlapVector = surfaceNormal * overlap;
			thing.position += overlapVector;
		}

		reflectionVector = thing.velocity - 2 * (D3DXVec2Dot(&thing.velocity, &surfaceNormal) * surfaceNormal);

		thingHit.velocity = thing.velocity / ((thing.mass + thingHit.mass) / thing.mass);
		thing.velocity = reflectionVector / ((thing.mass + thingHit.mass) / thingHit.mass);
	}
}

void cycleSpriteFrame(ball& thing, int col, int row, int maxFrames) {
	//float spriteHeight = textureHeight / row;
	//float spriteWidth = textureWidth / col;

	thing.rect.top = thing.spriteFrame / row * thing.height;
	thing.rect.bottom = thing.rect.top + thing.height;

	thing.rect.left = thing.spriteFrame % col * thing.width;
	thing.rect.right = thing.rect.left + thing.width;

	thing.spriteFrame++;

	if (thing.spriteFrame >= maxFrames) {
		thing.spriteFrame = 0;
	}
}

int countdown = 0;

void gameS::update(game* games, int framesToUpdate, int& scoreOne, int& scoreTwo)
{
	//if (reset == 0) {
	//	srand(time(NULL));

	//	//ball1.rotation = ((rand() % 101) * 0.01) * (pi / 2) + pi / 4;
	//	//if (ball1.rotation >= (pi / 2 - pi / 16) && ball1.rotation <= (pi / 2 + pi / 16)) {
	//	//	if (rand() % 2 == 0) {
	//	//		ball1.rotation += pi / 16;
	//	//	}
	//	//	else {
	//	//		ball1.rotation -= pi / 16;
	//	//	}
	//	//}
	//	//if (rand() % 2 == 0) {
	//	//	ball1.rotation *= -1;
	//	//}

	//	//ball1.velocity = ball1.force / ball1.mass;

	//	red = 255;
	//	green = 255;
	//	blue = 255;

	//	reset++;
	//}

	ball1.force.x = ball1.forceMagnitude * sin(ball1.rotation);
	ball1.force.y = ball1.forceMagnitude * -cos(ball1.rotation);

	ball1.acceleration = ball1.force / ball1.mass;

	player1.force.x = player1.forceMagnitude * sin(player1.rotation);
	player1.force.y = player1.forceMagnitude * -cos(player1.rotation);

	player1.acceleration = player1.force / player1.mass;

	player2.force.x = player2.forceMagnitude * sin(player2.rotation);
	player2.force.y = player2.forceMagnitude * -cos(player2.rotation);

	player2.acceleration = player2.force / player2.mass;

	if (escStartKey) {
		PostQuitMessage(0);

		escStartKey = false;
	}

	if (upKey) {
		player2.velocity += player2.acceleration;

		upKey = false;
	}

	if (downKey) {
		//if (player2.position.y <= (WINDOWHEIGHT - player2.height * player2.scaling.x)) {
		//	/*	player2.moveY += player2.speed;*/
		//}
		//else {
		//	if (player2.position.y <= (WINDOWHEIGHT - player2.height * player2.scaling.x)) {
		//		player2.position.y = (WINDOWHEIGHT - player2.height * player2.scaling.x);
		//	}
		//}

		player2.velocity -= player2.acceleration;

		downKey = false;
	}

	if (leftKey) {
		player2.rotationAdd -= player2.rotationSpeed;

		leftKey = false;
	}

	if (rightKey) {
		player2.rotationAdd += player2.rotationSpeed;

		rightKey = false;
	}

	if (wKey) {
		//if (player1.position.y >= 0) {
		//	/*player1.moveY -= player1.speed;*/
		//}
		//else {
		//	if (player1.position.y <= 0) {
		//		player1.position.y = 0;
		//	}
		//}
		player1.velocity += player1.acceleration;

		wKey = false;
	}
	if (sKey) {
		//if (player1.position.y <= (WINDOWHEIGHT - player1.height * player1.scaling.x)) {
		//	/*player1.moveY += player1.speed;*/
		//}
		//else {
		//	if (player1.position.y <= (WINDOWHEIGHT - player1.height * player1.scaling.x)) {
		//		player1.position.y = (WINDOWHEIGHT - player1.height * player1.scaling.x);
		//	}
		//}

		player1.velocity -= player1.acceleration;

		sKey = false;
	}
	if (aKey) {
		player1.rotationAdd -= player1.rotationSpeed;

		aKey = false;
	}
	if (dKey) {
		player1.rotationAdd += player1.rotationSpeed;

		dKey = false;
	}

	colBox(player2, WINDOWWIDTH / 2, WINDOWWIDTH, 0, WINDOWHEIGHT);
	colBox(player1, 0, WINDOWWIDTH / 2, 0, WINDOWHEIGHT);

	colCircle(player1, ball1);
	colCircle(player2, ball1);

	if (ball1.position.x < 0 || ball1.position.x > WINDOWWIDTH - ball1.width * ball1.scaling.x) {
		if (ball1.position.x < 0) {
			ball1.velocity = D3DXVECTOR2(0, 0);

			scoreTwo++;
			reset = 0;

			if (scoreOne != 5 && scoreOne != 5) {
				games->changeState(gameO::instance());
			}
			else {
				games->changeState(gameW::instance());
			}
		}
		if (ball1.position.x > WINDOWWIDTH - ball1.width * ball1.scaling.x) {
			ball1.velocity = D3DXVECTOR2(0, 0);

			scoreOne++;
			reset = 0;

			games->changeState(gameO::instance());
		}
	}

	if (ball1.position.y < 0 || ball1.position.y > WINDOWHEIGHT - ball1.height * ball1.scaling.y) {
		ball1.velocity.y *= -1;
		/*	ball1.velocity *= 1.05;
			ball1.velocity.x *= 1.07;*/

		if (ball1.position.y < 0) {
			ball1.position.y = 0;
		}
		if (ball1.position.y > WINDOWHEIGHT - ball1.height * ball1.scaling.y) {
			ball1.position.y = WINDOWHEIGHT - ball1.height * ball1.scaling.y;
		}
	}

	//if (checkCol(player1.position, 128, 32, ball1.position, 32, 32)) {
	//	ball1.position.x = player1.position.x + 33;
	//	ball1.velocity.x *= -1;
	//	ball1.velocity *= 1.05;
	//	ball1.velocity.y *= 1.07;

	//	red = 255;
	//	green = 0;
	//	blue = 0;

	//	if (pow(ball1.velocity.x, 2) > 1) {
	//		ball1.velocity *= 1.05;
	//	}
	//	else {
	//		ball1.velocity.x += 1;
	//	}
	//}

	//if (checkCol(player2.position, 128, 32, ball1.position, 32, 32)) {
	//	ball1.position.x = player2.position.x - 33;
	//	ball1.velocity.x *= -1;
	//	ball1.velocity *= 1.05;
	//	ball1.velocity.x *= 1.02;

	//	red = 0;
	//	green = 0;
	//	blue = 255;

	//	if (pow(ball1.velocity.x, 2) > 1) {
	//		ball1.velocity *= 1.05;
	//	}
	//	else {
	//		ball1.velocity.y += 1;
	//	}
	//}

	//if (pow(ball1.velocity.x * 10, 2) < 100) {
	//	if (ball1.velocity >= 0) {
	//		ball1.velocity.x += 10;
	//	}
	//	else {
	//		ball1.velocity.x -= 10;
	//	}
	//}

	//}

	for (int frame = 0; frame < framesToUpdate; frame++) {
		//if (gameStart == true) {
		/*player1.position.y += player1.moveY;
		player1.moveY = 0;
		player2.position.y += player2.moveY;
		player2.moveY = 0;*/

		//ball1.velocity += ball1.acceleration;
		/*ball1.position += ball1.velocity;*/
		//}

		cycleSpriteFrame(player2, 2, 2, 2);
		cycleSpriteFrame(player1, 2, 2, 2);

		player2.rotation += player2.rotationAdd;
		player2.rotationAdd = 0;

		player1.rotation += player1.rotationAdd;
		player1.rotationAdd = 0;

		player2.velocity *= (1 - player2.friction);
		player2.position += player2.velocity;

		player1.velocity *= (1 - player1.friction);
		player1.position += player1.velocity;

		ball1.velocity *= (1 - ball1.friction);
		ball1.position += ball1.velocity;
	}

	/*cout << "ball1x: " << ball1.velocity.x << " ball1y: " << ball1.velocity.y << endl;*/

	/*return 2;*/
}

void gameS::render(game* games, IDirect3DDevice9* d3dDevice)
{
	//player& player1 = *playerP1;
	//player& player2 = *playerP2;
	//ball& ball1 = *ballP;
	//LPD3DXSPRITE& sprite = *spriteP;
	//LPD3DXLINE& line = *lineP;

	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	d3dDevice->BeginScene();

	line->Begin();
	line->Draw(lineVertices, 2, D3DCOLOR_XRGB(255, 255, 255));
	line->Draw(lineVertices2, 2, D3DCOLOR_XRGB(255, 255, 255));
	line->End();

	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	D3DXMATRIX mat;

	player1.spriteCenter.x = player1.width * player1.scaling.x * 0.5;
	player1.spriteCenter.y = player1.height * player1.scaling.y * 0.5;
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &player1.scaling, &player1.spriteCenter, player1.rotation, &player1.position);
	sprite->SetTransform(&mat);

	sprite->Draw(player1.texture, &player1.rect, NULL, NULL, D3DCOLOR_XRGB(255, 0, 0));

	player2.spriteCenter.x = player2.width * player2.scaling.x * 0.5;
	player2.spriteCenter.y = player2.height * player2.scaling.y * 0.5;
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

void gameS::playSound(game* games)
{
}