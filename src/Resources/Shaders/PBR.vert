#version 330
uniform mat4 in_Projection;
uniform mat4 in_View;
uniform mat4 in_Model;

in vec3 in_Position;
in vec2 in_TexCoord;
in vec3 in_Normal;

out vec2 ex_TexCoord;
out vec3 ex_FragPos;
out vec3 ex_Normal;

void main()
{
	gl_Position =  in_Projection * in_View * vec4(ex_FragPos, 1.0);
    ex_TexCoord = in_TexCoord;
    ex_FragPos = vec3(in_Model * vec4(in_Position, 1.0));
    ex_Normal = mat3(in_Model) * in_Normal;   
}