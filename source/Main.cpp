#include "main.h"


int main(){

    Graphics gGraphics(400, 300, "teste");

    gGraphics.loadFont("../fonts/04B_30__.TTF");//carrega uma fonte no id 0

    windowHandle gWindowHandle = gGraphics.getWindowHandle();
    Events gEvents(gWindowHandle);
    
    Game game(&gGraphics, &gEvents);

    sf::Clock clock;
    float dt;


    while(gGraphics.isWindowOpen()){



        dt = clock.getElapsedTime().asSeconds();
        clock.restart();

        game.update(dt);
        game.render();
    }

    return 0;
}

Game::Game(){


}

Game::Game(Graphics* gameGraphics, Events* gameEvents){

    setGraphics(gameGraphics);
    setEvents(gameEvents);

    setStateMachine(new GameStateMachine(gameGraphics));

}

Game::~Game(){

    delete gameStateMachine;
}

void Game::update(float dt){

    gameEvents->pollAll();//verifica os eventos

    if (gameEvents->getCloseEvent()){
            gameGraphics->closeWindow();
    }
           
    gameStateMachine->update(dt, gameEvents);

}

void Game::render(){
    gameStateMachine->render(gameGraphics);
    gameGraphics->render();
}

void Game::setGraphics(Graphics* gameGraphics){
    this->gameGraphics = gameGraphics;
}

void Game::setEvents(Events* gameEvents){
    this->gameEvents = gameEvents;
}

void Game::setStateMachine(StateMachine* gameStateMachine){
    this->gameStateMachine = gameStateMachine;
}