#include <math.h>

#include "shapes.h"
#include "../main.h"




void init_circle(void);
void init_sphere(void);
void init_triangle(void);
void init_polygon(void);
void init_rectangle(void);


GLuint triangle_vert_buff;
GLuint polygon_vert_buff;
GLuint circle_vert_buff;
GLuint square_vert_buff;
GLuint sphere_vert_buff;



// TODO:
// I'm realizing if two models are using the same mesh, they
// should reference the opengl context for it rather than make a new
// one. In other words, the mesh should create a buffer, not the model
TRIANGLE_MESH_TYPE triangle_mesh = {
    .verts = 3,
    .type = MESHTYPE_2D_PACKED,
    .mode = GL_TRIANGLES,
    .data = {
         0.0,  0.5,
        -0.5, -0.5,
         0.5, -0.5,
    },
};

// TODO: Change OpenGL default winding order to be clockwise
SQUARE_MESH_TYPE square_mesh = {
    .verts = 4,
    .type = MESHTYPE_2D_PACKED,
    .mode = GL_TRIANGLE_FAN,
    .data = {
        -0.5,  0.5,
        -0.5, -0.5,
         0.5, -0.5,
         0.5,  0.5,
    },
};
    
CIRCLE_MESH_TYPE circle_mesh = {
    .verts = CIRCLE_RES,
    .type = MESHTYPE_2D_PACKED,
    .mode = GL_TRIANGLE_FAN,
    .data = {0},
};


SPHERE_MESH_TYPE sphere_mesh = {
    .verts = SPHERE_VERTS,
    .type = MESHTYPE_3D_PACKED,
    .mode = GL_TRIANGLE_STRIP,
    .data = {0},
};










SHADER* shader_init(SHADER* shader, GLuint program, SHADER_USE_CALL call, void* data) {
    *shader = (SHADER){
        .program = program,
        .callback = call,
        .data = data,
    };

    // select current shader to get value locations
    glUseProgram(program);

    shader->vert_pos_loc = glGetAttribLocation(program,  "vert_pos");
    ASSERT(shader->vert_pos_loc >= 0, NULL, "no location for vert_pos_loc\n");

    // note, these may return -1, meaning they are not in the program
    shader->u_mod_mat_loc    = glGetUniformLocation(program, "u_mod_mat");
    shader->u_color_loc      = glGetUniformLocation(program, "u_color");
    shader->u_light_norm_loc = glGetUniformLocation(program, "u_light_norm");
    shader->u_light_map_loc  = glGetUniformLocation(program, "u_light_map");

    // deselect shader to undefined shader
    glUseProgram(NULL_SHADER);

    return shader;
}

SHADER* shader_use(SHADER* shader) {
    glUseProgram(shader->program);

    if (shader->callback)
        shader->callback(shader, shader->data);

    return shader;
}






void shapes_init(void) {
    init_circle();
    init_sphere();
    init_triangle();
    init_polygon();
    init_rectangle();
}


void init_circle(void) {
    for (int i = 0; i < CIRCLE_RES; i++) {
        circle_mesh.data[i*2+0] = (float)cos( (float)i * (2*MATH_PI/CIRCLE_RES) );
        circle_mesh.data[i*2+1] = (float)sin( (float)i * (2*MATH_PI/CIRCLE_RES) );
    }

    // create buffer
    glGenBuffers(1, &circle_vert_buff);

    // upload buffer data
    glBindBuffer(GL_ARRAY_BUFFER, circle_vert_buff);
    glBufferData(
        GL_ARRAY_BUFFER, 
        (GLsizeiptr)MESH_sizeof(&circle_mesh),
        circle_mesh.data,
        GL_STATIC_DRAW
    );
    glBindBuffer(GL_ARRAY_BUFFER, NULL_BUFFER);
}


void init_sphere(void) {
    #define STRIP_VERT_INDEX(__V, __D) ((__V) + (__D)*STRIP_VERTS)
    #define X_ANG_OFFSET ((MATH_PI*1/(float)SPHERE_V_RES))
    // 4??? Yeah... This will probably be a problem later
    #define Y_ANG_OFFSET ((MATH_PI*4/(float)SPHERE_D_RES))
        
    // generate sphere mesh
    for (int i = 0; i < SPHERE_D_RES; i++) {
        float yang = Y_ANG_OFFSET*i;
        for (int j = 0; j < SPHERE_V_RES+1; j++) {
            float xang = X_ANG_OFFSET*j;
            // y extruding point
            // rotate on x first and then y, and then y again for extra offset
            vec3 v = {0, -1, 0};
            glm_vec3_rotate(v, xang, (vec3){1, 0, 0});
            glm_vec3_rotate(v, yang, (vec3){0, 1, 0});
            glm_vec3_copy(v, sphere_mesh.v3[STRIP_VERT_INDEX(j*2, i)]);
            //printf("vec1 %f, %f, %f\n", v[0], v[1], v[2]);
            glm_vec3_rotate(v, Y_ANG_OFFSET, (vec3){0, 1, 0});
            glm_vec3_copy(v, sphere_mesh.v3[STRIP_VERT_INDEX(j*2+1, i)]);
            //printf("vec2 %f, %f, %f\n", v[0], v[1], v[2]);
        }
        //glm_vec3_copy((vec3){0, 1,0}, sphere_mesh.v3[STRIP_VERT_INDEX(0, i)]);
        //glm_vec3_copy((vec3){0,-1,0},
        //    sphere_mesh.v3[STRIP_VERT_INDEX(STRIP_VERTS-1, i)]);
    }
    /*for (int i = 0; i < SPHERE_VERTS; i++) {
        vec3* v = sphere_mesh.v3+i;
        if (i%STRIP_VERTS == 0)
            printf("#### strip %d ####\n", i/STRIP_VERTS);
        printf("vec[%d] %f, %f, %f\n", i, v[0][0], v[0][1], v[0][2]);
    }*/

    // create buffer
    glGenBuffers(1, &sphere_vert_buff);

    // upload buffer data
    glBindBuffer(GL_ARRAY_BUFFER, sphere_vert_buff);
    glBufferData(
        GL_ARRAY_BUFFER, 
        (GLsizeiptr)MESH_sizeof(&sphere_mesh),
        sphere_mesh.data,
        GL_STATIC_DRAW
    );
    glBindBuffer(GL_ARRAY_BUFFER, NULL_BUFFER);
}


