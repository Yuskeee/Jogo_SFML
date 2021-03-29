#ifndef _PHYSICS_H
#define _PHYSICS_H

#include "Map.h"
#include "Entity.h"

class Physics{

private:
    const float gravity = 2;
    const float maxVertVel = 180;

    Map* pMap;//ponteiro para o mapa (alocado em Level)
    std::vector<Entities::Entity*>* bodies;//ponteiro para o vetor de entidades (alocado em Level)

    float getOffsetY(Entities::Entity* ent);//calcula quanto uma entidade entrou verticalmente em um bloco solido do mapa
    float getOffsetX(Entities::Entity* ent);//calcula quanto uma entidade entrou verticalmente em um bloco solido do mapa

    bool checkEntityCollision(Entities::Entity* a, Entities::Entity* b);

public:
    Physics(Map* pMap = NULL, std::vector<Entities::Entity*>* bodies = NULL);
    ~Physics();

    void collideMap(float dt);//colide todas as entidades com o mapa
    void collideEntities();//colide todas as entidades entre si

    void applyGravity();

};

#endif