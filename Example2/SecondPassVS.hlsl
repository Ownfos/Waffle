struct VS_OUTPUT
{
	float4 pos : SV_POSITION;
	float2 texcoord : TEXCOORD;
};

cbuffer WVP : register(b0)
{
	float4x4 transform;
};

VS_OUTPUT main(float4 pos : POSITION, float2 texcoord : TEXCOORD)
{
	VS_OUTPUT rtn;
	rtn.pos = pos;
	rtn.texcoord = texcoord;
	return rtn;
}