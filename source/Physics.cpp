#include "Physics.h"

using namespace World;

Physics::Physics(Map* pMap){
    this->pMap = pMap;
}

Physics::~Physics(){

}

float Physics::getOffsetX(Body* bd){
    if(bd->getVel().x > 0)//Direita: testa se os cantos superior direito ou inferior direito estao dentro de um bloco solido 
        if(pMap->isPositionSolid(bd->getPos().x + bd->getRect().x, bd->getPos().y)
        || pMap->isPositionSolid(bd->getPos().x + bd->getRect().x, bd->getPos().y + bd->getRect().y))
        {
            float offset = bd->getPos().x + bd->getRect().x; 
            offset = offset - TILE_WIDTH*(int)(offset/TILE_WIDTH);//verifica quanto a entidade entrou no bloco a sua direita: offset = Xentidade + LarguraEntidade - Xbloco = Xentidade + LarguraEntidade - TAMANHO_BLOCO*floor(Xentidade/TAMANHO_BLOCO)   
            return offset + 0.0001f;//retorna o offset um pouco maior do que ele realmente é, para expulsar completamente a entidade do bloco
        }
        else
            return 0;//se a parte direita da entidade nao esta dentro de um bloco solido, nao ha offset para ser retorado
    else//Esquerda
        if(pMap->isPositionSolid(bd->getPos().x, bd->getPos().y)
        || pMap->isPositionSolid(bd->getPos().x, bd->getPos().y + bd->getRect().y))
        {
            float offset = bd->getPos().x; 
            offset = offset - TILE_WIDTH*((int)(offset/TILE_WIDTH)+1);//verifica quanto a entidade entrou no bloco a sua esquerda: offset = Xentidade - Xbloco = Xentidade - TAMANHO_BLOCO*ceil(Xentidade/TAMANHO_BLOCO)
            return offset - 0.0001f;//retorna o offset um pouco maior do que ele realmente é, para expulsar completamente a entidade do bloco
        }
        else
            return 0;//se a parte esquerda da entidade nao esta dentro de um bloco solido, nao ha offset para ser retorado

}

float Physics::getOffsetY(Body* bd){
    if(bd->getVel().y > 0)//Baixo
        if(pMap->isPositionSolid(bd->getPos().x, bd->getPos().y + bd->getRect().y)
        || pMap->isPositionSolid(bd->getPos().x + bd->getRect().x, bd->getPos().y + bd->getRect().y))
        {
            float offset = bd->getPos().y + bd->getRect().y; 
            offset = offset - TILE_HEIGHT*(int)(offset/TILE_HEIGHT);//verifica quanto a entidade entrou no bloco embaixo de si: offset = Yentidade + AlturaEntidade - Ybloco = Yentidade + LarguraEntidade - TAMANHO_BLOCO*floor(Yentidade/TAMANHO_BLOCO)
            return offset + 0.0001f;//retorna o offset um pouco maior do que ele realmente é, para expulsar completamente a entidade do bloco
        }
        else
            return 0;//se a parte de baixo da entidade nao esta dentro de um bloco solido, nao ha offset para ser retorado
    else //Cima
        if(pMap->isPositionSolid(bd->getPos().x, bd->getPos().y)
        || pMap->isPositionSolid(bd->getPos().x + bd->getRect().x, bd->getPos().y))
        {
            float offset = bd->getPos().y; 
            offset = offset - TILE_HEIGHT*((int)(offset/TILE_HEIGHT)+1);//verifica quanto a entidade entrou no bloco acima de si: offset = Yentidade - Ybloco = Yentidade - TAMANHO_BLOCO*ceil(Yentidade/TAMANHO_BLOCO)
            return offset - 0.0001f;//retorna o offset um pouco maior do que ele realmente é, para expulsar completamente a entidade do bloco
        }
        else
            return 0;//se a parte de cima da entidade nao esta dentro de um bloco solido, nao ha offset para ser retorado
}

bool Physics::checkBodyCollision(Body* a, Body* b){
    if(a->getPos().x > b->getPos().x + b->getRect().x || a->getPos().x + a->getRect().x < b->getPos().x)
        return false;
    else if(a->getPos().y > b->getPos().y + b->getRect().y || a->getPos().y + a->getRect().y < b->getPos().y)
        return false;
    else
        return true;
}

