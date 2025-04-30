#ifndef MODEL_H
#define MODEL_H

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <GLES2/gl2.h>
#include <cglm/types.h>
// for the LENOF macro
// TODO: move the LENOF macro to a more general file instead of main.h
//#include "../main.h"

#include "tolc/tinyobj_loader_c.h"

#ifndef LENOF
#define LENOF(__n) (sizeof(__n)/sizeof((__n)[0]))
#endif



// I should really get my macro library working and just put these in there.
#define __FORCE_INLINE__ inline __attribute__((always_inline))


struct _SHADER;
struct _TEXTURE;
typedef struct _SHADER SHADER;
typedef struct _TEXTURE TEXTURE;


//#define LENOF(__n) (sizeof(__n)/sizeof((__n)[0]))



enum meshtype {
    MESHTYPE_NONE = 0,
    // might be better to create a derived class for this
    //MESHTYPE_INDEX, // besides, this is a model thing anyway.
    MESHTYPE_1D_PACKED,
    MESHTYPE_2D_PACKED,
    MESHTYPE_3D_PACKED,
    MESHTYPE_3D_VERT_NORM,
    MESHTYPE_3D_VERT_NORM_TEX2,
};



// to be used for sizeof or LENOF only. Otherwise you will segfault
#define VEC2_DUMMY (*(vec2*)NULL)
#define VEC3_DUMMY (*(vec3*)NULL)


// TODO: I should've put the 3d/2d stuff in the mesh mode, not model drawtype!
#define MESH(__n) struct {  \
    int verts;              \
    int type;               \
    /* TODO: consider moving this to shader, so that a shader can determine between wireframe and
    // rasterization. And then maybe create an enum for types that should be determined by mesh, like
    // how the triangles are organized to be rendered, as the shader cant know that. */ \
    GLenum mode;            \
    union {          /*is this union even neccessary?*/       \
        /*vec2 v2[__n/sizeof(vec2)];  \
        vec3 v3[__n/sizeof(vec3)];  \*/ \
        float v1[0];        \
        vec2 v2[0];         \
        vec3 v3[0];         \
    };                      \
    GLfloat data[__n];      \
}
#define MESH2(__n) MESH((__n)*LENOF(VEC3_DUMMY))
#define MESH3(__n) MESH((__n)*LENOF(VEC3_DUMMY))
typedef MESH() MESH;



enum newmeshtype {
    NEWMESHTYPE_NONE = 0,
    // might be better to create a derived class for this
    //MESHTYPE_INDEX, // besides, this is a model thing anyway.
    NEWMESHTYPE_VERT1_PACKED,
    NEWMESHTYPE_VERT2_PACKED,
    NEWMESHTYPE_VERT3_PACKED,
    NEWMESHTYPE_VERT3_NORM3,
    NEWMESHTYPE_VERT3_NORM3_TEX2,
};



typedef struct {
    vec3 vert;
    vec3 norm;
} V3N3;


typedef struct {
    vec3 vert;
    vec3 norm;
    vec2 tex;
} V3N3T2;



typedef struct {
    int type;
    GLenum mode;
    
    int vert_count;
    int index_count;

    union {
        float *v1;
        vec2 *v2;
        vec3 *v3;
        V3N3 *v3n3;
        V3N3T2 *v3n3t2;
        float *data;
    };
    
    //short *indices;
    union {
        unsigned short (*faces)[3];
        unsigned short *indices;
    };

} NEWMESH;

#define NEWMESH_DUMMY (*(NEWMESH*)NULL)



__FORCE_INLINE__ size_t mesh_data_sizeof(MESH* m) {
    MESH* mesh = (MESH*)m;

    switch (mesh->type) {
        //case MESHTYPE_INDEX:
        case MESHTYPE_1D_PACKED:
            return mesh->verts * sizeof(float);
        case MESHTYPE_2D_PACKED:
            return mesh->verts * sizeof(VEC2_DUMMY);
        case MESHTYPE_3D_PACKED:
            return mesh->verts * sizeof(VEC3_DUMMY);
        case MESHTYPE_3D_VERT_NORM:
            return mesh->verts * 2 * sizeof(VEC3_DUMMY);
        case MESHTYPE_3D_VERT_NORM_TEX2:
            return mesh->verts * (2 * sizeof(VEC3_DUMMY) + 1 * sizeof(VEC2_DUMMY));
    }
    return -1;
}


