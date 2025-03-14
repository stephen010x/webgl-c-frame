#include <math.h>

#include "mouse.h"
#include "../core/input.h"
#include "../core/texture.h"
#include "drawsurface.h"




void mouse_collide_cell(PMOUSE* mouse, int c, int r);
void mouse_collide_rect(PMOUSE* mouse, float rx, float ry, float width, float height);
void mouse_draw_wall_test(PMOUSE* mouse, double t);

/*static void path_setup(SHADER* shader, void* data) {
    PMOUSE* mouse = data;

    mat4 viewmat;
    glm_ortho(
        0, 0,
        c->wmin[1], c->wmax[1],
        0, 1000,
        viewmat
    );
}*/



void mouse_surface_draw(DRAWSURFACE* surface, PMOUSE* mouse, double t, float dt);


PMOUSE* mouse_init(PMOUSE* mouse, float x, float y, float scale, COLOR color, MAZE* maze, SHADER* shader) {
    float maze_width  = CELL_SIZE * maze->cols;
    float maze_height = CELL_SIZE * maze->rows;

    *mouse = (PMOUSE){
        .mode = MOUSE_TOP,
        .x = x,
        .y = y,
        .px = x,
        .py = y,
        //.dx = x,
        //.dy = y,
        .scale = scale,
        .speed = 0.01,
        .color = color,
        .pcolor = (COLOR){0,0,0,0},
        .shader2 = shader,
        //.path_shader = 
        .maze = maze,
        .trail_camera = {
            .pos = {0,0,1},
            .zoom = 1,
            .type = CAMERA_ORTHOGRAPHIC,
            //.type = CAMERA_NULL,
            //.wmin = {-maze_width/2, -maze_height/2, 0},
            //.wmax = { maze_width/2,  maze_height/2, 10},
        },
        .camera = {
            .pos = {x+scale/2,y+scale/2,scale},
            .rot = {MATH_PI/2, MATH_PI, MATH_PI},
            .fov = DEG_TO_RAD(90), //MATH_PI/2,
            .type = CAMERA_PERSPECTIVE,
        },
    };

    //printf("%f\n", DEG_TO_RAD(90));


    camera_init(&mouse->trail_camera);
    camera_init(&mouse->camera);

    camera_update_actual(&mouse->camera);

    camera_setviewport(&mouse->trail_camera, 
        (vec3){-maze_width/2, -maze_height/2,  1},
        (vec3){ maze_width/2,  maze_height/2, -1});
    /*camera_setviewport(&mouse->trail_camera, 
        (vec3){-1, -1,  1},
        (vec3){ 1,  1, -1});*/
    /*camera_update(&mouse->trail_camera);

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            printf("%f, ", mouse->trail_camera.viewmat[y][x]);
        }
        printf("; ");
    }
    printf("\n");*/
    

    maze->surface.callback = (DRAWSURFACE_CALLBACK)&mouse_surface_draw;
    maze->surface.data = mouse;
    
    return mouse;
}




void mouse_draw(PMOUSE* mouse, double t) {
    // TODO: Add an assert to see if shapes.c has been initilized yet
    /*draw_rectangle(
        mouse->scale, mouse->scale, 0, (vec2){mouse->px, mouse->py}, 
        mouse->pcolor, mouse->shader, 0);*/

    if (mouse->shader3)
        draw_rect3((vec3){mouse->x, mouse->y, 0}, (vec3){mouse->scale, mouse->scale, mouse->scale}, 
        NULL, 0, mouse->color, mouse->shader3);
    else
        draw_rectangle(
            //mouse->scale, mouse->scale, 0, (vec2){mouse->dx, mouse->dy},
            mouse->scale, mouse->scale, 0, (vec2){mouse->x, mouse->y},
            mouse->color /*DEBUG*//*(COLOR){0,1,0,1}*/, mouse->shader2, -1);

    /*float pscale = (CELL_SIZE-WALL_THICK+mouse->scale/2)*1.25;
    float offset = (mouse->scale-pscale)/2;
    
    draw_rectangle(
        pscale, pscale, 0, (vec2){mouse->px+offset, mouse->py+offset}, 
        /\*mouse->pcolor*\/(COLOR){1,0,0,1}, mouse->shader, 0);*/

    //draw_rectangle(0.5, WALL_THICK, 0, (vec2){-0.25, -0.25}, mouse->color, mouse->shader, 1);
    //draw_rectangle(0.5, 0.5, 0, (vec2){0, 0}, mouse->color, mouse->shader, 1);

    //mouse_draw_wall_test(mouse, t);
}



