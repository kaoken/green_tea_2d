#pragma once

//-------------------------------------------------------------
//! @name ���b�Z�[�W�{�b�N�X�\��(DEBUG�p�j
//-------------------------------------------------------------
//@{
int DebugMsgBoxX   (const TString &file, int line, SDL_MessageBoxFlags flag, const TString &title, const TString &txt);
int DebugMsgBoxX_EX(const TString &file, int line, SDL_MessageBoxFlags flag, const TString &title, const TChar *pFmt, ...);

#define DEBUG_ERR_ICONMSG   (_title, _txt)      DebugMsgBoxX   (_T(__FILE__), __LINE__, SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, _title, _txt);
#define DEBUG_ERR_ICONMMC_EX(_title, _fmt, ...) DebugMsgBoxX_EX(_T(__FILE__), __LINE__, SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, _title, _fmt __VA_OPT__(,) __VA_ARGS__);


#define DEBUG_ERR_ICONMMC_BRK   (_title, _txt)      DbgBreak(); DebugMsgBoxX   (_T(__FILE__), __LINE__, SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, _title, _txt);
#define DEBUG_ERR_ICONMMC_BRK_EX(_title, _fmt, ...) DbgBreak(); DebugMsgBoxX_EX(_T(__FILE__), __LINE__, SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, _title, _fmt __VA_OPT__(,) __VA_ARGS__);


int MsgBoxA(SDL_MessageBoxFlags flag, const std::string &title,  const char    *pFmt, ...);
int MsgBoxW(SDL_MessageBoxFlags flag, const std::wstring &title, const wchar_t *pFmt, ...);

#ifdef _UNICODE
//!< �G���[���b�Z�[�W�{�b�N�X�iUFT16�Łj
#  define MsgBox(_type, _title, _format, ...) MsgBoxW(_type, _title, _format,__VA_ARGS__)
#  define ErrMsgBox(_title, _format, ...)     MsgBoxW( SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, _title, _format,__VA_ARGS__)
#else
//!< �G���[���b�Z�[�W�{�b�N�X�iASCII�Łj
#  define MsgBox(_type, _title, _format, ...) MsgBoxA(_type, _title, _format,__VA_ARGS__)
#  define ErrMsgBox(_title, _format, ...)     MsgBoxA( SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, _title, _format,__VA_ARGS__)
#endif
//!< �G���[���b�Z�[�W�{�b�N�X�iASCII, sjis�Łj
#define ErrMsgBoxA(_title, _format, ...)   MsgBoxA(SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, _title, _format,__VA_ARGS__)
#define ErrMsgBoxW(_title, _format, ...)   MsgBoxW(SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, _title, _format,__VA_ARGS__)


//@}


//--------------------------------------
// �ʏ�g���[�X
//--------------------------------------

//! �f�o�b�O�̏o�͂́A�ψ������X�g������Ă���
void TraceA(const char *pFmt, ...);
void TraceW(const wchar_t *pFmt, ...);

#ifdef _UNICODE
#  define Trace(_format, ...) TraceW(_format, __VA_ARGS__)
#else
#  define Trace(_format, ...) TraceA(_format, __VA_ARGS__)
#endif
