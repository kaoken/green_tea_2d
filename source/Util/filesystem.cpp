#include <Util/filesystem.h>


using namespace std;
using namespace std::experimental::filesystem;

/*!
 * @brief コンストラクタ
 */
GT2File::GT2File() :
	m_aCharBuffer{'\0'}
{
	SetLittleEndian();
	m_pFile			= nullptr;
	m_fileSize		= 0;
	m_isBigEndian	= true;
}
/*!
 * @brief デストラクタ
 */
GT2File::~GT2File()
{
	this->Close();
}

/*!
* @brief ファイルが存在するか？
* @param [in] pFilePath ファイルパス
* @return 存在した場合はTRUEを返す。
*/
bool GT2File::IsFileExits(const TChar * pFilePath)
{
#ifdef _UNICODE
	return IsFileExitsW(pFilePath);
#else
	return IsFileExitsA(pFilePath);
#endif
}
/*!
* @brief ファイルが存在するか？(ascii)
* @param [in] pFilePath ファイルパス
* @return 存在した場合はTRUEを返す。
*/
bool GT2File::IsFileExitsA(const char * pFilePath)
{
	error_code fileErr;
	path filePath(pFilePath);
	// 検索 .\	
	if (!exists(filePath, fileErr) || fileErr)
		return FALSE;
	return TRUE;
}
/*!
* @brief ファイルが存在するか？(UNICODE)
* @param [in] pFilePath ファイルパス
* @return 存在した場合はTRUEを返す。
*/
bool GT2File::IsFileExitsW(const wchar_t * pFilePath)
{
	error_code fileErr;
	path filePath(pFilePath);
	// 検索 .\	
	if (!exists(filePath, fileErr) || fileErr)
		return FALSE;
	return TRUE;
}

/*!
* @brief 現在の作業ディレクトリの文字列を返す
* @return 現在のワーキングディレクトリの文字列を返す。
*/
TString GT2File::GetWorkingDirectory()
{
#ifdef _UNICODE
	return GetWorkingDirectoryW();
#else
	return GetWorkingDirectoryA();
#endif
}
/*!
* @brief 現在のワーキングディレクトリの文字列を返す(ascii)
* @return 現在のワーキングディレクトリの文字列を返す。
*/
std::string GT2File::GetWorkingDirectoryA()
{
	std::string out;
	char szDir[512] = { '\0' };
#if defined(_WIN32) || defined(_WIN64)
	_getcwd(szDir, 512);

#else
	getcwd(szDir, 512);
#endif
	out = szDir;
	return out;
}
/*!
* @brief 現在のワーキングディレクトリの文字列を返す(Unicode)
* @return 現在のワーキングディレクトリの文字列を返す。
*/
std::wstring GT2File::GetWorkingDirectoryW()
{
	std::wstring out;
	wchar_t szDir[512] = { L'\0' };
#if defined(_WIN32) || defined(_WIN64)
	_wgetcwd(szDir, 512);

#else
	char szTmp[512] = { L'\0' };
	getcwd(szTmp, 512);
	ConvertCopy_UTF16_SJIS(szDir, 511, szTmp);
#endif
	out = szDir;
	return out;
}

/*!
* @brief ファイルを開いた後、そのファイルサイズを取得することができる。
* @return バイト単位のファイルサイズを返す。
*/
int64_t GT2File::GetSize() const{ return m_fileSize; }
/*!
* @brief 読み書きのモードがビッグエンディアンか？
* @return ビッグエンディアンの場合、TRUEを返す
*/
bool GT2File::IsBigEndian(){ return m_isBigEndian; }
/*!
* @brief 読み書きのモードがリトルエンディアンか？
* @return リトルエンディアンの場合、TRUEを返す
*/
bool GT2File::IsLittleEndian(){ return m_isBigEndian == FALSE; }
/*!
* @brief 読み書き時、ビッグエンディアン・モードにする
* @return なし
*/
void GT2File::SetBigEndian(){ m_isBigEndian = TRUE; }
/*!
* @brief 読み書き時、リトルエンディアン・モードにする
* @return なし
*/
void GT2File::SetLittleEndian(){ m_isBigEndian = FALSE; }
/*!
* @brief 指定された位置にファイル ポインタを移動します。
* @param [in] offset   origin からのバイト数。
* @param [in] origin   初期位置。
*   @arg SEEK_CUR : ファイル ポインタの現在位置。
*   @arg SEEK_END : ファイルの終端。
*   @arg SEEK_SET : ファイルの先頭。
* @return これらの各関数は、str を返します。エラーが発生、またはファイルの終端に達すると、nullptr を返します。
*/
int GT2File::SeekSet(int64_t offset, int origin)
{
#if defined(_WIN32) || defined(_WIN64)
	return _fseeki64(m_pFile, offset, origin);
#else
	return fseek64(m_pFile, offset, origin);
#endif
}

/*!
* @brief ファイル ポインタの現在位置を取得します。
* @return 現在のファイル位置を返します。
*/
int64_t GT2File::Tell()
{
#if defined(_WIN32) || defined(_WIN64)
	return _ftelli64(m_pFile);
#else
	return ftello64(m_pFile);
#endif
}

/*!
* @brief EOFか？
* @return EOFの場合TRUEを返す。
*/
bool GT2File::IsEOF() const
{
	if (m_pFile == 0)
		return TRUE;

	return feof(m_pFile) ? TRUE : FALSE;
}


/*!
* @brief トリームを閉じます
* @return ストリームが正常に閉じられた場合、 0 を返します。エラーが発生したときは EOF を返します。
*/
bool GT2File::Close()
{
	bool bRet = TRUE;

	if (m_pFile != nullptr){
		bRet = ::fclose(m_pFile);
		m_pFile = nullptr;
	}
	return bRet;
}


