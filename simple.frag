#version 330 core
// Cours de Realite Virtuelle
// leo.donati@unice.fr
//
// 2016_2017

in vec4 out_color;
out vec4 fragColor;

void main(void)
{
    fragColor = out_color.rgba;
}
