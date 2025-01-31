#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <math.h>
#include <GLES2/gl2.h>
#include <emscripten.h>
#include <emscripten/html5.h>
//#include <emscripten/fetch.h>
#include <cglm/cglm.h>
#include "main.h"
#include "model.h"
#include "webgl.h"
//#include "gobjects.h"
#include "shaders/gen/shaders.h"
//#include "macros/macros.h"


#define NUM_MODELS 10
#define CIRC_RES 32


enum {
    ERROR_NONE = 0,
    ERROR_CREATE_CONTEXT,
};


//typedef unsigned char bool;
#define TRUE 1
#define FALSE 0



void init_scene(GLuint shader_program);
EM_BOOL frame_loop(double t, void *user_data);
int __main(void);
bool keydown_event_handler(int etype, const EmscriptenKeyboardEvent* event, void* params);
bool touch_event_handler(int etype, const EmscriptenTouchEvent* event, void* params);


// TODO:
// I'm realizing if two models are using the same mesh, they
// should reference the opengl context for it rather than make a new
// one. In other words, the mesh should create a buffer, not the model
MESH(6) triangle_mesh = {
    .verts = 3,
    .mode = GL_TRIANGLES,
    .data = {
        0.0,  0.5,
       -0.5, -0.5,
        0.5, -0.5,
    }
};

MESH(CIRC_RES*2) circle_mesh = {
    .verts = CIRC_RES,
    .mode = GL_TRIANGLE_FAN,
    .data = {0}
};


MODEL models[NUM_MODELS];





int main() {
    printf("starting webgl\n");

    int retval = __main();
    printf("main exited with code (%d)\n", retval);

    return retval;
}



const vec3 gravity0 = {0, -0.001, 0};
vec3 gravity = {0, -0.001, 0};
//vec3 gravity = {0, 0, 0};




int __main(void) {

    // set starting random seed
    srand((unsigned int)time(NULL));

    // remember, you wrote this function. Pass in canvas name, 
    // and returns shader programs
    // a bit counterintuitive, but you can fix this later
    int err = init_webgl("#canvas");
    ASSERT(err == 0, -1, "init_webgl failed\n");

    GLuint program = shader_program(
        "program", "model.vert", model_vert, "model.frag", model_frag);

    // TODO: good lord fix this
    //emscripten_set_canvas_element_size("#canvas", 256, 256);

    //get canvas width and height
    //FRAME canvas;
    //EMSCRIPTEN_RESULT result = emscripten_get_canvas_element_size("#canvas", &canvas.width, &canvas.height);

    // TODO I don't really know where to go with this
    // I eventually want control over the screen buffer size/resolution
    //glViewport(0, 0, 256, 256);

    // set the uniform u_proj_mat
    GLint u_proj_mat_loc = glGetUniformLocation(program, "u_proj_mat");

    mat4 u_proj_mat;
    // TODO: Make this cooler. (ie. 0 to 256 rather than -1 to 1)
    glm_ortho(-1, 1, -1, 1, 0, (1<<16)-1, u_proj_mat);

    glUniformMatrix4fv(u_proj_mat_loc, 1, GL_FALSE, (GLfloat*)&u_proj_mat);

    emscripten_set_keydown_callback(
        EMSCRIPTEN_EVENT_TARGET_WINDOW, NULL, EM_FALSE, &keydown_event_handler);

    // for the mobiley gifted
    emscripten_set_touchstart_callback(
        EMSCRIPTEN_EVENT_TARGET_WINDOW, NULL, EM_FALSE, &touch_event_handler);

    // init scene
    init_scene(program);

    // set frame callback
    // a while loop would stall the webpage, so this is neccissary
    printf("starting animation frame loop\n");
    emscripten_request_animation_frame_loop(&frame_loop, NULL);

    return 0;
}





#define UPDATE_DIVISOR 1

// T/ODO: WTF IS THERE A MEMORY LEAK????
// this is getting overridden by something to 1065353216
// turns out 1065353216 is the integer representation of 1.0f
// enable and disable certain functions to find out what is 
// causing this!!!
// FIS THIX!!!!!
// AHAH! I FOUND IT!
// The circle mesh generator in init_scene overflows
bool behave_flag = false;


