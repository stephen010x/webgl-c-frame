#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
// TODO: in an ideal world, this wouldn't be needed in main
#include <GLES2/gl2.h>
// TODO" in an ideal world, these also wouldn't be needed in main
#include <emscripten.h>
#include <emscripten/html5.h>

// TODO: get rid of main header
#include "main.h"
#include "core.h"
#include "objects.h"
#include "shaders/shaders.h"



//*DEBUG*/ extern CUBE_MESH_TYPE cube_mesh;


#define COLOR_RED    ((COLOR){0.8, 0.3, 0.2, 1.0})
#define COLOR_BLUE   ((COLOR){0.3, 0.4, 0.9, 1.0})
#define COLOR_PURPLE ((COLOR){0.7, 0.2, 0.6, 1.0})
#define COLOR_WHITE  ((COLOR){1.0, 1.0, 1.0, 1.0})
#define COLOR_BLACK  ((COLOR){0.0, 0.0, 0.0, 1.0})


//#define MAX_CURVES 5
//BEZIER curves[MAX_CURVES];

//FRACTAL fractal;

#define DT_DIVISOR 100


//WINDOW window;
MOUSE mouse;
// player mouse
PMOUSE pmouse;




//#define SQRT_3 1.73205080757

WORLD world = {
    .light = {
        .type = LIGHTSOURCE_TYPE_DIR,
        .dir = {
            .norm = {0.8, 1, -0.8},
            .range = {0.05, 1.5},
        },
    },
};


CAMERA camera = {
    .zoom = 1,
    .type = CAMERA_ORTHOGRAPHIC,
};

CAMERA camera_1 = {
    .pos = {0,0,-1},
    .rot = {0,0,0},
    .zoom = 1.7,
    .type = CAMERA_ORTHOGRAPHIC,
};

CAMERA camera_2 = {
    .pos = {0,0,0},
    .rot = {0,0,0},
    .fov = 45,
    .type = CAMERA_PERSPECTIVE,
};

CAMERA camera_3 = {
    .pos = {0,0,0},
    .rot = {0,0,0},
    .fov = 45,
    .type = CAMERA_PERSPECTIVE,
};



void init_scene(void);
EM_BOOL frame_loop(double t, void *user_data);
int __main(void);



//MODEL models[NUM_MODELS];
//void controls(double t, float dt);
void update_camera(void);




EMSCRIPTEN_KEEPALIVE int main() {
    printf("starting webgl\n");

    int retval = __main();
    printf("main exited with code (%d)\n", retval);

    return retval;
}



//int swidth, sheight;
//vec3 wmin, wmax;




GLuint poly_program;
GLuint sphere_program;
GLuint bezier_program;
GLuint point_program;
GLuint fractal_program;
GLuint poly3d_program;
GLuint texplane_program;
GLuint maze_program;

SHADER poly_shader;
SHADER poly3d_shader;
SHADER maze_shader;
SHADER point_shader;
SHADER texplane_shader;

ASSET nyan_asset;
TEXTURE nyan_texture;

MAZE maze;



//int swidth, sheight;


