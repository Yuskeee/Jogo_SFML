#ifndef _ENTIDADE_H
#define _ENTIDADE_H

#include "Graphics.h"

//Serve de base para outras classes de tipo personagem
class Entidade{
protected:
    sf::Vector2<float> pos, vel, rect;
    int vidas;
    bool vulnerabilidade;

    //StateMachine gameStateMachine;
    textureID idTextura;
    spriteID idSprite;

public:
    Entidade(sf::Vector2<float> pos = {0.0f, 0.0f}, sf::Vector2<float> vel = {0.0f, 0.0f}, sf::Vector2<float> rect = {0.0f, 0.0f}, textureID idT = -1, spriteID idS = -1);
    virtual ~Entidade();

    virtual void update(float dt) = 0; //implementar futuramente //gameStateMachine->update(dt);

    virtual void draw(Graphics &gameGraphics);

    const sf::Vector2<float> getPos() const;
    const sf::Vector2<float> getRect() const;
};

#endif
