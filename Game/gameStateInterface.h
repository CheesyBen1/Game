#pragma once
class gameStateInterface
{
public:
	virtual void getInput();
	virtual void update();
	virtual void render();
	virtual void playSound();
};
