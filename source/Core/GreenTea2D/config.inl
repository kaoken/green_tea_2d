#pragma once


/**
 *
 */
struct GT2PathAndClass
{
	TString path;		//!< ���΃p�X�ł�AS�t�@�C����
	TString className;	//!< �쐬�Ώۂ̃N���X��
	//!< �R���X�^���g
	GT2PathAndClass() {}
	//!< �R���X�^���g
	GT2PathAndClass(const TString& s1, const TString& s2) :
		path(s1), className(s2) {}
};

typedef  std::map<TString, GT2PathAndClass> GT2StatePaths;


/**
 * ���̃A�v���̃R���t�B�O�̃f�[�^������
 */
class GT2Config : public CSingleton<GT2Config>
{
private:
	TString		m_windowTitle;					//!< �A�v���^�C�g��
	TString		m_appClassName;					//!< �A�v���̃N���X��
	uint32_t	m_width;						//!< ��ʃT�C�Y�̕�
	uint32_t	m_height;						//!< ��ʃT�C�Y�̍���
	uint32_t	m_minCPU_MHz;					//!< �ŏ�CPU�̎��g���iMHz�j
	uint32_t	m_minMemorySize;				//!< �ŏ��������[�T�C�Y
	uint32_t	m_minVideoMemorySize;			//!< �ŏ��r�f�I�������T�C�Y
	uint32_t	m_minTextureSize;				//!< �ŏ��e�N�X�`���[�T�C�Y
	bool		m_isConstantFrameTime;			//!< 
	bool		m_isFullScreen;					//!< ����̉�ʂ̏��
	float		m_TimePerFrame;					//!< 
	bool		m_isWaitFrameTime;				//!< 
	float		m_WaitTimePerFrame;				//!< 

	//------------------------------
	//! @name Windows�n�̂�
	//------------------------------
	//@{
	bool		m_isWindowMaximizeButton;		//!< �E�B���h�E�̍ő剻�{�^��
	bool		m_isWindowMinimizeButton;		//!< �E�B���h�E�̍ŏ����{�^��
	bool		m_isResizableWindow;			//!< �E�B���h�E�̑��g����̃��T�C�Y
	bool		m_isFullScreenFromAltEnterKey;	//!< Alt+Enter�L�[�ɂ��t���X�N���[��
	bool		m_isExitAppFromALtF4Key;		//!< ALt+F4�L�[����A�v���̏I��
	bool		m_isExitAppFromEscKey;			//!< Esc�L�[����A�v���̏I��
	bool		m_isPauseAppFromPauseKey;		//!< �|�[�Y�L�[����A�v�����ꎞ��~
	//@}


	
	GT2StatePaths		m_registrationStates;	//!< �����o�^������Ԗ�
	TString				m_startState;			//!< �J�n�X�e�[�g

protected:

public:
	//! �R���g���N�^
	GT2Config();
	//! �f�X�g���N�^
	virtual ~GT2Config();

	//------------------------------
	//! @name �ŏ� �X�y�b�N
	//------------------------------
	//@{
	//! @brief �A�v���i�\�t�g�j�� ���Z�b�g
	inline void SetTitle(const TString& title)			{ m_windowTitle = title; }
	//! @brief CPU�̍ŏ� MHz ���Z�b�g
	inline void SetMinCPU_MHz(uint32_t mHz)				{ m_minCPU_MHz = mHz; }
	//! @brief �ŏ��������T�C�Y ���Z�b�g
	inline void SetMinMemorySize(uint32_t mByte)		{ m_minMemorySize = mByte; }
	//! @brief �ŏ��r�f�I�������T�C�Y ���Z�b�g
	inline void SetMinVideoMemorySize(uint32_t mByte)	{ m_minVideoMemorySize = mByte; }
	//! @brief �ŏ��e�N�X�`���[�T�C�Y ���Z�b�g
	inline void SetMinTextureSize(uint32_t size)		{ m_minTextureSize = size; }
	//@}