/*!
* @brief ストリームにデータを書き込みます。
* @param [in] buffer 書き込むデータへのポインタ
* @param [in] size   項目のサイズ (バイト単位)。
* @param [in] count  書き込む最大項目数。
* @return 実際に書き込まれた完全な項目の数を返します。この数は、エラーが発生した場合、count より少なくなることがあります。
*/
size_t GT2File::Write(const void *pvBuffer, size_t size, size_t count)
{
	return fwrite(pvBuffer, size, count, m_pFile);
}


/*!
* @brief ストリームにデータを書き込みます。
* @param [in] format     書式指定文字列。
* @param [in] argument   省略可能な引数。
* @return 出力したバイト数を返します。失敗した場合は-1を返します。
*/
int GT2File::Printf(const TChar *format, ...)
{
	int ret;
	va_list args;
	va_start(args, format);

	ret = gt2_vfprintf(m_pFile, format, args);

	va_end(args);

	return ret;
}
/*!
* @brief ストリームにデータを書き込みます。文字コードがASCII
* @param [in] format     書式指定文字列。
* @param [in] argument   省略可能な引数。
* @return 出力したバイト数を返します。失敗した場合は-1を返します。
*/
int GT2File::PrintfA(const char *format, ...)
{
	int ret;
	va_list args;

	va_start(args, format);
	ret = vfprintf_s(m_pFile, format, args);
	va_end(args);

	return ret;
}
/*!
* @brief ストリームにデータを書き込みます。文字コードがunicode
* @param [in] format     書式指定文字列。
* @param [in] argument   省略可能な引数。
* @return 出力したバイト数を返します。失敗した場合は-1を返します。
*/
int GT2File::PrintfW(const wchar_t *format, ...)
{
	int ret;
	va_list args;

	va_start(args, format);
	ret = vfwprintf_s(m_pFile, format, args);
	va_end(args);

	return ret;
}

/*!
* @brief ストリームに文字列を書き込みます。
* @param [in] str 出力する文字列。
* @return これらの各関数は、正常に処理されると負でない値を返します。エラーが発生すると、
*         PutsA 関数は EOF を返し、PutsW 関数は WEOFを返します。
*/
int GT2File::Puts(const TChar *str)
{
#ifdef _UNICODE
	return this->PutsW(str);
#else
	return this->PutsA(str);
#endif
}
/*!
* @brief ストリームに文字列を書き込みます。文字コードがASCII
* @param [in] str 出力する文字列。
* @return これらの各関数は、正常に処理されると負でない値を返します。
*         エラーが発生すると、fputs 関数は EOF を返します。
*/
int GT2File::PutsA(const char *str)
{
	return fputs(str, m_pFile);
}
/*!
* @brief ストリームに文字列を書き込みます。文字コードがunicode
* @param [in] str 出力する文字列。
* @return これらの各関数は、正常に処理されると負でない値を返します。
*         エラーが発生すると、WEOFを返します。
*/
int GT2File::PutsW(const wchar_t *str)
{
	return fputws(str, m_pFile);
}

/*!
* @brief ストリームからデータを読み出します。
* @param [in] buffer  データの格納場所。
* @param [in] size    項目のサイズ (バイト単位)。
* @param [in] count   読み出す最大項目数。
* @return 実際に読み取った完全な項目の数を返します。この数は、エラーが発生した場合や、
*  count に達する前にファイルの終端に達した場合に、count より少なることがあります。
*/
size_t GT2File::Read(void *pvBuffer, size_t size, size_t count)
{
	return fread(pvBuffer, size, count, m_pFile);
}
/*!
* @brief ストリームから書式化されたデータを読み出します。
* @param [in] format     書式指定文字列。
* @param [in] argument   省略可能な引数。
* @return 入力したバイト数を返します。失敗した場合は-1を返します。
*/
int GT2File::Scanf(const TChar *format, ...)
{
	int i, iNum;
	va_list args;
	va_start(args, format);

	GT2ZeroMemory(m_aCharBuffer, FBUFFER_SIZE);

#ifdef _UNICODE
	wchar_t buff[4] = { L'\0' };
	wchar_t *wBuff = (wchar_t*)m_aCharBuffer;
	for (i = 0; i < FBUFFER_SIZE / 2; i++)
	{
		if (this->GetsW(buff, 1) != nullptr)
		{
			wBuff[i] = buff[0];
			if (buff[0] == L'\n')
			{
				break;
			}
		}
		else
		{
			va_end(args);
			return -1;
		}
	}

	iNum = vswscanf((wchar_t*)m_aCharBuffer, format, args);
#else
	char buff[4] = { '\0' };
	for (i = 0; i < FBUFFER_SIZE; i++)
	{
		if (this->GetsA(buff, 1) != nullptr)
		{
			m_aCharBuffer[i] = buff[0];
			if (buff[0] == '\n')
			{
				break;
			}
		}
		else
		{
			va_end(args);
			return -1;
		}
	}

	iNum = vsscanf(m_aCharBuffer, format, args);
#endif
	va_end(args);
	return iNum;
}
/*!
* @brief ストリームから書式化されたデータを読み出します。文字コードがASCII
* @param [in] format     書式指定文字列。
* @param [in] argument   省略可能な引数。
* @return 入力したバイト数を返します。失敗した場合は-1を返します。
*/
int GT2File::ScanfA(const char *format, ...)
{
	int i, iNum;

	char buff[4] = { '\0' };
	va_list args;

	va_start(args, format);
	GT2ZeroMemory(m_aCharBuffer, FBUFFER_SIZE);

	for (i = 0; i < FBUFFER_SIZE; i++)
	{
		if (this->GetsA(buff, 1) != nullptr)
		{
			m_aCharBuffer[i] = buff[0];
			if (buff[0] == '\n')
			{
				break;
			}
		}
		else
		{
			va_end(args);
			return -1;
		}
	}

	iNum = vsscanf(m_aCharBuffer, format, args);

	va_end(args);

	return iNum;
}
/*!
* @brief ストリームから書式化されたデータを読み出します。文字コードがunicode
* @param [in] format     書式指定文字列。
* @param [in] argument   省略可能な引数。
* @return 入力したバイト数を返します。失敗した場合は-1を返します。
*/
int GT2File::ScanfW(const wchar_t *format, ...)
{
	int i, iNum;

	wchar_t buff[4] = { L'\0' };
	va_list args;

	va_start(args, format);
	GT2ZeroMemory(m_aCharBuffer, FBUFFER_SIZE);

	wchar_t *wBuff = (wchar_t*)m_aCharBuffer;
	for (i = 0; i < FBUFFER_SIZE / 2; i++)
	{
		if (this->GetsW(buff, 1) != nullptr)
		{
			wBuff[i] = buff[0];
			if (buff[0] == L'\n')
			{
				break;
			}
		}
		else
		{
			va_end(args);
			return -1;
		}
	}

	iNum = vswscanf((wchar_t*)m_aCharBuffer, format, args);

	va_end(args);

	return iNum;
}

