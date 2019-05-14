#include "../GreenTea2D.h"
#include <Util/filesystem.h>
#include <Graphics/Font/fontManager.h>
//#include <MCLib/script/add/scriptbuilder.h>
//#include <MCLib/dx11/DXFontMgr.h>


//-----------------------------------------------------------------------------------
//! @brief �R���X�g���N�^
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
//! @brief �f�X�g���N�^
//-----------------------------------------------------------------------------------
GT2Config::~GT2Config()
{
}


//-----------------------------------------------------------------------------------
//! @brief ��Ԃ�o�^����
//! @param [in] stateName ���j�[�N�ȃX�e�[�g��
//! @param [in] filePath  ���[�J���p�X
//! @param [in] className �N���X��
//! @return ��Ԃ�o�^�ł����ꍇ�A0��Ԃ�
//-----------------------------------------------------------------------------------
int GT2Config::RegisterState(const TString& stateName, const TString& filePath, const TString& className)
{
	auto rc = m_registrationStates.insert(gtMkPair(stateName, GT2PathAndClass(filePath, className)));

	if (!rc.second)
	{
		//GT_EXCEPT_SCRIPT(_T("RegisterScreen() [%s]�͂��łɓo�^����Ă��܂��B"), stateName.c_str());
		return -1;
	}
	TString path;

	if (GT_FAILED(SimpleFindFilePath(&path, filePath.c_str(), GT2_SCRIPT_DIR))) {
		//GT_EXCEPT_SCRIPT(_T("RegisterScreen() �t�@�C��[%s]�́A���݂��܂���B"), filePath.c_str());
		return -2;
	}
	return 0;
	// 
}
//-----------------------------------------------------------------------------------
//! @brief �J�n���̏�Ԃ�ݒ肷��
//! @return �J�n��Ԃ�ݒ�ł����ꍇ�Atrue��Ԃ�
//-----------------------------------------------------------------------------------
bool GT2Config::StartState(const TString& stateName)
{
	if (m_registrationStates.find(stateName) == m_registrationStates.end())
	{
		//GT_EXCEPT_SCRIPT(_T("StartState() [%s]�͑��݂��܂���B"), stateName.c_str());
		return false;
	}

	m_startState = stateName;
	return  true;
}


//-----------------------------------------------------------------------------------
//! @brief ��Ԗ�����X�N���v�g�Ŏg�p����N���X����Ԃ�
//! @param [in]  stateName ��Ԗ�
//! @param [out] pOut      �N���X�����n�����
//! @return �������ꍇtrue��Ԃ�
//-----------------------------------------------------------------------------------
std::string GT2Config::GetStateClassName(const TString& stateName) const
{
	auto i = m_registrationStates.find(stateName);
	if (i == m_registrationStates.end()) return "";

	return i->second.className;
}

////-----------------------------------------------------------------------------------
////! @brief �o�^���ꂽ�X�e�[�g�N���X�̃C���N���[�h�t�@�C�����r���h����
////! @return ���������GT_S_OK��Ԃ�
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
//			ErrMsgBoxA("�G���[����", "%s�t�@�C�������݂��܂���B", t.c_str());
//			return FALSE;
//		}
//		r = builder.AddSectionFromFile(filePath.c_str());
//		if (r < 0)
//		{
//			ErrMsgBoxA("�G���[����", "%s�t�@�C�����ō\���G���[������܂��B", t.c_str());
//			return FALSE;
//		}
//	}
//	return GT_S_OK;
//}
//-----------------------------------------------------------------------------------
//! @brief �t�H���g��ǉ�����
//-----------------------------------------------------------------------------------
bool GT2Config::AddFontPath(const TString & path)
{
	return g_FontMgr.AddFontPath(path);
}


