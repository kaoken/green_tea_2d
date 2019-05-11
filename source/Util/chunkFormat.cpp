#include "chunkFormat.h"


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@
//@@ SaveState
//@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

/*!
* @brief コンストラクタ
*/
SaveState::SaveState()
{
	m_file;
	m_currentID = -1;
	m_lastState = LAST_NOTHING;
}
/*!
* @brief デストラクタ
*/
SaveState::~SaveState()
{
	this->End();
}
/*!
* @brief 初期設定をする
* @param [in] fileName ファイル名
* @param [in] hederMagicNo ヘッダー構造体内のmagicNoへ入力する
* @attention Start()メソッドを呼び出す前に必ず呼び出す。
* @see Start()
* @return なし
*/
void SaveState::InitSetting(const char *fileName, int32_t hederMagicNo)
{
	m_fileName = fileName;
	m_header.version = hederMagicNo;
	m_PType = FF_OPERATION_FILE;
}
/*!
* @brief 初期設定をする
* @param [in] spBuffer バッファー
* @param [in] hederMagicNo ヘッダー構造体内のmagicNoへ入力する
* @attention Start()メソッドを呼び出す前に必ず呼び出す。
* @see Start()
* @return なし
*/
void SaveState::InitSetting(GT2UtilBufferSP &spBuffer, int32_t hederMagicNo)
{
	m_spUtilBuffer = spBuffer;
	m_header.version = hederMagicNo;
	m_PType = FF_OPERATION_BUFFER;
}

