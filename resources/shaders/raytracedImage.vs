#version 330 core
layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 texCoordIn;

out vec2 texCoord;

void main()
{
	texCoord = texCoordIn;
	gl_Position = vec4(pos, 0.0, 1.0);
}