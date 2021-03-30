#include "Entity.h"

using namespace Entities;

Entity::Entity(Managers::Graphics* pGameGraphicsManager, sf::Vector2<float> pos, sf::Vector2<float> vel, sf::Vector2<float> rect, Managers::textureID idT, Managers::spriteID idS):
pos(pos), vel(vel), rect(rect), vulnerabilidade(), idTextura(idT), idSprite(idS), frame(0, 0, 0, 0){

}

Entity::~Entity(){
}

void Entity::draw(Managers::Graphics* pGameGraphicsManager){
    pGameGraphicsManager->setSpritePos(idSprite, pos.x, pos.y);
    pGameGraphicsManager->drawSprite(idSprite);
}

void Entity::setPos(sf::Vector2<float> pos){
    this->pos = pos;
}

void Entity::setVel(sf::Vector2<float> vel){
    this->vel = vel;
}

void Entity::setGrounded(bool isGrounded){
    this->isGrounded = isGrounded;
}

const sf::Vector2<float> Entity::getPos() const{
return pos;
}

const sf::Vector2<float> Entity::getVel() const{
return vel;
}

const sf::Vector2<float> Entity::getRect() const{
return rect;
}
