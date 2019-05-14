/*! 
 * @file  chunk.h
 * @brief �ȒP��IFF�iInterchange File Format�j
 * @author kaoken
 * @version 1.0
 * @date 2014/01/24 �쐬�J�n
 */

#pragma once

#include <Core/greenTea2D.h>
#include <Util/filesystem.h>
#include <Util/UtilBuffer.h>


//------------------------------------------
// �錾��i�߂Ă���
//------------------------------------------
class LoadState;
class LoadChank;
class LoadData;


//------------------------------------------
// �}�N��
//------------------------------------------
#define FF_SFT64(x,n) ((uint64_t)(x)<<n)
#define FF_SFT32(x,n) ((uint32_t)(x)<<n)
#define FFID4_(a,b,c,d)	 (FF_SFT32(d,24)|FF_SFT32(c,16)|FF_SFT32(b,8)|(uint32_t)(a))
#define FFID8_(a,b,c,d,e,f,g,h)	 (FF_SFT64(h,56)|FF_SFT64(g,48)|FF_SFT64(f,40)|FF_SFT64(e,32)|FF_SFT64(d,24)|FF_SFT64(c,16)|FF_SFT64(b,8)|(uint64_t)(a))
#define FF_SHIFT(n) (1<<n)


/*!
	* @brief F �Ƃ��\���̂��ׂĂɔh�����Ďg�p����B
	*/
struct BasicBody
{
	/*!
		* @brief �\���̂����ʂ��邽�߂�ID���擾����
		* @return �\���̂�ID
		*/
	virtual inline uint64_t GetID() const = 0;
	/*!
		* @brief �\���̂̃T�C�Y���擾����
		* @return �\���̂̃T�C�Y��Ԃ�
		*/
	virtual inline int GetStructSize() const = 0;
	/*!
		* @brief �t�@�C���ɏ�������
		* @param [in] rFile GT2File�N���X
		* @return �������ݐ������A1��Ԃ��B
		*/
	virtual inline int Write(GT2File &rFile) const = 0;
	/*!
		* @brief �o�b�t�@�ɏ�������
		* @param [in] spFile GT2UtilBufferSP�X�}�[�g�|�C���^
		* @return GT2UtilBuffer�̏������݈ʒu��Ԃ��B
		*/
	virtual inline int Write(GT2UtilBufferSP &spFile) const = 0;
	/*!
		* @brief �t�@�C����ǂݍ���
		* @param [in] rFile GT2File�N���X
		* @return �ǂݍ��ݐ������A1��Ԃ��B
		*/
	virtual inline int Read(GT2File &rFile) = 0;
	/*!
		* @brief �o�b�t�@����ǂݍ���
		* @param [in] rFile GT2File�N���X
		* @return GT2UtilBuffer�̓ǂݍ��݈ʒu��Ԃ��B
		*/
	virtual inline int Read(GT2UtilBufferSP &spFile) = 0;
};

// fileType �Ŏg�p����
#define FF_HEADER_FTYPE_BIN	FFID4_('b','i','n','\0')	// �o�C�i���t�@�C���^�C�v
/*!
* @brief �t�@�C���̃w�b�_�ɕK���Z�b�g����
*/
struct Header : public BasicBody
{
	uint32_t	version;		//!< �o�[�W����
	uint32_t	fileType;		//!< �t�@�C���̃^�C�v�A�o�C�i���܂��̓e�L�X�g
	int64_t		size;			//!< �w�b�_�f�[�^����̑S�f�[�^�̈��\���B
	Header()
	{
		version = 0;
		fileType = FF_HEADER_FTYPE_BIN;
		size = 0;
	}
public:
	/*!
		* @brief ������Z�q =
		* @param [in] r Header�\����
		* @return ���M�̃|�C���^
		*/
	Header& operator = (const Header& r){
		version = r.version;
		fileType = r.fileType;
		size = r.size;

		return *this;
	}
		