void mouse_surface_draw(DRAWSURFACE* surface, PMOUSE* mouse, double t, float dt) {

    camera_update(&mouse->trail_camera);
    camera_apply(&mouse->trail_camera, mouse->shader2->program);

    float pscale = (CELL_SIZE-WALL_THICK+mouse->scale/2)*1.25;
    float offset = (mouse->scale-pscale)/2;
    
    draw_rectangle(
        pscale, pscale, 0, (vec2){mouse->px+offset, mouse->py+offset}, 
        //pscale, pscale, 0, (vec2){mouse->dx+offset, mouse->dy+offset}, 
        mouse->pcolor, mouse->shader2, 2);
}





void mouse_draw_wall_test(PMOUSE* mouse, double t) {
    int c, r;
    float x, y;
    maze_getcell(mouse->maze, mouse->px, mouse->py, &c, &r);
    maze_getpos(mouse->maze, c+0, r-0, &x, &y);

    float k = fmod(t/3, 0.5);
    //draw_rectangle(CELL_SIZE, CELL_SIZE, 0, (vec2){x, y}, (COLOR){k,k,k,0.5}, mouse->shader2, -1);

    draw_rectangle(
        WALL_LENGTH, WALL_THICK, 0, (vec2){x, y + CELL_SIZE},
        (COLOR){k,k,k,1}, mouse->shader2, 0);
    draw_rectangle(
        WALL_LENGTH, WALL_THICK, 0, (vec2){x, y}, 
        (COLOR){k,k,k,1}, mouse->shader2, 0);
    draw_rectangle(
        WALL_THICK, WALL_LENGTH, 0, (vec2){x + CELL_SIZE, y},
        (COLOR){k,k,k,1}, mouse->shader2, 0);
    draw_rectangle(
        WALL_THICK, WALL_LENGTH, 0, (vec2){x, y}, 
        (COLOR){k,k,k,1}, mouse->shader2, 0);
}






void mouse_update_fps(PMOUSE* mouse, double t, float dt);

//#define CELL_WALL_MAX (CELL_SIZE-WALL_THICK)
//#define CELL_WALL_MIN WALL_THICK

// get cell using previous position, and collide using current position
void mouse_update(PMOUSE* mouse, double t, float dt) {

    mouse->px = mouse->x;
    mouse->py = mouse->y;

    float speed;
    if (mouse->mode == MOUSE_FPS) {
        //return mouse_update_fps(mouse, t, dt);
        mouse_update_fps(mouse, t, dt);
        //speed = mouse->speed / 4;
        return;
    } else {
        speed = mouse->speed;
    }

    // these need to happen at the beginning rather than the end in order for
    // the draw function to also have valid px and py values (for the trail)
    mouse->px = mouse->x;
    mouse->py = mouse->y;

    float dx = ((key[KEY_RIGHT] || key[KEY_D]) - (key[KEY_LEFT] || key[KEY_A])) * speed;
    float dy = ((key[KEY_UP]    || key[KEY_W]) - (key[KEY_DOWN] || key[KEY_S])) * speed;

    float div = sqrt((dx*dx != 0.0) + (dy*dy != 0.0));

    div = 1.0;

    if (div != 0) {
        mouse->x += dx/div;
        mouse->y += dy/div;
    }

    //printf("%f, %f\n", mouse->x, mouse->y);

    int c, r;
    //maze_getcell(mouse->maze, mouse->px, mouse->py, &c, &r);
    maze_getcell(mouse->maze, mouse->x, mouse->y, &c, &r);

    // alright. Order matters. If you do these out of order, then sliding conflicts occur
    mouse_collide_cell(mouse, c, r);
    
    // mouse_collide_cell(mouse, c+1, r  );
    // mouse_collide_cell(mouse, c,   r+1);
    // mouse_collide_cell(mouse, c+1, r+1);

    // I dunno why these prevent sliding while the others don't
    mouse_collide_cell(mouse, c+1, r  );
    mouse_collide_cell(mouse, c,   r+1);
    mouse_collide_cell(mouse, c-1, r  );
    mouse_collide_cell(mouse, c,   r-1);

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

    //mouse->dx = (mouse->dx + mouse->x)/2;
    //mouse->dy = (mouse->dy + mouse->y)/2;
}


