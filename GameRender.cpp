#include "GameRender.h"

GameRender::GameRender(char *filename){
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
    
    initMemory(&this->state, filename);
    
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
    uint8_t joyp = this->state.memory[0xff00];
    if (GB_A == GLFW_PRESS){
        this->state.memory[0xff00] = (1) | joyp;
    }
    if (GB_B == GLFW_PRESS){
        this->state.memory[0xff00] = (2) | joyp;
    }
    else {
        this->state.memory[0xff00] = 0;
    }
}

void GameRender::cancel(){
    glfwDestroyWindow(this->wind);
    exit(0);
}

void GameRender::start(){
    setColorCompatible(&this->state);
    glBegin(GL_POINT);
    
#if mainGraphics == GBC_GRAPHICS
    for (int i =0; i < 360; i++){
        int pix = 0;
        for (int x= 0; x < 8; x++){
            for (int y= 0; y < 8; y++){
                int r = this->tileh->positions[i].tile.pixels[pix].color.r;
                int g = this->tileh->positions[i].tile.pixels[pix].color.g;
                int b = this->tileh->positions[i].tile.pixels[pix].color.b;
                
                glColor3i(r, g, b);
                glVertex2i((i * 8) + x, (i * 8) + y);
                glVertex2i((i * 8) + x + 1, (i * 8) + y);
                glVertex2i((i * 8) + x + 1, (i * 8) + y + 1);
                glVertex2i((i * 8) + x, (i * 8) + y + 1);
                pix++;
            }
        }
    }
    
#elif mainGraphics == GB_GRAPHICS
    
#endif
    glEnd();
}

void GameRender::update(){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINT);
    
#if mainGraphics == GBC_GRAPHICS
    for (int i =0; i < 360; i++){
        int pix = 0;
        for (int x= 0; x < 8; x++){
            for (int y= 0; y < 8; y++){
                int r = this->tileh->positions[i].tile.pixels[pix].color.r;
                int g = this->tileh->positions[i].tile.pixels[pix].color.g;
                int b = this->tileh->positions[i].tile.pixels[pix].color.b;
                
                glColor3i(r, g, b);
                glVertex2i((i * 8) + x, (i * 8) + y);
                pix++;
            }
        }
    }
    
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
        this->tileh->initTiles(&this->state);
        this->IOHandle();
        
        glfwSwapBuffers(this->wind);
        glfwPollEvents();
    }
    printf("Closing GB...\n");
    this->cancel();
}