#include "fontManager.h"

//-----------------------------------------------------------------------------------
//! @brief コンストラクタ
//-----------------------------------------------------------------------------------
GT2FontManager::GT2FontManager()
{

}

//-----------------------------------------------------------------------------------
//! @brief デストラクタ
//-----------------------------------------------------------------------------------
GT2FontManager::~GT2FontManager()
{

}


//-----------------------------------------------------------------------------------
//! @brief フォントパスの追加、絶対パス、相対パス
//! @param  [in] path
//! @return 成功した場合はtrueを返す
//-----------------------------------------------------------------------------------
bool GT2FontManager::AddFontPath(const TString& path)
{
	//if (this->IsBuild()) return false;
	gt2HRESULT hr;
	TString fullpath;

	//if (GT_FAILED(hr = SimpleFindFilePath(&fullpath, path.c_str(), GT2_FONT_DIR))) {
	//	return false;
	//}
	std::wstring fullPahtW;
#ifdef _UNICODE
	fullPahtW = fullpath;
#else
	Convert_TCHAR_To_UTF16(fullpath, &fullPahtW);
#endif
	mc_filePaths.push_back(fullPahtW);

	return true;
}