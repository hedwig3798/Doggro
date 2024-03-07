Texture2D DeferredTexture : register(t0);

SamplerState f_Sampler : register(s0);

struct PS_POSTFX_INPUT
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD0;
};

float4 PS(PS_POSTFX_INPUT input) : SV_Target
{
	//DeferredTexture
	float4 DTexture = DeferredTexture.Sample(f_Sampler, input.Tex);
	
	return DTexture;

}