/*! 
 * @file  chunk.h
 * @brief 簡単なIFF（Interchange File Format）
 * @author kaoken
 * @version 1.0
 * @date 2014/01/24 作成開始
 */

#pragma once

#include <Core/greenTea2D.h>
#include <Util/filesystem.h>
#include <Util/UtilBuffer.h>


//------------------------------------------
// 宣言を進めておく
//------------------------------------------
class LoadState;
class LoadChank;
class LoadData;


//------------------------------------------
// マクロ
//------------------------------------------
#define FF_SFT64(x,n) ((uint64_t)(x)<<n)
#define FF_SFT32(x,n) ((uint32_t)(x)<<n)
#define FFID4_(a,b,c,d)	 (FF_SFT32(d,24)|FF_SFT32(c,16)|FF_SFT32(b,8)|(uint32_t)(a))
#define FFID8_(a,b,c,d,e,f,g,h)	 (FF_SFT64(h,56)|FF_SFT64(g,48)|FF_SFT64(f,40)|FF_SFT64(e,32)|FF_SFT64(d,24)|FF_SFT64(c,16)|FF_SFT64(b,8)|(uint64_t)(a))
#define FF_SHIFT(n) (1<<n)


/*!
	* @brief F とつく構造体すべてに派生して使用する。
	*/
struct BasicBody
{
	/*!
		* @brief 構造体を識別するためのIDを取得する
		* @return 構造体のID
		*/
	virtual inline uint64_t GetID() const = 0;
	/*!
		* @brief 構造体のサイズを取得する
		* @return 構造体のサイズを返す
		*/
	virtual inline int GetStructSize() const = 0;
	/*!
		* @brief ファイルに書き込む
		* @param [in] rFile GT2Fileクラス
		* @return 書き込み成功時、1を返す。
		*/
	virtual inline int Write(GT2File &rFile) const = 0;
	/*!
		* @brief バッファに書き込む
		* @param [in] spFile GT2UtilBufferSPスマートポインタ
		* @return GT2UtilBufferの書き込み位置を返す。
		*/
	virtual inline int Write(GT2UtilBufferSP &spFile) const = 0;
	/*!
		* @brief ファイルを読み込む
		* @param [in] rFile GT2Fileクラス
		* @return 読み込み成功時、1を返す。
		*/
	virtual inline int Read(GT2File &rFile) = 0;
	/*!
		* @brief バッファから読み込む
		* @param [in] rFile GT2Fileクラス
		* @return GT2UtilBufferの読み込み位置を返す。
		*/
	virtual inline int Read(GT2UtilBufferSP &spFile) = 0;
};

// fileType で使用する
#define FF_HEADER_FTYPE_BIN	FFID4_('b','i','n','\0')	// バイナリファイルタイプ
/*!
* @brief ファイルのヘッダに必ずセットする
*/
struct Header : public BasicBody
{
	uint32_t	version;		//!< バージョン
	uint32_t	fileType;		//!< ファイルのタイプ、バイナリまたはテキスト
	int64_t		size;			//!< ヘッダデータより先の全データ領域を表す。
	Header()
	{
		version = 0;
		fileType = FF_HEADER_FTYPE_BIN;
		size = 0;
	}
public:
	/*!
		* @brief 代入演算子 =
		* @param [in] r Header構造体
		* @return 自信のポインタ
		*/
	Header& operator = (const Header& r){
		version = r.version;
		fileType = r.fileType;
		size = r.size;

		return *this;
	}
		
	/**
		* @name BasicBodyより派生メソッド
		*/
	//@{
	virtual inline uint64_t GetID() const override { return FFID8_('H', 'e', 'a', 'd', 'e', 'r','\0', '\0'); }
	virtual inline int GetStructSize() const override { return 16; }
	virtual inline int Write(GT2File &rFile) const override {
		rFile.WriteN32(version);
		rFile.WriteN32(fileType);
		rFile.WriteN64(size);
		return 1;
	}
	virtual inline int Write(GT2UtilBufferSP &spFile) const override {
		spFile->WriteN32(version);
		spFile->WriteN32(fileType);
		spFile->WriteN64(size);
		return spFile->Seek();
	}
	virtual inline int Read(GT2File &rFile) override {
		version = rFile.ReadU32();
		fileType = rFile.ReadU32();
		size = rFile.ReadN64();
		return 1;
	}
	virtual inline int Read(GT2UtilBufferSP &spFile) override {
		spFile->ReadU32(&version);
		spFile->ReadU32(&fileType);
		spFile->ReadN64(&size);
		return spFile->Seek();
	}
	//@}
};


