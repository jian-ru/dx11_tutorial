#pragma once

// speed up build by excluding some headers
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include "inputclass.h"
#include "graphicsclass.h"

class SystemClass
{
public:
	SystemClass();
	SystemClass(const SystemClass &);
	~SystemClass();

	bool initialize();
	void run();
	void shutdown();

	LRESULT CALLBACK msgHandler(HWND, UINT, WPARAM, LPARAM);

private:
	bool frame();
	void initializeWindows(int &, int &);
	void shutdownWindows();

	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;

	InputClass *m_input;
	GraphicsClass *m_graphics;
};

static LRESULT CALLBACK wndProc(HWND, UINT, WPARAM, LPARAM);

static SystemClass *g_applicationHandle = 0;