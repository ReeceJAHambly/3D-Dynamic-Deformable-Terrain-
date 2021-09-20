#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform vec3 Color;

out vec3 pos;
out vec3 Normal;
out vec3 vcolor;
out vec4 tcolor;

float noise(vec2 p);

void main() {
	pos = position;
	Normal = normal;
	
	gl_Position = projection * view * model * vec4(position, 1.0f);
	
	float p = (position.y + 10.0)/15.0;
	vcolor = vec3(0.75*(abs(0.5-p))+0.25,p,0.5*p+0.25);

	//float c = .1 + (2.0 * noise(vec2(position.x,position.z)) - 1.0);
	/*if(mod(position.z, 16) == 0)
	{
		vcolor = vec3(1.0,1.0,1.0);
	}
	else if(mod(position.x,16) == 0)
	{
		vcolor = vec3(1.0,1.0,1.0);
	}*/

	if(position.y == -2.5)
	{
		vcolor = vec3(0.0,0.6,1.0);// + vec3(c * .05); 
	}
}

float rand(vec2 n) { 
	return fract(sin(dot(n, vec2(12.9898, 4.1414))) * 43758.5453);
}

float noise(vec2 p){
	vec2 ip = floor(p);
	vec2 u = fract(p);
	u = u*u*(3.0-2.0*u);
	
	float res = mix(
		mix(rand(ip),rand(ip+vec2(1.0,0.0)),u.x),
		mix(rand(ip+vec2(0.0,1.0)),rand(ip+vec2(1.0,1.0)),u.x),u.y);
	return res*res;
}