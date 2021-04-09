#ifndef _PHYSICS_H
#define _PHYSICS_H

#include "Map.h"
#include "Body.h"
#include "List.h"

namespace World{

class Physics{ 

private:
    const float gravity = 1050/*210*/;
    const float maxVertVel = 300;

    Map* pMap;//ponteiro para o mapa (alocado em Level)
    List<Body*> bodies;//ponteiro para o vetor de entidades (alocado em Level)

    float getOffsetY(Body* bd);//calcula quanto uma corpo entrou verticalmente em um bloco solido do mapa
    float getOffsetX(Body* bd);//calcula quanto uma corpo entrou verticalmente em um bloco solido do mapa

    bool checkBodyCollision(Body* a, Body* b);

public:
    Physics(Map* pMap = NULL);
    ~Physics();

    void collideMap();//colide todas as corpos com o mapa
    void collideBodies();//colide todas as corpos entre si

    void applyGravity(float dt);

    void addBody(Body* bd);
    void removeBody(int id);

};
}

#endif
