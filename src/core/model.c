#include <stdio.h>

#include "model.h"
#include "shader.h"
#include "texture.h"
#include "files.h"
#include "../main.h"




// TODO use this to create a function that updates all models, maybe.

/*void model_update_pipeline(double t, float dt) {
    // Alright. It looks like the multi-pass model is still
    // the most stable. 
    // Also, the jitteryness seems to be a product of 
    // perfectly elastic collisions in an approximate
    // enviroment with a ball pushing another ball into
    // a wall and demanding 

    //dt /= BEHAVE_PASSES;
    dt = 0.3;
    
    for (int i = 0; i < BEHAVE_PASSES; i++) {
        #if 0
        // This is the multi-pass model in order to 
        // remove bias from order of execution
        for (int i = 0; i < NUM_MODELS; i++)
            MODEL_update(models+i, t, dt);
        for (int i = 0; i < NUM_MODELS; i++) {
            // TODO: actually add this to a model callback or something
            // perhaps implement a multi-pass physics system (layers)
            behave_apply(behave+i, t, dt);
            model_transform(models+i);
        }
        #else
        // this is the single-pass model. Behavior is less equal,
        // but it should avoid some of the jank created by the previous model
        for (int i = 0; i < NUM_MODELS; i++) {
            MODEL_update(models+i, t, dt);
            behave_apply(behave+i, t, dt);
            model_transform(models+i);
        }
        /\*for (int i = 0; i < NUM_MODELS; i++) {
            behave_apply(behave+i, t, dt);
            model_transform(models+i);
        }*\/
        #endif
    }
}*/


int _model_init(MODEL* model);




int model_init(MODEL* model, MESH* mesh, TEXTURE* texture, bool stream) {
    static int count = 0;
    
    *model = (MODEL){
        .color = (COLOR){1.0f, 1.0f, 1.0f, 1.0f},
        .mesh = mesh,
        .id = count++,
        .data = NULL,
        .visable = true,
        .gl_usage = GL_STATIC_DRAW,
        .update_call = NULL,
        .draw_call = NULL,
        .view_mat = GLM_MAT4_IDENTITY_INIT,
        .texture = texture,
    };

    if (!stream)
        model->gl_usage = GL_STATIC_DRAW;
    else
        model->gl_usage = GL_STREAM_DRAW;

    _model_init(model);
        
    return 0;
}

int model_newinit(MODEL* model, NEWMESH* mesh) {

    *model = (MODEL){
        .color = (COLOR){1.0f, 1.0f, 1.0f, 1.0f},
        .newmesh = mesh,
        .id = 0,
        .data = NULL,
        .visable = true,
        .gl_usage = GL_STATIC_DRAW,
        .update_call = NULL,
        .draw_call = NULL,
        .view_mat = GLM_MAT4_IDENTITY_INIT,
        .texture = NULL,
        .use_newmesh = true,
    };

    _model_init(model);
        
    return 0;
}


int _model_init(MODEL* model) {
    // select shader program to use
    //glUseProgram(model->shader_prog);
    
    // create buffer
    glGenBuffers(1, &model->vert_buff);
    glGenBuffers(1, &model->index_buff);

    // store locations for values
    // T/ODO: this is the sort of thing to be stored in a shader object
    /*model->u_mod_mat_loc = glGetUniformLocation(model->shader_prog, "u_mod_mat");
    model->u_color_loc   = glGetUniformLocation(model->shader_prog, "u_color");
    // T/ODO: add error checking for this and others. As it can return -1 if invalid
    model->vert_pos_loc  = glGetAttribLocation(model->shader_prog,  "vert_pos");
    ASSERT(model->vert_pos_loc >= 0, NULL, "no location for vert_pos_loc\n");
    model->vert_norm_loc  = glGetAttribLocation(model->shader_prog,  "vert_norm");

    // get u_light_norm and map location (if it exists)
    model->u_light_norm_loc = glGetUniformLocation(model->shader_prog, "u_light_norm");
    model->u_light_map_loc = glGetUniformLocation(model->shader_prog, "u_light_map");*/

    /*GLenum data_usage;

    switch (model->type) {
    
        case MODELTYPE_STATIC:
            data_usage = GL_STATIC_DRAW;
            break;
            
        case MODELTYPE_DYNAMIC,
            data_usage = GL_STREAM_DRAW;
            break;
    }*/

    if (model->use_newmesh) {


        //printf("%d\n", (int)newmesh_index_sizeof(model->newmesh));
        //printf("%d %d %d\n", (int)model->newmesh->index_count, (int)newmesh_index_sizeof(model->newmesh), (int)newmesh_data_sizeof(model->newmesh));

        glBindBuffer(GL_ARRAY_BUFFER, model->vert_buff);
        glBufferData(
            GL_ARRAY_BUFFER,
            (GLsizeiptr)newmesh_data_sizeof(model->newmesh),
            model->newmesh->data,
            model->gl_usage
        );
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->index_buff);
        glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            (GLsizeiptr)newmesh_index_sizeof(model->newmesh),
            model->newmesh->indices,
            model->gl_usage
        );

        /*GLint bufferSize;
    	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->index_buff);
    	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferSize);
    	printf("size %d\n", bufferSize);*/

    } else {

        glBindBuffer(GL_ARRAY_BUFFER, model->vert_buff);
        glBufferData(
            GL_ARRAY_BUFFER,
            (GLsizeiptr)mesh_data_sizeof(model->mesh),
            model->mesh->data,
            model->gl_usage /*data_usage*/
        );
    }
    
    return 0;
}