#define FF_CUNK_ID FFID8_('C', 'h', 'u', 'n', 'k', '*', '*', '*');
/*!
	* @brief チャンク構造体
	*/
struct Chunk : public BasicBody
{
	uint64_t	id;				//!< チャンクid(文字で8文字分)
	int32_t		structNum;		//!< 構造体(フォーマット)数
	int64_t		size;			//!< サイズ
public:
	Chunk& operator = (const Chunk& r){
		id = r.id;
		structNum = r.structNum;
		size = r.size;
		return *this;
	}

	/**
	* @name BasicBodyより派生メソッド
	*/
	//@{
	virtual inline uint64_t GetID() const override { return FF_CUNK_ID; }
	virtual inline int GetStructSize() const override { return 20; }
	virtual inline int Write(GT2File &rFile) const override {
		// パディング&派生により、個々に書き込む
		rFile.WriteN64(id);
		rFile.WriteN32(structNum);
		rFile.WriteN64(size);
		return 1;
	}
	virtual inline int Write(GT2UtilBufferSP &spFile) const override {
		// パディング&派生により、個々に書き込む
		spFile->WriteN64(id);
		spFile->WriteN32(structNum);
		spFile->WriteN64(size);
		return spFile->Seek();
	}
	virtual inline int Read(GT2File &rFile) override {
		// パディング&派生により、個々に読み込む
		id = rFile.ReadU64();
		structNum = rFile.ReadN32();
		size = rFile.ReadN64();
		return 1;
	}
	virtual inline int Read(GT2UtilBufferSP &spFile) override {
		// パディング&派生により、個々に読み込む
		spFile->ReadU64(&id);
		spFile->ReadN32(&structNum);
		spFile->ReadN64(&size);
		return spFile->Seek();
	}
	//@}
};


/*!
* @brief ブロックの名前付けをする構造体
*/
struct BlockIndent
{
	int64_t		id;		//!< チャンクid
	const char	*sz;	//!< 名前
};

typedef char CHANK_FLG;		//!< チャンクフラグ型
#define CHANK_FLG_NOTHING	0	//!< 特になし @see CHANK_FLG
#define CHANK_FLG_NEST		1	//!< チャンクの入れ子 @see CHANK_FLG
#define CHANK_FLG_CHANK		2	//!< 同じ層に入れ子 @see CHANK_FLG


/*!
* @brief ブロックの名前付けをする構造体
*/
struct ChankOffset
{
	Chunk	chank;		//!< チャンクデータ
	int64_t	offset;		//!< オフセット
};
//!< 各チャンクのオフセット値を格納するとき使用する型 @see ChankOffset
typedef gtVector<ChankOffset>	VChankOffset;

/*!
* @brief 処理タイプ
*/
enum FF_OPERATION_TYPE
{
	FF_OPERATION_FILE,	//!< FF_構造体関連で、ファイル処理
	FF_OPERATION_BUFFER	//!< FF_構造体関連で、バッファ処理
};


/*!
* @brief 汎用フォーマットをファイルを保存するときに使う
*/
class SaveState
{
protected:
	//! @name m_lastState で使用するフラグ 
	//! @see SaveState::m_lastState
	//@{
	const static int LAST_NOTHING = 0;		//!< 特になし @see SaveState::m_lastState
	const static int LAST_START = 1;			//!< 開始された @see SaveState::m_lastState
	const static int LAST_BLOCK_START = 2;	//!< ブロックが開始された @see SaveState::m_lastState
	const static int LAST_BLOCK_END = 3;		//!< ブロックが終了した @see SaveState::m_lastState
	const static int LAST_WRITE = 4;			//!< データを書き込んだ @see SaveState::m_lastState
	const static int LAST_END = 5;			//!< 終了 @see SaveState::m_lastState
	//@}
protected:
	FF_OPERATION_TYPE	m_PType;
	int64_t				m_currentID;			//!< 現在のid
	int					m_lastState;			//!< 最終状態