	//! @brief main.mc2d�t�@�C�����̍ŏ��ɌĂяo�����N���X�� ���Z�b�g
	inline void SetAppClassName(const TString& name) { m_appClassName = name; }
	//! @brief main.mc2d�t�@�C�����̍ŏ��ɌĂяo�����N���X�� ���擾
	inline const TString& GetAppClassName() { return m_appClassName; }


	//------------------------------
	//! @name Windows�n�̂�
	//------------------------------
	//@{
	//! @brief �E�B���h�E�̍ő剻�{�^�� ���擾
	inline bool GetWindowMaximizeButton()		const { return m_isWindowMaximizeButton; }
	//! @brief �E�B���h�E�̍ő剻�{�^�� ���Z�b�g
	inline void SetWindowMaximizeButton(bool b)		  { m_isWindowMaximizeButton = b; }
	//! @brief  �E�B���h�E�̍ŏ����{�^�� ���擾
	inline bool GetWindowMinimizeButton()		const { return m_isWindowMinimizeButton; }
	//! @brief  �E�B���h�E�̍ŏ����{�^�� ���Z�b�g
	inline void SetWindowMinimizeButton(bool b)		  { m_isWindowMinimizeButton = b; }
	//! @brief  �E�B���h�E�̑��g����̃��T�C�Y ���擾
	inline bool GetResizableWindow()			const { return m_isResizableWindow; }
	//! @brief  �E�B���h�E�̑��g����̃��T�C�Y ���Z�b�g
	inline void SetResizableWindow(bool b)			  { m_isResizableWindow = b; }
	//! @brief  Alt+Enter�L�[�ɂ��t���X�N���[�����擾
	inline bool GetFullScreenFromAltEnterKey()	const { return m_isFullScreenFromAltEnterKey; }
	//! @brief  Alt+Enter�L�[�ɂ��t���X�N���[�� ���Z�b�g
	inline void SetFullScreenFromAltEnterKey(bool b)  { m_isFullScreenFromAltEnterKey = b; }
	//! @brief  ALt+F4�L�[����A�v���̏I�� ���擾
	inline bool GetExitAppFromALtF4Key()		const { return m_isExitAppFromALtF4Key; }
	//! @brief  ALt+F4�L�[����A�v���̏I�� ���Z�b�g
	inline void SetExitAppFromALtF4Key(bool b)		  { m_isExitAppFromALtF4Key = b; }
	//! @brief  Esc�L�[����A�v���̏I�� ���擾
	inline bool GetExitAppFromEscKey()			const { return m_isExitAppFromEscKey; }
	//! @brief  Esc�L�[����A�v���̏I�� ���Z�b�g
	inline void SetExitAppFromEscKey(bool b)		  { m_isExitAppFromEscKey = b; }
	//! @brief  �|�[�Y�L�[����A�v�����ꎞ��~ ���擾
	inline bool GetPauseAppFromPauseKey()		const { return m_isPauseAppFromPauseKey; }
	//! @brief  �|�[�Y�L�[����A�v�����ꎞ��~ ���Z�b�g
	inline void SetPauseAppFromPauseKey(bool b)		  { m_isPauseAppFromPauseKey = b; }
	//! @brief �J�n��ʂ��t���X�N���[�����H
	inline void SetFullScreen(bool b)				  { m_isFullScreen = b; }
	//@}


