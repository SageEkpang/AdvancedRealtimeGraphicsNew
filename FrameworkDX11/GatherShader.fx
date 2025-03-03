//--------------------------------------------------------------------------------------
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

// the lighting equations in this code have been taken from https://www.3dgep.com/texturing-lighting-directx-11/
// with some modifications by David White

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------

cbuffer GeoBuffer : register(b0)
{
    matrix m_World;
    matrix m_View;
    matrix m_Projeciton;
}

//--------------------------------------------------------------------------------------

Texture2D AlbedoTexture : register(t0);
SamplerState AlbedoSampler : register(s0);

Texture2D SpecularTexture : register(t2);
SamplerState SpecularSampler : register(s2);

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float2 Tex : TEXCOORD0;
    float3x3 TBNMatrix : TBNMATRIX;
    float3 Normal : NORMAL;
    
    float4 Color : SV_Target0;
    //float4 WorldNormal : SV_Target1;
    //float4 WorldPosition : SV_Target2;
    //float4 Speclar : SV_Target3;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------

PS_INPUT VS(float4 Pos : POSITION0, float3 Norm : NORMAL, float2 Tex : TEXCOORD0, float3 Tangent : TANGENT, float3 BiNormal : BINORMAL)
{
    // INIT VARIABLES
    PS_INPUT output = (PS_INPUT) 0;
    //output.Pos = mul(Pos, m_World);
    //output.Pos = mul(output.Pos, m_View);
    //output.Pos = mul(output.Pos, m_Projeciton);
    //output.Tex = Tex;
    
    // WOLRD POSITION
    // output.WorldPosition = mul(Pos, m_World);
    
    // NORMAL CALCULATION(s)
    //float3x3 T_NormalisedWorld = (float3x3) m_World;
    //float3 T = mul(Tangent, T_NormalisedWorld);
    //float3 B = mul(BiNormal, T_NormalisedWorld);
    //float3 N = mul(Norm, T_NormalisedWorld);
    //float3x3 TBN = float3x3(T, B, N);
    //float3x3 TBN_inv = transpose(TBN);
    //output.Normal = Norm;
    
    return output;
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------

float4 PS(PS_INPUT IN) : SV_Target1
{
    // PS_INPUT output = (PS_INPUT) 0;
    
    //// COLOUR
    //output.Color = AlbedoTexture.Sample(AlbedoSampler, IN.Tex);
    
    //// SPECULAR
    //output.Speclar = SpecularTexture.Sample(SpecularSampler, IN.Tex);

    //// NORMAL
    //float3 t_Bump = IN.Normal;
    //t_Bump = (t_Bump * 2.0f) - 1.0f;
    //float3 t_Normal = mul(IN.TBNMatrix, t_Bump);
    //output.WorldNormal = float4(t_Normal.xyz, 1.0f);
    float4 test = float4(1.0f, 1.0f, 0.0f, 1.0f);
    
    // RESULT
    return test;
}
