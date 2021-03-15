#ifndef _ENTIDADE_H
#define _ENTIDADE_H

#include "Graphics.h"

//Serve de base para outras classes de tipo personagem
class Entidade{
protected:
    sf::Vector2 pos, vel, rect;
    int vidas;
    bool vulnerabilidade;

    //StateMachine gameStateMachine;
    TextureID idTextura;
    SpriteID idSprite;

public:
    Entidade::Entidade(sf::Vector2 pos = {0.0f, 0.0f}, sf::Vector2vel = {0.0f, 0.0f}, sf::Vector2rect = {0.0f, 0.0f}, TextureID idT = -1, SpriteID idS = -1);
    virtual ~Entidade();

    virtual void update(float dt) = 0; //implementar futuramente //gameStateMachine->update(dt);

    const Vetor2F Entidade::getPos() const;
    const Vetor2F Entidade::getRect() const;
};

#endif
