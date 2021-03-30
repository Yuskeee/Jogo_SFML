#include "Physics.h"

Physics::Physics(Map* pMap, std::vector<Entities::Entity*>* bodies){
    this->pMap = pMap;
    this->bodies = bodies;
}

Physics::~Physics(){


}

float Physics::getOffsetX(Entities::Entity* ent){
    if(ent->getVel().x > 0)//Direita: testa se os cantos superior direito ou inferior direito estao dentro de um bloco solido 
        if(pMap->isPositionSolid(ent->getPos().x + ent->getRect().x, ent->getPos().y)
        || pMap->isPositionSolid(ent->getPos().x + ent->getRect().x, ent->getPos().y + ent->getRect().y))
        {
            float offset = ent->getPos().x + ent->getRect().x; 
            offset = offset - TILE_WIDTH*(int)(offset/TILE_WIDTH);//verifica quanto a entidade entrou no bloco a sua direita: offset = Xentidade + LarguraEntidade - Xbloco = Xentidade + LarguraEntidade - TAMANHO_BLOCO*floor(Xentidade/TAMANHO_BLOCO)   
            return offset + 0.0001f;//retorna o offset um pouco maior do que ele realmente é, para expulsar completamente a entidade do bloco
        }
        else
            return 0;//se a parte direita da entidade nao esta dentro de um bloco solido, nao ha offset para ser retorado
    else//Esquerda
        if(pMap->isPositionSolid(ent->getPos().x, ent->getPos().y)
        || pMap->isPositionSolid(ent->getPos().x, ent->getPos().y + ent->getRect().y))
        {
            float offset = ent->getPos().x; 
            offset = offset - TILE_WIDTH*((int)(offset/TILE_WIDTH)+1);//verifica quanto a entidade entrou no bloco a sua esquerda: offset = Xentidade - Xbloco = Xentidade - TAMANHO_BLOCO*ceil(Xentidade/TAMANHO_BLOCO)
            return offset - 0.0001f;//retorna o offset um pouco maior do que ele realmente é, para expulsar completamente a entidade do bloco
        }
        else
            return 0;//se a parte esquerda da entidade nao esta dentro de um bloco solido, nao ha offset para ser retorado

}

float Physics::getOffsetY(Entities::Entity* ent){
    if(ent->getVel().y > 0)//Baixo
        if(pMap->isPositionSolid(ent->getPos().x, ent->getPos().y + ent->getRect().y)
        || pMap->isPositionSolid(ent->getPos().x + ent->getRect().x, ent->getPos().y + ent->getRect().y))
        {
            float offset = ent->getPos().y + ent->getRect().y; 
            offset = offset - TILE_HEIGHT*(int)(offset/TILE_HEIGHT);//verifica quanto a entidade entrou no bloco embaixo de si: offset = Yentidade + AlturaEntidade - Ybloco = Yentidade + LarguraEntidade - TAMANHO_BLOCO*floor(Yentidade/TAMANHO_BLOCO)
            return offset + 0.0001f;//retorna o offset um pouco maior do que ele realmente é, para expulsar completamente a entidade do bloco
        }
        else
            return 0;//se a parte de baixo da entidade nao esta dentro de um bloco solido, nao ha offset para ser retorado
    else //Cima
        if(pMap->isPositionSolid(ent->getPos().x, ent->getPos().y)
        || pMap->isPositionSolid(ent->getPos().x + ent->getRect().x, ent->getPos().y))
        {
            float offset = ent->getPos().y; 
            offset = offset - TILE_HEIGHT*((int)(offset/TILE_HEIGHT)+1);//verifica quanto a entidade entrou no bloco acima de si: offset = Yentidade - Ybloco = Yentidade - TAMANHO_BLOCO*ceil(Yentidade/TAMANHO_BLOCO)
            return offset - 0.0001f;//retorna o offset um pouco maior do que ele realmente é, para expulsar completamente a entidade do bloco
        }
        else
            return 0;//se a parte de cima da entidade nao esta dentro de um bloco solido, nao ha offset para ser retorado
}

bool Physics::checkEntityCollision(Entities::Entity* a, Entities::Entity* b){
    if(a->getPos().x > b->getPos().x + b->getRect().x || a->getPos().x + a->getRect().x < b->getPos().x)
        return false;
    else if(a->getPos().y > b->getPos().y + b->getRect().y || a->getPos().y + a->getRect().y < b->getPos().y)
        return false;
    else
        return true;
}

