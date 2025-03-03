//--------------------------------------------------------------------------------------
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

// the lighting equations in this code have been taken from https://www.3dgep.com/texturing-lighting-directx-11/
// with some modifications by David White

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------

cbuffer ColourBuffer : register(b0)
{
    matrix m_World;
    matrix m_View;
    matrix m_Projeciton;
}

Texture2D BaseTexture : register(t0);
SamplerState BaseSampler : register(s0);

//--------------------------------------------------------------------------------------

struct PS_INPUT
{
    float4 Pos : SV_POSITION; // 16
    float2 Tex : TEXCOORD0; // 8
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
    
    return output;
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------

float4 PS(PS_INPUT IN) : SV_TARGET
{
    // Init Variables
    float4 t_BaseResult = BaseTexture.Sample(BaseSampler, IN.Tex);
    
    if (t_BaseResult.r <= 0)
    {
        t_BaseResult = float4(0.5, 0.5, 0.5, 1);
    }
    
    // RESULT
    return t_BaseResult;
}