#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_d3d = NULL;
	m_Camera = NULL;
	m_Model = NULL;
	m_TextureShader = NULL;
}

GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}

GraphicsClass::~GraphicsClass()
{
}

bool GraphicsClass::initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	m_d3d = new D3DClass;
	if (!m_d3d)
	{
		return false;
	}

	if (!m_d3d->initialize(screenWidth, screenHeight, g_vsyncEnabled, hwnd,
		g_fullScreen, g_farClip, g_nearClip))
	{
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->setPosition(0.0f, 0.0f, -5.0f);

	// Create the model object.
	m_Model = new ModelClass;
	if (!m_Model)
	{
		return false;
	}

	// Initialize the model object.
	if (!m_Model->initialize(m_d3d->getDevice(), m_d3d->getDeviceContext(), "stone01.tga"))
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the color shader object.
	m_TextureShader = new TextureShaderClass;
	if (!m_TextureShader)
	{
		return false;
	}

	// Initialize the color shader object.
	if (!m_TextureShader->initialize(m_d3d->getDevice(), hwnd))
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}

void GraphicsClass::shutdown()
{
	// Release the color shader object.
	if (m_TextureShader)
	{
		m_TextureShader->shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	// Release the model object.
	if (m_Model)
	{
		m_Model->shutdown();
		delete m_Model;
		m_Model = 0;
	}

	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	if (m_d3d)
	{
		m_d3d->shutdown();
		delete m_d3d;
		m_d3d = NULL;
	}
}

bool GraphicsClass::frame()
{
	if (!render())
	{
		return false;
	}

	return true;
}

bool GraphicsClass::render()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;
	bool result;

	// Clear the buffers to begin the scene.
	m_d3d->beginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_d3d->getWorldMatrix(worldMatrix);
	m_Camera->getViewMatrix(viewMatrix);
	m_d3d->getProjectionMatrix(projectionMatrix);

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Model->render(m_d3d->getDeviceContext());

	// Render the model using the color shader.
	result = m_TextureShader->render(m_d3d->getDeviceContext(), m_Model->getIndexCount(),
		worldMatrix, viewMatrix, projectionMatrix, m_Model->getTexture());
	if (!result)
	{
		return false;
	}

	// swap buffers
	m_d3d->endScene();

	return true;
}