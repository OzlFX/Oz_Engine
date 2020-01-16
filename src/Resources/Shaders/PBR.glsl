#ifdef VERTEX
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
#endif
#ifdef FRAGMENT
out vec4 ex_FragColor;
in vec2 ex_TexCoord;
in vec3 ex_FragPos;
in vec3 ex_Normal;

// material parameters

uniform sampler2D in_albedo;
uniform sampler2D in_normalMap;
uniform sampler2D in_metallic;
uniform sampler2D in_roughness;
uniform sampler2D in_ao;

uniform vec3 in_LightPos;
uniform vec3 in_LightColor;
//uniform float in_shine;
uniform mat4 in_View;

uniform vec3 in_camPos;

const float PI = 3.14159265359;

vec3 getNormalFromMap()
{
    vec3 tangentNormal = texture(in_normalMap, ex_TexCoord).xyz * 2.0 - 1.0;

    vec3 Q1  = dFdx(ex_FragPos);
    vec3 Q2  = dFdy(ex_FragPos);
    vec2 st1 = dFdx(ex_TexCoord);
    vec2 st2 = dFdy(ex_TexCoord);

    vec3 N   = normalize(ex_Normal);
    vec3 T  = normalize(Q1*st2.t - Q2*st1.t);
    vec3 B  = -normalize(cross(N, T));
    mat3 TBN = mat3(T, B, N);

    return normalize(TBN * tangentNormal);
}


float DistGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness*roughness;
    float a2 = a*a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;

    float nom   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return nom / denom;
}


float GeoSchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float nom   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return nom / denom;
}


//float ggx (vec3 N, vec3 V, vec3 L, float roughness, float F0) {
//  float alpha = roughness*roughness;
//  vec3 H = normalize(L - V);
//  float dotLH = max(0.0, dot(L,H));
//  float dotNH = max(0.0, dot(N,H));
//  float dotNL = max(0.0, dot(N,L));
//  float alphaSqr = alpha * alpha;
//  float denom = dotNH * dotNH * (alphaSqr - 1.0) + 1.0;
//  float D = alphaSqr / (3.141592653589793 * denom * denom);
//  float F = F0 + (1.0 - F0) * pow(1.0 - dotLH, 5.0);
//  float k = 0.5 * alpha;
//  float k2 = k * k;
//  return dotNL * D * F / (dotLH*dotLH*(1.0-k2)+k2);
//}


float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeoSchlickGGX(NdotV, roughness);
    float ggx1 = GeoSchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}

//float lerp(float a, float b, float w)
//{
// return a + w*(b-a);
//}

vec3 fresnelSch(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}
//float DisneyDiffuse (float NdotV ,float NdotL ,float LdotH ,float linearRoughness)
//{
//	float energyBias = lerp(0 , 0.5 , linearRoughness );
//	float energyFactor = lerp(1.0 , 1.0 / 1.51 , linearRoughness );
//	vec3 fo = vec3 (1.0 f , 1.0 f , 1.0 f);
//	float lightScatter = fresnelSchlick (NdotL , fo   ) .r;
//	float viewScatter = fresnelSchlick (NdotV  ,fo  ).r;
//
//	return lightScatter * viewScatter * energyFactor ;
//}


void main()
{		
    vec3 albedo     = pow(texture(in_albedo, ex_TexCoord).rgb, vec3(2.2));
    float metallic  = texture(in_metallic, ex_TexCoord).r;
    float roughness = texture(in_roughness, ex_TexCoord).r;
    float ao        = texture(in_ao, ex_TexCoord).r;

    vec3 N = getNormalFromMap();
    vec3 V = normalize(in_camPos - ex_FragPos);
 
    vec3 F0 = vec3(0.04); 
    F0 = mix(F0, albedo, metallic);
	
    //reflectance equation
		vec3 Lo = vec3(0.0);
    
        // calculate radiance
        vec3 L = normalize(in_LightPos - ex_FragPos);
        vec3 H = normalize(V + L);
        float distance = length(in_LightPos - ex_FragPos);
        float attenuation = 1.0 / (distance * distance);
        vec3 radiance = in_LightColor * attenuation;
	
        //Cook-Torrance BRDF
           
        float G   = GeometrySmith(N, V, L, roughness);      
        vec3 F    = fresnelSch(max(dot(H, V), 0.0), F0);
		float NDF = DistGGX(N, H, roughness);
        //float NDF =  ggx(N,V,L,roughness,0.04f);
        vec3 nominator    = NDF * G * F; 
        float denominator = 4 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.001; // 0.001 to prevent divide by zero.
        vec3 specular = nominator / denominator;

        vec3 Diff = vec3(1.0) - F;

		//vec3 Diff = DisneyDiffuse(abs( dot (N , V )), dot (N , L ),dot(L,H),roughness) * albedo;

        Diff *= 1.0 - metallic;	  
	
        // scale light by NdotL
        float NdotL = max(dot(N, L), 0.0);        
	
        // add to outgoing radiance Lo
        Lo += (Diff * albedo / PI + specular) * radiance * NdotL;

	// replace with IBL soon

    vec3 ambient = vec3(0.3) * albedo * ao;
    
    vec3 color = ambient + Lo ;

    ex_FragColor = vec4(color, 1.0);
}
#endif