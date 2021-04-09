#include "Level.h"

using namespace World;

Level::Level(Managers::Graphics* pGraphicsManager):map(pGraphicsManager), LevelPhysics(&map){
    this->pGraphicsManager = pGraphicsManager;
}

Level::~Level(){
    int id;
    for(int i = 0; i < entities.size(); i++){
        id = entities[i]->getId();
        LevelPhysics.removeBody(id);
        delete entities[i];
    }
}

void Level::update(float dt, Managers::Events* pEvents){

    for(int i = 0; i < entities.size(); i++)
        entities[i]->update(dt, pEvents);
    LevelPhysics.applyGravity(dt);
    LevelPhysics.collideMap();
    LevelPhysics.collideBodies();
}

void Level::render(){
    map.draw(pGraphicsManager);
    for(int i = 0; i < entities.size(); i++)
        entities[i]->draw();

}

void Level::startLevel(int n, int players){
    loadMap(levelMapFiles[n]);

    Managers::textureID Player1Texture = pGraphicsManager->loadTexture(PLAYER_TEXTURE_FILE);
    Managers::spriteID Player1Sprite = pGraphicsManager->createSprite(Player1Texture);
    Entities::Player* p1 = new Entities::Player(pGraphicsManager, sf::Vector2f(20, 20), sf::Vector2f(0, 0), sf::Vector2f(16, 20), Player1Texture, Player1Sprite);
    entities.push_back(static_cast<Entities::Entity*>(p1));//adiciona o player na lista de entidades da fase
    LevelPhysics.addBody(static_cast<Body*>(p1));//adiciona o player na lista de corpos da fisica

    if(players > 1){
        Managers::textureID Player2Texture = pGraphicsManager->loadTexture(PLAYER2_TEXTURE_FILE);
        Managers::spriteID Player2Sprite = pGraphicsManager->createSprite(Player2Texture);
        Entities::Player* p2 = new Entities::Player(pGraphicsManager, sf::Vector2f(50, 20), sf::Vector2f(0, 0), sf::Vector2f(16, 20), Player2Texture, Player2Sprite, false);
        entities.push_back(static_cast<Entities::Entity*>(p2));//adiciona o player na lista de entidades da fase
        LevelPhysics.addBody(static_cast<Body*>(p2));//adiciona o player na lista de corpos da fisica
        Entities::Enemy::setPlayers(p1, p2);
    }
    else
        Entities::Enemy::setPlayers(p1);

    Managers::textureID ZombieTexture = pGraphicsManager->loadTexture(ZOMBIE_TEXTURE_FILE);
    Managers::spriteID Zombie1Sprite = pGraphicsManager->createSprite(ZombieTexture);    
    Entities::Zombie* z1 = new Entities::Zombie(pGraphicsManager, sf::Vector2f(80, 20), sf::Vector2f(0, 0), sf::Vector2f(16, 20), ZombieTexture, Zombie1Sprite);
    entities.push_back(static_cast<Entities::Entity*>(z1));//adiciona o player na lista de entidades da fase
    LevelPhysics.addBody(static_cast<Body*>(z1));//adiciona o player na lista de corpos da fisica

    


}

void Level::loadMap(const char* arquivo){
    map.load(arquivo);
}