int __main(void) {
    // set starting random seed
    srand((unsigned int)time(NULL));

    // remember, you wrote this function.
    int err = init_webgl("#" HTML_CANVAS_ID);
    ASSERT(err == 0, -1, "init_webgl failed\n");

    //emscripten_get_canvas_element_size(HTML_CANVAS_ID, &swidth, &sheight);


    // TODO: allow for different programs to share shader programs
    // so that it doesn't have to recompile every single one.
    // perhaps generate a function to compile them all, and then user
    // their shader id's in manually calling them to compile
    SHADER_DESCRIPTOR sdesc[] = {
        SHADER_DESC_GEN( true,  &poly_program,     poly,    poly    ),
        SHADER_DESC_GEN( false, &sphere_program,   sphere,  simple  ),
        SHADER_DESC_GEN( false, &bezier_program,   bezier,  simple  ),
        SHADER_DESC_GEN( true , &point_program,    point,   simple  ),
        SHADER_DESC_GEN( false, &fractal_program,  poly,    fractal ),
        SHADER_DESC_GEN( true,  &poly3d_program,   poly3d,  simple  ),
        SHADER_DESC_GEN( true,  &texplane_program, texture, texture ),
        //SHADER_DESC_GEN( true,  &maze_program,     maze,    texture ),
    };

    compile_shaders(LENOF(sdesc), sdesc);

    shader_init(&poly_shader,     poly_program,     NULL, NULL);
    shader_init(&poly3d_shader,   poly3d_program,   NULL, NULL);
    shader_init(&point_shader,    point_program,    NULL, NULL);
    shader_init(&texplane_shader, texplane_program, NULL, NULL);
    //shader_init(&maze_shader,     maze_program,     NULL, NULL);

    // TODO: enable clockwise vertex order here or whatever
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glDepthFunc(GL_LESS);

    //asset_load_jpg(&nyan_asset, "/assets/nyan-cat.jpg");
    asset_load_img(&nyan_asset, "crying-cat");
    texture_init(&nyan_texture, &nyan_asset, TEX_NEAREST, TEX_DEFAULT);

    //glDisable(GL_CULL_FACE);
    //glDisable(GL_DEPTH_TEST);

    camera_init(&camera); // this one probably not neccissary
    camera_init(&camera_1);
    camera_init(&camera_2);
    camera_init(&camera_3);
    input_init();
    shapes_init();
        
    init_scene();

    // set frame callback
    // a while loop would stall the webpage, so this is neccissary
    printf("starting animation frame loop\n");
    emscripten_request_animation_frame_loop(&frame_loop, NULL);

    return 0;
}







//BEHAVE behave[NUM_MODELS];

void model_transform(MODEL* model);
void model_update_pipeline(double t, float dt);




#define UPDATE_DIVISOR 1

void update_frame_time(double _t, double* t, float* dt) {
    static double t0;
    double _dt = _t - t0;
    t0 = _t;
    *t = _t/DT_DIVISOR;
    *dt = _dt/DT_DIVISOR;
}






void init_scene(void) {
    // set background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    /*FRACTAL_init(&fractal, 
        (vec2[]){
            {wmin[0], wmin[1]},
            {wmax[0], wmax[1]},
        }, (vec3){0,0,0});*/

    maze_init(&maze, 20, 40, COLOR_WHITE, &poly_shader);
    maze.x = -CELL_SIZE*10;
    maze.y = -CELL_SIZE*20;
    maze.shader_3d = &poly3d_shader;
    maze.shader_trail = &texplane_shader;
    maze.mode = MAZE_MODE_3D;

    float x, y;
    maze_getpos(&maze, 10, 1, &x, &y);
    
    //mouse_init(&pmouse, x, y, 0.03, COLOR_PURPLE, &maze, &poly_shader);
    mouse_init(&pmouse, x, y, 0.03, COLOR_BLACK, &maze, &poly_shader);
    //mouse_init(&pmouse, x, y, CELL_SIZE-WALL_THICK, COLOR_BLACK, &maze, &poly_shader);
    pmouse.pcolor = COLOR_BLUE;
    pmouse.shader3 = &poly3d_shader;
}




void update_cam(void);


