#ifndef _PAUSE_STATE_H
#define _PAUSE_STATE_H

#include "../Level.h"

//nao inclui nada relativo aos estados, esse cabecalho esta dentro de GameStateMachine

#define PAUSE_BACKGROUND_FILE "../assets/ground_top.png"

namespace GameSM{

class PauseState:public SM::State{

private:
    float timeElapsed;
    bool _isSaved;

    Managers::Graphics* pGraphicsManager;

    int selection;
    Managers::textID titleText;
    Managers::textID backText;
    Managers::textID saveText;
    Managers::textID saveCheckText;
    Managers::textID quitText;

    Managers::spriteID background;

    static World::Level *pLevel;

public:
    PauseState(SM::StateMachine* pStateMachine = NULL, Managers::Graphics* pGraphicsManager = NULL);
    ~PauseState();

    virtual void enter(void* arg);

    virtual void update(float dt, Managers::Events* pEventsManager);
    virtual void render(Managers::Graphics* pGraphicsManager);

    static void setpLevel(World::Level *pLevel);
};

}

#endif
