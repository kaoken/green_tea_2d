/*! @file  UtilBuffer.h
* @brief ��������ɓK���ȃT�C�Y�̃o�b�t�@�����A�ǂݏ���������̂���Ɉ���
* @author kaoken
* @date 2014/01/23 �쐬�J�n
*/
#pragma once

#include <Core/greenTea2D.h>


/*!
* @brief ��������ɓK���ȃT�C�Y�̃o�b�t�@�����A�ǂݏ�������N���X
*/
class GT2UtilBuffer
{
protected:
	byte*		m_pBffer;		//!< �o�b�t�@
	int64_t		m_bufferSize;	//!< �o�b�t�@�̃T�C�Y�i�o�C�g�P�ʁj
	int64_t		m_pos;			//!< �o�b�t�@�̈ʒu
	bool		m_isBigEndian;	//!< �r�b�O�G���f�B�A�����H
protected:
	byte ReadByte();

public:
	GT2UtilBuffer(int size, bool isBigEndian = FALSE);
	~GT2UtilBuffer();
	byte* BufferPtr();
	int BufferSize();
	bool SeekSet(int64_t pos);
	int Seek();
	bool CheckOverSeek(int len);
	bool ReadByte(byte* p);
	bool ReadByte(byte* pB, int length);
	bool ReadN8(int8_t* pN);
	bool ReadN16(int16_t* pN);
	bool ReadN32(int32_t* pN);
	bool ReadN64(int64_t* pN);
	bool ReadU16(uint16_t* pN);
	bool ReadU32(uint32_t* pN);
	bool ReadU64(uint64_t* pN);
	bool ReadF32(float* pN);
	bool ReadF64(double* pN);
	bool WriteByte(const byte n);
	bool WriteByte(const byte* pB, int length);
	bool WriteN8(const int8_t n);
	bool WriteN16(const int16_t n);
	bool WriteN32(const int32_t n);
	bool WriteN64(const int64_t n);
	bool WriteU16(const uint16_t n);
	bool WriteU32(const uint32_t n);
	bool WriteU64(const uint64_t n);
	bool WriteF32(const double n);
	bool WriteF64(const double n);
};
typedef S_PTR<GT2UtilBuffer> GT2UtilBufferSP;	//!< GT2UtilBuffer�̃X�}�[�g�|�C���^(shared)�̌^
typedef W_PTR<GT2UtilBuffer> CUtilBufferWP;	//!< GT2UtilBuffer�̃X�}�[�g�|�C���^(weak)�̌^

/*!
* @brief GT2UtilBuffer�̃X�}�[�g�|�C���^�^�Ńo�b�t�@���쐬����
* @param [in]  size         �o�b�t�@�T�C�Y
* @param [in]  isBigEndian  �r�b�O�G���f�B�A�����H �w�肵�Ȃ��o�C��FALSE
* @return GT2UtilBuffer�̃X�}�[�g�|�C���^�^�ŕԂ��B
*/
inline GT2UtilBufferSP CreateUtilBuffer(int size, bool isBigEndian = TRUE)
{
	return GT2UtilBufferSP(new GT2UtilBuffer(size, isBigEndian));
}
