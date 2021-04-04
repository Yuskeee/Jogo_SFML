#ifndef _GAMESTATEMACHINE_H
#define _GAMESTATEMACHINE_H

#include <stdio.h>

#include "states/MainMenuState.h"
#include "states/ChooseMenuState.h"
#include "states/PlayState.h"

namespace GameSM{

enum GameStates{
    MainMenuStateID,
    ChooseMenuStateID,
    GamePlayStateID
};

class GameStateMachine:public SM::StateMachine{

public:
    GameStateMachine(Managers::Graphics* pGraphicsManager = NULL);
    ~GameStateMachine();

};

}

#endif