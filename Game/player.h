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
	D3DXVECTOR2 spriteCenter = D3DXVECTOR2(width * 0.5, height * 0.5);

	int speed;

	int spriteFrame = 0;

	D3DXVECTOR2 move = D3DXVECTOR2(0.0f, 0.0f);
};
