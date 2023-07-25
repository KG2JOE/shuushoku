#include "InstancingOBJShaderHeader.hlsli"

VSOutput main(VertexInput input)
{
    VSOutput output;
    
    // インスタンスごとの位置と色を加算
    float2 position = input.position + input.instancePosition;
    float3 color = input.color + input.instanceColor;
    
    // モデル座標を射影座標に変換
    output.position = mul(float4(position, 0.0f, 1.0f), projectionMatrix);
    output.color = color;
    
    return output;
}