// NOTICE: only call this within a shader draw callback
int model_draw(MODEL* model, double t){
    if (!model->visable)
        return 0;

    glBindBuffer(GL_ARRAY_BUFFER, model->vert_buff);

    if (model->use_newmesh)
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->index_buff);

    //printf("%d\n", model->index_buff);
    
    shader_setup_attributes(current_shader);

    // call object specific draw function
    // TODO eventually get rid of this.
    // objects should call this, not the other way around
    if (model->draw_call != NULL)
        model->draw_call(model, t);

    switch (model->gl_usage) {
            
        case GL_STREAM_DRAW:
            glBufferSubData(
                GL_ARRAY_BUFFER,
                0,
                (GLsizeiptr)mesh_data_sizeof(model->mesh),
                model->mesh->data
            );
        break;
    }




    // TODO: Why does this need to be enabled? Is it possible to have
    // multiple vertex attribute arrays, and then just activate one of them?
    //glEnableVertexAttribArray(model->vert_pos_loc);
    GLint vert_pos_loc = glGetAttribLocation(current_shader->program, "vert_pos");
    glEnableVertexAttribArray(vert_pos_loc);

    // set uniform u_color
    if (current_shader->u_color_loc >= 0) 
        glUniform4fv(current_shader->u_color_loc, 1, model->color.raw);

    // set uniform model view matrix
    if (current_shader->u_mod_mat_loc >= 0)
        glUniformMatrix4fv(current_shader->u_mod_mat_loc,
            1, GL_FALSE, (GLfloat*)model->view_mat);

    // set uniform normal matrix
    if (current_shader->u_norm_mat_loc > 0) {
        mat3 norm_mat;
        glm_mat4_pick3(model->view_mat, norm_mat);
        glm_mat3_inv(norm_mat, norm_mat);
        glm_mat3_transpose(norm_mat);
        
        glUniformMatrix3fv(current_shader->u_norm_mat_loc, 
            1, GL_FALSE, (GLfloat*)norm_mat);
    }

    if (model->texture != NULL)
        texture_bind(model->texture, current_shader, "tex0", GL_TEXTURE0);
    
    // send draw to queue
    /*switch (current_shader->drawtype) {
        case SHADER_DRAW_DEFAULT:
            glDrawArrays(model->mesh->mode, 0, model->mesh->verts);
            break;
        case SHADER_DRAW_WIREFRAME:
            glDrawArrays(GL_LINES, 0, model->mesh->verts);
            break;
        case SHADER_DRAW_POINTS:
            glDrawArrays(GL_POINTS, 0, model->mesh->verts);
            break;
    }*/

    /*printf("%d %d %p\n", model->newmesh->mode, model->newmesh->index_count,	
            (void*)model->newmesh->indices);*/

    //static int printcount = 0;

    //printf("i %d\n", model->index_buff);

    if (model->use_newmesh) {
        //if (printcount++ < 8)
        //printf("::%d %d\n", (int)model->newmesh->index_count, (int)newmesh_index_sizeof(model->newmesh));
        
        glDrawElements(model->newmesh->mode, model->newmesh->index_count,	
            GL_UNSIGNED_SHORT, (void*)0); //(void*)model->newmesh->indices);

        //glDrawArrays(model->newmesh->mode, 0, model->newmesh->vert_count);
        
    } else {
        switch (current_shader->drawtype) {
            case SHADER_DRAW_DEFAULT:
                glDrawArrays(model->mesh->mode, 0, model->mesh->verts);
                break;
            case SHADER_DRAW_WIREFRAME:
                glDrawArrays(GL_LINES, 0, model->mesh->verts);
                break;
            case SHADER_DRAW_POINTS:
                glDrawArrays(GL_POINTS, 0, model->mesh->verts);
                break;
        }
    }

    return 0;
}



