#ifdef VERTEX
attribute vec3 in_Position;
attribute vec3 in_Normal;
attribute vec3 in_TexCoord;

out VS_OUT {
    vec3 out_FragPos;
    vec3 out_Normal;
    vec2 out_TexCoords;
} vs_out;

uniform mat4 in_Projection;
uniform mat4 in_View;

	void main()
	{
		vs_out.out_FragPos = in_Position;
		vs_out.out_Normal = in_Normal;
		vs_out.out_TexCoords = in_TexCoord;
		
		gl_Position = in_Projection * in_View * vec4(in_Position, 1.0);
	}
#endif
#ifdef FRAGMENT
varying vec4 FragColour;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} fs_in;

uniform sampler2D in_Texture;
uniform vec3 in_LightPos;
uniform vec3 in_ViewPos;
uniform bool blinn;

	void main()
	{
		vec3 colour = texture(in_Texture, fs_in.TexCoords).rgb;
		
		// ambient
		vec3 ambient = 0.05 * colour;
		
		// diffuse
		vec3 lightDir = normalize(in_LightPos - fs_in.FragPos);
		vec3 normal = normalize(fs_in.Normal);
		float diff = max(dot(lightDir, normal), 0.0);
		vec3 diffuse = diff * colour;
		
		// specular
		vec3 viewDir = normalize(in_ViewPos - fs_in.FragPos);
		vec3 reflectDir = reflect(-lightDir, normal);
		float spec = 0.0;
		
		if(blinn)
		{
			vec3 halfwayDir = normalize(lightDir + viewDir);  
			spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
		}
		else
		{
			vec3 reflectDir = reflect(-lightDir, normal);
			spec = pow(max(dot(viewDir, reflectDir), 0.0), 8.0);
		}
		
		vec3 specular = vec3(0.3) * spec; // assuming bright white light color
		FragColor = vec4(ambient + diffuse + specular, 1.0);
	}
#endif