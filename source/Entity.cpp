#include "Entity.h"

#include "Level.h"

using namespace Entities;

Entity::Entity(Managers::Graphics* pGraphicsManager, World::Level* pLevel, const sf::Vector2<float>& pos, const sf::Vector2<float>& vel, beingType type):
Being(type, pos, vel), pGraphicsManager(pGraphicsManager), lives(5), vulnerability(), frame(0, 0, 0, 0){
    this->pLevel = pLevel;
    idSprite = -1;
    idTextura = -1;
}

Entity::~Entity(){
    if(idSprite >= 0)
        pGraphicsManager->removeSprite(idSprite);
}

void Entity::draw(){
    pGraphicsManager->setSpriteRect(idSprite, frame);
    pGraphicsManager->setSpritePos(idSprite, pos.x, pos.y);
    pGraphicsManager->drawSprite(idSprite);
}

void Entity::damage(int damage){
    if(vulnerability){
        lives -= damage;
        vulnerability = false;
    }
}

int Entity::getLives() const{
    return lives;
}

void Entity::saveEntityInfo(std::ofstream& out) const{
    out <<  this->getType()             << " " <<
            this->getId()               << " " <<
            this->idTextura             << " " <<
            this->idSprite              << " " <<
            this->frame.left            << " " <<
            this->frame.top             << " " <<
            this->frame.width           << " " <<
            this->frame.height          << " " <<
            this->getPos().x            << " " <<
            this->getPos().y            << " " <<
            this->getVel().x            << " " <<
            this->getVel().y            << " " <<
            this->getLives()            << " " <<
            this->vulnerability;

}

void Entity::saveEntity(std::ofstream& out) const{

}

void Entity::loadEntity(std::ifstream& in){
    std::string contents;
    getline(in, contents);
}
