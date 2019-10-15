#version 310 es
precision mediump float;
out vec4 fragColor;

in vec2 fTexCoord;

uniform sampler2D diffuseMap_0;

void main()
{
    fragColor = texture(diffuseMap_0, fTexCoord);
}