void Physics::collideMap(){
    float offsetX, offsetY;//quanto uma entidade sobrepos um bloco solido em cada eixo
    float bdVelX, bdVelY;//velocidade da entidade na ultima atualizacao
    Body* bd;//ponteiro para a entidade

    for(int i = bodies.size()-1; i >= 0; i--){//para cada entidade carregada

        bd = bodies[i];//resgata os dados da entidade em questao
        bdVelX = bd->getVel().x;
        bdVelY = bd->getVel().y;

        offsetX = getOffsetX(bd);//calcula o offset de ambos os eixos
        offsetY = getOffsetY(bd);

        if(offsetX == 0.0f && offsetY == 0.0f){
            //nao houve colisao
        }
        //se o offset vertical for menor que o horizontal, provavelmente ocorreu uma colisao em Y
        else if(offsetY*offsetY < offsetX*offsetX){
            bd->setPos(sf::Vector2f(bd->getPos().x, bd->getPos().y - offsetY));//corrige a sobreposicao do eixo Y

            offsetX = getOffsetX(bd);//verifica se X continua sobreposto apos a correcao
            if (offsetX != 0){//se X continua sobreposto, a colisao nao ocorreu apenas em Y, mas pode ter ocorrido apenas em X
                bd->setPos(sf::Vector2f(bd->getPos().x - offsetX, bd->getPos().y + offsetY));//corrige a sobreposicao de X e desfaz a correcao anterior em Y
                offsetY = getOffsetY(bd);//se Y agora nao esta mais sobreposto mesmo com a correcao anulada, signfica que a colisao era apenas em X
                bd->setPos(sf::Vector2f(bd->getPos().x, bd->getPos().y - offsetY));//se Y voltou a ficar sobreposto apos X ter sido corrigido, a colisao era em X e Y. Refaz a correcao de Y 
                bd->setVel(sf::Vector2f(0.0f, bdVelY));//de qualquer forma nesse ponto, ocorreu uma colisao em X, zera a velocidade nesse eixo
            }
            if(offsetY){
                bd->setVel(sf::Vector2f(bdVelX, 0.0f));//se ocorreu colisao em Y zera a velocidade nesse eixo
                if(offsetY > 0)
                    bd->setGrounded(true);//a entidade esta no chao
            } 
        }
        else{//caso contrario, é mais provavel uma colisao em X
            bd->setPos(sf::Vector2f(bd->getPos().x - offsetX, bd->getPos().y));//corrige a sobreposicao no eixo X

            offsetY = getOffsetY(bd);//verifica se Y continua sobreposto apos a correcao
            if (offsetY != 0){//se Y continua sobreposto, a colisao nao ocorreu apenas em X, mas pode ter ocorrido apenas em Y
                bd->setPos(sf::Vector2f(bd->getPos().x + offsetX, bd->getPos().y - offsetY));//corrige a sobreposicao de Y e desfaz a correcao anterior em X
                offsetX = getOffsetX(bd);//se X agora nao esta mais sobreposto mesmo com a correcao anulada, signfica que a colisao era apenas em Y
                bd->setPos(sf::Vector2f(bd->getPos().x - offsetX, bd->getPos().y));//se X voltou a ficar sobreposto apos Y ter sido corrigido, a colisao era em X e Y. Refaz a correcao de X
                bd->setVel(sf::Vector2f(bdVelX, 0.0f));//de qualquer forma nesse ponto, ocorreu uma colisao em Y, zera a velocidade nesse eixo
                if(offsetY > 0)
                    bd->setGrounded(true);//a entidade esta no chao
            }
            if(offsetX)
               bd->setVel(sf::Vector2f(0.0f, bdVelY));//se ocorreu colisao em X zera a velocidade nesse eixo 
        }
 
    }
}

void Physics::collideBodies(){
    Body *a, *b;
    for(int i = bodies.size()-1; i >= 0; i--){
        for(int j = i - 1; j >= 0; j--)
        {
            a = bodies[i];
            b = bodies[j];
            
            if(checkBodyCollision(a, b)){///se a colidiu com b, chama os metodos de colisao de cada uma passando ponteiro para a outra
                a->onCollide(b);
                b->onCollide(a);
            }
        }
    }
}

void Physics::applyGravity(float dt){
    for(int i = bodies.size()-1; i >= 0; i--){
        if(bodies[i]->isGravitable())
            if(bodies[i]->getVel().y < maxVertVel)
                bodies[i]->setVel(sf::Vector2f(bodies[i]->getVel().x, bodies[i]->getVel().y + gravity*dt));
            else
                bodies[i]->setVel(sf::Vector2f(bodies[i]->getVel().x, maxVertVel));
    }

}

void Physics::addBody(Body* bd){
    bodies.push_back(bd);
}

void Physics::removeBody(int id){

    for(auto i = bodies.begin(); i != bodies.end(); i++)
        if(i->getId() == id)
            bodies.erase(i);
        
}
