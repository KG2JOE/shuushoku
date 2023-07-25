cbuffer cbuff0 : register(b0)
{
    matrix projectionMatrix;
};

// ���_�V�F�[�_�[����s�N�Z���V�F�[�_�[�ւ̂����Ɏg�p����\����
struct VSOutput
{
 
    float4 position : SV_POSITION;
    float3 color : COLOR;
};

struct VertexInput
{
    float2 position : POSITION;
    float3 color : COLOR;
    float2 instancePosition : INSTANCEPOSITION;
    float3 instanceColor : INSTANCECOLOR;
};