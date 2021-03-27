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
            return offset;
        }
        else
            return 0;//se a parte direita da entidade nao esta dentro de um bloco solido, nao ha offset para ser retorado
    else//Esquerda
        if(pMap->isPositionSolid(ent->getPos().x, ent->getPos().y)
        || pMap->isPositionSolid(ent->getPos().x, ent->getPos().y + ent->getRect().y))
        {
            float offset = ent->getPos().x; 
            offset = offset - TILE_WIDTH*((int)(offset/TILE_WIDTH)+1);//verifica quanto a entidade entrou no bloco a sua esquerda: offset = Xentidade - Xbloco = Xentidade - TAMANHO_BLOCO*ceil(Xentidade/TAMANHO_BLOCO)
            return offset;
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
            return offset;
        }
        else
            return 0.;//se a parte de baixo da entidade nao esta dentro de um bloco solido, nao ha offset para ser retorado
    else //Cima
        if(pMap->isPositionSolid(ent->getPos().x, ent->getPos().y)
        || pMap->isPositionSolid(ent->getPos().x + ent->getRect().x, ent->getPos().y))
        {
            float offset = ent->getPos().y; 
            offset = offset - TILE_HEIGHT*((int)(offset/TILE_HEIGHT)+1);//verifica quanto a entidade entrou no bloco acima de si: offset = Yentidade - Ybloco = Yentidade - TAMANHO_BLOCO*ceil(Yentidade/TAMANHO_BLOCO)
            return offset;
        }
        else
            return 0;//se a parte de cima da entidade nao esta dentro de um bloco solido, nao ha offset para ser retorado
}


void Physics::collideMap(float dt){

    float offsetX, offsetY;//quanto uma entidade sobrepos um bloco solido em cada eixo
    float entVelX, entVelY;//velocidade da entidade na ultima atualizacao
    Entities::Entity* ent;//ponteiro para a entidade

    for(int i = bodies->size()-1; i >= 0; i--){//para cada entidade carregada

        ent = (*bodies)[i];//resgata os dados da entidade em questao
        entVelX = ent->getVel().x;
        entVelY = ent->getVel().y;

        offsetX = getOffsetX(ent);//calcula o offset de ambos os eixos
        offsetY = getOffsetY(ent);

        //se o offset vertical for menor que o ultimo deslocamento da entidade, provavelmente ocorreu uma colisao em Y
        if(offsetY*offsetY <= entVelY*entVelY*dt*dt && offsetY != 0.0f){
            ent->setPos(sf::Vector2f(ent->getPos().x, ent->getPos().y - 1.1f*offsetY));//corrige a sobreposicao do eixo X

            offsetX = getOffsetX(ent);//verifica se X continua sobreposto apos a correcao
            if (offsetX != 0){//se X continua sobreposto, a colisao nao ocorreu apenas em Y, mas pode ter ocorrido apenas em X
                ent->setPos(sf::Vector2f(ent->getPos().x - 1.1f*offsetX, ent->getPos().y + 1.1f*offsetY));//corrige a sobreposicao de X e desfaz a correcao anterior em Y
                offsetY = getOffsetY(ent);//se Y agora nao esta mais sobreposto mesmo com a correcao anulada, signfica que a colisao era apenas em X
                ent->setPos(sf::Vector2f(ent->getPos().x, ent->getPos().y - 1.1f*offsetY));//se Y voltou a ficar sobreposto apos X ter sido corrigido, a colisao era em X e Y. Refaz a correcao de Y 
            }
        }
        else{//caso contrario, é mais provavel uma colisao em X
            ent->setPos(sf::Vector2f(ent->getPos().x - 1.1f*offsetX, ent->getPos().y));//corrige a sobreposicao no eixo X

            offsetY = getOffsetY(ent);//verifica se Y continua sobreposto apos a correcao
            if (offsetY != 0){//se Y continua sobreposto, a colisao nao ocorreu apenas em X, mas pode ter ocorrido apenas em Y
                ent->setPos(sf::Vector2f(ent->getPos().x + 1.1f*offsetX, ent->getPos().y - 1.1f*offsetY));//corrige a sobreposicao de Y e desfaz a correcao anterior em X
                offsetX = getOffsetX(ent);//se X agora nao esta mais sobreposto mesmo com a correcao anulada, signfica que a colisao era apenas em Y
                ent->setPos(sf::Vector2f(ent->getPos().x - 1.1f*offsetX, ent->getPos().y));//se X voltou a ficar sobreposto apos Y ter sido corrigido, a colisao era em X e Y. Refaz a correcao de X
            }
        }


        
    }


}

void Physics::collideEntities(){

}