/*!
* @brief ストリームに文字列を書き込みます。
* @param [in] str データの格納場所。
* @param [in] n   読み取る最大文字数。
* @return これらの各関数は、str を返します。エラーが発生、またはファイルの終端に達すると、nullptr を返します。
*/
TChar* GT2File::Gets(TChar *str, int n)
{
#ifdef _UNICODE
	return this->GetsW(str, n);
#else
	return this->GetsA(str, n);
#endif
}
/*!
* @brief ストリームに文字列を書き込みます。
* @param [in] str データの格納場所。
* @param [in] n   読み取る最大文字数。
* @return これらの各関数は、str を返します。エラーが発生、またはファイルの終端に達すると、nullptr を返します。
*/
char* GT2File::GetsA(char *str, int n)
{
	return fgets(str, n, m_pFile);
}
/*!
* @brief ストリームに文字列を書き込みます。
* @param [in] str データの格納場所。
* @param [in] n   読み取る最大文字数。
* @return これらの各関数は、str を返します。エラーが発生、またはファイルの終端に達すると、nullptr を返します。
*/
wchar_t* GT2File::GetsW(wchar_t *str, int n)
{
	return fgetws(str, n, m_pFile);
}

/*!
 * 対象ファイルのすべてを文字列として読み込む
 * @info ただし、読み込み位置が一番はじめになる。
 * @param [out] str     読み込んだ文字列を格納する
 * @return 読み込んだ文字数を返す。エラー時は、0または、ファイルサイズより少ない値が返る。
 */
int GT2File::AllReadString(std::string& str)
{
	if (m_pFile == nullptr || m_fileSize == 0) return 0;

	return this->ReadString(m_fileSize, str);
}
/*!
* @brief 文字列を読み込む tchar版
* @param [in]  length  読み込む文字数。
* @param [out] str     読み込んだ文字列を格納する
* @return 読み込んだ文字数を返す。エラー時は、0または、lengthより少ない値が返る。
*/
int GT2File::ReadString(gtUINT length, TString &str)
{
	if (m_pFile == nullptr) return 0;

	str.resize(length);
	int size = (int)this->Read(&str[0], sizeof(TChar), length);
	str.resize(size);

	return size;
}
/*!
* @brief 文字列を読み込む Ascii版
* @param [in]  length  読み込む文字数。1文字あたり1バイト
* @param [out] str     読み込んだ文字列を格納する。
* @return 読み込んだ文字数を返す。エラー時は、0または、lengthより少ない値が返る。
*/
int GT2File::ReadStringA(gtUINT length, std::string &str)
{
	if (m_pFile == nullptr) return 0;

	str.resize(length);
	int size = (int)this->Read(&str[0], sizeof(char), length);
	str.resize(size);

	return size;
}
/*!
* @brief 文字列を読み込む unicode版
* @param [in]  length  読み込む文字数。1文字あたり2バイト
* @param [out] str     読み込んだ文字列を格納する
* @return 読み込んだ文字数を返す。エラー時は、0または、lengthより少ない値が返る。
*/
int GT2File::ReadStringW(gtUINT length, std::wstring &str)
{
	if (m_pFile == nullptr) return 0;

	str.resize(length);
	int size = (int)this->Read(&str[0], sizeof(wchar_t), length);
	str.resize(size);

	return size;
}
/*!
* @brief 一行（改行文字が現れるまで）読み込む TCHAR版
* @param [out] str     読み込んだ文字列を格納する
* @return 読み込んだ文字数を返す。エラー時は、0が返る。
*/
int GT2File::ReadLine(TString &str)
{
#ifdef _UNICODE
	return this->ReadLineW(str);
#else
	return this->ReadLineA(str);
#endif
}
/*!
* @brief 一行（改行文字が現れるまで）読み込む Ascii版
* @param [out] str     読み込んだ文字列を格納する
* @return 読み込んだ文字数を返す。エラー時は、0が返る。
*/
int GT2File::ReadLineA(std::string &str)
{
	if (m_pFile == nullptr) return 0;

	str = "";
	char buf[256];

	do
	{
		int start = ftell(m_pFile);
		buf[255] = 1;
		char *r = fgets(buf, 256, m_pFile);
		if (r == 0) break;
		int end = ftell(m_pFile);
		str.append(buf, end - start);
	} while (!feof(m_pFile) && buf[255] == 0 && buf[254] != '\n');

	return int(str.size());
}
/*!
* @brief 一行（改行文字が現れるまで）読み込む Unicode版
* @param [out] str     読み込んだ文字列を格納する
* @return 読み込んだ文字数を返す。エラー時は、0が返る。
*/
int GT2File::ReadLineW(std::wstring &str)
{
	if (m_pFile == nullptr) return 0;

	str = L"";
	wchar_t buf[256];

	do
	{
		int start = ftell(m_pFile);
		buf[255] = 1;
		wchar_t *r = fgetws(buf, 256, m_pFile);
		if (r == 0) break;
		int end = ftell(m_pFile);
		str.append(buf, end - start);
	} while (!feof(m_pFile) && buf[255] == 0 && buf[254] != L'\n');

	return int(str.size());
}
#define RUInt16() ((uint16_t)ReadU8())
#define RUInt32() ((uint32_t)ReadU8())
#define RUInt64() ((uint64_t)ReadU8())

