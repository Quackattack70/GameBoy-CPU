#include "GameRender.h"

GameRender::GameRender(){
    if (!glfwInit()){
        fprintf(stderr, "Error occured");
        exit(-1);
    }
    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    this->wind = glfwCreateWindow(320, 288, "GB", NULL, NULL);
    
    if(this->wind == NULL){
        fprintf(stderr, "Error occured");
        glfwTerminate();
        exit(-1);
    }
    
    this->tileh = new TileHandler();
    this->tileh->initTiles(&this->state);
}

void GameRender::init(){
    
    glfwMakeContextCurrent(this->wind);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 320, 288, 0, 1, -1);
    glMatrixMode(GL_MODELVIEW);
}

void GameRender::IOHandle(){
    if (GB_A == GLFW_PRESS){
        
    }
    if (GB_B == GLFW_PRESS){
        
    }
}

void GameRender::cancel(){
    glfwDestroyWindow(this->wind);
    exit(0);
}

void GameRender::start(){
    setColorCompatible(&this->state);
    glBegin(GL_POLYGON);
#if mainGraphics == GBC_GRAPHICS
    
#elif mainGraphics == GB_GRAPHICS
    
#endif
    glEnd();
}

void GameRender::update(){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
#if mainGraphics == GBC_GRAPHICS
    
#elif mainGraphics == GB_GRAPHICS
    
#endif
    glEnd();
}

void GameRender::loop(){
    printf("Creating Window...\n");
    this->init();
    this->start();
    printf("Starting GB...\n");
    
    state.pc = 150;
    
    while(glfwWindowShouldClose(this->wind) == 0){
        this->update();
        EmulateInstruct(&this->state);
        this->IOHandle();
        
        glfwSwapBuffers(this->wind);
        glfwPollEvents();
    }
    
    printf("Closing GB...\n");
    this->cancel();
}