#ifndef GAMERENDER_H
#define GAMERENDER_H

#include "GBFuncs.h"
#include "TileHandler.h"
#include "GBBase.h"
#include "GBFuncs.h"
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

class GameRender {
public:
    GLFWwindow* wind;
    TileHandler* tileh;
    GBState state;
    GameRender(char *filename);
    void init();
    void IOHandle();
    void start();
    void update();
    void loop();
    void cancel();
};

#define GB_A glfwGetKey(this->wind, GLFW_KEY_Z)
#define GB_B glfwGetKey(this->wind, GLFW_KEY_X)

#endif