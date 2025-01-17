//#include <math.h>
#include <stdio.h>
#include "circle.h"


#define FRAND() ((float)rand()/(float)RAND_MAX)


//#define INIT_SIZE 32


#define ABS(__n) ({typeof(__n) n = (__n); n >= 0 ? n : -n;})
#define SIGN(__n) ({typeof(__n) n = (__n); n == 0 ? 0 : (n > 0 ? 1 : -1);})


/*int CIRCLE_needed_verts(CIRCLE* circle) {
    return INIT_SIZE*4;
}


int CIRCLE_needed_size() {
    return sizeof(CIRCLE) + INIT_SIZE*4;
}*/


CIRCLE* CIRCLE_default(CIRCLE* circle, int screen_width, int screen_height, GLuint shader_program, MESH* mesh) {
    // generate default values for circle
    circle->screen_width = screen_width;
    circle->screen_height = screen_height;
    circle->shader_program = shader_program;
    circle->x = (GLfloat)(rand()%screen_width);
    circle->y = (GLfloat)(rand()%screen_height);
    circle->radius = (GLfloat)(rand()%(screen_width/4));
    circle->color = (COLOR){
        .r = (GLfloat)FRAND(),
        .g = (GLfloat)FRAND(),
        .b = (GLfloat)FRAND()
    };
    circle->dx = FRAND()*10;
    circle->dy = FRAND()*10;
    circle->mesh = mesh;
    //circle->vert_count = CIRCLE_needed_verts(circle);
    return circle;
}


CIRCLE* CIRCLE_init(CIRCLE* circle) {
    //int v_count = CIRCLE_needed_verts(circle);

    // make sure there is enough allocated space to place vertices
    //if (circle->vert_count != v_count)
    //    return NULL;
        
    // generate vertices
    // [x] TODO: Generate this as a single mesh in the main, and then
    // pass it to the model to use as a mesh.
    /*for (int i = 0; i <= v_count/4; i++) {
        circle->verts[i+0] = 0;
        circle->verts[i+1] = 0;
        circle->verts[i+2] = cos( (float)i * (2*MATH_PI/(v_count/4)) );
        circle->verts[i+3] = sin( (float)i * (2*MATH_PI/(v_count/4)) );
    }*/

    // allocate buffer for our vertices
    // glGenBuffers will find an unused buffer greater than 0. It *technically*
    // isn't neccissary if you kept track of the numbers yourself.
    glGenBuffers(1, &circle->vert_buff);
    glBindBuffer(GL_ARRAY_BUFFER, circle->vert_buff);
    // TODO: add error handling. This is basically a malloc for gpus, so it can fail
    // if out of storage
    glBufferData(GL_ARRAY_BUFFER, 
        (GLsizeiptr)((unsigned long)circle->mesh->len * sizeof(*circle->mesh->verts)), 
        circle->mesh->verts,  GL_STATIC_DRAW);

    // set vertex attributes
    GLuint pos_vert_attrib_loc = 
        (GLuint)glGetAttribLocation(circle->shader_program, "vert_pos");
    glVertexAttribPointer(
        pos_vert_attrib_loc,
        2,
        GL_FLOAT,
        GL_FALSE,
        0, //sizeof(GLfloat)*2, // this is calculated by opengl if set to zero
        (void*)0                // offset from vertex. The cast is confusing
    );
    glEnableVertexAttribArray(pos_vert_attrib_loc);

    // set uniform u_color
    GLint u_color_loc = glGetUniformLocation(circle->shader_program, "u_color");
    glUniform4fv(u_color_loc, 1, circle->color.raw);

    // store model view matrix location
    circle->u_mod_view_mat_loc =
        glGetUniformLocation(circle->shader_program, "u_mod_view_mat_loc");
    
    return circle;
}


void CIRCLE_destroy(CIRCLE* circle) {
    // TODO: destroy gl buffers and other such stuff here
    (void)circle;
    return;
}


void CIRCLE_update(CIRCLE* circle, float dt) {
    // predict next position
    register const float p_x = circle->x + circle->dx*dt;
    register const float p_y = circle->y + circle->dy*dt;
    register const float s_w = (GLfloat)circle->screen_width;
    register const float s_h = (GLfloat)circle->screen_height;
    register const float rad = circle->radius;

    // add collisions
    if (p_x + rad > s_w)
        circle->dx = -ABS(circle->dx);
    if (p_x - rad < 0)
        circle->dx = ABS(circle->dx);

    if (p_y + rad > s_h)
        circle->dy = -ABS(circle->dy);
    if (p_y - rad < 0)
        circle->dy = ABS(circle->dy);

    //.evaluate new position
    circle->x += circle->dx*dt;
    circle->y += circle->dx*dt;

    printf("%p: (%f, %f)\n", circle, circle->x, circle->y);
}


void CIRCLE_draw(CIRCLE* circle) {
    const register GLfloat x = circle->x;
    const register GLfloat y = circle->y;
    const register GLfloat rad = circle->radius;

    // hopefully this is the right matrix
    // all this should do is translate and scale
    GLfloat mat4[16] = {
        1.8329142332077026f, 0, 0, 0,
        0, 1.8329142332077026f, 0, 0,
        0, 0, 1, 0,
        -4.312682628631592f, -7.941835403442383f, 0, 1
    };

    /*{
        rad,   0,   0, 0,
        0,     rad, 0, 0,
        0,     0,   1, 0,
        x,     y,   0, 1,
    };*/
    glUniformMatrix4fv(circle->u_mod_view_mat_loc, 1, GL_FALSE, mat4);

    // finally draw the model to the screen/draw buffer
    // TODO: replace the 66 with a more dynamic value
    //glDrawArrays(GL_TRIANGLE_STRIP, 0, 66);
    glDrawArrays(GL_LINES, 0, 66);
}
