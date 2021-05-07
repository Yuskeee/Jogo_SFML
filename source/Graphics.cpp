#include "Graphics.h"

using namespace Managers;

Graphics::Graphics(int screenWidth, int screenHeight, const char* windowName):
screenWidth(screenWidth), screenHeight(screenHeight){

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

const bool Graphics::isWindowOpen()const{
    return screen.isOpen();
}

void Graphics::closeWindow(){
    screen.close();
}

const textureID Graphics::loadTexture(const char* file){

    auto it = loadedTextures.find(file);

    if(it != loadedTextures.end())//se a textura ja foi carregada
        return it->second;//retorna o id

    else{
        sf::Texture* newTexture = new sf::Texture();

        if(!newTexture->loadFromFile(file)){
            printf("error loading file\n");
            return -1;//problema ao carregar o arquivo
        }

        textures.push_back(newTexture);

        loadedTextures[file] = textures.size()-1;//adiciona o id da textura no mapa de texturas carregadas
        return textures.size()-1;//retorna a posicao que guarda a nova textura
    }
}

const spriteID Graphics::createSprite(textureID baseTexture){

    if(baseTexture >= textures.size()){
        printf("ERROR: texture id out of range\n");
        return -1;
    }
    else{
        sf::Sprite* newSprite = new sf::Sprite(*textures[baseTexture]);

        auto i = sprites.begin();
        spriteID newSpriteID = 0;
        for(newSpriteID, i; i != sprites.end() && *i != NULL; i++, newSpriteID++);//procura por uma posicao vaga ou pelo fim

        if(i == sprites.end()){//nao encontrou posicao vaga insere no fim
            sprites.push_back(newSprite);
        }
        else{
            i.getElement()->setInfo(newSprite);
        }

        return newSpriteID;

    }
}

void Graphics::removeSprite(spriteID sprite){

    if(sprite >= sprites.size())
        printf("ERROR: sprite id out of range\n");
    else{
        auto i = sprites.begin();
        for(sprite; sprite > 0; i++, sprite--);
        delete *i;

        if(sprite == sprites.size()-1)
            sprites.erase(i);
        else
            (i.getElement())->setInfo(NULL);
    }
}

void Graphics::setSpriteRect(spriteID sprite, const spriteRect& rect){

    if(sprite >= sprites.size())
        printf("ERROR: sprite id out of range\n");
    else
        sprites[sprite]->setTextureRect(rect);

}

void Graphics::setSpritePos(spriteID sprite, float x, float y){

    if(sprite >= sprites.size())
        printf("ERROR: sprite id out of range\n");
    else{
        sf::Vector2f pos(x, y);
        sprites[sprite]->setPosition(pos);
    }
}

void Graphics::drawSprite(spriteID sprite){

    if(sprite >= sprites.size())
        printf("ERROR: sprite id out of range\n");
    else
        screen.draw(*sprites[sprite]);

}

void Graphics::setBackground(spriteID sprite){

    if(sprite >= sprites.size())
        printf("ERROR: sprite id out of range\n");
    else{
        backgroundSprite = sprite;

        float factorX = (float)screenWidth/sprites[sprite]->getTextureRect().width;
        float factorY = (float)screenHeight/sprites[sprite]->getTextureRect().height;
        sprites[sprite]->setScale(factorX, factorY);
        sprites[sprite]->setPosition(0, 0);
    }
}

const fontID Graphics::loadFont(const char* file){

    sf::Font* newFont = new sf::Font();

    if (!newFont->loadFromFile(file))
        return -1;

    fonts.push_back(newFont);
    return fonts.size()-1;

}

const textID Graphics::createText(fontID baseFont, std::string text, int size){

    sf::Text* newText = new sf::Text(text, *fonts[baseFont], size);

    texts.push_back(newText);
    return texts.size()-1;
}

void Graphics::setTextColor(textID text, int red, int green, int blue, int alpha){

    texts[text]->setFillColor(sf::Color(red, green, blue, alpha));
}

void Graphics::setString(textID text, std::string newText){
    texts[text]->setString(newText);
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
        if(backgroundSprite >= 0)//se houver um plano de fundo definido
            screen.draw(*sprites[backgroundSprite]);
    }
}
