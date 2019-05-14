#include "chunkFormat.h"


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@
//@@ SaveState
//@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

/*!
* @brief �R���X�g���N�^
*/
SaveState::SaveState()
{
	m_file;
	m_currentID = -1;
	m_lastState = LAST_NOTHING;
}
/*!
* @brief �f�X�g���N�^
*/
SaveState::~SaveState()
{
	this->End();
}
/*!
* @brief �����ݒ������
* @param [in] fileName �t�@�C����
* @param [in] hederMagicNo �w�b�_�[�\���̓���magicNo�֓��͂���
* @attention Start()���\�b�h���Ăяo���O�ɕK���Ăяo���B
* @see Start()
* @return �Ȃ�
*/
void SaveState::InitSetting(const char *fileName, int32_t hederMagicNo)
{
	m_fileName = fileName;
	m_header.version = hederMagicNo;
	m_PType = FF_OPERATION_FILE;
}
/*!
* @brief �����ݒ������
* @param [in] spBuffer �o�b�t�@�[
* @param [in] hederMagicNo �w�b�_�[�\���̓���magicNo�֓��͂���
* @attention Start()���\�b�h���Ăяo���O�ɕK���Ăяo���B
* @see Start()
* @return �Ȃ�
*/
void SaveState::InitSetting(GT2UtilBufferSP &spBuffer, int32_t hederMagicNo)
{
	m_spUtilBuffer = spBuffer;
	m_header.version = hederMagicNo;
	m_PType = FF_OPERATION_BUFFER;
}

