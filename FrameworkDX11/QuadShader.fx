//--------------------------------------------------------------------------------------
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

// the lighting equations in this code have been taken from https://www.3dgep.com/texturing-lighting-directx-11/
// with some modifications by David White

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------

Texture2D QuadTexture : register(t0);
SamplerState QuadSampler : register(s0);

//--------------------------------------------------------------------------------------
struct VS_INPUT
{

};

struct PS_INPUT
{
    float4 Pos : SV_POSITION; // 16
    float Norm : NORMAL; // 4
    float3 EyeVectorTS : POSITION0;
    float2 Tex : TEXCOORD0; // 8
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------

PS_INPUT VS(float4 Pos : POSITION, float3 Norm : NORMAL, float2 Tex : TEXCOORD0)
{
    PS_INPUT output = (PS_INPUT) 0;
    output.Pos = Pos;
    output.Norm = Norm;
    output.Tex = Tex;
    return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------

float4 PS(PS_INPUT IN) : SV_TARGET
{
	// Tangent Space Lighting, Tangent Space Eye, and Normal Map Normal
    float4 t_TextureColor = QuadTexture.Sample(QuadSampler, IN.Tex);
    
	// Output Final Results
    return t_TextureColor;
}