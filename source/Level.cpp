#include "Level.h"

using namespace World;

Level::Level(Managers::Graphics* pGraphicsManager):map(pGraphicsManager), LevelPhysics(&map){
    this->pGraphicsManager = pGraphicsManager;
    backgroundSprite = -1;
}

Level::~Level(){
    int id;
    for(int i = 0; i < entities.size(); i++){
        id = entities[i]->getId();
        LevelPhysics.removeBody(id);
        delete entities[i];
    }
}

void Level::update(float dt, Managers::Events* pEvents){

    for(auto i = entities.begin(); i != entities.end(); i++){//da para fazer esses loops com iterator tambem (talvez seja melhor)
        i->update(dt, pEvents);
    }

    for(auto i = entities.begin(); i != entities.end(); i++)//remove da lista as entidades com 0 ou menos vida
        if(i->getLives() <= 0){
            removeBody(i->getId());
            removeEntity(i->getId());
        }

    LevelPhysics.applyGravity(dt);
    LevelPhysics.collideMap();
    LevelPhysics.collideBodies();
}

void Level::render(){
    map.draw(pGraphicsManager);
    for(int i = 0; i < entities.size(); i++)
        entities[i]->draw();

}

void Level::addEntity(Entities::Entity* pEntity){//adiciona uma entidade no vetor de entidades
        entities.push_back(pEntity);
}

void Level::removeEntity(int id){

    
    for(auto i = entities.begin(); i != entities.end(); i++){
        if(i->getId() == id){
            delete *i;
            entities.erase(i);
            break;
        }
    }
}

void Level::addBody(Body* pBody){
    LevelPhysics.addBody(pBody);
}
void Level::removeBody(int id){
    LevelPhysics.removeBody(id);
}

void Level::startLevel(int n, int players){
    loadMap(levelMapFiles[n]);

    Entities::Player* p1 = new Entities::Player(pGraphicsManager, this, sf::Vector2f(20, 20), sf::Vector2f(0, 0));
    addEntity(static_cast<Entities::Entity*>(p1));//adiciona o player na lista de entidades da fase
    addBody(static_cast<Body*>(p1));//adiciona o player na lista de corpos da fisica

    if(players > 1){
        Entities::Player* p2 = new Entities::Player(pGraphicsManager, this, sf::Vector2f(50, 20), sf::Vector2f(0, 0), false);
        addEntity(static_cast<Entities::Entity*>(p2));//adiciona o player na lista de entidades da fase
        LevelPhysics.addBody(static_cast<Body*>(p2));//adiciona o player na lista de corpos da fisica
        Entities::Enemy::setPlayers(p1, p2);
    }
    else
        Entities::Enemy::setPlayers(p1);
 
    Entities::Zombie* z1 = new Entities::Zombie(pGraphicsManager, this, sf::Vector2f(80, 20), sf::Vector2f(0, 0));
    addEntity(static_cast<Entities::Entity*>(z1));//adiciona o zumbi na lista de entidades da fase
    addBody(static_cast<Body*>(z1));//adiciona o zumbi na lista de corpos da fisica

    Entities::Flower* f1 = new Entities::Flower(pGraphicsManager, this, sf::Vector2f(100, 40));
    addEntity(static_cast<Entities::Entity*>(f1));//adiciona a flor na lista de entidades da fase
    addBody(static_cast<Body*>(f1));//adiciona a flor na lista de corpos da fisica


    backgroundSprite = pGraphicsManager->createSprite(pGraphicsManager->loadTexture(levelBackgroundFiles[n]));
    pGraphicsManager->setBackground(backgroundSprite);

}

void Level::loadMap(const char* arquivo){
    map.load(arquivo);
}

Managers::Graphics* Level::getGraphicsManager(){
    return pGraphicsManager;
}
