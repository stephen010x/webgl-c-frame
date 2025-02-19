#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <math.h>
#include <GLES2/gl2.h>
#include <emscripten.h>
#include <emscripten/html5.h>

#include "main.h"
#include "model.h"
#include "webgl.h"
#include "input.h"
#include "bezier.h"
#include "shaders/gen/shaders.h"


#define MAX_CURVES 5


BEZIER curves[MAX_CURVES];


enum {
    ERROR_NONE = 0,
    ERROR_CREATE_CONTEXT,
};


//typedef unsigned char bool;
#define TRUE 1
#define FALSE 0


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
    .pos = {0,0,-3},
    .rot = {0,0,0},
    .fov = MATH_PI/4,
    .type = CAMERA_PERSPECTIVE,
};


MOUSE mouse;





void init_scene(void);
EM_BOOL frame_loop(double t, void *user_data);
int __main(void);





EMSCRIPTEN_KEEPALIVE int main() {
    printf("starting webgl\n");

    int retval = __main();
    printf("main exited with code (%d)\n", retval);

    return retval;
}




void get_elementid_size(char* id, int* width, int* height) {
    *width = EM_ASM_INT({
        let idstr = UTF8ToString($0);
        let element = document.getElementById(idstr);
        return element.width;
    }, id);
    *height = EM_ASM_INT({
        let idstr = UTF8ToString($0);
        let element = document.getElementById(idstr);
        return element.height;
    }, id);
}



int swidth, sheight;
vec3 wmin, wmax;


void controls(double t, float dt);
void update_camera(void);


//GLuint poly_program;
//GLuint sphere_program;
GLuint bezier_program;
GLuint point_program;


int __main(void) {


    // set starting random seed
    srand((unsigned int)time(NULL));

    // remember, you wrote this function. Pass in canvas name, 
    // and returns shader programs
    // a bit counterintuitive, but you can fix this later
    int err = init_webgl("#canvas");
    ASSERT(err == 0, -1, "init_webgl failed\n");

    /*poly_program = shader_program(
        "poly_program", "poly.vert", poly_vert, "poly.frag", poly_frag);
    sphere_program = shader_program(
        "sphere_program", "sphere.vert", sphere_vert, "sphere.frag", sphere_frag);*/
    bezier_program = shader_program(
        "bezier_program", "bezier.vert", bezier_vert, "simple.frag", simple_frag);
    point_program = shader_program(
        "point_program", "point.vert", point_vert, "simple.frag", simple_frag);

    //GLuint programs[] = {poly_program, sphere_program, bezier_program};

    // TODO: use this to set canvas size instead of javascript
    //emscripten_set_canvas_element_size("#canvas", 256, 256);

    //get canvas width and height
    // well for some reason this errors now.
    //int width, height;
    //EMSCRIPTEN_RESULT result = emscripten_get_canvas_element_size("#canvas", &width, &height);

    get_elementid_size("canvas", &swidth, &sheight);

    float ratio = (float)swidth/sheight;

    // TODO: add this to a camera init function or something
    if (ratio > 1) {
        wmin[0] = -1*ratio;
        wmax[0] =  1*ratio;
        wmin[1] = -1;
        wmax[1] =  1;
    } else {
        wmin[0] = -1;
        wmax[0] =  1;
        wmin[1] = -1/ratio;
        wmax[1] =  1/ratio;
    }
    wmin[2] = 0.1;
    wmax[2] = 1000.0;

    camera.ratio = ratio;
    //glm_vec3_copy((vec3){0,0,-1}, camera.pos);

    input_init();
    

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    glDepthFunc(GL_LESS);

    //glDisable(GL_CULL_FACE);
    //glDisable(GL_DEPTH_TEST);

    // init scene
    init_scene();

    // set frame callback
    // a while loop would stall the webpage, so this is neccissary
    printf("starting animation frame loop\n");
    emscripten_request_animation_frame_loop(&frame_loop, NULL);

    return 0;
}




#define DT_DIVISOR 100



//BEHAVE behave[NUM_MODELS];

void model_transform(MODEL* model);
void model_update_pipeline(double t, float dt);


#define UPDATE_DIVISOR 1



