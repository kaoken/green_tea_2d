/*!
* @file as_config.h
* @brief アプリのコンフィグを設定する。スクリプトを作る
* @author kaoken
* @date 2014/01/17 作成開始
*/
#pragma once


#include <Core/greenTea2D.h>
#include <Python/Util/pyBind11Util.h>


#define PY_CONFIG_METHOD_GET_SET(__TYPE, __name) \
	inline __TYPE Get##__name(){ \
		return gGt2Config.Get##__name(); \
	} \
	inline void Set##__name(const __TYPE val) { \
		gGt2Config.Set##__name(val); \
	}

/**
 * コンフィグのラッパークラス
 */
class PYConfig
{
public:
	void Run();


	//! @brief ウィンドウの最大化ボタン 
	PY_CONFIG_METHOD_GET_SET(bool, WindowMaximizeButton)
	//! @brief ウィンドウの最小化ボタン
	PY_CONFIG_METHOD_GET_SET(bool, WindowMinimizeButton)
	//! @brief ウィンドウの太枠からのリサイズ
	PY_CONFIG_METHOD_GET_SET(bool, ResizableWindow)
	//! @brief Alt+Enterキーによるフルスクリーン
	PY_CONFIG_METHOD_GET_SET(bool, FullScreenFromAltEnterKey)
	//! @brief ALt+F4キーからアプリの終了
	PY_CONFIG_METHOD_GET_SET(bool, ExitAppFromALtF4Key)
	//! @brief Escキーからアプリの終了
	PY_CONFIG_METHOD_GET_SET(bool, ExitAppFromEscKey)
	//! @brief ポーズキーからアプリを一時停止
	PY_CONFIG_METHOD_GET_SET(bool, PauseAppFromPauseKey)
};
