#include "../GreenTea2D.h"

/** デバッグマクロが有効な場合、メッセージボックスを表示させる
 * @param [in] file  ファイルパス
 * @param [in] line  行数
 * @param [in] flag  メッセージボックスのボタンやアイコンのタイプ
 * @param [in] title  タイトル
 * @param [in] txt   メッセージ内容
 * @return
 */
int DebugMsgBoxX(const TString &file, int line, SDL_MessageBoxFlags flag, const TString &title, const TString &txt)
{
#if !defined(_DEBUG)
	return 0;
#endif
	TChar szMsg[STR_TMP_4096] = { 0 };
	stringU8 strU8;

	gt2_sprintf(szMsg, _T("%s [LINE:%4d]\n\n%s"), file.c_str(), line, txt.c_str());


	strU8 = ToUTF8(TString(szMsg));

	return SDL_ShowSimpleMessageBox(
		flag,
		"Debug Message",
		strU8.c_str(),
		NULL);
}


/** デバッグマクロが有効な場合、メッセージボックスを表示させる
 * @param [in] file   ファイルパス
 * @param [in] line   行数
 * @param [in] flag   メッセージボックスのボタンやアイコンのタイプ
 * @param [in] title   タイトル
 * @param [in] format  書式文字列
 * @return
 */
int DebugMsgBoxX_EX(const TString &file, int line, SDL_MessageBoxFlags flag, const TString &title, const TChar *pFmt, ...)
{
#if !defined(_DEBUG)
	return 0;
#endif
	TChar szMsgTmp[STR_TMP_4096] = { 0 };
	TChar szMsg[STR_TMP_4096] = { 0 };
	stringU8 strU8;
	va_list args;
	va_start(args, pFmt);

	gt2_vsnprintf(szMsgTmp, STR_TMP_4096, pFmt, args);

	va_end(args);
	gt2_sprintf(szMsg, _T("%s [LINE:%4d]\n\n%s"), file.c_str(), line, szMsgTmp);

	strU8 = ToUTF8(TString(szMsg));

	return SDL_ShowSimpleMessageBox(
		flag,
		"Debug Message",
		strU8.c_str(),
		NULL);
}


/**メッセージボックスを表示させる ASCIIタイプ
 * @param [in] flag   メッセージボックスのボタンやアイコンのタイプ
 * @param [in] title   タイトル
 * @param [in] pFormat 書式文字列()
 * @return
 */
int MsgBoxA(SDL_MessageBoxFlags flag, const std::string &title, const char *pFmt, ...)
{
	char szMsgTmp[STR_TMP_4096] = { 0 };
	stringU8 strU8;

	va_list args;
	va_start(args, pFmt);

	gt2_vsnprintf(szMsgTmp, STR_TMP_4096, pFmt, args);

	va_end(args);

	strU8 = ToUTF8(std::string(szMsgTmp));

	return SDL_ShowSimpleMessageBox(
		flag,
		"Debug Message",
		strU8.c_str(),
		NULL);
}

/**メッセージボックスを表示させる UNICODEタイプ
 * @param [in] flag   メッセージボックスのボタンやアイコンのタイプ
 * @param [in] title   タイトル
 * @param [in] pFormat 書式文字列()
 * @return
 */
int MsgBoxW(SDL_MessageBoxFlags flag, const std::wstring &title, const wchar_t *pFmt, ...)
{
	wchar_t szMsgTmp[STR_TMP_4096] = { 0 };
	stringU8 strU8;

	va_list args;
	va_start(args, pFmt);

	vswprintf_s(szMsgTmp, STR_TMP_4096, pFmt, args);

	va_end(args);

	strU8 = ToUTF8(std::wstring(szMsgTmp));

	return SDL_ShowSimpleMessageBox(
		flag,
		"Debug Message",
		strU8.c_str(),
		NULL);
}

/**出力ウィンドウに内容を出力する ASCIIタイプ
 * @param [in] pFmt 書式文字列
 * @return
 */
void TraceA(const char *pFmt, ...) 
{
	char szMsgTmp[STR_TMP_4096] = { 0 };

	va_list args;
	va_start(args, pFmt);

	gt2_vsnprintf(szMsgTmp, STR_TMP_4096, pFmt, args);

	va_end(args);

#if defined(_WIN32) || defined(_WIN64)
	ATLTRACE2(szMsgTmp);
#elif defined(ANDROID) || defined(__ANDROID__)
	__android_log_print(ANDROID_LOG_INFO, szMsgTmp))
#endif
}

/**出力ウィンドウに内容を出力する UNICODEタイプ
 * @param [in] pFmt 書式文字列
 * @return
 */
void TraceW(const wchar_t *pFmt, ...)
{
	wchar_t szMsgTmp[STR_TMP_4096] = { 0 };

	va_list args;
	va_start(args, pFmt);

	vswprintf_s(szMsgTmp, STR_TMP_4096, pFmt, args);

	va_end(args);

	std::string msg;
	Convert_UTF16_To_SJIS(std::wstring(szMsgTmp), &msg);
#if defined(_WIN32) || defined(_WIN64)
	ATLTRACE2(msg.c_str());
#elif defined(ANDROID) || defined(__ANDROID__)
	__android_log_print(ANDROID_LOG_INFO, msg.c_str()))
#endif
}