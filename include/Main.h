#ifndef _MAIN_H
#define _MAIN_H

#include "Graphics.h"
#include "Events.h"
#include "states/GameStateMachine.h"

#define WINDOW_HEIGHT   480
#define WINDOW_WIDTH    640

class Game{

private:

    Managers::Graphics* gameGraphicsManager;
    Managers::Events* gameEventsManager;
    SM::StateMachine* gameStateMachine;



public:
    Game();
    Game(Managers::Graphics* gameGraphicsManager, Managers::Events* gameEventsManager);
    ~Game();

    void update(float dt);
    void render();

    void setGraphics(Managers::Graphics* gameGraphicsManager);
    void setEvents(Managers::Events* gameEventsManager);
    void setStateMachine(SM::StateMachine* gameStateMachine);
};

#endif