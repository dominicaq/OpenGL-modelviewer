#version 430 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

/* Uniforms */
uniform mat4 model, view, projection;

out vec2 texCoord;
out vec3 FragNorm;
out vec3 FragPos;
out vec3 FragView;

void main() 
{
	FragNorm = mat3(transpose(inverse(model))) * aNormal;
	FragView = vec3(view);
	FragPos  = aPosition;
	texCoord = aTexCoord;

	gl_Position = projection * view * model * vec4(aPosition, 1.0);	
}