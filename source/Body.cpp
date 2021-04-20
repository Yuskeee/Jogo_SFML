#include "Body.h"


Body::Body(const sf::Vector2<float>& pos, const sf::Vector2<float>& vel, const sf::Vector2<float>& rect, bool isGrounded, beingType type): Being(type, pos, vel){
    this->rect = rect;
    this->isGrounded = isGrounded;
}

Body::~Body(){

}

void Body::onCollide(Body* other, float dt){

}

void Body::setRect(const sf::Vector2<float>& rect){
    this->rect = rect;
}

void Body::setGrounded(const bool& isGrounded){
    this->isGrounded = isGrounded;
}

const sf::Vector2<float> Body::getRect() const{
    return rect;
}

const bool Body::getGrounded() const{
    return isGrounded;
}

const bool Body::isGravitable() const{
    return gravitableBeingTypes[type];
}