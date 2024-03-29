#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include <SFML/Graphics.hpp>
#include "List.h"
#include <map>

namespace Managers{

typedef sf::RenderWindow* windowHandle;
typedef sf::Rect<int> spriteRect;//typedefs para usar tipos da sfml fora desse arquivo

typedef int textureID;//int que representa a posicao de uma textura na lista
typedef int spriteID;//int que representa a posicao de um sprite na lista
typedef int fontID;//int que representa a posicao de uma fonte na lista
typedef int textID;//int que representa a posicao de uma fonte na lista

class Graphics{

private:
    std::map<const char*, textureID> loadedTextures;

    sf::RenderWindow screen;//objeto janela da sfml

    const int screenWidth, screenHeight; //altura e largura da tela em pixels

    //cria a janela com estilo padrao
    void createWindow(int screenWidth, int screenHeight, const char* windowName);

    Container::List<sf::Texture*> textures;//lista de texturas carregadas
    Container::List<sf::Sprite*> sprites;//lista de sprites criados
    Container::List<sf::Font*> fonts;//lista de fontes carregadas
    Container::List<sf::Text*> texts;//lista de textos criados

    spriteID backgroundSprite;//id do sprite selecionado como fundo

public:
    Graphics(int screenWidth = 800, int screenHeight = 600, const char* windowName = "window");
    ~Graphics();

    //retorna um ponteiro para a janela. Util se outras classes precisarem acessar funcoes do objeto janela
    windowHandle getWindowHandle();

    const bool isWindowOpen()const;
    void closeWindow();

    const textureID loadTexture(const char* file);//carrega textura de arquivo

    const spriteID createSprite(textureID baseTexture);//cria um sprite baseado em uma textura, retorna seu id
    void removeSprite(spriteID sprite);
    void setSpriteRect(spriteID sprite, const spriteRect& rect);//seleciona parte da textura para ser renderizada
    void setSpritePos(spriteID sprite, float x, float y);//modifica a posicao do sprite
    void drawSprite(spriteID sprite);//desenha o sprite na tela

    void setBackground(spriteID sprite);//usa um sprite como plano de fundo

    const fontID loadFont(const char* file);
    const textID createText(fontID baseFont, std::string text, int size);//cria um texto baseado em uma fonte, retorna seu id
    void setTextPos(textID text, float x, float y);
    void setTextColor(textID text, int red, int green, int blue, int alpha);
    void setString(textID text, std::string newText);
    void drawText(textID text);//desenha o texto na tela



    void render();//exibe na tela o que foi desenhado

};
}

#endif
