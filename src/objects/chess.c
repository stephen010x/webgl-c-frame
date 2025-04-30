#include <stdio.h>
#include <string.h>
#include <cglm/cglm.h>

#include "../core/model.h"
#include "chess.h"



//#define BOARD_HEIGHT 0.1
#define MATH_PI 3.1415926535897
#define DEG_TO_RAD(__n) ((__n)*MATH_PI/180.0)



int chess_piece_init(CHESS_PIECE *self, COLOR color, NEWMESH *mesh, float padding, int flags) {

    *self = (CHESS_PIECE) {
        .flags = flags,
        .scale = 1.0,
        //.color = color,
        //.mesh = mesh,
        .pos = {0, -3.5, 0},
        .rot = DEG_TO_RAD(90),
    };

    switch (flags & CHESS_TYPE_MASK) {
        case CHESS_ROOK:   self->pos[0] =  3.5; break;
        case CHESS_KNIGHT: self->pos[0] =  2.5; break;
        case CHESS_BISHOP: self->pos[0] =  1.5; break;
        case CHESS_KING:   self->pos[0] =  0.5; break;
        case CHESS_QUEEN:  self->pos[0] = -0.5; break;
        default: {
            int pawnid = (flags & CHESS_TYPE_MASK) - CHESS_PAWN1;
            if (pawnid + CHESS_PAWN1 <= CHESS_PAWN4) {
                self->pos[0] = pawnid + 0.5;
                self->pos[1] = -2.5;
            } else {
                printf("ERROR: Invalid chess piece type %p\n", (void*)flags);
                return -1;
            }
        }
    }

    switch (flags & CHESS_TYPE_MASK) {
        
    }

    glm_vec3_scale(self->pos, padding, self->pos);

    if ((flags & CHESS_HAND_MASK) == CHESS_LEFT)
        glm_vec3_copy((vec3){-self->pos[0], self->pos[1], self->pos[2]}, self->pos);
        
    if ((flags & CHESS_COLOR_MASK) == CHESS_BLACK) {
        glm_vec3_copy((vec3){-self->pos[0], -self->pos[1], self->pos[2]}, self->pos);
        self->rot += DEG_TO_RAD(180);
    }


    model_newinit(&self->model, mesh);
    self->model.color = color;
    
    return 0;
}




void chess_piece_update(CHESS_PIECE *self, double t, float dt) {
    mat4 *viewmat = &self->model.view_mat;
    glm_mat4_identity(*viewmat);
    glm_translate(*viewmat, self->pos);
    glm_rotate(*viewmat, self->rot, (vec3){0,0,1});
    glm_scale_uni(*viewmat, self->scale);
}




void chess_piece_draw(CHESS_PIECE *self, double t) {
    model_draw(&self->model, t);
}




int chess_board_init(CHESS_BOARD *self, COLOR color_white, COLOR color_black, COLOR color_border, NEWMESH *mesh_white, NEWMESH *mesh_black, NEWMESH *mesh_border) {

    *self = (CHESS_BOARD){
        .pos = {0},
        .rot = 0.0,
        .scale = 1.0,
    };

    model_newinit(self->model+0, mesh_white);
    self->model[0].color = color_white;

    model_newinit(self->model+1, mesh_black);
    self->model[1].color = color_black;

    model_newinit(self->model+2, mesh_border);
    self->model[2].color = color_border;
    
    return 0;
}




void chess_board_update(CHESS_BOARD *self, double t, float dt) {
    for (int i = 0; i < LENOF(self->model); i++) {
        mat4 *viewmat = &self->model[i].view_mat;
        glm_mat4_identity(*viewmat);
        glm_translate(*viewmat, self->pos);
        glm_rotate(*viewmat, self->rot, (vec3){0,0,1});
        glm_scale_uni(*viewmat, self->scale);
    }
}




void chess_board_draw(CHESS_BOARD *self, double t, int id) {
    model_draw(self->model+id, t);
}




