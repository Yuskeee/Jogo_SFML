#ifndef _GAMESTATEMACHINE_H
#define _GAMESTATEMACHINE_H

#include "State.h"
#include <stdio.h>
#include "Level.h"

namespace GameSM{

enum GameStates{
    GameMenuStateID,
    GamePlayStateID
};


class GameMenuState:public SM::State{

private:
    float timeElapsed;
    Managers::textID menuText;//para testes
    float menuTextPosX, menuTextPosY;//para testes
    float textSpeed;//para testes

public:
    GameMenuState(SM::StateMachine* pStateMachine = NULL, Managers::Graphics* pGraphicsManager = NULL);
    ~GameMenuState();

    virtual void enter();
    virtual void exit();

    virtual void update(float dt, Managers::Events* pEventsManager);
    virtual void render(Managers::Graphics* pGraphicsManager);
};

class GamePlayState:public SM::State{

private:
    float timeElapsed;
    Managers::textID playText;//para testes
    float playTextPosX, playTextPosY;//para testes
    float textSpeed;//para testes
    Level* pLevel;

public:
    GamePlayState(SM::StateMachine* pStateMachine = NULL, Managers::Graphics* pGraphicsManager = NULL);
    ~GamePlayState();

    virtual void enter();
    virtual void exit();

    virtual void update(float dt, Managers::Events* pEventsManager);
    virtual void render(Managers::Graphics* pGraphicsManager);
};

class GameStateMachine:public SM::StateMachine{

public:
    GameStateMachine(Managers::Graphics* pGraphicsManager = NULL);
    ~GameStateMachine();

};

}

#endif