#pragma once
#include "gameState.h"
class gameStart :
    public gameState
{
public:
	
	void GetInput();
	void Update();
	void Render();
	void PlaySound();
};

