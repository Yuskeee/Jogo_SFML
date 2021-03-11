#include "main.h"

int main(){

    Graphics gGraphics(400, 300, "teste");

    windowHandle gWindowHandle = gGraphics.getWindowHandle();
    Events gEvents(gWindowHandle);
    
    Game game(&gGraphics, &gEvents);

    std::chrono::time_point<std::chrono::steady_clock> tStart;//variaveis para marcar o tempo
    std::chrono::time_point<std::chrono::steady_clock> tEnd;
    float dt;

    while(gGraphics.isWindowOpen()){


        tEnd = std::chrono::steady_clock::now();//marca o tempo final
        dt = std::chrono::duration_cast<std::chrono::microseconds>(tEnd - tStart).count()*0.000001;//calcula o tempo decorrido e armazena em um float
        tStart = std::chrono::steady_clock::now();//marca o tempo inicial

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

    //apenas para testes--------------------------------------------------
    testText = gameGraphics->createText(gameGraphics->loadFont("../fonts/04B_30__.TTF"),"teste", 20);
    textPosX = 0;
    textPosY = 0;
    //--------------------------------------------------------------------------
}

Game::~Game(){


}

void Game::update(float dt){

    gameEvents->pollAll();//verifica os eventos

    if (gameEvents->getCloseEvent()){
            gameGraphics->closeWindow();
    }
        
    //gameStateMachine->update(dt);//futuramente

    //apenas para testes--------------------------------------------------
    if(gameEvents->keyDown(Events::keycode::W))
        textPosY += -0.1;
    if(gameEvents->keyDown(Events::keycode::D))
        textPosX += 0.1;
    if(gameEvents->keyDown(Events::keycode::S))
        textPosY += 0.1;
    if(gameEvents->keyDown(Events::keycode::A))
        textPosX += -0.1;
    //--------------------------------------------------------------------

}

void Game::render(){
    //gameStateMachine->render();//futuramente
    gameGraphics->setTextPos(testText, textPosX, textPosY);
    gameGraphics->drawText(testText);
    gameGraphics->render();

}

void Game::setGraphics(Graphics* gameGraphics){
    this->gameGraphics = gameGraphics;
}

void Game::setEvents(Events* gameEvents){
    this->gameEvents = gameEvents;
}