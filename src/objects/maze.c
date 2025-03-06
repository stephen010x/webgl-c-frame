#include <string.h>
//#include <cglm/cglm.h>
#include "maze.h"







void maze_traverse(MAZE* maze/*, vec3 start, vec3 end*/) {
    /*int buffer[maze->cols*maze->rows][2];
    GRID(maze->cols, maze->rows) grid = {0};
    int buff_index = 0;
    int x = 0;
    int y = 5;
    while (x != maze->cols-1 && y != 5) {
        int k = rand()%4;
        switch ()
    }*/

    int y = maze->cols/2;
    for (int x = 0; x < maze->cols; x++) {
        int ny = maze->cols/2 + RANDRANGE(-maze->cols/2, maze->cols/2+1);
        
        y = ny;
    }
}







MAZE* maze_init(MAZE* maze, int cols, int rows, COLOR color, SHADER* shader) {

    WALLS_PTR(cols) hwalls = malloc(sizeof(WALLS(cols)));
    WALLS_PTR(rows) vwalls = malloc(sizeof(WALLS(rows)));
    GRID_PTR(cols, rows) grid = malloc(sizeof(GRID(cols, rows)));
    memset(grid, 0, sizeof(GRID(cols, rows)));

    *maze = (MAZE){
        .cols = cols,
        .rows = rows,
        .color = color,
        .shader = shader,
        .hwalls = hwalls,
        .vwalls = vwalls,
        .grid = grid,
    };

    // generate horizontal walls
    for (int c = 0; c < cols; c++)
        for (int r = 0; r < rows+1; r++) {
            hwalls[r][c] = WALL_EXIST;
        }

    // generate vertical walls
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols+1; c++) {
            vwalls[c][r] = WALL_EXIST;
        }

    /*int start = RANDRANGE(0, rows);
    int end = RANDRANGE(0, rows);

    bool no_change = false;
    while (!no_change) {
        for (int y = 0; y < rows; y++)
    }*/

    // I don't have time for good maze generation, so...

    for (int i = 0; i < 20; i++) {
        printf("%d\n", rand()%4);
    }

    for (int y = 0; y < rows; y++)
        for (int x = 0; x < cols; x++) {
            MAZE_WALLS walls = maze_findwalls(maze, x, y);
            for (int i = 0; i < RANDRANGE(1,3); i++) {
                int k = rand()%4;
                switch (k) {
                    case 0:
                        *walls.right = WALL_NONE;
                        break;
                    case 1:
                        *walls.left = WALL_NONE;
                        break;
                    case 2:
                        *walls.up = WALL_NONE;
                        break;
                    case 3:
                        *walls.down = WALL_NONE;
                        break;
                }
            }
        }

    for (int x = 0; x < cols; x++) {
        MAZE_WALLS walls;
        walls = maze_findwalls(maze, x, 0);
        *walls.down = WALL_EXIST;
        walls = maze_findwalls(maze, x, rows-1);
        *walls.up = WALL_EXIST;
    }

    for (int y = 0; y < rows; y++) {
        WALL_FLAGS set = WALL_EXIST;
        if (y == maze->cols/2) set = WALL_NONE;
        MAZE_WALLS walls;
        walls = maze_findwalls(maze, 0, y);
        *walls.left = set;
        walls = maze_findwalls(maze, cols-1, y);
        *walls.right = set;
    }

    for (int i = 0; i < 3; i++) {
        MAZE_WALLS walls;
        walls = maze_findwalls(maze, i, maze->cols/2+1);
        *walls.left = WALL_NONE;
        walls = maze_findwalls(maze, cols-1-i, maze->cols/2);
        *walls.right = WALL_NONE;
    }

    /*for (int y = 1; y < 10; y++)
        for (int x = 1; x < 10; x++) {
            vwalls[x][y] = 0;
        }*/

    return maze;
}





void maze_destroy(MAZE* maze) {
    free(maze->hwalls);
    free(maze->vwalls);
    free(maze->grid);
}




MAZE* maze_draw(MAZE* maze, double t) {
    WALLS_PTR(maze->cols) hwalls = maze->hwalls;
    WALLS_PTR(maze->rows) vwalls = maze->vwalls;

    // draw the left border of maze
    for (int r = 0; r < maze->rows; r++) {
        WALL_FLAGS flags = maze_getwalls(maze, 0, r);
        if (flags & WALL_LEFT) {
            float x, y;
            maze_getpos(maze, 0, r, &x, &y);
            x -= CELL_SIZE/2.0;
            draw_rectangle(
                WALL_THICK*1.5, WALL_LENGTH, 0, (vec2){x, y}, maze->color, maze->shader);
        }
    }

    // draw the bottom border of maze
    for (int c = 0; c < maze->cols; c++) {
        WALL_FLAGS flags = maze_getwalls(maze, c, 0);
        if (flags & WALL_DOWN) {
            float x, y;
            maze_getpos(maze, c, 0, &x, &y);
            y -= CELL_SIZE/2.0;
            draw_rectangle(
                WALL_LENGTH, WALL_THICK*1.5, 0, (vec2){x, y}, maze->color, maze->shader);
        }
    }

    // draw the top and right walls of each of the cells
    for (int r = 0; r < maze->rows; r++)
        for (int c = 0; c < maze->cols; c++) {
            WALL_FLAGS flags = maze_getwalls(maze, c, r);
            float x, y;
            maze_getpos(maze, c, r, &x, &y);
            
            if (flags & WALL_RIGHT)
                draw_rectangle(
                    WALL_THICK*1.5, WALL_LENGTH, 0, (vec2){x + CELL_SIZE/2.0, y}, 
                    maze->color, maze->shader);

            if (flags & WALL_UP)
                draw_rectangle(
                    WALL_LENGTH, WALL_THICK*1.5, 0, (vec2){x, y + CELL_SIZE/2.0}, 
                    maze->color, maze->shader);
        }
    return maze;
}








// TODO: finish implementing this
// it will basically just return the wall status on each four sides of the
// square pointed to with the x and y
// TODO: inline this
WALL_FLAGS maze_getwalls(MAZE* maze, int c, int r) {
    MAZE_WALLS walls = maze_findwalls(maze, c, r);
    WALL_FLAGS retval = 0;
    
    if (*walls.up    == WALL_EXIST) retval |= WALL_UP;
    if (*walls.down  == WALL_EXIST) retval |= WALL_DOWN;
    if (*walls.left  == WALL_EXIST) retval |= WALL_LEFT;
    if (*walls.right == WALL_EXIST) retval |= WALL_RIGHT;
    
    return retval;
}






// TODO: inline this
MAZE_WALLS maze_findwalls(MAZE* maze, int c, int r) {
    MAZE_WALLS walls;
    WALLS_PTR(maze->cols) hwalls = maze->hwalls;
    WALLS_PTR(maze->rows) vwalls = maze->vwalls;

    walls.down  = &vwalls[ c   ][ r ];
    walls.up    = &vwalls[ c+1 ][ r ];
    walls.left  = &hwalls[ r   ][ c ];
    walls.right = &hwalls[ r+1 ][ c ];

    return walls;
}






// this converts position to cell and column
// TODO: finish implementing this
void maze_getcell(MAZE* maze, float x, float y, int* c, int* r) {
    return;
}




void maze_getpos(MAZE* maze, int c, int r, float* x, float* y) {
    *x = (float)c*CELL_SIZE + maze->x;
    *y = (float)r*CELL_SIZE + maze->y;
}
