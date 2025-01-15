#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <math.h>
//#include <math.h>
#include <GLES2/gl2.h>
#include <emscripten.h>
#include <emscripten/html5.h>
#include <emscripten/fetch.h>
#include "circle.h"
//#include <stdbool.h>

#include "shaders/gen/shaders.h"


#define NUM_CIRCLES 2
#define CIRC_RES 32



//#define ASSERT(__cond, __code, ...) _ASSERT(__cond, __code, __VA_ARGS__, "")

#ifdef DEBUG_MODE
    #define ASSERT(__cond, __code, ...) do {    \
            if (!(__cond)) {                    \
                printf(__VA_ARGS__);            \
                return (__code);                \
            }                                   \
        } while(0);
#else
    #define ASSERT(__cond, __code, ...) \
        do {if (!(__cond)) return (__code);} while(0)
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

#define LENOF(__n) (sizeof(__n)/sizeof(*(__n)))
#define MATH_PI 3.141592653589793238462643383
#define ABS(__n) ({typeof(__n) n = (__n); n >= 0 ? n : -n;})
#define SIGN(__n) ({typeof(__n) n = (__n); n == 0 ? 0 : (n > 0 ? 1 : -1);})


enum {
    ERROR_NONE = 0,
    ERROR_CREATE_CONTEXT,
};


//typedef unsigned char bool;
#define TRUE 1
#define FALSE 0

    


int fetch_file(const char* url, char* data, uint64_t max, uint64_t* bytes);
GLuint init_webgl(const char* canvas_id);
static GLuint compile_shader(GLenum shader_type, const char* url);
static int link_program(GLuint program, const char* name);
void init_scene(CIRCLE* circles, MESH* circle_mesh, GLuint shader_program, int width, int height);
EM_BOOL frame_loop(double t, void *user_data);


/*typedef struct {
    struct {
        int width;
        int height;
    } canvas;
    
} GL_INSTANCE;*/

typedef struct {
    int width;
    int height;
} FRAME;




// some global variables

// declare our sole mesh
MESH circle_mesh = { .len = CIRC_RES*4 };
// allocate some space for our mesh vertices
volatile MESH_VERT _circle_mesh_verts[CIRC_RES*4];

// declare our circle array
CIRCLE circles[NUM_CIRCLES];


void* _main(void* args);
int __main(void);

int main() {
    printf("starting webgl\n");
    int retval;
    pthread_t thread;
    pthread_create(&thread, NULL, _main, NULL);
    //pthread_join(thread, (void**)&retval);
    return retval;
}


void* _main(void* args) {
    printf("detatching main\n");
    int retval =__main();
    // TODO: this errors for some reason??? Fix this
    //printf("main exited with code (%d)\n", retval);
    return (void*)retval;
}


int __main(void) {

    // set starting random seed
    srand((unsigned int)time(NULL));

    // remember, you wrote this function. Pass in canvas name, 
    // and returns shader programs
    // a bit counterintuitive, but you can fix this later
    GLuint program = init_webgl(".canvas");
    ASSERT(program, -1, "init_webgl failed\n");

    // TODO: good lord fix this
    emscripten_set_canvas_element_size("#canvas", 800, 600);

    //get canvas width and height
    FRAME canvas;
    EMSCRIPTEN_RESULT result = emscripten_get_canvas_element_size("#canvas", &canvas.width, &canvas.height);

    //*debug*/ printf("canvas %d %d %d %d\n", canvas.width, canvas.height, result, EMSCRIPTEN_RESULT_SUCCESS);
    
    // set the uniform u_proj_mat
    GLint u_proj_mat_loc = glGetUniformLocation(program, "u_proj_mat");
    //GLfloat aspect = (GLfloat)canvas.width / (GLfloat)canvas.height;
    // TODO: improve this projection matrix
    const GLfloat u_proj_mat[16] = {
            0.07500000298023224, 0,                    0, 0,
            0,                   0.10000000149011612,  0, 0,
            0,                   0,                   -1, 0,
            0,                   0,                    0, 1
        };
    glUniformMatrix4fv(u_proj_mat_loc, 16, GL_FALSE, u_proj_mat);


    /*
    Alright, I just wanted to demonstrate that there are three ways to
    allocate space for our mesh on the stack.

    --Method 1--
    
    MESH* circle_mesh = alloca(sizeof(MESH) + CIRC_RES*4);

    --Method 2--

    volatile char _reserved[sizeof(MESH) + CIRC_RES*4];
    MESH* circle_mesh = (MESH*)_reserved;

    --Method 3--
    
    MESH circle_mesh;
    volatile char _reserved[CIRC_RES*4];

    --NOTE--

    renaming _reserved to circle_mesh_verts would really twist some fingers
    */

    // init scene
    init_scene(circles, &circle_mesh, program, canvas.width, canvas.height);

    // set frame callback
    // a while loop would stall the webpage, so this is neccissary
    emscripten_request_animation_frame_loop(&frame_loop, NULL);

    return 0;
}


