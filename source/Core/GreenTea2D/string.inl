/*! @file  string.inl
* @brief MCLib.h�t�@�C��������Ăяo�����̂ŁA�ق�����Ăяo���Ȃ��悤�ɁI
*  ����́A������֌W
* @author kaoken
* @date 2019/02/24 �쐬�J�n
*/
#pragma once




//------------------------------------------------------------
//! @name �����֌W
//------------------------------------------------------------
//@{
#define STR_TMP_16		16
#define STR_TMP_32		32
#define STR_TMP_64		64
#define STR_TMP_128		128
#define STR_TMP_256		256
#define STR_TMP_512		512
#define STR_TMP_1024	1024
#define STR_TMP_4096	4096
#define STR_TMP_8192	8192


typedef char	charU8;	//!< chara utf8


//! string utf8 only
typedef std::basic_string<charU8, std::char_traits<charU8>, std::allocator<charU8> > stringU8;


//! std::string �̃x�N�g��
typedef std::vector<std::string> VString;
//! std::wstring �̃x�N�g��
typedef std::vector<std::wstring> VStringW;


//! to_string �̃}�N��
#define toStr(_num) std::to_string(_num)
//! to_wstring �̃}�N��
#define toStrW(_num) std::to_wstring(_num)


#ifdef _UNICODE
#  define toTStr(_num) toStrW(_num)
#  define TChar wchar_t
#  ifndef _T
#    define __T(x)		L ## x
#    define _T(x)		__T(x)
#  endif
#  define TString std::wstring
typedef std::vector<std::string> VTString;
#  define gt2_tistream std::wistream
#  define gt2_tostream std::wostream
#  define gt2_tostringstream std::wostringstream
#  define gt2_tstringstream std::wstringstream
#else
#  define toTStr(_num) toStr(_num)
#  define TChar char
#  ifndef _T
#    define _T(x)      x
#  endif
#  define TString std::string
typedef std::vector<std::string> VTString;
#  define gt2_tistream std::istream
#  define gt2_tostream std::ostream
#  define gt2_tostringstream std::ostringstream
#  define gt2_tstringstream std::stringstream
#endif


#if defined(_WIN32) || defined(_WIN64)
#  ifdef _UNICODE
#    define gt2_snprintf_s	swprintf_s
#    define gt2_vsnprintf(buffer,bufferCount,format,argList)	vswprintf_s(buffer,bufferCount,format,argList)
#    define gt2_vsprintf(buffer,format,argList)	std::vswprintf_s(buffer, sizeof(bufferCount)>>1,format,argList)
#    define gt2_strcmp		std::wcscmp
#    define gt2_strcpy_s	std::wcscpy_s
#    define gt2_strrchr		std::wcsrchr
#    define gt2_getcwd		std::wgetcwd
#    define gt2_sprintf(buffer,format,...)	swprintf_s(buffer, (sizeof(buffer)>>1)-1,format,__VA_ARGS__)	
#    define gt2_strlen		wcslen
#    define gt2_strtod		wcstod
#    define gt2_setlocale	_wsetlocale
#    define gt2_vfprintf     vfwprintf_s
#    define gt2_tolower		std::towlower
#  else
#    define gt2_snprintf_s	sprintf_s
#    define gt2_vsnprintf(buffer,bufferCount,format,argList)	vsnprintf_s(buffer,bufferCount,format,argList)
#    define gt2_vsprintf(buffer,format,argList)	std::vsnprintf_s(buffer, sizeof(bufferCount),format,argList)
#    define gt2_strcmp		std::strcmp
#    define gt2_strcpy_s	std::strcpy_s
#    define gt2_strrchr		std::strrchr
#    define gt2_getcwd		std::getcwd
#    define gt2_sprintf(buffer,format,...)	sprintf_s(buffer, sizeof(buffer),format,__VA_ARGS__)	
#    define gt2_strlen		strlen
#    define gt2_strtod		strtod
#    define gt2_setlocale	setlocale
#    define gt2_vfprintf    vfprintf_s
#    define gt2_tolower		std::tolower
#  endif
#endif
//@}



//------------------------------------------------------------
//! @name ��`�ς݃}�N��
//------------------------------------------------------------
//@{
#define __TBASE_FILE__ _T(__BASE_FILE__)
#define __TFUNCTION__ _T(__FUNCTION__)
#define __TFILE__ _T(__FILE__)
#define __WFUNCTION__ L__FUNCTION__
#define __WFILE__ L__FILE__
#define __WBASE_FILE__ L__BASE_FILE__

#ifndef L__FUNCTION__
#  define L__FUNCTION__ L"dumy L__FUNCTION__"
#endif
#ifndef L__FILE__
#  define L__FILE__ L"dumy L__FILE__"
#endif
//@}


