#version 330 core

layout(location=0) in vec3 vertex;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 texcoord;
layout(location=3) in vec4 color;
out vec3 vert;
out vec3 vertNormal;
out vec4 col;
uniform mat4 projMatrix;
uniform mat4 mvMatrix;
uniform mat3 normalMatrix;

void main() {
   vert = vertex;
   vertNormal = normalMatrix * normal;
   gl_Position = projMatrix * mvMatrix * vec4(vertex, 1.0);
   col = color;
}
