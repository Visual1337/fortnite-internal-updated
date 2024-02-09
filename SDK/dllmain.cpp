#include "includes.h"

//extern "C" __declspec (dllexport) int BattlEye(int code, WPARAM wParam, LPARAM lParam) { SPOOF_FUNC return CallNextHookEx(NULL, code, wParam, lParam); }

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved) {
	SPOOF_FUNC;

	if (reason == DLL_PROCESS_ATTACH) {
		UnrealEngine::init();
	}

	return TRUE;
}