#include <emscripten.h>
#include <emscripten/html5.h>
#include <GLES2/gl2.h>
#include "camera.h"
#include "../main.h"
#include "../helper.h"




CAMERA* camera_init(CAMERA* c) {
    get_elementid_size("canvas", &c->swidth, &c->sheight);
    c->ratio = (float)c->swidth/c->sheight;

    if (c->ratio > 1) {
        c->wmin[0] = -1*c->ratio;
        c->wmax[0] =  1*c->ratio;
        c->wmin[1] = -1;
        c->wmax[1] =  1;
    } else {
        c->wmin[0] = -1;
        c->wmax[0] =  1;
        c->wmin[1] = -1/c->ratio;
        c->wmax[1] =  1/c->ratio;
    }
    c->wmin[2] = 0.1;
    c->wmax[2] = 1000.0;
    
    return c;
}




CAMERA* camera_update(CAMERA* c) {
    switch (c->type) {
        case CAMERA_ORTHOGRAPHIC:
            glm_ortho(
                c->wmin[0], c->wmax[0],
                c->wmin[1], c->wmax[1],
                c->wmin[2], c->wmax[2],
                c->viewmat
            );
            break;
        case CAMERA_PERSPECTIVE:
            glm_perspective(c->fov, c->ratio, c->wmin[2], c->wmax[2], c->viewmat);
            break;
    }

    // translate first so that it rotates about the origin
    glm_translate(c->viewmat, c->pos);

    // rotate second, x, y, z axes in order
    glm_rotate_x(c->viewmat, c->rot[0], c->viewmat);
    glm_rotate_y(c->viewmat, c->rot[1], c->viewmat);
    glm_rotate_z(c->viewmat, c->rot[2], c->viewmat);

    return c;
}



CAMERA* camera_apply(CAMERA* c, GLuint shader_program) {
    ASSERT(shader_program > 0, NULL, "invalid shader program");
    GLint u_proj_mat_loc;
    glUseProgram(shader_program);
    u_proj_mat_loc = glGetUniformLocation(shader_program, "u_proj_mat");
    // TODO consider just making this an assert, as if you don't want to use 
    // a camera for a shader, then just don't call fhis function. /shrug
    if (u_proj_mat_loc > 0)
        glUniformMatrix4fv(u_proj_mat_loc, 1, GL_FALSE, (GLfloat*)c->raw);

    return c;
}
