/*! @file  logger.inl
* @brief GreenTea2D.h�t�@�C��������Ăяo�����̂ŁA�ق�����Ăяo���Ȃ��悤�ɁI
*  ����́A�Z�a�������\���̂��g�����߂̂���
* @author kaoken
* @date 2019/03/19 �쐬�J�n
*/
#include <spdlog/spdlog.h>
#include <spdlog/sinks/rotating_file_sink.h>

namespace spdlog {
	class logger;
}


class Logger : public CSingleton<Logger> {
	friend class Logger;
	std::shared_ptr<spdlog::logger> m_spdlog;
	std::shared_ptr<spdlog::logger> m_spScriptLog;
public:
	enum GT_LOG_OUTPUT_TYPE {
		T_FATAL,
		T_ERROR,
		T_WARNING,
		T_INFO,
		T_DEBUG,
		T_NOTE,
	};
public:
	Logger();
	~Logger();
	static int Log(const GT_LOG_OUTPUT_TYPE type, const bool isShowMsgBox, const TString msg, const TChar*  pFile, const TChar* pFunc, const int line);
	static int LogFmt(const GT_LOG_OUTPUT_TYPE type, const bool isShowMsgBox, const TChar* pFmt, const TChar*  pFile, const TChar* pFunc, const int line, ...);
private:
	int ShowWriteLog(
		const GT_LOG_OUTPUT_TYPE type, const bool isShowMsgBox,
		const TChar* szMsg, const TChar*  pFile, const TChar* pFunc, const int line);

};




//! @name ���O�}�N��
//@{

//!< �v���I�ȃG���[�^�O�Ń��O����������
#define GT_FATAL(msg) Logger::Log(Logger::T_FATAL, true, msg, __TBASE_FILE__, __TFUNCTION__, __LINE__)

//!< �v���I�ȃG���[�^�O�ŕ�����t�H�[�}�b�g�L��̃��O����������
#define GT_FATAL_FMT(fmt,...)  Logger::LogFmt(Logger::T_FATAL, true, fmt, __TBASE_FILE__, __TFUNCTION__, __LINE__, __VA_ARGS__)

//!< �G���[�^�O�Ń��O����������
#define GT_ERROR(msg) Logger::Log(Logger::T_ERROR, true, msg, __TBASE_FILE__, __TFUNCTION__, __LINE__)

//!< �G���[�^�O�ŕ�����t�H�[�}�b�g�L�胍�O����������
#define GT_ERROR_FMT(fmt,...) Logger::LogFmt(Logger::T_ERROR, true, fmt, __TBASE_FILE__, __TFUNCTION__, __LINE__, __VA_ARGS__)

//!< �x���^�O�Ń��O����������
#define GT_WARNING(msg)  Logger::Log(Logger::T_WARNING, false, msg, __TBASE_FILE__, __TFUNCTION__, __LINE__)

//!< �x���^�O�ŕ�����t�H�[�}�b�g�L�胍�O����������
#define GT_WARNING_FMT(fmt,...)  Logger::LogFmt(Logger::T_WARNING, false, fmt, __TBASE_FILE__, __TFUNCTION__, __LINE__, __VA_ARGS__)

//!< ���^�O�Ń��O����������
#define GT_INFO(msg) Logger::Log(Logger::T_INFO, false, msg, nullptr, nullptr, 0)

//!< ���^�O�Ń��O����������
#define GT_INFO_FMT(fmt,...) Logger::LogFmt(Logger::T_INFO, false, fmt, nullptr, nullptr, 0, __VA_ARGS__)


#ifdef _DEBUG

//!< �f�o�b�O�^�O�Ń��O����������
#define GT_DEBUG_LOG(msg) Logger::Log(Logger::T_DEBUG, false, msg, nullptr, nullptr, 0)

//!< �f�o�b�O�^�O�Ń��O����������
#define GT_DEBUG_LOG_FMT(fmt,...) Logger::LogFmt(Logger::T_DEBUG, false, fmt, nullptr, nullptr, 0, __VA_ARGS__)

//!< ���̃}�N���́AGT_ASSERT()��u�������܂�
#define GT_ASSERT(expr) \
do \
{ \
	if (!(expr)) \
	{ \
		Logger::Log(Logger::T_WARNING, true, _T(#expr), __TBASE_FILE__, __TFUNCTION__, __LINE__); \
	} \
} while (0)
//@}
#else  // NDEBUG is defined
//! @name �����́A��L�̃}�N���̃����[�X���[�h�̒�`�B�����͂��ׂāA�R���p�C���ɂ���Ċ��S�ɖ��������
//@{
#define GT_DEBUG_LOG(expr) (void*)0
#define GT_ASSERT(expr) (void*)0
//@}
#endif  // !defined NDEBUG


