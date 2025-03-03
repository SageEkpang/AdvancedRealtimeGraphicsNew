//--------------------------------------------------------------------------------------
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

// the lighting equations in this code have been taken from https://www.3dgep.com/texturing-lighting-directx-11/
// with some modifications by David White

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
cbuffer ConstantBuffer : register(b0)
{
    matrix World;
    matrix View;
    matrix Projection;
    float4 vOutputColor;
}

Texture2D BaseMap : register(t0);
Texture2D NormalMap : register(t1);
Texture2D SpecularMap : register(t2);
Texture2D RoughnessMap : register(t3);

SamplerState BaseSampler : register(s0);
SamplerState NormalSampler : register(s1);
SamplerState SpecularSampler : register(s2);
SamplerState RoughnessSampler : register(s3);

#define MAX_LIGHTS 1
// Light types.
#define DIRECTIONAL_LIGHT 0
#define POINT_LIGHT 1
#define SPOT_LIGHT 2

struct _Material
{
    float4 Emissive; // 16 bytes
							//----------------------------------- (16 byte boundary)
    float4 Ambient; // 16 bytes
							//------------------------------------(16 byte boundary)
    float4 Diffuse; // 16 bytes
							//----------------------------------- (16 byte boundary)
    float4 Specular; // 16 bytes
							//----------------------------------- (16 byte boundary)
    float SpecularPower; // 4 bytes
    bool UseTexture; // 4 bytes
    float2 Padding; // 8 bytes
							//----------------------------------- (16 byte boundary)
}; // Total:               // 80 bytes ( 5 * 16 )

cbuffer MaterialProperties : register(b1)
{
    _Material Material;
};

struct Light
{
    float4 Position; // 16 bytes
										//----------------------------------- (16 byte boundary)
    float4 Direction; // 16 bytes
										//----------------------------------- (16 byte boundary)
    float4 Color; // 16 bytes
										//----------------------------------- (16 byte boundary)
    float SpotAngle; // 4 bytes
    float ConstantAttenuation; // 4 bytes
    float LinearAttenuation; // 4 bytes
    float QuadraticAttenuation; // 4 bytes
										//----------------------------------- (16 byte boundary)
    int LightType; // 4 bytes
    bool Enabled; // 4 bytes
    int2 Padding; // 8 bytes
										//----------------------------------- (16 byte boundary)
}; // Total:                           // 80 bytes (5 * 16)

cbuffer LightProperties : register(b2)
{
    float4 EyePosition; // 16 bytes
										//----------------------------------- (16 byte boundary)
    float4 GlobalAmbient; // 16 bytes
										//----------------------------------- (16 byte boundary)
    Light Lights[MAX_LIGHTS]; // 80 * 8 = 640 bytes
}; 

//--------------------------------------------------------------------------------------
struct VS_INPUT
{

};

struct PS_INPUT
{
    float4 Pos : SV_POSITION; // 16
	
    float4 worldPos : POSITION; // 16
	
    float3 EyeVectorTS : POSITION1; // 12
    float3 Norm : NORMAL; // 4
	
    float3 LightVectorTS : POSITION2; // 12
	
    float2 Tex : TEXCOORD0; // 8
    float3x3 TBNMatrix : TBNMATRIX; // 27
};


float4 DoDiffuse(Light light, float3 L, float3 N)
{
    float NdotL = max(0, dot(N, L));
    return light.Color * NdotL;
}

float4 DoSpecular(Light lightObject, float3 vertexToEye, float3 lightDirectionToVertex, float3 Normal)
{
    float4 lightDir = float4(normalize(-lightDirectionToVertex), 1);
    vertexToEye = normalize(vertexToEye);

    float lightIntensity = saturate(dot(Normal, lightDir.xyz));
    float4 specular = float4(0, 0, 0, 0);
    if (lightIntensity > 0.0f)
    {
        float3 reflection = normalize(2 * lightIntensity * Normal - lightDir.xyz);
        // specular = pow(saturate(dot(reflection, vertexToEye)), Material.SpecularPower); // 32 = specular power
        specular = pow(saturate(dot(reflection, vertexToEye)), 128); // 32 = specular power
    }

    return specular;
}

float DoAttenuation(Light light, float d)
{
    return 1.0f / (light.ConstantAttenuation + light.LinearAttenuation * d + light.QuadraticAttenuation * d * d);
}

struct LightingResult
{
    float4 Diffuse;
    float4 Specular;
};

