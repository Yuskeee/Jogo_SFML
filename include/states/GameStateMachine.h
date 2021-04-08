#ifndef _GAMESTATEMACHINE_H
#define _GAMESTATEMACHINE_H

#include <stdio.h>
#include <states/State.h>

namespace GameSM{

enum GameStates{
    MainMenuStateID,
    ChooseMenuStateID,
    PlayerSelectionStateID,
    GamePlayStateID
};

enum argType{
    levelArg,
    playersArg,
    nArgs
};
}

//cabecalhos de estados especificos sao incluidos depois de declarado o que lhes é necessario
#include "states/MainMenuState.h"
#include "states/ChooseMenuState.h"
#include "states/PlayerSelectionState.h"
#include "states/PlayState.h"

namespace GameSM{
class GameStateMachine:public SM::StateMachine{

public:
    GameStateMachine(Managers::Graphics* pGraphicsManager = NULL);
    ~GameStateMachine();

};

}

#endif