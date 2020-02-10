cbuffer WVP : register(b0)
{
	float4x4 transform;
};

float4 main(float4 pos : POSITION, float2 texcoord : TEXCOORD) : SV_POSITION
{
	return mul(pos, transform);
}