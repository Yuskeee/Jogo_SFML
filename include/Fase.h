#ifndef _FASE_H
#define _FASE_H

#include <vector>


#include "Graphics.h"
#include "Entidade.h"
#include "Player.h"

class Fase{

private:
    std::vector<Entidade*> entities;
    Graphics* pGraphics;

public:
    Fase(Graphics* pGraphics = NULL);
    ~Fase();

    void update(float dt, Events* pEvents);//chama update de todas as entidades no vetor
    void render();//desenha todas as entidades no vetor (e futuramente o mapa)

    template <class entityClass> void addEntity(sf::Vector2<float> pos = {0.0f, 0.0f}, sf::Vector2<float> vel = {0.0f, 0.0f}, sf::Vector2<float> rect = {0.0f, 0.0f}, textureID idT = -1, spriteID idS = -1){//adiciona uma entidade do tipo entityClass no vetor de entidades
        if(std::is_base_of<Entidade, entityClass>::value){
            entityClass* newEntityInstance = new entityClass(pGraphics);
            Entidade* newEntity = static_cast<Entidade*>(newEntityInstance);
            entities.push_back(newEntity);
        }
    }
    //void loadMap(char* arquivo);
    //void salvar(char* arquivo);


};


#endif