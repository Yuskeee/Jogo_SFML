#ifndef _MAIN_H
#define _MAIN_H

#include "Graphics.h"
#include "Events.h"
#include "GameStateMachine.h"

class Game{

private:

    Graphics* gameGraphics;
    Events* gameEvents;
    StateMachine* gameStateMachine;



public:
    Game();
    Game(Graphics* gameGraphics, Events* gameEvents);
    ~Game();

    void update(float dt);
    void render();

    void setGraphics(Graphics* gameGraphics);
    void setEvents(Events* gameEvents);
    void setStateMachine(StateMachine* gameStateMachine);
};

#endif