//*DEBUG*/ print_array_buff(model->mesh->verts, GL_FLOAT);

// void print_array_buff(GLint verts, GLenum type);

/*void print_array_buff(GLint verts, GLenum type) {
    if (verts <= 0)
        return;
    switch (type) {
        case GL_FLOAT: {
            GLfloat data[verts];
            glGetBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(data), *data);
            printf("{");
            for (int i = 0; i < verts-1; i++)
                printf("%f, ", (float)data[i]);
            printf("%f}\n", data[verts-1]);
            break;
        }
    }
}*/






int newmesh_load(NEWMESH* mesh, char* url, char* group) {
    OBJDATA objdata;
    int err;
    int type;
    
    err = load_obj_web(url, &objdata, group);
    if (err) return err;

    switch ((objdata.num_normals > 0) | ((objdata.num_texcoords > 0)<<1)) {
        case 0:
            type = NEWMESHTYPE_VERT3_PACKED;
            break;
        case 1:
            type = NEWMESHTYPE_VERT3_NORM3;
            break;
        case 2:
            ASSERT(false, -1, "ERROR: newmesh_load has not implemented verts with texcoords without norms\n");
            break;
        case 3:
            type = NEWMESHTYPE_VERT3_NORM3_TEX2;
            break;
        default:
            type = MESHTYPE_NONE;     
    }

    *mesh = (NEWMESH){
        .type = type,
        .mode = GL_TRIANGLES,
        //.vert_count = objdata.num_vertices,
        //.index_count = objdata.num_indices,
        .vert_count = objdata.num_indices,
        .index_count = objdata.num_indices,
    };

    /*mesh->data = malloc(newmesh_data_sizeof(mesh));
    mesh->indices = malloc(newmesh_index_sizeof(mesh));

    for (int i = 0; i < objdata.num_indices; i++) {
        float* vertoff = (float*)&objdata.vertices3[objdata.indices[i].vert];
        float* normoff = (float*)&objdata.normals3[objdata.indices[i].norm];
        float* texcoff = (float*)&objdata.texcoords2[objdata.indices[i].tex];
        int vert_index = objdata.indices[i].vert;
        mesh->v3n3t2[vert_index] = (V3N3T2){
            .vert = {vertoff[0], vertoff[1], vertoff[2]},
            .norm = {normoff[0], normoff[1], normoff[2]},
            .tex = {texcoff[0], texcoff[1]},
        };
        mesh->indices[i] = objdata.indices[i].vert;
    }

    // calculate norms manually because objs are misbehaving
    for (int i = 0; i < objdata.num_indices / 3 - 5; i++) {
        vec3 *v[3], *n[3], t1, t2, norm;
        unsigned short *index = &mesh->indices[i*3];
        v[0] = &mesh->v3n3t2[(int)index].vert;
        for (int j = 0; j < 3; j++) {
            v[j] = &mesh->v3n3t2[index[j+3]].vert;
            n[j] = &mesh->v3n3t2[index[j+3]].norm;
        }
        glm_vec3_sub(*v[0], *v[1], t1);
        glm_vec3_sub(*v[1], *v[2], t2);
        glm_vec3_crossn(t1, t2, norm);
        /\*for (int j = 0; j < 3; j++)
            glm_vec3_copy(norm, *n[j]);
            //glm_vec3_copy((vec3){0.0, 0.0, 1.0}, *n[j]);*\/
        glm_vec3_copy((vec3){i%3==0, i%3==1, i%3==2}, *n[0]);
        glm_vec3_copy((vec3){i%3==0, i%3==1, i%3==2}, *n[1]);
        glm_vec3_copy((vec3){i%3==0, i%3==1, i%3==2}, *n[2]);
    }*/

    mesh->data = malloc(newmesh_data_sizeof(mesh));
    mesh->indices = malloc(newmesh_index_sizeof(mesh));

    for (int i = 0; i < objdata.num_indices; i++) {
        float* vertoff = (float*)&objdata.vertices3[objdata.indices[i].vert];
        float* normoff = (float*)&objdata.normals3[objdata.indices[i].norm];
        float* texcoff = (float*)&objdata.texcoords2[objdata.indices[i].tex];
        mesh->v3n3t2[i] = (V3N3T2){
            .vert = {vertoff[0], vertoff[1], vertoff[2]},
            .norm = {normoff[0], normoff[1], normoff[2]},
            .tex = {texcoff[0], texcoff[1]},
        };
        mesh->indices[i] = i;
    }

    objdata_free(&objdata);

    return 0;
}
