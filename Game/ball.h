#pragma once
#include "player.h"

class ball : public player
{

public:
	
	float mass;
	D3DXVECTOR2 velocity;
	D3DXVECTOR2 acceleration;
	D3DXVECTOR2 force;
	float forceMagnitude = 1;
};

