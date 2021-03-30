#include "GameStateMachine.h"

using namespace GameSM;

//GameMenuState----------------------------

GameMenuState::GameMenuState(SM::StateMachine* pStateMachine, Managers::Graphics* pGraphics):SM::State(pStateMachine){
    timeElapsed = 0;
    menuText = pGraphics->createText(0, "MENU: Pressione J para jogar", 15);
    menuTextPosX = 0;
    menuTextPosY = 0;
    textSpeed = 50;
}

GameMenuState::~GameMenuState(){

}

void GameMenuState::enter(){
    printf("Entrando no menu\n");
}

void GameMenuState::exit(){
    printf("Saindo do menu\n");
}

void GameMenuState::update(float dt, Managers::Events* pEventsManager){
    timeElapsed += dt;

    if(pEventsManager->keyDown(Managers::Events::keycode::W))
        menuTextPosY -= textSpeed*dt;
    if(pEventsManager->keyDown(Managers::Events::keycode::D))
        menuTextPosX += textSpeed*dt;
    if(pEventsManager->keyDown(Managers::Events::keycode::S))
        menuTextPosY += textSpeed*dt;
    if(pEventsManager->keyDown(Managers::Events::keycode::A))
        menuTextPosX -= textSpeed*dt;


    if(pEventsManager->keyPressed(Managers::Events::keycode::J))
        pStateMachine->changeState(GamePlayStateID);
        printf("menu state updated\n");

}

void GameMenuState::render(Managers::Graphics* pGraphicsManager){
    pGraphicsManager->setTextPos(menuText, menuTextPosX, menuTextPosY);
    pGraphicsManager->drawText(menuText);
    //printf("Estado: Menu\nTempo decorrido: %f\nPressione 'J' para jogar\n\n", timeElapsed);
}


//GamePlayState----------------------------

GamePlayState::GamePlayState(SM::StateMachine* pStateMachine, Managers::Graphics* pGraphicsManager):SM::State(pStateMachine){
    timeElapsed = 0;
    playText = pGraphicsManager->createText(0, "JOGANDO", 15);
    playTextPosX = 0;
    playTextPosY = 0;
    textSpeed = 50;
    pLevel = new World::Level(pGraphicsManager);
    pLevel->loadMap("../assets/mapa1.txt");
}

GamePlayState::~GamePlayState(){
    delete pLevel;
}

void GamePlayState::enter(){
    printf("Entrando no jogo\n");
}

void GamePlayState::exit(){
    printf("Saindo do jogo\n");
}

void GamePlayState::update(float dt, Managers::Events* pEvents){
    timeElapsed += dt;

    pLevel->update(dt, pEvents);
}

void GamePlayState::render(Managers::Graphics* pGraphicsManager){
    pGraphicsManager->setTextPos(playText, playTextPosX, playTextPosY);
    pGraphicsManager->drawText(playText);
    pLevel->render(pGraphicsManager);
    //printf("Jogando\nTempo decorrido: %f\n\n", timeElapsed);
}



//GameStateMachine-------------------------------------



GameStateMachine::GameStateMachine(Managers::Graphics* pGraphicsManager){
    printf("criando maquina de estados\n");

    SM::State* state = static_cast<SM::State*>(new GameMenuState(static_cast<StateMachine*>(this), pGraphicsManager));
    addState(state);
    state = static_cast<SM::State*>(new GamePlayState(static_cast<StateMachine*>(this), pGraphicsManager));
    addState(state);
    printf("estados criados\n");
    currentStateID = GameMenuStateID;
}

GameStateMachine::~GameStateMachine(){

    
}