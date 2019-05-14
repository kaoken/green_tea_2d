#pragma once
#include <Core\greenTea2D.h>

/**
 * �`�悷��t�H���g���Ǘ�����
 */
class GT2FontManager : public CSingleton<GT2FontManager>{
private:
	std::vector<std::wstring> mc_filePaths;

public:
	GT2FontManager();
	~GT2FontManager();

	bool AddFontPath(const TString& path);
};

//! @name CDXImgResMgr�V���O���g���N���X�փA�N�Z�X
//@{
#define g_FontMgr		GT2FontManager::GetSingleton()
#define g_FontMgrPtr	GT2FontManager::GetSingletonPtr()
//@}