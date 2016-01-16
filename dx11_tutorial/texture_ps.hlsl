Texture2D shaderTexture;
SamplerState sampleType;

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
};

float4  texturePixelShader(PixelInputType input) : SV_TARGET
{
	return shaderTexture.Sample(sampleType, input.tex);
}