#pragma once
#include <d3d9.h>

namespace hooks {
	void init();
	void detach();

	constexpr void* VirtualFn(void* thisptr, size_t id) {
		return (*static_cast<void***>(thisptr))[id];
	}

	using fnEndScene = long(__thiscall*)(void*, IDirect3DDevice9*);
	using fnReset = HRESULT(__thiscall*)(void*, IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);
	using fnSCP = BOOL(__stdcall*)(int, int);

	inline fnEndScene oEndScene = nullptr;
	inline fnReset oReset = nullptr;

	long __stdcall EndScene(IDirect3DDevice9* dev);
	HRESULT __stdcall Reset(IDirect3DDevice9* dev, D3DPRESENT_PARAMETERS* params);
}