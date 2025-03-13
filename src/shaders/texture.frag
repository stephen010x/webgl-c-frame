precision mediump float;

uniform sampler2D tex0;

varying vec4 color;
varying vec3 norm;
varying vec2 tex_coord;

void main() {
    gl_FragColor = texture2D(tex0, tex_coord);
    //gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);
}
