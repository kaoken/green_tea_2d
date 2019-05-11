#pragma once


/**
 *
 */
struct GT2PathAndClass
{
	TString path;		//!< 相対パスでのASファイル名
	TString className;	//!< 作成対象のクラス名
	//!< コンスタント
	GT2PathAndClass() {}
	//!< コンスタント
	GT2PathAndClass(const TString& s1, const TString& s2) :
		path(s1), className(s2) {}
};

typedef  std::map<TString, GT2PathAndClass> GT2StatePaths;


/**
 * このアプリのコンフィグのデータを扱う
 */
class GT2Config : public CSingleton<GT2Config>
{
private:
	TString		m_windowTitle;					//!< アプリタイトル
	TString		m_appClassName;					//!< アプリのクラス名
	uint32_t	m_width;						//!< 画面サイズの幅
	uint32_t	m_height;						//!< 画面サイズの高さ
	uint32_t	m_minCPU_MHz;					//!< 最小CPUの周波数（MHz）
	uint32_t	m_minMemorySize;				//!< 最小メモリーサイズ
	uint32_t	m_minVideoMemorySize;			//!< 最小ビデオメモリサイズ
	uint32_t	m_minTextureSize;				//!< 最小テクスチャーサイズ
	bool		m_isConstantFrameTime;			//!< 
	bool		m_isFullScreen;					//!< 初回の画面の状態
	float		m_TimePerFrame;					//!< 
	bool		m_isWaitFrameTime;				//!< 
	float		m_WaitTimePerFrame;				//!< 

	//------------------------------
	//! @name Windows系のみ
	//------------------------------
	//@{
	bool		m_isWindowMaximizeButton;		//!< ウィンドウの最大化ボタン
	bool		m_isWindowMinimizeButton;		//!< ウィンドウの最小化ボタン
	bool		m_isResizableWindow;			//!< ウィンドウの太枠からのリサイズ
	bool		m_isFullScreenFromAltEnterKey;	//!< Alt+Enterキーによるフルスクリーン
	bool		m_isExitAppFromALtF4Key;		//!< ALt+F4キーからアプリの終了
	bool		m_isExitAppFromEscKey;			//!< Escキーからアプリの終了
	bool		m_isPauseAppFromPauseKey;		//!< ポーズキーからアプリを一時停止
	//@}


	
	GT2StatePaths		m_registrationStates;	//!< 複数登録した状態名
	TString				m_startState;			//!< 開始ステート

protected:

public:
	//! コントラクタ
	GT2Config();
	//! デストラクタ
	virtual ~GT2Config();

	//------------------------------
	//! @name 最小 スペック
	//------------------------------
	//@{
	//! @brief アプリ（ソフト）名 をセット
	inline void SetTitle(const TString& title)			{ m_windowTitle = title; }
	//! @brief CPUの最小 MHz をセット
	inline void SetMinCPU_MHz(uint32_t mHz)				{ m_minCPU_MHz = mHz; }
	//! @brief 最小メモリサイズ をセット
	inline void SetMinMemorySize(uint32_t mByte)		{ m_minMemorySize = mByte; }
	//! @brief 最小ビデオメモリサイズ をセット
	inline void SetMinVideoMemorySize(uint32_t mByte)	{ m_minVideoMemorySize = mByte; }
	//! @brief 最小テクスチャーサイズ をセット
	inline void SetMinTextureSize(uint32_t size)		{ m_minTextureSize = size; }
	//@}

	//! @brief main.mc2dファイル内の最初に呼び出されるクラス名 をセット
	inline void SetAppClassName(const TString& name) { m_appClassName = name; }
	//! @brief main.mc2dファイル内の最初に呼び出されるクラス名 を取得
	inline const TString& GetAppClassName() { return m_appClassName; }


	//------------------------------
	//! @name Windows系のみ
	//------------------------------
	//@{
	//! @brief ウィンドウの最大化ボタン を取得
	inline bool GetWindowMaximizeButton()		const { return m_isWindowMaximizeButton; }
	//! @brief ウィンドウの最大化ボタン をセット
	inline void SetWindowMaximizeButton(bool b)		  { m_isWindowMaximizeButton = b; }
	//! @brief  ウィンドウの最小化ボタン を取得
	inline bool GetWindowMinimizeButton()		const { return m_isWindowMinimizeButton; }
	//! @brief  ウィンドウの最小化ボタン をセット
	inline void SetWindowMinimizeButton(bool b)		  { m_isWindowMinimizeButton = b; }
	//! @brief  ウィンドウの太枠からのリサイズ を取得
	inline bool GetResizableWindow()			const { return m_isResizableWindow; }
	//! @brief  ウィンドウの太枠からのリサイズ をセット
	inline void SetResizableWindow(bool b)			  { m_isResizableWindow = b; }
	//! @brief  Alt+Enterキーによるフルスクリーンを取得
	inline bool GetFullScreenFromAltEnterKey()	const { return m_isFullScreenFromAltEnterKey; }
	//! @brief  Alt+Enterキーによるフルスクリーン をセット
	inline void SetFullScreenFromAltEnterKey(bool b)  { m_isFullScreenFromAltEnterKey = b; }
	//! @brief  ALt+F4キーからアプリの終了 を取得
	inline bool GetExitAppFromALtF4Key()		const { return m_isExitAppFromALtF4Key; }
	//! @brief  ALt+F4キーからアプリの終了 をセット
	inline void SetExitAppFromALtF4Key(bool b)		  { m_isExitAppFromALtF4Key = b; }
	//! @brief  Escキーからアプリの終了 を取得
	inline bool GetExitAppFromEscKey()			const { return m_isExitAppFromEscKey; }
	//! @brief  Escキーからアプリの終了 をセット
	inline void SetExitAppFromEscKey(bool b)		  { m_isExitAppFromEscKey = b; }
	//! @brief  ポーズキーからアプリを一時停止 を取得
	inline bool GetPauseAppFromPauseKey()		const { return m_isPauseAppFromPauseKey; }
	//! @brief  ポーズキーからアプリを一時停止 をセット
	inline void SetPauseAppFromPauseKey(bool b)		  { m_isPauseAppFromPauseKey = b; }
	//! @brief 開始画面がフルスクリーンか？
	inline void SetFullScreen(bool b)				  { m_isFullScreen = b; }
	//@}


