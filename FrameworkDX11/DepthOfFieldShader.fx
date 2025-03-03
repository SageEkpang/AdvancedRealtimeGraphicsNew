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
    matrix m_World;
    // ---------- 16 bytes
    matrix m_View;
    // ---------- 16 bytes
    matrix m_Projection;
    // ---------- 16 bytes
}

Texture2D SceneTexture : register(t0);
SamplerState SceneSampler : register(s0);

Texture2D DepthTexture : register(t1);
SamplerState DepthSampler : register(s1);

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
    output.Pos = Pos; 
    output.Tex = Tex;
   
    return output;
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------


float4 DoBlur(float2 UV)
{
    float4 t_OutputColour = 0;
    
    float t_Pi = 6.28318530718;
    
    const float t_Directions = 16; // 16
    const float t_Quality = 3; // 3
    const float t_Size = 10; // 8
    
    float2 t_Radius = t_Size;
    
    t_OutputColour = SceneTexture.Sample(SceneSampler, UV);
    
    for (float d = 0.0; d < t_Pi; d += t_Pi / t_Directions)
    {
        for (float i = 1.001 / t_Quality; i <= 1.0; i += 1.0 / t_Quality)
        {
            t_OutputColour += SceneTexture.Sample(SceneSampler, UV, float2(cos(d), sin(d)) * t_Radius * i);
        }
    }
    
    t_OutputColour /= t_Quality * t_Directions - 15.0;
    return t_OutputColour;
}


float4 PS(PS_INPUT IN) : SV_TARGET
{
    // Init Variable(s)
    float4 t_InFocusTexture = SceneTexture.Sample(SceneSampler, IN.Tex);
    float4 t_OutFocusTexture = DoBlur(IN.Tex);
    float4 t_DepthTexture = DepthTexture.Sample(DepthSampler, IN.Tex);
    
    float4 t_TotalColour = 0;
    float4 t_TotalOutput = lerp(t_OutFocusTexture, t_InFocusTexture, t_DepthTexture);

	// Output Final Results
    return t_TotalOutput;
}