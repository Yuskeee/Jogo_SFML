#include "states/GameStateMachine.h"

using namespace GameSM;

GamePlayState::GamePlayState(SM::StateMachine* pStateMachine, Managers::Graphics* pGraphicsManager):SM::State(pStateMachine), score(0){
    this->pGraphicsManager = pGraphicsManager;
    pLevel = NULL;

    scoreText = pGraphicsManager->createText(0, "Score: 0", 20);
    pGraphicsManager->setTextPos(scoreText, 255, 20);
    pGraphicsManager->setTextColor(scoreText, 255, 255, 0, 255);
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
        int* rArgs = (int*)(arg);
        pLevel->startLevel(rArgs[levelArg], rArgs[playersArg]);
    }
    else if(pLevel){
        pGraphicsManager->setBackground(pLevel->getBackground());
    }
}

void GamePlayState::exit(){
    printf("Saindo do jogo\n");
}

void GamePlayState::update(float dt, Managers::Events* pEvents){
    pLevel->update(dt, pEvents);
    if(pEvents->keyDown(Managers::Events::keycode::P))
        pStateMachine->changeState(PauseStateID, NULL);

    score = pLevel->getScore();
    std::string text = "Score: " + std::to_string(static_cast<unsigned long int>(score));

    pGraphicsManager->setString(scoreText, text);

    if(!pLevel->getPlayers()){
        int finalScore = score;
        pStateMachine->changeState(GameOverStateID, (void*)&finalScore);
    }
}

void GamePlayState::render(Managers::Graphics* pGraphicsManager){
    pLevel->render();
    pGraphicsManager->drawText(scoreText);
    //printf("Jogando\nTempo decorrido: %f\n\n", timeElapsed);
}
