#include "main.h"

//Função Main
int main(){

    Game game;

    game.run();

    return 0;
}

Game::Game(){

    gameGraphicsManager = new Managers::Graphics(WINDOW_WIDTH, WINDOW_HEIGHT, "As Aventuras do Alienzinho");

    gameEventsManager = new Managers::Events(gameGraphicsManager->getWindowHandle());

    gameGraphicsManager->loadFont("../fonts/04B_30__.TTF");//carrega uma fonte no id 0

    gameStateMachine = new GameSM::GameStateMachine(gameGraphicsManager);
}

Game::~Game(){
    delete gameStateMachine;
}

void Game::run(){
    sf::Clock clock;
    float dt;

    while(gameGraphicsManager->isWindowOpen()){

        dt = clock.getElapsedTime().asSeconds();
        clock.restart();

        update(dt);
        render();
    }

}

void Game::update(const float dt){

    gameEventsManager->pollAll();//verifica os eventos

    if (gameEventsManager->getCloseEvent()){
            gameGraphicsManager->closeWindow();
    }

    gameStateMachine->update(dt, gameEventsManager);

}

void Game::render(){
    gameStateMachine->render(gameGraphicsManager);

    gameGraphicsManager->render();
}

//void Game::setGraphics(Managers::Graphics* gameGraphicsManager){
//    this->gameGraphicsManager = gameGraphicsManager;
//}
//
//void Game::setEvents(Managers::Events* gameEventsManager){
//    this->gameEventsManager = gameEventsManager;
//}
//
//void Game::setStateMachine(SM::StateMachine* gameStateMachine){
//    this->gameStateMachine = gameStateMachine;
//}
