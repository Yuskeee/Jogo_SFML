#ifndef _MAIN_H
#define _MAIN_H

#include "Graphics.h"
#include "Events.h"
#include "states/GameStateMachine.h"

#define WINDOW_HEIGHT   480
#define WINDOW_WIDTH    640

//classe principal
class Game{

private:

    Managers::Graphics* gameGraphicsManager;
    Managers::Events* gameEventsManager;
    SM::StateMachine* gameStateMachine;

    void update(const float dt); //chama update da máquina de estados que, por sua vez, chama update do estado corrente
    void render(); //chama render de Graphics e da máquina de Estados

public:
    Game();
    ~Game();

    void run();

//    //funções set
//    void setGraphics(Managers::Graphics* gameGraphicsManager);
//    void setEvents(Managers::Events* gameEventsManager);
//    void setStateMachine(SM::StateMachine* gameStateMachine);
};

#endif
