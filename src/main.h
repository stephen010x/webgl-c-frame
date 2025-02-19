#ifndef MAIN_H
#define MAIN_H

#include <cglm/cglm.h>


// I just don't like this, so I pushed it into here.
typedef struct {
    int width;
    int height;
} FRAME;






#define FRAND() ((float)rand()/(float)RAND_MAX)

#define FRANDRANGE(__min, __max) MAP(FRAND(), 0, 1, __min, __max)




#define VEC3_RANDRANGE(__min, __max) (vec3){    \
        FRANDRANGE(__min, __max),               \
        FRANDRANGE(__min, __max),               \
        FRANDRANGE(__min, __max),               \
    }
    



#define CAMERA_NULL         0
#define CAMERA_ORTHOGRAPHIC 1
#define CAMERA_PERSPECTIVE  2


typedef struct {
    vec3 pos;
    vec3 rot; // rotated on x, y, z axes in that order around it's position, not origin
    float fov;
    //vec2 window[2];
    float ratio;
    int type;
    union {
        mat4 viewmat;
        GLfloat raw[16];
    };
} CAMERA;

extern CAMERA camera;



// TODO:
// Delete this header eventually. Main doesn't need a header.
// I just wanted to get these assert macros out of there to reduce
// clutter. Eventually move these to a macro header file



//#define ASSERT(__cond, __code, ...) _ASSERT(__cond, __code, __VA_ARGS__, "")

#if 0
#ifdef DEBUG_MODE
    #define ASSERT(__cond, __code, ...)     \
        do {                                \
            if (!(__cond)) {                \
                printf(__VA_ARGS__);        \
                IFTHENELSE(ISVOID(__code),  \
                    return; ,               \
                    return (__code);        \
                )                           \
            }                               \
        } while(0)
#else
    #define ASSERT(__cond, __code, ...)     \
        do {                                \
            if (!(__cond))                  \
                IFTHENELSE(ISVOID(__code),  \
                    return; ,               \
                    return (__code);        \
                )                           \
        } while(0)
#endif
#else
// use this until the macro library works
#ifdef DEBUG_MODE
    #define ASSERT(__cond, __code, ...) \
        do {                            \
            if (!(__cond)) {            \
                printf(__VA_ARGS__);    \
                return (__code);        \
            }                           \
        } while(0)
    #define ASSERTVOID(__cond, ...)     \
        do {                            \
            if (!(__cond)) {            \
                printf(__VA_ARGS__);    \
                return;                 \
            }                           \
        } while(0)
#else
    #define ASSERT(__cond, __code, ...) \
        do {                            \
            if (!(__cond))              \
                return (__code);        \
        } while(0)
    #define ASSERTVOID(__cond, ...)     \
        do {                            \
            if (!(__cond))              \
                return;                 \
        } while(0)
#endif
#endif


#define MAX(__a, __b) ({        \
        typeof(__a) a = (__a);  \
        typeof(__b) b = (__b);  \
        a > b ? a : b;          \
    })

#define MIN(__a, __b) ({        \
        typeof(__a) a = (__a);  \
        typeof(__b) b = (__b);  \
        a <= b ? a : b;         \
    })


//#define LENOF(__n) (sizeof(__n)/sizeof(*(__n)))
#define LENOF(__n) (sizeof(__n)/sizeof((__n)[0]))
#define MATH_PI 3.141592653589793238462643383
#define ABS(__n) ({typeof(__n) n = (__n); n >= 0 ? n : -n;})
#define SIGN(__n) ({typeof(__n) n = (__n); n == 0 ? 0 : (n > 0 ? 1 : -1);})

#define MAP(__n, __i1, __i2, __o1, __o2) ({ \
        typeof(__n)  n  = (__n );   \
        typeof(__i1) i1 = (__i1);   \
        typeof(__i2) i2 = (__i2);   \
        typeof(__o1) o1 = (__o1);   \
        typeof(__o2) o2 = (__o2);   \
        (n-i1)*(o2-o1)/(i2-i1)+o1;  \
    })



// TODO: Add a point light


