#ifndef OBJECTS_CHESS_H
#define OBJECTS_CHESS_H

#include "../core/model.h"



#define CHESS_TYPE_MASK 0xF
#define CHESS_PAWN1  0x0
#define CHESS_PAWN2  0x1
#define CHESS_PAWN3  0x2
#define CHESS_PAWN4  0x3
#define CHESS_ROOK   0x4
#define CHESS_KNIGHT 0x5
#define CHESS_BISHOP 0x6
#define CHESS_QUEEN  0x7
#define CHESS_KING   0x8

#define CHESS_HAND_MASK (0b1<<4)
#define CHESS_RIGHT (0<<4)
#define CHESS_LEFT  (1<<4)

#define CHESS_COLOR_MASK (0b1<<5)
#define CHESS_WHITE (0<<5)
#define CHESS_BLACK (1<<5)



#define CHESS_BOARD_WHITE 0
#define CHESS_BOARD_BLACK 1
#define CHESS_BOARD_BORDER 2




typedef struct {
    int flags;

    vec3 pos;
    float rot;
    float scale;
    
    //COLOR color;
    
    //NEWMESH *mesh;
    MODEL model;
} CHESS_PIECE;




typedef struct {
    vec3 pos;
    float rot;
    float scale;

    //COLOR color_black;
    //COLOR color_white;
    //MESH *mesh_white;
    //MESH *mesh_black;
    MODEL model[3];
} CHESS_BOARD;




typedef struct {
    float padding;
    float scale;
    float height;
    const char *rootpath;
    union {
        struct {
            const char *pawn_path;
            const char *rook_path;
            const char *knight_path;
            const char *bishop_path;
            const char *king_path;
            const char *queen_path;
            const char *board_path;
        };
        const char *paths[7];
    };
    COLOR color_white;
    COLOR color_black;
    COLOR color_border;
} CHESS_GEN_DESC;


typedef union {
    NEWMESH index[9];
    struct {
        NEWMESH pawn;
        NEWMESH rook;
        NEWMESH knight;
        NEWMESH bishop;
        NEWMESH king;
        NEWMESH queen;
        NEWMESH board_white;
        NEWMESH board_black;
        NEWMESH board_border;
    };
} MESH_ORGANIZER;




int chess_piece_init(CHESS_PIECE *self, COLOR color, NEWMESH *mesh, float padding, int flags);
void chess_piece_update(CHESS_PIECE *self, double t, float dt);
void chess_piece_draw(CHESS_PIECE *self, double t);


int chess_board_init(CHESS_BOARD *self, COLOR color_white, COLOR color_black, COLOR color_border, NEWMESH *mesh_white, NEWMESH *mesh_black, NEWMESH *mesh_border);
void chess_board_update(CHESS_BOARD *self, double t, float dt);
void chess_board_draw(CHESS_BOARD *self, double t, int id);


void chess_set_gen(CHESS_PIECE (*pieces)[32], NEWMESH (*_meshes)[9], CHESS_BOARD *board, CHESS_GEN_DESC *desc);



#endif
