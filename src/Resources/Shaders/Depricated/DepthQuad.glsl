#ifdef VERTEX
attribute vec3 in_Position;
attribute vec2 in_TexCoords;

varying vec2 TexCoords;

void main()
{
    TexCoords = in_TexCoords;
    gl_Position = vec4(in_Position, 1.0);
}
#endif
#ifdef FRAGMENT
varying vec4 ex_FragColor;

varying vec2 TexCoords;

uniform sampler2D in_DepthMap;
uniform float in_NearPlane;
uniform float in_FarPlane;

// required when using a perspective projection matrix
float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // Back to NDC 
    return (2.0 * near_plane * far_plane) / (far_plane + near_plane - z * (far_plane - near_plane));	
}

void main()
{             
    float depthValue = texture(depthMap, TexCoords).r;
    // FragColor = vec4(vec3(LinearizeDepth(depthValue) / far_plane), 1.0); // perspective
    FragColor = vec4(vec3(depthValue), 1.0); // orthographic
}
#endif