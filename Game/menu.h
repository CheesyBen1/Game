#pragma once
#include "gameState.h"

class menu :
    public gameState
{
public:
    menu();
    void getInput(LPDIRECTINPUTDEVICE8 dInputKeyboardDevice1, BYTE diKeys[256]);
    bool update(int framesToUpdate);
    void render();
    void playSound();
};

