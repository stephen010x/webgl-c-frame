#version 300 es
precision mediump float;
//#extension GL_OES_standard_derivatives : enable
//#extension GL_EXT_shader_texture_lod : enable

uniform vec3 u_light_norm;
uniform float u_light_amb;
uniform float u_light_bright;
uniform float u_light_spec_bright;
uniform float u_light_spec_pow;
uniform vec4 u_light_diff_color;
uniform vec4 u_light_amb_color;
uniform vec3 u_cam_pos;

uniform bool u_enable_vfog;
uniform bool u_enable_texture;
uniform bool u_enable_occlusion;
uniform bool u_enable_normals;

uniform float u_tex0_scale;
uniform float u_tex0_strength;
uniform sampler2D u_tex0_tex;
uniform sampler2D u_tex0_norm;
// TODO: rename occl to amb
uniform sampler2D u_tex0_occl;
uniform sampler2D u_tex0_disp;

in vec4 v_color;
in vec2 v_tex_coord;  // interpolated per vertex norm image coords
in vec3 v_coords3;     // interpolated fragment 3d coords
in float v_depth;

in vec3 T;
in vec3 B;
in vec3 N;

out vec4 o_color;



vec3 color_to_norm(vec4 color);
vec4 norm_to_color(vec3 norm);

//float round(float n);
//vec2 round(vec2 n);
//vec3 round(vec3 n);
vec2 vfloor(vec2 n);



void main() {

    // calculate lod
    /*vec2 dithercoord = v_tex_coord.xy / u_ditherscale;
    float dmul = 1.0/1.5;
    vec2 dudx = dFdx(dithercoord/dmul);
    vec2 dldy = dFdy(dithercoord/dmul);
    float delta_max = max(dot(dudx, dudx), dot(dldy, dldy));
    float lod = 0.5 * log2(delta_max);
    float flod2 = exp2(floor(max(lod+0.5, 0.0)));*/

    // calculate dither
    /*int k;
    ivec2 index = ivec2(mod(dithercoord/flod2, vec2(4.0)));
    k = int(u_dithermat[index.x][index.y]);*/


    

    vec2 tex_coord0 = v_tex_coord / u_tex0_scale;
    
    vec2 dx0 = dFdx(tex_coord0);
    vec2 dy0 = dFdy(tex_coord0);
    

    float tex_strength = u_tex0_strength;
    vec4 norm_color = u_enable_normals ? textureGrad(u_tex0_norm, tex_coord0, dx0, dy0) : 
        norm_to_color(vec3(0.0, 0.0, 1.0));
    vec4 tex_color  = u_enable_texture ? textureGrad(u_tex0_tex, tex_coord0, dx0, dy0) : vec4(1.0);
    vec4 occl_color = u_enable_occlusion ? textureGrad(u_tex0_occl, tex_coord0, dx0, dy0) : vec4(1.0);




    ////////////////////////////
    // translate normal vector to model space
    
    mat3 TBN = mat3(normalize(T), normalize(B), normalize(N));
    vec3 prenorm = color_to_norm(norm_color);
    vec3 norm = normalize(TBN * normalize(vec3(prenorm.xy, prenorm.z / tex_strength)));




    ////////////////////////////
    // calculate lighting
    
    vec3 light_norm = normalize(u_light_norm);
    vec3 backlight_norm = vec3(-light_norm.x/2.0, -light_norm.y/2.0, -light_norm.z/2.0);

    // calculate diffuse light
    vec3 diffuse = max(dot(norm, light_norm), 0.0) * u_light_bright * u_light_diff_color.rgb; 
    
    // calculate specular light
    vec3 specular = vec3(0.0);
    if (diffuse.x > 0.0 || diffuse.y > 0.0 || diffuse.z > 0.0) {
        vec3 half_norm = normalize(light_norm + normalize(-v_coords3+u_cam_pos));
        float spec_angle = max(dot(half_norm, norm), 0.0);
        specular = pow(spec_angle, u_light_spec_pow) * u_light_spec_bright * u_light_diff_color.rgb;
    }

    // calculate ambience
    vec3 ambient = u_light_amb * u_light_amb_color.rgb * occl_color.rgb;

    // calculate backlight
    vec3 backlight = max(dot(norm, backlight_norm), 0.0) * u_light_bright * u_light_amb_color.rgb / 2.0;


    ////////////////////////////
    // calculate final color value
    
    vec4 color = v_color * tex_color;
    color = vec4(color.rgb * (diffuse + ambient + backlight) + specular, color.a);
    color = clamp(color, 0.0, 1.0);
    
    o_color = color;
    //o_color = norm_to_color(normalize(TBN*vec3(0.0, 0.0, 1.0)));
    //o_color = norm_to_color(TBN * vec3(prenorm.xy, prenorm.z));

    //o_color = norm_to_color(norm);
}






vec3 color_to_norm(vec4 color) {
    vec3 norm = normalize(color.rgb * 2.0 - 1.0);
    return vec3(norm.x, norm.y, norm.z);
    //return vec3(norm.x, norm.y, norm.z);
}


vec4 norm_to_color(vec3 norm) {
    vec3 _norm = vec3(norm.x, norm.y, norm.z);
    return vec4(clamp((_norm + 1.0) / 2.0, 0.0, 1.0), 1.0);
    //return vec4(clamp((norm + 1.0) / 2.0, 0.0, 1.0), 1.0);
}

vec2 vfloor(vec2 n) {
    return vec2(floor(n.x), floor(n.y));
}
