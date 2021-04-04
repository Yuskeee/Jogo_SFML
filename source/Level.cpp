#include "Level.h"

using namespace World;

Level::Level(Managers::Graphics* pGraphicsManager):map(pGraphicsManager), LevelPhysics(&map, &entities){
    this->pGraphicsManager = pGraphicsManager;
}

Level::~Level(){
    for(int i = 0; i < entities.size(); i++)
        delete entities[i];
}

void Level::update(float dt, Managers::Events* pEvents){
    for(int i = 0; i < entities.size(); i++)
        entities[i]->update(dt, pEvents);
    LevelPhysics.applyGravity(dt);
    LevelPhysics.collideMap();
    LevelPhysics.collideEntities();
}

void Level::render(){
    map.draw(pGraphicsManager);
    for(int i = 0; i < entities.size(); i++)
        entities[i]->draw(pGraphicsManager);
    
}

void Level::startLevel(int n){
    loadMap(levelMapFiles[n]);
    addEntity<Entities::Player>(sf::Vector2f(20, 20), sf::Vector2f(0, 0), sf::Vector2f(16, 20));

}

void Level::loadMap(const char* arquivo){
    map.load(arquivo);
}
