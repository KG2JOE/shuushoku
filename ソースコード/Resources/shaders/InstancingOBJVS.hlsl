#include "InstancingOBJShaderHeader.hlsli"

VSOutput main(VertexInput input)
{
    VSOutput output;
    
    // �C���X�^���X���Ƃ̈ʒu�ƐF�����Z
    float2 position = input.position + input.instancePosition;
    float3 color = input.color + input.instanceColor;
    
    // ���f�����W���ˉe���W�ɕϊ�
    output.position = mul(float4(position, 0.0f, 1.0f), projectionMatrix);
    output.color = color;
    
    return output;
}