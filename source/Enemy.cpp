#include "Enemy.h"
#include "Level.h"

using namespace Entities;

const Player* Enemy::p1 = NULL;
const Player* Enemy::p2 = NULL;

Enemy::Enemy(Managers::Graphics* pGraphicsManager, World::Level* pLevel, const sf::Vector2<float>& pos, const sf::Vector2<float>& vel, const sf::Vector2<float>& rect, const float accel, const float mVel):
Entity(pGraphicsManager, pLevel, pos, vel), Body(pos, vel, rect), Being(zombie/*por padrao*/, pos, vel), acceleration(accel), velMax(mVel){

}

Enemy::~Enemy(){
}

void Enemy::setTarget(){

    if(p1||p2){
        if(!p2)
            target = p1;
        else if(!p1)
            target = p2;
        else{
            float distanceTo1 = ((p1->getPos()- pos).x*(p1->getPos()- pos).x) + ((p1->getPos()- pos).y*(p1->getPos()- pos).y);
            float distanceTo2 = ((p2->getPos()- pos).x*(p2->getPos()- pos).x) + ((p2->getPos()- pos).y*(p2->getPos()- pos).y);
            target = (distanceTo1 <= distanceTo2) ? p1 : p2;
        }
    }
    else
        target = NULL;
}

void Enemy::setPlayer1(const Player *p1){
    Enemy::p1 = p1;
}

void Enemy::setPlayer2(const Player *p2){
    Enemy::p2 = p2;
}



const Player* Enemy::getTarget(){
    return target;
}

const Player* Enemy::getP1(){
    return p1;
}

const Player* Enemy::getP2(){
    return p2;
}