//---------------------------------------------------------------
//!@name  SJIS -> xxxx
//---------------------------------------------------------------
//@{
/*!
* @brief SJIS�������UTF16�֕ϊ�����
* @param [in]  src    SJIS������
* @param [out] pOut   �ϊ�����UTF16������
* @return �G���[���Ȃ����true��Ԃ��B
*/
bool Convert_SJIS_To_UTF16(const std::string& src, std::wstring* pOut);

/*!
* @brief UTF8�������SJIS�֕ϊ�����
* @param [in]   src    SJIS������
* @param [out]  pUTF8  �ϊ�����UTF8�����񂪓n�����B
* @return �G���[���Ȃ����true��Ԃ��B
*/
bool Convert_SJIS_To_UTF8(const std::string& src, stringU8 *pUTF8);
/*!
* @brief SJIS�������TCHAR�֕ϊ�����
* @param [in]  pSrc  SJIS������
* @param [out] pOut  �ϊ�����TCHAR������
* @return �G���[���Ȃ����true��Ԃ��B
*/
bool Convert_SJIS_To_TCHAR(const std::string &src, std::string *pOut);
//@}

//###############################################################
//# UTF8 -> xxxx
//###############################################################
//!@name  UTF8 -> xxxx
//@{
/*!
* @brief SJIS�������UTF8�֕ϊ�����
* @param [in]   pUTF8  UTF8������|�C���^
* @param [out]  pSjis  �ϊ�����SJIS�����񂪓n�����B
* @return �G���[���Ȃ����true��Ԃ��B
*/
bool Convert_UTF8_To_SJIS(const stringU8 &src, std::string *pSjis);

/*!
* @brief UTF8�������UTF16�֕ϊ�����
* @param [in]   pUTF8  UTF8������|�C���^
* @param [out]  pUTF16  �ϊ�����UTF16�����񂪓n�����B
* @return �G���[���Ȃ����true��Ԃ��B
*/
bool Convert_UTF8_To_UTF16(const stringU8& src, std::wstring *pUTF16);

/*!
* @brief UTF8�������UTF16�֕ϊ�����
* @param [in]   pUTF8  UTF8������|�C���^
* @param [out]  pOut   �ϊ�����TCHAR�����񂪓n�����B
* @return �G���[���Ȃ����true��Ԃ��B
*/
bool Convert_UTF8_To_TCHAR(const stringU8& src, std::string *pOut);
//@}



//###############################################################
//# UTF16 -> xxxx
//###############################################################
//!@name UTF16 -> xxxx
//@{
/*!
* @brief UTF16�������SJIS�֕ϊ�����
* @param [in]  src   UTF16������
* @param [out] pOut  �ϊ�����SJIS�����񂪓n�����B
* @return �G���[���Ȃ����true��Ԃ��B
*/
bool Convert_UTF16_To_SJIS(const std::wstring& src, std::string* pOut);

/*! UTF16�������UTF8�֕ϊ�����
* @param [in]  pSrc   UTF16������
* @param [out] pOut   �ϊ�����UTF8�����񂪓n�����B
* @return �G���[���Ȃ����true��Ԃ��B
*/
bool Convert_UTF16_To_UTF8(const std::wstring &src, stringU8* pOut);
//@}

//---------------------------------------------------------------
//!@name TCHAR -> xxxx
//---------------------------------------------------------------
//@{
/*!
* @brief TCHAR�������SJIS�֕ϊ�����
* @param [in]  pSrc  TCHAR������
* @param [out] pOut  �ϊ�����SJIS������
* @return �G���[���Ȃ����true��Ԃ��B
*/
bool Convert_TCHAR_To_SJIS(const std::string& src, std::string* pOut);
/*!
* @brief TCHAR�������UTF8�֕ϊ�����
* @param [in]  pSrc  TCHAR������
* @param [out] pOut  �ϊ�����UTF8������
* @return �G���[���Ȃ����true��Ԃ��B
*/
bool Convert_TCHAR_To_UTF8(const std::string& src, stringU8* pOut);
/*!
* @brief TCHAR�������UTF16�֕ϊ�����
* @param [in]  pSrc  TCHAR������
* @param [out] pOut  �ϊ�����UTF16������
* @return �G���[���Ȃ����true��Ԃ��B
*/
bool Convert_TCHAR_To_UTF16(const std::string& src, std::wstring* pOut);

//@}

/*! SJIS�������TCHAR�֕ϊ�����
* @param [in]  str  SJIS������
* @return ������TCHAR�ɕϊ����ꂽ�������Ԃ��B���s�����ꍇ��0�����̕������Ԃ�
*/
std::string ToTString(const std::string& str);
/*! UTF16�������TCHAR�֕ϊ�����
* @param [in]  str  UTF16������
* @return ������TCHAR�ɕϊ����ꂽ�������Ԃ��B���s�����ꍇ��0�����̕������Ԃ�
*/
std::string ToTString(const std::wstring& str);


