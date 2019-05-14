#include "GameApp.h"

bool ManagerDeploy::ms_isDeploy = false;
bool ManagerDeploy::Deploy()
{
	// 01: ���K�[�̏�����
	try {
		m_pLogger = new Logger();
	}
	catch (const spdlog::spdlog_ex & ex) {
		ErrMsgBoxA(std::string("Error"), "Log failed: %s\n", ex.what());
		return false;
	}
	return true;
}

GameApp::GameApp()
{
	m_pMutex = nullptr;
	m_TimeSinceLastFrame = 0.0f;
	m_FPS = 0.0f;
	m_Initialize = false;/*
	M_GET_PUB_SET_PRI(float, TimeSinceLastFrame, UTIL_RECUTSIVE_LOCK())
		M_GET_PUB_SET_PRI(float, FPS, UTIL_RECUTSIVE_LOCK())
		M_IS_PUB_SET_PRI(Initialize, UTIL_RECUTSIVE_LOCK())*/

}

GameApp::~GameApp()
{
	if(m_pMutex)
		SDL_DestroyMutex(m_pMutex);
}

//-----------------------------------------------------------------------------------

void GameApp::Initialize()
{
	if (!m_managerDeploy.Deploy())throw "";
	//----------------------------------------------------------------------
	// �~���[�e�b�N�X
	//----------------------------------------------------------------------
	m_pMutex = SDL_CreateMutex();
	if (!m_pMutex) {
		throw new std::exception("�~���[�e�b�N�X�͍쐬�ς݂ł�\n");
	}

	if (SDL_LockMutex(m_pMutex) == 0) {
		/* Do stuff while mutex is locked */
		SDL_UnlockMutex(m_pMutex);
	}
	else {
		throw new std::exception("�~���[�e�b�N�X�����b�N�ł��܂���ł���\n");
	}
	this->SetInitialize(true);
}

//-----------------------------------------------------------------------------------

/**
 * �Q�[���܂��̓V�X�e���̏�Ԃ�ǂݍ���
 */
void GameApp::Configure()
{
	//----------------------------
	// �R���t�B�O�̓ǂݍ���
	//----------------------------
	PYConfig pyConfig;
	pyConfig.Run();
}

//-----------------------------------------------------------------------------------

