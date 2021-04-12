#include "states/GameStateMachine.h"

using namespace GameSM;

GamePlayState::GamePlayState(SM::StateMachine* pStateMachine, Managers::Graphics* pGraphicsManager):SM::State(pStateMachine){
    this->pGraphicsManager = pGraphicsManager;
    pLevel = NULL;
}

GamePlayState::~GamePlayState(){
    delete pLevel;
}

void GamePlayState::enter(void* arg){
    printf("Entrando no jogo\n");
    if(arg){
        if(pLevel)
            delete pLevel;
        printf("loading level\n");

        pLevel = new World::Level(pGraphicsManager);
        int* rArgs = static_cast<int*>(arg);
        pLevel->startLevel(rArgs[levelArg], rArgs[playersArg]);
    }
}

void GamePlayState::exit(){
    printf("Saindo do jogo\n");
}

void GamePlayState::update(float dt, Managers::Events* pEvents){
    pLevel->update(dt, pEvents);

    if(pEvents->keyDown(Managers::Events::keycode::P))
        pStateMachine->changeState(PauseStateID, NULL);
}

void GamePlayState::render(Managers::Graphics* pGraphicsManager){
    pLevel->render();
    //printf("Jogando\nTempo decorrido: %f\n\n", timeElapsed);
}