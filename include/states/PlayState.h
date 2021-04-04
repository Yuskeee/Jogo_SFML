#ifndef _PLAY_STATE_H
#define _PLAY_STATE_H

#include "states/State.h"
#include "Level.h"

namespace GameSM{

class GamePlayState:public SM::State{

private:
    float timeElapsed;
    Managers::textID playText;//para testes
    float playTextPosX, playTextPosY;//para testes
    float textSpeed;//para testes
    World::Level* pLevel;

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