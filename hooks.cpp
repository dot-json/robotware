#include "framework.h"


void hooks::init() {
	if (MH_Initialize() != MH_OK)
		throw std::runtime_error("MHInit Failed!");

	if(MH_CreateHook(VirtualFn(dx::dev, 42), &EndScene, reinterpret_cast<void**>(&oEndScene)) != MH_OK)
		throw std::runtime_error("EndSceneHook Failed!");

	if (MH_CreateHook(VirtualFn(dx::dev, 16), &Reset, reinterpret_cast<void**>(&oReset)) != MH_OK)
		throw std::runtime_error("EndSceneHook Failed!");

	if(MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
		throw std::runtime_error("EnableHooks Failed!");

	dx::destroyDX();
}

void hooks::detach() {
	MH_DisableHook(MH_ALL_HOOKS);
	MH_RemoveHook(MH_ALL_HOOKS);
	MH_Uninitialize();
}

long __stdcall hooks::EndScene(IDirect3DDevice9* dev) {
	static const auto retAddr = _ReturnAddress();
	const auto result = oEndScene(dev, dev);

	if (_ReturnAddress() == retAddr)
		return result;
	if (!dx::setup)
		dx::initMenu(dev);
	if (dx::mOpen)
		dx::render();

	return result;
}

HRESULT __stdcall hooks::Reset(IDirect3DDevice9* dev, D3DPRESENT_PARAMETERS* params) {
	ImGui_ImplDX9_InvalidateDeviceObjects();
	const auto result = oReset(dev, dev, params);
	ImGui_ImplDX9_CreateDeviceObjects();
	return result;
}