// TODO: implement these
void init_triangle(void) {return;}
void init_polygon(void) {return;}



void init_rectangle(void) {

    // create buffer
    glGenBuffers(1, &square_vert_buff);

    // upload buffer data
    glBindBuffer(GL_ARRAY_BUFFER, square_vert_buff);
    glBufferData(
        GL_ARRAY_BUFFER,
        (GLsizeiptr)MESH_sizeof(&square_mesh),
        square_mesh.data,
        GL_STATIC_DRAW
    );
    glBindBuffer(GL_ARRAY_BUFFER, NULL_BUFFER);
}




// TODO: finish implementing this
int draw_triangle(vec2 points[3], vec2 pos, SHADER* shader) {
    // TODO: add a default shader if shader is null
    if (shader)
        shader_use(shader);
    else
        return -1;
    /*else
        shader_use();*/

    return -1;
}




int draw_rectangle( float width, float height, float rot, vec2 pos, COLOR color, SHADER* shader) {
    shader_use(shader);
    
    glBindBuffer(GL_ARRAY_BUFFER, square_vert_buff);

    if (shader->callback)
        shader->callback(shader, shader->data);

    glVertexAttribPointer(
        shader->vert_pos_loc,
        2,
        GL_FLOAT,
        GL_FALSE,
        0*sizeof(GLfloat),
        (void*)0            // offset from vertex. The cast is confusing
    );

    glEnableVertexAttribArray(shader->vert_pos_loc);

    mat4 viewmat = GLM_MAT4_IDENTITY_INIT;
    // blegh. I forgot about the opengl ordering here. These need to be in reverse
    glm_translate(viewmat, (vec3){pos[0], pos[1], 0});
    glm_rotate_z(viewmat, rot, viewmat);
    glm_scale(viewmat, (vec3){width, height, 0});

    // set uniform model view matrix
    if (shader->u_mod_mat_loc >= 0)
        glUniformMatrix4fv(shader->u_mod_mat_loc, 
            1, GL_FALSE, (GLfloat*)viewmat);

        // set uniform u_color
    if (shader->u_color_loc >= 0) 
        glUniform4fv(shader->u_color_loc, 1, color.raw);
    
    // send draw to queue
    glDrawArrays(square_mesh.mode, 0, square_mesh.verts);

    return 0;
}



// TODO: implement these later
int draw_polygon(vec2* points, float rot, vec2 pos, SHADER* shader) {return -1;}
int draw_oval(      float width, float height, float rot, vec2 pos, SHADER* shader) {return -1;}
int draw_sphere(vec3 size, vec3 pos, SHADER* shader) {return -1;}





// TODO: paste this code into the relevant above functions

/*

    // create model
    // 2D Circle
    #if 0
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
            .drawtype = DRAWTYPE_2D_PLAIN,
            .update_call = (UPDATE_CALLBACK)circle_update,
            .shader_prog = poly_program,
            .view_mat = GLM_MAT4_IDENTITY_INIT,
        };

        float scale = (FRAND()*0.9 + 0.2)/4;
        
        behave[i] = (BEHAVE){
            .vel = {
                (FRAND()*2-1)/10/10,
                (FRAND()*2-1)/10/10,
                0,
            },
            .pos = {
                FRANDRANGE(wmin[0]+scale, wmax[0]-scale),
                FRANDRANGE(wmin[1]+scale, wmax[1]-scale),
                0,
            },
            .scale = scale,
            .mass = (4/3)*MATH_PI*scale*scale*scale*DENSITY,
        };

        model_transform(models+i);

        MODEL_init(models+i);
    }
    #else
    // 3D Sphere
    for (int i = 0; i < NUM_MODELS; i++) {
        models[i] = (MODEL){
            .color = {
                .r = FRAND(),
                .g = FRAND(),
                .b = FRAND(),
                .w = 1.0
            },
            .id = i,
            .mesh = (MESH*)&sphere_mesh,
            .visable = true,
            .drawtype = DRAWTYPE_3D_PLAIN,
            .update_call = (UPDATE_CALLBACK)circle_update,
            .shader_prog = sphere_program,
            .view_mat = GLM_MAT4_IDENTITY_INIT,
        };

        //float scale = (FRAND()*0.9 + 0.6)/4;
        float scale = FRANDRANGE(0.1, 0.4);
        
        behave[i] = (BEHAVE){
            .vel = {
                (FRAND()*2-1)/10/10,
                (FRAND()*2-1)/10/10,
                (FRAND()*2-1)/10/10,
            },
            .pos = {
                FRANDRANGE(wmin[0]+scale, wmax[0]-scale),
                FRANDRANGE(wmin[1]+scale, wmax[1]-scale),
                FRANDRANGE(wmin[2]+scale, wmax[2]-scale),
            },
            .scale = scale,
            .mass = (4/3)*MATH_PI*scale*scale*scale*DENSITY,
        };

        model_transform(models+i);

        MODEL_init(models+i);
    }
    #endif
}
*/