	//------------------------------
	//! @name PCなどの最小スペックチェック
	//------------------------------
	//@{
	//! @brief  CPUxxxMHzより小さいかチェックする
	inline uint32_t GetMinCPU_MHz()			const { return m_minCPU_MHz; }
	//! @brief  通常メモリサーズxxxMBより小さいかチェックする
	inline uint32_t GetMinMemorySize()		const { return m_minMemorySize; }
	//! @brief  ビデオカードのメモリサーズxxxMBより小さいかチェックする
	inline uint32_t GetMinVideoMemorySize() const { return m_minVideoMemorySize; }
	//! @brief  サポートされているテクスチャーサイズxxxより小さいかチェック @n
	//! 1024,2048,4096,8192のいずれか
	inline uint32_t GetMinTextureSize()		const { return m_minTextureSize; }
	//@}


	int RegisterState(const TString& stateName, const TString& filePath, const TString& className);
	std::string GetStateClassName(const TString& stateName) const;
	bool StartState(const TString& stateName);
	bool AddFontPath(const TString& path);
};

#define gGt2ConfigPtr	GT2Config::GetSingletonPtr()
#define gGt2Config		GT2Config::GetSingleton()

//----------------------------------------------------------------------
//! @name ディレクトリ
//----------------------------------------------------------------------
//@{
#if defined(_WIN32) || defined(_WIN64)
	//! オーガコンフィグファイルがある
#	define GT2_OGRE_CNF_DIR_A		"./cnf"
#if defined(GT2_DEBUG)
	//! プラグインがある。例えばdllなど
#	define GT2_PLUGIN_DIR_A			"./plugin_d"
#else
	//! プラグインがある。例えばdllなど
#	define GT2_PLUGIN_DIR_A			"./plugin"
#endif
	//! 何らかのセーブデータがある
#	define GT2_SAVE_DIR_A			"./save"
	//! ログファイルがある
#	define GT2_LOG_DIR_A			"./log"
	//! MCAS用のログファイルパス
#	define GT2_MCAS_LOG_A			GT2_LOG_DIR_A "/GreenTea2D.log"
#	define GT2_DATA_DIR_A			"./Media"
#	define GT2_EFFECT_DIR_A			"./Media/effects"
#	define GT2_SCRIPT_DIR_A			"./Media/Scripts"
#	define GT2_SOUND_DIR_A			"./Media/sounds"
#	define GT2_IMG_DIR_A			"./Media/images"
#	define GT2_OBJ_DIR_A			"./Media/models"
#	define GT2_FONT_DIR_A			"./Media/fonts"
	//! ゲームの好くリーショットなどの画像ファイルがある
#	define GT2_SCREEN_SHOT_DIR_A	"./screen shot"
	//----------------------------------------------------------------------
	//! オーガコンフィグファイルがある
#	define GT2_OGRE_CNF_DIR			_T(GT2_OGRE_CNF_DIR_A)
#if defined(GT2_DEBUG)
	//! プラグインがある。例えばdllなど
#	define GT2_PLUGIN_DIR			_T(GT2_PLUGIN_DIR_A)
#else
	//! プラグインがある。例えばdllなど
#	define GT2_PLUGIN_DIR			_T(GT2_PLUGIN_DIR_A)
#endif
	//! 何らかのセーブデータがある
#	define GT2_SAVE_DIR				_T(GT2_SAVE_DIR_A)
	//! ログファイルがある
#	define GT2_LOG_DIR				_T(GT2_LOG_DIR_A)
#	define GT2_DATA_DIR				_T(GT2_DATA_DIR_A)
#	define GT2_EFFECT_DIR			_T(GT2_EFFECT_DIR_A)
#	define GT2_SCRIPT_DIR			_T(GT2_SCRIPT_DIR_A)
#	define GT2_SOUND_DIR			_T(GT2_SOUND_DIR_A)
#	define GT2_OBJ_DIR				_T(GT2_OBJ_DIR_A)
#	define GT2_IMG_DIR				_T(GT2_IMG_DIR_A)
#	define GT2_FONT_DIR				_T(GT2_FONT_DIR_A)
	//! ゲームの好くリーショットなどの画像ファイルがある
#	define GT2_SCREEN_SHOT_DIR		_T(GT2_SCREEN_SHOT_DIR_A)
#else


#endif
	//@}