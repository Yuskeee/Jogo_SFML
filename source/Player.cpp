#include "Player.h"
#include "Level.h"

using namespace Entities;

//PlayerJumpState-------------------
Player::PlayerJumpState::PlayerJumpState(SM::StateMachine* pStateMachine, Player *p):State(pStateMachine), double_jump(){
    this->p = p;
}

Player::PlayerJumpState::~PlayerJumpState(){
}

void Player::PlayerJumpState::enter(void* arg){
    std::cout << "JUMP\n";
    double_jump = (bool&&)arg;
    p->vel.y = -p->jumpVel;
}

void Player::PlayerJumpState::update(float dt, Managers::Events* pEventsManager){
    if(p){

        if(pEventsManager->keyDown(p->_rightKey)){ //DIREITA
            p->rightDirection = true;
            //atualiza velocidades
            p->vel.x += p->airAcceleration;
            if(p->vel.x > p->velMax)
                p->vel.x = p->velMax;
        }

        if(pEventsManager->keyDown(p->_leftKey)){ //ESQUERDA
            p->rightDirection = false;
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
                pStateMachine->changeState(PlayerJumpStateID, (void*)(bool&&)false);//chama o pulo sem possibilidade de double jump
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
                pStateMachine->changeState(PlayerJumpStateID, (void*)(bool&&)true);//chama o pulo com possibilidade de double jump
                //muda o retangulo do sprite
                p->frame = Managers::spriteRect(JUMP);
            }
            else{
                pStateMachine->changeState(PlayerJumpStateID, (void*)(bool&&)false);//chama o pulo sem possibilidade de double jump
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
            p->rightDirection = true;
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
            p->rightDirection = false;
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
        if(!pEventsManager->keyDown(p->_rightKey) && !pEventsManager->keyDown(p->_leftKey)){
            pStateMachine->changeState(PlayerRestStateID, NULL);
            p->vel.x = 0;
            p->frame = Managers::spriteRect(DEFAULT);
        }

        //ESTADO PULO
        if(pEventsManager->keyPressed(p->_jumpKey)){
            if(p->isGrounded){
                p->setGrounded(false);
                pStateMachine->changeState(PlayerJumpStateID, (void*)(bool&&)true);//chama o pulo com possibilidade de pulo duplo

                //muda o retangulo do sprite
                p->frame = (p->vel.x > 0) ? Managers::spriteRect(JUMP): Managers::spriteRect(JUMP_L);
            }
            else{
                pStateMachine->changeState(PlayerJumpStateID, (void*)(bool&&)false);//chama o pulo sem possibilidade de pulo duplo

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
    SM::State* state = static_cast<SM::State*>(new PlayerJumpState(static_cast<SM::StateMachine*>(this), p));
    addState(state);
    state = static_cast<SM::State*>(new PlayerRestState(static_cast<SM::StateMachine*>(this), p));
    addState(state);
    state = static_cast<SM::State*>(new PlayerWalkState(static_cast<SM::StateMachine*>(this), p));
    addState(state);
    currentStateID = PlayerRestStateID;
}

Player::PlayerStateMachine::~PlayerStateMachine(){
}

//Player----------------------------

Player::Player(Managers::Graphics* pGraphicsManager, World::Level* pLevel, const sf::Vector2<float>& pos, const sf::Vector2<float>& vel, bool player1):
Entity(pGraphicsManager, pLevel, pos, vel), Body(pos, vel, {PLAYER_WIDTH, PLAYER_HEIGHT}), Being(player1 ? player_1:player_2, pos, vel), rightDirection(true), vulnerability_timer(0), attackTimer(0){

    this->pGraphicsManager = pGraphicsManager;

    this->pLevel = pLevel;

    loadControl(player1);

    if(pGraphicsManager){
        frame = Managers::spriteRect(DEFAULT);
        idTextura = pGraphicsManager->loadTexture(player1 ? PLAYER_TEXTURE_FILE : PLAYER2_TEXTURE_FILE);
        idSprite = pGraphicsManager->createSprite(idTextura);
        pGraphicsManager->setSpriteRect(idSprite, frame);

        PlayerSM = new PlayerStateMachine(this);
    }

}

Player::~Player(){
    delete PlayerSM;
}

#define VULNERABILITY_MAX 0.5f

void Player::update(float dt, Managers::Events* pEventsManager){

    if(PlayerSM)
        PlayerSM->update(dt, pEventsManager);

    pos += vel*dt;

    if(pGraphicsManager)
        pGraphicsManager->setSpriteRect(idSprite, frame);

    if(!vulnerability){
        if(vulnerability_timer > VULNERABILITY_MAX){
            vulnerability = true;
            vulnerability_timer = 0;
        }
        vulnerability_timer += dt;
    }

    attackTimer += dt;

    if(attackTimer > attackInterval && pEventsManager->keyPressed(_fireKey)){
        attackTimer = 0;
        Projectile* proj = new Projectile(pLevel->getGraphicsManager(), pLevel, {pos.x + ((rightDirection) ? rect.x*0.5f:-rect.x*0.5f), pos.y}, {(rightDirection) ? projectileSpeed:-projectileSpeed, 0.0f}, true);

        pLevel->addEntity(static_cast<Entities::Entity*>(proj));
        pLevel->addBody(static_cast<Body*>(proj));
    }

    std::cout << lives << std::endl;

}

void Player::onCollide(Body* other){
    if(vulnerability){
        if(dynamic_cast<Projectile*>(other) != 0){
            if(!dynamic_cast<Projectile*>(other)->fromPlayer()){
                lives -= 1;
                vulnerability = false;
            }
        }
        else if(dynamic_cast<Enemy*>(other) != 0){
            lives -= 1;
            vulnerability = false;
        }
    }
}

void Player::loadControl(bool player1){
    if(player1){
        _leftKey = Managers::Events::keycode::A;
        _rightKey = Managers::Events::keycode::D;
        _jumpKey = Managers::Events::keycode::Space;
        _fireKey = Managers::Events::keycode::G;
    }
    else{
        _leftKey = Managers::Events::keycode::Left;
        _rightKey = Managers::Events::keycode::Right;
        _jumpKey = Managers::Events::keycode::RControl;
        _fireKey = Managers::Events::keycode::RShift;
    }
}