bool GameApp::Setup()
{
	//----------------------------
	// �C�x���g�}�l�[�W���[
	//----------------------------
	//m_pEventManager = new EventManager(_T("MCAS_EventManager"), true);
	//MC_IF_EXCEPT_EX_OUTOFMEMORY(m_pEventManager, _T("new EventManager"), _T("CASAppMain::CASAppMain()"));

	//----------------------------
	// �R���t�B�O
	//----------------------------
	Configure();


	//----------------------------
	// AS���C���E�X�N���v�g�쐬
	//----------------------------
	//m_pASAppMain = new ASAppMain(&m_config);
	//MC_IF_EXCEPT_EX_OUTOFMEMORY(m_pASAppMain, _T("new CASAppMain"), _T("GameApp::Configure()"));

	// AS��APPMAin������������
	//std::string className;
	//Convert_TCHAR_To_SJIS(m_config.GetAppClassName(), &className);
	//m_pASAppMain->Initialization(className.c_str());

	//##########################################
	//### 05: �Q�[�����s
	//##########################################
	//------------------------------------------
#ifdef MC_DIRECTX
	this->SetCallBackDXUTFunctions(true, nullptr);
	this->SetIsInGammaCorrectMode(true);
	this->DXUTInit(false, true, _T("DXCreateWindow"), true);
	this->SetCursorSettings(true, true);
	this->SetHotkeyHandling(
		m_config.GetFullScreenFromAltEnterKey(),
		m_config.GetExitAppFromEscKey(),u
		m_config.GetPauseAppFromPauseKey(),
		m_config.GetExitAppFromALtF4Key()
	);
	this->SetWindowStyle(
		m_config.GetWindowMinimizeButton(),
		m_config.GetWindowMaximizeButton(),
		m_config.GetResizableWindow()
	);
	this->SetConstantFrameTime(m_config.IsConstantFrameTime(), m_config.GetTimePerFrame());
	//this->SetWaitFrameTime(m_config.IsWaitFrameTime(), m_config.GetWaitTimePerFrame());

	gt2HRESULT hr;
	if (MC_FAILED(hr = this->DXCreateWindow(m_config.GetTitle().c_str(), nullptr))) {
		mc_tstringstream ss;
		ss << std::uppercase << std::setfill(_T('0')) << std::setw(4) << std::hex;
		ss << _T("�E�B���h�E�쐬�Ɏ��s���܂����B[0x");
		ss << hr << _T("]");
		this->Shutdown(this->GetExitCode());
		MC_EXCEPT_EX(MCException::ERR_INTERNAL_ERROR, ss.str().c_str(), _T("DirectX11 Device"));
	}
	//ASOutputDialogInit(this->GetHINSTANCE(), this->GetHWND());

	// DirectX11 Device �쐬
	hr = this->CreateDevice(D3D_FEATURE_LEVEL_11_0, true, m_config.GetWidth(), m_config.GetHeight());
	if (MC_FAILED(hr)) {
		mc_tstringstream ss;
		ss << std::uppercase << std::setfill(_T('0')) << std::setw(4) << std::hex;
		ss << _T("�f�o�C�X�쐬�Ɏ��s���܂����B[0x");
		ss << hr << _T("]");
		this->Shutdown(this->GetExitCode());
		MC_EXCEPT_EX(MCException::ERR_INTERNAL_ERROR, ss.str().c_str(), _T("DirectX11 Device"));
	}
#endif

	//----------------------------
	// ���̓f�o�C�X�̏�����
	//----------------------------
//	OIS::ParamList pl;
//#if defined(_WIN32) || defined(_WIN64)
//	std::ostringstream windowHndStr;
//	windowHndStr << std::dec << (uint64_t)this->GetHWND();
//	pl.insert(mcMkPair(std::string("WINDOW"), windowHndStr.str()));
//	pl.insert(mcMkPair(std::string("w32_mouse"), "DISCL_FOREGROUND"));
//	pl.insert(mcMkPair(std::string("w32_mouse"), "DISCL_NONEXCLUSIVE"));
//#else
//
//#endif;
//	hr = m_managerDeploy.GetInputDevice()->Initialization(pl, this, this, this);
//	if (MC_FAILED(hr)) {
//		mc_tstringstream ss;
//		ss << std::uppercase << std::setfill(_T('0')) << std::setw(4) << std::hex;
//		ss << _T("���̓f�o�C�X�쐬�Ɏ��s���܂����B[0x");
//		ss << hr << _T("]");
//
//		MC_EXCEPT_EX(MCException::ERR_INTERNAL_ERROR, ss.str().c_str(), _T("Input Device"));
//	}

	//----------------------------
	// ���\�[�X�̐ݒ�
	//----------------------------
	//SetupResources();


	//----------------------------
	// SceneManager���쐬��
	//----------------------------
	//m_pSceneMgr = m_pRoot->createSceneManager(ST_GENERIC);

	//----------------------------
	// �T�E���h���쐬��
	//----------------------------
	//m_pSoundMgr->Init();

	//----------------------------
	// �Œ�X�v���C�g�J�����Ƃ���
	//----------------------------
	//CreateCamera();

	//---------------------------------------------------------------------------
	// �r���[�|�[�g�쐬
	//---------------------------------------------------------------------------
	// �r���[�|�[�g���쐬���A�E�B���h�E�S��
	//m_spCamera->BindViewport(m_pRenderWnd);



	// �ݒ肳�ꂽ�f�t�H���g�̃~�b�v�}�b�v���x���iNB�͈ꕔ��API�͂���𖳎�����j
	//TextureManager::getSingleton().setDefaultNumMipmaps(5);

	// �C�ӂ̃��\�[�X���X�i�[���쐬���܂��B�i���[�f�B���O�X�N���[���p�j
	//CreateResourceListener();
	// ���\�[�X�̃��[�h
	//LoadResources();



	//==========================
	// AS����쐬����
	//==========================
	//hr = m_pASAppMain->OnDeviceCreated();
	//if (MC_FAILED(hr)) return false;


	return true;
}


//-----------------------------------------------------------------------------------

void GameApp::Go()
{
	try {


		if (!this->IsInitialize()) {
			this->Initialize();
		}
		if (Setup()) {


			//ChangeAppState(pState);
		}
	}
	catch (std::exception &e) {
		ErrMsgBoxA("Error", e.what());
	}

}