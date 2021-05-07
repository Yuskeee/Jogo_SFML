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
            if (lastEvent.type == sf::Event::Closed){
                closeEvent = true;
            }

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

const bool Events::keyPressed(const keycode key)const{
    return keysPressed[key];
}

const bool Events::keyReleased(const keycode key)const{
    return keysReleased[key];
}

const bool Events::keyDown(const keycode key)const{
    return keysDown[key];
}

const std::string Events::getInputAsString(){

    std::string input = "";
    for(char i = 0; i < 26; i++)
        if(keysPressed[i])
            input += ('A' + (char)i);

    return input;
}

const bool Events::getCloseEvent() const{
    return closeEvent;
}
