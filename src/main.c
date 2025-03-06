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


#define COLOR_RED   ((COLOR){0.8, 0.3, 0.2, 1.0})
#define COLOR_WHITE ((COLOR){1.0, 1.0, 1.0, 1.0})


//#define MAX_CURVES 5
//BEZIER curves[MAX_CURVES];

//FRACTAL fractal;

#define DT_DIVISOR 100


//WINDOW window;
MOUSE mouse;




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
    .pos = {0,0,-1},
    .rot = {0,0,0},
    .fov = 0,
    .type = CAMERA_ORTHOGRAPHIC,
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

SHADER poly_shader;

MAZE maze;



int __main(void) {
    // set starting random seed
    srand((unsigned int)time(NULL));

    // remember, you wrote this function.
    int err = init_webgl("#canvas");
    ASSERT(err == 0, -1, "init_webgl failed\n");


    // TODO: allow for different programs to share shader programs
    // so that it doesn't have to recompile every single one.
    // perhaps generate a function to compile them all, and then user
    // their shader id's in manually calling them to compile
    SHADER_DESCRIPTOR sdesc[] = {
        SHADER_DESC_GEN( true,  &poly_program,    poly,   poly    ),
        SHADER_DESC_GEN( false, &sphere_program,  sphere, sphere  ),
        SHADER_DESC_GEN( false, &bezier_program,  bezier, simple  ),
        SHADER_DESC_GEN( false, &point_program,   point,  simple  ),
        SHADER_DESC_GEN( false, &fractal_program, poly,   fractal ),
    };

    compile_shaders(LENOF(sdesc), sdesc);

    shader_init(&poly_shader, poly_program, NULL, NULL);


    // TODO: enable clockwise vertex order here or whatever
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    //glDisable(GL_CULL_FACE);
    //glDisable(GL_DEPTH_TEST);

    camera_init(&camera);
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





EM_BOOL frame_loop(double _t, void *user_data) {
    (void)user_data;

    double t;
    float dt;

    //////////////////////////
    //// UPDATE SCENE  //////
    ////////////////////////

    // update frame times
    update_frame_time(_t, &t, &dt);

    camera_update(&camera);
    camera_apply(&camera, poly_program);


    // update models
    /*if (count%UPDATE_DIVISOR == 0 && behave_flag)
        model_update_pipeline(t, dt);

    //////////////////////////
    //// DRAW SCENE  ////////
    ////////////////////////

    // clear the scene
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw models
    for (int i = 0; i < NUM_MODELS; i++)
        MODEL_draw(models+i);
        glUniformMatrix4fv(u_proj_mat_loc, 1, GL_FALSE, (GLfloat*)&u_proj_mat);
    }*/

    //draw_rectangle(WALL_THICK, WALL_LENGTH, 0, (vec2){0.5,0}, COLOR_RED, &poly_shader);

    maze_draw(&maze, t);

    // requests frame buffer swap. Will actually render stuff to screen
    // this is neccissary because explicitSwapControl was set to GL_TRUE
    emscripten_webgl_commit_frame();

    // return true to keep looping
    // return false to kill loop
    return EM_TRUE;
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




void init_scene(void) {
    // set background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    /*FRACTAL_init(&fractal, 
        (vec2[]){
            {wmin[0], wmin[1]},
            {wmax[0], wmax[1]},
        }, (vec3){0,0,0});*/

    maze_init(&maze, 10, 10, COLOR_WHITE, &poly_shader);
    maze.x = -CELL_SIZE*5;
    maze.y = -CELL_SIZE*5;
}







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