EM_BOOL frame_loop(double t, void *user_data) {
    (void)user_data;
    static double t0;
    double dt = t - t0;
    t0 = t;

    static unsigned long long count = 0;
    // update count for physics update slowing
    count++;
    
    //*DEBUG*/ printf("%d\n", behave_flag);

    // clear the scene
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (count%UPDATE_DIVISOR == 0 && behave_flag)
        for (int i = 0; i < NUM_MODELS; i++)
            MODEL_update(models+i, dt);
        
    for (int i = 0; i < NUM_MODELS; i++)
        MODEL_draw(models+i);

    // rotate gravity
    // mainly for debugging purposes
    // but it also looks cool
    glm_vec3_copy(*(vec3*)&gravity0, gravity);
    glm_vec3_rotate(gravity, t/3000, (vec3){0,0,1});

    // requests frame buffer swap. Will actually render stuff to screen
    // this is neccissary because explicitSwapControl was set to GL_TRUE
    emscripten_webgl_commit_frame();

    // return true to keep looping
    // return false to kill loop
    return EM_TRUE;
}





void tri_update(MODEL* model, float dt);



#define FRAND() ((float)rand()/(float)RAND_MAX)


typedef struct {
    vec3 vel;
    float scale;
} BEHAVE_DATA;


BEHAVE_DATA behave[NUM_MODELS];



void init_scene(GLuint program) {
    // set background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    //*DEBUG*/ extern int behave_flag;
    //*DEBUG*/ behave_flag = 1002;

    // generate circle mesh
    for (int i = 0; i < CIRC_RES; i++) {
        circle_mesh.data[i*2+0] = (float)cos( (float)i * (2*MATH_PI/CIRC_RES) );
        circle_mesh.data[i*2+1] = (float)sin( (float)i * (2*MATH_PI/CIRC_RES) );
    }

    
    // create model
    for (int i = 0; i < NUM_MODELS; i++) {
        models[i] = (MODEL){
            .color = {
                .r = FRAND(),
                .g = FRAND(),
                .b = FRAND(),
                .w = 1.0
            },
            .id = i,
            .mesh = (MESH*)&circle_mesh,
            .visable = true,
            .drawtype = 0, // not implemented yet
            .update_call = (UPDATE_CALLBACK)tri_update,
            .shader_prog = program,
            .view_mat = GLM_MAT4_IDENTITY_INIT,
        };

        behave[i] = (BEHAVE_DATA){
            .vel = {
                (FRAND()*2-1)/10,
                (FRAND()*2-1)/10,
                0,
            },
            .scale = (FRAND()*0.9 + 0.1)/4,
        };

        vec3 init_pos = {
            (FRAND()-0.5),
            (FRAND()-0.5),
            0,
        };

        // stupid scaling vs position stuff with matrix
        //glm_vec3_scale(behave[i].vel, 1/behave[i].scale, behave[i].vel);

        glm_vec3_scale(init_pos, 1/behave[i].scale, init_pos);
        glm_scale_uni(models[i].view_mat, behave[i].scale);
        glm_translate(models[i].view_mat, init_pos);

        MODEL_init(models+i);
    }

}



// TODO: I think air drag might be messing up perfectly inelastic collisions
#define DRAG_COEFF 0.2
//#define DRAG_COEFF 0
#define DENSITY 1
#define ELASTICITY 0.5
//#define ELASTICITY 0
//#define ELASTICITY 1
#define BOUNCE_THRESH 0.01

// TODO: get rid of bool debug parameter
void collision(float coeff, vec3 v1, vec3 v2, float m1, float m2, vec3 n1x, vec3 n2x, vec3 v1o, vec3 v2o, bool debug);
void collision_adjust(vec3 norm, float m1, float m2, float overlap, vec3 p1o, vec3 p2o);
void wall_collide(MODEL* model, vec3 norm, float overlap);
bool sphere_collide_test(MODEL* model1, MODEL* model2);


