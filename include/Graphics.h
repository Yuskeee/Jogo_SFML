#include<SFML/Graphics.hpp>
#include <vector>

typedef sf::RenderWindow* windowHandle;
typedef sf::Rect<int> spriteRect;//typedefs para usar tipos da sfml fora desse arquivo

typedef int textureID;//int que representa a posicao de uma textura na lista
typedef int spriteID;//int que representa a posicao de um sprite na lista

class Graphics{

private:
    sf::RenderWindow screen;//objeto janela da sfml

    int screenWidth, screenHeight; //altura e largura da tela em pixels

    //cria a janela com estilo padrao 
    void createWindow(int screenWidth, int screenHeight, const char* windowName);

    std::vector<sf::Texture*> textures;//lista de texturas carregadas
    std::vector<sf::Sprite*> sprites;//lista de sprites criados

    spriteID backgroundSprite;//id do sprite selecionado como fundo

public:
    Graphics(int screenWidth = 800, int screenHeight = 600, const char* windowName = "window");
    ~Graphics();    

    //retorna um ponteiro para a janela. Util se outras classes precisarem acessar funcoes do objeto janela
    windowHandle getWindowHandle();

    bool isWindowOpen();
    void closeWindow();

    textureID loadTexture(const char* file);//carrega textura de arquivo
    
    spriteID createSprite(textureID baseTexture);//cria um sprite baseado em uma textura, retorna seu id
    void setSpriteRect(spriteID sprite, const spriteRect& rect);//seleciona parte da textura para ser renderizada
    void setSpritePos(spriteID sprite, float x, float y);//modifica a posicao do sprite
    void drawSprite(spriteID sprite);//desenha o sprite na tela

    void setBackground(spriteID sprite);//usa um sprite como plano de fundo


    void render();//exibe na tela o que foi desenhado

};