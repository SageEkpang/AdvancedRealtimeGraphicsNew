//--------------------------------------------------------------------------------------
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

// the lighting equations in this code have been taken from https://www.3dgep.com/texturing-lighting-directx-11/
// with some modifications by David White

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
cbuffer ChromaticAbberationConstantBuffer : register(b0)
{
    
    
    
    
}

Texture2D SceneTexture : register(t0);
SamplerState SceneSampler : register(s0);

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

float4 PS(PS_INPUT IN) : SV_TARGET
{
    
    float t_ChromaticAmount = 3.0f; // TODO: ADD TO SHADER CONSTANT BUFFER
    float t_RedOffset = t_ChromaticAmount;
    float t_GreenOffset = t_ChromaticAmount;
    float t_BlueOffset = t_ChromaticAmount;
    float4 t_ChromoColour = 0;
    
    t_ChromoColour.r = SceneTexture.Sample(SceneSampler, IN.Tex, int2(0, 1) * t_RedOffset).r;
    t_ChromoColour.g = SceneTexture.Sample(SceneSampler, IN.Tex, int2(1, -1) * t_GreenOffset).g;
    t_ChromoColour.b = SceneTexture.Sample(SceneSampler, IN.Tex, int2(-1, -1) * t_BlueOffset).b;

    return t_ChromoColour;
}
