#ifdef VERTEX
attribute vec3 in_Position;
attribute vec3 in_Normal;

varying vec3 out_FragPos;
varying vec3 out_Normal;

uniform mat4 in_Projection;
uniform mat4 in_Model;
uniform mat4 in_View;

	void main()
	{
		out_FragPos = vec3(in_Model * vec4(in_Position, 1.0);
		out_Normal = in_Normal;
		
		gl_Position = in_Projection * in_View * vec4(out_FragPos, 1.0);
	}
#endif
#ifdef FRAGMENT
varying vec4 FragColour;

attribute vec3 in_Normal;
attribute vec3 in_FragPos;

uniform vec3 in_LightPos;
uniform vec3 in_ViewPos;
uniform vec3 in_LightColour;
uniform vec3 in_ObjectColour;

	void main()
	{
		//ambient
		float ambientStrength = 0.1;
		vec3 ambient = ambientStrength * in_LightColour;
		
		//diffuse
		vec3 norm = normalize(in_Normal);
		vec3 lightDir = normalize(in_LightPos - in_FragPos);
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = diff * in_LightColour;
		
		// specular
		float specularStrength = 0.5;
		vec3 viewDir = normalize(in_ViewPos - in_FragPos);
		vec3 reflectDir = reflect(-lightDir, norm);  
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
		vec3 specular = specularStrength * spec * in_LightColour; 
		
		vec3 result = (ambient + diffuse) * objectColour;
		FragColour = vec4(result, 1.0);
	}
#endif