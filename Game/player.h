#pragma once

#include <d3d9.h>
#include <d3dx9.h>

class player
{

public:
	player();
	D3DXVECTOR2 position;
	RECT rect;
	LPDIRECT3DTEXTURE9 texture = NULL;
	int height;
	int width;
	float rotation = 0.0f;
	D3DXVECTOR2 scaling = D3DXVECTOR2(1.0f, 1.0f);
	D3DXVECTOR2 spriteCenter = D3DXVECTOR2(width / 2, height / 2);

	int speed;

	int moveX = 0;
	int moveY = 0;

	

	
};

