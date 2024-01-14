#version 330 core
layout(location=0) in vec2 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 text_coord;
out vec3 fragColor; // New color attribute
out vec2 texture_coord; // New texture coord attribute
uniform float scale; //scaling factor
void main()
{
	gl_Position = vec4(position.x*scale,position.y*scale,0.0,1.0);
	fragColor = color;
	texture_coord = text_coord;
};