#include "fontManager.h"

//-----------------------------------------------------------------------------------
//! @brief �R���X�g���N�^
//-----------------------------------------------------------------------------------
GT2FontManager::GT2FontManager()
{

}

//-----------------------------------------------------------------------------------
//! @brief �f�X�g���N�^
//-----------------------------------------------------------------------------------
GT2FontManager::~GT2FontManager()
{

}


//-----------------------------------------------------------------------------------
//! @brief �t�H���g�p�X�̒ǉ��A��΃p�X�A���΃p�X
//! @param  [in] path
//! @return ���������ꍇ��true��Ԃ�
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