#ifndef GAMERENDER_H
#define GAMERENDER_H

#include "GBFuncs.h"
#include "TileHandler.h"
#include "GBBase.h"
#include "GBFuncs.h"
#include <unistd.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

class GameRender {
public:
    GLFWwindow* wind;
    TileHandler* tileh;
    GBState state;
    GameRender();
    void init();
    void start();
    void update();
    void loop();
    void cancel();
};

#endif

