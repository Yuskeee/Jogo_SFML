#include "Entidade.h"

Entidade::Entidade(Graphics* pGraphics, sf::Vector2<float> pos, sf::Vector2<float> vel, sf::Vector2<float> rect, textureID idT, spriteID idS):
pos(pos), vel(vel), rect(rect), vulnerabilidade(), idTextura(idT), idSprite(idS), frame(0, 0, 0, 0){

}

Entidade::~Entidade(){
}

void Entidade::draw(Graphics* gameGraphics){
    gameGraphics->setSpritePos(idSprite, pos.x, pos.y);
    gameGraphics->drawSprite(idSprite);
}

void Entidade::setPos(sf::Vector2<float> pos){
    this->pos = pos;
}

void Entidade::setVel(sf::Vector2<float> vel){
    this->vel = vel;
}

const sf::Vector2<float> Entidade::getPos() const{
return pos;
}

const sf::Vector2<float> Entidade::getRect() const{
return rect;
}