/*!
* @brief 符号なし1バイト整数を読み込む
* @return 符号なし1バイト整数を読み込む
*/
uint8_t GT2File::ReadU8()
{
	if (m_pFile == 0) return 0;
	uint8_t u;
	if (!this->Read(&u, 1, 1))
		return 0;
	return u;
}
/*!
* @brief 符号なし2バイト整数を読み込む
* @return 符号なし2バイト整数を読み込む
*/
uint16_t GT2File::ReadU16()
{
	if (m_pFile == 0) return 0;
	if (!m_isBigEndian) { uint16_t tmp; Read(&tmp, 2, 1); return tmp; }
	return (RUInt16() | (RUInt16() << 8));
}
/*!
* @brief 符号なし4バイト整数を読み込む
* @return 符号なし4バイト整数を読み込む
*/
uint32_t GT2File::ReadU32()
{
	if (m_pFile == 0) return 0;
	if (!m_isBigEndian) { uint32_t tmp; Read(&tmp, 4, 1); return tmp; }
	return RUInt32() | (RUInt32() << 8) | (RUInt32() << 16) | (RUInt32() << 24);
}
/*!
* @brief 符号なし8バイト整数を読み込む
* @return 符号なし8バイト整数を読み込む
*/
uint64_t GT2File::ReadU64()
{
	if (m_pFile == 0) return 0;
	if (!m_isBigEndian) { long tmp; Read(&tmp, 8, 1); return tmp; }
	return RUInt64() | (RUInt64() << 8) | (RUInt64() << 16) |
		(RUInt64() << 24) | (RUInt64() << 32) | (RUInt64() << 40) |
		(RUInt64() << 48) | (RUInt64() << 56);
}
/*!
* @brief 1バイト整数を読み込む
* @return 1バイト整数を読み込む
*/
int8_t GT2File::ReadN8()
{
	int8_t n = ReadU8();
	return R_CAST(int8_t&, n);
}
/*!
* @brief 2バイト整数を読み込む
* @return 2バイト整数を読み込む
*/
int16_t GT2File::ReadN16()
{
	uint16_t n = ReadU16();
	return R_CAST(int16_t&, n);
}
/*!
* @brief 4バイト整数を読み込む
* @return 4バイト整数を読み込む
*/
int32_t GT2File::ReadN32()
{
	uint32_t n = ReadU32();
	return R_CAST(int32_t&, n);
}
/*!
* @brief 8バイト整数を読み込む
* @return 8バイト整数を読み込む
*/
int64_t GT2File::ReadN64()
{
	uint64_t n = ReadU64();
	return R_CAST(int64_t&, n);
}
/*!
* @brief 4バイト浮動小数を読み込む
* @return 4バイト整数を読み込む
*/
float GT2File::ReadF32()
{
	uint32_t n = ReadU32();
	return R_CAST(float&, n);
}
/*!
* @brief 8バイト浮動小数を読み込む
* @return 8バイト整数を読み込む
*/
double GT2File::ReadF64()
{
	uint64_t n = ReadU64();
	return R_CAST(double&, n);
}
/*!
* @brief 文字列を書き込む。 tchar版
* @param [in] length  読み込む文字数。1文字あたり1～2バイト
* @param [in] str     書き込む文字列
* @return 読み込んだ文字数を返す。エラー時は、-1が返る。
*/
int GT2File::WriteString(gtUINT length, const TString &str)
{
#ifdef _UNICODE
	return this->WriteStringW(length, str);
#else
	return this->WriteStringA(length, str);
#endif
}
/*!
* @brief 文字列を書き込む。ascii版
* @param [in] length  読み込む文字数。1文字あたり1バイト
* @param [in] str     書き込む文字列
* @return 書き込んだ文字数を返す。エラー時は、-1が返る。
*/
int GT2File::WriteStringA(gtUINT length, const std::string &str)
{
	if (m_pFile == 0) return -1;
	length = (gtUINT)(str.length() < length ? str.length() : length);
	size_t r = fwrite(&str[0], 1, length, m_pFile);
	return int(r);
}
/*!
* @brief 文字列を書き込む。unicode版
* @param [in] length  読み込む文字数。1文字あたり2バイト
* @param [in] str     書き込む文字列
* @return 書き込んだ文字数を返す。エラー時は、-1が返る。
*/
int GT2File::WriteStringW(gtUINT length, const std::wstring &str)
{
	if (m_pFile == 0) return -1;
	length = (gtUINT)(str.length() < length ? str.length() : length);
	size_t r = fwrite(&str[0], 2, length, m_pFile);
	return int(r);
}