/*!
* @brief 書き出しを開始する。
* @return 何もなければ1を返す
*/
int SaveState::Start()
{
	ChankOffset ckOffset;
	this->End();

	// 深さを０にする
	m_currentDepth = 0;
	m_lastState = LAST_START;

	if (m_PType == FF_OPERATION_FILE)
	{
		if ( !m_file.OpenA(m_fileName.c_str(), "wb") ){
			return 0;
		}
	}
	// ヘッダの書き込み
	m_header.size += ckOffset.chank.GetStructSize();
	m_header.Write(m_file);
	// 初回チャンク設定＆書き込み
	ckOffset.offset = m_file.Tell();
	ckOffset.chank.id = FF_CUNK_ID;
	ckOffset.chank.structNum = 0;
	ckOffset.chank.size = 0;
	if (m_PType == FF_OPERATION_FILE)
		ckOffset.chank.Write(m_file);
	else
		ckOffset.chank.Write(m_spUtilBuffer);

	m_vChankBlockStack.push_back(ckOffset);

	return 1;
}
/*!
* @brief 指定idのチャンクデータを書き出し、ブロックを開始する。
* @param [in] id チャンクid
* @return 何もなければ1を返す
*/
int SaveState::BlockStart(int64_t id, int32_t version)
{
	ChankOffset ckOffset;
	CHANK_FLG cFlg;


	//=====================================
	// 最終ステートフラグのチェック
	//=====================================
	if (m_lastState == LAST_WRITE){
		//---------------------------
		// 前回が書き込みモードなら
		//---------------------------
		ChankOffset ckWrite;
		// チャンクフラグを書く
		this->SizeUpdate(sizeof(CHANK_FLG));
		cFlg = CHANK_FLG_NEST;
		m_file.WriteN8(cFlg);
		// ブロックチャンクを書き込む
		this->SizeUpdate(ckWrite.chank.GetStructSize());
		ckWrite.chank.id = FF_CUNK_ID;
		ckWrite.chank.structNum = 0;
		ckWrite.chank.size = 0;
		if (m_PType == FF_OPERATION_FILE)
		{
			ckWrite.offset = m_file.Tell();
			m_vChankBlockStack.push_back(ckWrite);
			ckWrite.chank.Write(m_file);
		}
		else
		{
			ckWrite.offset = m_spUtilBuffer->Seek();
			m_vChankBlockStack.push_back(ckWrite);
			ckWrite.chank.Write(m_spUtilBuffer);
		}
	}

	// ブロック内のチャンク数カウント＋１
	++m_vChankBlockStack.back().chank.structNum;

	// idが変わった
	m_currentID = id;
	//
	ckOffset.chank.id = id;
	ckOffset.chank.structNum = 0;
	ckOffset.chank.size = 0;
	// 指定idのチャックデータを書き込む
	ckOffset.offset = m_file.Tell();
	ckOffset.chank.Write(m_file);
	// サイズの加算
	this->SizeUpdate(ckOffset.chank.GetStructSize());


	// 新たにスタックにプッシュする
	// 層を+1する
	m_vChankStack.push_back(ckOffset);
	++m_currentDepth;

	// フラグ
	m_lastState = LAST_BLOCK_START;

	return 1;
}
/*!
* @brief m_currentID(現在のid）の値から指定した構造体のデータを書き込む。
* @param [in] pFFS BasicBodyポインタ
* @return 何もなければ1を返す
*/
int SaveState::Write(const BasicBody* pFFS)
{
	auto itr = m_vChankStack.end();
	CHANK_FLG ckFlg;

	if (m_vChankStack.begin() != m_vChankStack.end())
		itr = --m_vChankStack.end();
	else
		return -1;

	//=====================================
	// 最終ステートフラグのチェック
	//=====================================
	if (itr->chank.structNum > 0 && m_lastState == LAST_WRITE){
		// フォーマット数が0より大きい場合
		// チャンクフラグ０を書き込む
		ckFlg = CHANK_FLG_NOTHING;
		if (m_PType == FF_OPERATION_FILE)
			m_file.WriteN8(ckFlg);
		else
			m_spUtilBuffer->WriteN8(ckFlg);
		// サイズの加算
		this->SizeUpdate(sizeof(CHANK_FLG));
	}
	else if (m_lastState == LAST_BLOCK_END){
		// 前回ブロックを閉じた
		// ブロックチャンクスタックをポップ
		this->BlockChankStackPop();
	}
	itr->chank.structNum++;


	// サイズの加算
	this->SizeUpdate(pFFS->GetStructSize());
	// 書き込み
	if (m_PType == FF_OPERATION_FILE)
		pFFS->Write(m_file);
	else
		pFFS->Write(m_spUtilBuffer);


	// フラグ
	m_lastState = LAST_WRITE;
	return 1;
}
/*!
* @brief 現在のチャンクをポップ。
* @return 何もなければ1を返す
*/
int SaveState::BlockEnd()
{
	CHANK_FLG cFlg;
	int64_t currentOffset;

	//=====================================
	// 最終ステートフラグのチェック
	//=====================================
	if (m_lastState == LAST_BLOCK_END){
		// 連続で閉じたことになるので取り出し
		this->BlockChankStackPop();
	}
	else if (m_lastState == LAST_WRITE){
		// 前回が書き込みモードなら
		// チャンクフラグを書く
		this->SizeUpdate(sizeof(CHANK_FLG));
		cFlg = CHANK_FLG_NOTHING;
		if (m_PType == FF_OPERATION_FILE)
			m_file.WriteN8(cFlg);
		else
			m_spUtilBuffer->WriteByte((byte)cFlg);
	}

	if (m_PType == FF_OPERATION_FILE)
	{
		// 現在のオフセット値を取得
		// スタック取り出し前のオフセット値に移動
		currentOffset = m_file.Tell();
		m_file.SeekSet(m_vChankStack.back().offset, SEEK_SET);
		// 指定場所へチャンクを更新
		// そして元のオフセット値に戻す
		m_vChankStack.back().chank.Write(m_file);
		m_file.SeekSet(currentOffset, SEEK_SET);
	}
	else
	{
		// 現在のオフセット値を取得
		// スタック取り出し前のオフセット値に移動
		currentOffset = m_spUtilBuffer->Seek();
		m_spUtilBuffer->SeekSet(m_vChankStack.back().offset);
		// 指定場所へチャンクを更新
		// そして元のオフセット値に戻す
		m_vChankStack.back().chank.Write(m_spUtilBuffer);
		m_spUtilBuffer->SeekSet(currentOffset);
	}
	// スタックから取り出し
	m_vChankStack.pop_back();

	// 層を－１する
	--m_currentDepth;
	// idを元に戻す
	if (!m_vChankStack.empty())
		m_currentID = m_vChankStack.back().chank.id;
	else
		m_currentID = -1;

	// フラグ
	m_lastState = LAST_BLOCK_END;

	return 1;
}
/*!
* @brief 書き出しを終了する。
* @return 何もなければ1を返す
*/
int SaveState::End()
{
	if ( m_PType == FF_OPERATION_FILE){
		// ヘッダ部分にデータサイズを再書き込みする
		m_file.SeekSet(0, SEEK_SET);
		m_header.Write(m_file);
		// 初回チャンク
		assert(m_vChankBlockStack.size() == 1);
		this->BlockChankStackPop();

		m_file.Close();
	}
	else
	{
		// ヘッダ部分にデータサイズを再書き込みする
		m_spUtilBuffer->SeekSet(0);
		m_header.Write(m_spUtilBuffer);
		// 初回チャンク
		assert(m_vChankBlockStack.size() == 1);
		this->BlockChankStackPop();

		m_spUtilBuffer.reset();
	}
	return 1;
}
/*!
* @brief ブロックチャンクスタックをポップし、指定されたオフセット値に移動しファイルを
*  書き換える。そして、ファイル位置を元の位置に戻す。
* @return 何もなければ1を返す
*/
int SaveState::BlockChankStackPop()
{
	int64_t currentOffset;
	if (m_PType == FF_OPERATION_FILE)
	{
		// 現在のオフセット値を取得、スタック取り出し前のオフセット値に移動
		currentOffset = m_file.Tell();
		m_file.SeekSet(m_vChankBlockStack.back().offset, SEEK_SET);
		// 指定場所へチャンクを更新、そして元のオフセット値に戻す
		m_vChankBlockStack.back().chank.Write(m_file);
		m_file.SeekSet(currentOffset, SEEK_SET);
	}
	else
	{
		// 現在のオフセット値を取得、スタック取り出し前のオフセット値に移動
		currentOffset = m_spUtilBuffer->Seek();
		m_spUtilBuffer->SeekSet(m_vChankBlockStack.back().offset);
		// 指定場所へチャンクを更新、そして元のオフセット値に戻す
		m_vChankBlockStack.back().chank.Write(m_spUtilBuffer);
		m_spUtilBuffer->SeekSet(currentOffset);
	}
	// ブロックスタックからポップ
	m_vChankBlockStack.pop_back();
	return 1;
}
/*!
* @brief  サイズの更新処理
* @param [in] size サイズ（バイト単位）
* @return 何もなければ1を返す
*/
int SaveState::SizeUpdate(int size)
{
	// ヘッダサイズの更新
	m_header.size += size;

	// ブロックチャンク
	for (auto &val : m_vChankBlockStack)
		val.chank.size += size;

	// スタック内のサイズをすべて加算する m_vChankStack
	for (auto &val : m_vChankStack)
		val.chank.size += size;

	return 1;
}





















