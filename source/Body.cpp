#include "Body.h"


Body::Body(bodyType type, const sf::Vector2<float>& pos, const sf::Vector2<float>& vel, const sf::Vector2<float>& rect, bool isGrounded): Being(pos, vel){
    this->type = type;
    this->rect = rect;
    this->isGrounded = isGrounded;
}

Body::~Body(){


}

void Body::onCollide(Body* other){

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