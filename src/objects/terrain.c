#include <stdbool.h>
#include <math.h>
#include "terrain.h"
#include "../core.h"
#include "../objects.h"


// I got so tired of vec3's not being a friggen' copy constructed type!
typedef struct {
    union {
        vec3 pack;
        vec3 unpack;
    };
} vec3_pack;


vec3_pack terrain_gen_height(TERRAIN* t, int x, int y);
vec3_pack   terrain_gen_norm(TERRAIN* t, int x, int y);
float terrain_gen_height_raw(TERRAIN* t, int x, int y);
//void terrain_draw(void* t, double _, float dt);
//void _terrain_draw(void* t, double _, float dt);


static GEN_MODEL NULL_GEN_MODEL = (GEN_MODEL){0};


void terrain_init(TERRAIN* t, vec3 pos, vec3 scale, GEN_MODEL* gen_model, COLOR color, SHADER* shader/*, LIGHTSOURCE* light*/) {
    *t = (TERRAIN){
        //.pos = (vec3){pos[0], pos[1], pos[2]},
        //.scale = (vec3){scale[0], scale[1], scale[2]},
        //.rows = rows,
        //.cols = cols,
        .color = color,
        .texture = NULL,
        .shader = shader,
        .gen_model = (gen_model == NULL) ? (&NULL_GEN_MODEL) : (gen_model),
        //.light = light,
    };
    glm_vec3_copy(pos, t->pos);
    glm_vec3_copy(scale, t->scale);

    int rows = gen_model->rows;
    int cols = gen_model->cols;

    {
        MESH tmesh = (MESH){
            .verts = cols*rows*12,
            .type = MESHTYPE_3D_VERT_NORM,
            .mode = GL_TRIANGLES,
        };
        // fuck you clang
        //t->mesh = malloc(sizeof(MESH3(cols*rows*12)));
        t->mesh = malloc(MESH_sizeof(&tmesh));
        *t->mesh = tmesh;

        vec3 (*data)[cols][12] = (void*)t->mesh->data;
        vec3_pack (*data_packed)[cols][12] = (void*)data;

        // generate terrain
        for (int x = 0; x < cols; x++)
            for (int y = 0; y < rows; y++) {
                // tri 1
                //data[y][x][0] = (vec3){x+0, y+0, terrain_gen_height(t, x+0, y+0)};
                data_packed[y][x][0]  = terrain_gen_height( t, x+0, y+0 );
                data_packed[y][x][1]  = terrain_gen_norm(   t, x+0, y+0 );
                data_packed[y][x][2]  = terrain_gen_height( t, x+1, y+0 );
                data_packed[y][x][3]  = terrain_gen_norm(   t, x+1, y+0 );
                data_packed[y][x][4]  = terrain_gen_height( t, x+1, y+1 );
                data_packed[y][x][5]  = terrain_gen_norm(   t, x+1, y+1 );
                // tri 2
                data_packed[y][x][6]  = terrain_gen_height( t, x+1, y+1 );
                data_packed[y][x][7]  = terrain_gen_norm(   t, x+1, y+1 );
                data_packed[y][x][8]  = terrain_gen_height( t, x+0, y+1 );
                data_packed[y][x][9]  = terrain_gen_norm(   t, x+0, y+1 );
                data_packed[y][x][10] = terrain_gen_height( t, x+0, y+0 );
                data_packed[y][x][11] = terrain_gen_norm(   t, x+0, y+0 );
            }
    }
    
    model_init(&t->model, t->mesh, NULL, false);
    t->model.color = t->color;
    t->model.draw_call = (DRAW_CALLBACK)terrain_draw;
}




void terrain_destroy(TERRAIN* t) {
    free(t->mesh);
    // TODO: make this a debug mode feature
    *t = (TERRAIN){0};
}





float terrain_gen_height_raw(TERRAIN* t, int x, int y) {
    float height = 0;
    GEN_MODEL* gen = t->gen_model;
    x += gen->x_off;
    y += gen->y_off;

    x *= gen->scale;
    y *= gen->scale;
    
    for (int i = 0; i < gen->sincount; i++) {
        float damp = 1.0;
        
        register float p = gen->sindata[i].period;
        register float h = gen->sindata[i].height;
        register float n = (float)gen->sindata[i].power;
        
        register float a = sin((x + h * cos(y / p)) / p);
        register float b = cos((y + h * cos(x / p)) / p);

        if (gen->sindata[i].damp_enable == true) {
            register float k = gen->sindata[i].damp_period;

            register float a = sin((x + k * cos(y / k)) / k);
            register float b = cos((y + k * cos(x / k)) / k);
            
            damp = a*b;
        }
        
        height += h*(powf(a, n) + powf(b, n)) * damp;
    }
    
    return height;
}




__FORCE_INLINE__ vec3_pack terrain_gen_height(TERRAIN* t, int x, int y) {
    return (vec3_pack){
        .pack = {x, y, terrain_gen_height_raw(t, x, y)},
    };
}




vec3_pack terrain_gen_norm(TERRAIN* t, int x, int y) {
    //float h = terrain_gen_height(t, x, y);
    
    register float hx0 = terrain_gen_height_raw(t, x-1, y);
    register float hx1 = terrain_gen_height_raw(t, x+1, y);
    
    register float hy0 = terrain_gen_height_raw(t, x, y-1);
    register float hy1 = terrain_gen_height_raw(t, x, y+1);

    register float dhx = (hx1 - hx0) / 2;
    register float dhy = (hy1 - hy0) / 2;

    register vec3_pack norm;
    glm_vec3_crossn((vec3){1,0,dhx}, (vec3){0,1,dhy}, norm.pack);

    return norm;
}




void terrain_draw(TERRAIN* t, double _t) {
    shader_set_vec4(current_shader, "u_color", t->color.raw);
    model_draw(&t->model, _t);
}




void terrain_update(TERRAIN* t, double _, float dt) {
    glm_mat4_identity(t->model.view_mat);
    glm_translate(t->model.view_mat, t->pos);
    glm_scale(t->model.view_mat, t->scale);
}




/*void _terrain_draw(void* t, double _t) {
    shader_set_vec3(t->shader, "u_light_dir", t->light->dir.dir);
    
    shader_set_float(t->shader, "u_light_amb",    t->light->dir.amb);
    shader_set_float(t->shader, "u_light_spec",   t->light->dir.spec);
    shader_set_float(t->shader, "u_light_bright", t->light->dir.bright);
}*/