#define X 0
#define Y 1
#define Z 2

void mouse_update_fps(PMOUSE* m, double t, float dt) {
    if (!mouse.grabbed)
        return;

    m->camera.pos[X] = m->x + m->scale/2;
    m->camera.pos[Y] = m->y + m->scale/2;

    m->camera.rot[Y] +=  mouse.dx / 200.0;
    m->camera.rot[X] +=  mouse.dy / 200.0;

    //m->camera.rot[X] += 0.01;

    // TODO: seriously, create a clamp macro
    if (m->camera.rot[X] > MATH_PI*1/2+MATH_PI/2.5)
        m->camera.rot[X] = MATH_PI*1/2+MATH_PI/2.5;
    else if (m->camera.rot[X] < MATH_PI*1/2-MATH_PI/2.5)
        m->camera.rot[X] = MATH_PI*1/2-MATH_PI/2.5;

    //printf("%d, %d, %f, %f\n", mouse.dx, mouse.dy, m->camera.rot[X], m->camera.rot[Y]);

    camera_update_actual(&m->camera);



    float speed = m->speed / 8;

    if (key[KEY_SHIFT])
        speed *= 2;

    float dx = ((key[KEY_RIGHT] || key[KEY_D]) - (key[KEY_LEFT] || key[KEY_A])) * speed;
    float dy = ((key[KEY_UP]    || key[KEY_W]) - (key[KEY_DOWN] || key[KEY_S])) * speed;

    float div = sqrt((dx*dx != 0.0) + (dy*dy != 0.0));

    if (div != 0) {
        vec3 delta = (vec3){-dx/div, -dy/div, 0};
        glm_vec3_rotate(delta, -m->camera.rot[Y], (vec3){0,0,1});
    
        m->x += delta[0];
        m->y += delta[1];
    }


    int c, r;
    maze_getcell(m->maze, m->x, m->y, &c, &r);

    mouse_collide_cell(m, c, r);
    
    mouse_collide_cell(m, c+1, r  );
    mouse_collide_cell(m, c,   r+1);
    mouse_collide_cell(m, c-1, r  );
    mouse_collide_cell(m, c,   r-1);
}

#undef X
#undef Y
#undef Z



__FORCE_INLINE__ void mouse_collide_cell_static(PMOUSE* mouse, const int c, const int r, const WALL_FLAGS sflags) {
    float cx, cy;
    maze_getpos(mouse->maze, c, r, &cx, &cy);
    
    WALL_FLAGS flags = maze_getwalls(mouse->maze, c, r);
    
    if ((sflags & WALL_UP) & (flags & WALL_UP))
        mouse_collide_rect(mouse, cx, cy + CELL_SIZE, WALL_LENGTH, WALL_THICK);
    if ((sflags & WALL_DOWN) & (flags & WALL_DOWN))
        mouse_collide_rect(mouse, cx, cy, WALL_LENGTH, WALL_THICK);
    if ((sflags & WALL_RIGHT) & (flags & WALL_RIGHT))
        mouse_collide_rect(mouse, cx + CELL_SIZE, cy, WALL_THICK, WALL_LENGTH);
    if ((sflags & WALL_LEFT) & (flags & WALL_LEFT))
        mouse_collide_rect(mouse, cx, cy, WALL_THICK, WALL_LENGTH);
}



