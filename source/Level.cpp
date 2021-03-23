#include "Level.h"


Level::Level(Managers::Graphics* pGraphics){
    this->pGraphicsManager = pGraphics;

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
    for(int i = 0; i < entities.size(); i++)
        entities[i]->draw(pGraphicsManager);
}