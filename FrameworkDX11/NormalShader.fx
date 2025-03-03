//--------------------------------------------------------------------------------------
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

// the lighting equations in this code have been taken from https://www.3dgep.com/texturing-lighting-directx-11/
// with some modifications by David White

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------

cbuffer NormalBuffer : register(b0)
{
    matrix m_World;
    matrix m_View;
    matrix m_Projeciton;
    float4 m_HasNormalTexture;
}

//--------------------------------------------------------------------------------------

Texture2D NormalTexture : register(t1);
SamplerState NormalSampler : register(s1);

struct PS_INPUT
{
    float4 Pos : SV_POSITION; // 16
    float3x3 TBNMatrix : TBNMATRIX;
    float3 Normal : NORMAL;
    float2 Tex : TEXCOORD0; // 8
    int HasNormal : POSITION1;
};

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
    output.Tex = Tex;
   
    output.Pos = mul(Pos, m_World);
    output.Pos = mul(output.Pos, m_View);
    output.Pos = mul(output.Pos, m_Projeciton);
    
    output.Normal = Norm;
    
    float3x3 normalisedWorld = (float3x3) m_World;
    
    float3 T = mul(Tangent, normalisedWorld);
    float3 B = mul(BiNormal, normalisedWorld);
    float3 N = mul(Norm, normalisedWorld);
    
    float3x3 TBN = float3x3(T, B, N);
    output.TBNMatrix = TBN;
    output.TBNMatrix = transpose(output.TBNMatrix);
    
    output.HasNormal = m_HasNormalTexture.x;
    
    return output;
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------

float4 PS(PS_INPUT IN) : SV_TARGET
{
    // Init Variables
    float4 t_NormalMap = 0;
    float3 t_Output = 0;
    t_NormalMap = NormalTexture.Sample(NormalSampler, IN.Tex) * 2.0f - 1.0f;
    
    int t_HasNormal = IN.HasNormal;
    
    if (t_HasNormal == 1)
    {
        t_Output = normalize(mul(t_NormalMap.rgb, IN.TBNMatrix));
    }
    else
    {
        t_Output = float4(IN.Normal, 1);
    }
    
    // RESULT
    float4 t_TotalColour = float4(t_Output, 1.0);
    return t_TotalColour;
}