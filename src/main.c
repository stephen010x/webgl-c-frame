#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
// TODO: in an ideal world, this wouldn't be needed in main
#include <GLES2/gl2.h>
// TODO" in an ideal world, these also wouldn't be needed in main
#include <emscripten.h>
#include <emscripten/html5.h>

// TODO: get rid of main header
#include "main.h"
#include "core.h"
#include "objects.h"
#include "shaders/shaders.h"
#include "helper.h"



//*DEBUG*/ extern CUBE_MESH_TYPE cube_mesh;


#define COLOR_RED    ((COLOR){0.8, 0.2, 0.2, 1.0})
#define COLOR_ORANGE ((COLOR){0.8, 0.3, 0.2, 1.0})
//#define COLOR_BLUE   ((COLOR){0.3, 0.4, 0.9, 1.0})
#define COLOR_PURPLE ((COLOR){0.7, 0.2, 0.6, 1.0})
#define COLOR_WHITE  ((COLOR){1.0, 1.0, 1.0, 1.0})
#define COLOR_BLACK  ((COLOR){0.0, 0.0, 0.0, 1.0})
#define COLOR_ORANGE_ALPHA ((COLOR){0.8, 0.3, 0.2, 0.5})
//#define COLOR_BLUE_ALPHA   ((COLOR){0.3, 0.4, 0.9, 15/16.0})
#define COLOR_BLUE_ALPHA   ((COLOR){0.3, 0.4, 0.9, 8.0/16.0})
//#define COLOR_BLUE_ALPHA COLOR_ORANGE_ALPHA

//#define COLOR_DIRT_GREY  ((COLOR){64.0/256.0, 59.0/256.0, 53.0/256.0, 1.0})
//#define COLOR_DIRT_GREY  ((COLOR){64.0/256.0*2, 59.0/256.0*2, 53.0/256.0*2, 1.0})
#define COLOR_DIRT_GREY  ((COLOR){68.0/256.0*2, 55.0/256.0*2, 40.0/256.0*2, 1.0})
#define COLOR_GREY  ((COLOR){0.8, 0.8, 0.8, 1.0})
#define COLOR_GREEN  ((COLOR){0.20, 0.3, 0.15, 1.0})
#define COLOR_BLUE  ((COLOR){0.15, 0.1, 0.3, 1.0})



//#define MAX_CURVES 5
//BEZIER curves[MAX_CURVES];

//FRACTAL fractal;

#define DT_DIVISOR 100


//WINDOW window;
MOUSE mouse;

// player mouse
//PMOUSE pmouse;


GEN_MODEL(20) _gen_model;
#define gen_model (*(GEN_MODEL*)&_gen_model)

TERRAIN terrain;
TERRAIN water;



//#define SQRT_3 1.73205080757


/*enum game_mode {
    GAME_MODE_NONE = 0,
    GAME_MODE_TOPVIEW,
    GAME_MODE_ROAMVIEW,
};


int game_mode = GAME_MODE_TOPVIEW;
*/

WORLD world = {
    .light = {
        .type = LIGHTSOURCE_TYPE_DIR,
        .dir = {
            .norm = {0.8, 1, 2},
            .amb = 0.2,
            .bright = 1.4,
        },
    },
};


CAMERA camera = {
    .pos = {0,0,0},
    .rot = {MATH_PI/2, MATH_PI, MATH_PI},
    .fov = DEG_TO_RAD(90),
    .type = CAMERA_PERSPECTIVE,
};

/*CAMERA camera_1 = {
    .pos = {0,0,-1},
    .rot = {0,0,0},
    .fov = DEG_TO_RAD(45),
    .type = CAMERA_PERSPECTIVE,
};

CAMERA camera_2 = {
    .pos = {0,0,0},
    .rot = {MATH_PI/2, MATH_PI, MATH_PI},
    .fov = DEG_TO_RAD(90),
    .type = CAMERA_PERSPECTIVE,
},*/





void init_scene(void);
EM_BOOL frame_loop(double t, void *user_data);
int __main(void);



//MODEL models[NUM_MODELS];
//void controls(double t, float dt);
//void update_camera(void);




