#include "game.h"
#include "states.h"

HWND g_hWnd = NULL;
WNDCLASS wndClass;

IDirect3DDevice9* d3dDevice;

LPDIRECTINPUT8 dInput; //	Direct Input object.
LPDIRECTINPUTDEVICE8  dInputKeyboardDevice; //	Direct Input keyboard device.

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		//	The message is post when we destroy the window.
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
		//	Default handling for other messages.
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void testFail(HRESULT hr, string message) {
	const char* str = message.c_str();
	if (FAILED(hr)) {
		MessageBox(NULL,
			TEXT(str),
			TEXT("Error!"),
			MB_OK);
	}
}

void createWindow(LPCSTR Title, int WINDOWWIDTH, int WINDOWHEIGHT) {
	//create box

	//clear box

	//	Set all members in wndClass to 0.
	ZeroMemory(&wndClass, sizeof(wndClass));

	//define class

	//	Filling wndClass. You are to refer to MSDN for each of the members details.
	//	These are the fundamental structure members to be specify, in order to create your window.
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hInstance = GetModuleHandle(NULL);//Instance;	//
	wndClass.lpfnWndProc = WindowProcedure;
	wndClass.lpszClassName = Title;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	//registers window

	//	Register the window.
	RegisterClass(&wndClass);

	//	Create the Window.

	//	You are to refer to MSDN for each of the parameters details.
	g_hWnd = CreateWindowEx(0, wndClass.lpszClassName, Title, WS_OVERLAPPEDWINDOW, 0, 100, WINDOWWIDTH, WINDOWHEIGHT, NULL, NULL, GetModuleHandle(NULL), NULL);
	ShowWindow(g_hWnd, 1);
	ShowCursor(true);

	//	Some interesting function to try out.
	//	ShowCursor(false);
}

bool createDirectX(int WINDOWWIDTH, int WINDOWHEIGHT) {
	HRESULT hr;
	//	Define Direct3D 9.
	IDirect3D9* direct3D9 = Direct3DCreate9(D3D_SDK_VERSION);

	//	Define how the screen presents.
	D3DPRESENT_PARAMETERS d3dPP;
	ZeroMemory(&d3dPP, sizeof(d3dPP));

	//	Refer to Direct3D 9 documentation for the meaning of the members.
	d3dPP.Windowed = true;
	d3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dPP.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dPP.BackBufferCount = 1;
	d3dPP.BackBufferWidth = WINDOWWIDTH;
	d3dPP.BackBufferHeight = WINDOWHEIGHT;
	d3dPP.hDeviceWindow = g_hWnd;

	//	Create a Direct3D 9 device.
	hr = direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dPP, &d3dDevice);
	testFail(hr, "d3dDevice");

	return true;
}

void createInput() {
	HRESULT hr;

	//	Create the Direct Input object.
	hr = DirectInput8Create(GetModuleHandle(NULL), 0x0800, IID_IDirectInput8, (void**)&dInput, NULL);
	testFail(hr, "dInput");

	//	Create the keyboard device.
	hr = dInput->CreateDevice(GUID_SysKeyboard, &dInputKeyboardDevice, NULL);
	testFail(hr, "keyboardDevice");

	//	Set the input data format.
	dInputKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);

	//	Set the cooperative level.
	dInputKeyboardDevice->SetCooperativeLevel(g_hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
}

void game::init(LPCSTR Title, int WINDOWWIDTH, int WINDOWHEIGHT)
{
	createWindow(Title, WINDOWWIDTH, WINDOWHEIGHT);
	if (!createDirectX(WINDOWWIDTH, WINDOWHEIGHT)) {
		MessageBox(NULL,
			TEXT("Failed to run createDirectX"),
			TEXT("Error!"),
			MB_OK);
	}
	createInput();

	dInputKeyboardDevice->Acquire();

	myTimer.init(60);
}

void cleanupWindow() {
	UnregisterClass(wndClass.lpszClassName, GetModuleHandle(NULL));
}

void cleanupDirectX() {
	//	Release the device when exiting.
	d3dDevice->Release();
	//	Reset pointer to NULL, a good practice.
	d3dDevice = NULL;

	//	Release keyboard mouse device.
	dInputKeyboardDevice->Unacquire();
	dInputKeyboardDevice->Release();
	dInputKeyboardDevice = NULL;

	//	Release DirectInput.
	dInput->Release();
	dInput = NULL;
}

void game::cleanup()
{
	cleanupDirectX();
	cleanupWindow();
}

void game::changeState(states* state)
{
	// cleanup the current state
	if (!stateStack.empty()) {
		stateStack.back()->cleanup();
		stateStack.pop_back();
	}

	// store and init the new state
	stateStack.push_back(state);
	stateStack.back()->init(d3dDevice);
}

void game::pushState(states* state)
{
	// pause current state
	if (!stateStack.empty()) {
		stateStack.back()->pause();
	}

	// store and init the new state
	stateStack.push_back(state);
	stateStack.back()->init(d3dDevice);
}

void game::popState()
{
	// cleanup the current state
	if (!stateStack.empty()) {
		stateStack.back()->cleanup();
		stateStack.pop_back();
	}

	// resume previous state
	if (!stateStack.empty()) {
		stateStack.back()->resume();
	}
}

void game::getInput()
{
	stateStack.back()->getInput(this, dInputKeyboardDevice);
}

void game::update()
{
	stateStack.back()->update(this, myTimer.framesToUpdate(), scoreOne, scoreTwo);
}

void game::render()
{
	stateStack.back()->render(this, d3dDevice);
}

void game::playSound()
{
	stateStack.back()->playSound(this);
}

bool game::running()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	int count = 0;

	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		//	Receive a quit message
		if (msg.message == WM_QUIT) {
			return false;
		}
		//	Translate the message, converts the message format back to the correct one
		TranslateMessage(&msg);
		//	Send message to your window procedure
		DispatchMessage(&msg);
	}
	return true;
}