#ifndef MOUSE_H
#define MOUSE_H

// includes COLOR
#include "../core/model.h"
#include "maze.h"
#include "shapes.h"


typedef struct {
    float x, y;
    float px, py;
    float scale;
    float speed;
    COLOR color;
    COLOR pcolor;
    MAZE* maze;
    SHADER* shader;
} PMOUSE;


PMOUSE* mouse_init(PMOUSE* mouse, float x, float y, float scale, COLOR color, MAZE* maze, SHADER* shader);
void mouse_draw(PMOUSE* mouse, double t);
void mouse_update(PMOUSE* mouse, double t, float dt);


#endif
