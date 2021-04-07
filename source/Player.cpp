#include "Player.h"

#include "Entity.h"

using namespace Entities;

//PlayerJumpState-------------------
Player::PlayerJumpState::PlayerJumpState(SM::StateMachine* pStateMachine, Player *p):State(pStateMachine), double_jump(){
    this->p = p;
}

Player::PlayerJumpState::~PlayerJumpState(){

}

void Player::PlayerJumpState::enter(void* arg){
    std::cout << "JUMP\n";
    double_jump = *((const bool*)arg);
    p->vel.y = -p->jumpVel;
}

void Player::PlayerJumpState::update(float dt, Managers::Events* pEventsManager){
    if(p){

        if(pEventsManager->keyDown(p->_rightKey)){ //DIREITA
            //atualiza velocidades
            p->vel.x += p->airAcceleration;
            if(p->vel.x > p->velMax)
                p->vel.x = p->velMax;
        }

        if(pEventsManager->keyDown(p->_leftKey)){ //ESQUERDA
            //atualiza velocidades
            p->vel.x -= p->airAcceleration;
            if(p->vel.x < -p->velMax)
                p->vel.x = -p->velMax;
        }
        p->frame = p->vel.x > 0 ? Managers::spriteRect(JUMP): Managers::spriteRect(JUMP_L);

        if(p->getGrounded()){//jogador atingiu o chao
            pStateMachine->changeState(PlayerRestStateID, NULL); //ESTADO PARADO
            p->vel.x = 0;

            //muda o retangulo do sprite
            p->frame = Managers::spriteRect(DEFAULT);
        }
        if(double_jump){ //PULO DUPLO
            if(pEventsManager->keyPressed(p->_jumpKey)){
                pStateMachine->changeState(PlayerJumpStateID, (void*)(&(const bool&)false));//chama o pulo sem possibilidade de double jump
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
        if(p->vel.y*p->vel.y > 5.0f)
            p->setGrounded(false);

        if(pEventsManager->keyPressed(p->_jumpKey)){
            if(p->isGrounded){
                p->setGrounded(false);
                pStateMachine->changeState(PlayerJumpStateID, (void*)(&(const bool&)true));//chama o pulo com possibilidade de double jump
                //muda o retangulo do sprite
                p->frame = Managers::spriteRect(JUMP);
            }
            else{
                pStateMachine->changeState(PlayerJumpStateID, (void*)(&(const bool&)false));//chama o pulo sem possibilidade de double jump
                //muda o retangulo do sprite
                p->frame = Managers::spriteRect(JUMP);
            }
        }

        //ESTADO ANDANDO
        else if(pEventsManager->keyDown(p->_rightKey) || pEventsManager->keyDown(p->_leftKey))
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
        if(p->vel.y*p->vel.y > 5.0f)
            p->setGrounded(false);
        if(pEventsManager->keyDown(p->_rightKey)){ //DIREITA
            //atualiza velocidades
            p->vel.x += p->groundAcceleration;
            if(p->vel.x > p->velMax)
                p->vel.x = p->velMax;

            //muda o retangulo do sprite
            p->frame = (nRect) ? Managers::spriteRect(WALK_R1): Managers::spriteRect(WALK_R2);

            frameTime += dt;
            if(frameTime > WALK_ANIMATION_FRAME_TIME){
                frameTime = 0;
                nRect = !nRect;
            }
        }

        if(pEventsManager->keyDown(p->_leftKey)){ //ESQUERDA
            //atualiza velocidades
            p->vel.x -= p->groundAcceleration;
            if(p->vel.x < -p->velMax)
                p->vel.x = -p->velMax;

            //muda o retangulo do sprite
            p->frame = (nRect) ? Managers::spriteRect(WALK_L1): Managers::spriteRect(WALK_L2);
            frameTime += dt;
            if(frameTime > WALK_ANIMATION_FRAME_TIME){
                frameTime = 0;
                nRect = !nRect;
            }
        }

        //ESTADO PARADO
        if(pEventsManager->keyReleased(p->_rightKey) || pEventsManager->keyReleased(p->_leftKey)){
            pStateMachine->changeState(PlayerRestStateID, NULL);
            p->vel.x = 0;
            p->frame = Managers::spriteRect(DEFAULT);
        }

        //ESTADO PULO
        if(pEventsManager->keyPressed(p->_jumpKey)){
            if(p->isGrounded){
                p->setGrounded(false);
                pStateMachine->changeState(PlayerJumpStateID, (void*)&(const bool&)true);//chama o pulo com possibilidade de pulo duplo

                //muda o retangulo do sprite
                p->frame = (p->vel.x > 0) ? Managers::spriteRect(JUMP): Managers::spriteRect(JUMP_L);
            }
            else{
                pStateMachine->changeState(PlayerJumpStateID, (void*)&(const bool&)false);//chama o pulo sem possibilidade de pulo duplo

                //muda o retangulo do sprite
                p->frame = (p->vel.x > 0) ? Managers::spriteRect(JUMP): Managers::spriteRect(JUMP_L);
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
bool Player::player1 = true;

Player::Player(Managers::Graphics* pGraphicsManager, const sf::Vector2<float>& pos, const sf::Vector2<float>& vel, const sf::Vector2<float>& rect, Managers::textureID idT, Managers::spriteID idS):
Entity(pGraphicsManager, pos, vel, idT, idS), Body(player1 ? player_1:player_2, pos, vel, rect), Being(pos, vel){

    this->pGraphicsManager = pGraphicsManager;

    loadControl();

    if(pGraphicsManager){
        frame = Managers::spriteRect(DEFAULT);
        pGraphicsManager->setSpriteRect(idS, frame);

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

void Player::loadControl(){
    if(type == 0){
        _leftKey = Managers::Events::keycode::A;
        _rightKey = Managers::Events::keycode::D;
        _jumpKey = Managers::Events::keycode::Space;

        player1 = false;
    }
    else{
        _leftKey = Managers::Events::keycode::Left;
        _rightKey = Managers::Events::keycode::Right;
        _jumpKey = Managers::Events::keycode::RControl;
    }
}
