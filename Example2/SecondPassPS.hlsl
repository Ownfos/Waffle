Texture2D t;
sampler s;

float4 main(float4 pos : SV_POSITION, float2 texcoord : TEXCOORD) : SV_TARGET
{
    return t.Sample(s, texcoord);
}