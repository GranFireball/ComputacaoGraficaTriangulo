#version 330

out vec4 color;
in vec4 vColor;
in vec2 TexCord;
uniform vec3 triangleColor;
uniform sampler2D theTexture;

void main(){
	color = texture(theTexture, TexCord);
}