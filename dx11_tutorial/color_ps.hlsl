struct PixelInputType
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

float4 colorPixelShader(PixelInputType input) : SV_TARGET
{
	return float4(input.color.rgb * .5f, input.color.a);
}