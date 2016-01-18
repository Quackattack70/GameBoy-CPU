#include "GameRender.h"

GameRender::GameRender(char *filename){
    initMemory(&this->state, filename);
    initLCDCONT(&this->state);
    setColorCompatible(&this->state);
    
    this->tileh = new TileHandler();
    this->tileh->getTilesFromFile(&this->state);
    this->tileh->initTiles(&this->state);
    
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
    glBegin(GL_POLYGON);
    
    for (int i = 0; i < 360; i++){
        int pix = 0;
        for (int x=0; x < 8; x++){
            for (int y=0; y < 8; y++){
                uint8_t co = this->tileh->positions[i].pixels[pix].oldC;

                switch(co){
                    case GB_BLACK:
                        glColor3i(0, 0, 0);
                        break;
                    case GB_WHITE:
                        glColor3i(255, 255, 255);
                        break;
                    case GB_LIGHTGRAY:
                        glColor3i(211, 211, 211);
                        break;
                    case GB_DARKGRAY:
                        glColor3i(105, 105, 105);
                        break;
                }
                glVertex2i((i * 8) + x, (i * 8) + y);
                glVertex2i((i * 8) + x + 1, (i * 8) + y);
                glVertex2i((i * 8) + x + 1, (i * 8) + y + 1);
                glVertex2i((i * 8) + x, (i * 8) + y + 1);
                pix++;
            }
        }
    }
    glEnd();
    printf("rendering complete\n");
}

void GameRender::update(){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    
   
    for (int i = 0; i < 360; i++){
        int pix = 0;
        int mainx = 0;
        int mainy = 0;
        for (int x=0; x < 8; x++){
            for (int y=0; y < 8; y++){
                uint8_t co = this->tileh->positions[i].pixels[pix].oldC;

                switch(co){
                    case GB_BLACK:
                        glColor3i(0, 0, 0);
                        break;
                    case GB_WHITE:
                        glColor3i(255, 255, 255);
                        break;
                    case GB_LIGHTGRAY:
                        glColor3i(211, 211, 211);
                        break;
                    case GB_DARKGRAY:
                        glColor3i(105, 105, 105);
                        break;
                }
                glVertex2i((mainx * 8) + x, (mainy * 8) + y);
                glVertex2i((mainx * 8) + x + 1, (mainy * 8) + y);
                glVertex2i((mainx * 8) + x + 1, (mainy * 8) + y + 1);
                glVertex2i((mainx * 8) + x, (mainy * 8) + y + 1);
                pix++;
                mainy++;
            }
            mainy = 0;
            mainx++;
        }
    }
    EmulateInstruct(&this->state);
    this->tileh->getTilesFromFile(&this->state);
    this->tileh->initTiles(&this->state);
    this->IOHandle();
        
    glEnd();
}

void GameRender::loop(){
    printf("Creating Window...\n");
    this->init();
    this->start();
    printf("Starting GB...\n");
    
    this->state.pc = 0x150;
    
    while(glfwWindowShouldClose(this->wind) == 0){
        this->update();
        
        glfwSwapBuffers(this->wind);
        glfwPollEvents();
    }
    printf("Closing GB...\n");
    printf("A: %02x, F: %02x\n", this->state.a, this->state.f);
    printf("B: %02x, C: %02x\n", this->state.b, this->state.c);
    printf("H: %02x, L: %02x\n", this->state.h, this->state.l);
    printf("PC: %04x, SP: %04x\n", this->state.pc, this->state.sp);
    printf("Graphics: %02x\n", (uint16_t)mainGraphics);
    this->cancel();
}