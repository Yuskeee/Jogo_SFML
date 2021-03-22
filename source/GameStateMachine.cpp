#include "GameStateMachine.h"

//GameMenuState----------------------------

GameMenuState::GameMenuState(StateMachine* pStateMachine, Graphics* pGraphics):State(pStateMachine){
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

void GameMenuState::update(float dt, Events* pEvents){
    timeElapsed += dt;

    if(pEvents->keyDown(Events::keycode::W))
        menuTextPosY -= textSpeed*dt;
    if(pEvents->keyDown(Events::keycode::D))
        menuTextPosX += textSpeed*dt;
    if(pEvents->keyDown(Events::keycode::S))
        menuTextPosY += textSpeed*dt;
    if(pEvents->keyDown(Events::keycode::A))
        menuTextPosX -= textSpeed*dt;


    if(pEvents->keyPressed(Events::keycode::J))
        pStateMachine->changeState(GamePlayStateID);

}

void GameMenuState::render(Graphics* pGraphics){
    pGraphics->setTextPos(menuText, menuTextPosX, menuTextPosY);
    pGraphics->drawText(menuText);
    printf("Estado: Menu\nTempo decorrido: %f\nPressione 'J' para jogar\n\n", timeElapsed);
}


//GamePlayState----------------------------

GamePlayState::GamePlayState(StateMachine* pStateMachine, Graphics* pGraphics):State(pStateMachine){
    timeElapsed = 0;
    playText = pGraphics->createText(0, "JOGANDO", 15);
    playTextPosX = 0;
    playTextPosY = 0;
    textSpeed = 50;
    pFase = new Fase(pGraphics);
}

GamePlayState::~GamePlayState(){
    delete pFase;
}

void GamePlayState::enter(){
    printf("Entrando no jogo\n");
}

void GamePlayState::exit(){
    printf("Saindo do jogo\n");
}

void GamePlayState::update(float dt, Events* pEvents){
    timeElapsed += dt;

    pFase->update(dt, pEvents);
}

void GamePlayState::render(Graphics* pGraphics){
    pGraphics->setTextPos(playText, playTextPosX, playTextPosY);
    pGraphics->drawText(playText);
    pFase->render();
    printf("Jogando\nTempo decorrido: %f\n\n", timeElapsed);
}



//GameStateMachine-------------------------------------



GameStateMachine::GameStateMachine(Graphics* pGraphics){
    printf("criando maquina de estados\n");

    State* state = static_cast<State*>(new GameMenuState(static_cast<StateMachine*>(this), pGraphics));
    addState(state);
    state = static_cast<State*>(new GamePlayState(static_cast<StateMachine*>(this), pGraphics));
    addState(state);
    printf("estados criados\n");
    currentStateID = GameMenuStateID;
}

GameStateMachine::~GameStateMachine(){

    
}