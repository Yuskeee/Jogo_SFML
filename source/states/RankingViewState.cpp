#include "states/GameStateMachine.h"

using namespace GameSM;

void RankingViewState::updateRanking(){
    ranking = Ranking::getInstance();
    for(int i = 0; i < MAX_ENTRIES; i++){
        pGraphicsManager->setString(positions[i], (i < ranking->getSize()) ? ranking->getEntry():DEFAULT_TEXT);
    }
}

void RankingViewState::clear(){
    ranking->clear();
}

RankingViewState::RankingViewState(SM::StateMachine* pStateMachine, Managers::Graphics* pGraphicsManager): SM::State(pStateMachine){

    this->pGraphicsManager = pGraphicsManager;

    selection = 0;

    ranking = Ranking::getInstance();

    for(int i = 0; i < MAX_ENTRIES; i++){
        positions[i] = pGraphicsManager->createText(0, DEFAULT_TEXT, 15);
        pGraphicsManager->setTextPos(positions[i], 225, 50 + 30 * i);
    }

    titleText = pGraphicsManager->createText(0, "PONTUACOES", 20);
    pGraphicsManager->setTextPos(titleText, 225, 20);

    backText = pGraphicsManager->createText(0, "Voltar", 20);
    pGraphicsManager->setTextPos(backText, 50, 270);

    eraseText = pGraphicsManager->createText(0, "Apagar Ranking", 20);
    pGraphicsManager->setTextPos(eraseText, 50, 320);

}

RankingViewState::~RankingViewState(){

}

void RankingViewState::enter(void* arg){
    updateRanking();
}

void RankingViewState::exit(){
    Ranking::deleteInstance();
}

void RankingViewState::update(float dt, Managers::Events* pEventsManager){

    if(pEventsManager->keyPressed(Managers::Events::keycode::W))
        selection--;
    else if(pEventsManager->keyPressed(Managers::Events::keycode::S))
        selection++;

    if(selection < 0)
        selection = 1;
    else if(selection > 1)
        selection = 0;

    if(pEventsManager->keyPressed(Managers::Events::keycode::Enter)||
       pEventsManager->keyPressed(Managers::Events::keycode::Space)){

        switch(selection){
            case 0:
                //VOLTAR AO MENU
                pStateMachine->changeState(MainMenuStateID, NULL);
                break;

            case 1:
                //APAGAR RANKING
                clear();
                updateRanking();
                break;
           }
    }
}
void RankingViewState::render(Managers::Graphics* pGraphicsManager){
    pGraphicsManager->drawText(titleText);

    for(int i = 0; i < MAX_ENTRIES; i++)
        pGraphicsManager->drawText(positions[i]);

    switch(selection){
        case 0:
            pGraphicsManager->setTextColor(eraseText, 255, 255, 255, 255);
            pGraphicsManager->setTextColor(backText, 255, 10, 10, 255);
            break;
        case 1:
            pGraphicsManager->setTextColor(backText, 255, 255, 255, 255);
            pGraphicsManager->setTextColor(eraseText, 255, 10, 10, 255);
            break;
        default:
            break;
    }

    pGraphicsManager->drawText(backText);
    pGraphicsManager->drawText(eraseText);
}