LightingResult DoPointLight(Light light, float3 vertexToEye, float4 vertexPos, float3 N, float3 lt)
{
    LightingResult result;

    float3 LightDirectionToVertex = (vertexPos - light.Position).xyz;
    // float3 LightDirectionToVertex = -lt;
    float distance = length(LightDirectionToVertex);
    LightDirectionToVertex = LightDirectionToVertex / distance;

    float3 vertexToLight = (light.Position - vertexPos).xyz;
    // float3 vertexToLight = lt;
    distance = length(vertexToLight);
    vertexToLight = vertexToLight / distance;

    float attenuation = DoAttenuation(light, distance);
    // attenuation = 1;


    result.Diffuse = DoDiffuse(light, vertexToLight, N) * attenuation;
    result.Specular = DoSpecular(light, vertexToEye, LightDirectionToVertex, N) * attenuation;

    return result;
}

LightingResult ComputeLighting(float4 vertexPos, float3 N, float3 lt, float3 et)
{
    float3 vertexToEye = normalize(EyePosition - vertexPos).xyz;
    // float3 vertexToEye = et;

    LightingResult totalResult = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 } };

	[unroll]
    for (int i = 0; i < MAX_LIGHTS; ++i)
    {
        LightingResult result = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 } };

        if (!Lights[i].Enabled) 
            continue;
		
        result = DoPointLight(Lights[i], vertexToEye, vertexPos, N, lt);
		
        totalResult.Diffuse += result.Diffuse;
        totalResult.Specular += result.Specular;
    }

    totalResult.Diffuse = saturate(totalResult.Diffuse);
    totalResult.Specular = saturate(totalResult.Specular);

    return totalResult;
}

float3 VectorToTangentSpace(float3 Vec, float3x3 inv)
{
    float3 t_TangentSpaceNormal = normalize(mul(Vec, inv));
    return t_TangentSpaceNormal;
}

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------

PS_INPUT VS(float4 Pos : POSITION, float3 Norm : NORMAL, float2 Tex : TEXCOORD0, float3 Tangent : TANGENT, float3 BiNormal : BINORMAL)
{
    PS_INPUT output = (PS_INPUT) 0;
    
    output.Pos = mul(Pos, World);
    float3 t_VertexToEye = EyePosition.xyz - output.Pos.xyz;
    float3 t_VertexToLight = Lights[0].Position.xyz - output.Pos.xyz;
    
    output.worldPos = mul(Pos, World);
    output.Pos = mul(output.Pos, View);
    output.Pos = mul(output.Pos, Projection);
	
	// Build TBN Matrix
    float3x3 normalisedWorld = (float3x3) World;
    float3 T = mul(Tangent, normalisedWorld);
    float3 B = mul(BiNormal, normalisedWorld);
    float3 N = mul(Norm, normalisedWorld);
	
    float3x3 TBN = float3x3(T, B, N);
    float3x3 TBN_inv = transpose(TBN);
    output.TBNMatrix = TBN_inv;
	
    output.EyeVectorTS = t_VertexToEye;
    output.LightVectorTS = t_VertexToLight;
	
	// multiply the normal by the world transform (to go from model space to world space)
    // output.Norm = VectorToTangentSpace(N, TBN_inv);
    output.Norm = VectorToTangentSpace(N, TBN_inv);
    
    output.Tex = Tex;
	
    return output;
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------

float4 PS(PS_INPUT IN) : SV_TARGET
{
	// Bump Map Calculations
    float3 t_BumpMap;
    t_BumpMap = NormalMap.Sample(NormalSampler, IN.Tex);
    t_BumpMap = (t_BumpMap * 2.0f) - 1.0f;
	
    float3 t_Normal = t_BumpMap;
    
    float3 t_EyeVec = VectorToTangentSpace(IN.EyeVectorTS, IN.TBNMatrix);
    float3 t_LightVec = VectorToTangentSpace(IN.LightVectorTS, IN.TBNMatrix);
    
	// Lighting Calculations
    LightingResult lit = ComputeLighting(IN.worldPos, t_Normal, t_LightVec, t_EyeVec);
	
	// Tangent Space Lighting, Tangent Space Eye, and Normal Map Normal
    float4 texColor = { 1, 1, 1, 1 };

    float4 emissive = Material.Emissive;
    float4 ambient = Material.Ambient * GlobalAmbient;
    float4 diffuse = Material.Diffuse * lit.Diffuse;
    float4 specular = Material.Specular * lit.Specular;

    float speTex = SpecularMap.Sample(SpecularSampler, IN.Tex);
	
	// Use the Texture
    if (Material.UseTexture)
    {
        texColor = BaseMap.Sample(BaseSampler, IN.Tex);
    }
    else
    {
        texColor = (1, 1, 1, 1);
    }
    
    // Transparency for the Alpha Channel
    // clip(texColor.a < 0.1 ? -1 : 1);

	// Output Final Results
    float4 finalColor = (emissive + ambient + diffuse + (specular * speTex * 5)) * texColor;
    return finalColor;
}