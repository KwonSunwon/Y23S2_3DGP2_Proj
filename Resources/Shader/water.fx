#ifndef _TERRAIN_FX_
#define _TERRAIN_FX_

#include "params.fx"
#include "utils.fx"

struct VS_IN
{
    float3 pos : POSITION;
    float2 uv : TEXCOORD0;
};

struct VS_OUT
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD0;
};

// g_float_0 : time
// g_mat_0 : animatino matrix

VS_OUT VS_Main(VS_IN input)
{
    VS_OUT output;
    
    input.pos.y += sin(g_float_0 * 0.35f + input.pos.x * 0.35f) * 2.95f + cos(g_float_0 * 0.30f + input.pos.z * 0.35f) * 2.05f;
    output.pos = mul(float4(input.pos, 1.0f), g_matWorld);
    if (155.0f < output.pos.y)
        output.pos.y = 155.0f;
    output.pos = mul(mul(output.pos, g_matView), g_matProjection);

    output.uv = input.uv;
    
    return output;
}

float4 PS_Main(VS_OUT input) : SV_Target
{
    float2 uv = input.uv;

    uv = mul(float3(input.uv, 1.0f), (float3x3) g_mat_0).xy;
    // uv.y += g_float_0 * 0.00125f

    float4 cBaseTexColor = g_tex_0.SampleLevel(g_sam_0, uv, 0);
    float4 cDetail0TexColor = g_tex_1.SampleLevel(g_sam_0, uv * 10.0f, 0);
    float4 cDetail1TexColor = g_tex_2.SampleLevel(g_sam_0, uv * 5.0f, 0);

    float4 cColor = float4(0.0f, 0.0f, 0.0f, 1.0f);
    cColor = lerp(cBaseTexColor * cDetail0TexColor, cDetail1TexColor.r * 0.5f, 0.35f);

    return (cColor);
}

#endif