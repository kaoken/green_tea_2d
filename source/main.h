#pragma once


#include "GameApp.h"


#if defined(_WIN32) || defined(_WIN64)
#  pragma warning(disable:4819) // disable 「ファイルは、現在のコード ページ (932) で表示できない文字を含んでいます。データの損失を防ぐために、ファイルを Unicode 形式で保存してください。」
#  pragma region libs
#  pragma comment( lib, "python3.lib" )
#  pragma comment( lib, "python37.lib" )
#  pragma comment( lib, "SDL2.lib" )
#  pragma comment( lib, "SDL2main.lib" )
#  pragma comment( lib, "SDL2test.lib" )
#  pragma comment( lib, "SDL2_image.lib" )
#  pragma comment( lib, "SDL2_mixer.lib" )
#  pragma comment( lib, "SDL2_net.lib" )
#  pragma comment( lib, "SDL2_ttf.lib" )
#  pragma comment( lib, "icuuc.lib" )
#  pragma comment( lib, "Pdh.lib" )
#  if defined(_DEBUG)

#  else

#  endif
#  pragma endregion libs

#endif