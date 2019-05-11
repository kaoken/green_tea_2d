#include "main.h"
#include <windows.h>


#ifdef _WIN32
	INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
	int main(int argc, char *argv[])
#endif
	{
#if defined(_WIN32) && defined(_DEBUG)
		// デバッグビルド実行時にメモリチェックを有効
		// '出力'ウィンドウには、すべてのリークを（デバッグモード）ダンプ作る。
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
		_CrtSetBreakAlloc(1);
		//_crtBreakAlloc = 454;
#endif
		GameApp app;
		app.Go();
		
		return 0;
	}
