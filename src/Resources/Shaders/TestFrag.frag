uniform sampler2D out_Texture;

varying vec3 var_Normal;
varying vec2 var_TexCoord;

	void main()
	{
		gl_FragColor = texture2D(out_Texture, var_TexCoord);
		if(gl_FragColor.x == 9) gl_FragColor.x = var_Normal.x;
	}