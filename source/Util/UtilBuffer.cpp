#include <Util/UtilBuffer.h>


#define RN16() ((int16_t)ReadByte())
#define RN32() ((int32_t)ReadByte())
#define RN64() ((int64_t)ReadByte())
/*!
* @brief �R���X�g���N�^
* @param [in]  size         �o�b�t�@�T�C�Y
* @param [in]  isBigEndian  �r�b�O�G���f�B�A�����H �w�肵�Ȃ��o�C��false
*/
GT2UtilBuffer::GT2UtilBuffer(int size, bool isBigEndian)
{
	assert(size);
	m_isBigEndian = isBigEndian;
	m_bufferSize = size;
	m_pos = 0;
	m_pBffer = new byte[size];
}
/*!
* @brief �f�X�g���N�^
*/
GT2UtilBuffer::~GT2UtilBuffer()
{
	SAFE_DELETE_ARRAY(m_pBffer);
}
/*!
* @brief 1�o�C�g�擾����
* @return 1�o�C�g�Ԃ�
*/
byte GT2UtilBuffer::ReadByte()
{
	int n = m_pos;
	if (++m_pos >= m_bufferSize)
	{
		return 0;
	}
	return *(m_pBffer + n);
}
/*!
* @brief �o�b�t�@�|�C���^���擾����
* @return �o�b�t�@�|�C���^��Ԃ�
*/
byte* GT2UtilBuffer::BufferPtr(){ return m_pBffer; }
/*!
* @brief �o�b�t�@�T�C�Y���擾����
* @return �o�b�t�@�T�C�Y��Ԃ�
*/
int GT2UtilBuffer::BufferSize(){ return m_bufferSize; }
/*!
* @brief �o�b�t�@�̎Q�ƈʒu��ς���
* @param [in]  pos         �o�b�t�@�̈ʒu���w��
* @return �ʒu���s���ȏꍇfalse��Ԃ��A�ʒu�͕ς��Ȃ��B
*/
bool GT2UtilBuffer::SeekSet(int64_t pos)
{
	if (pos >= m_bufferSize)
		return false;
	m_pos = pos;
	return true;
}
/*!
* @brief �o�b�t�@�̌��݂̈ʒu���擾
* @return �o�b�t�@�̌��݂̈ʒu��Ԃ�
*/
int GT2UtilBuffer::Seek()
{
	return m_pos;
}
/*!
* @brief �o�b�t�@�̌��݂̈ʒu���A����len�𑫂����ʒu�܂ŗL�����`�F�b�N
* @param [in]  len         ����
* @return �o�b�t�@�̌��݂̈ʒu���A����len�𑫂����ʒu�܂ŗL���̏ꍇ��true��Ԃ�
*/
bool GT2UtilBuffer::CheckOverSeek(int len)
{
	if ((m_pos + len) >= m_bufferSize)
		return true;
	return false;
}
/*!
* @brief 1�o�C�g�ǂݍ���
* @param [in]  p         byte�̒l��n���|�C���^
* @return �ǂݍ��ݐ�����true��Ԃ�
*/
bool GT2UtilBuffer::ReadByte(byte* p)
{
	if (CheckOverSeek(1))return false;
	*p = *(m_pBffer + 1);
	return true;
}
/*!
* @brief �w�肵�������̃o�C�g���ǂݍ���
* @param [in]  p         byte�̒l��n���|�C���^
* @param [in]  length    �ǂݍ��ޒ����A�o�C�g�P��
* @return �ǂݍ��ݐ�����true��Ԃ�
*/
bool GT2UtilBuffer::ReadByte(byte* pB, int length)
{
	if (CheckOverSeek(length))return false;
	for (int i = 0; i < length; ++i)
		pB[i] = ReadByte();
	return true;
}
/*!
* @brief int8_t�^�i1�o�C�g�ǂݍ��݁j
* @param [in]  pN    int16_t�̒l��n���|�C���^
* @return �ǂݍ��ݐ�����true��Ԃ�
*/
bool GT2UtilBuffer::ReadN8(int8_t* pN)
{
	return ReadByte((byte*)pN);
}
/*!
* @brief int16_t�^�i2�o�C�g�ǂݍ��݁j
* @param [in]  pN    int16_t�̒l��n���|�C���^
* @return �ǂݍ��ݐ�����true��Ԃ�
*/
bool GT2UtilBuffer::ReadN16(int16_t* pN)
{
	if (CheckOverSeek(2))return false;
	if (!m_isBigEndian) return ReadByte((byte*)pN, 2);
	*pN = RN16() | (RN16() << 8);
	return true;
}
/*!
* @brief int32_t�^�i4�o�C�g�ǂݍ��݁j
* @param [in]  pN    int32_t�̒l��n���|�C���^
* @return �ǂݍ��ݐ�����true��Ԃ�
*/
bool GT2UtilBuffer::ReadN32(int32_t* pN)
{
	if (CheckOverSeek(4))return false;
	if (!m_isBigEndian) return ReadByte((byte*)pN, 4);
	*pN = RN32() | (RN32() << 8) | (RN32() << 16) | (RN32() << 24);
	return true;
}
/*!
* @brief int64_t�^�i8�o�C�g�ǂݍ��݁j
* @param [in]  pN    int64_t�̒l��n���|�C���^
* @return �ǂݍ��ݐ�����true��Ԃ�
*/
bool GT2UtilBuffer::ReadN64(int64_t* pN)
{
	if (CheckOverSeek(8))return false;
	if (!m_isBigEndian) return ReadByte((byte*)pN, 8);
	*pN = RN64() | (RN64() << 8) | (RN64() << 16) |
		(RN64() << 24) | (RN64() << 32) | (RN64() << 40) |
		(RN64() << 48) | (RN64() << 56);
	return true;
}
/*!
* @brief uint16_t�^�i2�o�C�g�������݁j
* @param [in]  n     uint16_t�^����
* @return �������ݐ�����true��Ԃ�
*/
bool GT2UtilBuffer::ReadU16(uint16_t* pN)
{
	return ReadN16((int16_t*)pN);
}
/*!
* @brief uint32_t�^�i4�o�C�g�������݁j
* @param [in]  n     uint32_t�^����
* @return �������ݐ�����true��Ԃ�
*/
bool GT2UtilBuffer::ReadU32(uint32_t* pN)
{
	return ReadN32((int32_t*)pN);
}
/*!
* @brief uint64_t�^�i8�o�C�g�������݁j
* @param [in]  n     uint64_t�^����
* @return �������ݐ�����true��Ԃ�
*/
bool GT2UtilBuffer::ReadU64(uint64_t* pN)
{
	return ReadN64((int64_t*)pN);
}
/*!
* @brief float�^�i4�o�C�g�ǂݍ��݁j
* @param [in]  pN    float�̒l��n���|�C���^
* @return �ǂݍ��ݐ�����true��Ԃ�
*/
bool GT2UtilBuffer::ReadF32(float* pN)
{
	return ReadN32((int32_t*)pN);
}
/*!
* @brief double�^�i8�o�C�g�ǂݍ��݁j
* @param [in]  pN    double�̒l��n���|�C���^
* @return �ǂݍ��ݐ�����true��Ԃ�
*/
bool GT2UtilBuffer::ReadF64(double* pN)
{
	return ReadN64((int64_t*)pN);
}