EM_BOOL frame_loop(double _t, void *user_data) {
    (void)user_data;

    double t;
    float dt;

    // update frame times
    update_frame_time(_t, &t, &dt);

    /////////////////////////////////////////////
    //// UPDATE HIDDEN FRAMEBUFFER DRAWS  //////
    ///////////////////////////////////////////

    // lol. Nevermind.

    ///////////////////////////
    //// UPDATE CAMERA  //////
    /////////////////////////

    update_cam();
    
    //////////////////////////
    //// UPDATE SCENE  //////
    ////////////////////////

    if (maze.mode == MAZE_MODE_2D || maze.mode == MAZE_MODE_3D) {
        mouse_update(&pmouse, t, dt);
    }


    // update models
    /*if (count%UPDATE_DIVISOR == 0 && behave_flag)
        model_update_pipeline(t, dt);*/

    //////////////////////////
    //// DRAW SCENE  ////////
    ////////////////////////

    /*for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            printf("%f, ", camera.viewmat[y][x]);
        }
        printf(";; ");
    }
    printf("\n");*/

    camera_apply(&camera, poly_program);
    camera_apply(&camera, poly3d_program);
    camera_apply(&camera, point_program);
    camera_apply(&camera, texplane_program);

    // clear the scene
    // note that with the new framebuffer draws, this is neccissary otherwise
    // weird overlap is going to occur
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glClear(GL_DEPTH_BUFFER_BIT);

    /*// draw models
    for (int i = 0; i < NUM_MODELS; i++)
        MODEL_draw(models+i);
        glUniformMatrix4fv(u_proj_mat_loc, 1, GL_FALSE, (GLfloat*)&u_proj_mat);
    }*/

    //draw_rectangle(0.8, 0.8, 0, (vec2){-0.4,-0.4}, COLOR_RED, &poly_shader, 0);
    //draw_rect3((vec3){-0.4,-0.4,-0.4}, (vec3){0.8,0.8,0.8}, (vec3){0,0,0}, 0, COLOR_RED, &poly3d_shader);
    /*cube_mesh.mode = GL_POINTS;
    draw_rect3((vec3){-0.4,-0.4,-0.4}, (vec3){0.8,0.8,0.8}, (vec3){0,0,0}, 0, COLOR_RED, &point_shader);
    cube_mesh.mode = GL_TRIANGLE_STRIP;*/

    //draw_rect3((vec3){-0.4,-0.4,-0.4}, (vec3){0.8,0.8,0.8}, (vec3){0,0,0}, 0, COLOR_RED, &poly3d_shader);

    mouse_draw(&pmouse, t);

    //draw_texture_plane((vec3){-0.5, -0.5, 0}, (vec2){1,1}, (vec3){0,0,1}, 0, &nyan_texture, &texplane_shader);

    // TODO: this overrides some of the cameras for some shaders, which is why it is last
    // please fix this, yeah?
    maze_draw(&maze, t);
    
    // requests frame buffer swap. Will actually render stuff to screen
    // this is neccissary because explicitSwapControl was set to GL_TRUE
    emscripten_webgl_commit_frame();

    // return true to keep looping
    // return false to kill loop
    return EM_TRUE;
}





