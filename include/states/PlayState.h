#ifndef _PLAY_STATE_H
#define _PLAY_STATE_H

//nao inclui nada relativo aos estados, esse cabecalho esta dentro de GameStateMachine

#include "Level.h"

namespace GameSM{

class GamePlayState:public SM::State{

private:
    Managers::Graphics* pGraphicsManager;
    World::Level* pLevel;

    Managers::textID scoreText;

    int score;

public:
    GamePlayState(SM::StateMachine* pStateMachine = NULL, Managers::Graphics* pGraphicsManager = NULL);
    ~GamePlayState();

    virtual void enter(void* arg);
    virtual void exit();

    virtual void update(float dt, Managers::Events* pEventsManager);
    virtual void render(Managers::Graphics* pGraphicsManager);
};

}

#endif
