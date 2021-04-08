#ifndef _CHOOSE_MENU_STATE_H
#define _CHOOSE_MENU_STATE_H

//nao inclui nada relativo aos estados, esse cabecalho esta dentro de GameStateMachine

namespace GameSM{

class ChooseMenuState:public SM::State{

private:

    int selection;
    Managers::textID titleText;
    Managers::textID level1Text;
    Managers::textID level2Text;
    Managers::textID level3Text;
    Managers::textID backText;


public:
    ChooseMenuState(SM::StateMachine* pStateMachine = NULL, Managers::Graphics* pGraphicsManager = NULL);
    ~ChooseMenuState();

    virtual void enter(void* arg);
    virtual void exit();

    virtual void update(float dt, Managers::Events* pEventsManager);
    virtual void render(Managers::Graphics* pGraphicsManager);
};
}

#endif