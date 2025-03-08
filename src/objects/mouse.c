#include <math.h>

#include "mouse.h"
#include "../core/input.h"




void mouse_collide_cell(PMOUSE* mouse, int c, int r);
void mouse_collide_rect(PMOUSE* mouse, float rx, float ry, float width, float height);
void mouse_draw_wall_test(PMOUSE* mouse, double t);




PMOUSE* mouse_init(PMOUSE* mouse, float x, float y, float scale, COLOR color, MAZE* maze, SHADER* shader) {
    *mouse = (PMOUSE){
        .x = x,
        .y = y,
        .px = x,
        .py = y,
        .scale = scale,
        .speed = 0.01,
        .color = color,
        .pcolor = (COLOR){0,0,0,0},
        .shader = shader,
        .maze = maze,
    };

    return mouse;
}




void mouse_draw(PMOUSE* mouse, double t) {
    // TODO: Add an assert to see if shapes.c has been initilized yet
    /*draw_rectangle(
        mouse->scale, mouse->scale, 0, (vec2){mouse->px, mouse->py}, 
        mouse->pcolor, mouse->shader, 0);*/
    float pscale = (CELL_SIZE-WALL_THICK+mouse->scale/2)*1.25;
    float offset = (mouse->scale-pscale)/2;
    draw_rectangle(
        pscale, pscale, 0, (vec2){mouse->px+offset, mouse->py+offset}, 
        mouse->pcolor, mouse->shader, 0);
    draw_rectangle(
        mouse->scale, mouse->scale, 0, (vec2){mouse->x, mouse->y}, 
        mouse->color, mouse->shader, 2);

    //draw_rectangle(0.5, WALL_THICK, 0, (vec2){-0.25, -0.25}, mouse->color, mouse->shader, 1);
    //draw_rectangle(0.5, 0.5, 0, (vec2){0, 0}, mouse->color, mouse->shader, 1);

    //mouse_draw_wall_test(mouse, t);
}





void mouse_draw_wall_test(PMOUSE* mouse, double t) {
    int c, r;
    float x, y;
    maze_getcell(mouse->maze, mouse->px, mouse->py, &c, &r);
    maze_getpos(mouse->maze, c+0, r-0, &x, &y);

    float k = fmod(t/3, 0.5);
    //draw_rectangle(CELL_SIZE, CELL_SIZE, 0, (vec2){x, y}, (COLOR){k,k,k,0.5}, mouse->shader, 0);

    draw_rectangle(
        WALL_LENGTH, WALL_THICK, 0, (vec2){x, y + CELL_SIZE},
        (COLOR){k,k,k,1}, mouse->shader, 1);
    draw_rectangle(
        WALL_LENGTH, WALL_THICK, 0, (vec2){x, y}, 
        (COLOR){k,k,k,1}, mouse->shader, 1);
    draw_rectangle(
        WALL_THICK, WALL_LENGTH, 0, (vec2){x + CELL_SIZE, y},
        (COLOR){k,k,k,1}, mouse->shader, 1);
    draw_rectangle(
        WALL_THICK, WALL_LENGTH, 0, (vec2){x, y}, 
        (COLOR){k,k,k,1}, mouse->shader, 1);
}






//#define CELL_WALL_MAX (CELL_SIZE-WALL_THICK)
//#define CELL_WALL_MIN WALL_THICK

// get cell using previous position, and collide using current position
void mouse_update(PMOUSE* mouse, double t, float dt) {
    // these need to happen at the beginning rather than the end in order for
    // the draw function to also have valid px and py values (for the trail)
    mouse->px = mouse->x;
    mouse->py = mouse->y;

    float dx = (key[KEY_RIGHT] - key[KEY_LEFT]) * mouse->speed;
    float dy = (key[KEY_UP]    - key[KEY_DOWN]) * mouse->speed;

    float div = sqrt((dx*dx != 0.0) + (dy*dy != 0.0));

    div = 1.0;

    if (div != 0) {
        mouse->x += dx/div;
        mouse->y += dy/div;
    }

    //printf("%f, %f\n", mouse->x, mouse->y);

    int c, r;
    maze_getcell(mouse->maze, mouse->px, mouse->py, &c, &r);

    mouse_collide_cell(mouse, c, r);

    // TODO: these are neccissary to fix all collision glitches
    // however, they cause sliding problems. Solve this!
    /*mouse_collide_cell(mouse, c+1, r+1);
    mouse_collide_cell(mouse, c+1, r-1);
    mouse_collide_cell(mouse, c-1, r+1);
    mouse_collide_cell(mouse, c-1, r-1);*/

    //mouse_collide_rect(mouse, -0.25, -0.25, 0.5, WALL_THICK);
    //mouse_collide_rect(mouse, 0, 0, 0.5, 0.5);

    //mouse->px = mouse->x;
    //mouse->py = mouse->y;
}



void mouse_collide_cell(PMOUSE* mouse, int c, int r) {
    float cx, cy;
    maze_getpos(mouse->maze, c, r, &cx, &cy);

    WALL_FLAGS flags = maze_getwalls(mouse->maze, c, r);

    if (flags & WALL_UP)
        mouse_collide_rect(mouse, cx, cy + CELL_SIZE, WALL_LENGTH, WALL_THICK);
    if (flags & WALL_DOWN)
        mouse_collide_rect(mouse, cx, cy, WALL_LENGTH, WALL_THICK);
    if (flags & WALL_RIGHT)
        mouse_collide_rect(mouse, cx + CELL_SIZE, cy, WALL_THICK, WALL_LENGTH);
    if (flags & WALL_LEFT)
        mouse_collide_rect(mouse, cx, cy, WALL_THICK, WALL_LENGTH);
}



void mouse_collide_rect(PMOUSE* mouse, float rx, float ry, float width, float height) {
    register float x  = mouse->x;
    register float y  = mouse->y;
    register float scale = mouse->scale;

    register float up_off    = ry - scale;
    register float down_off  = ry + height;
    register float right_off = rx - scale;
    register float left_off  = rx + width;

    // if current state inside box
    if ((x > right_off) && (x < left_off) && (y > up_off) && (y < down_off)) {

        register float px = mouse->px;
        register float py = mouse->py;
    
        // if past state in diagonal cast
        bool test1 = (py-ry+scale )*(width+scale) >  (px-rx+scale)*(height+scale);
        bool test2 = (py-ry-height)*(width+scale) > -(px-rx+scale)*(height+scale);

        // final checks and position asserts
        if (test1) if (test2) mouse->y = down_off;
                   else       mouse->x = right_off;
        else       if (test2) mouse->x = left_off;
                   else       mouse->y = up_off;
    }
}
