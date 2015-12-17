#include "GameRender.h"

void GameRender::init(){
    this->wind = glfwCreateWindow(160, 144, "GB", NULL, NULL);
    this->tileh = new TileHandler();
}

void GameRender::cancel(){
    glfwDestroyWindow(this->wind);
}