void tri_update(MODEL* model, float dt) {
    // adjusting dt so as to not have speeds be haywire
    dt = dt / 8;

    //*DEBUG*/ behave[0].vel[0] = 0;
    //*DEBUG*/ behave[0].vel[1] = 0;
    
    int id = model->id;

    // copy view matrix
    //mat4 mat;
    //glm_mat4_copy(model->view_mat, mat);

    // TODO: there has got to be a better way to 
    // extract these positions from this matrix
    // at the very least create a helper function for this
    vec3 pos = {
        model->view_mat[3][0],
        model->view_mat[3][1],
        0,
    };

    // apply gravity
    glm_vec3_add(behave[id].vel, gravity, behave[id].vel);

    //*DEBUG*/ printf("pos %f, %f\n", pos[0], pos[1]);

    float x = pos[0];
    float y = pos[1];
    float rad = behave[id].scale;
    float mass = (4/3)*MATH_PI*rad*rad*rad*DENSITY;

    // TODO:
    // for the physics part, have each boundry create a collision vector
    // that represents the position of where the collision happens
    // so that the hard stuff can be easily incorperated with the circle-to-circle
    // collision
    // TODO:
    // also it is probably worth looking into doing shader based collisions.



    // test wall collisions
    if (x + rad >  1) wall_collide(model, (vec3){-1, 0, 0},  x+rad-1);
    if (x - rad < -1) wall_collide(model, (vec3){ 1, 0, 0}, -x+rad-1);
    if (y + rad >  1) wall_collide(model, (vec3){ 0,-1, 0},  y+rad-1);
    if (y - rad < -1) wall_collide(model, (vec3){ 0, 1, 0}, -y+rad-1);

    // test circle collisions for every other circle with a greater id
    for (int i = id+1; i < NUM_MODELS; i++)
        //if (i != id)
            sphere_collide_test(model, models+i);
    

    // TODO: consider reference to vel rather than copy
    vec3 vel;
    glm_vec3_copy(behave[id].vel, vel);


    //glm_vec3_copy(behave[id].vel, vel);

    // friction multiplier coefficient for velocity
    // formula for sphere used, for future compatability
    float vel_abs = glm_vec3_norm(vel);
    float frict_mult = 1 - DRAG_COEFF*vel_abs*rad*rad*dt/mass;
    // turns out 
    if (frict_mult < 0.9) frict_mult = 0.9;
    glm_vec3_scale(vel, frict_mult, vel);

    // update velocities to new values
    behave[id].vel[0] = vel[0];
    behave[id].vel[1] = vel[1];
    behave[id].vel[2] = vel[2];
    
    // translate model
    // TODO: I feel like position might need to be adjusted too?
    //       Then again maybe not because the wall collision is sound
    glm_vec3_scale(vel, 1/rad*dt, vel);
    glm_translate(model->view_mat, vel);

}




void wall_collide(MODEL* model, vec3 norm, float overlap) {

    // garbage collecting vector
    vec3 garbage;

    // get id
    int id = model->id;

    // TODO: consider reference to vel rather than copy
    // get velocity
    vec3 vel;
    glm_vec3_copy(behave[id].vel, vel);

    // get radius
    float rad = behave[id].scale;
    
    // get mass
    float mass = (4/3)*MATH_PI*rad*rad*rad*DENSITY;

    // calculate collision
    // old mass was 1e25
    collision(ELASTICITY, vel, (vec3){0,0,0}, mass, INFINITY, norm, norm, vel, garbage, false);

    //*debug*/ printf("before: (%f, %f)\n", behave[id].vel[0], behave[id].vel[1]);
    //*debug*/ printf("new: (%f, %f)\n", vel[0], vel[1]);

    // update velocity
    glm_vec3_copy(vel, behave[id].vel);

    //*debug*/ printf("after: (%f, %f)\n", behave[id].vel[0], behave[id].vel[1]);

    // absolute position collision adjustment
    vec3 off;
    collision_adjust(norm, mass, INFINITY, overlap, off, garbage);
    // stupid scaling neccissary for translation
    glm_vec3_scale(off, 1/rad, off);
    glm_translate(model->view_mat, off);
}


