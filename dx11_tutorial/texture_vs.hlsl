cbuffer MatrixBuffer
{
	matrix modelMatrix;
	matrix viewMatrix;
	matrix projMatrix;
};

struct VertexInputType
{
	float4 position : POSITION;
	float2 tex : TEXCOORD0;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
};

PixelInputType textureVertexShader(VertexInputType input)
{
	PixelInputType output;

	input.position.w = 1.f;
	output.position = mul(mul(mul(input.position, modelMatrix), viewMatrix), projMatrix);
	output.tex = input.tex;

	return output;
}