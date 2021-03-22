#ifndef _GAMESTATEMACHINE_H
#define _GAMESTATEMACHINE_H

#include "State.h"
#include <stdio.h>
#include "Fase.h"

enum GameStates{
    GameMenuStateID,
    GamePlayStateID
};


class GameMenuState:public State{

private:
    float timeElapsed;
    textID menuText;//para testes
    float menuTextPosX, menuTextPosY;//para testes
    float textSpeed;//para testes

public:
    GameMenuState(StateMachine* pStateMachine = NULL, Graphics* pGraphics = NULL);
    ~GameMenuState();

    virtual void enter();
    virtual void exit();

    virtual void update(float dt, Events* pEvents);
    virtual void render(Graphics* pGraphics);
};

class GamePlayState:public State{

private:
    float timeElapsed;
    textID playText;//para testes
    float playTextPosX, playTextPosY;//para testes
    float textSpeed;//para testes
    Fase* pFase;

public:
    GamePlayState(StateMachine* pStateMachine = NULL, Graphics* pGraphics = NULL);
    ~GamePlayState();

    virtual void enter();
    virtual void exit();

    virtual void update(float dt, Events* pEvents);
    virtual void render(Graphics* pGraphics);
};

class GameStateMachine:public StateMachine{

public:
    GameStateMachine(Graphics* pGraphics = NULL);
    ~GameStateMachine();

};


#endif