bool sphere_collide_test(MODEL* model1, MODEL* model2) {
    // get id
    int id1 = model1->id;
    int id2 = model2->id;
        
    // TODO: seriously, create a helper function for this
    // extract position vectors
    vec3 pos1 = {
        model1->view_mat[3][0],
        model1->view_mat[3][1],
        0,
    };
    vec3 pos2 = {
        model2->view_mat[3][0],
        model2->view_mat[3][1],
        0,
    };

    // calculate radius for each
    float rad1 = behave[id1].scale;
    float rad2 = behave[id2].scale;

    // calculate distance between two vectors
    float dist = glm_vec3_distance(pos1, pos2);

    // detect if collision happens. If not, then return
    if (dist > rad1+rad2)
        return false;

    //*DEBUG*/ behave_flag = false;

    //printf("-----------------------------\n");
    //printf("collision %d with %d\n", id1, id2);
    //printf("pos %d  %f, %f\n", id1, pos1[0], pos1[1]);
    //printf("pos %d  %f, %f\n", id2, pos2[0], pos2[1]);

    // get velocities
    vec3 vel1, vel2;
    glm_vec3_copy(behave[id1].vel, vel1);
    glm_vec3_copy(behave[id2].vel, vel2);

    // get masses
    float mass1 = (4/3)*MATH_PI*rad1*rad1*rad1*DENSITY;
    float mass2 = (4/3)*MATH_PI*rad2*rad2*rad2*DENSITY;

    // get normal and anti-normal vector
    vec3 norm, anorm;
    // hopefully this does what I want
    // no. No it doesn't
    //glm_vec3_lerp(pos1, pos2, 1.0, norm);
    // turns out you can just do this with subtraction
    glm_vec3_sub(pos1, pos2, norm);
    glm_vec3_negate_to(norm, anorm);

    // calculate collision
    vec3 vel1o, vel2o;
    collision(ELASTICITY, vel1, vel2, mass1, mass2, anorm, norm, vel1o, vel2o, true);

    // update velocities
    glm_vec3_copy(vel1o, behave[id1].vel);
    glm_vec3_copy(vel2o, behave[id2].vel);


    // absolute position collision adjustment
    /*vec3 off1, off2;
    float overlap = glm_vec3_distance(pos1, pos2) - rad1 - rad2;
    collision_adjust(anorm, mass1, mass2, overlap, off1, off2);
    // stupid scaling neccissary for translation
    glm_vec3_scale(off1, 1/rad1, off1);
    glm_vec3_scale(off2, 1/rad2, off2);
    glm_translate(model1->view_mat, off1);
    glm_translate(model2->view_mat, off2);*/

    return true;
}




// the normal doesn't have to be a unit vector. I will adjust it so 
// that it is treated like a unit vector a normal
// Notice that this is designed for 3D collisions. This is me thinking ahead.
// It will also work for 2D collisions too. The vector math is the exact same.
// also, yes, it is safe to pass in the same vector for the input and output velocity
void collision(float coeff, vec3 v1, vec3 v2, float m1, float m2, vec3 n1x, vec3 n2x, vec3 v1o, vec3 v2o, bool debug) {
    /*
     *  Alright, so this is 2 collisions, so this is how this needs to work:
     *  First, we need to extract the velicity relative to each normal.
     *  Which should be a simple cross product. This will get us our usable
     *  scalar velocity. And I think we will need to subtrac the original velocity
     *  output from that, and then add it back in with the adjusted velocity
     *  on that axis. (just do a subtraction and make the output the output vector)
     *  And of course, the adjusted velocity scalar will be multiplied to the 
     *  normal scalar and then added back into the output
     */

    /* for bounce threshold to stabilize the system under constant accelaration,
     * Just take the absolute value of the relative speed between the two
     * and if it falls below the treshold, then make the collision perfectly 
     * inelastic.
     * We do have to worry about adjusting position. And the best way to do that
     * is to adjust position according to center of mass. Lets try to go for a
     * separate function for this, which is effectively instead of a velocity 
     * collider function, is instead a spacial and positional collider function.
     */

    // TODO: add dt in this calculation so that the bounce threshold is reduced
    // at higher framerates
    // TODO: another idea is to have elasticity decrease at lower speeds
    // if relative speed between two objects less than bounce threshold,
    // then make collision perfectly inelastic
    vec3 sum;
    glm_vec3_add(v1, v2, sum);
    float rs = glm_vec3_norm(sum);
    if (rs < BOUNCE_THRESH)
        coeff = 0;
    //printf("%f, %f\n", rs, coeff);

    //*DEBUG*/ if (debug) printf("vel1 %f, %f\n", v1[0], v1[1]);
    //*DEBUG*/ if (debug) printf("vel2 %f, %f\n", v2[0], v2[1]);

    // enforce normals to be unit vectorrs
    vec3 n1, n2;
    glm_vec3_normalize_to(n1x, n1);
    glm_vec3_normalize_to(n2x, n2);

    // perform dot product
    float dot1 = glm_vec3_dot(v1, n1);
    float dot2 = glm_vec3_dot(v2, n2);
    
    // calculate velocities parallel to normal 
    vec3 v1n, v2n;
    glm_vec3_scale(n1, dot1, v1n);
    glm_vec3_scale(n2, dot2, v2n);

    //*DEBUG*/ if (debug) printf("normal 1 %f, %f\n", n1[0], n1[1]);
    //*DEBUG*/ if (debug) printf("normal 2 %f, %f\n", n2[0], n2[1]);

    //*DEBUG*/ if (debug) printf("mass1 %f, mass2 %f\n", m1, m2);
    
    // subtract normal velocity from original velocity, and place in output
    // we add in the *adjusted* normal velocity back in later
    glm_vec3_sub(v1, v1n, v1o);
    glm_vec3_sub(v2, v2n, v2o);

    // get magnitudes of NORMAL velocities for collision formula
    float v1s = glm_vec3_norm(v1n);
    float v2s = glm_vec3_norm(v2n);

    //*DEBUG*/ printf("test %f, %f\n", v1s, v2s);

    // calculate magnitudes of new velocity
    // TODO DOES THIS NEED TO BE NEGATIVE???
    // https://en.wikipedia.org/wiki/Inelastic_collision
    float v1x, v2x;
    if (m2 == INFINITY) {
        v1x = -(coeff*(v2s-v1s) + v2s);
        v2x = -v2s; // probably adjust back to positive due to how I handle normals
    } else {
        v1x = -(coeff*m2*(v2s-v1s) + m1*v1s + m2*v2s) / (m1+m2);
        v2x = -(coeff*m1*(v1s-v2s) + m2*v2s + m1*v1s) / (m1+m2);
    }

    //*DEBUG*/ printf("mags %f, %f\n", v1x, v2x);

    //*DEBUG*/ if (debug) printf("math1 (%f, %f) * %f = (%f, %f)\n", n1[0], n1[1], v1x, v1n[0], v1n[1]);
    //*DEBUG*/ if (debug) printf("math2 (%f, %f) * %f = (%f, %f)\n", n2[0], n2[1], v2x, v2n[0], v1n[1]);

    // create normal velocity vector with new scalar values
    glm_vec3_scale(n1, v1x, v1n);
    glm_vec3_scale(n2, v2x, v2n);

    //*DEBUG*/ if (debug) printf("addon1 %f, %f\n", v1n[0], v1n[1]);
    //*DEBUG*/ if (debug) printf("addon2 %f, %f\n", v2n[0], v2n[1]);

    // add our adjusted velocity normals back into the output velocity
    glm_vec3_add(v1o, v1n, v1o);
    glm_vec3_add(v2o, v2n, v2o);
}



