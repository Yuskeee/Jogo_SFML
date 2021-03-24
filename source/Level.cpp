#include "Level.h"


Level::Level(Managers::Graphics* pGraphicsManager):map(pGraphicsManager){
    this->pGraphicsManager = pGraphicsManager;
    printf("creating level\n");
    //apenas para testes
    addEntity<Entities::Player>();//futuramente isso vai ficar em uma funcao de carregar a fase junto com as outras chamadas

}

Level::~Level(){
    for(int i = 0; i < entities.size(); i++)
        delete entities[i];
}

void Level::update(float dt, Managers::Events* pEvents){
    for(int i = 0; i < entities.size(); i++)
        entities[i]->update(dt, pEvents);
}

void Level::render(){
    map.draw(pGraphicsManager);
    for(int i = 0; i < entities.size(); i++)
        entities[i]->draw(pGraphicsManager);
    
}

void Level::loadMap(const char* arquivo){
    map.load(arquivo);
}
