precision mediump float;

attribute vec2 vertPosition;
attribute vec3 vertColor;
varying vec3 fragColor;
uniform mat4 u_proj_mat;
uniform mat4 u_mod_view_mat;

void main() {
    fragColor = vertColor;
    gl_Position = u_proj_mat * u_mod_view_mat * vec4(vertPosition, 0.0, 1.0);
}
