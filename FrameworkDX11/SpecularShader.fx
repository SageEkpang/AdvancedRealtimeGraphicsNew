//--------------------------------------------------------------------------------------
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

// the lighting equations in this code have been taken from https://www.3dgep.com/texturing-lighting-directx-11/
// with some modifications by David White

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------

cbuffer SpecularBuffer : register(b0)
{
    matrix m_World;
    matrix m_View;
    matrix m_Projeciton;
    float4 m_HasSpecularTexture;
}

Texture2D SpecularTexture : register(t2);
SamplerState SpecularSampler : register(s2);

//--------------------------------------------------------------------------------------

struct PS_INPUT
{
    float4 Pos : SV_POSITION; // 16
    float2 Tex : TEXCOORD0; // 8
    int HasSpecular : POSITION1;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------

PS_INPUT VS(float4 Pos : POSITION, float3 Norm : NORMAL, float2 Tex : TEXCOORD0)
{
    PS_INPUT output = (PS_INPUT) 0;
    output.Pos = mul(Pos, m_World);
    output.Pos = mul(output.Pos, m_View);
    output.Pos = mul(output.Pos, m_Projeciton);
    output.Tex = Tex;
    output.HasSpecular = m_HasSpecularTexture.x;
    return output;
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------

float4 PS(PS_INPUT IN) : SV_TARGET
{
    // Init Variables
    float4 t_SpecularResult = 0; // 
    
    int t_HasSpecular = IN.HasSpecular;
    
    if (t_HasSpecular == 1)
    {
        t_SpecularResult = SpecularTexture.Sample(SpecularSampler, IN.Tex);
    }
    else
    {
        t_SpecularResult = float4(0.0f, 0.0f, 0.0f, 1.0f);
    }
    
    // RESULT
    return t_SpecularResult;
}