__FORCE_INLINE__ size_t newmesh_data_sizeof(NEWMESH* m) {
    switch (m->type) {
        case NEWMESHTYPE_VERT1_PACKED:
            return m->vert_count * sizeof(float);
        case NEWMESHTYPE_VERT2_PACKED:
            return m->vert_count * sizeof(VEC2_DUMMY);
        case NEWMESHTYPE_VERT3_PACKED:
            return m->vert_count * sizeof(VEC3_DUMMY);
        case NEWMESHTYPE_VERT3_NORM3:
            return m->vert_count * sizeof(VEC3_DUMMY) * 2;
        case NEWMESHTYPE_VERT3_NORM3_TEX2:
            return m->vert_count * (sizeof(VEC3_DUMMY) * 2 + sizeof(VEC2_DUMMY));;
    }
    return -1;
}

__FORCE_INLINE__ size_t newmesh_index_sizeof(NEWMESH* m) {
    return sizeof(NEWMESH_DUMMY.indices[0]) * m->index_count;
}


__FORCE_INLINE__ size_t mesh_sizeof(MESH* m) {
    return mesh_data_sizeof(m) + sizeof(MESH);
}




//typedef (int (*DRAW_CALLBACK)(int));
typedef void (*UPDATE_CALLBACK)(void*, double, float);
typedef void (*DRAW_CALLBACK)(void*, double);




typedef union {
    struct {
        GLfloat r;
        GLfloat g;
        GLfloat b;
        GLfloat a;
    };
    GLfloat raw[4];
} COLOR;

typedef union {
    struct {
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
    };
    unsigned char raw[4];
} ICOLOR;



#define MODEL_DRAWVOID 0


/*enum drawtype {
    DRAYTYPE_NONE = 0,
    DRAWTYPE_2D_PLAIN,
    DRAWTYPE_3D_PLAIN,
    DRAWTYPE_3D_LINE,
    DRAWTYPE_1D,
};*/


/*enum modeltype {
    MODELTYPE_NONE = 0,
    MODELTYPE_STATIC,
    MODELYYPE_DYNAMIC,
}*/


typedef struct {
    // user set items
    COLOR color;
    union {
        MESH* mesh;
        NEWMESH* newmesh;
    };
    int id; // for indexing behavior data
    void* data; // pointer to object specific structures
    //float x;
    //float y;
    //float scale;
    //float rot;
    bool visable;
    //int drawtype; // probably not needed for now
    //int type;
    GLenum gl_usage;
    // TODO: get rid of these, and have this be more like a derived class
    // where the classes that inherit this call the draw call of this
    // rather than the other way around
    UPDATE_CALLBACK update_call;
    DRAW_CALLBACK draw_call;
    //GLuint shader_prog;
    mat4 view_mat;

    TEXTURE* texture;

    // background items
    // TODO: these really need to be put into a shader class.
    // TODO: The vert buff specifically should go into a mesh class
    GLuint vert_buff;
    GLuint index_buff;
    /*GLint u_mod_mat_loc;
    GLint u_color_loc;
    GLint vert_pos_loc;
    GLint vert_norm_loc;
    GLint u_light_norm_loc;
    GLint u_light_map_loc;*/

    bool use_newmesh;
} MODEL;



// got rid of shader stuff, as the model should act independant of shader
int model_init(MODEL* model, MESH* mesh, TEXTURE* texture, bool stream);
int model_newinit(MODEL* model, NEWMESH* mesh);
// expects the user set items to be populated
//int model_init(MODEL* model);
// NOTICE!  only call this within a shader draw callback
int model_draw(MODEL* model, double t);

__FORCE_INLINE__ void model_update(MODEL* model, double t, float dt) {
    if (model->update_call != NULL)
        return model->update_call(model, t, dt);
}


int newmesh_load(NEWMESH* mesh, char* url, char* group);

__FORCE_INLINE__ void newmesh_free(NEWMESH* mesh) {
    free(mesh->data);
    free(mesh->indices);
}









// OLD notes for old version of mesh
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


/*typedef struct {
    int verts;
    GLenum mode;
    union {
        vec3 verts[0];
    }
    GLfloat data[];
} MESH;*/


#endif
