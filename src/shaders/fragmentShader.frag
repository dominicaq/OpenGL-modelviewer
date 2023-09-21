#version 430 core
out vec4 FragColor;

uniform struct Light {
   vec3 position;
   vec3 color; //a.k.a the color of the light
} light;

uniform sampler2D texture0;
in vec2 texCoord;

in vec3 FragPos;
in vec3 FragNorm;
in vec3 FragView;

float ka = .2, kd = 1, ks = 1;
int shine = 32;

void main()
{
	// Ambient
	vec3 ambient = light.color;

	// Diffuse
	vec3 L = normalize(light.position - FragPos);
	vec3 N = normalize(FragNorm);
	float diffuse = max(dot(L,N), 0.0);

	// Specular
	float specular = 0.0;
	vec3 V = normalize(FragView - FragPos); // Vector to viewer
	vec3 R = reflect(-L, N);      // Reflected light vector
	float specAngle = max(dot(V, R), 0.0);
	specular = pow(specAngle, shine);

	vec4 tex = texture(texture0, texCoord);
	
	FragColor = tex * vec4(ka * ambient + 
					 	   kd * diffuse + 
					 	   ks * specular
					 	   ,1.0);
}

