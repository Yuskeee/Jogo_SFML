#include "main.h"


int main(){

    Managers::Graphics gameGraphicsManager(400, 300, "teste");

    gameGraphicsManager.loadFont("../fonts/04B_30__.TTF");//carrega uma fonte no id 0

    Managers::windowHandle gWindowHandle = gameGraphicsManager.getWindowHandle();
    Managers::Events gEvents(gWindowHandle);
    
    Game game(&gameGraphicsManager, &gEvents);

    sf::Clock clock;
    float dt;


    while(gameGraphicsManager.isWindowOpen()){



        dt = clock.getElapsedTime().asSeconds();
        clock.restart();

        game.update(dt);
        game.render();
    }

    return 0;
}

Game::Game(){


}

Game::Game(Managers::Graphics* gameGraphicsManager, Managers::Events* gameEventsManager){

    setGraphics(gameGraphicsManager);
    setEvents(gameEventsManager);

    setStateMachine(new GameSM::GameStateMachine(gameGraphicsManager));

}

Game::~Game(){

    delete gameStateMachine;
}

void Game::update(float dt){

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

void Game::setGraphics(Managers::Graphics* gameGraphicsManager){
    this->gameGraphicsManager = gameGraphicsManager;
}

void Game::setEvents(Managers::Events* gameEventsManager){
    this->gameEventsManager = gameEventsManager;
}

void Game::setStateMachine(SM::StateMachine* gameStateMachine){
    this->gameStateMachine = gameStateMachine;
}