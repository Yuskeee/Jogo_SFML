#ifndef _EVENTS_H
#define _EVENTS_H

#include <SFML/Graphics.hpp>

namespace Managers{

typedef sf::RenderWindow* windowHandle;

class Events{

public: typedef sf::Keyboard::Key keycode;

private:

    windowHandle window;//ponteiro para janela na qual buscar por eventos

    bool keysPressed[sf::Keyboard::KeyCount];//marca todas as teclas pressionadas na ultima verificacao
    bool keysReleased[sf::Keyboard::KeyCount];//marca todas as teclas liberadas na ultima verificacao
    bool keysDown[sf::Keyboard::KeyCount];//marca todas as teclas atualmente pressionadas

    bool closeEvent;//marca se o usuario tentou fechar a janela

public:

    Events();
    Events(windowHandle window);

    ~Events();

    void setWindow(windowHandle window);

    void pollAll();//checa teclas pressionadas, teclas liberadas, e se a janela foi fechada

    bool keyPressed(keycode key);//busca por uma certa tecla na lista de pressionadas
    bool keyReleased(keycode key);//busca por uma certa tecla na lista de liberadas
    bool keyDown(keycode key);//busca por uma certa tecla na lista de atualmente pressionadas

    bool getCloseEvent();

};
}

#endif