EMSCRIPTEN_KEEPALIVE int main() {
    printf("starting webgl\n");

    int retval = __main();
    printf("main exited with code (%d)\n", retval);

    return retval;
}



//int swidth, sheight;
//vec3 wmin, wmax;




/*GLuint poly_program;
GLuint sphere_program;
GLuint bezier_program;
GLuint point_program;
GLuint fractal_program;
GLuint poly3d_program;
GLuint texplane_program;
GLuint texplane_dither_program;
GLuint maze_program;
GLuint mirror_program;
GLuint terrain_program;

SHADER poly_shader;
SHADER poly3d_shader;
SHADER maze_shader;
SHADER point_shader;
SHADER texplane_shader;
SHADER texplane_dither_shader;
SHADER mirror_shader;

ASSET nyan_asset;
ASSET rock_wall_tex_asset;
ASSET rock_wall_tex_asset_512;
ASSET rock_wall_norm_asset;
ASSET rock_wall_norm_asset_512;
ASSET test_norm_asset;
ASSET torch_asset;
ASSET cat_avatar_asset;
TEXTURE nyan_texture;
TEXTURE rock_wall_tex_512;
TEXTURE rock_wall_tex;
TEXTURE rock_wall_norm;
TEXTURE rock_wall_norm_512;
TEXTURE test_norm;
TEXTURE torch_tex;
TEXTURE cat_avatar_tex;

MAZE maze;


DRAWSURFACE mirror;*/


SHADER terrain_shader;
SHADER water_shader;


// assume mirror always points (0, -1, 0)
/*struct {
    vec3 pos;
    vec2 scale;
} mirror_prop;


void mirror_frame(DRAWSURFACE* surface, void* data, double t, float dt);
*/

//int swidth, sheight;


void _frame_loop(void);


/*EM_JS(float, calcFPS, (int count){
    var opts = {};
    
    var requestFrame = window.requestAnimationFrame ||
        window.webkitRequestAnimationFrame ||
        window.mozRequestAnimationFrame;
    if (!requestFrame) return true; // Check if "true" is returned; 
                                    // pick default FPS, show error, etc...
    function checker(){
        if (index--) requestFrame(checker);
        else {
            // var result = 3*Math.round(count*1000/3/(performance.now()-start));
            var result = count*1000/(performance.now()- start);
            if (typeof opts.callback === "function") opts.callback(result);
            //console.log("Calculated: "+result+" frames per second");
            return result
        }
    }
    //if (!opts) opts = {};
    //var count = opts.count||60, index = count, start = performance.now();
    var index = count, start = performance.now();
    checker();
}*/

//static float refresh_rate;


void terrain_draw_frame(SHADER* shader, double t, void* data);


