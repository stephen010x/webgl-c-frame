precision mediump float;

uniform vec3 u_light_norm;
uniform float u_light_amb;
uniform float u_light_bright;
uniform float u_light_spec_bright;
uniform float u_light_spec_pow;
uniform vec3 u_cam_pos;

uniform bool u_enable_vfog;
uniform float u_tex_scale;
uniform float u_tex_strength;
uniform sampler2D u_norm0;

varying vec4 v_color;
varying vec2 v_norm_coord;  // interpolated per vertex norm image coords
varying vec3 v_coords3;     // interpolated fragment 3d coords
varying float v_depth;

varying vec3 T;
varying vec3 B;
varying vec3 N;


vec3 color_to_norm(vec4 color);
vec4 norm_to_color(vec3 norm);

//float round(float n);
//vec2 round(vec2 n);
//vec3 round(vec3 n);
vec2 vfloor(vec2 n);



void main() {

    ////////////////////////////
    // translate normal vector to model space
    
    mat3 TBN = mat3(normalize(T), normalize(B), normalize(N));
    //vec4 norm_color = texture2D(u_norm0, vfloor(v_norm_coord/v_depth/1000.0)*v_depth);
    vec4 norm_color = texture2D(u_norm0, v_norm_coord);
    //vec4 norm_color = texture2DLod(u_norm0, v_norm_coord/100.0, 1);
    vec3 prenorm = color_to_norm(norm_color);
    vec3 norm = normalize(TBN * normalize(vec3(prenorm.xy, prenorm.z / u_tex_strength)));
    //norm = vec3(norm.zy, norm.z * u_tex_scale);
    //norm = N;
    //norm = TBN * vec3(0.0,0.0,1.0);



    ////////////////////////////
    // calculate lighting
    
    vec3 light_norm = normalize(u_light_norm);

    // calculate diffuse light
    float diffuse = max(dot(norm, light_norm), 0.0); 
    
    // calculate specular light
    float specular = 0.0;
    if (diffuse > 0.0) {
        vec3 half_norm = normalize(light_norm + normalize(-v_coords3+u_cam_pos));
        float spec_angle = max(dot(half_norm, norm), 0.0);
        specular = pow(spec_angle, u_light_spec_pow);
    }

    // calculate ambience
    float ambient = u_light_amb;

    // calculate backlight
    //float backlight = max(dot(norm, vec3(-light_norm.xy*2.0, light_norm.z)), 0.0)/4.0;
    float backlight = 0.0;



    ////////////////////////////
    // calculate final color value
    
    //vec4 color = norm_to_color(normalize(T));
    //vec4 color = norm_to_color(norm);
    vec4 color = v_color;
    color = vec4(color.rgb * (diffuse + backlight) * u_light_bright + 
                specular * u_light_spec_bright + ambient, color.a);
    color = clamp(color, 0.0, 1.0);

    
    
    
    gl_FragColor = color;
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
