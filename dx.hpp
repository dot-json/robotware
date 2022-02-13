#pragma once
struct smenu {
	float width;
	float height;
};

namespace dx {
	inline HWND window = nullptr;
	inline WNDCLASSEX wndClass = {};
	inline WNDPROC oWndPrc = nullptr;
	inline LPDIRECT3DDEVICE9 dev = nullptr;
	inline LPDIRECT3D9 d3d9 = nullptr;

	bool initWinClass(const char* winClassName);
	void destroyWinClass();
	bool initWindow(const char* winName);
	void destroyWindow();
	bool setupDX();
	void destroyDX();

	void init();

	inline bool mOpen = true;
	inline ImFont* font_menu = nullptr;
	inline ImFont* font_menu_tab = nullptr;
	inline ImFont* font_menu_info = nullptr;
	inline ImFont* font_Futura_25 = nullptr;
	inline ImFont* font_Futura_12 = nullptr;
	inline IDirect3DTexture9* logoTexture = NULL;
	inline IDirect3DTexture9* tabTextures[4] = {NULL, NULL, NULL, NULL};
	inline smenu menu = { 750.f, 460.f };
	inline const char* tabs[] = {"ASSISTANCE", "VISUALS", "MISC", "SETTINGS"};
	inline int selectedTab = 0;
	void initMenu(LPDIRECT3DDEVICE9 dev);
	bool loadTextureFromMEM(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DTEXTURE9* pTexture, BYTE* pSrcData, UINT size);
	void loadImCfg();
	void renderMenu();
	inline bool setup = false;

	void shutdown();
	void render();
}