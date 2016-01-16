#pragma once

// specify the libraries to link
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;

class D3DClass
{
public:
	D3DClass();
	D3DClass(const D3DClass &);
	~D3DClass();

	bool initialize(int, int, bool, HWND, bool, float, float);
	void shutdown();

	void beginScene(float, float, float, float);
	void endScene();

	ID3D11Device* getDevice();
	ID3D11DeviceContext* getDeviceContext();

	void getProjectionMatrix(XMMATRIX &);
	void getWorldMatrix(XMMATRIX &);
	void getOrthoMatrix(XMMATRIX &);

	void getVideoCardInfo(char *, int &);

private:
	bool m_vsyncEnabled;
	int m_videoCardMemory;
	char m_videoCardDescription[128];
	IDXGISwapChain* m_swapChain;
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;
	ID3D11RenderTargetView* m_renderTargetView;
	ID3D11Texture2D* m_depthStencilBuffer;
	ID3D11DepthStencilState* m_depthStencilState;
	ID3D11DepthStencilView* m_depthStencilView;
	ID3D11RasterizerState* m_rasterState;
	XMMATRIX m_projectionMatrix;
	XMMATRIX m_worldMatrix;
	XMMATRIX m_orthoMatrix;
};