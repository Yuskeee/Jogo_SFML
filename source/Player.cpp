#include "Player.h"

#include "Entity.h"

using namespace Entities;

//PlayerJumpState-------------------
Player::PlayerJumpState::PlayerJumpState(SM::StateMachine* pStateMachine, Player *p):State(pStateMachine), double_jump(){
    this->p = p;
}

Player::PlayerJumpState::~PlayerJumpState(){

}

void Player::PlayerJumpState::update(float dt, Managers::Events* pEventsManager){
    if(p){
        if(p->vel.y*p->vel.y > 0.5)
            p->isGrounded = false;
        if(p->isGrounded){//se espaco foi pressionado e o jogador esta no chao
            pStateMachine->changeState(PlayerRestStateID, NULL); //ESTADO PARADO
            p->vel.x = 0;

            //muda o retangulo do sprite
            p->frame = Managers::spriteRect(DEFAULT);
        }
        if(double_jump){ //PULO DUPLO
            if(pEventsManager->keyPressed(Managers::Events::keycode::Space)){
                p->vel.y -= p->jumpVel;
                double_jump = false;
            }
        }
    }
}

void Player::PlayerJumpState::render(Managers::Graphics* pGraphicsManager){

}

//PlayerRestState-------------------
Player::PlayerRestState::PlayerRestState(SM::StateMachine* pStateMachine, Player *p):State(pStateMachine){
    this->p = p;
}

Player::PlayerRestState::~PlayerRestState(){

}

void Player::PlayerRestState::update(float dt, Managers::Events* pEventsManager){
    if(p){
        if(pEventsManager->keyPressed(Managers::Events::keycode::Space)){
            if(p->isGrounded){
                //atualiza velocidades
                pStateMachine->changeState(PlayerJumpStateID, NULL);
                p->vel.y -= p->jumpVel;

                //muda o retangulo do sprite
                p->frame = Managers::spriteRect(JUMP);
            }
        }

        //ESTADO ANDANDO
        else if(pEventsManager->keyDown(Managers::Events::keycode::D) || pEventsManager->keyDown(Managers::Events::keycode::A))
            pStateMachine->changeState(PlayerWalkStateID, NULL);
    }
}

void Player::PlayerRestState::render(Managers::Graphics* pGraphicsManager){

}

//PlayerWalkState-------------------
Player::PlayerWalkState::PlayerWalkState(SM::StateMachine* pStateMachine, Player *p):State(pStateMachine), nRect(){
    this->p = p;
}

Player::PlayerWalkState::~PlayerWalkState(){

}

void Player::PlayerWalkState::update(float dt, Managers::Events* pEventsManager){
    if(p){
        if(pEventsManager->keyDown(Managers::Events::keycode::D)){ //DIREITA
            //atualiza velocidades
            p->vel.x += p->acceleration;
            if(p->vel.x > p->velMax)
                p->vel.x = p->velMax;

            //muda o retangulo do sprite
            p->frame = (nRect) ? Managers::spriteRect(WALK_R1): Managers::spriteRect(WALK_R2);
            nRect = !nRect;
        }

        if(pEventsManager->keyDown(Managers::Events::keycode::A)){ //ESQUERDA
            //atualiza velocidades
            p->vel.x -= p->acceleration;
            if(p->vel.x < -p->velMax)
                p->vel.x = -p->velMax;

            //muda o retangulo do sprite
            p->frame = (nRect) ? Managers::spriteRect(WALK_L1): Managers::spriteRect(WALK_L2);
            nRect = !nRect;
        }

        //ESTADO PARADO
        if(pEventsManager->keyReleased(Managers::Events::keycode::D) || pEventsManager->keyReleased(Managers::Events::keycode::A)){
            pStateMachine->changeState(PlayerRestStateID, NULL);
            p->vel.x = 0;
            p->frame = Managers::spriteRect(DEFAULT);
        }

        //ESTADO PULO
        if(pEventsManager->keyPressed(Managers::Events::keycode::Space)){
            if(p->isGrounded){
                pStateMachine->changeState(PlayerJumpStateID, NULL);
                p->vel.y -= p->jumpVel;

                //muda o retangulo do sprite
                p->frame = Managers::spriteRect(JUMP);
            }
        }
    }
}

void Player::PlayerWalkState::render(Managers::Graphics* pGraphicsManager){

}

//PlayerStateMachine----------------
Player::PlayerStateMachine::PlayerStateMachine(Player *p){
    SM::State* state = static_cast<SM::State*>(new PlayerJumpState(static_cast<StateMachine*>(this), p));
    addState(state);
    state = static_cast<SM::State*>(new PlayerRestState(static_cast<StateMachine*>(this), p));
    addState(state);
    state = static_cast<SM::State*>(new PlayerWalkState(static_cast<StateMachine*>(this), p));
    addState(state);
    currentStateID = PlayerRestStateID;
}

Player::PlayerStateMachine::~PlayerStateMachine(){

}

//Player----------------------------

Player::Player(Managers::Graphics* pGraphicsManager, sf::Vector2<float> pos, sf::Vector2<float> vel, sf::Vector2<float> rect, Managers::textureID idT, Managers::spriteID idS):
Entity(pGraphicsManager, pos, vel, idT, idS), Body(player, pos, vel, rect), Being(pos, vel){

    this->pGraphicsManager = pGraphicsManager;

    if(pGraphicsManager){
        idTextura = pGraphicsManager->loadTexture("../assets/green_alien.png");
        idSprite = pGraphicsManager->createSprite(idTextura);
        frame = Managers::spriteRect(DEFAULT);
        pGraphicsManager->setSpriteRect(idSprite, frame);

        PlayerSM = new PlayerStateMachine(this);
    }

}

Player::~Player(){
    delete PlayerSM;
}

void Player::update(float dt, Managers::Events* pEventsManager){

    if(PlayerSM)
        PlayerSM->update(dt, pEventsManager);

    pos += vel*dt;

    if(pGraphicsManager)
        pGraphicsManager->setSpriteRect(idSprite, frame);

}

void Player::onCollide(Entity* other){


}