	//------------------------------
	//! @name PC�Ȃǂ̍ŏ��X�y�b�N�`�F�b�N
	//------------------------------
	//@{
	//! @brief  CPUxxxMHz��菬�������`�F�b�N����
	inline uint32_t GetMinCPU_MHz()			const { return m_minCPU_MHz; }
	//! @brief  �ʏ탁�����T�[�YxxxMB��菬�������`�F�b�N����
	inline uint32_t GetMinMemorySize()		const { return m_minMemorySize; }
	//! @brief  �r�f�I�J�[�h�̃������T�[�YxxxMB��菬�������`�F�b�N����
	inline uint32_t GetMinVideoMemorySize() const { return m_minVideoMemorySize; }
	//! @brief  �T�|�[�g����Ă���e�N�X�`���[�T�C�Yxxx��菬�������`�F�b�N @n
	//! 1024,2048,4096,8192�̂����ꂩ
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
//! @name �f�B���N�g��
//----------------------------------------------------------------------
//@{
#if defined(_WIN32) || defined(_WIN64)
	//! �I�[�K�R���t�B�O�t�@�C��������
#	define GT2_OGRE_CNF_DIR_A		"./cnf"
#if defined(GT2_DEBUG)
	//! �v���O�C��������B�Ⴆ��dll�Ȃ�
#	define GT2_PLUGIN_DIR_A			"./plugin_d"
#else
	//! �v���O�C��������B�Ⴆ��dll�Ȃ�
#	define GT2_PLUGIN_DIR_A			"./plugin"
#endif
	//! ���炩�̃Z�[�u�f�[�^������
#	define GT2_SAVE_DIR_A			"./save"
	//! ���O�t�@�C��������
#	define GT2_LOG_DIR_A			"./log"
	//! MCAS�p�̃��O�t�@�C���p�X
#	define GT2_MCAS_LOG_A			GT2_LOG_DIR_A "/GreenTea2D.log"
#	define GT2_DATA_DIR_A			"./Media"
#	define GT2_EFFECT_DIR_A			"./Media/effects"
#	define GT2_SCRIPT_DIR_A			"./Media/Scripts"
#	define GT2_SOUND_DIR_A			"./Media/sounds"
#	define GT2_IMG_DIR_A			"./Media/images"
#	define GT2_OBJ_DIR_A			"./Media/models"
#	define GT2_FONT_DIR_A			"./Media/fonts"
	//! �Q�[���̍D�����[�V���b�g�Ȃǂ̉摜�t�@�C��������
#	define GT2_SCREEN_SHOT_DIR_A	"./screen shot"
	//----------------------------------------------------------------------
	//! �I�[�K�R���t�B�O�t�@�C��������
#	define GT2_OGRE_CNF_DIR			_T(GT2_OGRE_CNF_DIR_A)
#if defined(GT2_DEBUG)
	//! �v���O�C��������B�Ⴆ��dll�Ȃ�
#	define GT2_PLUGIN_DIR			_T(GT2_PLUGIN_DIR_A)
#else
	//! �v���O�C��������B�Ⴆ��dll�Ȃ�
#	define GT2_PLUGIN_DIR			_T(GT2_PLUGIN_DIR_A)
#endif
	//! ���炩�̃Z�[�u�f�[�^������
#	define GT2_SAVE_DIR				_T(GT2_SAVE_DIR_A)
	//! ���O�t�@�C��������
#	define GT2_LOG_DIR				_T(GT2_LOG_DIR_A)
#	define GT2_DATA_DIR				_T(GT2_DATA_DIR_A)
#	define GT2_EFFECT_DIR			_T(GT2_EFFECT_DIR_A)
#	define GT2_SCRIPT_DIR			_T(GT2_SCRIPT_DIR_A)
#	define GT2_SOUND_DIR			_T(GT2_SOUND_DIR_A)
#	define GT2_OBJ_DIR				_T(GT2_OBJ_DIR_A)
#	define GT2_IMG_DIR				_T(GT2_IMG_DIR_A)
#	define GT2_FONT_DIR				_T(GT2_FONT_DIR_A)
	//! �Q�[���̍D�����[�V���b�g�Ȃǂ̉摜�t�@�C��������
#	define GT2_SCREEN_SHOT_DIR		_T(GT2_SCREEN_SHOT_DIR_A)
#else


#endif
	//@}