#ifndef _GAMESTATEMACHINE_H
#define _GAMESTATEMACHINE_H

#include "State.h"
#include <stdio.h>

enum GameStates{
    GameMenuStateID,
    GamePlayStateID
};


class GameMenuState:public State{

private:
    float timeElapsed;

public:
    GameMenuState(StateMachine* pStateMachine = NULL);
    ~GameMenuState();

    virtual void enter();
    virtual void exit();

    virtual void update(float dt, Events* pEvents);
    virtual void render(Graphics* pGraphics);
};

class GamePlayState:public State{

private:
    float timeElapsed;

public:
    GamePlayState(StateMachine* pStateMachine = NULL);
    ~GamePlayState();

    virtual void enter();
    virtual void exit();

    virtual void update(float dt, Events* pEvents);
    virtual void render(Graphics* pGraphics);
};

class GameStateMachine:public StateMachine{

public:
    GameStateMachine();
    ~GameStateMachine();

};


#endif