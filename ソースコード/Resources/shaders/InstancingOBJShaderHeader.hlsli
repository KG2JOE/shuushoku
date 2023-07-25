cbuffer cbuff0 : register(b0)
{
    matrix projectionMatrix;
};

// 頂点シェーダーからピクセルシェーダーへのやり取りに使用する構造体
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