#include "shapes.h"


    for (int i = 0; i < CIRC_RES; i++) {
        circle_mesh.data[i*2+0] = (float)cos( (float)i * (2*MATH_PI/CIRC_RES) );
        circle_mesh.data[i*2+1] = (float)sin( (float)i * (2*MATH_PI/CIRC_RES) );
    }

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
