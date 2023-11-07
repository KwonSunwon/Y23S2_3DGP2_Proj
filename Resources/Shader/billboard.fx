#ifndef _BILLBOARD_FX_
#define _BILLBOARD_FX_

#include "params.fx"
#include "utils.fx"

struct VS_IN
{
    float3 posW : POSITION;
};

struct VS_OUT
{
    float3 centerW : POSITION;
    float2 sizeW : SIZE;
};

struct GS_OUT
{
    float4 posH : SV_Position;
    float3 posW : POSITION;
    float3 normalW : NORMAL;
    float2 uv : TEXCOORD;
    uint primID : SV_PrimitiveID;
};

// g_int_0 : texture index
// g_vec2_0 : texture size
// g_vec3_0 : camera position

VS_OUT VS_Main(VS_IN input)
{
    VS_OUT output;
    output.centerW = input.posW;
    output.sizeW = g_vec2_0;
    return output;
}

[maxvertexcount(4)]
void GS_Main(point VS_OUT input[1], uint primID : SV_PrimitiveID, inout TriangleStream<GS_OUT> outStream)
{
    float3 vUp = float3(0.0f, 1.0f, 0.0f);
    float3 vLook = g_vec3_0 - input[0].centerW;
    vLook = normalize(vLook);
    float3 vRight = cross(vUp, vLook);
    
    float halfWidth = input[0].sizeW.x * 0.5f;
    float halfHeight = input[0].sizeW.y * 0.5f;
    
    float4 vertices[4];
    vertices[0] = float4(input[0].centerW + (-vRight * halfWidth + vUp * halfHeight), 1.0f);
    vertices[1] = float4(input[0].centerW + (vRight * halfWidth + vUp * halfHeight), 1.0f);
    vertices[2] = float4(input[0].centerW + (-vRight * halfWidth + -vUp * halfHeight), 1.0f);
    vertices[3] = float4(input[0].centerW + (vRight * halfWidth + -vUp * halfHeight), 1.0f);

    float2 uvs[4] = { float2(0.f, 1.f), float2(0.f, 0.f), float2(1.f, 1.f), float2(1.f, 0.f) };
    
    GS_OUT output;
    for (int i = 0; i < 4; i++)
    {
        output.posH = mul(vertices[i], g_matProjection);
        output.posW = vertices[i].xyz;
        output.normalW = vLook;
        output.uv = uvs[i];
        output.primID = primID;
        outStream.Append(output);
    }
}

float4 PS_Main(GS_OUT input) : SV_Target
{
    float3 uvw = float3(input.uv, (input.primID % 4));
    float4 cTexture;
    switch (g_int_0)
    {
        case 0:
            cTexture = g_tex_0.Sample(g_sam_0, uvw);
            break;
        case 1:
            cTexture = g_tex_1.Sample(g_sam_0, uvw);
            break;
        case 2:
            cTexture = g_tex_2.Sample(g_sam_0, uvw);
            break;
        case 3:
            cTexture = g_tex_3.Sample(g_sam_0, uvw);
            break;
        case 4:
            cTexture = g_tex_4.Sample(g_sam_0, uvw);
            break;
    }
    return cTexture;
}

#endif