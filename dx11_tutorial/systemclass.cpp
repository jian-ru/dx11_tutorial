#include "systemclass.h"

SystemClass::SystemClass()
{
	m_input = NULL;
	m_graphics = NULL;
}

SystemClass::SystemClass(const SystemClass &other) {}

SystemClass::~SystemClass() {}

bool SystemClass::initialize()
{
	int screenWidth, screenHeight;
	bool result;

	screenWidth = 0;
	screenHeight = 0;

	initializeWindows(screenWidth, screenHeight);

	m_input = new InputClass;
	if (!m_input)
	{
		return false;
	}

	m_input->initialize();

	m_graphics = new GraphicsClass;
	if (!m_graphics)
	{
		return false;
	}

	result = m_graphics->initialize(screenWidth, screenHeight, m_hwnd);
	if (!result)
	{
		return false;
	}

	return true;
}

void SystemClass::shutdown()
{
	if (m_graphics)
	{
		m_graphics->shutdown();
		delete m_graphics;
		m_graphics = NULL;
	}

	if (m_input)
	{
		delete m_input;
		m_input = NULL;
	}

	shutdownWindows();
}

void SystemClass::run()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while (true)
	{
		// hanlde the windows messages/events
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
		{
			break;
		}
		else
		{
			if (!frame())
			{
				break;
			}
		}
	}
}

bool SystemClass::frame()
{
	if (m_input->isKeyDown(VK_ESCAPE))
	{
		return false;
	}

	// render scene
	if (!m_graphics->frame())
	{
		return false;
	}

	return true;
}

LRESULT CALLBACK SystemClass::msgHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	switch (umsg)
	{
	case WM_KEYDOWN:
		m_input->keyDown((unsigned int)wparam);
		return 0;
	case WM_KEYUP:
		m_input->keyUp((unsigned int)wparam);
		return 0;
	default:
		// default message handler
		return DefWindowProc(hwnd, umsg, wparam, lparam);
	}
}

void SystemClass::initializeWindows(int &width, int &height)
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;

	g_applicationHandle = this;

	m_hinstance = GetModuleHandle(NULL);
	m_applicationName = L"dx11_tutorial";

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = wndProc; // redirect messages to SystemClass::msgHandler()
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	RegisterClassEx(&wc);

	// determine the resolution of the client's desktop screen
	width = GetSystemMetrics(SM_CXSCREEN);
	height = GetSystemMetrics(SM_CYSCREEN);

	if (g_fullScreen)
	{
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)width;
		dmScreenSettings.dmPelsHeight = (unsigned long)height;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
		// set the position of the window to the top left corner
		posX = posY = 0;
	}
	else
	{
		width = 1600;
		height = 1200;
		posX = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;
	}

	// create window
	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
		posX, posY, width, height, NULL, NULL, m_hinstance, NULL);

	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

	ShowCursor(false);
}

void SystemClass::shutdownWindows()
{
	ShowCursor(true);

	// fix display settings if leaving full screen mode
	if (g_fullScreen)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	DestroyWindow(m_hwnd);
	m_hinstance = NULL;
	g_applicationHandle = NULL;
}

LRESULT CALLBACK wndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch (umessage)
	{
		// Check if the window is being destroyed.
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}

	// Check if the window is being closed.
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}

	// All other messages pass to the message handler in the system class.
	default:
	{
		return g_applicationHandle->msgHandler(hwnd, umessage, wparam, lparam);
	}
	}
}