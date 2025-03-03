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
    float4 vOutputColor;
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

float4 HueShift(float3 colour, float hueShift)
{
    float3 t_Point = float3(0.55735, 0.55735, 0.55735) * dot(float3(0.55735, 0.55735, 0.55735), colour);
    float3 t_Up = colour - t_Point;
    float3 t_Vector = cross(float3(0.55735, 0.55735, 0.55735), t_Up);
    colour = t_Up * cos(hueShift * 6.2832) + t_Vector * sin(hueShift * 6.2832) + t_Point;
    return float4(colour, 1.0);
}

float4 BoxBlurFunc(float4 pixelToBlur, float bloomStrength, PS_INPUT IN)
{
    float4 t_TempBlur = pixelToBlur;
    pixelToBlur += SceneTexture.Sample(SceneSampler, IN.Tex, int2(0, 0) * bloomStrength); // 1
    pixelToBlur += SceneTexture.Sample(SceneSampler, IN.Tex, int2(-1, 1) * bloomStrength); // 2
    pixelToBlur += SceneTexture.Sample(SceneSampler, IN.Tex, int2(0, 1) * bloomStrength); // 3
    pixelToBlur += SceneTexture.Sample(SceneSampler, IN.Tex, int2(1, 1) * bloomStrength); // 4
    pixelToBlur += SceneTexture.Sample(SceneSampler, IN.Tex, int2(1, 0) * bloomStrength); // 5
    pixelToBlur += SceneTexture.Sample(SceneSampler, IN.Tex, int2(1, -1) * bloomStrength); // 6
    pixelToBlur += SceneTexture.Sample(SceneSampler, IN.Tex, int2(0, -1) * bloomStrength); // 7
    pixelToBlur += SceneTexture.Sample(SceneSampler, IN.Tex, int2(-1, -1) * bloomStrength); // 8
    pixelToBlur += SceneTexture.Sample(SceneSampler, IN.Tex, int2(-1, 0) * bloomStrength); // 9
    
    pixelToBlur /= 9;
    
    return pixelToBlur;
}

float4 PS(PS_INPUT IN) : SV_TARGET
{
    // TEXTURE VARIABLE
    float4 t_ResultImage = SceneTexture.Sample(SceneSampler, IN.Tex);
    float4 t_TotalColour = 0;
   
    // HUE ------------------
    // HUE = RANGE (0 to 1)
    // DEFAULT (0)
    float t_HueAmount = 0.2f;
    t_TotalColour += HueShift(t_ResultImage.rgb, t_HueAmount);
    
    // RESULT (HUE)
    // ----------------------
    
    
    // SATURATION -----------
    // SATURATION = RANGE (0 to 10)
    // DEFAULT (1)
    //float t_SatValue = 1.0f; // TODO: Add constant buffer value for this
    //float4 t_Saturation = float4(t_SatValue, t_SatValue, t_SatValue, 1);
    //float3 t_LuminanceWeights = float3(0.299, 0.587, 0.114);
    
    //float t_Luminance = dot(t_ResultImage, t_LuminanceWeights);
    //t_TotalColour += lerp(t_Luminance, t_ResultImage, t_Saturation);
    
    // t_TotalColour.a = t_ResultImage.a;
    
    // RESULTS (SATURATION)
    // ----------------------
    
    
    // SHARPNESS ------------
    // SHARPNESS = RANGE (-1 to 10)
    // DEFAULT (0.5)
    //float t_SharpnessAmount = 0.0; // TODO: Add constant buffer value for this
    //float4 t_TextureA = SceneTexture.Sample(SceneSampler, IN.Tex, int2(-1, -1));
    //float4 t_TextureB = SceneTexture.Sample(SceneSampler, IN.Tex, int2(1, -1));
    //float4 t_TextureC = SceneTexture.Sample(SceneSampler, IN.Tex, int2(-1, 1));
    //float4 t_TextureD = SceneTexture.Sample(SceneSampler, IN.Tex, int2(1, 1));
    
    //float4 t_Around = 0.25 * (t_TextureA + t_TextureB + t_TextureC + t_TextureD);
    //float4 t_Center = SceneTexture.Sample(SceneSampler, IN.Tex);
    
    //float4 t_SharpColour = t_Center + (t_Center - t_Around) * t_SharpnessAmount;
    //t_TotalColour.rgb /= t_TotalColour.a + 4;
    //t_TotalColour += t_SharpColour;

    // RESULT
    // ----------------------
    
    
    // BLOOM ----------------
    // STRENGTH = RANGE (0 to 1), BLUR_STRENGTH = RANGE (1 to 6), MULTIPLIER = RANGE (1.0 to 6)
    // STRENGTH = DEFAULT (0), BLUR_STRENGTH = DEFAULT (1.5), MULTIPLIER = DEFAULT (1.5)
    //float t_BloomStrength = 0.0f;
    //float t_BloomBlurStrength = 1.5f;
    //float t_BloomMultiplier = 1.5f;
    //float4 t_OutOfFocusTexture = SceneTexture.Sample(SceneSampler, IN.Tex);
    //t_OutOfFocusTexture = BoxBlurFunc(t_OutOfFocusTexture, 5, IN);
    
    //t_OutOfFocusTexture.rgb /= t_OutOfFocusTexture.a;
    //t_TotalColour += lerp(float4(0.0f, 0.0f, 0.0f, 1.0f), t_OutOfFocusTexture, t_BloomStrength) * t_BloomMultiplier;
    // RESULT
    // ----------------------
    
    
    
    // CONTRAST ------------- 
    // CONTRAST = RANGE (0 to 2)
    // DEFAULT (1)
    //float t_ContValue = 1.0f; // TODO: Add constant buffer value for this
   
    //t_TotalColour.rgb /= t_TotalColour.a;
    //t_TotalColour.rgb = ((t_TotalColour.rgb - 0.5f) * max(t_ContValue, 0)) + 0.5f;
    //t_TotalColour.rgb *= t_TotalColour.a;
    
    // RESULT
    // ----------------------
    
    
    // TINT -----------------
    // R = RANGE (0 to 1), G = RANGE (0 to 1), B = RANGE (0 to 1)
    // R = DEFAULT (0), G = DEFAULT (0), B = DEFAULT (0)
    // MULTIPLIER = RANGE (0 to 1)
    //float t_RedTintOffset = 0.0f; // TODO: Add constant buffer value for this
    //float t_GreenTintOffset = 0.0f; // TODO: Add constant buffer value for this
    //float t_BlueTintOffset = 0.0f; // TODO: Add constant buffer value for this
    //float t_TintMultiplier = 0.0f; // TODO: Add constant buffer value for this
    
    //t_TotalColour += float4(t_RedTintOffset, t_GreenTintOffset, t_BlueTintOffset, 1.0f) * t_TintMultiplier;
    //t_TotalColour.a = t_ResultImage.a;
    
    // RESULT (TINT)
    // ----------------------
   
    
    // BRIGHTNESS ----------- 
    // BRIGHT = RANGE: (-1 to 1)
    // DEFAULT (0)
    //float t_BrightValue = 0.0f; // TODO: Add constant buffer value for this
    
    //t_TotalColour.rgb += t_BrightValue;
    //t_TotalColour.a = t_ResultImage.a;
    
    // RESULT
    // ----------------------
    
    return t_TotalColour;
}

//--------------------------------------------------------------------------------------
// PSSolid - render a solid color
//--------------------------------------------------------------------------------------
float4 PSSolid(PS_INPUT input) : SV_Target
{
    return vOutputColor;
}
