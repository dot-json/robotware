#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
#include <thread>
#include <stdexcept>
#include <intrin.h>

#include <d3d9.h>
#include <D3dx9tex.h>
#pragma comment(lib, "D3dx9")

#include <MinHook.h>
#pragma comment(lib, "libMinHook.x86.lib")

#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"

#include "dx.hpp"
#include "hooks.hpp"
#include "rawdata.hpp"