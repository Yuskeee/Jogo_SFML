#include "Graphics.h"
#include "Events.h"

int main(){

    Graphics gGraphics(400, 300, "teste");

    windowHandle gWindowHandle = gGraphics.getWindowHandle();

    Events gEvents(gWindowHandle);
    
    spriteID testSprite = gGraphics.createSprite(gGraphics.loadTexture("../assets/green_alien.png"));//loadTexture retorna o ID da textura direto para createSprite
    
    spriteRect testRect(0, 0, 16, 20);//recorte da textura
    gGraphics.setSpriteRect(testSprite, testRect);
    
    gGraphics.setSpritePos(testSprite,40.0,10.0);
    gGraphics.setBackground(testSprite);

    textID testText = gGraphics.createText(gGraphics.loadFont("../fonts/04B_30__.TTF"),"teste", 20);
    float textPosX = 0, textPosY = 0, textVelX = 0, textVelY = 0;

    while(gGraphics.isWindowOpen()){

        gEvents.pollAll();

        if (gEvents.getCloseEvent()){
            gGraphics.closeWindow();
        }
        
        if(gEvents.keyDown(Events::keycode::W))
            textPosY += -0.1;
        if(gEvents.keyDown(Events::keycode::D))
            textPosX += 0.1;
        if(gEvents.keyDown(Events::keycode::S))
            textPosY += 0.1;
        if(gEvents.keyDown(Events::keycode::A))
            textPosX += -0.1;
      

        //gGraphics.drawSprite(testSprite);

        gGraphics.setTextPos(testText, textPosX, textPosY);
        gGraphics.drawText(testText);
        gGraphics.render();
    }
    return 0;
}