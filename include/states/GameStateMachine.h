#ifndef _GAMESTATEMACHINE_H
#define _GAMESTATEMACHINE_H

#include <stdio.h>
#include "states/State.h"

namespace GameSM{

enum GameStates{
    MainMenuStateID,
    ChooseMenuStateID,
    RankingViewStateID,
    PlayerSelectionStateID,
    GamePlayStateID,
    PauseStateID
};

enum argType{
    levelArg,
    playersArg,
    nArgs
};
}

//cabecalhos de estados especificos sao incluidos depois de declarado o que lhes é necessario
#include "MainMenuState.h"
#include "ChooseMenuState.h"
#include "RankingViewState.h"
#include "PlayerSelectionState.h"
#include "PlayState.h"
#include "PauseState.h"

namespace GameSM{
class GameStateMachine:public SM::StateMachine{

public:
    GameStateMachine(Managers::Graphics* pGraphicsManager = NULL);
    ~GameStateMachine();

};

}

#endif
