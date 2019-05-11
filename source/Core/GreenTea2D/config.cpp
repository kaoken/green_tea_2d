#include "../GreenTea2D.h"
#include <Util/filesystem.h>
#include <Graphics/Font/fontManager.h>
//#include <MCLib/script/add/scriptbuilder.h>
//#include <MCLib/dx11/DXFontMgr.h>


//-----------------------------------------------------------------------------------
//! @brief コンストラクタ
//-----------------------------------------------------------------------------------
GT2Config::GT2Config()
{	
	m_minCPU_MHz			= 0;
	m_isPauseAppFromPauseKey=false;
	m_minMemorySize			= 0;
	m_minVideoMemorySize	= 0;
	m_minTextureSize		= 0;

	m_appClassName			= _T("CMainGame");
	m_windowTitle			= _T("no title");
	m_startState			= _T("");
	m_width					= 640;
	m_height				= 480;
	m_isConstantFrameTime	= true;
	m_TimePerFrame			= 1.0f / 60.0f;
	m_isWaitFrameTime		= true;
	m_WaitTimePerFrame		= 1.0f / 60.0f;

	m_isFullScreen					= false;
	m_isWindowMaximizeButton		= false;
	m_isWindowMinimizeButton		= false;
	m_isResizableWindow				= false;
	m_isFullScreenFromAltEnterKey	= false;
	m_isExitAppFromALtF4Key			= false;
	m_isExitAppFromEscKey			= false;
}

//-----------------------------------------------------------------------------------
//! @brief デストラクタ
//-----------------------------------------------------------------------------------
GT2Config::~GT2Config()
{
}


//-----------------------------------------------------------------------------------
//! @brief 状態を登録する
//! @param [in] stateName ユニークなステート名
//! @param [in] filePath  ローカルパス
//! @param [in] className クラス名
//! @return 状態を登録できた場合、0を返す
//-----------------------------------------------------------------------------------
int GT2Config::RegisterState(const TString& stateName, const TString& filePath, const TString& className)
{
	auto rc = m_registrationStates.insert(gtMkPair(stateName, GT2PathAndClass(filePath, className)));

	if (!rc.second)
	{
		//GT_EXCEPT_SCRIPT(_T("RegisterScreen() [%s]はすでに登録されています。"), stateName.c_str());
		return -1;
	}
	TString path;

	if (GT_FAILED(SimpleFindFilePath(&path, filePath.c_str(), GT2_SCRIPT_DIR))) {
		//GT_EXCEPT_SCRIPT(_T("RegisterScreen() ファイル[%s]は、存在しません。"), filePath.c_str());
		return -2;
	}
	return 0;
	// 
}
//-----------------------------------------------------------------------------------
//! @brief 開始時の状態を設定する
//! @return 開始状態を設定できた場合、trueを返す
//-----------------------------------------------------------------------------------
bool GT2Config::StartState(const TString& stateName)
{
	if (m_registrationStates.find(stateName) == m_registrationStates.end())
	{
		//GT_EXCEPT_SCRIPT(_T("StartState() [%s]は存在しません。"), stateName.c_str());
		return false;
	}

	m_startState = stateName;
	return  true;
}


//-----------------------------------------------------------------------------------
//! @brief 状態名からスクリプトで使用するクラス名を返す
//! @param [in]  stateName 状態名
//! @param [out] pOut      クラス名が渡される
//! @return 見つけた場合trueを返す
//-----------------------------------------------------------------------------------
std::string GT2Config::GetStateClassName(const TString& stateName) const
{
	auto i = m_registrationStates.find(stateName);
	if (i == m_registrationStates.end()) return "";

	return i->second.className;
}

////-----------------------------------------------------------------------------------
////! @brief 登録されたステートクラスのインクルードファイルをビルドする
////! @return 成功すればGT_S_OKを返す
////-----------------------------------------------------------------------------------
//gt2HRESULT GT2Config::BuildState(CScriptBuilder & builder) const
//{
//	std::string filePath;
//	int r;
//	for (auto& state : m_registrationStates) {
//		std::string t;
//		Convert_TCHAR_To_SJIS(state.second.path, &t);
//		gt2HRESULT hr = SimpleFindFilePathA(&filePath, t.c_str(), GT_SCRIPT_DIR_A);
//		if (hr != GT_S_OK)
//		{
//			ErrMsgBoxA("エラー発生", "%sファイルが存在しません。", t.c_str());
//			return FALSE;
//		}
//		r = builder.AddSectionFromFile(filePath.c_str());
//		if (r < 0)
//		{
//			ErrMsgBoxA("エラー発生", "%sファイル内で構文エラーがあります。", t.c_str());
//			return FALSE;
//		}
//	}
//	return GT_S_OK;
//}
//-----------------------------------------------------------------------------------
//! @brief フォントを追加する
//-----------------------------------------------------------------------------------
bool GT2Config::AddFontPath(const TString & path)
{
	return g_FontMgr.AddFontPath(path);
}


