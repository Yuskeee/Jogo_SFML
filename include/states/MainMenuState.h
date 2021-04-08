#ifndef _MAIN_MENU_STATE_H
#define _MAIN_MENU_STATE_H

//nao inclui nada relativo aos estados, esse cabecalho esta dentro de GameStateMachine

namespace GameSM{

class MainMenuState:public SM::State{

private:
    float timeElapsed;

    int selection;
    Managers::textID titleText;
    Managers::textID playText;
    Managers::textID chooseText;
    Managers::textID loadText;
    Managers::textID scoreText;
    Managers::textID quitText;

    bool quit;

public:
    MainMenuState(SM::StateMachine* pStateMachine = NULL, Managers::Graphics* pGraphicsManager = NULL);
    ~MainMenuState();

    virtual void update(float dt, Managers::Events* pEventsManager);
    virtual void render(Managers::Graphics* pGraphicsManager);
};

}

#endif
