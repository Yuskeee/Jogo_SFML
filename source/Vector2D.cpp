#include "Vector2D.h"

Vector2D::Vector2D(){

}

Vector2D::Vector2D(float x, float y){

    setX(x);
    setY(y);
}

Vector2D::~Vector2D(){

}

void Vector2D::setX(float x){
    this->x = x;
}

void Vector2D::setY(float y){
    this->y = y;
}

float Vector2D::getX() const{
    return x;
}

float Vector2D::getY() const{
    return y;
}

void Vector2D::operator=(const Vector2D& vec){
    x = vec.x;
    y = vec.y;
}

void Vector2D::operator+=(const Vector2D& vec){
    x += vec.x;
    y += vec.y;
}

void Vector2D::operator-=(const Vector2D& vec){
    x -= vec.x;
    y -= vec.y;
}

Vector2D operator+(const Vector2D& vec1, const Vector2D& vec2){
    Vector2D sum(vec1.getX() + vec2.getX(), vec1.getY() + vec2.getY());
    return sum;
}

Vector2D operator-(const Vector2D& vec1, const Vector2D& vec2){
    Vector2D sub(vec1.getX() - vec2.getX(), vec1.getY() - vec2.getY());
    return sub;
}