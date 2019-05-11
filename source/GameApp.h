#pragma once

#include <Core/greenTea2D.h>
#include <Python\pyAppConfig.h>

/**
* シングルトンクラスの管理関係のオブジェクトを配置し、GameApp でのみ使用する
* @note メンバ変数はアクセス不可能！
* @ref GameApp
*/
class ManagerDeploy {
private:
	static bool ms_isDeploy;
	Logger*			m_pLogger;			//!< ロガー
	//ASShareDataMgr		m_shareDataMgr;		//!< 共有データー管理
	//ASClientServer		m_asClientServer;	//!< クライアントサーバー
	//MCCameraMgr			m_cameraMgr;		//!< カメラ管理
	//MCImageMgr			m_imageMgr;			//!< イメージ管理
	//MCDXFontMgr			m_fontMgr;			//!< フォント管理
	//MCSpriteManager		m_spriteMgr;		//!< スプライト管理
	//MCImgAnimationMgr	m_imgAnimationMgr;	//!< ２Dアニメーション管理
	//MCInputDevice		m_inputDevice;		//!< 入力系
	//MCSoundManager		m_soundMgr;			//!< サウンド管理
	//MCMeshMgr			m_MeshMgr;			//!< メッシュ管理
	//MCBatchDrawingMgr	m_batchDrawingMgr;	//!< 描画コマンド管理
	//MCStateManager		m_stateMgr;			//!< 状態管理
	//MCActorMgr			m_actorMgr;			//!< アクター管理
public:
	ManagerDeploy() {
		assert(!ms_isDeploy);
		m_pLogger = nullptr;
		ms_isDeploy = true;
	}
	bool Deploy();
	//InputDevice* GetInputDevice() { return &m_inputDevice; }
	~ManagerDeploy() {
		SAFE_DELETE(m_pLogger);
	}
};
/**
 *
 */
class GameApp
{
private:
	// ミューテックス
	SDL_mutex*			m_pMutex;
	ManagerDeploy		m_managerDeploy;
public:		// GET SET
	M_GET_PUB_SET_PRI(float, TimeSinceLastFrame, UTIL_RECUTSIVE_LOCK())
	M_GET_PUB_SET_PRI(float, FPS, UTIL_RECUTSIVE_LOCK())
	M_IS_PUB_SET_PRI(Initialize, UTIL_RECUTSIVE_LOCK())
public:
	GameApp();
	~GameApp();
	//! 初期化
	void Initialize();
	//! 開始
	void Go();
private:

	//! 一番最初に呼び出すセットアップ
	//! @return セットアップが成功した場合、trueを返す
	bool Setup();

	//! アプリケーションを構成します。
	void Configure();
private:
	//-----------------------
	// スクリプト関連
	//-----------------------
	GT2Config				m_config;				//!< スクリプト側から読み込んだコンフィグデータ
};