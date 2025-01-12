precision mediump float;

//attribute vec2 vertPosition;
//uniform mat4 uModelViewMatrix;
//uniform mat4 uProjectionMatrix;

attribute vec2 vert_pos;
uniform mat4 u_mod_view_mat;
uniform mat4 u_proj_mat;

void main() {
    gl_Position = u_proj_mat * u_mod_view_mat * vec4(vert_pos, 0.0, 1.0);
}