/*! sjis/utf8�������sjis/utf8�֕ϊ�����
* @param [in]  str  sjis/utf8������
* @return ������sjis/utf8�ɕϊ����ꂽ�������Ԃ��B���s�����ꍇ��0�����̕������Ԃ�
*/
std::string ToString(const std::string& str);
/*! UTF16�������sjis/utf8�֕ϊ�����
* @param [in]  str  UTF16������
* @return ������sjis/utf8�ɕϊ����ꂽ�������Ԃ��B���s�����ꍇ��0�����̕������Ԃ�
*/
std::string ToString(const std::wstring& str);


/*! SJIS�������UTF16�֕ϊ�����
* @param [in]  str  SJIS������
* @return ������UTF16�ɕϊ����ꂽ�������Ԃ��B���s�����ꍇ��0�����̕������Ԃ�
*/
std::wstring ToUTF16(const std::string& str);
/*! SJIS�������UTF8�֕ϊ�����
* @param [in]  str  SJIS������
* @return ������UTF8�ɕϊ����ꂽ�������Ԃ��B���s�����ꍇ��0�����̕������Ԃ�
*/
stringU8 ToUTF8(const std::string& str);
/*! UTF16�������UTF8�֕ϊ�����
* @param [in]  str  SJIS������
* @return ������UTF8�ɕϊ����ꂽ�������Ԃ��B���s�����ꍇ��0�����̕������Ԃ�
*/
stringU8 ToUTF8(const std::wstring& str);
/*! UTF8�������SJIS�֕ϊ�����
* @param [in]  str  UTF8������
* @return ������SJIS�ɕϊ����ꂽ�������Ԃ��B���s�����ꍇ��0�����̕������Ԃ�
*/
std::string ToSJIS(const stringU8& str);
/*! UTF16�������SJIS�֕ϊ�����
* @param [in]  str  UTF16������
* @return ������UTF16�ɕϊ����ꂽ�������Ԃ��B���s�����ꍇ��0�����̕������Ԃ�
*/
std::string ToSJIS(const std::wstring& str);


#define MAX_DIGITS_IN_INT 12  // int�^�̌��̍ő吔 (-2147483647 = 11 ��, +1 for the '\0')
typedef std::vector<std::string> StringVec;

// �ŏ���'\n'�̂ɕ������폜���܂�
void RemoveFirstLine(std::string &src, std::string &result);

// �擪�̋󔒂��폜���܂�
void TrimLeft(std::string &s);

// �e�L�X�g�̃u���b�N�̍s�����J�E���g
int CountLines(const std::wstring &s);


std::string ToStr(int num, int base = 10);
std::string ToStr(unsigned int num, int base = 10);
std::string ToStr(unsigned long num, int base = 10);
std::string ToStr(float num, int setprecision = 4);
std::string ToStr(double num, int setprecision = 15);
std::string ToStr(bool val);


// ������̃x�N�g���ɋ�؂蕶���ŕ�����𕪊����܂��B���Ƃ��΁A���̕����������Ƃ��āF
//   std::string test("one,two,three");
// ���̂悤��Split()���Ăяo�����Ƃ��ł��܂��F
//   Split(test, outVec, ',');
// outVec�́A�ȉ��̒l�������ƂɂȂ�܂��F
//   "one", "two", "three"
void Split(const std::string& str, StringVec& vec, char delimiter);

std::string ToLower(const std::string &in);
std::string ToUpper(const std::string &in);


/*! �����񂩂�n�b�V�����쐬����B
* @param [in]  str  ������
* @return �n�b�V����Ԃ��B
*/
inline size_t GetHash(const std::string &name)
{
	static std::hash<std::string> str_hash;
	return str_hash(name);
}


/*! �����񂩂�n�b�V�����쐬����B
* @param [in]  str  ������
* @return �n�b�V����Ԃ��B
*/
inline size_t GetHash(const std::wstring &name)
{
	static std::hash<std::wstring> str_hash;
	return str_hash(name);
}



/*! �����񂩂�16�i��������̃n�b�V���l���쐬����
* @param [in]  str  ������
* @return 16�i��������̃n�b�V���l
*/
inline std::string GetHashStrHex(const std::string &name)
{
	static std::hash<std::string> str_hash;
	std::stringstream ss;
	ss << std::hex << str_hash(name);
	return ss.str();
}

/*! �����񂩂�16�i��������̃n�b�V���l���쐬����
* @param [in]  str  ������
* @return 16�i��������̃n�b�V���l
*/
inline std::wstring GetHashStrHex(const std::wstring &name)
{
	static std::hash<std::wstring> str_hash;
	std::wstringstream ss;
	ss << std::hex << str_hash(name);
	return ss.str();
}
