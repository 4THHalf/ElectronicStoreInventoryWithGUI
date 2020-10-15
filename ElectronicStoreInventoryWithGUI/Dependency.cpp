#include "Dependency.h"

SystemClass::SystemClass() {}

SystemClass::SystemClass(const SystemClass& other) {}

SystemClass::~SystemClass() {}

bool SystemClass::Initialize() {
	int screenWidth, screenHeight;
	bool result;

	screenWidth = 0;
	screenHeight = 0;

	InitializeWindow(screenWidth, screenHeight);

	m_Input = new InputClass;
	if (!m_Input)
		return false;

	m_Input->Initialize();

	return true;
}

void SystemClass::Shutdown() {

	if (m_Input) {
		delete m_Input;
		m_Input = 0;
	}

	ShutdownWindow();

	return;
}

void SystemClass::Run() {

	MSG msg;
	bool done, result;

	ZeroMemory(&msg, sizeof(MSG));

	done = false;
	while (!done) {
	
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
		
			done = true;

		else {
			result = Frame();
			if (!result)
				done = true;
		}
	
	}

	return;

}

bool SystemClass::Frame() {

	bool result;

	if (m_Input->IsKeyDown(VK_ESCAPE))
		return false;
	else
		return true;

}

LRESULT CALLBACK SystemClass::MessageHandler(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {

	switch (msg) {
	
	case WM_KEYDOWN: {
		m_Input->KeyDown((unsigned int)wparam);
		return 0;
	}
	case WM_KEYUP: {
		m_Input->KeyUp((unsigned int)wparam);
		return 0;
	}
	default: {
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}
	
	}

}


void SystemClass::InitializeWindow(int& ScreenWidth, int& ScreenHeight) {

	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;

	ApplicationHandle = this;

	m_hinstance = GetModuleHandle(NULL);
	m_applicationName = L"DatabaseManager";

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hinstance;
	wc.hIcon = LoadIcon (m_hinstance, MAKEINTRESOURCE(IDI_ICON1));
	wc.hIconSm = LoadIcon (m_hinstance, MAKEINTRESOURCE(IDI_ICON1));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	RegisterClassEx(&wc);

	ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	ScreenHeight = GetSystemMetrics(SM_CYSCREEN);

	ScreenWidth = 800;
	ScreenHeight = 600;

	posX = (GetSystemMetrics(SM_CXSCREEN) - ScreenWidth) / 2;
	posY = (GetSystemMetrics(SM_CYSCREEN) - ScreenHeight) / 2;

	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName,
		WS_OVERLAPPEDWINDOW,
		posX, posY, ScreenWidth, ScreenHeight, NULL, NULL, m_hinstance, NULL);

	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

	ShowCursor(true);

	return;

}

void SystemClass::ShutdownWindow() {

	ShowCursor(true);

	DestroyWindow(m_hwnd);
	m_hwnd = NULL;

	UnregisterClass(m_applicationName, m_hinstance);
	m_hinstance = NULL;

	ApplicationHandle = NULL;

	return;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) {

	switch (message) {
	case WM_CREATE: {CreateWindow(L"BUTTON", L"MAMA MIA",
		WS_VISIBLE | WS_CHILD,
		20,
		50,
		80,
		25,
		hwnd, (HMENU)1, NULL, NULL);
		break;
	}
	case WM_COMMAND: {
		if (LOWORD(wparam) == 1) {
			PostQuitMessage(0);
		}
		return 0;
	}
	case WM_DESTROY: {
		PostQuitMessage(0);
		return 0;
	}
	case WM_CLOSE: {
		PostQuitMessage(0);
		return 0;
	}
	default: {
		return ApplicationHandle->MessageHandler(hwnd, message, wparam, lparam);
	}

	}

}
