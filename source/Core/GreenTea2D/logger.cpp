#include <Core/greenTea2D.h>


Logger::Logger()
{
	std::string path;

	path += GT2_LOG_DIR_A;
	path += "/MC2D";
	path = "test";

	m_spdlog = spdlog::rotating_logger_mt("MC2D", path.c_str(), 1048576 * 5, 3);

	//
	//path += MC_LOG_DIR_A;
	//path += "/script";

	//m_spScriptLog = spdlog::rotating_logger_mt("script", path.c_str(), 1048576 * 5, 3);
}
Logger::~Logger()
{
}


int Logger::ShowWriteLog(
	const GT_LOG_OUTPUT_TYPE type, const bool isShowMsgBox,
	const TChar* szMsg, const TChar* pFile, const TChar* pFunc, const int line)
{
	TString out;

	if (pFile != nullptr)
	{
		out += _T("[FILE:");
		out += pFile;
		out += _T("]\t");
	}
	if (pFunc != nullptr)
	{
		out += _T("[FUNC:");
		out += pFunc;
		out += _T("]\t");
	}
	if (line != 0)
	{
		out += _T("[LINE:");
		out += toTStr(line);
		out += _T("]\t");
	}
	if (szMsg != nullptr)
	{
		out += _T("[MSG:");
		out += szMsg;
		out += _T("]");
	}

	const TChar* szTitle;
	const char* szLog;
#ifdef _UNICODE
	std::string strLog;
	strLog = ToSJIS(out);
	szLog = strLog.c_str();
#else
	szLog = out.c_str();
#endif
	switch (type)
	{
	case T_FATAL:
		szTitle = _T("FATAL");
		m_spdlog->critical(szLog);
		break;
	case T_ERROR:
		szTitle = _T("ERROR");
		m_spdlog->error(szLog);
		break;
	case T_WARNING:
		szTitle = _T("WARNING");
		m_spdlog->warn(szLog);
		break;
	case T_INFO:
		szTitle = _T("INFO");
		m_spdlog->info(szLog);
		break;
	case T_DEBUG:
		szTitle = _T("DEBUG");
		m_spdlog->debug(szLog);
		break;
	default:
		szTitle = _T("TRACE");
		m_spdlog->trace(szLog);
		break;
	}
	// ダイアログボックスを表示
	if (isShowMsgBox)
		return ErrMsgBox(szTitle, _T("%s"), out.c_str());
	return 0;
}


int Logger::LogFmt(const GT_LOG_OUTPUT_TYPE type, const bool isShowMsgBox, const TChar* pFmt, const TChar* pFile, const TChar* pFunc, const int line, ...)
{
	assert(Logger::GetSingletonPtr());
	TChar szMsgTmp[STR_TMP_4096] = { '\0' };
	va_list args;


	va_start(args, pFmt);

	gt2_vsnprintf(szMsgTmp, STR_TMP_4096, pFmt, args);

	va_end(args);

	return  Logger::GetSingleton().ShowWriteLog(type, isShowMsgBox, szMsgTmp, pFile, pFunc, line);
}

/**
	* ログファイルに内容を書き込む
	* @param [in] str  メッセージ
	* @param [in] file ファイル場所
	* @param [in] func 関数名
	* @param [in] line 行数
	*/
int Logger::Log(const GT_LOG_OUTPUT_TYPE type, const bool isShowMsgBox, const TString msg, const TChar* pFile, const TChar* pFunc, const int line)
{
	assert(Logger::GetSingletonPtr());
	return  Logger::GetSingleton().ShowWriteLog(type, isShowMsgBox, msg.c_str(), pFile, pFunc, line);
}