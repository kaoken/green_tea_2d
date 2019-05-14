#include "main.h"
#include <windows.h>


#ifdef _WIN32
	INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
	int main(int argc, char *argv[])
#endif
	{
#if defined(_WIN32) && defined(_DEBUG)
		// �f�o�b�O�r���h���s���Ƀ������`�F�b�N��L��
		// '�o��'�E�B���h�E�ɂ́A���ׂẴ��[�N���i�f�o�b�O���[�h�j�_���v���B
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
		_CrtSetBreakAlloc(1);
		//_crtBreakAlloc = 454;
#endif
		GameApp app;
		app.Go();
		
		return 0;
	}
