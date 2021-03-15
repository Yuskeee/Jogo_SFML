#include "Entidade.h"

Entidade::Entidade(sf::Vector2 pos, sf::Vector2 vel, sf::Vector2 , TextureID idT, SpriteID idS):
pos(pos), vel(vel), rect(rect), vulnerabilidade(), idTextura(idT), idSprite(idS){
}

Entidade::~Entidade(){
}

void Entidade::desenhar(Graphics &gameGraphics){
gameGraphics.drawSprite(idSprite);
}

const Vetor2F Entidade::getPos() const{
return pos;
}

const Vetor2F Entidade::getRect() const{
return rect;
}
