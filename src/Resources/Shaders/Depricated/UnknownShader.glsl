#ifdef VERTEX
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
#endif
#ifdef FRAGMENT
uniform sampler2D in_Texture;

varying vec3 var_Normal;
varying vec2 var_TexCoord;

	void main()
	{
		gl_FragColor = texture2D(in_Texture, var_TexCoord);
		if(gl_FragColor.x == 9) gl_FragColor.x = var_Normal.x;
	}
#endif