// sort of a different version of collisions that enforces objective
// reality on the spheres by adjusting their positions while maintaining 
// center of mass between two objects
// I am assuming just one normal this time, as I probably should be with
// the previous collision function too, as the force will always be in equal
// and opposite directions
// TODO: consider putting the collision functions in a separate file
void collision_adjust(vec3 norm, float m1, float m2, float overlap, vec3 p1o, vec3 p2o) {
    // calculate anti-normal
    // just use negative for final scale
    //vec3 anorm;
    //glm_vec3_negate_to(norm, anorm);

    float r1, r2;

    if (m2 == INFINITY) {
        r1 = overlap;
        r2 = 0;
    } else {
        r1 = m2*overlap/(m2-m1);
        r2 = m1*overlap/(m1-m2);
    }

    // scale_as converts it to normal vector for me
    // TODO apply scale_as to other collision function
    glm_vec3_scale_as(norm, r1, p1o);
    glm_vec3_scale_as(norm, -r2, p2o);
}






bool keydown_event_handler(int etype, const EmscriptenKeyboardEvent* event, void* params) {
    printf("pressed key %d\n", event->keyCode);
    switch (event->keyCode) {
        case 32:
            behave_flag = !behave_flag;
            return true;
        case 78:
        case 68:
            for (int i = 0; i < NUM_MODELS; i++)
                MODEL_update(models+i, 10);
            return true;
    }
    /*DEBUG*\/ { // norm test
        vec3 norm;
        vec3 pos1 = {0, 1, 0};
        vec3 pos2 = {2, 8, 0};
        glm_vec3_lerp(pos1, pos2, 1.0, norm);
        printf("//////////////////\n");
        printf("/// Norm pos1: %f, %f\n", pos1[0], pos1[1]);
        printf("/// Norm pos2: %f, %f\n", pos2[0], pos2[1]);
        printf("/// Norm lerp: %f, %f\n", norm[0], norm[1]);
    }//*/
    return false;
}


bool touch_event_handler(int etype, const EmscriptenTouchEvent* event, void* params) {
    behave_flag = !behave_flag;
    return true;
}
