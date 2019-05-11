#pragma once
#include <Core\greenTea2D.h>

/**
 * 描画するフォントを管理する
 */
class GT2FontManager : public CSingleton<GT2FontManager>{
private:
	std::vector<std::wstring> mc_filePaths;

public:
	GT2FontManager();
	~GT2FontManager();

	bool AddFontPath(const TString& path);
};

//! @name CDXImgResMgrシングルトンクラスへアクセス
//@{
#define g_FontMgr		GT2FontManager::GetSingleton()
#define g_FontMgrPtr	GT2FontManager::GetSingletonPtr()
//@}