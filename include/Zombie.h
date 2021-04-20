#ifndef _ZOMBIE_H
#define _ZOMBIE_H

#include "Enemy.h"
#include "states/State.h"
#include <iostream>

namespace Entities{

#define DEFAULT   0, 0,  16, 20
#define JUMP     64, 0,  16, 20
#define JUMP_L   80, 0, -16, 20
#define WALK_R1 144, 0,  16, 20
#define WALK_R2 160, 0,  16, 20
#define WALK_L1 160, 0, -16, 20
#define WALK_L2 176, 0, -16, 20

#define ZOMBIE_WIDTH   16.0f
#define ZOMBIE_HEIGHT  20.0f

#define WALK_ANIMATION_FRAME_TIME 0.1

#define ZOMBIE_TEXTURE_FILE   "../assets/zombie_alien.png"

#define ZOMBIE_SCORE_VALUE 10

class Zombie: public Enemy{

private:
    enum ZombieStates{
        ZombieJumpStateID,
        ZombieRestStateID,
        ZombieWalkStateID
    };

    class ZombieJumpState: public SM::State{
    private:
        Zombie *z;
    public:
        ZombieJumpState(SM::StateMachine* pStateMachine = NULL, Zombie *p = NULL);
        ~ZombieJumpState();

        void enter(void* arg);

        void update(float dt, Managers::Events* pEventsManager);
        void render(Managers::Graphics* pGraphicsManager);
    };
    class ZombieRestState: public SM::State{
    private:
        Zombie *z;
    public:
        ZombieRestState(SM::StateMachine* pStateMachine = NULL, Zombie *z = NULL);
        ~ZombieRestState();

        void enter(void* arg){std::cout << "REST\n";}

        void update(float dt, Managers::Events* pEventsManager);
        void render(Managers::Graphics* pGraphicsManager);
    };
    class ZombieWalkState: public SM::State{
    private:
        Zombie *z;
        bool nRect;
        float frameTime;
    public:
        ZombieWalkState(SM::StateMachine* pStateMachine = NULL, Zombie *p = NULL);
        ~ZombieWalkState();

        void enter(void* arg){std::cout << "WALK\n"; nRect = false; frameTime = 0.0f;}

        void update(float dt, Managers::Events* pEventsManager);
        void render(Managers::Graphics* pGraphicsManager);
    };
    /*
    class ZombieFireState: public State{

    };
    */
    class ZombieStateMachine: public SM::StateMachine{
    public:
        ZombieStateMachine(Zombie *z = NULL);
        ~ZombieStateMachine();
    };

private:
    const float groundAcceleration = 9;
    const float airAcceleration = 0.5;
    const float velMax = 60;
    const float jumpVel = 300;

    SM::StateMachine *ZombieSM;
    Managers::Graphics* pGraphicsManager;

public:

    Zombie(Managers::Graphics* pGraphicsManager = NULL, World::Level* pLevel = NULL, const sf::Vector2<float>& pos = {0.0f, 0.0f}, const sf::Vector2<float>& vel = {0.0f, 0.0f});
    virtual ~Zombie();

    virtual void attack();

    virtual void update(float dt, Managers::Events* pEventsManager);
    virtual void onCollide(Body* other, float dt);






};
}

#endif