	VChankOffset		m_vChankStack;			//!< チャンクスタック
	VChankOffset		m_vChankBlockStack;		//!< チャンクブロックスタック
	std::string			m_fileName;				//!< ファイル名
	GT2File				m_file;					//!< ファイル構造体ポインタ
	GT2UtilBufferSP		m_spUtilBuffer;			//!< バッファー
	Header				m_header;				//!< ヘッダー構造体
	int				m_currentDepth;			//!< 現在の深さ
public:
	/*!
	* @brief ヘッダデータ取得
	* @param [out] pHeader Headerポインタ
	* @return なし
	*/
	inline void GetHeader(Header* pHeader)
	{
		(*pHeader) = m_header;
	}
public:
	SaveState();
	~SaveState();

	inline int GetDepth(){ return m_currentDepth - 1; }
	void InitSetting(const char *fileName, int32_t hederMagicNo);
	void InitSetting(GT2UtilBufferSP &spBuffer, int32_t hederMagicNo);
	int Start();
	int BlockStart(int64_t id, int32_t version);
	int Write(const BasicBody* pFFS);
	int BlockEnd();
	int End();

protected:
	int BlockChankStackPop();
	int SizeUpdate(int size);
};

/*!
* @brief チャンクロードクラス
*/
class LoadChank
{
protected:
	FF_OPERATION_TYPE	m_PType;		//!<  処理タイプ
	GT2File*			m_pFile;		//!<  ファイル構造体ポインタ @note 参照のみ
	GT2UtilBufferSP	m_spUtilBuffer;		//!<  バッファー
	Chunk		m_chank;			//!<  チャンク
	int64_t			m_offset;			//!<  次のファイルのオフセット値
	int64_t			m_nextOffset;		//!<  次のファイルのオフセット値
	int32_t			m_chankCnt;			//!<  検索した回数
	int32_t			m_refCnt;			//!<  参照カウント
public:
	LoadChank(GT2File *pFile, const Chunk *pChank, int64_t offset);
	LoadChank(GT2UtilBufferSP &spBuffer, const Chunk *pChank, int64_t offset);
	~LoadChank();
	int32_t Release();
	void GetBlockChank(Chunk* pOut);
	int FindChank(Chunk* pChank, LoadData** ppData);
};

/*!
* @brief チャンクのid毎に決められたデータを読み込む
*/
class LoadData
{
public:
	LoadData(GT2File *pFile, const Chunk *pChank, int64_t offset);
	LoadData(GT2UtilBufferSP &spBuffer, const Chunk *pChank, int64_t offset);
	~LoadData();
	int32_t Release();
	int FindData(BasicBody* pFFS, LoadChank** ppChank);
	void GetChank(Chunk *pOut);
protected:
	FF_OPERATION_TYPE	m_PType;		//!< 処理タイプ
	GT2File*		m_pFile;			//!< ファイル構造体ポインタ @note 参照のみ
	GT2UtilBufferSP	m_spUtilBuffer;		//!< バッファー
	int64_t			m_nextOffset;		//!< 次のファイルのオフセット値
	int64_t			m_offset;			//!< オフセット値
	int32_t			m_count;			//!< データカウント数
	Chunk		m_chank;			//!< チャンク構造体
	int32_t			m_refCnt;			//!< 参照カウント
};

/*!
* @brief 状態の取得クラス
*/
class LoadState
{
	FF_OPERATION_TYPE	m_PType;		//!< 処理タイプ
	std::string			m_fileName;		//!< ファイル名
	GT2File				m_file;			//!< ファイルクラス
	GT2UtilBufferSP		m_spUtilBuffer;	//!< バッファー
	Header				m_header;		//!< ヘッダー構造体
	int				m_currentDepth;	//!< 現在の深さ
public:
	LoadState();
	~LoadState();

	void InitSetting(const char *fileName);
	void InitSetting(GT2UtilBufferSP &spBuffer);
	int Start(LoadChank **ppOut);
	int End();
	/*!
	* @brief ヘッダデータ取得
	* @param [out] pHeader Headerポインタ
	* @return なし
	*/
	inline void GetHeader(Header* pHeader)
	{
		(*pHeader) = m_header;
	}
};