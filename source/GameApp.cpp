#include "GameApp.h"

bool ManagerDeploy::ms_isDeploy = false;
bool ManagerDeploy::Deploy()
{
	// 01: ロガーの初期化
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
	// ミューテックス
	//----------------------------------------------------------------------
	m_pMutex = SDL_CreateMutex();
	if (!m_pMutex) {
		throw new std::exception("ミューテックスは作成済みです\n");
	}

	if (SDL_LockMutex(m_pMutex) == 0) {
		/* Do stuff while mutex is locked */
		SDL_UnlockMutex(m_pMutex);
	}
	else {
		throw new std::exception("ミューテックスをロックできませんでした\n");
	}
	this->SetInitialize(true);
}

//-----------------------------------------------------------------------------------

/**
 * ゲームまたはシステムの状態を読み込む
 */
void GameApp::Configure()
{
	//----------------------------
	// コンフィグの読み込み
	//----------------------------
	PYConfig pyConfig;
	pyConfig.Run();
}

//-----------------------------------------------------------------------------------

bool GameApp::Setup()
{
	//----------------------------
	// イベントマネージャー
	//----------------------------
	//m_pEventManager = new EventManager(_T("MCAS_EventManager"), true);
	//MC_IF_EXCEPT_EX_OUTOFMEMORY(m_pEventManager, _T("new EventManager"), _T("CASAppMain::CASAppMain()"));

	//----------------------------
	// コンフィグ
	//----------------------------
	Configure();


	//----------------------------
	// ASメイン・スクリプト作成
	//----------------------------
	//m_pASAppMain = new ASAppMain(&m_config);
	//MC_IF_EXCEPT_EX_OUTOFMEMORY(m_pASAppMain, _T("new CASAppMain"), _T("GameApp::Configure()"));

	// ASのAPPMAinを初期化する
	//std::string className;
	//Convert_TCHAR_To_SJIS(m_config.GetAppClassName(), &className);
	//m_pASAppMain->Initialization(className.c_str());

	//##########################################
	//### 05: ゲーム実行
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
		ss << _T("ウィンドウ作成に失敗しました。[0x");
		ss << hr << _T("]");
		this->Shutdown(this->GetExitCode());
		MC_EXCEPT_EX(MCException::ERR_INTERNAL_ERROR, ss.str().c_str(), _T("DirectX11 Device"));
	}
	//ASOutputDialogInit(this->GetHINSTANCE(), this->GetHWND());

	// DirectX11 Device 作成
	hr = this->CreateDevice(D3D_FEATURE_LEVEL_11_0, true, m_config.GetWidth(), m_config.GetHeight());
	if (MC_FAILED(hr)) {
		mc_tstringstream ss;
		ss << std::uppercase << std::setfill(_T('0')) << std::setw(4) << std::hex;
		ss << _T("デバイス作成に失敗しました。[0x");
		ss << hr << _T("]");
		this->Shutdown(this->GetExitCode());
		MC_EXCEPT_EX(MCException::ERR_INTERNAL_ERROR, ss.str().c_str(), _T("DirectX11 Device"));
	}
#endif

	//----------------------------
	// 入力デバイスの初期化
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
//		ss << _T("入力デバイス作成に失敗しました。[0x");
//		ss << hr << _T("]");
//
//		MC_EXCEPT_EX(MCException::ERR_INTERNAL_ERROR, ss.str().c_str(), _T("Input Device"));
//	}

	//----------------------------
	// リソースの設定
	//----------------------------
	//SetupResources();


	//----------------------------
	// SceneManagerを作成し
	//----------------------------
	//m_pSceneMgr = m_pRoot->createSceneManager(ST_GENERIC);

	//----------------------------
	// サウンドを作成し
	//----------------------------
	//m_pSoundMgr->Init();

	//----------------------------
	// 固定スプライトカメラとする
	//----------------------------
	//CreateCamera();

	//---------------------------------------------------------------------------
	// ビューポート作成
	//---------------------------------------------------------------------------
	// ビューポートを作成し、ウィンドウ全体
	//m_spCamera->BindViewport(m_pRenderWnd);



	// 設定されたデフォルトのミップマップレベル（NBは一部のAPIはこれを無視する）
	//TextureManager::getSingleton().setDefaultNumMipmaps(5);

	// 任意のリソースリスナーを作成します。（ローディングスクリーン用）
	//CreateResourceListener();
	// リソースのロード
	//LoadResources();



	//==========================
	// ASから作成する
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