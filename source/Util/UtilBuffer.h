/*! @file  UtilBuffer.h
* @brief メモリ上に適当なサイズのバッファを作り、読み書きするものを主に扱う
* @author kaoken
* @date 2014/01/23 作成開始
*/
#pragma once

#include <Core/greenTea2D.h>


/*!
* @brief メモリ上に適当なサイズのバッファを作り、読み書きするクラス
*/
class GT2UtilBuffer
{
protected:
	byte*		m_pBffer;		//!< バッファ
	int64_t		m_bufferSize;	//!< バッファのサイズ（バイト単位）
	int64_t		m_pos;			//!< バッファの位置
	bool		m_isBigEndian;	//!< ビッグエンディアンか？
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
typedef S_PTR<GT2UtilBuffer> GT2UtilBufferSP;	//!< GT2UtilBufferのスマートポインタ(shared)の型
typedef W_PTR<GT2UtilBuffer> CUtilBufferWP;	//!< GT2UtilBufferのスマートポインタ(weak)の型

/*!
* @brief GT2UtilBufferのスマートポインタ型でバッファを作成する
* @param [in]  size         バッファサイズ
* @param [in]  isBigEndian  ビッグエンディアンか？ 指定しないバイはFALSE
* @return GT2UtilBufferのスマートポインタ型で返す。
*/
inline GT2UtilBufferSP CreateUtilBuffer(int size, bool isBigEndian = TRUE)
{
	return GT2UtilBufferSP(new GT2UtilBuffer(size, isBigEndian));
}
