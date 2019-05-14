#include "../GreenTea2D.h"

/** �f�o�b�O�}�N�����L���ȏꍇ�A���b�Z�[�W�{�b�N�X��\��������
 * @param [in] file  �t�@�C���p�X
 * @param [in] line  �s��
 * @param [in] flag  ���b�Z�[�W�{�b�N�X�̃{�^����A�C�R���̃^�C�v
 * @param [in] title  �^�C�g��
 * @param [in] txt   ���b�Z�[�W���e
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


/** �f�o�b�O�}�N�����L���ȏꍇ�A���b�Z�[�W�{�b�N�X��\��������
 * @param [in] file   �t�@�C���p�X
 * @param [in] line   �s��
 * @param [in] flag   ���b�Z�[�W�{�b�N�X�̃{�^����A�C�R���̃^�C�v
 * @param [in] title   �^�C�g��
 * @param [in] format  ����������
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


/**���b�Z�[�W�{�b�N�X��\�������� ASCII�^�C�v
 * @param [in] flag   ���b�Z�[�W�{�b�N�X�̃{�^����A�C�R���̃^�C�v
 * @param [in] title   �^�C�g��
 * @param [in] pFormat ����������()
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

/**���b�Z�[�W�{�b�N�X��\�������� UNICODE�^�C�v
 * @param [in] flag   ���b�Z�[�W�{�b�N�X�̃{�^����A�C�R���̃^�C�v
 * @param [in] title   �^�C�g��
 * @param [in] pFormat ����������()
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

/**�o�̓E�B���h�E�ɓ��e���o�͂��� ASCII�^�C�v
 * @param [in] pFmt ����������
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

/**�o�̓E�B���h�E�ɓ��e���o�͂��� UNICODE�^�C�v
 * @param [in] pFmt ����������
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