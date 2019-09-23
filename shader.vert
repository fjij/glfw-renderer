#version 110
uniform mat4 MVP;
attribute vec3 vCol;
attribute vec2 vPos;
attribute float time;
varying vec3 color;
void main()
{
    gl_Position = MVP * vec4(vPos, 0.0, 0.1);
    color = vCol;
}