void mouse_collide_cell(PMOUSE* mouse, int c, int r) {
    float cx, cy;
    //float cxr, cxl, cyu, cyd;
    maze_getpos(mouse->maze, c, r, &cx, &cy);
    //maze_getpos(mouse->maze, c+1, r+1, &cxr, &cyu);
    //maze_getpos(mouse->maze, c-1, r-1, &cxl, &cyd);

    /*if (flags & WALL_UP)
        mouse_collide_rect(mouse, cx, cy + CELL_SIZE, WALL_LENGTH, WALL_THICK);
    if (flags & WALL_DOWN)
        mouse_collide_rect(mouse, cx, cy, WALL_LENGTH, WALL_THICK);
    if (flags & WALL_RIGHT)
        mouse_collide_rect(mouse, cx + CELL_SIZE, cy, WALL_THICK, WALL_LENGTH);
    if (flags & WALL_LEFT)
        mouse_collide_rect(mouse, cx, cy, WALL_THICK, WALL_LENGTH);*/

    mouse_collide_cell_static(mouse, c, r, WALL_UP | WALL_DOWN | WALL_RIGHT | WALL_LEFT);
    
    /*mouse_collide_cell_static(mouse, cxl, cyd, flags, WALL_UP   | WALL_RIGHT);
    mouse_collide_cell_static(mouse, cxr, cyd, flags, WALL_UP   | WALL_LEFT );
    mouse_collide_cell_static(mouse, cxl, cyu, flags, WALL_DOWN | WALL_RIGHT);
    mouse_collide_cell_static(mouse, cxr, cyu, flags, WALL_DOWN | WALL_LEFT );*/

    /*mouse_collide_cell_static(mouse, c-1, r-1, WALL_UP   | WALL_RIGHT);
    mouse_collide_cell_static(mouse, c+1, r-1, WALL_UP   | WALL_LEFT );
    mouse_collide_cell_static(mouse, c-1, r+1, WALL_DOWN | WALL_RIGHT);
    mouse_collide_cell_static(mouse, c+1, r+1, WALL_DOWN | WALL_LEFT );*/
}



void mouse_collide_rect(PMOUSE* mouse, float rx, float ry, float width, float height) {
    register float x  = mouse->x;
    register float y  = mouse->y;
    register float scale = mouse->scale;

    register float up_off    = ry - scale;
    register float down_off  = ry + height;
    register float right_off = rx - scale;
    register float left_off  = rx + width;

    // this is a duck tape solution to prevent wall stickyness
    // TODO: get rid of this and make this collide algorithm better
    #define MOUSE_COLLIDE_GIVE 0.00001

    // if current state inside box
    if ((x > right_off) && (x < left_off) && 
        (y > up_off   ) && (y < down_off)) {

        register float px = mouse->px;
        register float py = mouse->py;
    
        // if past state in diagonal cast
        bool test1 = (py-ry+scale )*(width+scale) >  (px-rx+scale)*(height+scale);
        bool test2 = (py-ry-height)*(width+scale) > -(px-rx+scale)*(height+scale);

        // alright, so using present values fixes the sticky wall issue
        // but it does force the player to one side of the wall sometimes
        // (which is fine in this case)
        //bool test1 = (y-ry+scale )*(width+scale) >  (x-rx+scale)*(height+scale);
        //bool test2 = (y-ry-height)*(width+scale) > -(x-rx+scale)*(height+scale);

        // final checks and position asserts
        if (test1) if (test2) mouse->y = down_off  + MOUSE_COLLIDE_GIVE;
                   else       mouse->x = right_off - MOUSE_COLLIDE_GIVE;
        else       if (test2) mouse->x = left_off  + MOUSE_COLLIDE_GIVE;
                   else       mouse->y = up_off    - MOUSE_COLLIDE_GIVE;
    }
}