EM_BOOL frame_loop(double t, void *user_data) {
    (void)user_data;
    static double t0;
    double dt = t - t0;
    t0 = t;

    // clear the scene
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // update the scene
    for (int i = 0; i < NUM_CIRCLES; i++)
        CIRCLE_update(circles+i, (float)dt);

    for (int i = 0; i < NUM_CIRCLES; i++)
        CIRCLE_draw(circles+i);

     // return true to keep looping
     // return false to kill loop
    return EM_TRUE;
}


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


GLuint init_webgl(const char* canvas_id) {
    //static const char const* vs_path = "./src/shaders/default.vert";
    //static const char const* fs_path = "./src/shaders/default.frag"

    // webgl attribute structure
    EmscriptenWebGLContextAttributes gl_attrib;

    // populate webgl attributes with default and custom values
    emscripten_webgl_init_context_attributes(&gl_attrib);
    gl_attrib.alpha = GL_FALSE;
    gl_attrib.antialias = GL_FALSE;
    gl_attrib.powerPreference = EM_WEBGL_POWER_PREFERENCE_LOW_POWER;
    gl_attrib.majorVersion = 2; // might be less compatible with browsers
    gl_attrib.enableExtensionsByDefault = GL_TRUE; // consider setting to false
    gl_attrib.explicitSwapControl = GL_TRUE;
    gl_attrib.renderViaOffscreenBackBuffer = GL_TRUE;

    // create webgl context to canvas element using id
    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE gl_context = emscripten_webgl_create_context(
        canvas_id, &gl_attrib);
    ASSERT(gl_context, (GLuint)0, "ERROR: Failed to create webgl context\n");

    // activate webgl context
    ASSERT(emscripten_webgl_make_context_current(gl_context) == 
        EMSCRIPTEN_RESULT_SUCCESS, (GLuint)0,
        "ERROR: Failed to mamke webgl context current\n");

    // compile shaders
    GLuint vs = compile_shader(GL_VERTEX_SHADER, "/src/shaders/default.vert");
    // "https://raw.githubusercontent.com/stephen010x/webgl-c-frame/refs/heads/main/src/shaders/default.vert"
    ASSERT(vs, (GLuint)0, "vertex shader failed to compile\n");
    GLuint fs = compile_shader(GL_FRAGMENT_SHADER, "/src/shaders/default.frag");
    ASSERT(fs, (GLuint)0, "fragment shader failed to compilen\n");

    // create program object
    GLuint program = glCreateProgram();

    // attach shaders to program
    glAttachShader(program, vs);
    glAttachShader(program, fs);

    // set first index in a vertice to be called "pos"
    glBindAttribLocation(program, 0, "pos");

    // link the program
    ASSERT(!link_program(program, "default"), (GLuint)0, "");

    // install program as part of current rendering state
    glUseProgram(program);

    return program;
}



typedef struct {
    const char* url;
    char* data;
    uint64_t max;
    uint64_t* bytes;
} fetch_file_args;

void* fetch_sync(void* _args);


