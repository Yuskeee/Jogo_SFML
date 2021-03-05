#include <Graphics.h>

Graphics::Graphics(int screenWidth, int screenHeight, const char* windowName){

    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    createWindow(screenWidth, screenHeight, windowName);

}
Graphics::~Graphics(){

    for(int i = 0; i < sprites.size(); i++)
        delete sprites[i];

    for(int i = 0; i < textures.size(); i++)
        delete textures[i];

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

void Graphics::render(){

    screen.display();
    screen.clear();
    screen.draw(*sprites[backgroundSprite]);
}