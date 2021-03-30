#include "Level.h"


Level::Level(Managers::Graphics* pGraphicsManager):map(pGraphicsManager), LevelPhysics(&map, &entities){
    //apenas para testes
    addEntity<Entities::Player>(pGraphicsManager, sf::Vector2f(20, 20), sf::Vector2f(0, 0), sf::Vector2f(16, 20));//futuramente isso vai ficar em uma funcao de carregar a fase junto com as outras chamadas
}

Level::~Level(){
    for(int i = 0; i < entities.size(); i++)
        delete entities[i];
}

void Level::update(float dt, Managers::Events* pEvents){
    for(int i = 0; i < entities.size(); i++)
        entities[i]->update(dt, pEvents);
    LevelPhysics.applyGravity(dt);
    LevelPhysics.collideMap(dt);
    LevelPhysics.collideEntities();
}

void Level::render(Managers::Graphics* pGraphicsManager){
    map.draw(pGraphicsManager);
    for(int i = 0; i < entities.size(); i++)
        entities[i]->draw(pGraphicsManager);
    
}

void Level::loadMap(const char* arquivo){
    map.load(arquivo);
}
