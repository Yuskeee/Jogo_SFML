#include "states/GameStateMachine.h"

using namespace GameSM;

GameOverState::GameOverState(SM::StateMachine* pStateMachine, Managers::Graphics* pGraphics):SM::State(pStateMachine){

    name = "";
    scoreStr = "";
    args[scoreArg] = 1;

    titleText = pGraphics->createText(0, "GAME OVER", 20);
    pGraphics->setTextPos(titleText, 70, 20);

    scoreText = pGraphics->createText(0, "Pontuacao: ", 15);
    pGraphics->setTextPos(scoreText, 70, 50);

    nameText = pGraphics->createText(0, "Digite seu nome: ", 15);
    pGraphics->setTextPos(nameText, 70, 70);

    enterText = pGraphics->createText(0, "Pressione ENTER para inserir", 15);
    pGraphics->setTextPos(enterText, 70, 110);
    

}

GameOverState::~GameOverState(){

}

void GameOverState::enter(void* arg){
    scoreStr = "Pontuacao: " + std::to_string(*(int*)arg);
}

void GameOverState::update(float dt, Managers::Events* pEventsManager){

    if(pEventsManager->keyPressed(Managers::Events::keycode::Enter)){
        pStateMachine->changeState(MainMenuStateID, NULL);

    }
    else if(pEventsManager->keyPressed(Managers::Events::keycode::BackSpace)){
        if(name.length()>0)
            name.pop_back();
    }
    else{
        name += pEventsManager->getInputAsString();
    }

}

void GameOverState::render(Managers::Graphics* pGraphicsManager){

    pGraphicsManager->setString(scoreText, "Pontuacao: " + scoreStr);
    pGraphicsManager->setString(nameText, "Digite seu nome: " + name);

    pGraphicsManager->drawText(titleText);
    pGraphicsManager->drawText(scoreText);
    pGraphicsManager->drawText(nameText);
    pGraphicsManager->drawText(enterText);
}