void chess_set_gen(CHESS_PIECE (*pieces)[32], NEWMESH (*_meshes)[9], CHESS_BOARD *board, CHESS_GEN_DESC *desc) {

    MESH_ORGANIZER *meshes = (void*)*_meshes;
    COLOR white = desc->color_white;
    COLOR black = desc->color_black;
    float padding = desc->padding;

    char buff[64];
    for (int i = 0; i < 6; i++) {
        strcpy(buff, desc->rootpath);
        strcat(buff, desc->paths[i]);
        newmesh_load(meshes->index+i, buff, NULL);
    }
    strcpy(buff, desc->rootpath);
    strcat(buff, desc->paths[6]);
    newmesh_load(meshes->index+6, buff, "white");
    newmesh_load(meshes->index+7, buff, "black");
    newmesh_load(meshes->index+8, buff, "border");

    chess_board_init(board, desc->color_white, desc->color_black, desc->color_border,
        &meshes->board_white, &meshes->board_black, &meshes->board_border);

    chess_piece_init(pieces[0]+0,  white, &meshes->pawn,   padding, CHESS_PAWN1  | CHESS_WHITE | CHESS_RIGHT);
    chess_piece_init(pieces[0]+1,  white, &meshes->pawn,   padding, CHESS_PAWN2  | CHESS_WHITE | CHESS_RIGHT);
    chess_piece_init(pieces[0]+2,  white, &meshes->pawn,   padding, CHESS_PAWN3  | CHESS_WHITE | CHESS_RIGHT);
    chess_piece_init(pieces[0]+3,  white, &meshes->pawn,   padding, CHESS_PAWN4  | CHESS_WHITE | CHESS_RIGHT);
    chess_piece_init(pieces[0]+4,  white, &meshes->rook,   padding, CHESS_ROOK   | CHESS_WHITE | CHESS_RIGHT);
    chess_piece_init(pieces[0]+5,  white, &meshes->knight, padding, CHESS_KNIGHT | CHESS_WHITE | CHESS_RIGHT);
    chess_piece_init(pieces[0]+6,  white, &meshes->bishop, padding, CHESS_BISHOP | CHESS_WHITE | CHESS_RIGHT);
    chess_piece_init(pieces[0]+7,  white, &meshes->pawn,   padding, CHESS_PAWN1  | CHESS_WHITE | CHESS_LEFT);
    chess_piece_init(pieces[0]+8,  white, &meshes->pawn,   padding, CHESS_PAWN2  | CHESS_WHITE | CHESS_LEFT);
    chess_piece_init(pieces[0]+9,  white, &meshes->pawn,   padding, CHESS_PAWN3  | CHESS_WHITE | CHESS_LEFT);
    chess_piece_init(pieces[0]+10, white, &meshes->pawn,   padding, CHESS_PAWN4  | CHESS_WHITE | CHESS_LEFT);
    chess_piece_init(pieces[0]+11, white, &meshes->rook,   padding, CHESS_ROOK   | CHESS_WHITE | CHESS_LEFT);
    chess_piece_init(pieces[0]+12, white, &meshes->knight, padding, CHESS_KNIGHT | CHESS_WHITE | CHESS_LEFT);
    chess_piece_init(pieces[0]+13, white, &meshes->bishop, padding, CHESS_BISHOP | CHESS_WHITE | CHESS_LEFT);
    chess_piece_init(pieces[0]+14, white, &meshes->king,   padding, CHESS_KING   | CHESS_WHITE);
    chess_piece_init(pieces[0]+15, white, &meshes->queen,  padding, CHESS_QUEEN  | CHESS_WHITE);

    chess_piece_init(pieces[0]+16, black, &meshes->pawn,   padding, CHESS_PAWN1  | CHESS_BLACK | CHESS_RIGHT);
    chess_piece_init(pieces[0]+17, black, &meshes->pawn,   padding, CHESS_PAWN2  | CHESS_BLACK | CHESS_RIGHT);
    chess_piece_init(pieces[0]+18, black, &meshes->pawn,   padding, CHESS_PAWN3  | CHESS_BLACK | CHESS_RIGHT);
    chess_piece_init(pieces[0]+19, black, &meshes->pawn,   padding, CHESS_PAWN4  | CHESS_BLACK | CHESS_RIGHT);
    chess_piece_init(pieces[0]+20, black, &meshes->rook,   padding, CHESS_ROOK   | CHESS_BLACK | CHESS_RIGHT);
    chess_piece_init(pieces[0]+21, black, &meshes->knight, padding, CHESS_KNIGHT | CHESS_BLACK | CHESS_RIGHT);
    chess_piece_init(pieces[0]+22, black, &meshes->bishop, padding, CHESS_BISHOP | CHESS_BLACK | CHESS_RIGHT);
    chess_piece_init(pieces[0]+23, black, &meshes->pawn,   padding, CHESS_PAWN1  | CHESS_BLACK | CHESS_LEFT);
    chess_piece_init(pieces[0]+24, black, &meshes->pawn,   padding, CHESS_PAWN2  | CHESS_BLACK | CHESS_LEFT);
    chess_piece_init(pieces[0]+25, black, &meshes->pawn,   padding, CHESS_PAWN3  | CHESS_BLACK | CHESS_LEFT);
    chess_piece_init(pieces[0]+26, black, &meshes->pawn,   padding, CHESS_PAWN4  | CHESS_BLACK | CHESS_LEFT);
    chess_piece_init(pieces[0]+27, black, &meshes->rook,   padding, CHESS_ROOK   | CHESS_BLACK | CHESS_LEFT);
    chess_piece_init(pieces[0]+28, black, &meshes->knight, padding, CHESS_KNIGHT | CHESS_BLACK | CHESS_LEFT);
    chess_piece_init(pieces[0]+29, black, &meshes->bishop, padding, CHESS_BISHOP | CHESS_BLACK | CHESS_LEFT);
    chess_piece_init(pieces[0]+30, black, &meshes->king,   padding, CHESS_KING   | CHESS_BLACK);
    chess_piece_init(pieces[0]+31, black, &meshes->queen,  padding, CHESS_QUEEN  | CHESS_BLACK);

    for (int i = 0; i < 32;  i++) {
        pieces[0][i].scale = desc->scale;
        pieces[0][i].pos[2] += desc->height;
    }
    board->scale = desc->scale;
    board->pos[2] += desc->height;
}
