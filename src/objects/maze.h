#ifndef MAZE_H
#define MAZE_H

// TODO: I should create a directory to put all the headers in or something.
// and then use make to point to them or something
#include "../core/model.h"
#include "shapes.h"




#define CELL_SIZE ((float)0.1)
#define WALL_THICK ((float)0.01)

#define WALL_LENGTH (CELL_SIZE + WALL_THICK*1.5)



#define WALLS(__n) typeof(unsigned char[__n+1][__n])
#define WALLS_PTR(__n) typeof(unsigned char (*)[__n])
#define GRID(__c, __r) typeof(unsigned char[__c][__r])
#define GRID_PTR(__c, __r) typeof(unsigned char (*)[__r])



#define WALL_NONE  0
#define WALL_EXIST 1
#define CELL_EMPTY 0
#define CELL_USED  1

#define WALL_UP    (1<<0)
#define WALL_DOWN  (1<<1)
#define WALL_LEFT  (1<<2)
#define WALL_RIGHT (1<<3)

typedef unsigned char WALL_FLAGS;

/*#define MAZE(__n) struct {
    int cols;
    int rows;

    COLOR color;

    //unsigned char (*hwalls)[__n];
    //unsigned char (*vwalls)[__n];

    WALLS(__n)* hwalls;
    WALLS(__n)* vwalls;
}*/




typedef struct {
    int cols;
    int rows;

    float x;
    float y;
    // scale is being ignored in favor of CELL_SIZE
    // TODO: implement this later
    float scale;

    COLOR color;

    SHADER* shader;

    void* hwalls;
    void* vwalls;
    void* grid;
} MAZE;


typedef struct {
    unsigned char* up;
    unsigned char* down;
    unsigned char* left;
    unsigned char* right;
} MAZE_WALLS;


MAZE* maze_init(MAZE* maze, int cols, int rows, COLOR color, SHADER* shader);
void maze_destroy(MAZE* maze);
MAZE* maze_draw(MAZE* maze, double t);

WALL_FLAGS maze_getwalls(MAZE* maze, int c, int r);
MAZE_WALLS maze_findwalls(MAZE* maze, int c, int r);

void maze_getcell(MAZE* maze, float x, float y, int* c, int* r);
void maze_getpos(MAZE* maze, int c, int r, float* x, float* y);



/* Holy shit this actually works...
 * This means that sizeof also works during runtime, not just compiletime


#define WALLS(__n) typeof(unsigned char[__n+1][__n])

int main() {
    for (int i = 1; i <= 10; i++) {
        WALLS(i) wall;
        printf("%lu\n", sizeof(WALLS(i)));
    }
    return 0;
}


*/



#endif
