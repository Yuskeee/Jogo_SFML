#include "states/GameStateMachine.h"

using namespace GameSM;

GamePlayState::GamePlayState(SM::StateMachine* pStateMachine, Managers::Graphics* pGraphicsManager):SM::State(pStateMachine){
    timeElapsed = 0;
    playText = pGraphicsManager->createText(0, "JOGANDO", 15);
    playTextPosX = 0;
    playTextPosY = 0;
    textSpeed = 50;
    pLevel = new World::Level(pGraphicsManager);
}

GamePlayState::~GamePlayState(){
    delete pLevel;
}

void GamePlayState::enter(void* arg){
    printf("Entrando no jogo\n");
    int* rArgs = static_cast<int*>(arg);
    printf("loaded level %d", rArgs[levelArg]);
    pLevel->startLevel(rArgs[levelArg], rArgs[playersArg]);
}

void GamePlayState::exit(){
    printf("Saindo do jogo\n");
}

void GamePlayState::update(float dt, Managers::Events* pEvents){
    timeElapsed += dt;

    pLevel->update(dt, pEvents);
}

void GamePlayState::render(Managers::Graphics* pGraphicsManager){
    pGraphicsManager->setTextPos(playText, playTextPosX, playTextPosY);
    pGraphicsManager->drawText(playText);
    pLevel->render();
    //printf("Jogando\nTempo decorrido: %f\n\n", timeElapsed);
}