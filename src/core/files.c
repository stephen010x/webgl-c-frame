#include <stdbool.h>
#include <stdlib.h>
#include <emscripten.h>

#include "files.h"
#include "../main.h"

#define TINYOBJ_LOADER_C_IMPLEMENTATION
#include "../lib/tolc/tinyobj_loader_c.h"




#define DB_NAME "wasm-c-frame-filesystem"




const char* db_name = DB_NAME;


bool file_exists(const char* path) {
    int error;
    int exists;
    emscripten_idb_exists(db_name, path, &exists, &error);
    ASSERT(!error, false, "ERROR checking if file \"%s\" exists\n", path);
    return !!exists;
}




int load_file(const char* path, void** buffer) {
    int error;
    int bytes;
    emscripten_idb_load(db_name, path, buffer, &bytes, &error);
    ASSERT(!error, -1, "ERROR loading file \"%s\"\n", path);
    return bytes;
}




int write_file(const char* path, void* data, int bytes) {
    //if (file_exists(path))
    //    delete_file(path);
    int error;
    emscripten_idb_store(db_name, path, data, bytes, &error);
    ASSERT(!error, -1, "ERROR writing file \"%s\"\n", path);
    return 0;
}




void delete_file(const char* path) {
    int error;
    emscripten_idb_delete(db_name, path, &error);
    ASSERTVOID(!error, "ERROR deleting file \"%s\"\n", path);
}




int load_file_web(const char* url, void** buffer) {
    int error;
    int bytes;
    emscripten_wget_data(url, buffer, &bytes, &error);
    ASSERT(!error, -1, "ERROR fetching url \"%s\"\n", url);
    return bytes;
}




void my_file_reader_callback(void *_, const char *url, int is_mtl, const char *__, char **buff, size_t *len) {
    if (is_mtl) {
        *buff = NULL;
        *len = 0;
        printf("oh noes! no support!");
        return;
    }

    *len = load_file_web(url, (void**)buff);
}




int load_obj_web(const char* url, OBJDATA *objdata, char* group) {
    tinyobj_attrib_t attrib;
    tinyobj_shape_t *shapes;
    tinyobj_material_t *materials;
    size_t num_shapes;
    size_t num_materials;
    int err;

    err = tinyobj_parse_obj(&attrib, &shapes, &num_shapes, &materials, 
        &num_materials, url, &my_file_reader_callback, NULL, 0);

    ASSERT(err == TINYOBJ_SUCCESS, err, "ERROR: tinyobj_parse_obj in load_obj_web failed with code %d\n", err);

    err = 0;
    for (int i = 0; i < attrib.num_face_num_verts; i++)
        if (attrib.face_num_verts[i] != 3) {
            err = -4;
            break;
        }

    ASSERT(err == 0, err, "ERROR: attrib.face_num_verts array is corrupt\n");

    if (group != NULL) {
    
        int i;
        for (i = 0; strcmp(group, shapes[i].name) != 0 && i < num_shapes; i++);

        if (i >= num_shapes) {
            printf("ERROR: obj group not found \"%s\"\n", group);
            tinyobj_attrib_free(&attrib);
            tinyobj_materials_free(materials, num_materials);
            tinyobj_shapes_free(shapes, num_shapes);
            return -1;
        }

        printf("%d %d %d %d %s %s %d\n", shapes[i].face_offset, shapes[i].length, attrib.num_faces, num_shapes, shapes[i].name, group, i);
        
        *objdata = (OBJDATA){
            .num_indices   = shapes[i].length*3,
            .num_vertices  = attrib.num_vertices,
            .num_normals   = attrib.num_normals,
            .num_texcoords = attrib.num_texcoords,
            .indices   = (void*)(attrib.faces + shapes[i].face_offset*3),
            .vertices  = attrib.vertices,
            .normals   = attrib.normals,
            .texcoords = attrib.texcoords,
            .original_indices = (void*)attrib.faces,
        };
    } else {
        *objdata = (OBJDATA){
            .num_indices   = attrib.num_faces,
            .num_vertices  = attrib.num_vertices,
            .num_normals   = attrib.num_normals,
            .num_texcoords = attrib.num_texcoords,
            .indices   = (void*)attrib.faces,
            .vertices  = attrib.vertices,
            .normals   = attrib.normals,
            .texcoords = attrib.texcoords,
            .original_indices = (void*)attrib.faces,
        };
    }

    tinyobj_materials_free(materials, num_materials);
    tinyobj_shapes_free(shapes, num_shapes);

    if (attrib.face_num_verts) free(attrib.face_num_verts);
    if (attrib.material_ids)   free(attrib.material_ids);

    return 0;
}