/*!
* @brief 1バイトの符号なし整数を書き込む
* @param [in] u     書き込む数値
* @return 書き込んだ場合は1を返し、失敗した場合は、0を返します。
*/
int GT2File::WriteU8(uint8_t u)
{
	int r;
	r = (int)Write(&u, 1, 1);
	return r;
}
/*!
* @brief 2バイトの符号なし整数を書き込む
* @param [in] u     書き込む数値
* @return 書き込んだ場合は1を返し、失敗した場合は、0を返します。
*/
int GT2File::WriteU16(uint16_t u)
{
	int r;
	if (!m_isBigEndian) { r = (int)Write(&u, 2, 1); return r; }
	r = WriteU8((uint8_t)( u & 0x00FF)); if (r == 0)return 0;
	r = WriteU8((uint8_t)((u & 0xFF00) >> 8)); if (r == 0)return 0;
	return r;
}
/*!
* @brief 4バイトの符号なし整数を書き込む
* @param [in] u     書き込む数値
* @return 書き込んだ場合は1を返し、失敗した場合は、0を返します。
*/
int GT2File::WriteU32(uint32_t u)
{
	int r;
	if (!m_isBigEndian) { r = (int)Write(&u, 4, 1); return r; }
	r = WriteU8((uint8_t)( u & 0x000000FF)); if (r == 0)return 0;
	r = WriteU8((uint8_t)((u & 0x0000FF00) >> 8)); if (r == 0)return 0;
	r = WriteU8((uint8_t)((u & 0x00FF0000) >> 16)); if (r == 0)return 0;
	r = WriteU8((uint8_t)((u & 0xFF000000) >> 24)); if (r == 0)return 0;
	return r;
}
/*!
* @brief 8バイトの符号なし整数を書き込む
* @param [in] u     書き込む数値
* @return 書き込んだ場合は1を返し、失敗した場合は、0を返します。
*/
int GT2File::WriteU64(uint64_t u)
{
	int r;
	if (!m_isBigEndian) { r = (int)Write(&u, 8, 1); return r; }
	r = WriteU8((uint8_t)( u & 0x00000000000000FF));
	r = WriteU8((uint8_t)((u & 0x000000000000FF00) >> 8));
	r = WriteU8((uint8_t)((u & 0x0000000000FF0000) >> 16));
	r = WriteU8((uint8_t)((u & 0x00000000FF000000) >> 24));
	r = WriteU8((uint8_t)((u & 0x000000FF00000000) >> 32));
	r = WriteU8((uint8_t)((u & 0x0000FF0000000000) >> 40));
	r = WriteU8((uint8_t)((u & 0x00FF000000000000) >> 48));
	r = WriteU8((uint8_t)((u & 0xFF00000000000000) >> 56));
	return r;
}
/*!
* @brief 1バイトの整数を書き込む
* @param [in] u     書き込む数値
* @return 書き込んだ場合は1を返し、失敗した場合は、0を返します。
*/
int GT2File::WriteN8(int8_t n)
{
	return WriteU8(R_CAST(uint8_t&, n));
}
/*!
* @brief 2バイトの整数を書き込む
* @param [in] u     書き込む数値
* @return 書き込んだ場合は1を返し、失敗した場合は、0を返します。
*/
int GT2File::WriteN16(int16_t n)
{
	return WriteU16(R_CAST(uint16_t&, n));
}
/*!
* @brief 4バイトの整数を書き込む
* @param [in] u     書き込む数値
* @return 書き込んだ場合は1を返し、失敗した場合は、0を返します。
*/
int GT2File::WriteN32(int32_t n)
{
	return WriteU32(R_CAST(uint32_t&, n));
}
/*!
* @brief 8バイトの整数を書き込む
* @param [in] u     書き込む数値
* @return 書き込んだ場合は1を返し、失敗した場合は、0を返します。
*/
int GT2File::WriteN64(int64_t n)
{
	return WriteU64(R_CAST(uint64_t&, n));
}
/*!
* @brief 4バイトの浮動小数を書き込む
* @param [in] u     書き込む数値
* @return 書き込んだ場合は1を返し、失敗した場合は、0を返します。
*/
int GT2File::WriteF32(float f)
{
	return WriteU32(R_CAST(uint32_t&, f));
}
/*!
* @brief 8バイトの浮動小数を書き込む
* @param [in] u     書き込む数値
* @return 書き込んだ場合は1を返し、失敗した場合は、0を返します。
*/
int GT2File::WriteF64(double f)
{
	return WriteU64(R_CAST(uint64_t&, f));
}

