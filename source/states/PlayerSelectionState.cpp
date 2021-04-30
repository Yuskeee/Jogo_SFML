#include "states/GameStateMachine.h"

using namespace GameSM;

PlayerSelectionState::PlayerSelectionState(SM::StateMachine* pStateMachine, Managers::Graphics* pGraphicsManager):SM::State(pStateMachine){

    selection = 0;
    args[playersArg] = 1;
    args[levelArg] = 0;

    titleText = pGraphicsManager->createText(0, "SELECIONE O NUMERO DE JOGADORES", 20);
    pGraphicsManager->setTextPos(titleText, 70, 20);

    singleplayerText = pGraphicsManager->createText(0, "Um Jogador", 15);
    pGraphicsManager->setTextPos(singleplayerText, 70, 50);

    multiplayerText = pGraphicsManager->createText(0, "Dois Jogadores", 15);
    pGraphicsManager->setTextPos(multiplayerText, 70, 70);

    backText = pGraphicsManager->createText(0, "Voltar", 15);
    pGraphicsManager->setTextPos(backText, 70, 110);

    background = pGraphicsManager->createSprite(pGraphicsManager->loadTexture(PLAYER_SELECTION_BACKGROUND_FILE));

    this->pGraphicsManager = pGraphicsManager;

}

PlayerSelectionState::~PlayerSelectionState(){

}

void PlayerSelectionState::enter(void* arg){
    printf("Entrando na selecao de jogadores\n");
    this->args[levelArg] = *(int*)arg;
    this->args[loadArg] = 0;//falso
    pGraphicsManager->setBackground(background);
}

void PlayerSelectionState::update(float dt, Managers::Events* pEventsManager){

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
                args[playersArg] = 1;
                pStateMachine->changeState(GamePlayStateID, static_cast<void*>(args));
                break;

            case 1:
                args[playersArg] = 2;
                pStateMachine->changeState(GamePlayStateID, static_cast<void*>(args));
                break;

            case 2:
                pStateMachine->changeState(MainMenuStateID, NULL);
                break;

           }


    }

}

void PlayerSelectionState::render(Managers::Graphics* pGraphicsManager){
    pGraphicsManager->drawText(titleText);

    switch(selection){
        case 0:
            pGraphicsManager->setTextColor(backText, 255, 255, 255, 255);
            pGraphicsManager->setTextColor(singleplayerText, 255, 10, 10, 255);
            pGraphicsManager->setTextColor(multiplayerText, 255, 255, 255, 255);
            break;
        case 1:
            pGraphicsManager->setTextColor(singleplayerText, 255, 255, 255, 255);
            pGraphicsManager->setTextColor(multiplayerText, 255, 10, 10, 255);
            pGraphicsManager->setTextColor(backText, 255, 255, 255, 255);
            break;
        case 2:
            pGraphicsManager->setTextColor(multiplayerText, 255, 255, 255, 255);
            pGraphicsManager->setTextColor(backText, 255, 10, 10, 255);
            pGraphicsManager->setTextColor(singleplayerText, 255, 255, 255, 255);
            break;

        default:
            break;
    }

    pGraphicsManager->drawText(titleText);
    pGraphicsManager->drawText(singleplayerText);
    pGraphicsManager->drawText(multiplayerText);
    pGraphicsManager->drawText(backText);
}
