#pragma once

#include <d3d11.h>
#include <directxmath.h>
using namespace DirectX;

#include "textureclass.h"

class ModelClass
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
	};

public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();

	bool initialize(ID3D11Device*, ID3D11DeviceContext*, char*);
	void shutdown();
	void render(ID3D11DeviceContext*);

	int getIndexCount();
	ID3D11ShaderResourceView* getTexture();

private:
	bool initializeBuffers(ID3D11Device*);
	void shutdownBuffers();
	void renderBuffers(ID3D11DeviceContext*);

	bool loadTexture(ID3D11Device*, ID3D11DeviceContext*, char*);
	void releaseTexture();

private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	TextureClass* m_Texture;
};