#pragma once

#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "textureshaderclass.h"


const bool g_fullScreen = false;
const bool g_vsyncEnabled = true;
const float g_farClip = 1000.f;
const float g_nearClip = .1f;


class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool initialize(int, int, HWND);
	void shutdown();
	bool frame();

private:
	bool render();

	D3DClass *m_d3d;
	CameraClass* m_Camera;
	ModelClass* m_Model;
	TextureShaderClass* m_TextureShader;
};