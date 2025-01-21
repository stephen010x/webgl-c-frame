#ifndef CIRCLE_H
#define CIRCLE_H

#include <GLES2/gl2.h>
#include <stdlib.h>


/*#ifndef typeof
#ifdef __clang__
#define typeof(x) __typeof__(x)
#endif
#endif*/



typedef struct {
    int len;
    GLfloat verts[];
} MESH;

#define MESH_VERT typeof(*((MESH*)NULL)->verts)


typedef struct {
    GLfloat x;
    GLfloat y;
} POINT;

typedef union {
    struct {
        GLfloat r;
        GLfloat g;
        GLfloat b;
        GLfloat w;
    };
    GLfloat raw[4];
} COLOR;


typedef struct {
    COLOR color;
    //POINT vel;
    GLfloat dx, dy, radius;
    int vert_count;
    int screen_width;
    int screen_height;

    GLuint vert_buff;
    GLuint shader_program;
    GLint u_mod_view_mat_loc;
    
    /*union {
        struct {
            GLfloat x, y, verts[0];
        };
        GLfloat buff[2];
    };*/
    GLfloat x, y;
    MESH* mesh;
} CIRCLE;


//int CIRCLE_needed_verts(CIRCLE* circle);
//int CIRCLE_needed_size();
CIRCLE* CIRCLE_default(CIRCLE* circle, int screen_width, int screen_height, GLuint shader_program, MESH* mesh);
CIRCLE* CIRCLE_init(CIRCLE* circle);
void CIRCLE_destroy(CIRCLE* circle);
void CIRCLE_update(CIRCLE* circle, float dt);
void CIRCLE_draw(CIRCLE* circle);


#endif
