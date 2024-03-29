#ifndef _GAME_OVER_STATE_H
#define _GAME_OVER_STATE_H

//nao inclui nada relativo aos estados, esse cabecalho esta dentro de GameStateMachine

#define GAME_OVER_BACKGROUND_FILE "../assets/ground_top.png"

#include "Ranking.h"

namespace GameSM{

class GameOverState:public SM::State{

private:

    Managers::Graphics* pGraphicsManager;

    int args[nArgs];
    std::string name;
    std::string scoreStr;
    Managers::textID titleText;
    Managers::textID scoreText;
    Managers::textID nameText;
    Managers::textID enterText;

    Managers::spriteID background;

    Leaderboard::Ranking *ranking;



public:
    GameOverState(SM::StateMachine* pStateMachine = NULL, Managers::Graphics* pGraphicsManager = NULL);
    ~GameOverState();

    virtual void enter(void* arg);
    virtual void exit();

    virtual void update(float dt, Managers::Events* pEventsManager);
    virtual void render(Managers::Graphics* pGraphicsManager);
};
}

#endif
