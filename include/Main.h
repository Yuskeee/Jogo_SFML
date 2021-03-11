#ifndef _MAIN_H
#define _MAIN_H

#include "Graphics.h"
#include "Events.h"

#include <chrono>


class Game{

private:

    Graphics* gameGraphics;
    Events* gameEvents;
    //stateMachine* gameStateMachine;

    //apenas para testes--------------------------------------------------
    textID testText;
    float textPosX, textPosY;
    //------------------------------------------------------------------


public:
    Game();
    Game(Graphics* gameGraphics, Events* gameEvents);
    ~Game();

    void update(float dt);
    void render();

    void setGraphics(Graphics* gameGraphics);
    void setEvents(Events* gameEvents);
    //void setStateMachine(stateMachine* gameStateMachine);
};

#endif