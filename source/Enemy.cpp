#include "Enemy.h"

using namespace Entities;

const Player* Enemy::p1 = NULL;
const Player* Enemy::p2 = NULL;

Enemy::Enemy(Managers::Graphics* pGraphicsManager, sf::Vector2<float> pos, sf::Vector2<float> vel, sf::Vector2<float> rect, Managers::textureID idT, Managers::spriteID idS, const float accel, const float mVel):
Entity(pGraphicsManager, pos, vel, rect, idT, idS), acceleration(accel), velMax(mVel){

}

Enemy::~Enemy(){

}

void Enemy::loseLife(const int damage){
	lives -= damage;
}

void Enemy::setPlayers(const Player *p1, const Player *p2){
    Enemy::p1 = p1;
    Enemy::p2 = p2;
}

const Player* Enemy::getP1(){
    return p1;
}

const Player* Enemy::getP2(){
    return p2;
}
