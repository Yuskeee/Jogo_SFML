#include "GameStateMachine.h"

using namespace GameSM;

World::Level* PauseState::pLevel = NULL;

PauseState::PauseState(SM::StateMachine* pStateMachine, Managers::Graphics* pGraphicsManager):SM::State(pStateMachine), _isSaved(false){
    timeElapsed = 0;

    selection = 0;

    titleText = pGraphicsManager->createText(0, "PAUSA", 20);
    pGraphicsManager->setTextPos(titleText, 225, 20);

    backText = pGraphicsManager->createText(0, "Retornar ao Jogo", 15);
    pGraphicsManager->setTextPos(backText, 225, 50);

    saveText = pGraphicsManager->createText(0, "Salvar Jogo", 15);
    pGraphicsManager->setTextPos(saveText, 225, 70);

    saveCheckText = pGraphicsManager->createText(0, "SALVO COM SUCESSO!", 15);
    pGraphicsManager->setTextPos(saveCheckText, 300, 400);

    quitText = pGraphicsManager->createText(0, "Sair", 15);
    pGraphicsManager->setTextPos(quitText, 225, 90);

    background = pGraphicsManager->createSprite(pGraphicsManager->loadTexture(PAUSE_BACKGROUND_FILE));

    this->pGraphicsManager = pGraphicsManager;


}

PauseState::~PauseState(){

}

void PauseState::enter(void* arg){
    pGraphicsManager->setBackground(background);

    _isSaved = false;

/* PARA THREADS----------------------------------*/
    if(pLevel->getBossThread())
        pLevel->getBossThread()->pause(true);
/* PARA THREADS----------------------------------*/
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
                /* PARA THREADS----------------------------------*/
                if(pLevel->getBossThread())
                    pLevel->getBossThread()->pause(false);//despausa thread
                /* PARA THREADS----------------------------------*/
                break;
            case 1:
                if(pLevel){
                    pLevel->save();
                    _isSaved = true;
                }
                else
                    std::cerr << "Erro: Ponteiro para level aterrado!" << std::endl;
                break;
            case 2:
                pStateMachine->changeState(MainMenuStateID, NULL);
                /* PARA THREADS----------------------------------*/
                if(pLevel->getBossThread())
                    pLevel->deleteBossThread();//deleta thread
                /* PARA THREADS----------------------------------*/
                break;
           }

    }

}

void PauseState::render(Managers::Graphics* pGraphicsManager){
    pGraphicsManager->drawText(titleText);

    switch(selection){
        case 0:
            pGraphicsManager->setTextColor(quitText, 255, 255, 255, 255);
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

    if(_isSaved)
        pGraphicsManager->drawText(saveCheckText);

    //printf("Estado: Menu\nTempo decorrido: %f\nPressione 'J' para jogar\n\n", timeElapsed);
}

void PauseState::setpLevel(World::Level *pLevel){
    PauseState::pLevel = pLevel;
}