// this function is synchronous. It will block until it gets the data
// the bytes parameter is both input and output. As input it represents
// the max bytes, and as output it will be how many bytes were read.
// nevermind, an explicit extra member will be added for max
int fetch_file(const char* url, char* data, uint64_t max, uint64_t* bytes) {
    fetch_file_args args = {
        .url = url,
        .data = data,
        .max = max,
        .bytes = bytes
    };
    int retval;
    
    pthread_t thread;
    pthread_create(&thread, NULL, fetch_sync, &args);
    pthread_join(thread, (void**)&retval);

    return retval;
}


void* fetch_sync(void* _args) {
    fetch_file_args* args = (fetch_file_args*)_args;
    const char* url = args->url;
    char* data = args->data;
    uint64_t max = args->max;
    uint64_t* bytes = args->bytes;

    // fetch attributes
    emscripten_fetch_attr_t fetch_attrib;

    // populate fetch attributes with default and custom values
    emscripten_fetch_attr_init(&fetch_attrib);
    fetch_attrib.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY | 
                              EMSCRIPTEN_FETCH_SYNCHRONOUS; // |
                              //EMSCRIPTEN_FETCH_REPLACE;
    strcpy(fetch_attrib.requestMethod, "GET");

    // fetch file (blocking)
    emscripten_fetch_t *fetch = emscripten_fetch(&fetch_attrib, url);
    // the documentation on this is, like, nonexistant. So I have no idea why 
    // the success fetch status is 200. Maybe it is an http code.
    
    if (fetch->status == 200) {
        printf("Fetched \"%s\" (%llu)\n", fetch->url, fetch->numBytes);
        //*test*/ printf("%s\n", (char*)fetch->data);
    } else {
        printf("Fetch \"%s\" FAILED! (HTTP status code: %d)\n", 
            fetch->url, fetch->status);
        //*test*/ printf("%s\n", (char*)fetch->data);
        emscripten_fetch_close(fetch);
        return (void*)-1;
    }

    // copy data to data buffer
    memcpy(data, fetch->data, (uint32_t)MIN(max, fetch->numBytes));

    // set output of total length of file
    if (bytes != NULL)
        *bytes = fetch->numBytes;

    // free fetch object
    emscripten_fetch_close(fetch);

    return (void*)0;
}


static GLuint compile_shader(GLenum shader_type, const char* url) {
    // load shader
    // make sure everything is zeroed out so that the
    // string terminator is there by default
    char src[1024] = {0};
    uint64_t len = sizeof(src);
    ASSERT(fetch_file(url, src, len-1, &len) == 0, 0, "fetch_file failed\n");
    ASSERT(len < sizeof(src), 0, 
        "ERROR: Loaded shader file exceeded buffer length \"%s\"\n", url);

    // create shader object (only returns handle)
    GLuint shader = glCreateShader(shader_type);

    char* _src = src;

    // set the shader source to a single shader that is null terminated
    // I am not sure what is going on with the const typecast warning here
    // I assumed that the const param only affects the callee
    // this is confirmed working by using glShaderGetSource
    // what the heck???
    // For some reason this function spectacularly fails when I try to 
    // pass our src as the pointer to a static array casted to a a const GLchar**
    // and yet using a pointer that points to our static array works.
    // turns out static arrays when referencing will just decay into a pointer
    // without referencing
    glShaderSource(shader, 1, (const GLchar**)&_src, NULL);

    printf("Compiling shader \"%s\"\n", url);

    // compile the shader
    glCompileShader(shader);
    //GLenum err = glGetError();

    // print out compiler errors if any
    {
        GLint err, len;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &err);
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
        if (err == GL_FALSE) {
            char log[len];
            glGetShaderInfoLog(shader, len, NULL, log);
            //printf("SHADER COMPILER ERROR\n--------------------\n");
            printf("SHADER COMPILER ERROR:\n");
            printf(log);
            return 0;
        }
    }

    // returns shader handler
    return shader;
}


static int link_program(GLuint program, const char* name) {
    printf("Linking program \"%s\"\n", name);

    // link program
    glLinkProgram(program);

    // print out linker errors if any
    GLint err, len;
    glGetProgramiv(program, GL_LINK_STATUS, &err);
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);
    if (err == GL_FALSE) {
        char log[len];
        glGetProgramInfoLog(program, len, NULL, log);
        printf(log);
        return -1;
    }

    return 0;
}
