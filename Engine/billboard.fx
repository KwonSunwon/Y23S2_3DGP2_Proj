#ifndef _BILLBOARD_FX_
#define _BILLBOARD_FX_

#include "params.fx"
#include "utils.fx"

struct VS_IN
{
    float3 posW : POSITION;
    float2 sizeW : SIZE;
};

struct VS_OUT
{
    float3 centerW : POSITION;
    float2 sizeW : SIZE;
};

struct GS_OUT
{
    float4 posH : SV_POSITION;
    float3 posW : POSITION;
    float3 normalW : NORMAL;
    float2 uv : TEXCOORD;
    uint primID : SV_PrimitiveID;
};

VS_OUT VS_Main(VS_IN input)
{
    VS_OUT output;
    output.centerW = input.posW;
    output.sizeW = input.sizeW;
    return output;
}

[maxvertexcount(4)]
void GS_Main(point VS_OUT input[1], uint primID : SV_PrimitiveID, inout TriangleStream<GS_OUT> outStream)
{
    float3 vUp = float3(0.0f, 1.0f, 0.0f);
    float3 vLook = cameraPos.xyz - input[0].centerW;
    vLook = normalize(vLook);
    float3 vRight = cross(vUp, vLook);
    
    float halfWidth = input[0].sizeW.x * 0.5f;
    float halfHeight = input[0].sizeW.y * 0.5f;
    float4 vertices[4];
    vertices[0] = float4(input[0].centerW + halfWidth * vRight - halfHeight * vUp, 1.0f);
    vertices[1] = float4(input[0].centerW + halfWidth * vRight + halfHeight * vUp, 1.0f);
    vertices[2] = float4(input[0].centerW - halfWidth * vRight + halfHeight * vUp, 1.0f);
    vertices[3] = float4(input[0].centerW - halfWidth * vRight - halfHeight * vUp, 1.0f);
    
    float2 uvs[4] = { float2(0.f, 1.f), float2(0.f, 0.f), float2(1.f, 1.f), float2(1.f, 0.f) };
    GS_OUT output;
    for (uint i = 0; i < 4; ++i)
    {
        output.posW = vertices[i].xyz;
        output.posH = mul(vertices[i], g_mViewProj);
        output.normalW = vLook;
        output.uv = uvs[i];
        output.primID = primID;
        outStream.Append(output);
    }
}

float4 PS_Main(GS_OUT input) : SV_Target
{
    float3 uvw = float3(input.uv, (input.primID % 4));
    float4 texture = treeTextureArray.Sample(gSamplerState, uvw);
    return texture;
}

#endif