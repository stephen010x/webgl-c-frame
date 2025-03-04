#ifndef CAMERA_H
#define CAMERA_H

#include <cglm/cglm.h>



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
        float raw[16];
    };
    /*struct {
        int width;
        int height;
    } screen;*/
    int swidth, sheight;
    vec3 wmin, wmax;
} CAMERA;


extern CAMERA camera;




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




CAMERA* camera_init(CAMERA* camera);
CAMERA* camera_apply(CAMERA* c, unsigned int shader_program)


#endif
