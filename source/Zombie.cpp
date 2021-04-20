#include "Zombie.h"
#include "Level.h"

using namespace Entities;

//ZombieJumpState-------------------
Zombie::ZombieJumpState::ZombieJumpState(SM::StateMachine* pStateMachine, Zombie *z):State(pStateMachine){
    this->z = z;
}

Zombie::ZombieJumpState::~ZombieJumpState(){

}

void Zombie::ZombieJumpState::enter(void* arg){
    std::cout << "JUMP\n";
    z->vel.y = -z->jumpVel;
}

void Zombie::ZombieJumpState::update(float dt, Managers::Events* pEventsManager){
    if(z && (p1||p2)){
        z->setTarget();
        const Player* target = z->getTarget();

        if(target->getPos().x > z->getPos().x){ //DIREITA
            //atualiza velocidades
            z->vel.x += z->airAcceleration;
            if(z->vel.x > z->velMax)
                z->vel.x = z->velMax;
        }

        else{ //ESQUERDA
            //atualiza velocidades
            z->vel.x -= z->airAcceleration;
            if(z->vel.x < -z->velMax)
                z->vel.x = -z->velMax;
        }
        z->frame = z->vel.x > 0 ? Managers::spriteRect(JUMP): Managers::spriteRect(JUMP_L);

        if(z->getGrounded()){//zumbi atingiu o chao
            pStateMachine->changeState(ZombieRestStateID, NULL); //ESTADO PARADO

            //muda o retangulo do sprite
            z->frame = Managers::spriteRect(DEFAULT);
        }
    }
}

void Zombie::ZombieJumpState::render(Managers::Graphics* pGraphicsManager){

}

//ZombieRestState-------------------
Zombie::ZombieRestState::ZombieRestState(SM::StateMachine* pStateMachine, Zombie *z):State(pStateMachine){
    this->z = z;
}

Zombie::ZombieRestState::~ZombieRestState(){

}

void Zombie::ZombieRestState::update(float dt, Managers::Events* pEventsManager){
    if(z && (p1||p2)){
        z->setTarget();
        if(z->vel.y*z->vel.y > 5.0f)
            z->setGrounded(false);


        //ESTADO ANDANDO
        else if(z->target)
            pStateMachine->changeState(ZombieWalkStateID, NULL);
    }
}

void Zombie::ZombieRestState::render(Managers::Graphics* pGraphicsManager){

}

//ZombieWalkState-------------------
Zombie::ZombieWalkState::ZombieWalkState(SM::StateMachine* pStateMachine, Zombie *z):State(pStateMachine), nRect(){
    this->z = z;
}

Zombie::ZombieWalkState::~ZombieWalkState(){

}

void Zombie::ZombieWalkState::update(float dt, Managers::Events* pEventsManager){
    if(z && (p1||p2)){

        z->setTarget();
        const Player* target = z->getTarget();
        //se o alvo estiver perto e acima
        //ESTADO PULO
        if(((target->getPos().x - z->pos.x)*(target->getPos().x - z->pos.x) < 1024.0f && target->getPos().y < z->pos.y)
            || z->vel.x*z->vel.x < 10.0f){
            if(z->isGrounded){
                z->setGrounded(false);
                pStateMachine->changeState(ZombieJumpStateID, NULL);

                //muda o retangulo do sprite
                z->frame = (z->vel.x > 0) ? Managers::spriteRect(JUMP): Managers::spriteRect(JUMP_L);
            }
        }

        if(z->vel.y*z->vel.y > 5.0f)
            z->setGrounded(false);
        if(target->getPos().x > z->getPos().x){ //DIREITA
            //atualiza velocidades
            z->vel.x += z->groundAcceleration;
            if(z->vel.x > z->velMax)
                z->vel.x = z->velMax;

            //muda o retangulo do sprite
            z->frame = (nRect) ? Managers::spriteRect(WALK_R1): Managers::spriteRect(WALK_R2);

            frameTime += dt;
            if(frameTime > WALK_ANIMATION_FRAME_TIME){
                frameTime = 0;
                nRect = !nRect;
            }
        }

        if(target->getPos().x < z->getPos().x){ //ESQUERDA
            //atualiza velocidades
            z->vel.x -= z->groundAcceleration;
            if(z->vel.x < -z->velMax)
                z->vel.x = -z->velMax;

            //muda o retangulo do sprite
            z->frame = (nRect) ? Managers::spriteRect(WALK_L1): Managers::spriteRect(WALK_L2);
            frameTime += dt;
            if(frameTime > WALK_ANIMATION_FRAME_TIME){
                frameTime = 0;
                nRect = !nRect;
            }
        }

    }
}

void Zombie::ZombieWalkState::render(Managers::Graphics* pGraphicsManager){

}

//ZombieStateMachine----------------
Zombie::ZombieStateMachine::ZombieStateMachine(Zombie *z){
    SM::State* state = static_cast<SM::State*>(new ZombieJumpState(static_cast<StateMachine*>(this), z));
    addState(state);
    state = static_cast<SM::State*>(new ZombieRestState(static_cast<StateMachine*>(this), z));
    addState(state);
    state = static_cast<SM::State*>(new ZombieWalkState(static_cast<StateMachine*>(this), z));
    addState(state);
    currentStateID = ZombieRestStateID;
}

Zombie::ZombieStateMachine::~ZombieStateMachine(){

}

//Zombie----------------------------

Zombie::Zombie(Managers::Graphics* pGraphicsManager, World::Level* pLevel, const sf::Vector2<float>& pos, const sf::Vector2<float>& vel):
Enemy(pGraphicsManager, pLevel, pos, vel, {ZOMBIE_WIDTH, ZOMBIE_HEIGHT}), Being(enemy, pos, vel){

    this->pGraphicsManager = pGraphicsManager;

    if(pGraphicsManager){
        idTextura = pGraphicsManager->loadTexture(ZOMBIE_TEXTURE_FILE);
        idSprite = pGraphicsManager->createSprite(idTextura);
        frame = Managers::spriteRect(DEFAULT);
        pGraphicsManager->setSpriteRect(idSprite, frame);

        ZombieSM = new ZombieStateMachine(this);
    }

}

Zombie::~Zombie(){
    delete ZombieSM;
}

void Zombie::attack(){

}

void Zombie::update(float dt, Managers::Events* pEventsManager){
    if(ZombieSM)
        ZombieSM->update(dt, pEventsManager);

    pos += vel*dt;

    if(!vulnerability){
        if(vulnerability_timer > VULNERABILITY_MAX){
            vulnerability = true;
            vulnerability_timer = 0;
        }
        vulnerability_timer += dt;
    }

    if(pGraphicsManager)
        pGraphicsManager->setSpriteRect(idSprite, frame);
}

void Zombie::onCollide(Body* other, float dt){
    if((dynamic_cast<Projectile*>(other) && dynamic_cast<Projectile*>(other)->fromPlayer())){
        lives -= 1;
        if(lives == 0)
            pLevel->setScore(pLevel->getScore() + ZOMBIE_SCORE_VALUE);
    }
}
