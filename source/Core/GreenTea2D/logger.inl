/*! @file  logger.inl
* @brief GreenTea2D.hファイル内から呼び出されるので、ほかから呼び出さないように！
*  これは、短径を扱う構造体を使うためのもの
* @author kaoken
* @date 2019/03/19 作成開始
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




//! @name ログマクロ
//@{

//!< 致命的なエラータグでログを書き込む
#define GT_FATAL(msg) Logger::Log(Logger::T_FATAL, true, msg, __TBASE_FILE__, __TFUNCTION__, __LINE__)

//!< 致命的なエラータグで文字列フォーマット有りのログを書き込む
#define GT_FATAL_FMT(fmt,...)  Logger::LogFmt(Logger::T_FATAL, true, fmt, __TBASE_FILE__, __TFUNCTION__, __LINE__, __VA_ARGS__)

//!< エラータグでログを書き込む
#define GT_ERROR(msg) Logger::Log(Logger::T_ERROR, true, msg, __TBASE_FILE__, __TFUNCTION__, __LINE__)

//!< エラータグで文字列フォーマット有りログを書き込む
#define GT_ERROR_FMT(fmt,...) Logger::LogFmt(Logger::T_ERROR, true, fmt, __TBASE_FILE__, __TFUNCTION__, __LINE__, __VA_ARGS__)

//!< 警告タグでログを書き込む
#define GT_WARNING(msg)  Logger::Log(Logger::T_WARNING, false, msg, __TBASE_FILE__, __TFUNCTION__, __LINE__)

//!< 警告タグで文字列フォーマット有りログを書き込む
#define GT_WARNING_FMT(fmt,...)  Logger::LogFmt(Logger::T_WARNING, false, fmt, __TBASE_FILE__, __TFUNCTION__, __LINE__, __VA_ARGS__)

//!< 情報タグでログを書き込む
#define GT_INFO(msg) Logger::Log(Logger::T_INFO, false, msg, nullptr, nullptr, 0)

//!< 情報タグでログを書き込む
#define GT_INFO_FMT(fmt,...) Logger::LogFmt(Logger::T_INFO, false, fmt, nullptr, nullptr, 0, __VA_ARGS__)


#ifdef _DEBUG

//!< デバッグタグでログを書き込む
#define GT_DEBUG_LOG(msg) Logger::Log(Logger::T_DEBUG, false, msg, nullptr, nullptr, 0)

//!< デバッグタグでログを書き込む
#define GT_DEBUG_LOG_FMT(fmt,...) Logger::LogFmt(Logger::T_DEBUG, false, fmt, nullptr, nullptr, 0, __VA_ARGS__)

//!< このマクロは、GT_ASSERT()を置き換えます
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
//! @name これらは、上記のマクロのリリースモードの定義。これらはすべて、コンパイラによって完全に無視される
//@{
#define GT_DEBUG_LOG(expr) (void*)0
#define GT_ASSERT(expr) (void*)0
//@}
#endif  // !defined NDEBUG