//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@
//@@ LoadChank
//@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//-----------------------------------------------------------------------------------
//! @brief コンストラクタ
//-----------------------------------------------------------------------------------
/*!
* @brief  コンストラクタ
* @param [in] rFile GT2Fileポインタ
* @param [in] pChank Chunkポインタ
* @param [in] offset オフセット値
*/
LoadChank::LoadChank(GT2File *pFile, const Chunk *pChank, int64_t offset)
{
	m_PType = FF_OPERATION_FILE;
	m_refCnt = 1;
	m_pFile = pFile;
	m_chank = *pChank;
	m_offset = offset;
	m_nextOffset = offset;
	m_chankCnt = 0;
}
/*!
* @brief  コンストラクタ
* @param [in] spBuffer GT2UtilBufferスマートポインタ(share)
* @param [in] pChank Chunkポインタ
* @param [in] offset オフセット値
*/
LoadChank::LoadChank(GT2UtilBufferSP &spBuffer, const Chunk *pChank, int64_t offset)
{
	m_PType = FF_OPERATION_BUFFER;
	m_refCnt = 1;
	m_pFile = nullptr;
	m_spUtilBuffer = spBuffer;
	m_chank = *pChank;
	m_offset = offset;
	m_nextOffset = offset;
	m_chankCnt = 0;
}
/*!
* @brief  デストラクタ
*/
LoadChank::~LoadChank()
{

}
/*!
* @brief 解放処理
* @return 参照数
*/
int32_t LoadChank::Release()
{
	if (--m_refCnt <= 0){
		delete this;
		return 0;
	}
	return m_refCnt;
}
/*!
* @brief ブロックチャンクを取得する
* @param [out] pOut 値を入れるチャンク構造体ポインタ
* @return 何もなければ1を返す
*/
void LoadChank::GetBlockChank(Chunk* pOut)
{
	*pOut = m_chank;
}
/*!
* @brief 次のチャンクデータを探し出す。ppDataへLoadDataのポインタを渡す。
*  使い終わったら必ずRelease関数を呼び出す。
* @param [out] pChank 値を入れるチャンク構造体ポインタ
* @param [out] ppData LoadDataポインタポインタ。失敗した場合はnullptrを返す。
* @return 何もなければ1を返す
*/
int LoadChank::FindChank(Chunk* pChank, LoadData** ppData)
{
	Chunk chank;

	if (m_chankCnt <  m_chank.structNum){
		if (m_PType == FF_OPERATION_FILE)
		{
			m_pFile->SeekSet(m_nextOffset, SEEK_SET);
			chank.Read(*m_pFile);
			m_nextOffset += chank.size + chank.GetStructSize();
			*ppData = new LoadData(m_pFile, &chank, m_pFile->Tell());
		}
		else
		{
			m_spUtilBuffer->SeekSet(m_nextOffset);
			chank.Read(m_spUtilBuffer);
			m_nextOffset += chank.size + chank.GetStructSize();
			*ppData = new LoadData(m_spUtilBuffer, &chank, m_spUtilBuffer->Seek());
		}
		if (*ppData == nullptr){
			*ppData = nullptr;
			return -1;
		}
		*pChank = chank;
		++m_chankCnt;
	}
	else{
		*ppData = nullptr;
		return 0;
	}
	return 1;
}





















