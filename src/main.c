#include <stdio.h>
//#include <math.h>
#include <GLES2/gl2.h>
#include <emscripten.h>
#include <emscripten/html5.h>
//#include <stdbool.h>



//#define ASSERT(__cond, __code, ...) _ASSERT(__cond, __code, __VA_ARGS__, "")

#ifdef DEBUG_MODE
    #define ASSERT(__cond, __code, ...) do {    \
            if (!(__cond)) {                    \
                printf( __VA_ARGS__);           \
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


enum {
    ERROR_NONE = 0,
    ERROR_CREATE_CONTEXT,
};


typedef unsigned char bool;
#define TRUE 1
#define FALSE 0


int fetch_file(const char* url, char* data, int max, int* bytes);

GLuint init_webgl();
static GLuint compile_shader(GLenum shader_type, const char* url)
static int link_program(GLuint program);


/*typedef struct {
    struct {
        int width;
        int height;
    } canvas;
    
} GL_INSTANCE;*/

typedef struct {
    int width;
    int height;
} POINT;


int main() {
    printf("starting webgl\n");

    GLuint program = init_webgl("canvas");

    //get canvas width and height
    POINT canvas;
    emscripten_get_canvas_element_size("#canvas", &canvas.width, &canvas.height);
    
    // set the uniform u_proj_mat
    GLint u_proj_mat_loc = glGetUniformLocation(program, "u_proj_mat");
    GLfloat aspect = (GLfloat)canvas.width / (GLfloat)canvas.height;
    proj_mat

    return 0;
}


GLuint init_webgl(const char* canvas_id) {
    //static const char const* vs_path = "./src/shaders/default.vert";
    //static const char const* fs_path = "./src/shaders/default.frag"

    // webgl attribute structure
    EmscriptenWebGLContextAttributes gl_attrib;

    // populate webgl attributes with default and custom values
    emscripten_webgl_init_context_attributes(&gl_attrib);
    gl_attrib.alpha = FALSE;
    gl_attrib.antialias = FALSE;
    gl_attrib.powerPreference = EM_WEBGL_POWER_PREFERENCE_LOW_POWER;
    gl_attrib.majorVersion = 2; // might be less compatible with browsers
    gl_attrib.enableExtensionsByDefault = TRUE; // consider setting to false
    gl_attrib.explicitSwapControl = TRUE;
    gl_attrib.renderViaOffscreenBackBuffer = TRUE;

    // create webgl context to canvas element using id
    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE gl_context = emscripten_webgl_create_context(
        canvas_id, &gl_attrib);
    ASSERT(gl_context, -1, "ERROR: Failed to create webgl context\n");

    // activate webgl context
    ASSERT(emscripten_webgl_make_context_current(&gl_context), -1,
        "ERROR: Failed to mamke webgl context current\n");
        

    // compile shaders
    GLuint vs = compile_shader(GL_VERTEX_SHADER, "./src/shaders/default.vert");
    ASSERT(vs, -1, "");
    GLuint fs = compile_shader(GL_FRAGMENT_SHADER, "./src/shaders/default.frag");
    ASSERT(fs, -1, "");

    // create program object
    GLuint program = glCreateProgram();

    // attach shaders to program
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    // set first index in a vertice to be called "pos"
    glBindAttribLocation(program, 0, "pos");

    // link the program
    ASSERT(!link_program(program), -1, "");

    // install program as part of current rendering state
    glUseProgram(program);
}


// this function is synchronous. It will block until it gets the data
// the bytes parameter is both input and output. As input it represents
// the max bytes, and as output it will be how many bytes were read.
// nevermind, an explicit extra member will be added for max
int fetch_file(const char* url, char* data, int max, int* bytes) {
    // fetch attributes
    EMSCRIPTEN_FETCH_ATTR_T fetch_attrib;

    // populate fetch attributes with default and custom values
    emscripten_fetch_attr_init(&fetch_attrib);
    fetch_attrib.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY | 
                              EMSCRIPTEN_FETCH_SYNCHRONOUS;
    strcpy(fetch_attrib.requestMethod, "GET");

    // fetch file (blocking)
    emscripten_fetch_t *fetch = emscripten_fetch(&attr, url);
    // the documentation on this is, like, nonexistant. So I have no idea why 
    // the success fetch status is 200. Maybe it is an http code.
    if (fetch->status == 200)
        printf("Fetched \"%s\" (%llu)\n", fetch->url, fetch->numBytes);
    else {
        printf("Fetch \"%s\" FAILED! (HTTP status code: %d)\n", 
            fetch->url, fetch->status);
        return -1;
    }

    // copy data to data buffer
    memcpy(data, fetch->data, MIN(max, fetch->numBytes));

    // set output of total length of file
    if (bytes != NULL)
        *bytes = fetch->numBytes;

    // free fetch object
    emscripten_fetch_close(fetch);

    return 0;
}


static GLuint compile_shader(GLenum shader_type, const char* url) {
    // load shader
    // make sure everything is zeroed out so that the
    // string terminator is there by default
    char src[1024] = {0};
    int len = sizeof(data);
    ASSERT(fetch_file(url, src, len-1, &len), 0, "");
    ASSERT(len < sizeof(data), 0, 
        "ERROR: Loaded shader file exceeded buffer length \"%s\"", url);

    // create shader object (only returns handle)
    GLuint shader = glCreateShader(shader_type);

    // set the shader source to a single shader that is null terminated
    glShaderSource(shader, 1, &src, NULL);

    printf("Compiling shader \"%s\"", name);

    // compile the shader
    glCompileShader(shader);
    //GLenum err = glGetError();

    // print out compiler errors if any
    GLint err, len;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &err);
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
    if (err == GL_FALSE) {
        char log[len];
        glGetShaderInfoLog(shader, len, NULL, log);
        printf(log);
        return 0;
    }

    // returns shader handler
    return shader;
}


static int link_program(GLuint program, const char* name) {
    printf("Linking program \"%s\"", name);

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
