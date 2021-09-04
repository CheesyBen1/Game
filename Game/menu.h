#pragma once
#include "gameState.h"

class menu :
    public gameState
{
public:
    menu();
    void getInput(LPDIRECTINPUTDEVICE8  dInputKeyboardDevice, BYTE diKeys[256]);
    bool update();
    void render();
    void playSound();
};

