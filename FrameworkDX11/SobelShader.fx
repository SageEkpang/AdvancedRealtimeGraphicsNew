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

float intensity(float4 colour)
{
    return sqrt((colour.x * colour.x) + (colour.y * colour.y) + (colour.z * colour.z));
}

float3 Sobel(float stepX, float stepY, float2 UV)
{
    float t_TopLeft = intensity(SceneTexture.Sample(SceneSampler, UV, int2(-stepX, stepY)));
    float t_Left = intensity(SceneTexture.Sample(SceneSampler, UV, int2(-stepX, 0)));
    float t_BottomLeft = intensity(SceneTexture.Sample(SceneSampler, UV, int2(-stepX, -stepY)));
    float t_Top = intensity(SceneTexture.Sample(SceneSampler, UV, int2(0, stepY)));
    float t_Bottom = intensity(SceneTexture.Sample(SceneSampler, UV, int2(0, -stepY)));
    float t_TopRight = intensity(SceneTexture.Sample(SceneSampler, UV, int2(stepX, stepY)));
    float t_Right = intensity(SceneTexture.Sample(SceneSampler, UV, int2(stepX, 0)));
    float t_BottomRight = intensity(SceneTexture.Sample(SceneSampler, UV, int2(stepX, -stepY)));
    
    float t_X = t_TopLeft + 2.0 * t_Left + t_BottomLeft - t_TopRight - 2.0 * t_Right - t_BottomRight;
    float t_Y = -t_TopLeft - 2.0 * t_Top - t_TopRight + t_BottomLeft + 2.0 * t_Bottom + t_BottomRight;
    float t_Colour = sqrt((t_X * t_X) + (t_Y * t_Y));
    return float3(t_Colour, t_Colour, t_Colour);
}

float3 NewSobel(float2 UV)
{
    float3 t_Colour = 0;
    
    float3x3 t_SobelX = float3x3(-1.0, -2.0, -1.0,
                                  0.0, 0.0, 0.0,
                                  1.0, 2.0, 1.0);
    
    float3x3 t_SobelY = float3x3(-1.0, 0.0, 1.0,
                                 -2.0, 0.0, 2.0,
                                 -1.0, 0.0, 1.0);
    
    float t_SumX = 0.0f;
    float t_SumY = 0.0f;
    
    for (int i = -1; i <= 1; ++i)
    {
        for (int j = -1; j <= 1; ++j)
        {
            t_SumX += length(SceneTexture.Sample(SceneSampler, UV).xyz) * float(t_SobelY[1+i][1+j]);
            t_SumY += length(SceneTexture.Sample(SceneSampler, UV).xyz) * float(t_SobelX[1+i][1+j]);
        }
    }
    
    float t_G = abs(t_SumX) + abs(t_SumY);
    // t_G = sqrt((t_SumX * t_SumX) + (t_SumY * t_SumY));
    
    if (t_G > 1.0)
    {
        t_Colour = float3(1.0, 1.0, 1.0);
        return t_Colour;
    }
    else
    {
        t_Colour = t_Colour * 0.0f;
        return t_Colour;
    }
}

float4 PS(PS_INPUT IN) : SV_TARGET
{
    float4 t_TotalTexture = 0;
    float t_Step = 1.f;
    
    float4 t_ColourColour = SceneTexture.Sample(SceneSampler, IN.Tex);
    t_TotalTexture.rgb = Sobel(t_Step, t_Step, IN.Tex);
       
    t_ColourColour = 1;
    return t_TotalTexture * t_ColourColour;
}