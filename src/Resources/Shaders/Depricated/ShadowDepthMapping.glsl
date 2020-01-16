#ifdef VERTEX
attribute vec3 in_Position;

uniform mat4 in_LightSpaceMatrix;
uniform mat4 in_Model;

void main()
{
    gl_Position = in_LightSpaceMatrix * in_Model * vec4(in_Position, 1.0);
}
#endif
#ifdef FRAGMENT
void main()
{             
    gl_FragDepth = gl_FragCoord.z;
}
#endif