/*!
* @brief byte�^�i1�o�C�g�������݁j
* @param [in]  n    byte�̒l
* @return �������ݐ�����true��Ԃ�
*/
bool GT2UtilBuffer::WriteByte(const byte n)
{
	if (CheckOverSeek(1))return false;
	m_pBffer[m_pos] = n;
	++m_pos;
	return true;
}
/*!
* @brief byte�^�i1�o�C�g�������݁j
* @param [in]  pB     byte�^�|�C���^
* @param [in]  length �ǂݍ��ޒ���
* @return �������ݐ�����true��Ԃ�
*/
bool GT2UtilBuffer::WriteByte(const byte* pB, int length)
{
	if (CheckOverSeek(length))return false;
	for (int i = 0; i < length; ++i)
		m_pBffer[i] = *pB;
	return true;
}
/*!
* @brief int8_t�^�i1�o�C�g�������݁j
* @param [in]  pB     int8_t�^����
* @return �������ݐ�����true��Ԃ�
*/
bool GT2UtilBuffer::WriteN8(const int8_t n)
{
	return WriteByte(R_CAST(const int8_t&, n));
}
/*!
* @brief int16_t�^�i2�o�C�g�������݁j
* @param [in]  pB     int16_t�^����
* @return �������ݐ�����true��Ԃ�
*/
bool GT2UtilBuffer::WriteN16(const int16_t n)
{
	if (CheckOverSeek(2))return false;
	if (!m_isBigEndian) return WriteByte((byte*)&n, 2);
	WriteByte((byte)(n & 0x000000FF));
	WriteByte((byte)((n & 0x0000FF00) >> 8));
	return true;
}
/*!
* @brief int32_t�^�i4�o�C�g�������݁j
* @param [in]  n     int32_t�^����
* @return �������ݐ�����true��Ԃ�
*/
bool GT2UtilBuffer::WriteN32(const int32_t n)
{
	if (CheckOverSeek(4))return false;
	if (!m_isBigEndian) return WriteByte((byte*)&n, 4);
	WriteByte((byte)(n & 0x000000FF));
	WriteByte((byte)((n & 0x0000FF00) >> 8));
	WriteByte((byte)((n & 0x00FF0000) >> 16));
	WriteByte((byte)((n & 0xFF000000) >> 24));
	return true;
}
/*!
* @brief int64_t�^�i8�o�C�g�������݁j
* @param [in]  n     int64_t�^����
* @return �������ݐ�����true��Ԃ�
*/
bool GT2UtilBuffer::WriteN64(const int64_t n)
{
	if (CheckOverSeek(8))return false;
	if (!m_isBigEndian) return WriteByte((byte*)&n, 8);
	WriteByte((byte)( n & 0x00000000000000FF));
	WriteByte((byte)((n & 0x000000000000FF00) >> 8));
	WriteByte((byte)((n & 0x0000000000FF0000) >> 16));
	WriteByte((byte)((n & 0x00000000FF000000) >> 24));
	WriteByte((byte)((n & 0x000000FF00000000) >> 32));
	WriteByte((byte)((n & 0x0000FF0000000000) >> 40));
	WriteByte((byte)((n & 0x00FF000000000000) >> 48));
	WriteByte((byte)((n & 0xFF00000000000000) >> 56));
	return true;
}
/*!
* @brief uint16_t�^�i2�o�C�g�������݁j
* @param [in]  n     uint16_t�^����
* @return �������ݐ�����true��Ԃ�
*/
bool GT2UtilBuffer::WriteU16(const uint16_t n)
{
	return WriteN16(R_CAST(const int16_t&, n));
}
/*!
* @brief uint32_t�^�i4�o�C�g�������݁j
* @param [in]  n     uint32_t�^����
* @return �������ݐ�����true��Ԃ�
*/
bool GT2UtilBuffer::WriteU32(const uint32_t n)
{
	return WriteN32(R_CAST(const int32_t&, n));
}
/*!
* @brief uint64_t�^�i8�o�C�g�������݁j
* @param [in]  n     uint64_t�^����
* @return �������ݐ�����true��Ԃ�
*/
bool GT2UtilBuffer::WriteU64(const uint64_t n)
{
	return WriteN64(R_CAST(const int64_t&, n));
}
/*!
* @brief int32_t�^�i4�o�C�g�������݁j
* @param [in]  n     int32_t�^����
* @return �������ݐ�����true��Ԃ�
*/
bool GT2UtilBuffer::WriteF32(const double n)
{
	return WriteN32(R_CAST(const int32_t&, n));
}
/*!
* @brief int64_t�^�i8�o�C�g�������݁j
* @param [in]  n     int64_t�^����
* @return �������ݐ�����true��Ԃ�
*/
bool GT2UtilBuffer::WriteF64(const double n)
{
	return WriteN64(R_CAST(const int64_t&, n));
}

#undef RN16
#undef RN32
#undef RN64