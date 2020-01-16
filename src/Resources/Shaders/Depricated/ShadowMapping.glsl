#ifdef VERTEX
uniform mat4 in_Projection;
uniform mat4 in_Model;
uniform mat4 in_View;
uniform mat4 in_LightSpaceMatrix;

attribute vec3 in_Position;
attribute vec2 in_TexCoord;
attribute vec3 in_Normal;

varying vec2 ex_TexCoord;
varying vec3 ex_FragPos;
varying vec3 ex_Normal;
varying vec4 ex_FragPosLightSpace;

void main()
{
  ex_FragPos = vec3(in_Model * vec4(in_Position, 1.0));
  ex_Normal = mat3(in_Model) * in_Normal;
  ex_TexCoord = in_TexCoord;
  ex_FragPosLightSpace = in_LightSpaceMatrix * vec4(ex_FragPos, 1.0);
  gl_Position = in_Projection * in_View * in_Model * vec4(in_Position, 1.0);
}
#endif
#ifdef FRAGMENT
varying vec4 ex_FragColor;

varying vec2 in_TexCoord;
varying vec3 in_FragPos;
varying vec3 in_Normal;
varying vec4 in_FragPosLightSpace;

uniform sampler2D in_DiffuseTexture;
uniform sampler2D in_ShadowMap;

uniform vec3 in_LightPos;
uniform vec3 in_ViewPos;

float ShadowCalculation(vec4 fragPosLightSpace)
{
    // perform perspective divide
    vec3 projCoords = in_FragPosLightSpace.xyz / in_FragPosLightSpace.w;
	
    // transform to [0,1] range (slightly inefficient and could cause issues)
    projCoords = projCoords * 0.5 + 0.5;
	
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture2D(in_ShadowMap, projCoords.xy).r;
	
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
	
    // calculate bias (based on depth map resolution and slope)
    vec3 normal = normalize(in_Normal);
    vec3 lightDir = normalize(in_LightPos - in_FragPos);
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
	
    // check whether current frag pos is in shadow
    // float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;
    // PCF
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(in_ShadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture2D(in_ShadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;        
        }    
    }
    shadow /= 9.0;
    
    // keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
    if(projCoords.z > 1.0)
        shadow = 0.0;
        
    return shadow;
}

void main()
{           
    vec3 color = texture2D(in_DiffuseTexture, in_TexCoord).rgb;
    vec3 normal = normalize(in_Normal);
    vec3 lightColor = vec3(0.3);
	
    // ambient
    vec3 ambient = 0.3 * color;
	
    // diffuse
    vec3 lightDir = normalize(in_LightPos - in_FragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * lightColor;
	
    // specular
    vec3 viewDir = normalize(in_ViewPos - in_FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
    vec3 specular = spec * lightColor; 
	
    // calculate shadow
    float shadow = ShadowCalculation(in_FragPosLightSpace);                      
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;    
    
    ex_FragColor = vec4(lighting, 1.0);
}
#endif