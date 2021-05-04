#include "states/GameStateMachine.h"

using namespace GameSM;

MainMenuState::MainMenuState(SM::StateMachine* pStateMachine, Managers::Graphics* pGraphicsManager):SM::State(pStateMachine){
    timeElapsed = 0;

    selection = 0;
    quit = false;

    titleText = pGraphicsManager->createText(0, "As Aventuras do Alienzinho", 20);
    pGraphicsManager->setTextPos(titleText, 112, 20);

    playText = pGraphicsManager->createText(0, "Jogar", 15);
    pGraphicsManager->setTextPos(playText, 112, 50);

    chooseText = pGraphicsManager->createText(0, "Escolher Fase", 15);
    pGraphicsManager->setTextPos(chooseText, 112, 70);

    loadText = pGraphicsManager->createText(0, "Carregar Jogo Salvo", 15);
    pGraphicsManager->setTextPos(loadText, 112, 90);

    scoreText = pGraphicsManager->createText(0, "Pontuacoes", 15);
    pGraphicsManager->setTextPos(scoreText, 112, 110);

    quitText = pGraphicsManager->createText(0, "Sair", 15);
    pGraphicsManager->setTextPos(quitText, 112, 130);

    background = pGraphicsManager->createSprite(pGraphicsManager->loadTexture(MAIN_MENU_BACKGROUND_FILE));

    this->pGraphicsManager = pGraphicsManager;

}

MainMenuState::~MainMenuState(){

}

void MainMenuState::enter(void* arg){
    pGraphicsManager->setBackground(background);
}


void MainMenuState::update(float dt, Managers::Events* pEventsManager){
    timeElapsed += dt;

    if(pEventsManager->keyPressed(Managers::Events::keycode::W))
        selection--;
    else if(pEventsManager->keyPressed(Managers::Events::keycode::S))
        selection++;

    if(selection < 0)
        selection = 4;
    else if(selection > 4)
        selection = 0;

    if(pEventsManager->keyPressed(Managers::Events::keycode::Enter)||
       pEventsManager->keyPressed(Managers::Events::keycode::Space)){

        switch(selection){
            case 0:{
                int level = 0;
                pStateMachine->changeState(PlayerSelectionStateID, static_cast<void*>(&level));
                break;
            }
            case 1:
                pStateMachine->changeState(ChooseMenuStateID, NULL);
                break;

            case 2:{
                int _shouldLoad = 1;
                pStateMachine->changeState(GamePlayStateID, static_cast<void*>(&_shouldLoad));//carrega fase salva
                break;
            }
            case 3:
                pStateMachine->changeState(RankingViewStateID, NULL);
                break;

            case 4:
                quit = true;
                break;

           }

    }

}

void MainMenuState::render(Managers::Graphics* pGraphicsManager){
    pGraphicsManager->drawText(titleText);

    switch(selection){
        case 0:
            pGraphicsManager->setTextColor(quitText, 255, 255, 255, 255);
            pGraphicsManager->setTextColor(playText, 255, 10, 10, 255);
            pGraphicsManager->setTextColor(chooseText, 255, 255, 255, 255);
            break;
        case 1:
            pGraphicsManager->setTextColor(playText, 255, 255, 255, 255);
            pGraphicsManager->setTextColor(chooseText, 255, 10, 10, 255);
            pGraphicsManager->setTextColor(loadText, 255, 255, 255, 255);
            break;
        case 2:
            pGraphicsManager->setTextColor(chooseText, 255, 255, 255, 255);
            pGraphicsManager->setTextColor(loadText, 255, 10, 10, 255);
            pGraphicsManager->setTextColor(scoreText, 255, 255, 255, 255);
            break;
        case 3:
            pGraphicsManager->setTextColor(loadText, 255, 255, 255, 255);
            pGraphicsManager->setTextColor(scoreText, 255, 10, 10, 255);
            pGraphicsManager->setTextColor(quitText, 255, 255, 255, 255);
            break;
        case 4:
            pGraphicsManager->setTextColor(scoreText, 255, 255, 255, 255);
            pGraphicsManager->setTextColor(quitText, 255, 10, 10, 255);
            pGraphicsManager->setTextColor(playText, 255, 255, 255, 255);
            break;

        default:
            break;
    }

    pGraphicsManager->drawText(playText);
    pGraphicsManager->drawText(chooseText);
    pGraphicsManager->drawText(loadText);
    pGraphicsManager->drawText(scoreText);
    pGraphicsManager->drawText(quitText);
    //printf("Estado: Menu\nTempo decorrido: %f\nPressione 'J' para jogar\n\n", timeElapsed);
    if(quit)
        pGraphicsManager->closeWindow();
}