int __main(void) {
    // set starting random seed
    srand((unsigned int)time(NULL));

    // remember, you wrote this function.
    int err = init_webgl("#" HTML_CANVAS_ID);
    ASSERT(err == 0, -1, "init_webgl failed\n");

    //emscripten_get_canvas_element_size(HTML_CANVAS_ID, &swidth, &sheight);


    // TODO: allow for different programs to share shader programs
    // so that it doesn't have to recompile every single one.
    // perhaps generate a function to compile them all, and then user
    // their shader id's in manually calling them to compile
    /*SHADER_DESCRIPTOR sdesc[] = {
        SHADER_DESC_GEN( false, &sphere_program,   sphere,  simple  ),
        SHADER_DESC_GEN( false, &bezier_program,   bezier,  simple  ),
        SHADER_DESC_GEN( false, &fractal_program,  poly,    fractal ),
        SHADER_DESC_GEN( false, &point_program,    point,   simple  ),
        SHADER_DESC_GEN( false, &poly_program,     poly,    poly    ),
        SHADER_DESC_GEN( false, &poly3d_program,   poly3d,  simple  ),
        SHADER_DESC_GEN( false, &texplane_program, texture, texture ),
        SHADER_DESC_GEN( false, &maze_program,     maze,    texture_lighting ),
        SHADER_DESC_GEN( false, &texplane_dither_program, texture, texture_dither ),
        SHADER_DESC_GEN( false, &mirror_program,   texture, mirror),
        SHADER_DESC_GEN( true, &terrain_program,  terrain, simple),
    };

    compile_shaders(LENOF(sdesc), sdesc);*/

    //shader_init(&poly_shader,     poly_program,     NULL, NULL);
    //shader_init(&poly3d_shader,   poly3d_program,   NULL, NULL);
    //shader_init(&point_shader,    point_program,    NULL, NULL);
    //shader_init(&texplane_shader, texplane_program, NULL, NULL);
    //shader_init(&maze_shader,     maze_program,     NULL, NULL);
    //shader_init(&texplane_dither_shader, texplane_dither_program, NULL, NULL);
    //shader_init(&mirror_shader, mirror_program, NULL, NULL);
    //shader_init(&terrain_shader, terrain_program, NULL, NULL);

    SHADER_DESCRIPTOR descriptor = SHADER_DESC_GEN(true, NULL,  terrain, simple);
    shader_init(&terrain_shader, &descriptor, terrain_draw_frame, 
        NULL, MESHTYPE_3D_VERT_NORM);


    // TODO: enable clockwise vertex order here or whatever
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_DITHER);
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glDisable(GL_MULTISAMPLE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    //glDepthRangef(1.0, 0.0);
    glDepthFunc(GL_GEQUAL);
    //glDepthFunc(GL_LESS);

    glClearDepthf(log2(-10000));

    //asset_load_jpg(&nyan_asset,           "/assets/nyan-cat.jpg");
    /*asset_load_img(&nyan_asset,           "crying-cat");
    asset_load_img(&rock_wall_tex_asset,  "rock-wall-white");
    asset_load_img(&rock_wall_norm_asset, "rock-wall-norm");
    asset_load_img(&rock_wall_tex_asset_512,  "rock-wall-white-512");
    asset_load_img(&rock_wall_norm_asset_512, "rock-wall-norm-512");
    asset_load_img(&test_norm_asset,      "test-norm");
    asset_load_img(&torch_asset,          "torch");
    asset_load_img(&cat_avatar_asset,     "cat-avatar");
    texture_init(&nyan_texture,   &nyan_asset,           TEX_NEAREST, TEX_DEFAULT);
    texture_init(&rock_wall_tex,  &rock_wall_tex_asset,  TEX_NEAREST, TEX_WRAP);
    texture_init(&rock_wall_tex_512,  &rock_wall_tex_asset_512,  TEX_NEAREST, TEX_WRAP);
    texture_init(&rock_wall_norm_512, &rock_wall_norm_asset_512, TEX_NEAREST, TEX_WRAP);
    texture_init(&rock_wall_norm, &rock_wall_norm_asset, TEX_NEAREST, TEX_WRAP);
    texture_init(&test_norm,      &test_norm_asset,      TEX_NEAREST, TEX_WRAP);
    texture_init(&torch_tex,      &torch_asset,          TEX_NEAREST, TEX_DEFAULT);
    texture_init(&cat_avatar_tex, &cat_avatar_asset,     TEX_NEAREST, TEX_DEFAULT);*/

    //glDisable(GL_CULL_FACE);
    //glDisable(GL_DEPTH_TEST);

    camera_init(&camera);
    //camera_init(&camera_1);
    //camera_init(&camera_2);
    //camera_init(&camera_static);
    //camera_init(&camera_mirror);
    //camera_init(&camera_3);
    input_init();
    shapes_init();
        
    init_scene();

    // set frame callback
    // a while loop would stall the webpage, so this is neccissary
    printf("starting animation frame loop\n");
    //emscripten_set_main_loop(&_frame_loop, 60, false);
    emscripten_set_main_loop(&_frame_loop, 0, false);
    //emscripten_set_main_loop(&_frame_loop, 1000, false);
    //emscripten_request_animation_frame_loop(&frame_loop, NULL);

    return 0;
}


void _frame_loop(void) {
    double _t = EM_ASM_DOUBLE({
        return performance.now();
    });
    frame_loop(_t, NULL);
}







//BEHAVE behave[NUM_MODELS];

void model_transform(MODEL* model);
void model_update_pipeline(double t, float dt);




#define UPDATE_DIVISOR 1

