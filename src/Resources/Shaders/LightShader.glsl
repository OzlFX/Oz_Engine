#ifdef VERTEX
layout (location = 0) in vec3 in_Pos;
layout (location = 1) in vec3 in_Normal;

out vec3 out_FragPos;
out vec3 out_Normal;

uniform mat4 out_Projection;
uniform mat4 out_Model;
uniform mat4 out_View;

	void main()
	{
		out_FragPos = vec3(out_Model * vec4(in_Pos, 1.0);
		out_Normal = in_Normal;
		
		gl_Position = out_Projection * out_View * vec4(out_FragPos, 1.0);
	}
#endif
#ifdef FRAGMENT
out vec4 FragColour;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightPos;
uniform vec3 lightColour;
uniform vec3 objectColour;

	void main()
	{
		//ambient
		float ambientStrength = 0.1;
		vec3 ambient = ambientStrength * lightColour;
		
		//diffuse
		vec3 norm = normalize(Normal);
		vec3 lightDir = normalize(lightPos - FragPos);
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = diff * lightColour;
		
		vec3 result = (ambient + diffuse) * objectColour;
		FragColour = vec4(result, 1.0);
	}
#endif