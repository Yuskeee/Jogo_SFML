#ifndef _PLAYER_SELECTION_STATE_H
#define _PLAYER_SELECTION_STATE_H

//nao inclui nada relativo aos estados, esse cabecalho esta dentro de GameStateMachine

namespace GameSM{

class PlayerSelectionState:public SM::State{

private:

    int args[nArgs];
    int selection;
    Managers::textID titleText;
    Managers::textID singleplayerText;
    Managers::textID multiplayerText;
    Managers::textID backText;


public:
    PlayerSelectionState(SM::StateMachine* pStateMachine = NULL, Managers::Graphics* pGraphicsManager = NULL);
    ~PlayerSelectionState();

    virtual void enter(void* arg);

    virtual void update(float dt, Managers::Events* pEventsManager);
    virtual void render(Managers::Graphics* pGraphicsManager);
};
}

#endif