//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@
//@@ LoadData
//@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
/*!
* @brief コンストラクタ
* @param [in] pFile GT2Fileポインタ
* @param [in] pChank Chunkポインタ
* @param [in] offset 現在のファイルのオフセット値
*/
LoadData::LoadData(GT2File *pFile, const Chunk *pChank, int64_t offset)
{
	m_PType = FF_OPERATION_FILE;
	m_refCnt = 1;
	m_pFile = pFile;
	m_chank = *pChank;
	m_offset = offset;
	m_nextOffset = offset;
	m_count = 0;
}
/*!
* @brief コンストラクタ
* @param [in] spBuffer GT2UtilBufferスマートポインタ(shared)
* @param [in] pChank Chunkポインタ
* @param [in] offset 現在のバッファのオフセット値
*/
LoadData::LoadData(GT2UtilBufferSP &spBuffer, const Chunk *pChank, int64_t offset)
{
	m_PType = FF_OPERATION_BUFFER;
	m_refCnt = 1;
	m_pFile = nullptr;
	m_spUtilBuffer = spBuffer;
	m_chank = *pChank;
	m_offset = offset;
	m_nextOffset = offset;
	m_count = 0;
}
/*!
* @brief デストラクタ
*/
LoadData::~LoadData()
{

}
/*!
* @brief 解放処理
* @return 参照数
*/
int32_t LoadData::Release()
{
	if (--m_refCnt <= 0){
		delete this;
		return 0;
	}
	return m_refCnt;
}
/*!
* @brief チャンクを取得する
* @param [out] pOut 値を入れるチャンク構造体ポインタ
* @return 何もなければ1を返す
*/
void LoadData::GetChank(Chunk *pOut){
	*pOut = m_chank;
}
/*!
* @brief 次のデータを探し出す。ppOutへLoadChankのポインタを渡す。
*  使い終わったら必ずRelease関数を呼び出す。
* @param [in,out] pFFS    BasicBodyで派生された構造体ポインタを渡し、値を取得する。
* @param [out]    ppChank LoadChankポインタポインタ。失敗した場合はnullptrを返す。
* @return 何もなければ1を返す
*/
int LoadData::FindData(BasicBody* pFFS, LoadChank** ppChank)
{
	Chunk chank;
	CHANK_FLG flg;

	if (m_count < m_chank.structNum){
		++m_count;
		if (m_PType == FF_OPERATION_FILE)
		{
			m_pFile->SeekSet(m_nextOffset, SEEK_SET);
			pFFS->Read(*m_pFile);
			flg = m_pFile->ReadN8();
		}
		else
		{
			m_spUtilBuffer->SeekSet(m_nextOffset);
			pFFS->Read(m_spUtilBuffer);
			m_spUtilBuffer->ReadByte((byte*)&flg);
		}
		m_nextOffset += pFFS->GetStructSize() + 1;

		if (flg == CHANK_FLG_NEST){
			// 入れ子がある
			if (m_PType == FF_OPERATION_FILE)
			{
				chank.Read(*m_pFile);
				m_nextOffset += chank.size + chank.GetStructSize();
				*ppChank = new LoadChank(m_pFile, &chank, m_pFile->Tell());
			}
			else
			{
				chank.Read(m_spUtilBuffer);
				m_nextOffset += chank.size + chank.GetStructSize();
				*ppChank = new LoadChank(m_spUtilBuffer, &chank, m_spUtilBuffer->Seek());
			}
			if (*ppChank == nullptr){
				*ppChank = nullptr;
				return -1;
			}
			return 2;
		}
		else{
			*ppChank = nullptr;
		}

	}
	else{
		*ppChank = nullptr;
		return 0;
	}
	return 1;
}





















