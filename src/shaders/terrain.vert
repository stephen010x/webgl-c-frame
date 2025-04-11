precision mediump float;

attribute vec3 vert_pos;
attribute vec3 vert_norm;

uniform mat4 u_proj_mat;
uniform mat4 u_mod_mat;
uniform mat3 u_norm_mat;
uniform vec4 u_color;

uniform float u_tex_scale;

varying vec4 v_color;
varying vec2 v_norm_coord;  // interpolated per vertex norm image coords
varying vec3 v_coords3;     // interpolated fragment 3d coords
varying float v_depth;

varying vec3 T;
varying vec3 B;
varying vec3 N;




void main() {
    ////////////////////////////
    // vertex and normal translations
    
    // pass 3d coords to fragment shader
    vec4 coords3 = u_mod_mat * vec4(vert_pos, 1.0);
    v_coords3 = coords3.xyz / coords3.w;
    
    // translate vertex for rasterization
    vec4 pos = u_proj_mat * coords3;




    ////////////////////////////
    // set gl_Position

    // set depth to be logrithmic
    //gl_Position.z = 1.0/gl_Position.z;
    gl_Position = vec4(pos.xy, log2(pos.z), pos.w);
    //gl_Position = pos;




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
    
    v_norm_coord = v_coords3.xy / u_tex_scale;
    v_color = u_color;
    v_depth = pos.z;
}





