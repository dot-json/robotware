#include "framework.h"

#pragma warning (disable : 26812)

DWORD WINAPI EntryThread(HMODULE module) {
    dx::init();
    hooks::init();
    
    //MessageBeep(MB_OK);
    Beep(500, 350);

    while (!GetAsyncKeyState(VK_END)) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    hooks::detach();
    dx::shutdown();

    Beep(400, 350);

    FreeLibraryAndExitThread(module, EXIT_SUCCESS);
    return 0;
}

BOOL APIENTRY DllMain( HINSTANCE instance,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    HANDLE eThread = NULL;
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        eThread = CreateThread(NULL, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(EntryThread), instance, NULL, nullptr);
    }
    if (ul_reason_for_call == DLL_PROCESS_DETACH) {
        if (eThread)
            CloseHandle(eThread);
    }

    return TRUE;
}

