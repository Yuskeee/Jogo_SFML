#ifndef _ENTIDADE_H
#define _ENTIDADE_H

#include "Graphics.h"
#include "Events.h"

#include "Being.h"

namespace World{
    class Level;
}

namespace Entities{

//Serve de base para outras classes de tipo personagem
class Entity: public virtual Being{
protected:

    World::Level* pLevel;

    int lives;
    bool vulnerability;

    //StateMachine gameStateMachine;
    Managers::Graphics* pGraphicsManager;

    Managers::textureID idTextura;
    Managers::spriteID idSprite;
    Managers::spriteRect frame;

public:
    Entity(Managers::Graphics* pGraphicsManager = NULL, World::Level* pLevel = NULL, const sf::Vector2<float>& pos = {0.0f, 0.0f}, const sf::Vector2<float>& vel = {0.0f, 0.0f}, beingType type = Being::player_1);
    virtual ~Entity();

    virtual void update(float dt, Managers::Events* pEvents) = 0; //implementar futuramente //gameStateMachine->update(dt);

    virtual void draw();

    void damage(int damage);

    int getLives() const;
    

};

}

#endif
