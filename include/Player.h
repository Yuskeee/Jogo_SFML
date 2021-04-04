#ifndef _PLAYER_H
#define _PLAYER_H

#include "Entity.h"
#include "State.h"
#include <iostream>

namespace Entities{

#define DEFAULT   0, 0,  16, 20
#define JUMP     64, 0,  16, 20
#define WALK_R1 144, 0,  16, 20
#define WALK_R2 160, 0,  16, 20
#define WALK_L1 160, 0, -16, 20
#define WALK_L2 176, 0, -16, 20

class Player: public Entity{
private:
    enum PlayerStates{
        PlayerJumpStateID,
        PlayerRestStateID,
        //PlayerFireStateID,
        PlayerWalkStateID
    };

    class PlayerJumpState: public SM::State{
    private:
        Player *p;
        bool double_jump;
    public:
        PlayerJumpState(SM::StateMachine* pStateMachine = NULL, Player *p = NULL);
        ~PlayerJumpState();

        void enter(){std::cout << "JUMP\n"; double_jump = true;}

        void update(float dt, Managers::Events* pEventsManager);
        void render(Managers::Graphics* pGraphicsManager);
    };
    class PlayerRestState: public SM::State{
    private:
        Player *p;
    public:
        PlayerRestState(SM::StateMachine* pStateMachine = NULL, Player *p = NULL);
        ~PlayerRestState();

        void enter(){std::cout << "REST\n";}

        void update(float dt, Managers::Events* pEventsManager);
        void render(Managers::Graphics* pGraphicsManager);
    };
    class PlayerWalkState: public SM::State{
    private:
        Player *p;
        bool nRect;
    public:
        PlayerWalkState(SM::StateMachine* pStateMachine = NULL, Player *p = NULL);
        ~PlayerWalkState();

        void enter(){std::cout << "WALK\n"; nRect = false;}

        void update(float dt, Managers::Events* pEventsManager);
        void render(Managers::Graphics* pGraphicsManager);
    };
    /*
    class PlayerFireState: public State{

    };
    */
    class PlayerStateMachine: public SM::StateMachine{
    public:
        PlayerStateMachine(Player *p = NULL);
        ~PlayerStateMachine();
    };

private:
    const float acceleration = 5;
    const float velMax = 60;
    const float jumpVel = 100;

    SM::StateMachine *PlayerSM;
    Managers::Graphics* pGraphicsManager;

public:

    Player(Managers::Graphics* pGraphicsManager = NULL, sf::Vector2<float> pos = {0.0f, 0.0f}, sf::Vector2<float> vel = {0.0f, 0.0f}, sf::Vector2<float> rect = {0.0f, 0.0f}, Managers::textureID idT = -1, Managers::spriteID idS = -1);
    virtual ~Player();

    virtual void update(float dt, Managers::Events* pEventsManager);
    virtual void onCollide(Entity* other);


};
}



#endif
