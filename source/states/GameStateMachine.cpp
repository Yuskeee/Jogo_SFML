#include "states/GameStateMachine.h"

using namespace GameSM;

GameStateMachine::GameStateMachine(Managers::Graphics* pGraphicsManager){

    SM::State* state = static_cast<SM::State*>(new MainMenuState(static_cast<StateMachine*>(this), pGraphicsManager));
    addState(state);
    state = static_cast<SM::State*>(new ChooseMenuState(static_cast<StateMachine*>(this), pGraphicsManager));
    addState(state);
    state = static_cast<SM::State*>(new GamePlayState(static_cast<StateMachine*>(this), pGraphicsManager));
    addState(state);
    currentStateID = MainMenuStateID;
}

GameStateMachine::~GameStateMachine(){

    
}