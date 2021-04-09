#include "states/GameStateMachine.h"

using namespace GameSM;

PauseState::PauseState(SM::StateMachine* pStateMachine, Managers::Graphics* pGraphics):SM::State(pStateMachine){
    timeElapsed = 0;

    selection = 0;

    titleText = pGraphics->createText(0, "PAUSA", 20);
    pGraphics->setTextPos(titleText, 225, 20);

    backText = pGraphics->createText(0, "Retornar ao Jogo", 15);
    pGraphics->setTextPos(backText, 225, 50);

    saveText = pGraphics->createText(0, "Salvar Jogo", 15);
    pGraphics->setTextPos(saveText, 225, 70);

    quitText = pGraphics->createText(0, "Sair", 15);
    pGraphics->setTextPos(quitText, 225, 90);
    

}

PauseState::~PauseState(){

}


void PauseState::update(float dt, Managers::Events* pEventsManager){
    timeElapsed += dt;

    if(pEventsManager->keyPressed(Managers::Events::keycode::W))
        selection--;
    else if(pEventsManager->keyPressed(Managers::Events::keycode::S))
        selection++;

    if(selection < 0)
        selection = 2;
    else if(selection > 2)
        selection = 0;

    if(pEventsManager->keyPressed(Managers::Events::keycode::Enter)||
       pEventsManager->keyPressed(Managers::Events::keycode::Space)){

        switch(selection){
            case 0:
                pStateMachine->changeState(GamePlayStateID, NULL);
                break;
            case 1:
                //salva o jogo
                break;
            case 2:
                pStateMachine->changeState(MainMenuStateID, NULL);
                break;    
           }

    }

}

void PauseState::render(Managers::Graphics* pGraphicsManager){
    pGraphicsManager->drawText(titleText);

    switch(selection){
        case 0:
            pGraphicsManager->setTextColor(titleText, 255, 255, 255, 255);
            pGraphicsManager->setTextColor(backText, 255, 10, 10, 255);
            pGraphicsManager->setTextColor(saveText, 255, 255, 255, 255);
            break;
        case 1:
            pGraphicsManager->setTextColor(backText, 255, 255, 255, 255);
            pGraphicsManager->setTextColor(saveText, 255, 10, 10, 255);
            pGraphicsManager->setTextColor(quitText, 255, 255, 255, 255);
            break;
        case 2:
            pGraphicsManager->setTextColor(saveText, 255, 255, 255, 255);
            pGraphicsManager->setTextColor(quitText, 255, 10, 10, 255);
            pGraphicsManager->setTextColor(backText, 255, 255, 255, 255);
            break;
        default:
            break;
    }

    pGraphicsManager->drawText(titleText);
    pGraphicsManager->drawText(backText);
    pGraphicsManager->drawText(saveText);
    pGraphicsManager->drawText(quitText);
    //printf("Estado: Menu\nTempo decorrido: %f\nPressione 'J' para jogar\n\n", timeElapsed);
}