/*!
* @brief �����o�����J�n����B
* @return �����Ȃ����1��Ԃ�
*/
int SaveState::Start()
{
	ChankOffset ckOffset;
	this->End();

	// �[�����O�ɂ���
	m_currentDepth = 0;
	m_lastState = LAST_START;

	if (m_PType == FF_OPERATION_FILE)
	{
		if ( !m_file.OpenA(m_fileName.c_str(), "wb") ){
			return 0;
		}
	}
	// �w�b�_�̏�������
	m_header.size += ckOffset.chank.GetStructSize();
	m_header.Write(m_file);
	// ����`�����N�ݒ聕��������
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
* @brief �w��id�̃`�����N�f�[�^�������o���A�u���b�N���J�n����B
* @param [in] id �`�����Nid
* @return �����Ȃ����1��Ԃ�
*/
int SaveState::BlockStart(int64_t id, int32_t version)
{
	ChankOffset ckOffset;
	CHANK_FLG cFlg;


	//=====================================
	// �ŏI�X�e�[�g�t���O�̃`�F�b�N
	//=====================================
	if (m_lastState == LAST_WRITE){
		//---------------------------
		// �O�񂪏������݃��[�h�Ȃ�
		//---------------------------
		ChankOffset ckWrite;
		// �`�����N�t���O������
		this->SizeUpdate(sizeof(CHANK_FLG));
		cFlg = CHANK_FLG_NEST;
		m_file.WriteN8(cFlg);
		// �u���b�N�`�����N����������
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

	// �u���b�N���̃`�����N���J�E���g�{�P
	++m_vChankBlockStack.back().chank.structNum;

	// id���ς����
	m_currentID = id;
	//
	ckOffset.chank.id = id;
	ckOffset.chank.structNum = 0;
	ckOffset.chank.size = 0;
	// �w��id�̃`���b�N�f�[�^����������
	ckOffset.offset = m_file.Tell();
	ckOffset.chank.Write(m_file);
	// �T�C�Y�̉��Z
	this->SizeUpdate(ckOffset.chank.GetStructSize());


	// �V���ɃX�^�b�N�Ƀv�b�V������
	// �w��+1����
	m_vChankStack.push_back(ckOffset);
	++m_currentDepth;

	// �t���O
	m_lastState = LAST_BLOCK_START;

	return 1;
}
/*!
* @brief m_currentID(���݂�id�j�̒l����w�肵���\���̂̃f�[�^���������ށB
* @param [in] pFFS BasicBody�|�C���^
* @return �����Ȃ����1��Ԃ�
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
	// �ŏI�X�e�[�g�t���O�̃`�F�b�N
	//=====================================
	if (itr->chank.structNum > 0 && m_lastState == LAST_WRITE){
		// �t�H�[�}�b�g����0���傫���ꍇ
		// �`�����N�t���O�O����������
		ckFlg = CHANK_FLG_NOTHING;
		if (m_PType == FF_OPERATION_FILE)
			m_file.WriteN8(ckFlg);
		else
			m_spUtilBuffer->WriteN8(ckFlg);
		// �T�C�Y�̉��Z
		this->SizeUpdate(sizeof(CHANK_FLG));
	}
	else if (m_lastState == LAST_BLOCK_END){
		// �O��u���b�N�����
		// �u���b�N�`�����N�X�^�b�N���|�b�v
		this->BlockChankStackPop();
	}
	itr->chank.structNum++;


	// �T�C�Y�̉��Z
	this->SizeUpdate(pFFS->GetStructSize());
	// ��������
	if (m_PType == FF_OPERATION_FILE)
		pFFS->Write(m_file);
	else
		pFFS->Write(m_spUtilBuffer);


	// �t���O
	m_lastState = LAST_WRITE;
	return 1;
}
/*!
* @brief ���݂̃`�����N���|�b�v�B
* @return �����Ȃ����1��Ԃ�
*/
int SaveState::BlockEnd()
{
	CHANK_FLG cFlg;
	int64_t currentOffset;

	//=====================================
	// �ŏI�X�e�[�g�t���O�̃`�F�b�N
	//=====================================
	if (m_lastState == LAST_BLOCK_END){
		// �A���ŕ������ƂɂȂ�̂Ŏ��o��
		this->BlockChankStackPop();
	}
	else if (m_lastState == LAST_WRITE){
		// �O�񂪏������݃��[�h�Ȃ�
		// �`�����N�t���O������
		this->SizeUpdate(sizeof(CHANK_FLG));
		cFlg = CHANK_FLG_NOTHING;
		if (m_PType == FF_OPERATION_FILE)
			m_file.WriteN8(cFlg);
		else
			m_spUtilBuffer->WriteByte((byte)cFlg);
	}

	if (m_PType == FF_OPERATION_FILE)
	{
		// ���݂̃I�t�Z�b�g�l���擾
		// �X�^�b�N���o���O�̃I�t�Z�b�g�l�Ɉړ�
		currentOffset = m_file.Tell();
		m_file.SeekSet(m_vChankStack.back().offset, SEEK_SET);
		// �w��ꏊ�փ`�����N���X�V
		// �����Č��̃I�t�Z�b�g�l�ɖ߂�
		m_vChankStack.back().chank.Write(m_file);
		m_file.SeekSet(currentOffset, SEEK_SET);
	}
	else
	{
		// ���݂̃I�t�Z�b�g�l���擾
		// �X�^�b�N���o���O�̃I�t�Z�b�g�l�Ɉړ�
		currentOffset = m_spUtilBuffer->Seek();
		m_spUtilBuffer->SeekSet(m_vChankStack.back().offset);
		// �w��ꏊ�փ`�����N���X�V
		// �����Č��̃I�t�Z�b�g�l�ɖ߂�
		m_vChankStack.back().chank.Write(m_spUtilBuffer);
		m_spUtilBuffer->SeekSet(currentOffset);
	}
	// �X�^�b�N������o��
	m_vChankStack.pop_back();

	// �w���|�P����
	--m_currentDepth;
	// id�����ɖ߂�
	if (!m_vChankStack.empty())
		m_currentID = m_vChankStack.back().chank.id;
	else
		m_currentID = -1;

	// �t���O
	m_lastState = LAST_BLOCK_END;

	return 1;
}
/*!
* @brief �����o�����I������B
* @return �����Ȃ����1��Ԃ�
*/
int SaveState::End()
{
	if ( m_PType == FF_OPERATION_FILE){
		// �w�b�_�����Ƀf�[�^�T�C�Y���ď������݂���
		m_file.SeekSet(0, SEEK_SET);
		m_header.Write(m_file);
		// ����`�����N
		assert(m_vChankBlockStack.size() == 1);
		this->BlockChankStackPop();

		m_file.Close();
	}
	else
	{
		// �w�b�_�����Ƀf�[�^�T�C�Y���ď������݂���
		m_spUtilBuffer->SeekSet(0);
		m_header.Write(m_spUtilBuffer);
		// ����`�����N
		assert(m_vChankBlockStack.size() == 1);
		this->BlockChankStackPop();

		m_spUtilBuffer.reset();
	}
	return 1;
}
/*!
* @brief �u���b�N�`�����N�X�^�b�N���|�b�v���A�w�肳�ꂽ�I�t�Z�b�g�l�Ɉړ����t�@�C����
*  ����������B�����āA�t�@�C���ʒu�����̈ʒu�ɖ߂��B
* @return �����Ȃ����1��Ԃ�
*/
int SaveState::BlockChankStackPop()
{
	int64_t currentOffset;
	if (m_PType == FF_OPERATION_FILE)
	{
		// ���݂̃I�t�Z�b�g�l���擾�A�X�^�b�N���o���O�̃I�t�Z�b�g�l�Ɉړ�
		currentOffset = m_file.Tell();
		m_file.SeekSet(m_vChankBlockStack.back().offset, SEEK_SET);
		// �w��ꏊ�փ`�����N���X�V�A�����Č��̃I�t�Z�b�g�l�ɖ߂�
		m_vChankBlockStack.back().chank.Write(m_file);
		m_file.SeekSet(currentOffset, SEEK_SET);
	}
	else
	{
		// ���݂̃I�t�Z�b�g�l���擾�A�X�^�b�N���o���O�̃I�t�Z�b�g�l�Ɉړ�
		currentOffset = m_spUtilBuffer->Seek();
		m_spUtilBuffer->SeekSet(m_vChankBlockStack.back().offset);
		// �w��ꏊ�փ`�����N���X�V�A�����Č��̃I�t�Z�b�g�l�ɖ߂�
		m_vChankBlockStack.back().chank.Write(m_spUtilBuffer);
		m_spUtilBuffer->SeekSet(currentOffset);
	}
	// �u���b�N�X�^�b�N����|�b�v
	m_vChankBlockStack.pop_back();
	return 1;
}
/*!
* @brief  �T�C�Y�̍X�V����
* @param [in] size �T�C�Y�i�o�C�g�P�ʁj
* @return �����Ȃ����1��Ԃ�
*/
int SaveState::SizeUpdate(int size)
{
	// �w�b�_�T�C�Y�̍X�V
	m_header.size += size;

	// �u���b�N�`�����N
	for (auto &val : m_vChankBlockStack)
		val.chank.size += size;

	// �X�^�b�N���̃T�C�Y�����ׂĉ��Z���� m_vChankStack
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
//! @brief �R���X�g���N�^
//-----------------------------------------------------------------------------------
/*!
* @brief  �R���X�g���N�^
* @param [in] rFile GT2File�|�C���^
* @param [in] pChank Chunk�|�C���^
* @param [in] offset �I�t�Z�b�g�l
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
* @brief  �R���X�g���N�^
* @param [in] spBuffer GT2UtilBuffer�X�}�[�g�|�C���^(share)
* @param [in] pChank Chunk�|�C���^
* @param [in] offset �I�t�Z�b�g�l
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
* @brief  �f�X�g���N�^
*/
LoadChank::~LoadChank()
{

}
/*!
* @brief �������
* @return �Q�Ɛ�
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
* @brief �u���b�N�`�����N���擾����
* @param [out] pOut �l������`�����N�\���̃|�C���^
* @return �����Ȃ����1��Ԃ�
*/
void LoadChank::GetBlockChank(Chunk* pOut)
{
	*pOut = m_chank;
}
/*!
* @brief ���̃`�����N�f�[�^��T���o���BppData��LoadData�̃|�C���^��n���B
*  �g���I�������K��Release�֐����Ăяo���B
* @param [out] pChank �l������`�����N�\���̃|�C���^
* @param [out] ppData LoadData�|�C���^�|�C���^�B���s�����ꍇ��nullptr��Ԃ��B
* @return �����Ȃ����1��Ԃ�
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
* @brief �R���X�g���N�^
* @param [in] pFile GT2File�|�C���^
* @param [in] pChank Chunk�|�C���^
* @param [in] offset ���݂̃t�@�C���̃I�t�Z�b�g�l
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
* @brief �R���X�g���N�^
* @param [in] spBuffer GT2UtilBuffer�X�}�[�g�|�C���^(shared)
* @param [in] pChank Chunk�|�C���^
* @param [in] offset ���݂̃o�b�t�@�̃I�t�Z�b�g�l
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
* @brief �f�X�g���N�^
*/
LoadData::~LoadData()
{

}
/*!
* @brief �������
* @return �Q�Ɛ�
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
* @brief �`�����N���擾����
* @param [out] pOut �l������`�����N�\���̃|�C���^
* @return �����Ȃ����1��Ԃ�
*/
void LoadData::GetChank(Chunk *pOut){
	*pOut = m_chank;
}
/*!
* @brief ���̃f�[�^��T���o���BppOut��LoadChank�̃|�C���^��n���B
*  �g���I�������K��Release�֐����Ăяo���B
* @param [in,out] pFFS    BasicBody�Ŕh�����ꂽ�\���̃|�C���^��n���A�l���擾����B
* @param [out]    ppChank LoadChank�|�C���^�|�C���^�B���s�����ꍇ��nullptr��Ԃ��B
* @return �����Ȃ����1��Ԃ�
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
			// ����q������
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
* @brief �R���X�g���N�^
*/
LoadState::LoadState()
{
}
/*!
* @brief �f�X�g���N�^
*/
LoadState::~LoadState()
{
	this->End();
}
/*!
* @brief �쐬����t�@�C������ݒ肷��B
* @param [in] fileName   �t�@�C����
* @return �Ȃ�
*/
void LoadState::InitSetting(const char *fileName)
{
	m_fileName = fileName;
	m_PType = FF_OPERATION_FILE;
}
/*!
* @brief �쐬����GT2UtilBuffer�B
* @param [in] spBuffer   GT2UtilBuffer�̃X�}�[�g�|�C���^(shared)
* @return �Ȃ�
*/
void LoadState::InitSetting(GT2UtilBufferSP &spBuffer)
{
	assert(spBuffer);
	m_PType = FF_OPERATION_BUFFER;
	m_spUtilBuffer = spBuffer;
}

/*!
* @brief �ǂݍ��݂��J�n����BppOut��LoadChank�̃|�C���^��n���B�g���I�������K��Release�֐����Ăяo���B
* @param [in] spBuffer   GT2UtilBuffer�̃X�}�[�g�|�C���^(shared)
* @return �Ȃ�
*/
int LoadState::Start(LoadChank **ppOut)
{
	Chunk chank;
	this->End();

	if (m_PType == FF_OPERATION_FILE)
	{
		if (!(m_file.OpenA(m_fileName.c_str(), "rb")))
			return 0;
		// �w�b�_�̓ǂݍ���
		m_header.Read(m_file);
		// ����`�����N�ݒ�ǂݍ���
		chank.Read(m_file);
		*ppOut = new LoadChank(&m_file, &chank, m_file.Tell());
	}
	else
	{
		// �w�b�_�̓ǂݍ���
		m_header.Read(m_spUtilBuffer);
		// ����`�����N�ݒ�ǂݍ���
		chank.Read(m_spUtilBuffer);
		*ppOut = new LoadChank(m_spUtilBuffer, &chank, m_spUtilBuffer->Seek());
	}
	return 1;
}

/*!
* @brief �����o�����I������B
* @return �����Ȃ����1��Ԃ�
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

