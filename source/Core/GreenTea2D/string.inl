/*! @file  string.inl
* @brief MCLib.hファイル内から呼び出されるので、ほかから呼び出さないように！
*  これは、文字列関係
* @author kaoken
* @date 2019/02/24 作成開始
*/
#pragma once




//------------------------------------------------------------
//! @name 文字関係
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


//! std::string のベクトル
typedef std::vector<std::string> VString;
//! std::wstring のベクトル
typedef std::vector<std::wstring> VStringW;


//! to_string のマクロ
#define toStr(_num) std::to_string(_num)
//! to_wstring のマクロ
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
//! @name 定義済みマクロ
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
* @brief SJIS文字列をUTF16へ変換する
* @param [in]  src    SJIS文字列
* @param [out] pOut   変換したUTF16文字列
* @return エラーがなければtrueを返す。
*/
bool Convert_SJIS_To_UTF16(const std::string& src, std::wstring* pOut);

/*!
* @brief UTF8文字列をSJISへ変換する
* @param [in]   src    SJIS文字列
* @param [out]  pUTF8  変換したUTF8文字列が渡される。
* @return エラーがなければtrueを返す。
*/
bool Convert_SJIS_To_UTF8(const std::string& src, stringU8 *pUTF8);
/*!
* @brief SJIS文字列をTCHARへ変換する
* @param [in]  pSrc  SJIS文字列
* @param [out] pOut  変換したTCHAR文字列
* @return エラーがなければtrueを返す。
*/
bool Convert_SJIS_To_TCHAR(const std::string &src, std::string *pOut);
//@}

//###############################################################
//# UTF8 -> xxxx
//###############################################################
//!@name  UTF8 -> xxxx
//@{
/*!
* @brief SJIS文字列をUTF8へ変換する
* @param [in]   pUTF8  UTF8文字列ポインタ
* @param [out]  pSjis  変換したSJIS文字列が渡される。
* @return エラーがなければtrueを返す。
*/
bool Convert_UTF8_To_SJIS(const stringU8 &src, std::string *pSjis);

/*!
* @brief UTF8文字列をUTF16へ変換する
* @param [in]   pUTF8  UTF8文字列ポインタ
* @param [out]  pUTF16  変換したUTF16文字列が渡される。
* @return エラーがなければtrueを返す。
*/
bool Convert_UTF8_To_UTF16(const stringU8& src, std::wstring *pUTF16);

/*!
* @brief UTF8文字列をUTF16へ変換する
* @param [in]   pUTF8  UTF8文字列ポインタ
* @param [out]  pOut   変換したTCHAR文字列が渡される。
* @return エラーがなければtrueを返す。
*/
bool Convert_UTF8_To_TCHAR(const stringU8& src, std::string *pOut);
//@}



//###############################################################
//# UTF16 -> xxxx
//###############################################################
//!@name UTF16 -> xxxx
//@{
/*!
* @brief UTF16文字列をSJISへ変換する
* @param [in]  src   UTF16文字列
* @param [out] pOut  変換したSJIS文字列が渡される。
* @return エラーがなければtrueを返す。
*/
bool Convert_UTF16_To_SJIS(const std::wstring& src, std::string* pOut);

/*! UTF16文字列をUTF8へ変換する
* @param [in]  pSrc   UTF16文字列
* @param [out] pOut   変換したUTF8文字列が渡される。
* @return エラーがなければtrueを返す。
*/
bool Convert_UTF16_To_UTF8(const std::wstring &src, stringU8* pOut);
//@}

//---------------------------------------------------------------
//!@name TCHAR -> xxxx
//---------------------------------------------------------------
//@{
/*!
* @brief TCHAR文字列をSJISへ変換する
* @param [in]  pSrc  TCHAR文字列
* @param [out] pOut  変換したSJIS文字列
* @return エラーがなければtrueを返す。
*/
bool Convert_TCHAR_To_SJIS(const std::string& src, std::string* pOut);
/*!
* @brief TCHAR文字列をUTF8へ変換する
* @param [in]  pSrc  TCHAR文字列
* @param [out] pOut  変換したUTF8文字列
* @return エラーがなければtrueを返す。
*/
bool Convert_TCHAR_To_UTF8(const std::string& src, stringU8* pOut);
/*!
* @brief TCHAR文字列をUTF16へ変換する
* @param [in]  pSrc  TCHAR文字列
* @param [out] pOut  変換したUTF16文字列
* @return エラーがなければtrueを返す。
*/
bool Convert_TCHAR_To_UTF16(const std::string& src, std::wstring* pOut);

//@}