void update_frame_time(double _t, double* t, float* dt, float* fps) {
    static double t0;
    double _dt = _t - t0;
    t0 = _t;
    *t = _t/DT_DIVISOR;
    *dt = _dt/DT_DIVISOR;

    static float _fps = 0;
    _fps = (_fps*7 + 1000/(float)_dt)/8;
    *fps = _fps;
}






void init_scene(void) {
    // set background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    gen_model = (GEN_MODEL){
        .scale = 2.0,
        .rows = 500,//50,
        .cols = 500,//50,
        .x_off = -250,
        .y_off = -250,
        .sincount = 6,
    };

    gen_model.sindata[0] = (GEN_SINDATA){
        .period = 1,
        .height = 0.5,
        .power = 1,
        .damp_enable = true,
        .damp_period = 4,
    }; gen_model.sindata[1] = (GEN_SINDATA){
        .period = 2,
        .height = 1,
        .power = 1,
        .damp_enable = true,
        .damp_period = 8,
    }; gen_model.sindata[2] = (GEN_SINDATA){
        .period = 8,
        .height = 10,
        .power = 1,
        .damp_enable = true,
        .damp_period = 200,
    }; gen_model.sindata[3] = (GEN_SINDATA){
        .period = 32,
        .height = 50,
        .power = 8,
        .damp_enable = true,
        .damp_period = 100,
    }; gen_model.sindata[4] = (GEN_SINDATA){
        .period = 40,
        .height = 100,
        .power = 8,
        .damp_enable = true,
        .damp_period = 120,
    }; gen_model.sindata[5] = (GEN_SINDATA){
        .period = 30,
        .height = 80,
        .power = 1,
        .damp_enable = true,
        .damp_period = 140,
    };

    terrain_init(&terrain, (vec3){-250,-250,0}, (vec3){1,1,0.1},
        &gen_model, COLOR_GREEN, &terrain_shader);

    mouse.grabby = true;

    camera.pos[1] = 40;

    static GEN_MODEL water_model = (GEN_MODEL){
        .scale = 1.0,
        .rows = 500,
        .cols = 500,
    };

    terrain_init(&water, (vec3){-250,-250,-5}, (vec3){1,1,1},
        &water_model, COLOR_BLUE, &terrain_shader);
}





//void update_cam(void);

int frame_div = 1;


