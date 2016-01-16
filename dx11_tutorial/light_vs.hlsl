cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

struct VertexInputType
{
	float4 position : POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
};

PixelInputType lightVertexShader(VertexInputType input)
{
	PixelInputType output;

	input.position.w = 1.f;
	output.position = mul(mul(mul(input.position, worldMatrix), viewMatrix), projectionMatrix);
	output.tex = input.tex;
	output.normal = input.normal;

	return output;
}