EM_BOOL frame_loop(double _t, void *user_data) {
    (void)user_data;
    static double t0;
    double _dt = _t - t0;
    t0 = _t;
    float dt = _dt/DT_DIVISOR;
    double t = _t/DT_DIVISOR;

    static unsigned long long count = 0;
    // update count for physics update slowing
    count++;
    
    //*DEBUG*/ printf("%d\n", behave_flag);

    // clear the scene
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // update models
    /*if (count%UPDATE_DIVISOR == 0 && behave_flag)
        model_update_pipeline(t, dt);

    // draw models
    for (int i = 0; i < NUM_MODELS; i++)
        MODEL_draw(models+i);*/

    controls(t, dt);

    //camera.rot[1] += 0.001;
    //camera.pos[2] -= 0.01;

    update_camera();
    
    GLint u_proj_mat_loc;


    glUseProgram(bezier_program);
    u_proj_mat_loc = glGetUniformLocation(bezier_program, "u_proj_mat");
    glUniformMatrix4fv(u_proj_mat_loc, 1, GL_FALSE, camera.raw);

    glUseProgram(point_program);
    u_proj_mat_loc = glGetUniformLocation(point_program, "u_proj_mat");
    glUniformMatrix4fv(u_proj_mat_loc, 1, GL_FALSE, camera.raw);

    for (int i = 0; i < MAX_CURVES; i++) {
        BEZIER_update(curves+i, t, dt);
        BEZIER_draw(curves+i, t);
    }




    // requests frame buffer swap. Will actually render stuff to screen
    // this is neccissary because explicitSwapControl was set to GL_TRUE
    emscripten_webgl_commit_frame();

    // reset mouse dx and dy for the frame
    // likely not neccissary unless mouse move calls are done
    // more than once per frame
    mouse.dx = 0;
    mouse.dy = 0;

    // return true to keep looping
    // return false to kill loop
    return EM_TRUE;
}



void controls(double t, float dt) {
    if (mouse.button[0]) {
        camera.rot[1] += (float)mouse.dx/100;
        camera.rot[0] += (float)mouse.dy/100;
    }
    const register float k = MATH_PI*3.0/8.0;
    if (camera.rot[0] > k)
        camera.rot[0] = k;
    if (camera.rot[0] < -k)
        camera.rot[0] = -k;

    //printf("mouse pos %d, %d\n", mouse.x, mouse.y);
    //printf("mouse dif %d, %d\n", mouse.dx, mouse.dy);
    //printf("mouse but %d, %d, %d\n", mouse.button[0], mouse.button[1], mouse.button[2]);
}




void init_scene(void) {
    // set background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    for (int i = 0; i < MAX_CURVES; i++)
        BEZIER_init(curves+i, (vec3[4]){
            {FRANDRANGE(-1, 1), FRANDRANGE(-1, 1), FRANDRANGE(-1, 1)},
            {FRANDRANGE(-1, 1), FRANDRANGE(-1, 1), FRANDRANGE(-1, 1)},
            {FRANDRANGE(-1, 1), FRANDRANGE(-1, 1), FRANDRANGE(-1, 1)},
            {FRANDRANGE(-1, 1), FRANDRANGE(-1, 1), FRANDRANGE(-1, 1)},
        }, 0);
}



void update_camera(void) {
    switch (camera.type) {
        case CAMERA_ORTHOGRAPHIC:
            glm_ortho_aabb((vec3[]){
                {wmin[0], wmin[1], wmin[2]}, 
                {wmax[0], wmax[1], wmin[2]},
            }, camera.viewmat);
            break;
        case CAMERA_PERSPECTIVE:
            glm_perspective(camera.fov, camera.ratio, 0.1, 100.0, camera.viewmat);
            break;
    }

    // translate first so that it rotates about the origin
    glm_translate(camera.viewmat, camera.pos);

    // rotate second, x, y, z axes in order
    glm_rotate_x(camera.viewmat, camera.rot[0], camera.viewmat);
    glm_rotate_y(camera.viewmat, camera.rot[1], camera.viewmat);
    glm_rotate_z(camera.viewmat, camera.rot[2], camera.viewmat);

    //printf("cam rot %f, %f, %f\n", camera.rot[0], camera.rot[1], camera.rot[2]);
}





/*
void model_transform(MODEL* model) {
    BEHAVE* b = behave + model->id;

    // apply transformations to matrix
    // TODO: Why do I have to scale the position? I am scaling it first!!!
    vec3 pos;
    glm_vec3_scale(b->pos, 1/b->scale, pos);
    mat4 viewmat = GLM_MAT4_IDENTITY_INIT;
    glm_scale_uni(viewmat, b->scale);
    glm_translate_to(viewmat, pos, model->view_mat);
}
*/