/*! SJIS文字列をTCHARへ変換する
* @param [in]  str  SJIS文字列
* @return 成功時TCHARに変換された文字列を返す。失敗した場合は0文字の文字列を返す
*/
std::string ToTString(const std::string& str);
/*! UTF16文字列をTCHARへ変換する
* @param [in]  str  UTF16文字列
* @return 成功時TCHARに変換された文字列を返す。失敗した場合は0文字の文字列を返す
*/
std::string ToTString(const std::wstring& str);


/*! sjis/utf8文字列をsjis/utf8へ変換する
* @param [in]  str  sjis/utf8文字列
* @return 成功時sjis/utf8に変換された文字列を返す。失敗した場合は0文字の文字列を返す
*/
std::string ToString(const std::string& str);
/*! UTF16文字列をsjis/utf8へ変換する
* @param [in]  str  UTF16文字列
* @return 成功時sjis/utf8に変換された文字列を返す。失敗した場合は0文字の文字列を返す
*/
std::string ToString(const std::wstring& str);


/*! SJIS文字列をUTF16へ変換する
* @param [in]  str  SJIS文字列
* @return 成功時UTF16に変換された文字列を返す。失敗した場合は0文字の文字列を返す
*/
std::wstring ToUTF16(const std::string& str);
/*! SJIS文字列をUTF8へ変換する
* @param [in]  str  SJIS文字列
* @return 成功時UTF8に変換された文字列を返す。失敗した場合は0文字の文字列を返す
*/
stringU8 ToUTF8(const std::string& str);
/*! UTF16文字列をUTF8へ変換する
* @param [in]  str  SJIS文字列
* @return 成功時UTF8に変換された文字列を返す。失敗した場合は0文字の文字列を返す
*/
stringU8 ToUTF8(const std::wstring& str);
/*! UTF8文字列をSJISへ変換する
* @param [in]  str  UTF8文字列
* @return 成功時SJISに変換された文字列を返す。失敗した場合は0文字の文字列を返す
*/
std::string ToSJIS(const stringU8& str);
/*! UTF16文字列をSJISへ変換する
* @param [in]  str  UTF16文字列
* @return 成功時UTF16に変換された文字列を返す。失敗した場合は0文字の文字列を返す
*/
std::string ToSJIS(const std::wstring& str);


#define MAX_DIGITS_IN_INT 12  // int型の桁の最大数 (-2147483647 = 11 桁, +1 for the '\0')
typedef std::vector<std::string> StringVec;

// 最初の'\n'のに文字を削除します
void RemoveFirstLine(std::string &src, std::string &result);

// 先頭の空白を削除します
void TrimLeft(std::string &s);

// テキストのブロックの行数をカウント
int CountLines(const std::wstring &s);


std::string ToStr(int num, int base = 10);
std::string ToStr(unsigned int num, int base = 10);
std::string ToStr(unsigned long num, int base = 10);
std::string ToStr(float num, int setprecision = 4);
std::string ToStr(double num, int setprecision = 15);
std::string ToStr(bool val);


// 文字列のベクトルに区切り文字で文字列を分割します。たとえば、次の文字列をあるとして：
//   std::string test("one,two,three");
// このようにSplit()を呼び出すことができます：
//   Split(test, outVec, ',');
// outVecは、以下の値を持つことになります：
//   "one", "two", "three"
void Split(const std::string& str, StringVec& vec, char delimiter);

std::string ToLower(const std::string &in);
std::string ToUpper(const std::string &in);


/*! 文字列からハッシュを作成する。
* @param [in]  str  文字列
* @return ハッシュを返す。
*/
inline size_t GetHash(const std::string &name)
{
	static std::hash<std::string> str_hash;
	return str_hash(name);
}


/*! 文字列からハッシュを作成する。
* @param [in]  str  文字列
* @return ハッシュを返す。
*/
inline size_t GetHash(const std::wstring &name)
{
	static std::hash<std::wstring> str_hash;
	return str_hash(name);
}



/*! 文字列から16進数文字列のハッシュ値を作成する
* @param [in]  str  文字列
* @return 16進数文字列のハッシュ値
*/
inline std::string GetHashStrHex(const std::string &name)
{
	static std::hash<std::string> str_hash;
	std::stringstream ss;
	ss << std::hex << str_hash(name);
	return ss.str();
}

/*! 文字列から16進数文字列のハッシュ値を作成する
* @param [in]  str  文字列
* @return 16進数文字列のハッシュ値
*/
inline std::wstring GetHashStrHex(const std::wstring &name)
{
	static std::hash<std::wstring> str_hash;
	std::wstringstream ss;
	ss << std::hex << str_hash(name);
	return ss.str();
}
