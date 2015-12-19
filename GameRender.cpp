#include "GameRender.h"

GameRender::GameRender(){
    if (!glfwInit()){
        fprintf(stderr, "Error occured");
        exit(-1);
    }
    
    this->wind = glfwCreateWindow(640, 400, "GB", NULL, NULL);
    
    if(this->wind == NULL){
        fprintf(stderr, "Error occured");
        glfwTerminate();
        exit(-1);
    }
    
    this->tileh = new TileHandler();
}

void GameRender::init(){
    glfwDefaultWindowHints();
    glfwMakeContextCurrent(this->wind);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 640, 400, 0, 1, -1);
    glMatrixMode(GL_MODELVIEW);
}

void GameRender::cancel(){
    glfwDestroyWindow(this->wind);
    exit(0);
}

void GameRender::start(){
    glBegin(GL_POLYGON);
    
    glEnd();
}

void GameRender::update(){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    
    glEnd();
}

void GameRender::loop(){
    printf("Creating Window...\n");
    this->init();
    this->start();
    printf("Starting GB...\n");
    
    while(glfwWindowShouldClose(this->wind) == 0){
        this->update();
        EmulateInstruct(&this->state);
        
        glfwSwapBuffers(this->wind);
        glfwPollEvents();
    }
    
    printf("Closing GB...\n");
    this->cancel();
}