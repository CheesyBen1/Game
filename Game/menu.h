#pragma once
#include "gameState.h"

class menu :
    public gameState
{
public:
    menu();
    void getInput(LPDIRECTINPUTDEVICE8 dInputKeyboardDevice1, BYTE diKeys[256]);
    void initialize();
    bool update(int framesToUpdate);
    void render();
    void playSound();
    void cleanUp();
};

