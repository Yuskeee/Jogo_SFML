#ifndef _CHOOSE_MENU_STATE_H
#define _CHOOSE_MENU_STATE_H

//nao inclui nada relativo aos estados, esse cabecalho esta dentro de GameStateMachine

#define CHOOSE_MENU_BACKGROUND_FILE "../assets/ground_top.png"

namespace GameSM{

class ChooseMenuState:public SM::State{

private:

    Managers::Graphics* pGraphicsManager;

    int selection;
    Managers::textID titleText;
    Managers::textID level1Text;
    Managers::textID level2Text;
    Managers::textID level3Text;
    Managers::textID level4Text;
    Managers::textID backText;

    Managers::spriteID background;


public:
    ChooseMenuState(SM::StateMachine* pStateMachine = NULL, Managers::Graphics* pGraphicsManager = NULL);
    ~ChooseMenuState();

    virtual void enter(void* arg);

    virtual void update(float dt, Managers::Events* pEventsManager);
    virtual void render(Managers::Graphics* pGraphicsManager);
};
}

#endif
