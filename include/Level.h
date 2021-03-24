#ifndef _LEVEL_H
#define _LEVEL_H

#include <vector>
#include <fstream>

#include "Graphics.h"
#include "Entity.h"
#include "Player.h"
#include "Map.h"


class Level{

private:
    std::vector<Entities::Entity*> entities;
    Managers::Graphics* pGraphicsManager;
    Map map;

public:
    Level(Managers::Graphics* pGraphicsManager = NULL);
    ~Level();

    void update(float dt, Managers::Events* pEvents);//chama update de todas as entidades no vetor
    void render();//desenha todas as entidades no vetor (e futuramente o mapa)

    template <class entityClass> void addEntity(sf::Vector2<float> pos = {0.0f, 0.0f}, sf::Vector2<float> vel = {0.0f, 0.0f}, sf::Vector2<float> rect = {0.0f, 0.0f}, Managers::textureID idT = -1, Managers::spriteID idS = -1){//adiciona uma entidade do tipo entityClass no vetor de entidades
        if(std::is_base_of<Entities::Entity, entityClass>::value){
            entityClass* newEntityInstance = new entityClass(pGraphicsManager);
            Entities::Entity* newEntity = static_cast<Entities::Entity*>(newEntityInstance);
            entities.push_back(newEntity);
        }
    }
    void loadMap(const char* arquivo);
    //void salvar(char* arquivo);


};


#endif