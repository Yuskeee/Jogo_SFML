#include "Being.h"

int Being::nBeings = 0;

Being::Being(const sf::Vector2<float>& pos, const sf::Vector2<float>& vel){
    id = nBeings++;
    this->pos = pos;
    this->vel = vel;
}

Being::~Being(){
}

void Being::setPos(const sf::Vector2<float>& pos){
    this->pos = pos;
}

void Being::setVel(const sf::Vector2<float>& vel){
    this->vel = vel;
}

const int Being::getId() const{
    return id;
}

const sf::Vector2<float> Being::getPos() const{
    return pos;
}

const sf::Vector2<float> Being::getVel() const{
    return vel;
}