void Physics::collideMap(){

    float offsetX, offsetY;//quanto uma entidade sobrepos um bloco solido em cada eixo
    float entVelX, entVelY;//velocidade da entidade na ultima atualizacao
    Entities::Entity* ent;//ponteiro para a entidade

    for(int i = bodies->size()-1; i >= 0; i--){//para cada entidade carregada

        ent = (*bodies)[i];//resgata os dados da entidade em questao
        entVelX = ent->getVel().x;
        entVelY = ent->getVel().y;

        offsetX = getOffsetX(ent);//calcula o offset de ambos os eixos
        offsetY = getOffsetY(ent);

        if(offsetX == 0.0f && offsetY == 0.0f){
            //nao houve colisao
        }
        //se o offset vertical for menor que o horizontal, provavelmente ocorreu uma colisao em Y
        else if(offsetY*offsetY < offsetX*offsetX){
            ent->setPos(sf::Vector2f(ent->getPos().x, ent->getPos().y - offsetY));//corrige a sobreposicao do eixo Y

            offsetX = getOffsetX(ent);//verifica se X continua sobreposto apos a correcao
            if (offsetX != 0){//se X continua sobreposto, a colisao nao ocorreu apenas em Y, mas pode ter ocorrido apenas em X
                ent->setPos(sf::Vector2f(ent->getPos().x - offsetX, ent->getPos().y + offsetY));//corrige a sobreposicao de X e desfaz a correcao anterior em Y
                offsetY = getOffsetY(ent);//se Y agora nao esta mais sobreposto mesmo com a correcao anulada, signfica que a colisao era apenas em X
                ent->setPos(sf::Vector2f(ent->getPos().x, ent->getPos().y - offsetY));//se Y voltou a ficar sobreposto apos X ter sido corrigido, a colisao era em X e Y. Refaz a correcao de Y 
                ent->setVel(sf::Vector2f(0.0f, entVelY));//de qualquer forma nesse ponto, ocorreu uma colisao em X, zera a velocidade nesse eixo
            }
            if(offsetY){
               ent->setVel(sf::Vector2f(entVelX, 0.0f));//se ocorreu colisao em Y zera a velocidade nesse eixo
               ent->setGrounded(true);//a entidade esta no chao
            } 
        }
        else{//caso contrario, é mais provavel uma colisao em X
            ent->setPos(sf::Vector2f(ent->getPos().x - offsetX, ent->getPos().y));//corrige a sobreposicao no eixo X

            offsetY = getOffsetY(ent);//verifica se Y continua sobreposto apos a correcao
            if (offsetY != 0){//se Y continua sobreposto, a colisao nao ocorreu apenas em X, mas pode ter ocorrido apenas em Y
                ent->setPos(sf::Vector2f(ent->getPos().x + offsetX, ent->getPos().y - offsetY));//corrige a sobreposicao de Y e desfaz a correcao anterior em X
                offsetX = getOffsetX(ent);//se X agora nao esta mais sobreposto mesmo com a correcao anulada, signfica que a colisao era apenas em Y
                ent->setPos(sf::Vector2f(ent->getPos().x - offsetX, ent->getPos().y));//se X voltou a ficar sobreposto apos Y ter sido corrigido, a colisao era em X e Y. Refaz a correcao de X
                ent->setVel(sf::Vector2f(entVelX, 0.0f));//de qualquer forma nesse ponto, ocorreu uma colisao em Y, zera a velocidade nesse eixo
                ent->setGrounded(true);//a entidade esta no chao
            }
            if(offsetX)
               ent->setVel(sf::Vector2f(0.0f, entVelY));//se ocorreu colisao em X zera a velocidade nesse eixo 
        }
 
    }
}

void Physics::collideEntities(){

    Entities::Entity *a, *b;
    for(int i = bodies->size()-1; i >= 0; i--){
        for(int j = i + i; j >= 0; j--)
        {
            a = (*bodies)[i];
            b = (*bodies)[j];
            
            if(checkEntityCollision(a, b)){///se a colidiu com b, chama os metodos de colisao de cada uma passando ponteiro para a outra
                a->onCollide(b);
                b->onCollide(a);
            }
        }
    }
}

void Physics::applyGravity(float dt){
    for(int i = bodies->size()-1; i >= 0; i--){
        if((*bodies)[i]->getVel().y < maxVertVel)
            (*bodies)[i]->setVel(sf::Vector2f((*bodies)[i]->getVel().x, (*bodies)[i]->getVel().y + gravity*dt));
        else
            (*bodies)[i]->setVel(sf::Vector2f((*bodies)[i]->getVel().x, maxVertVel));
        
        //printf("to %f with %f\n", (*bodies)[i]->getVel().y, dt);
    }

}