typedef struct {
    vec3 norm;
    vec2 range;
} DIR_LIGHTSOURCE;

typedef struct {
    vec3 pos;
    vec2 range;
} POINT_LIGHTSOURCE;


typedef struct {
    int type;
    union {
        DIR_LIGHTSOURCE dir;
        POINT_LIGHTSOURCE point;
    };
} LIGHTSOURCE;


enum lightsource_type {
    LIGHTSOURCE_TYPE_NONE = 0,
    LIGHTSOURCE_TYPE_DIR,
    LIGHTSOURCE_TYPE_POINT,
    LIGHTSOURCE_TYPE_AMBIENT,
};


typedef struct {
    LIGHTSOURCE light;
} WORLD;

extern WORLD world;



extern vec3 wmin, wmax;






// Actually, lets just push some more junk code I don't want cluttering the
// main file into here that I am not yet willing to delete





    // TODO I don't really know where to go with this
    // I eventually want control over the screen buffer size/resolution
    //glViewport(0, 0, 256, 256);

    // set the uniform u_proj_mat
    /*for (int i = 0; i < LENOF(programs); i++){
        GLint u_proj_mat_loc = glGetUniformLocation(programs[i], "u_proj_mat");

        mat4 u_proj_mat;
        // TODO: Make this cooler. (ie. 0 to 256 rather than -1 to 1)
        //glm_ortho(wmin[0], wmax[0], wmin[1], wmax[1], -1, (1<<16)-1, u_proj_mat);
        //glm_ortho(wmin[0], wmax[0], wmin[1], wmax[1], wmin[2], wmax[2], u_proj_mat);
        glm_perspective(45*MATH_PI/180, ratio, -10, 0, u_proj_mat);
        glm_translate(u_proj_mat, (vec3){0,0,-4});

        glUniformMatrix4fv(u_proj_mat_loc, 1, GL_FALSE, (GLfloat*)&u_proj_mat);
    }*/



    


/*typedef struct {
    struct {
        int width;
        int height;
    } canvas;
    
} GL_INSTANCE;*/



/*
void init_scene(
    CIRCLE* circles, MESH* circle_mesh, GLuint shader_program , int screen_width, int screen_height) {

    for (int i = 0; i <= CIRC_RES; i++) {
        circle_mesh->verts[i+0] = 0;
        circle_mesh->verts[i+1] = 0;
        circle_mesh->verts[i+2] = (float)cos( (float)i * (2*MATH_PI/CIRC_RES) );
        circle_mesh->verts[i+3] = (float)sin( (float)i * (2*MATH_PI/CIRC_RES) );
    }
    
    for (int i = 0; i < NUM_CIRCLES; i++) {
        CIRCLE_init( CIRCLE_default(
            &circles[i],
            screen_width,
            screen_height,
            shader_program,
            circle_mesh
        ));
    }
}
*/



    // update the scene
    //for (int i = 0; i < NUM_CIRCLES; i++)
    //    CIRCLE_update(circles+i, (float)dt);

    //for (int i = 0; i < NUM_CIRCLES; i++)
    //    CIRCLE_draw(circles+i);

    //SIMPLET_draw(&simp);




/*int main() {
    printf("starting webgl\n");

    //\*debug*\/ printf("%p %lu %p %lu\n", &_circle_mesh, sizeof(_circle_mesh), &circle_mesh_struct._circle_mesh_verts, sizeof(circle_mesh_struct._circle_mesh_verts));

    /\*int retval;
    pthread_t thread;
    pthread_create(&thread, NULL, _main, NULL);
    //pthread_join(thread, (void**)&retval);
    return retval;*\/
    
    int retval = __main();
    printf("main exited with code (%d)\n", retval);

    // this is just a busyloop
    //emscripten_sleep(1000);

    // TODO: This function may work to replace emscripten FETCH
    // int emscripten_wget(const char *url, const char *file)
    
    return retval;
}*/




/*
void* _main(void* args) {
    printf("detatching main\n");
    int retval =__main();
    // TODO: this errors for some reason??? Fix this
    //printf("main exited with code (%d)\n", retval);
    return (void*)retval;
}
*/






#endif
