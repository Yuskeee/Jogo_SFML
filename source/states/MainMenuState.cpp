#include "states/MainMenuState.h"
#include "states/GameStateMachine.h"


using namespace GameSM;

MainMenuState::MainMenuState(SM::StateMachine* pStateMachine, Managers::Graphics* pGraphics):SM::State(pStateMachine){
    timeElapsed = 0;

    selection = 0;
    quit = false;

    titleText = pGraphics->createText(0, "NOME DO JOGO", 20);
    pGraphics->setTextPos(titleText, 225, 20);

    playText = pGraphics->createText(0, "Jogar", 15);
    pGraphics->setTextPos(playText, 225, 50);

    chooseText = pGraphics->createText(0, "Escolher Fase", 15);
    pGraphics->setTextPos(chooseText, 225, 70);

    loadText = pGraphics->createText(0, "Carregar Jogo Salvo", 15);
    pGraphics->setTextPos(loadText, 225, 90);

    scoreText = pGraphics->createText(0, "Pontuacoes", 15);
    pGraphics->setTextPos(scoreText, 225, 110);

    quitText = pGraphics->createText(0, "Sair", 15);
    pGraphics->setTextPos(quitText, 225, 130);
    

}

MainMenuState::~MainMenuState(){

}

void MainMenuState::enter(){
    printf("Entrando no menu\n");
}

void MainMenuState::exit(){
    printf("Saindo do menu\n");
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
                pStateMachine->changeState(GamePlayStateID, static_cast<void*>(&level));
                break;
            }
            case 1:
                pStateMachine->changeState(ChooseMenuStateID, NULL);
                break;

            case 2:
                break;

            case 3:
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