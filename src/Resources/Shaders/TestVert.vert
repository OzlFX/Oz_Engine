attribute vec3 in_Position;
attribute vec2 in_TexCoord;
attribute vec3 in_Normal;

uniform mat4 out_Projection;
uniform mat4 out_Model;

varying vec3 var_Normal;
varying vec2 var_TexCoord;

	void main()
	{
		gl_Position = out_Projection *
		 out_Model * vec4(in_Position, 1);
		 
		var_Normal = in_Normal;
		var_TexCoord = in_TexCoord;
	}