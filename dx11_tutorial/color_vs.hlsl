cbuffer MatrixBuffer
{
	matrix modelMatrix;
	matrix viewMatrix;
	matrix projMatrix;
};

struct VertexInputType
{
	float4 position : POSITION;
	float4 color : COLOR;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

PixelInputType colorVertexShader(VertexInputType input)
{
	PixelInputType output;

	input.position.w = 1.f;
	output.position = mul(mul(mul(input.position, modelMatrix), viewMatrix), projMatrix);
	output.color = input.color;

	return output;
}