// TODO: create a transition class for animations like this, 
// that will actually allow things to, you know, transision without having to 
// do all this extra variable setup and whatnot.
void update_cam(void) {

    static int lastmode = MAZE_MODE_2D;
    static int mode = MAZE_MODE_2D;
    static float inter = 1;

    static float cx = 0;
    static float cy = 0;
    static float cinter = 1;

    if (key[KEY_1] && mode != MAZE_MODE_2D && cinter > 0.99) {
        lastmode = mode;
        mode = MAZE_MODE_2D;
        inter = cinter = 0;
    } else if (key[KEY_2] && mode != MAZE_MODE_3D && cinter > 0.99) {
        lastmode = mode;
        mode = MAZE_MODE_3D;
        inter = cinter = 0;
    } else if (key[KEY_3] && mode != MAZE_MODE_DETAILED) {
        lastmode = mode;
        mode = MAZE_MODE_DETAILED;
        inter = cinter = 1;
    }

    inter += 0.016;
    inter = (inter > 1) ? (1) : (inter);

    //camera_rotate_about(&camera, (vec3){0,0,0}, (vec3){(float)(t/20), (float)(t/40)*0, 0}, 3.0);
    //camera_rotate_about(&camera, (vec3){0,0,0.3}, (vec3){-(float)MATH_PI/4, 0, (float)(t/40)}, 3.0);
    //camera.rot[0] += 0.01;
    //camera_update(&camera);

    //printf("pmode %d; mode %d; %f; keys %d%d%d\n", lastmode, mode, inter, key[KEY_1], key[KEY_2], key[KEY_3]);

    cx = (cx*15 + pmouse.x)/16;
    cy = (cy*15 + pmouse.y)/16;
    cinter = (cinter*15 + inter)/16;

    cinter = (cinter > 0.9999) ? (1) : (cinter);

    //printf("inter %f; cinter %f\n", inter, cinter);
    

    if (mode == MAZE_MODE_2D) {

        camera_rotate_about(&camera_1, (vec3){0,0,0}, (vec3){0, 0, 0}, 3.0);
    
    } else if (mode == MAZE_MODE_3D) {

        camera_rotate_about(&camera_2, (vec3){0,0,2}, (vec3){cy/3, -cx/3, 0}, 3.5);

    } else if (mode == MAZE_MODE_DETAILED) {

        //camera_3

    }
    

    switch (mode) {
        case MAZE_MODE_2D:
        
            if ((cinter < 1) && (lastmode == MAZE_MODE_3D)) {
                camera_interpolate(&camera, &camera_2, &camera_1, cinter);
                maze.mode = MAZE_MODE_3D;
            } else {
                camera_set(&camera, &camera_1);
                maze.mode = MAZE_MODE_2D;
            }
            break;


        case MAZE_MODE_3D:
        
            maze.mode = MAZE_MODE_3D;
            
            if ((cinter < 1) && (lastmode == MAZE_MODE_2D)) {
                camera_interpolate(&camera, &camera_1, &camera_2, cinter);
            } else {
                camera_set(&camera, &camera_2);
            }
            break;


        case MAZE_MODE_DETAILED:
        
            maze.mode = MAZE_MODE_DETAILED;
            camera_set(&camera, &camera_3);
            break;
    }
}





/*void controls(double t, float dt) {
    if (mouse.button[0]) {
        camera.rot[1] += (float)mouse.dx/100;
        camera.rot[0] += (float)mouse.dy/100;
    }
    const register float k = MATH_PI*3.0/8.0;
    if (camera.rot[0] > k)
        camera.rot[0] = k;
    if (camera.rot[0] < -k)
        camera.rot[0] = -k;
}*/







// TODO: add this to a behavior object class
/*
if (!disable_rotgrav) {
        // rotate gravity
        // mainly for debugging purposes
        // but it also looks cool
        glm_vec3_copy((vec3)GRAVITY, gravity);
        // TODO: because delta-v isn't hooked up to dt yet,
        // We have to scale gravity manually    glm_vec3_copy((vec3)GRAVITY, gravity);
        glm_vec3_scale(gravity, (float)1/sqrt(BEHAVE_PASSES)*3*GRAV_MUL, gravity);
        glm_vec3_rotate(gravity, (float)MATH_PI/2, (vec3){1,0,0});
        glm_vec3_rotate(gravity, t/300, (vec3){0,0,1});
        glm_vec3_rotate(gravity, t/300, (vec3){0,1,0});
    }
    
void circle_update(MODEL* model, double t, float dt) {
    BEHAVE* b = behave + model->id;

    float sratio = (float)swidth/sheight;

    wall_collide_eval(b, 
        (vec3){wmin[0],wmin[1],wmin[2]}, 
        (vec3){wmax[0],wmax[1],wmax[2]}, dt);

    for (int i = model->id + 1; i < NUM_MODELS; i++)
        sphere_collide_eval(b, behave+i, dt);
}

void model_transform(MODEL* model) {
    BEHAVE* b = behave + model->id;

    // apply transformations to matrix
    vec3 pos;
    glm_vec3_scale(b->pos, 1/b->scale, pos);
    //glm_vec3_scale(b->pos, 1, pos);
    mat4 viewmat = GLM_MAT4_IDENTITY_INIT;
    glm_scale_uni(viewmat, b->scale);
    glm_translate_to(viewmat, pos, model->view_mat);
}*/
