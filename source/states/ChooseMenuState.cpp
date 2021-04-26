#include "states/GameStateMachine.h"

using namespace GameSM;

ChooseMenuState::ChooseMenuState(SM::StateMachine* pStateMachine, Managers::Graphics* pGraphicsManager):SM::State(pStateMachine){

    selection = 0;

    titleText = pGraphicsManager->createText(0, "SELECIONE A FASE", 20);
    pGraphicsManager->setTextPos(titleText, 225, 20);

    level1Text = pGraphicsManager->createText(0, "Fase 1", 15);
    pGraphicsManager->setTextPos(level1Text, 225, 50);

    level2Text = pGraphicsManager->createText(0, "Fase 2", 15);
    pGraphicsManager->setTextPos(level2Text, 225, 70);

    level3Text = pGraphicsManager->createText(0, "Fase 3", 15);
    pGraphicsManager->setTextPos(level3Text, 225, 90);

    level4Text = pGraphicsManager->createText(0, "Fase 3 (Thread)", 15);
    pGraphicsManager->setTextPos(level4Text, 225, 110);

    backText = pGraphicsManager->createText(0, "Voltar", 15);
    pGraphicsManager->setTextPos(backText, 225, 130);

    background = pGraphicsManager->createSprite(pGraphicsManager->loadTexture(CHOOSE_MENU_BACKGROUND_FILE));

    this->pGraphicsManager = pGraphicsManager;

}

ChooseMenuState::~ChooseMenuState(){

}

void ChooseMenuState::enter(void* arg){
    pGraphicsManager->setBackground(background);
}

void ChooseMenuState::update(float dt, Managers::Events* pEventsManager){

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

        int level;

        switch(selection){
            case 0:
                level = 0;
                pStateMachine->changeState(PlayerSelectionStateID, static_cast<void*>(&level));
                break;

            case 1:
                level = 1;
                pStateMachine->changeState(PlayerSelectionStateID, static_cast<void*>(&level));
                break;

            case 2:
                level = 2;
                pStateMachine->changeState(PlayerSelectionStateID, static_cast<void*>(&level));
                break;

            case 3:
                level = 3;
                pStateMachine->changeState(PlayerSelectionStateID, static_cast<void*>(&level));
                break;

            case 4:
                pStateMachine->changeState(MainMenuStateID, NULL);
                break;

           }


    }

}

void ChooseMenuState::render(Managers::Graphics* pGraphicsManager){
    pGraphicsManager->drawText(titleText);

    switch(selection){
        case 0:
            pGraphicsManager->setTextColor(backText, 255, 255, 255, 255);
            pGraphicsManager->setTextColor(level1Text, 255, 10, 10, 255);
            pGraphicsManager->setTextColor(level2Text, 255, 255, 255, 255);
            break;
        case 1:
            pGraphicsManager->setTextColor(level1Text, 255, 255, 255, 255);
            pGraphicsManager->setTextColor(level2Text, 255, 10, 10, 255);
            pGraphicsManager->setTextColor(level3Text, 255, 255, 255, 255);
            break;
        case 2:
            pGraphicsManager->setTextColor(level2Text, 255, 255, 255, 255);
            pGraphicsManager->setTextColor(level3Text, 255, 10, 10, 255);
            pGraphicsManager->setTextColor(backText, 255, 255, 255, 255);
            break;
        case 3:
            pGraphicsManager->setTextColor(level3Text, 255, 255, 255, 255);
            pGraphicsManager->setTextColor(level4Text, 255, 10, 10, 255);
            pGraphicsManager->setTextColor(backText, 255, 255, 255, 255);
            break;
        case 4:
            pGraphicsManager->setTextColor(level4Text, 255, 255, 255, 255);
            pGraphicsManager->setTextColor(backText, 255, 10, 10, 255);
            pGraphicsManager->setTextColor(level1Text, 255, 255, 255, 255);
            break;

        default:
            break;
    }

    pGraphicsManager->drawText(titleText);
    pGraphicsManager->drawText(level1Text);
    pGraphicsManager->drawText(level2Text);
    pGraphicsManager->drawText(level3Text);
    pGraphicsManager->drawText(level4Text);
    pGraphicsManager->drawText(backText);
}
