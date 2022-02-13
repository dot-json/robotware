#include "framework.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WndPrc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


bool dx::initWinClass(const char* winClassName) {

	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = DefWindowProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = GetModuleHandle(NULL);
	wndClass.hIcon = NULL;
	wndClass.hCursor = NULL;
	wndClass.hbrBackground = NULL;
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = winClassName;
	wndClass.hIconSm = NULL;

	if (!RegisterClassEx(&wndClass))
		return false;

	return true;
}

void dx::destroyWinClass() {
	UnregisterClass(wndClass.lpszClassName, wndClass.hInstance);
}

bool dx::initWindow(const char* winName) {
	window = CreateWindow(wndClass.lpszClassName, winName, WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, 0, 0, wndClass.hInstance, 0);
	if (!window)
		return false;
	return true;
}

void dx::destroyWindow() {
	if (window)
		DestroyWindow(window);
}

bool dx::setupDX() {
	const auto dxHandle = GetModuleHandle("d3d9.dll");
	if (!dxHandle)
		return false;
	using CreateFn = LPDIRECT3D9(__stdcall*)(UINT);
	const auto dxCreate = reinterpret_cast<CreateFn>(GetProcAddress(dxHandle, "Direct3DCreate9"));
	if (!dxCreate)
		return false;
	d3d9 = dxCreate(D3D_SDK_VERSION);
	if (!d3d9)
		return false;

	D3DPRESENT_PARAMETERS params = {};
	params.BackBufferWidth = 0;
	params.BackBufferHeight = 0;
	params.BackBufferFormat = D3DFMT_UNKNOWN;
	params.BackBufferCount = 0;
	params.MultiSampleType = D3DMULTISAMPLE_NONE;
	params.MultiSampleQuality = NULL;
	params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	params.hDeviceWindow = window;
	params.Windowed = 1;
	params.EnableAutoDepthStencil = 0;
	params.AutoDepthStencilFormat = D3DFMT_UNKNOWN;
	params.Flags = NULL;
	params.FullScreen_RefreshRateInHz = 0;
	params.PresentationInterval = 0;

	if (d3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_NULLREF, window, D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_DISABLE_DRIVER_MANAGEMENT, &params, &dev) < 0) 
		return false;

	return true;
}

void dx::destroyDX() {
	if (dev) {
		dev->Release();
		dev = NULL;
	}
	if (d3d9) {
		d3d9->Release();
		d3d9 = NULL;
	}
}

void dx::init() {
	if (!initWinClass("RWClass001"))
		throw std::runtime_error("WinClassInit Failed!");
	if (!initWindow("RobotWare"))
		throw std::runtime_error("WindowInit Failed!");
	if (!setupDX())
		throw std::runtime_error("DXInit Failed!");
	destroyWindow();
	destroyWinClass();
}

void dx::initMenu(LPDIRECT3DDEVICE9 dev) {
	auto params = D3DDEVICE_CREATION_PARAMETERS{};
	dev->GetCreationParameters(&params);
	window = params.hFocusWindow;
	oWndPrc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WndPrc)));

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	loadImCfg();

	ImFontConfig font1_cfg, font2_cfg;
	font1_cfg.FontDataOwnedByAtlas = false;
	font2_cfg.FontDataOwnedByAtlas = false;

	font_menu = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\bahnschrift.ttf", 18.f);
	font_menu_info = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\bahnschrift.ttf", 15.f);
	font_Futura_25 = io.Fonts->AddFontFromMemoryTTF(rawdata::futuraFontData, 38134, 25.f, &font1_cfg);
	font_Futura_12 = io.Fonts->AddFontFromMemoryTTF(rawdata::futuraFontData, 38134, 18.f, &font2_cfg);

	loadTextureFromMEM(dev, &tabTextures[0], rawdata::asTabData, 5383);
	loadTextureFromMEM(dev, &tabTextures[1], rawdata::visTabData, 3880);
	loadTextureFromMEM(dev, &tabTextures[2], rawdata::miscTabData, 3265);
	loadTextureFromMEM(dev, &tabTextures[3], rawdata::settingsTabData, 4911);

	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX9_Init(dev);

	setup = true;
}

void dx::render() {
	ImGui_ImplWin32_NewFrame();
	ImGui_ImplDX9_NewFrame();
	ImGui::NewFrame();

	renderMenu();

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

void dx::shutdown() {
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	SetWindowLongPtr(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(oWndPrc));
	destroyDX();
}

bool dx::loadTextureFromMEM(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DTEXTURE9* pTexture, BYTE* pSrcData, UINT size) {
	IDirect3DTexture9* texture;
	if (D3D_OK == D3DXCreateTextureFromFileInMemory(pDevice, pSrcData, size, &texture)) {
		*pTexture = texture;
		return true;
	}
	return false;
}

LRESULT CALLBACK WndPrc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	if (msg == WM_KEYUP && wParam == VK_INSERT) {
		dx::mOpen = !dx::mOpen;
	}

	if (dx::mOpen) {
		ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
		return 1l;
	}

	return CallWindowProc(dx::oWndPrc, hWnd, msg, wParam, lParam);
}