//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@
//@@ LoadState
//@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

/*!
* @brief コンストラクタ
*/
LoadState::LoadState()
{
}
/*!
* @brief デストラクタ
*/
LoadState::~LoadState()
{
	this->End();
}
/*!
* @brief 作成するファイル名を設定する。
* @param [in] fileName   ファイル名
* @return なし
*/
void LoadState::InitSetting(const char *fileName)
{
	m_fileName = fileName;
	m_PType = FF_OPERATION_FILE;
}
/*!
* @brief 作成するGT2UtilBuffer。
* @param [in] spBuffer   GT2UtilBufferのスマートポインタ(shared)
* @return なし
*/
void LoadState::InitSetting(GT2UtilBufferSP &spBuffer)
{
	assert(spBuffer);
	m_PType = FF_OPERATION_BUFFER;
	m_spUtilBuffer = spBuffer;
}

/*!
* @brief 読み込みを開始する。ppOutへLoadChankのポインタを渡す。使い終わったら必ずRelease関数を呼び出す。
* @param [in] spBuffer   GT2UtilBufferのスマートポインタ(shared)
* @return なし
*/
int LoadState::Start(LoadChank **ppOut)
{
	Chunk chank;
	this->End();

	if (m_PType == FF_OPERATION_FILE)
	{
		if (!(m_file.OpenA(m_fileName.c_str(), "rb")))
			return 0;
		// ヘッダの読み込み
		m_header.Read(m_file);
		// 初回チャンク設定読み込み
		chank.Read(m_file);
		*ppOut = new LoadChank(&m_file, &chank, m_file.Tell());
	}
	else
	{
		// ヘッダの読み込み
		m_header.Read(m_spUtilBuffer);
		// 初回チャンク設定読み込み
		chank.Read(m_spUtilBuffer);
		*ppOut = new LoadChank(m_spUtilBuffer, &chank, m_spUtilBuffer->Seek());
	}
	return 1;
}

/*!
* @brief 書き出しを終了する。
* @return 何もなければ1を返す
*/
int LoadState::End()
{
	if (m_PType == FF_OPERATION_FILE)
	{
		m_file.Close();
	}
	else
	{
		m_spUtilBuffer.reset();
	}
	return 1;
}

