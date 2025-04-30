#ifndef CORE_FILE_H
#define CORE_FILE_H

#include <stdbool.h>


#define __FORCE_INLINE__ inline __attribute__((always_inline))



typedef struct {
    int num_indices;
    int num_vertices;
    int num_normals;
    int num_texcoords;

    void* original_indices;

    union {
        int raw[3];
        struct {
            int vert;
            int tex;
            int norm;
        };
    } *indices;
    union {
        float *vertices;
        float (*vertices3)[3];
    };
    union {
        float *normals;
        float (*normals3)[3];
    };
    union {
        float *texcoords;
        float (*texcoords2)[2];
    };
} OBJDATA;



bool file_exists(const char* path);
// returns number of bytes loaded
// success if return is greater than 0
int load_file(const char* path, void** buffer);
//void unload_file(void* buffer);
// returns error code
int write_file(const char* path, void* data, int bytes);
void delete_file(const char* path);


int load_file_web(const char* url, void** buffer);



__FORCE_INLINE__ void unload_file(void* buffer) { free(buffer); }
__FORCE_INLINE__ void unload_file_web(void* buffer) { free(buffer); }


int load_obj_web(const char* url, OBJDATA *objdata, char* group);

__FORCE_INLINE__ void objdata_free(OBJDATA* objdata) {
    free(objdata->original_indices);
    free(objdata->vertices);
    free(objdata->normals);
    free(objdata->texcoords);
    *objdata = (OBJDATA){0};
}


#endif
