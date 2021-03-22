#include "Fase.h"


Fase::Fase(Graphics* pGraphics){
    this->pGraphics = pGraphics;

    //apenas para testes
    addEntity<Player>();//futuramente isso vai ficar em uma funcao de carregar a fase junto com as outras chamadas
}

Fase::~Fase(){
    for(int i = 0; i < entities.size(); i++)
        delete entities[i];
}

void Fase::update(float dt, Events* pEvents){
    for(int i = 0; i < entities.size(); i++)
        entities[i]->update(dt, pEvents);
}

void Fase::render(){
    for(int i = 0; i < entities.size(); i++)
        entities[i]->draw(pGraphics);
}