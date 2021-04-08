#include "Level.h"

using namespace World;

Level::Level(Managers::Graphics* pGraphicsManager):map(pGraphicsManager), LevelPhysics(&map){
    this->pGraphicsManager = pGraphicsManager;
}

Level::~Level(){
    for(int i = 0; i < entities.size(); i++)
        delete entities[i];
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
        entities[i]->draw(pGraphicsManager);
    
}

void Level::startLevel(int n){
    loadMap(levelMapFiles[n]);
    //addEntity<Entities::Player>(sf::Vector2f(20, 20), sf::Vector2f(0, 0), sf::Vector2f(16, 20));
    Managers::textureID PlayerTexture = pGraphicsManager->loadTexture(PLAYER_TEXTURE_FILE);
    Managers::spriteID Player1Sprite = pGraphicsManager->createSprite(PlayerTexture);

    Managers::textureID ZombieTexture = pGraphicsManager->loadTexture(ZOMBIE_TEXTURE_FILE);
    Managers::spriteID Zombie1Sprite = pGraphicsManager->createSprite(ZombieTexture);

    Entities::Player* p1 = new Entities::Player(pGraphicsManager, sf::Vector2f(20, 20), sf::Vector2f(0, 0), sf::Vector2f(16, 20), PlayerTexture, Player1Sprite);
    entities.push_back(static_cast<Entities::Entity*>(p1));//adiciona o player na lista de entidades da fase
    LevelPhysics.addBody(static_cast<Body*>(p1));//adiciona o player na lista de corpos da fisica

    Entities::Zombie* z1 = new Entities::Zombie(pGraphicsManager, sf::Vector2f(90, 20), sf::Vector2f(0, 0), sf::Vector2f(16, 20), ZombieTexture, Zombie1Sprite);
    entities.push_back(static_cast<Entities::Entity*>(z1));//adiciona o player na lista de entidades da fase
    LevelPhysics.addBody(static_cast<Body*>(z1));//adiciona o player na lista de corpos da fisica

    Entities::Enemy::setPlayers(p1);
    

}

void Level::loadMap(const char* arquivo){
    map.load(arquivo);
}
