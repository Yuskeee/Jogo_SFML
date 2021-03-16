#include "GameStateMachine.h"

//GameMenuState----------------------------

GameMenuState::GameMenuState(StateMachine* pStateMachine):State(pStateMachine){
    timeElapsed = 0;
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
    if(pEvents->keyPressed(Events::keycode::A))
        pStateMachine->changeState(GamePlayStateID);
    
}

void GameMenuState::render(Graphics* pGraphics){
    printf("Estado: Menu\nTempo decorrido: %f\nPressione 'A' para jogar\n\n", timeElapsed);
}


//GamePlayState----------------------------

GamePlayState::GamePlayState(StateMachine* pStateMachine):State(pStateMachine){
    timeElapsed = 0;
}

GamePlayState::~GamePlayState(){

}

void GamePlayState::enter(){
    printf("Entrando no jogo\n");
}

void GamePlayState::exit(){
    printf("Saindo do jogo\n");
}

void GamePlayState::update(float dt, Events* pEvents){
    timeElapsed += dt;
}

void GamePlayState::render(Graphics* pGraphics){
    printf("Jogando\nTempo decorrido: %f\n\n", timeElapsed);
}



//GameStateMachine-------------------------------------



GameStateMachine::GameStateMachine(){

    State* state = static_cast<State*>(new GameMenuState(static_cast<StateMachine*>(this)));
    addState(state);
    state = static_cast<State*>(new GamePlayState(static_cast<StateMachine*>(this)));
    addState(state);

    currentStateID = GameMenuStateID;
}

GameStateMachine::~GameStateMachine(){

    
}