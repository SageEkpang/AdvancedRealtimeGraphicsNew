//--------------------------------------------------------------------------------------
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

// the lighting equations in this code have been taken from https://www.3dgep.com/texturing-lighting-directx-11/
// with some modifications by David White

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------

Texture2D BlurTexture : register(t0);
SamplerState BlurSampler : register(s0);

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
    // Init Variables
    float t_BlurSize = 4.f; // Default
    float4 t_Blurring = 0;
    
    // BOX BLUR
    t_Blurring += BlurTexture.Sample(BlurSampler, IN.Tex, int2(0, 0) * t_BlurSize); // 1
    t_Blurring += BlurTexture.Sample(BlurSampler, IN.Tex, int2(-1, 1) * t_BlurSize); // 2
    t_Blurring += BlurTexture.Sample(BlurSampler, IN.Tex, int2(0, 1) * t_BlurSize); // 3
    t_Blurring += BlurTexture.Sample(BlurSampler, IN.Tex, int2(1, 1) * t_BlurSize); // 4
    t_Blurring += BlurTexture.Sample(BlurSampler, IN.Tex, int2(1, 0) * t_BlurSize); // 5
    t_Blurring += BlurTexture.Sample(BlurSampler, IN.Tex, int2(1, -1) * t_BlurSize); // 6
    t_Blurring += BlurTexture.Sample(BlurSampler, IN.Tex, int2(0, -1) * t_BlurSize); // 7
    t_Blurring += BlurTexture.Sample(BlurSampler, IN.Tex, int2(-1, -1) * t_BlurSize); // 8
    t_Blurring += BlurTexture.Sample(BlurSampler, IN.Tex, int2(-1, 0) * t_BlurSize); // 9
    
    // Divide By Total Pixels
    t_Blurring /= 9;
    
    // RESULT
    return t_Blurring;
}
