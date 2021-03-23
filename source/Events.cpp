#include "Events.h"

using namespace Managers;

Events::Events(){
    closeEvent = false;

    for(int i = 0; i < sf::Keyboard::KeyCount; i++)
        keysDown[i] = false;//esse vetor precisa ser inicializado porque nao é limpo a cada verificacao
}

Events::Events(windowHandle window){
    closeEvent = false;

    setWindow(window);

    for(int i = 0; i < sf::Keyboard::KeyCount; i++)
        keysDown[i] = false;
}

Events::~Events(){

}

void Events::setWindow(windowHandle window){

    this->window = window;

}

void Events::pollAll(){

    sf::Event lastEvent;

    for(int i = 0; i < sf::Keyboard::KeyCount; i++){
        keysPressed[i] = false;
        keysReleased[i] = false;
    }

    while (window->pollEvent(lastEvent)){
            if (lastEvent.type == sf::Event::Closed)
                closeEvent = true;

            else if(lastEvent.type == sf::Event::KeyPressed){
                keysPressed[lastEvent.key.code] = true;
                keysDown[lastEvent.key.code] = true;
            }

            else if(lastEvent.type == sf::Event::KeyReleased){
                keysReleased[lastEvent.key.code] = true;
                keysDown[lastEvent.key.code] = false;
            }
            //adicionar mais eventos se necessario: mouse, aumento de janela, etc.
        }
}

bool Events::keyPressed(keycode key){
    return keysReleased[key];
}

bool Events::keyReleased(keycode key){
    return keysReleased[key];
}

bool Events::keyDown(keycode key){
    return keysDown[key];
}

bool Events::getCloseEvent(){
    return closeEvent;
}