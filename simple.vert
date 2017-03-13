#version 330 core
// Cours de Réalité Virtuelle
// leo.donati@unice.fr
//
// 2016_2017
//

layout(location=0) in vec3 pos;
layout(location=1) in vec3 col;
out vec4 out_color;
uniform mat4 u_ModelViewProjectionMatrix;
uniform float u_opacity;

void main(void)
{
   gl_Position = u_ModelViewProjectionMatrix * vec4(pos, 1);
   out_color = vec4(col,u_opacity);
}
