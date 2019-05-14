#pragma once

#include <Core/greenTea2D.h>
#include <Python\pyAppConfig.h>

/**
* �V���O���g���N���X�̊Ǘ��֌W�̃I�u�W�F�N�g��z�u���AGameApp �ł̂ݎg�p����
* @note �����o�ϐ��̓A�N�Z�X�s�\�I
* @ref GameApp
*/
class ManagerDeploy {
private:
	static bool ms_isDeploy;
	Logger*			m_pLogger;			//!< ���K�[
	//ASShareDataMgr		m_shareDataMgr;		//!< ���L�f�[�^�[�Ǘ�
	//ASClientServer		m_asClientServer;	//!< �N���C�A���g�T�[�o�[
	//MCCameraMgr			m_cameraMgr;		//!< �J�����Ǘ�
	//MCImageMgr			m_imageMgr;			//!< �C���[�W�Ǘ�
	//MCDXFontMgr			m_fontMgr;			//!< �t�H���g�Ǘ�
	//MCSpriteManager		m_spriteMgr;		//!< �X�v���C�g�Ǘ�
	//MCImgAnimationMgr	m_imgAnimationMgr;	//!< �QD�A�j���[�V�����Ǘ�
	//MCInputDevice		m_inputDevice;		//!< ���͌n
	//MCSoundManager		m_soundMgr;			//!< �T�E���h�Ǘ�
	//MCMeshMgr			m_MeshMgr;			//!< ���b�V���Ǘ�
	//MCBatchDrawingMgr	m_batchDrawingMgr;	//!< �`��R�}���h�Ǘ�
	//MCStateManager		m_stateMgr;			//!< ��ԊǗ�
	//MCActorMgr			m_actorMgr;			//!< �A�N�^�[�Ǘ�
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
	// �~���[�e�b�N�X
	SDL_mutex*			m_pMutex;
	ManagerDeploy		m_managerDeploy;
public:		// GET SET
	M_GET_PUB_SET_PRI(float, TimeSinceLastFrame, UTIL_RECUTSIVE_LOCK())
	M_GET_PUB_SET_PRI(float, FPS, UTIL_RECUTSIVE_LOCK())
	M_IS_PUB_SET_PRI(Initialize, UTIL_RECUTSIVE_LOCK())
public:
	GameApp();
	~GameApp();
	//! ������
	void Initialize();
	//! �J�n
	void Go();
private:

	//! ��ԍŏ��ɌĂяo���Z�b�g�A�b�v
	//! @return �Z�b�g�A�b�v�����������ꍇ�Atrue��Ԃ�
	bool Setup();

	//! �A�v���P�[�V�������\�����܂��B
	void Configure();
private:
	//-----------------------
	// �X�N���v�g�֘A
	//-----------------------
	GT2Config				m_config;				//!< �X�N���v�g������ǂݍ��񂾃R���t�B�O�f�[�^
};