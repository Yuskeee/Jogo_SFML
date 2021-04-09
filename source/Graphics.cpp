#include "Graphics.h"

using namespace Managers;

Graphics::Graphics(int screenWidth, int screenHeight, const char* windowName){

    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    createWindow(screenWidth, screenHeight, windowName);

    backgroundSprite = -1;

}
Graphics::~Graphics(){

    for(int i = 0; i < sprites.size(); i++)
        delete sprites[i];

    for(int i = 0; i < textures.size(); i++)
        delete textures[i];

    for(int i = 0; i < texts.size(); i++)
        delete texts[i];

    for(int i = 0; i < fonts.size(); i++)
        delete fonts[i];

}

void Graphics::createWindow(int screenWidth, int screenHeight, const char* windowName){

    screen.create(sf::VideoMode(screenWidth, screenHeight), windowName);
}

windowHandle Graphics::getWindowHandle(){
    return &screen;
}

bool Graphics::isWindowOpen(){
    return screen.isOpen();
}

void Graphics::closeWindow(){
    screen.close();
}

textureID Graphics::loadTexture(const char* file){

    sf::Texture* newTexture = new sf::Texture();

    if(!newTexture->loadFromFile(file))
        return -1;//problema ao carregar o arquivo

    textures.push_back(newTexture);

    return textures.size()-1;//retorna a posicao que guarda a nova textura
}

spriteID Graphics::createSprite(textureID baseTexture){


    sf::Sprite* newSprite = new sf::Sprite(*textures[baseTexture]);
    sprites.push_back(newSprite);

    return sprites.size()-1;

}

void Graphics::removeSprite(spriteID sprite){
    auto i = sprites.begin();
    for(sprite; sprite > 0; i++, sprite--);

    sprites.erase(i);
}

void Graphics::setSpriteRect(spriteID sprite, const spriteRect& rect){

    sprites[sprite]->setTextureRect(rect);

}

void Graphics::setSpritePos(spriteID sprite, float x, float y){

    sf::Vector2f pos(x, y);
    sprites[sprite]->setPosition(pos);

}

void Graphics::drawSprite(spriteID sprite){

    screen.draw(*sprites[sprite]);

}

void Graphics::setBackground(spriteID sprite){

    backgroundSprite = sprite;

    float factorX = screenWidth/sprites[sprite]->getTextureRect().width;
    float factorY = screenHeight/sprites[sprite]->getTextureRect().height;

    sprites[sprite]->scale(factorX, factorY);
    sprites[sprite]->setPosition(0, 0);

}

fontID Graphics::loadFont(const char* file){

    sf::Font* newFont = new sf::Font();

    if (!newFont->loadFromFile(file))
        return -1;

    fonts.push_back(newFont);
    return fonts.size()-1;

}

textID Graphics::createText(fontID baseFont, const char* text, int size){

    sf::Text* newText = new sf::Text(text, *fonts[baseFont], size);

    texts.push_back(newText);
    return texts.size()-1;
}

void Graphics::setTextColor(textID text, int red, int green, int blue, int alpha){

    texts[text]->setFillColor(sf::Color(red, green, blue, alpha));
}

void Graphics::drawText(textID text){
    screen.draw(*texts[text]);

}

void Graphics::setTextPos(textID text, float x, float y){

    sf::Vector2f pos(x, y);
    texts[text]->setPosition(pos);
}

void Graphics::render(){
    if(screen.isOpen()){
        screen.display();
        screen.clear();
        if(backgroundSprite > 0)//se houver um plano de fundo definido
            screen.draw(*sprites[backgroundSprite]);
    }
}
