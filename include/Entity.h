#ifndef _ENTIDADE_H
#define _ENTIDADE_H

#include "Graphics.h"
#include "Events.h"

namespace Entities{

//Serve de base para outras classes de tipo personagem
class Entity{
protected:

    enum entityType{
        player,
        //inimigo1,
        //inimigo2,
        //projetil,
        nEntityTypes

    };

    int type;
    sf::Vector2<float> pos, vel, rect;
    int vidas;
    bool vulnerabilidade;
    bool isGrounded;

    //StateMachine gameStateMachine;
    Managers::textureID idTextura;
    Managers::spriteID idSprite;
    Managers::spriteRect frame;

public:
    Entity(Managers::Graphics* pGameGraphicsManager = NULL, sf::Vector2<float> pos = {0.0f, 0.0f}, sf::Vector2<float> vel = {0.0f, 0.0f}, sf::Vector2<float> rect = {0.0f, 0.0f}, Managers::textureID idT = -1, Managers::spriteID idS = -1);
    virtual ~Entity();

    virtual void update(float dt, Managers::Events* pEvents) = 0; //implementar futuramente //gameStateMachine->update(dt);

    virtual void draw(Managers::Graphics* pGameGraphicsManager);

    void setPos(sf::Vector2<float> pos);
    void setVel(sf::Vector2<float> vel);
    void setGrounded(bool isGrounded);

    const sf::Vector2<float> getPos() const;
    const sf::Vector2<float> getVel() const;
    const sf::Vector2<float> getRect() const;

    virtual void onCollide(Entity* other) = 0;
};

}

#endif