	/**
		* @name BasicBody���h�����\�b�h
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
	* @brief �`�����N�\����
	*/
struct Chunk : public BasicBody
{
	uint64_t	id;				//!< �`�����Nid(������8������)
	int32_t		structNum;		//!< �\����(�t�H�[�}�b�g)��
	int64_t		size;			//!< �T�C�Y
public:
	Chunk& operator = (const Chunk& r){
		id = r.id;
		structNum = r.structNum;
		size = r.size;
		return *this;
	}

	/**
	* @name BasicBody���h�����\�b�h
	*/
	//@{
	virtual inline uint64_t GetID() const override { return FF_CUNK_ID; }
	virtual inline int GetStructSize() const override { return 20; }
	virtual inline int Write(GT2File &rFile) const override {
		// �p�f�B���O&�h���ɂ��A�X�ɏ�������
		rFile.WriteN64(id);
		rFile.WriteN32(structNum);
		rFile.WriteN64(size);
		return 1;
	}
	virtual inline int Write(GT2UtilBufferSP &spFile) const override {
		// �p�f�B���O&�h���ɂ��A�X�ɏ�������
		spFile->WriteN64(id);
		spFile->WriteN32(structNum);
		spFile->WriteN64(size);
		return spFile->Seek();
	}
	virtual inline int Read(GT2File &rFile) override {
		// �p�f�B���O&�h���ɂ��A�X�ɓǂݍ���
		id = rFile.ReadU64();
		structNum = rFile.ReadN32();
		size = rFile.ReadN64();
		return 1;
	}
	virtual inline int Read(GT2UtilBufferSP &spFile) override {
		// �p�f�B���O&�h���ɂ��A�X�ɓǂݍ���
		spFile->ReadU64(&id);
		spFile->ReadN32(&structNum);
		spFile->ReadN64(&size);
		return spFile->Seek();
	}
	//@}
};


/*!
* @brief �u���b�N�̖��O�t��������\����
*/
struct BlockIndent
{
	int64_t		id;		//!< �`�����Nid
	const char	*sz;	//!< ���O
};

typedef char CHANK_FLG;		//!< �`�����N�t���O�^
#define CHANK_FLG_NOTHING	0	//!< ���ɂȂ� @see CHANK_FLG
#define CHANK_FLG_NEST		1	//!< �`�����N�̓���q @see CHANK_FLG
#define CHANK_FLG_CHANK		2	//!< �����w�ɓ���q @see CHANK_FLG


/*!
* @brief �u���b�N�̖��O�t��������\����
*/
struct ChankOffset
{
	Chunk	chank;		//!< �`�����N�f�[�^
	int64_t	offset;		//!< �I�t�Z�b�g
};
//!< �e�`�����N�̃I�t�Z�b�g�l���i�[����Ƃ��g�p����^ @see ChankOffset
typedef gtVector<ChankOffset>	VChankOffset;

/*!
* @brief �����^�C�v
*/
enum FF_OPERATION_TYPE
{
	FF_OPERATION_FILE,	//!< FF_�\���̊֘A�ŁA�t�@�C������
	FF_OPERATION_BUFFER	//!< FF_�\���̊֘A�ŁA�o�b�t�@����
};


/*!
* @brief �ėp�t�H�[�}�b�g���t�@�C����ۑ�����Ƃ��Ɏg��
*/
class SaveState
{
protected:
	//! @name m_lastState �Ŏg�p����t���O 
	//! @see SaveState::m_lastState
	//@{
	const static int LAST_NOTHING = 0;		//!< ���ɂȂ� @see SaveState::m_lastState
	const static int LAST_START = 1;			//!< �J�n���ꂽ @see SaveState::m_lastState
	const static int LAST_BLOCK_START = 2;	//!< �u���b�N���J�n���ꂽ @see SaveState::m_lastState
	const static int LAST_BLOCK_END = 3;		//!< �u���b�N���I������ @see SaveState::m_lastState
	const static int LAST_WRITE = 4;			//!< �f�[�^���������� @see SaveState::m_lastState
	const static int LAST_END = 5;			//!< �I�� @see SaveState::m_lastState
	//@}
protected:
	FF_OPERATION_TYPE	m_PType;
	int64_t				m_currentID;			//!< ���݂�id
	int					m_lastState;			//!< �ŏI���

	VChankOffset		m_vChankStack;			//!< �`�����N�X�^�b�N
	VChankOffset		m_vChankBlockStack;		//!< �`�����N�u���b�N�X�^�b�N
	std::string			m_fileName;				//!< �t�@�C����
	GT2File				m_file;					//!< �t�@�C���\���̃|�C���^
	GT2UtilBufferSP		m_spUtilBuffer;			//!< �o�b�t�@�[
	Header				m_header;				//!< �w�b�_�[�\����
	int				m_currentDepth;			//!< ���݂̐[��
public:
	/*!
	* @brief �w�b�_�f�[�^�擾
	* @param [out] pHeader Header�|�C���^
	* @return �Ȃ�
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
* @brief �`�����N���[�h�N���X
*/
class LoadChank
{
protected:
	FF_OPERATION_TYPE	m_PType;		//!<  �����^�C�v
	GT2File*			m_pFile;		//!<  �t�@�C���\���̃|�C���^ @note �Q�Ƃ̂�
	GT2UtilBufferSP	m_spUtilBuffer;		//!<  �o�b�t�@�[
	Chunk		m_chank;			//!<  �`�����N
	int64_t			m_offset;			//!<  ���̃t�@�C���̃I�t�Z�b�g�l
	int64_t			m_nextOffset;		//!<  ���̃t�@�C���̃I�t�Z�b�g�l
	int32_t			m_chankCnt;			//!<  ����������
	int32_t			m_refCnt;			//!<  �Q�ƃJ�E���g
public:
	LoadChank(GT2File *pFile, const Chunk *pChank, int64_t offset);
	LoadChank(GT2UtilBufferSP &spBuffer, const Chunk *pChank, int64_t offset);
	~LoadChank();
	int32_t Release();
	void GetBlockChank(Chunk* pOut);
	int FindChank(Chunk* pChank, LoadData** ppData);
};

/*!
* @brief �`�����N��id���Ɍ��߂�ꂽ�f�[�^��ǂݍ���
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
	FF_OPERATION_TYPE	m_PType;		//!< �����^�C�v
	GT2File*		m_pFile;			//!< �t�@�C���\���̃|�C���^ @note �Q�Ƃ̂�
	GT2UtilBufferSP	m_spUtilBuffer;		//!< �o�b�t�@�[
	int64_t			m_nextOffset;		//!< ���̃t�@�C���̃I�t�Z�b�g�l
	int64_t			m_offset;			//!< �I�t�Z�b�g�l
	int32_t			m_count;			//!< �f�[�^�J�E���g��
	Chunk		m_chank;			//!< �`�����N�\����
	int32_t			m_refCnt;			//!< �Q�ƃJ�E���g
};

/*!
* @brief ��Ԃ̎擾�N���X
*/
class LoadState
{
	FF_OPERATION_TYPE	m_PType;		//!< �����^�C�v
	std::string			m_fileName;		//!< �t�@�C����
	GT2File				m_file;			//!< �t�@�C���N���X
	GT2UtilBufferSP		m_spUtilBuffer;	//!< �o�b�t�@�[
	Header				m_header;		//!< �w�b�_�[�\����
	int				m_currentDepth;	//!< ���݂̐[��
public:
	LoadState();
	~LoadState();

	void InitSetting(const char *fileName);
	void InitSetting(GT2UtilBufferSP &spBuffer);
	int Start(LoadChank **ppOut);
	int End();
	/*!
	* @brief �w�b�_�f�[�^�擾
	* @param [out] pHeader Header�|�C���^
	* @return �Ȃ�
	*/
	inline void GetHeader(Header* pHeader)
	{
		(*pHeader) = m_header;
	}
};