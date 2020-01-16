#ifdef VERTEX
uniform mat4 in_Projection;
uniform mat4 in_View;
uniform mat4 in_Model;

attribute vec3 in_Position;
attribute vec2 in_TexCoord;

varying vec2 ex_TexCoord;

void main()
{
  gl_Position = in_Projection * in_View * in_Model * vec4(in_Position, 1.0);
  ex_TexCoord = in_TexCoord;
}
#endif
#ifdef FRAGMENT
uniform sampler2D in_Texture;

varying vec2 ex_TexCoord;

void main()
{
  vec4 tex = texture2D(in_Texture, ex_TexCoord);
  
  if(tex.w != 1)
  {
	discard;
  }
  
  gl_FragColor = tex;
}
#endif