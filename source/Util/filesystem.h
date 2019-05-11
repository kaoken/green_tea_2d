/*! @file  filesystem.h
* @brief ファイル読み書きクラス
* @author kaoken
* @date 2019/05/03
*/
#pragma once

#include <Core/greenTea2D.h>
#include <filesystem>

//namespace mcFileSYS = experimental::filesystem;

#define FBUFFER_SIZE	2048

/*!
 * @brief ファイル読み書きクラス
 */
class GT2File
{
private:
	char			m_aCharBuffer[FBUFFER_SIZE];	//!< ファイルバッファ
	int64_t			m_fileSize;						//!< ファイルサイズ
	bool			m_isBigEndian;					//!< データの上位バイトからメモリに書く方式か？
	FILE*			m_pFile;						//!< ファイルポインタ

public:
	GT2File();
	~GT2File();

	static bool IsFileExits(const TChar * pFileName);
	static bool IsFileExitsA(const char * pFileName);
	static bool IsFileExitsW(const wchar_t * pFileName);
	static TString GetWorkingDirectory();
	static std::string GetWorkingDirectoryA();
	static std::wstring GetWorkingDirectoryW();

	int64_t GetSize() const;
	bool Close();
	bool IsBigEndian();
	bool IsLittleEndian();
	void SetBigEndian();
	void SetLittleEndian();

	bool Open(const TChar* pFileName, const TChar *pMode);
	bool OpenA(const char* pFileName, const char *pMode);
	bool OpenW(const wchar_t* pFileName, const wchar_t *pMode);
	int  SeekSet(int64_t offset, int origin);
	int64_t  Tell();
	bool IsEOF() const;

	// 読み込み
	size_t Read(void *pvBuffer, size_t size, size_t count);
	int Scanf(const TChar *format, ...);
	int ScanfA(const char *format, ...);
	int ScanfW(const wchar_t *format, ...);

	TChar* Gets(TChar *str, int n);
	char* GetsA(char *str, int n);
	wchar_t* GetsW(wchar_t *str, int n);
		
	int AllReadString(std::string &str);
	int ReadString(gtUINT length, TString &str);
	int ReadStringA(gtUINT length, std::string &str);
	int ReadStringW(gtUINT length, std::wstring &str);
	int ReadLine(TString &str);
	int ReadLineA(std::string &str);
	int ReadLineW(std::wstring &str);

	uint8_t		ReadU8();
	uint16_t	ReadU16();
	uint32_t	ReadU32();
	uint64_t	ReadU64();
	int8_t		ReadN8();
	int16_t		ReadN16();
	int32_t		ReadN32();
	int64_t		ReadN64();
	float		ReadF32();
	double		ReadF64();

	// 書き込み
	size_t Write(const void *pvBuffer, size_t size, size_t count);
	int Printf(const TChar *format, ...);
	int PrintfA(const char *format, ...);
	int PrintfW(const wchar_t *format, ...);

	int Puts(const TChar *str);
	int PutsA(const char *str);
	int PutsW(const wchar_t *str);

	int WriteString(gtUINT length, const TString &str);
	int WriteStringA(gtUINT length, const std::string &str);
	int WriteStringW(gtUINT length, const std::wstring &str);

	int WriteU8(uint8_t u);
	int WriteU16(uint16_t u);
	int WriteU32(uint32_t u);
	int WriteU64(uint64_t u);
	int WriteN8(int8_t n);
	int WriteN16(int16_t n);
	int WriteN32(int32_t n);
	int WriteN64(int64_t n);
	int WriteF32(float f);
	int WriteF64(double f);

};
typedef W_PTR<GT2File> CMCFileWP;	//!< GT2Fileスマートポインタ(weak)
typedef S_PTR<GT2File> CMCFileSP;	//!< GT2Fileスマートポインタ(shared)








#if defined(ANDROID) || defined(__ANDROID__)
	class CAPKFile
	{
	private:
		AAssetManager*	m_assetManager;
		AAsset*			m_pFile;
	public:
		CAPKFile(AAssetManager* assetManager) :
			m_assetManager(assetManager), m_pFile(nullptr){}
		~CAPKFile()
		{
			Close();
		}
		bool   Open(char const* path);
		void   Close();
		int    Getc();
		char*  Gets(char* s, int size);
		size_t Size();
		size_t Seek(long offset, int type);
		size_t Tell();
		size_t Read(void* ptr, size_t size, size_t nmemb);
		int    Eof();
	};
#endif


/*!
 * @brief ファイルの種類を取得
 */
enum struct GT2_FILE_TYPE
{
	UNKNOWN,	//!< 知らないタイプ
	NO_EXISTS,	//!< ファイルが存在しない
	// 画像ファイル
	JPG,		//!< JPEG画像ファイル
	GIF,		//!< GIF画像ファイル
	PNG,		//!< PNG画像ファイル
	DDS,		//!< DDS画像ファイル
	TGA,		//!< TGA画像ファイル
	TIFF,		//!< TIFF画像ファイル
	BMP,		//!< BMP画像ファイル
	ICO,		//!< アイコン画像ファイル
	WMP,		//!< Windows Media Photoファイル
	// 音声ファイル
	AIFF,		//!< AIFF音声ファイル
	WAV,		//!< WAV音声ファイル
	MP3,		//!< MP3音声ファイル
	OGG,		//!< OGG音声ファイル
	FLAC,		//!< FLAC音声ファイル
	MIDI,		//!< midi音声ファイル
	// 動画ファイル
	AVI,		//!< AVI動画ファイル
	MP4,		//!< MP4動画ファイル
	WMV,		//!< WMV動画ファイル
	MPEG2,		//!< MPEG2動画ファイル
	// 圧縮ファイル
	ZIP,		//!< ZIP圧縮ファイル
	RAR,		//!< RAR圧縮ファイル
	BZ2,		//!< BZ2圧縮ファイル
	LZH,		//!< LZH圧縮ファイル

};

GT2_FILE_TYPE GetFileTypeW(const wchar_t* pFilePath);
GT2_FILE_TYPE GetFileTypeA(const char* pFilePath);


gt2HRESULT SimpleFindFilePathA(std::string* pOutPath, const char* pFileName, const char* pAddDir = nullptr);
gt2HRESULT SimpleFindFilePathW(std::wstring* pOutPath, const wchar_t* pFileName, const wchar_t* pAddDir = nullptr);
gt2HRESULT SimpleFindDirPathA(std::string* pOutPath, const char* pDirPath);
gt2HRESULT SimpleFindDirPathW(std::wstring* pOutPath, const wchar_t* pDirPath);


#ifdef _UNICODE
#  define GetFileType(_path) GetFileTypeW(_path)
#  define SimpleFindFilePath(pOutPath, pFileName, pAddDir) SimpleFindFilePathW( pOutPath, pFileName, pAddDir)
#  define SimpleFindDirPath(pOutPath, pDirPath) SimpleFindDirPathW( pOutPath, pDirPath)
#else
#  define GetFileType(_path) GetFileTypeA(_path)
#  define SimpleFindFilePath(pOutPath, pFileName, pAddDir) SimpleFindFilePathA( pOutPath, pFileName, pAddDir)
#  define SimpleFindDirPath(pOutPath, pDirPath) SimpleFindDirPathA( pOutPath, pDirPath)
#endif


