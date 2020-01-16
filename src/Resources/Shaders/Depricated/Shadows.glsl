#ifdef VERTEX
uniform mat4 in_Projection;
uniform mat4 in_Model;
uniform mat4 in_View;

attribute vec3 in_Position;
attribute vec2 in_TexCoord;
attribute vec3 in_Normal;

varying vec2 ex_TexCoord;
varying vec3 ex_FragPos;
varying vec3 ex_Normal;


void main(){
  gl_Position = in_Projection * in_View * in_Model * vec4(in_Position, 1.0);
  ex_TexCoord = in_TexCoord;
  ex_Normal = mat3(in_Model) * in_Normal;
  ex_FragPos = vec3(in_Model * vec4(in_Position, 1.0));
}
#endif
#ifdef FRAGMENT
uniform sampler2D in_Texture;
uniform mat4 in_View;
uniform float in_FarPlane;
uniform float in_NearPlane;

varying vec2 ex_TexCoord;
varying vec3 ex_FragPos;
varying vec3 ex_Normal;

#define NO_POINT_LIGHTS 2
uniform samplerCube in_ShadowMaps[NO_POINT_LIGHTS];

struct PointLight{
  vec3 in_Pos;

  vec3 in_Emissive;
  vec3 in_Ambient;
  vec3 in_Specular;
  vec3 in_Diffuse;

  float in_Constant;
  float in_Linear;
  float in_Quadratic;

  mat4 in_View;
};

uniform PointLight in_Lights[NO_POINT_LIGHTS];

struct DirectionalLight{
  vec3 in_Dir;

  vec3 in_Emissive;
  vec3 in_Ambient;
  vec3 in_Specular;
  vec3 in_Diffuse;
};
#define NO_DIR_LIGHTS 1
uniform DirectionalLight in_DirLights[NO_DIR_LIGHTS];

vec3 calcPointLights(PointLight light, vec3 norm, samplerCube shadowMap);
vec3 calcDirLights(DirectionalLight light, vec3 norm);

float ShadowCalculation(vec3 fragPos, samplerCube shadowMap, vec3 lightPos);

void main(){
  vec4 tex = texture2D(in_Texture, ex_TexCoord);
  if(tex.w < 1){
    discard;
  }

  vec3 norm = normalize(ex_Normal);
  vec3 lighting = vec3(0,0,0);
  float shadow = 0;
  for(int i = 0; i < NO_POINT_LIGHTS; i++){
    lighting += CalcPointLights(lights[i], norm, in_ShadowMaps[i]);
	shadow += ShadowCalculation(ex_FragPos, in_ShadowMaps[i], lights[i].pos);
  }
  lighting += shadow;
  for(int i = 0; i < NO_DIR_LIGHTS; i++){
    lighting += CalcDirLights(dlights[i], norm);
  }
  gl_FragColor = vec4(lighting,1) * tex;
}

vec3 calcPointLights(PointLight light, vec3 norm, samplerCube shadowMap){
  vec3 lightDir = normalize(light.pos - ex_FragPos);

  float diff = max(dot(norm, lightDir), 0.0);
  light.diffuse = diff * light.diffuse;

  vec3 viewPos = vec3(inverse(in_View) * vec4(0,0,0,1));
  vec3 viewDir = normalize(viewPos - ex_FragPos);
  vec3 reflectDir = reflect(-lightDir, norm);

  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
  light.specular = spec * light.specular;

  float distance = length(light.pos - ex_FragPos);
  float attentuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

  vec3 lighting = light.emissive + ((light.ambient + light.diffuse + light.specular) * attentuation);
  //float shadow = ShadowCalculation(ex_FragPos, shadowMap, light.pos);
  return lighting;// * shadow;
}

vec3 calcDirLights(DirectionalLight light, vec3 norm){
  vec3 lightDir = normalize(-light.dir);

  float diff = max(dot(norm, lightDir), 0.0);
  light.diffuse = diff * light.diffuse;

  vec3 viewPos = vec3(inverse(in_View) * vec4(0,0,0,1));
  vec3 viewDir = normalize(viewPos - ex_FragPos);
  vec3 reflectDir = reflect(-lightDir, norm);

  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
  light.specular = spec * light.specular;

  vec3 lighting = light.emissive + light.ambient + light.diffuse + light.specular;

  return lighting;
}

vec3 sampleOffsetDirections[20] = vec3[]
(
   vec3( 1,  1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1,  1,  1), 
   vec3( 1,  1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1,  1, -1),
   vec3( 1,  1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1,  1,  0),
   vec3( 1,  0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1,  0, -1),
   vec3( 0,  1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0,  1, -1)
);  

float ShadowCalculation(vec3 fragPos, samplerCube shadowMap, vec3 lightPos){
  vec3 fragToLight = (fragPos - lightPos);
  float currentDepth = length(fragToLight);
  int samples  = 20;
  float diskRadius = 0.05;
  float bias = 0.001; 

  /*
  float shadowDepth = texture(shadowMap, (fragToLight)).r;
  float z = shadowDepth;// * 2.0 - 1.0; 
  float linearShadowDepth = (2.0 * in_NearPlane * in_FarPlane) / (in_FarPlane + in_NearPlane - z * (in_FarPlane - in_NearPlane));
  // check whether current frag pos is in shadow
  float shadow = currentDepth  -  bias > linearShadowDepth ? 0.0 : 1.0;
  */
  float shadow = 0;
  for(int i = 0; i < samples; ++i){
    float shadowDepth = texture(shadowMap, fragToLight + sampleOffsetDirections[i] * diskRadius).r;
	float z = shadowDepth;// * 2.0 - 1.0; 
    float linearShadowDepth = (2.0 * in_NearPlane * in_FarPlane) / (in_FarPlane + in_NearPlane - z * (in_FarPlane - in_NearPlane));
    if(currentDepth - bias > linearShadowDepth){
      shadow -= 1.0;
	}
  }
  shadow /= float(samples); 
  
  return shadow;
}
#endif