#version 310 es
precision mediump float;
layout(location = 0) out vec4 fragColor;

void main()
{
	fragColor = vec4(gl_FragCoord.z);
}