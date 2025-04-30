#version 300 es
precision mediump float;

uniform vec4 u_wire_color;
uniform float u_wire_range;

in vec3 v_coords3;     // interpolated fragment 3d coords
in float v_depth;

out vec4 out_color;


vec4 norm_to_color(vec3 norm);

void main() {
    //gl_FragColor = vec4(u_wire_color.rgb, 1.0 - u_wire_color.a * v_depth / u_wire_range);
    float intensity = 1.0 - v_depth / u_wire_range;
    out_color = vec4(u_wire_color.rgb * intensity, 1.0);
    //out_color = vec4(u_wire_color.rgb*(1.0 - v_depth / u_wire_range), 1.0);
}



vec4 norm_to_color(vec3 norm) {
    vec3 _norm = vec3(norm.x, norm.y, norm.z);
    return vec4(clamp((_norm + 1.0) / 2.0, 0.0, 1.0), 1.0);
    //return vec4(clamp((norm + 1.0) / 2.0, 0.0, 1.0), 1.0);
}
