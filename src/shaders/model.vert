#version 300 es
precision mediump float;

layout(location = 0) in vec3 vert_pos;
layout(location = 1) in vec3 vert_norm;
layout(location = 2) in vec2 vert_tex;

uniform mat4 u_proj_mat;
uniform mat4 u_mod_mat;
uniform mat3 u_norm_mat;
uniform vec4 u_color;

//uniform float u_tex0_scale;

out vec4 v_color;
out vec2 v_tex_coord;   // interpolated per vertex norm image coords
out vec3 v_coords3;     // interpolated fragment 3d coords
out float v_depth;

out vec3 T;
out vec3 B;
out vec3 N;


void main() {

    ////////////////////////////
    // vertex and normal translations
    
    // pass 3d coords to fragment shader
    vec4 coords3 = u_mod_mat * vec4(vert_pos.xy, vert_pos.z, 1.0);
    v_coords3 = coords3.xyz / coords3.w;
    
    // translate vertex for rasterization
    vec4 pos = u_proj_mat * coords3;




    ////////////////////////////
    // set gl_Position

    gl_Position = pos;




    ////////////////////////////
    // calculate TBN matrix

    // set normal
    // rotate normal according to model matrix
    N = normalize(u_norm_mat * vert_norm);

    // select temporary fake tangent
    // avoid colinearity
    T = vec3(1.0, 0.0, 0.0);
    if (abs(N.x) > 0.999)
        T = vec3(0.0, 1.0, 0.0);

    // set bitangent vector
    B = normalize(cross(N, T));

    // set real tangent
    T = normalize(cross(B, N));




    ////////////////////////////
    // calculate normal coords and per-vertex color
    
    v_tex_coord = vert_tex;
    v_color = u_color;
    v_depth = pos.z;

}





