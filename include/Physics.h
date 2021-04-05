#ifndef _PHYSICS_H
#define _PHYSICS_H

#include "Map.h"
#include "Entity.h"
#include "List.h"

namespace World{

class Physics{ 

private:
    const float gravity = 1050/*210*/;
    const float maxVertVel = 300;

    Map* pMap;//ponteiro para o mapa (alocado em Level)
    List<Entities::Entity*>* bodies;//ponteiro para o vetor de entidades (alocado em Level)

    float getOffsetY(Entities::Entity* ent);//calcula quanto uma entidade entrou verticalmente em um bloco solido do mapa
    float getOffsetX(Entities::Entity* ent);//calcula quanto uma entidade entrou verticalmente em um bloco solido do mapa

    bool checkEntityCollision(Entities::Entity* a, Entities::Entity* b);

public:
    Physics(Map* pMap = NULL, std::vector<Entities::Entity*>* bodies = NULL);
    ~Physics();

    void collideMap();//colide todas as entidades com o mapa
    void collideEntities();//colide todas as entidades entre si

    void applyGravity(float dt);

};
}

#endif
