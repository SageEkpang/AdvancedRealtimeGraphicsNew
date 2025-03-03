//--------------------------------------------------------------------------------------
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

// the lighting equations in this code have been taken from https://www.3dgep.com/texturing-lighting-directx-11/
// with some modifications by David White

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------

cbuffer PositionBuffer : register(b0)
{
    matrix m_World;
    matrix m_View;
    matrix m_Projeciton;
}

// MAIN DEFERRED VARIABLE(s)
Texture2D AlbedoTexture : register(t0); // 0
SamplerState AlbedoSampler : register(s0);

Texture2D NormalTexture : register(t1); // 1
SamplerState NormalSampler : register(s1);

Texture2D PositionTexture : register(t2); // 2
SamplerState PositionSampler : register(s2);

Texture2D SpecularAlbdeoTexture : register(t3); // 3
SamplerState SpecularAlbedoSampler : register(s3);

#define MAX_LIGHTS 3

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

LightingResult DoPointLight(Light light, float3 vertexToEye, float4 vertexPos, float3 N)
{
    LightingResult result;

    float3 LightDirectionToVertex = (vertexPos - light.Position).xyz;
    float distance = length(LightDirectionToVertex);
    LightDirectionToVertex = LightDirectionToVertex / distance;

    float3 vertexToLight = (light.Position - vertexPos).xyz;
    distance = length(vertexToLight);
    vertexToLight = vertexToLight / distance;

    float attenuation = DoAttenuation(light, distance);
    
    result.Diffuse = DoDiffuse(light, vertexToLight, N) * attenuation;
    result.Specular = DoSpecular(light, vertexToEye, LightDirectionToVertex, N) * attenuation;

    return result;
}

LightingResult ComputeLighting(float4 vertexPos, float3 N)
{
    // float3 vertexToEye = normalize(EyePosition - vertexPos).xyz;
    float3 vertexToEye = normalize(EyePosition).xyz;

    LightingResult totalResult = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 } };

	[unroll]
    for (int i = 0; i < MAX_LIGHTS; ++i)
    {
        LightingResult result = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 } };

        if (!Lights[i].Enabled) 
            continue;
		
        result = DoPointLight(Lights[i], vertexToEye, vertexPos, N);
		
        totalResult.Diffuse += result.Diffuse;
        totalResult.Specular += result.Specular;
    }

    totalResult.Diffuse = saturate(totalResult.Diffuse);
    totalResult.Specular = saturate(totalResult.Specular);

    return totalResult;
}

//--------------------------------------------------------------------------------------

struct PS_INPUT
{
    float4 Pos : SV_POSITION; // 16
    float4 WorldPos : POSITION0;
    float3 Norm : NORMAL;
    float2 Tex : TEXCOORD0; // 8
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------

PS_INPUT VS(float4 Pos : POSITION, float3 Norm : NORMAL, float2 Tex : TEXCOORD0)
{
    // INIT VARIBLE(s)
    PS_INPUT output = (PS_INPUT) 0;
    
    output.Pos = Pos;
    output.WorldPos = mul(Pos, m_World);
    output.Norm = Norm;
    output.Tex = Tex;
          
    return output;
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------

// MATERIAL INFORMATION
// AMBIENT 0.5
// DIFFUSE 1.0
// SPECULAR 1.
// SPEC POWER 128.0

float4 PS(PS_INPUT IN) : SV_TARGET
{
    // Deferred Textures
    float4 t_AlbedoDiffuse = AlbedoTexture.Sample(AlbedoSampler, IN.Tex); // COLOR SHADER
    float4 t_NormalTexture = NormalTexture.Sample(NormalSampler, IN.Tex); // NORMAL SHADER
    float4 t_PositionTexture = PositionTexture.Sample(PositionSampler, IN.Tex); // NOTE: This works but looks into it more of how to use this
    float4 t_SpecularTexture = SpecularAlbdeoTexture.Sample(SpecularAlbedoSampler, IN.Tex); // SPECULAR SHADER
    
    // Lighting Calulations  
    LightingResult lit = ComputeLighting(t_PositionTexture, t_NormalTexture.rgb);
    
    float4 t_Ambient = float4(0.5, 0.5, 0.5, 1.0);
    float4 t_Diffuse = lit.Diffuse;
    float4 t_Specular = lit.Specular;
    
    float4 t_TotalColour = (t_Ambient + t_Diffuse + (t_Specular * t_SpecularTexture)) * t_AlbedoDiffuse;
    
    // RESULT
    return t_TotalColour;
}
