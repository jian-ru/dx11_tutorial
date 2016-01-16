Texture2D shaderTexture;
SamplerState samplerState;

cbuffer LightBuffer
{
	float4 diffuseColor;
	float3 lightDirection; // in tangent space
	float padding;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
};

float4 lightPixelShader(PixelInputType input) : SV_TARGET
{
	float4 textureColor;
	float3 lightDir;
	float cosTheta;

	textureColor = shaderTexture.Sample(samplerState, input.tex);

	lightDir = -lightDirection;
	cosTheta = saturate(dot(input.normal, lightDir));

	return diffuseColor * textureColor * cosTheta;
}