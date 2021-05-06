#include "states/GameStateMachine.h"

using namespace GameSM;

GameOverState::GameOverState(SM::StateMachine* pStateMachine, Managers::Graphics* pGraphicsManager):SM::State(pStateMachine){

    name = "";
    scoreStr = "";
    args[scoreArg] = 1;

    titleText = pGraphicsManager->createText(0, "GAME OVER", 20);
    pGraphicsManager->setTextPos(titleText, 70, 20);

    scoreText = pGraphicsManager->createText(0, "Pontuacao: ", 15);
    pGraphicsManager->setTextPos(scoreText, 70, 50);

    nameText = pGraphicsManager->createText(0, "Digite seu nome: ", 15);
    pGraphicsManager->setTextPos(nameText, 70, 70);

    enterText = pGraphicsManager->createText(0, "Pressione ENTER para inserir", 15);
    pGraphicsManager->setTextPos(enterText, 70, 110);

    background = pGraphicsManager->createSprite(pGraphicsManager->loadTexture(GAME_OVER_BACKGROUND_FILE));

    this->pGraphicsManager = pGraphicsManager;

}

GameOverState::~GameOverState(){
    Leaderboard::Ranking::deleteInstance();
}

void GameOverState::enter(void* arg){
    ranking = Leaderboard::Ranking::getInstance();

    scoreStr = std::to_string(*(int*)arg);

    pGraphicsManager->setBackground(background);
}

void GameOverState::exit(){

}

void GameOverState::update(float dt, Managers::Events* pEventsManager){

    if(pEventsManager->keyPressed(Managers::Events::keycode::Enter)){
        ranking->add(std::stoul(scoreStr), name);
        pStateMachine->changeState(RankingViewStateID, NULL);

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