EM_BOOL frame_loop(double _t, void *user_data) {
    (void)user_data;

    double t;
    float dt;
    float fps;

    // update frame times
    update_frame_time(_t, &t, &dt, &fps);

    static int fps_count = 0;
    if ((fps_count++ % 60) == 0)
        printf("fps: %f\n", fps);

    /////////////////////////////////////////////
    //// UPDATE HIDDEN FRAMEBUFFER DRAWS  //////
    ///////////////////////////////////////////

    // lol. Nevermind.

    
    // TODO: add a function that will test for screen refresh rate
    // and then automatically adjust the frame divider using the current
    // frame per second to prevent overbudget frames, which messes up
    // stuff like player camera controls
    static bool bkey_debounce = true;
    if (key[KEY_B]) {
        if (bkey_debounce) {
            bkey_debounce = false;
            frame_div++;
            frame_div %= 5;
            if (frame_div == 0) frame_div = 1;
            printf("frames divided by %d\n", frame_div);
            emscripten_set_main_loop_timing(EM_TIMING_RAF, frame_div);
        }
    } else {
        bkey_debounce = true;
    }
    
    //////////////////////////
    //// UPDATE SCENE  //////
    ////////////////////////



    ///////////////////////////
    //// UPDATE CAMERA  //////
    /////////////////////////

    //update_cam();
    //camera_rotate_about(&camera, (vec3){0,0,0}, (vec3){0, 0, 0}, 3.0);

    // reference rotation vector
    //static vec3 ref = (vec3){0,0,1};

    if (mouse.grabbed) {
        camera.rot[1] += mouse.dx/100.0;
        camera.rot[0] += mouse.dy/100.0;
    }

    camera.rot[0] = CLAMP(camera.rot[0], MATH_PI/6, MATH_PI*7/6);
    //if (camera.rot[0] > MATH_PI*2/3) camera.rot[0] = MATH_PI*2/3;
    //if (camera.rot[0] < -MATH_PI*2/3) camera.rot[0] = -MATH_PI*2/3;
    
    //early camera update
    camera_update_actual(&camera);

    float tx = (key[KEY_RIGHT] || key[KEY_D]) - (key[KEY_LEFT] || key[KEY_A]);
    float ty = (key[KEY_UP]    || key[KEY_W]) - (key[KEY_DOWN] || key[KEY_S]);
    float tz = key[KEY_SPACE] - key[KEY_CTRL];
    //float pythag = sqrt(tx*tx + ty*ty + tz*tz);
    //float mul = (key[KEY_SHIFT] ? (5) : (1)) / 10.0 / pythag;

    // get unrotated player translation
    //vec3 vel = (vec3){tx * mul, ty * mul, 0};
    vec3 vel = (vec3){tx, ty, 0};

    // extract camera direction
    /*vec3 camdir;
    glm_vec3_copy(camera.viewmat[2], camdir);
    //glm_vec3_negate(camdir);

    // rotate velocity vector according to direction and reference vector
    vec3 mov, cross;
    float angle = glm_vec3_angle(ref, camdir);
    glm_vec3_crossn(ref, camdir, cross);
    glm_vec3_copy(vel, mov);
    glm_vec3_rotate(mov, angle, cross);
    //printf("%f %f %f %f\n", angle, cross[0], cross[1], cross[2]);
    printf("%f %f %f %f\n", angle, mov[0], mov[1], mov[2]);*/

    glm_vec3_rotate(vel, -(camera.rot[0]-MATH_PI/2.0), (vec3){1,0,0});
    glm_vec3_rotate(vel, -(camera.rot[1]-MATH_PI), (vec3){0,0,1});
    vel[2] += tz;

    float mul = (key[KEY_SHIFT] ? (5.0) : (1.0)) / 10.0 / glm_vec3_norm(vel);
    mul *= dt*6;

    glm_vec3_scale(vel, mul, vel);

    //printf("%f %f\n", camera.rot[0], camera.rot[1]);

    if (!(isnan(vel[0]) || isnan(vel[1]) || isnan(vel[2])))
        glm_vec3_add(camera.pos, vel, camera.pos);
    
    // final camera update;
    camera_update_actual(&camera);

    terrain_update(&terrain, t, dt);
    terrain_update(&water, t, dt);

    //glm_vec3_rotate(world.light.dir.norm, 0.01, (vec3){0,1,0});

    //////////////////////////
    //// DRAW SCENE  ////////
    ////////////////////////




    // clear the scene
    // note that with the new framebuffer draws, this is neccissary otherwise
    // weird overlap is going to occur
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glClear(GL_DEPTH_BUFFER_BIT);


    
    

    //camera_apply(&camera, poly_program);
    //camera_apply(&camera, poly3d_program);
    //camera_apply(&camera, point_program);
    //camera_apply(&camera, texplane_program);
    //camera_apply(&camera, texplane_dither_program);
    //camera_apply(&camera, maze_program);
    //camera_apply(&camera, mirror_program);

    camera_apply(&camera, terrain_shader.program);

    shader_draw(&terrain_shader, t);

    //draw_rect2((vec3){-250,-250,-5}, (vec3){500,500}, NULL, 0, COLOR_BLUE, &terrain_shader);


   
    
    
    // requests frame buffer swap. Will actually render stuff to screen
    // this is neccissary because explicitSwapControl was set to GL_TRUE
    emscripten_webgl_commit_frame();
    input_refresh();

    // return true to keep looping
    // return false to kill loop
    return EM_TRUE;
}





void terrain_draw_frame(SHADER* shader, double t, void* data) {
    // apply camera
    camera_apply(&camera, shader->program);
    // apply lightsource
    //lightsource_apply(&world.light, shader->program);
    lightsource_apply_spectral(&world.light, shader->program, &camera, 0.2, 10.0);
    terrain_draw(&terrain, t);
    
    lightsource_apply_spectral(&world.light, shader->program, &camera, 1.0, 1000.0);
    terrain_draw(&water, t);
}





