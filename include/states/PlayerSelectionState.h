#ifndef _PLAYER_SELECTION_STATE_H
#define _PLAYER_SELECTION_STATE_H

//nao inclui nada relativo aos estados, esse cabecalho esta dentro de GameStateMachine

#define PLAYER_SELECTION_BACKGROUND_FILE "../assets/ground_top.png"

namespace GameSM{

class PlayerSelectionState:public SM::State{

private:

    Managers::Graphics* pGraphicsManager;

    int args[nArgs];
    int selection;
    Managers::textID titleText;
    Managers::textID singleplayerText;
    Managers::textID multiplayerText;
    Managers::textID backText;

    Managers::spriteID background;


public:
    PlayerSelectionState(SM::StateMachine* pStateMachine = NULL, Managers::Graphics* pGraphicsManager = NULL);
    ~PlayerSelectionState();

    virtual void enter(void* arg);

    virtual void update(float dt, Managers::Events* pEventsManager);
    virtual void render(Managers::Graphics* pGraphicsManager);
};
}

#endif