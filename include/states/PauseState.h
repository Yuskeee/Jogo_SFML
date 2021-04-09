#ifndef _PAUSE_STATE_H
#define _PAUSE_STATE_H

//nao inclui nada relativo aos estados, esse cabecalho esta dentro de GameStateMachine

namespace GameSM{

class PauseState:public SM::State{

private:
    float timeElapsed;

    int selection;
    Managers::textID titleText;
    Managers::textID backText;
    Managers::textID saveText;
    Managers::textID quitText;

public:
    PauseState(SM::StateMachine* pStateMachine = NULL, Managers::Graphics* pGraphicsManager = NULL);
    ~PauseState();

    virtual void update(float dt, Managers::Events* pEventsManager);
    virtual void render(Managers::Graphics* pGraphicsManager);
};

}

#endif
