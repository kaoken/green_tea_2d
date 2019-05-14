/*!
* @file as_config.h
* @brief �A�v���̃R���t�B�O��ݒ肷��B�X�N���v�g�����
* @author kaoken
* @date 2014/01/17 �쐬�J�n
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
 * �R���t�B�O�̃��b�p�[�N���X
 */
class PYConfig
{
public:
	void Run();


	//! @brief �E�B���h�E�̍ő剻�{�^�� 
	PY_CONFIG_METHOD_GET_SET(bool, WindowMaximizeButton)
	//! @brief �E�B���h�E�̍ŏ����{�^��
	PY_CONFIG_METHOD_GET_SET(bool, WindowMinimizeButton)
	//! @brief �E�B���h�E�̑��g����̃��T�C�Y
	PY_CONFIG_METHOD_GET_SET(bool, ResizableWindow)
	//! @brief Alt+Enter�L�[�ɂ��t���X�N���[��
	PY_CONFIG_METHOD_GET_SET(bool, FullScreenFromAltEnterKey)
	//! @brief ALt+F4�L�[����A�v���̏I��
	PY_CONFIG_METHOD_GET_SET(bool, ExitAppFromALtF4Key)
	//! @brief Esc�L�[����A�v���̏I��
	PY_CONFIG_METHOD_GET_SET(bool, ExitAppFromEscKey)
	//! @brief �|�[�Y�L�[����A�v�����ꎞ��~
	PY_CONFIG_METHOD_GET_SET(bool, PauseAppFromPauseKey)
};