/*!
* @brief ストリームにデータを書き込みます。
* @param [in] pFileName ファイル名。
* @param [in] pMode   アクセス許可の種類。
* @return 正常終了した場合は 0 を返します。
*/
bool GT2File::Open(const TChar* pFileName, const TChar *pMode)
{
#ifdef _UNICODE
	return this->OpenW(pFileName, pMode);
#else 
	return this->OpenA(pFileName, pMode);
#endif
}
/*!
* @brief ストリームにデータを書き込みます。文字コードがASCII
* @param [in] pFileName ファイル名。
* @param [in] pMode   アクセス許可の種類。
* @return 正常終了した場合は 0 を返します。
*/
bool GT2File::OpenA(const char* pFileName, const char *pMode)
{
	this->Close();

#if defined(_WIN32) || defined(_WIN64)
	errno_t err = fopen_s(&m_pFile, pFileName, pMode);
	if (err == 0)
	{
		this->SeekSet(0, SEEK_END);
		m_fileSize = this->Tell();
		this->SeekSet(0, SEEK_SET);
	}
	return err == 0;

#else
	if ((m_pFile = fopen64(pFileName, pMode) != nullptr)
		return TRUE;
	return FALSE;
#endif
}
/*!
* @brief ストリームにデータを書き込みます。文字コードがunicode
* @param [in] pFileName ファイル名。
* @param [in] pMode   アクセス許可の種類。
* @return 正常終了した場合は 0 を返します。
*/
bool GT2File::OpenW(const wchar_t* pFileName, const wchar_t *pMode)
{
	this->Close();

#if defined(_WIN32) || defined(_WIN64)
	errno_t err = _wfopen_s(&m_pFile, pFileName, pMode);
	if (err == 0)
	{
		this->SeekSet(0, SEEK_END);
		m_fileSize = this->Tell();
		this->SeekSet(0, SEEK_SET);
	}
	return err == 0;

#else
	char szFileName[512] = { '\0}' };
	char szMode[32] = { '\0}' };

	Convert_UTF16_To_SJIS(szFileName, 511, pFileName);
	Convert_UTF16_To_SJIS(szMode, 511, pMode);

	if ((m_pFile = fopen64(szFileName, szMode) != nullptr)
		return TRUE;
	return FALSE;
#endif
}

#if defined(ANDROID) || defined(__ANDROID__)
bool CAPKFile::Open(char const* path)
{
	if (m_assetManager == nullptr)return false;
	m_pFile = AAssetManager_open(m_assetManager, path, AASSET_MODE_UNKNOWN);
	if (m_pFile == nullptr)
		return false;
	return true;
}
//! @param
void CAPKFile::Close()
{
	if( m_pFile )
		AAsset_close(m_pFile);
	m_pFile = nullptr;
}

int CAPKFile::Getc()
{
	char buff;
	AAsset_read(m_pFile, &buff, 1);

	return buff;
}

char* CAPKFile::Gets(char* s, int size)
{
	int i;
	char *d = s;
	for (i = 0; (size > 1) && (!this->Eof()); i++, size--, d++)
	{
		this->Read(d, 1, 1);
		if (*d == 10)
		{
			size = 1;
		}
	}
	*d = 0;

	return s;
}

size_t CAPKFile::Size()
{
	return AAsset_getLength(m_pFile);
}

size_t CAPKFile::Seek(long offset, int type)
{
	return (size_t)AAsset_seek(m_pFile, offset, type);
}

size_t CAPKFile::Tell()
{
	return this->Size() - AAsset_getRemainingLength(m_pFile);
}

size_t CAPKFile::Read(void* ptr, size_t size, size_t nmemb)
{
	size_t readLength = size*nmemb;

	size_t avail = this->Size() - this->Tell();
	if (readLength > avail)
	{
		readLength = avail;
		nmemb = readLength / size;
	}

	return AAsset_read(m_pFile, ptr, readLength);
}

int CAPKFile::Eof()
{
	int rv = (this->Tell() >= this->Size()) ? 1 : 0;
	return rv;
}
#endif // _ANDROID










//##############################################################################################
//##############################################################################################
//##############################################################################################
//###
//### ファイルの種類
//###
//##############################################################################################
//##############################################################################################
//##############################################################################################

//-----------------------------------------------------------------------------------
//! @brief ファイル名を指定して、ファイルタイプを取得する。UTF16版
//! @param [in] pFilePath   ファイルパス
//! @return GT2_FILE_TYPE列挙対の値
//! @see GT2_FILE_TYPE
//-----------------------------------------------------------------------------------
GT2_FILE_TYPE GetFileTypeW(const wchar_t* pFilePath)
{
	std::string path;
	Convert_UTF16_To_SJIS(pFilePath, &path);
	return GetFileTypeA(path.c_str());
}
//-----------------------------------------------------------------------------------
//! @brief ファイル名を指定して、ファイルタイプを取得する。ASCII版
//! @param [in] pFilePath   ファイルパス
//! @return GT2_FILE_TYPE列挙対の値
//! @see GT2_FILE_TYPE
//-----------------------------------------------------------------------------------
GT2_FILE_TYPE GetFileTypeA(const char* pFilePath)
{
	byte aBuff[32];
	int64_t len;
	// ファイルが存在しない
	if( !GT2File::IsFileExitsA(pFilePath) )
		return GT2_FILE_TYPE::NO_EXISTS;

	GT2File file;

	file.OpenA(pFilePath,"rb");

	len = file.GetSize();
	if (len > 32)len = 32;
	else return GT2_FILE_TYPE::UNKNOWN;

	file.Read(aBuff, len, 1);

#define MAGIC_NO_CHEKC_2(_start_idx, _no0, _no1) ((aBuff[_start_idx] == _no0) && (aBuff[_start_idx+1] == _no1))
#define MAGIC_NO_CHEKC_3(_start_idx, _no0, _no1, _no2) ( MAGIC_NO_CHEKC_2(_start_idx, _no0, _no1) && (aBuff[_start_idx+2] == _no2))
#define MAGIC_NO_CHEKC_4(_start_idx, _no0, _no1, _no2, _no3) ( MAGIC_NO_CHEKC_3(_start_idx, _no0, _no1,_no2 ) && (aBuff[_start_idx+3] == _no3) )
#define MAGIC_NO_CHEKC_5(_start_idx, _no0, _no1, _no2, _no3, _no4) ( MAGIC_NO_CHEKC_4(_start_idx, _no0, _no1,_no2, _no3) && (aBuff[_start_idx+4] == _no4) )
#define MAGIC_NO_CHEKC_6(_start_idx, _no0, _no1, _no2, _no3, _no4, _no5) ( MAGIC_NO_CHEKC_5(_start_idx, _no0, _no1, _no2, _no3, _no4) && (aBuff[_start_idx+5] == _no5) )
#define MAGIC_NO_CHEKC_7(_start_idx, _no0, _no1, _no2, _no3, _no4, _no5, _no6) ( MAGIC_NO_CHEKC_6(_start_idx, _no0, _no1, _no2, _no3, _no4, _no5) && (aBuff[_start_idx+6] == _no6) )
#define MAGIC_NO_CHEKC_8(_start_idx, _no0, _no1, _no2, _no3, _no4, _no5, _no6, _no7) ( MAGIC_NO_CHEKC_7(_start_idx, _no0, _no1, _no2, _no3, _no4, _no5, _no6) && (aBuff[_start_idx+7] == _no7) )
#define MN_OR_2(_idx, _no0, _no1) ((aBuff[_idx] == _no0) || (aBuff[_idx] == _no1))
#define MN_OR_3(_idx, _no0, _no1, _no2) ( MN_OR_2(_idx, _no0, _no1)|| (aBuff[_idx] == _no2))

	if (MAGIC_NO_CHEKC_3(0, 0xFF, 0xD8, 0xFF) ||  // SOI
		MAGIC_NO_CHEKC_3(0, 0xFF, 0xD9, 0xFF)) { // EOI
		// JPEG画像ファイル
		return GT2_FILE_TYPE::JPG;
	}
	else if (MAGIC_NO_CHEKC_6(0, 0x47, 0x49, 0x46, 0x36, 0x37, 0x61) ||
		     MAGIC_NO_CHEKC_6(0, 0x47, 0x49, 0x46, 0x36, 0x39, 0x61))
	{
		// GIF画像ファイル
		return GT2_FILE_TYPE::GIF;
	}
	else if (MAGIC_NO_CHEKC_8(0, 0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A))
	{
		// PNG画像ファイル
		return GT2_FILE_TYPE::PNG;
	}
	else if (MAGIC_NO_CHEKC_3(0, 0x44, 0x44, 0x53))
	{
		// DDS画像ファイル
		return GT2_FILE_TYPE::DDS;
	}
	else if (MAGIC_NO_CHEKC_2(0, 0x42, 0x4D))
	{
		// BMP画像ファイル
		return GT2_FILE_TYPE::BMP;
	}
	else if (MAGIC_NO_CHEKC_4(0, 0x00, 0x00, 0x01, 0x00))
	{
		// アイコン画像ファイル
		return GT2_FILE_TYPE::ICO;
	}
	else if (MAGIC_NO_CHEKC_4(0, 0x49, 0x49, 0x2A, 0x00) ||
		MAGIC_NO_CHEKC_4(0, 0x4D, 0x4D, 0x00, 0x2A))
	{
		// TIFF画像ファイル
		return GT2_FILE_TYPE::TIFF;
	}
	else if (MAGIC_NO_CHEKC_5(0, 0x00, 0x00, 0x02, 0x00, 0x00) )
	{
		// TGA画像ファイル
		return GT2_FILE_TYPE::TGA;
	}
	else if (MAGIC_NO_CHEKC_3(0, 0x49, 0x49, 0xBC))
	{
		// Windows Media Photo画像ファイル
		return GT2_FILE_TYPE::WMP;
	}
	else if (MAGIC_NO_CHEKC_4(0, 0x46, 0x4F, 0x52, 0x4D) && MAGIC_NO_CHEKC_4(8, 0x41, 0x49, 0x46, 0x46))
	{
		//AIFF音声ファイル
		return GT2_FILE_TYPE::AIFF;
	}
	else if (MAGIC_NO_CHEKC_4(0, 0x52, 0x49, 0x46, 0x46) && MAGIC_NO_CHEKC_4(8, 0x57, 0x41, 0x56, 0x45))
	{
		//WAV音声ファイル
		return GT2_FILE_TYPE::WAV;
	}
	else if (MAGIC_NO_CHEKC_2(0, 0xFF, 0xFB) || MAGIC_NO_CHEKC_3(0, 0x49, 0x44, 0x33))
	{
		//MP3音声ファイル
		return GT2_FILE_TYPE::MP3;
	}
	else if (MAGIC_NO_CHEKC_4(0, 0x4F, 0x67, 0x67, 0x53))
	{
		//OGG音声ファイル
		return GT2_FILE_TYPE::OGG;
	}
	else if (MAGIC_NO_CHEKC_4(0, 0x66, 0x4C, 0x61, 0x43))
	{
		//Flac音声ファイル
		return GT2_FILE_TYPE::FLAC;
	}
	else if (MAGIC_NO_CHEKC_4(0, 0x4D, 0x54, 0x68, 0x64))
	{
		// MIDI音声ファイル
		return GT2_FILE_TYPE::FLAC;
	}
	else if ((MAGIC_NO_CHEKC_4(0, 0x52, 0x49, 0x46, 0x46) && MAGIC_NO_CHEKC_8(8, 0x41, 0x56, 0x49, 0x20, 0x4C, 0x49, 0x53, 0x54)))
	{
		// AVI動画ァイル
		return GT2_FILE_TYPE::AVI;
	}
	else if ((MAGIC_NO_CHEKC_3(0, 0x00, 0x00, 0x00) && MAGIC_NO_CHEKC_4(4, 0x66, 0x74, 0x79, 0x70)) ||
		MAGIC_NO_CHEKC_4(4, 0x33, 0x67, 0x70, 0x35))
	{
		// MP4動画ァイル
		return GT2_FILE_TYPE::MP4;
	}
	else if (MAGIC_NO_CHEKC_8(0, 0x30, 0x26, 0xB2, 0x75, 0x8E, 0x66, 0xCF, 0x11) ||
		MAGIC_NO_CHEKC_8(0, 0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C))
	{
		// WMV動画ァイル
		return GT2_FILE_TYPE::WMV;
	}
	else if (MAGIC_NO_CHEKC_3(0, 0x00, 0x00, 0x01) && (aBuff[4] >= 0xB0 && aBuff[4] <= 0xBF))
	{
		// MPEG2動画ァイル
		return GT2_FILE_TYPE::MPEG2;
	}
	else if (MAGIC_NO_CHEKC_4(0, 0x50, 0x4B, 0x03, 0x04) || 
		     MAGIC_NO_CHEKC_4(0, 0x50, 0x4B, 0x05, 0x06) || 
		     MAGIC_NO_CHEKC_4(0, 0x50, 0x4B, 0x07, 0x08))
	{
		// ZIP圧縮ファイル
		return GT2_FILE_TYPE::ZIP;
	}
	else if (MAGIC_NO_CHEKC_8(0, 0x52, 0x61, 0x72, 0x21, 0x1A, 0x07, 0x01, 0x00) ||
		     MAGIC_NO_CHEKC_7(0, 0x52, 0x61, 0x72, 0x21, 0x1A, 0x07, 0x00) )
	{
		// RAR圧縮ファイル
		return GT2_FILE_TYPE::RAR;
	}
	else if (MAGIC_NO_CHEKC_3(0, 0x42, 0x5A, 0x68))
	{
		// BZ2圧縮ファイル
		return GT2_FILE_TYPE::BZ2;
	}
	else if (MAGIC_NO_CHEKC_3(0, 0x42, 0x5A, 0x68))
	{
		// BZ2圧縮ファイル
		return GT2_FILE_TYPE::BZ2;
	}
	else if (MAGIC_NO_CHEKC_2(0, 0x1F, 0xA0))
	{
		// LZH圧縮ファイル
		return GT2_FILE_TYPE::LZH;
	}


	return GT2_FILE_TYPE::UNKNOWN;
}



//##############################################################################################
//##############################################################################################
//##############################################################################################
//###
//### ファイル検索
//###
//##############################################################################################
//##############################################################################################
//##############################################################################################

//-----------------------------------------------------------------------------------
//! @brief ファイル名を指定して、ファイルパスを取得する。ASCII版
//! @param [out] pOutPath   見つけたファイルパス
//! @param [in]  pFileName  ファイル名
//! @param [in]  pAddDir    ファイル名の後ろに追加する相対ディレクトリ名。省略可能
//! @return 見つけた場合はGT_S_OKを返す
//-----------------------------------------------------------------------------------
gt2HRESULT SimpleFindFilePathA(std::string* pOutPath, const char* pFileName, const char* pAddDir)
{
	if (pFileName == nullptr) return GT_E_INVALIDARG;
	// よくあるディレクトリー:
	//		%カレントディレクトリ%\ 
	//		%カレントディレクトリ%\..\ 
	//		%カレントディレクトリ%\..\..\  
	//		%カレントディレクトリ%\..\..\..\ 
	gt2HRESULT ret = GT_S_OK;
	error_code fileErr;
	path filePath(pFileName);
	path tmpPath;

	if (pAddDir != nullptr) tmpPath = pAddDir;

	if (tmpPath.is_relative())
		filePath = tmpPath / filePath;

	// 検索 .\	
	tmpPath = filePath;
	if (!(!exists(tmpPath, fileErr) || fileErr))
		goto GOTO_END;

	// 検索 ..\	
	tmpPath = "..\\" / filePath;
	if (!(!exists(filePath, fileErr) || fileErr))
		goto GOTO_END;

	// 検索 ..\..\ 
	tmpPath = "..\\..\\" / filePath;
	if (!(!exists(tmpPath, fileErr) || fileErr))
		goto GOTO_END;

	// 検索 ..\..\..\ 
	tmpPath += "..\\..\\..\\" / filePath;
	if (!(!exists(tmpPath, fileErr) || fileErr))
		goto GOTO_END;

	ret = GT_E_NOT_FIND;
GOTO_END:
	if (ret == GT_S_OK)
	{
		if (is_regular_file(tmpPath))
		{
			*pOutPath = tmpPath.generic_string();
			return ret;
		}
	}
	return GT_E_NOT_FIND;


	return ret;
}
//-----------------------------------------------------------------------------------
//! @brief ファイル名を指定して、ファイルパスを取得する。UTF16版
//! @param [out] pOutPath   見つけたファイルパス
//! @param [in]  pFileName  ファイル名
//! @param [in]  pAddDir    ファイル名の後ろに追加する相対ディレクトリ名。省略可能
//! @return 見つけた場合はGT_S_OKを返す
//-----------------------------------------------------------------------------------
gt2HRESULT SimpleFindFilePathW(std::wstring* pOutPath, const wchar_t* pFileName, const wchar_t* pAddDir)
{
	std::string outPath, fileName, addDir;

	Convert_UTF16_To_SJIS(pFileName, &fileName);
	Convert_UTF16_To_SJIS(pAddDir, &addDir);
	gt2HRESULT ret = SimpleFindFilePathA(&outPath, fileName.c_str(), addDir.c_str());
	if (GT_SUCCEEDED(ret))
		Convert_SJIS_To_UTF16(outPath, pOutPath);
	return ret;
}
//-----------------------------------------------------------------------------------
//! @brief ファイル名を指定して、ファイルパスを取得する。ASCII版
//! @param [out] pOutPath   見つけたディレクトリパス
//! @param [in]  pDirPath   ディレクトリパス
//! @return 見つけた場合はGT_S_OKを返す
//-----------------------------------------------------------------------------------
gt2HRESULT SimpleFindDirPathA(std::string* pOutPath, const char* pDirPath)
{
	if (pDirPath == nullptr) return GT_E_INVALIDARG;
	// よくあるディレクトリー:
	//		%カレントディレクトリ%\ 
	//		%カレントディレクトリ%\..\ 
	//		%カレントディレクトリ%\..\..\  
	//		%カレントディレクトリ%\..\..\..\ 
	gt2HRESULT ret = GT_S_OK;
	error_code fileErr;
	path dirPath(pDirPath);
	path tmpPath(pDirPath);



	// 検索 .\	
	if (!(!exists(dirPath, fileErr) || fileErr))
		goto GOTO_END;

	// 検索 ..\	
	tmpPath = "..\\" / dirPath;
	if (!(!exists(tmpPath, fileErr) || fileErr))
		goto GOTO_END;

	// 検索 ..\..\ 
	tmpPath = "..\\..\\" / dirPath;
	if (!(!exists(tmpPath, fileErr) || fileErr))
		goto GOTO_END;

	// 検索 ..\..\..\ 
	tmpPath += "..\\..\\..\\" / dirPath;
	if (!(!exists(tmpPath, fileErr) || fileErr))
		goto GOTO_END;

	ret = GT_E_NOT_FIND;
GOTO_END:
	if (ret == GT_S_OK)
	{
		if (is_directory(tmpPath))
		{
			*pOutPath = tmpPath.generic_string();
			return ret;
		}
	}
	return GT_E_NOT_FIND;
}
gt2HRESULT SimpleFindDirPathW(std::wstring* pOutPath, const wchar_t* pDirPath)
{
	std::string outPath, dirPath;

	Convert_UTF16_To_SJIS(pDirPath, &dirPath);
	gt2HRESULT ret = SimpleFindDirPathA(&outPath, dirPath.c_str());
	if (GT_SUCCEEDED(ret))
		Convert_SJIS_To_UTF16(outPath, pOutPath);
	return ret;
}

