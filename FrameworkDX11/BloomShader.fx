//--------------------------------------------------------------------------------------
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

// the lighting equations in this code have been taken from https://www.3dgep.com/texturing-lighting-directx-11/
// with some modifications by David White

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------

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
    // BLOOM ----------------
    // STRENGTH = RANGE (0 to 1), BLUR_STRENGTH = RANGE (1 to 6), MULTIPLIER = RANGE (1.0 to 6)
    // STRENGTH = DEFAULT (0), BLUR_STRENGTH = DEFAULT (1.5), MULTIPLIER = DEFAULT (1.5)
    float t_BloomStrength = 0.0f;
    float t_BloomBlurStrength = 3.f;
    float t_BloomMultiplier = 1.5f;
    float t_BlurStrength = 4.0;
    
    // TEXTURE VARIABLE
    float4 t_SceneColour = SceneTexture.Sample(SceneSampler, IN.Tex);
    
    // Box Blur
    float4 t_BlurColour = 0;
    t_BlurColour += SceneTexture.Sample(SceneSampler, IN.Tex, int2(0, 0) * t_BlurStrength); // 1
    t_BlurColour += SceneTexture.Sample(SceneSampler, IN.Tex, int2(-1, 1) * t_BlurStrength); // 2
    t_BlurColour += SceneTexture.Sample(SceneSampler, IN.Tex, int2(0, 1) * t_BlurStrength); // 3
    t_BlurColour += SceneTexture.Sample(SceneSampler, IN.Tex, int2(1, 1) * t_BlurStrength); // 4
    t_BlurColour += SceneTexture.Sample(SceneSampler, IN.Tex, int2(1, 0) * t_BlurStrength); // 5
    t_BlurColour += SceneTexture.Sample(SceneSampler, IN.Tex, int2(1, -1) * t_BlurStrength); // 6
    t_BlurColour += SceneTexture.Sample(SceneSampler, IN.Tex, int2(0, -1) * t_BlurStrength); // 7
    t_BlurColour += SceneTexture.Sample(SceneSampler, IN.Tex, int2(-1, -1) * t_BlurStrength); // 8
    t_BlurColour += SceneTexture.Sample(SceneSampler, IN.Tex, int2(-1, 0) * t_BlurStrength); // 9
    
    // NOTE: Output Colour
    float4 t_TotalColour = 0;
    
    // t_BlurTexture.rgb /= t_BlurTexture.a;
    // t_TotalColour = lerp(t_TotalColour, (t_BlurTexture * 3), t_BloomStrength) * t_BloomMultiplier;
    t_TotalColour = t_SceneColour + t_BlurColour;
    
    // RESULT
    // ----------------------
    return t_TotalColour;
}