#include "Entidade.h"

Entidade::Entidade(sf::Vector2<float> pos, sf::Vector2<float> vel, sf::Vector2<float> , textureID idT, spriteID idS):
pos(pos), vel(vel), rect(rect), vulnerabilidade(), idTextura(idT), idSprite(idS){
}

Entidade::~Entidade(){
}

void Entidade::desenhar(Graphics &gameGraphics){
gameGraphics.drawSprite(idSprite);
}

const sf::Vector2<float> Entidade::getPos() const{
return pos;
}

const sf::Vector2<float> Entidade::getRect() const{
return rect;
}
