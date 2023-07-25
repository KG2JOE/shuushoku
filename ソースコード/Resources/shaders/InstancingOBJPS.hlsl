#include "InstancingOBJShaderHeader.hlsli"

float4 main(VSOutput input) : SV_TARGET
{
    return float4(input.color, 1.0f);
}