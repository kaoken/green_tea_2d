/*! @file  string.inl
* @brief MCLib.hファイル内から呼び出されるので、ほかから呼び出さないように！
*  型
* @author kaoken
* @date 2014/03/19 作成開始
*/
#pragma once

//------------------------------------------------------------
//! @name オリジナルの型
//------------------------------------------------------------
//@{
typedef int8_t				gtN8;	//!< 1バイト整数の型
typedef int16_t				gtN16;	//!< 2バイト整数の型
typedef int32_t				gtN32;	//!< 4バイト整数の型
typedef int64_t				gtN64;	//!< 8バイト整数の型
									//	typedef __int128			gtN128;	//!< 16バイト整数の型
typedef uint8_t				gtU8;	//!< 1バイト符号なし整数の型
typedef uint16_t			gtU16;	//!< 2バイト符号なし整数の型
typedef uint32_t			gtU32;	//!< 4バイト符号なし整数の型
typedef uint64_t			gtU64;	//!< 8バイト符号なし整数の型
									//typedef unsigned __int128	gtU128;
#ifndef _WIN 
typedef unsigned t128		gtU128;	//!< 16バイト符号なし整数の型
#endif

#ifdef _32BIT
typedef uint32_t			gtHandleID;	//!< ポインタを整数にした値の型
#define HANDLE_ID_MAX		0xffffffff
#else
typedef uint64_t			gtHandleID;	//!< ポインタを整数にした値の型
#define HANDLE_ID_MAX		0xffffffffffffffffui64
#endif

#if defined(mcULONGLONG)
#  undef gtULONGLONG
#endif

#if defined(mcLONGLONG)
#  undef gtLONGLONG
#endif


typedef int			gtBOOL;					//!< 4バイト整数のBOOL値
typedef long		gtLONG;					//!< long型
typedef long long	gtLONGLONG;				//!< long long型
typedef int			gtINT;					//!< int型
typedef short		gtSHORT;				//!< short型
typedef char		gtCHRA;					//!< char型
typedef unsigned long		gtULONG;		//!< unsigned long型
typedef unsigned long long	gtULONGLONG;	//!< unsigned long long型
typedef unsigned int		gtUINT;			//!< unsigned int型
typedef unsigned short		gtUSHORT;		//!< unsigned short型
typedef unsigned char		gtUCHRA;		//!< unsigned char型
typedef unsigned char		gtBYTE;			//!< unsigned char型
typedef unsigned short		gtWORD;			//!< unsigned short型
typedef unsigned long		gtDWORD;		//!< unsigned long型

typedef float gtF32;				//!< 4バイト浮動小数の型
typedef double gtF64;				//!< 8バイト浮動小数の型


#define gtN8_MIN	128
#define gtN8_MAX	(-127)
#define gtN16_MIN	(-32768)
#define gtN16_MAX	32767
#define gtN32_MIN	(-2147483647 - 1)
#define gtN32_MAX	2147483647L
#define gtN64_MIN	(-9223372036854775807i64 - 1)
#define gtN64_MAX	9223372036854775807i64

#define gtU8_MIN	0
#define gtU8_MAX	0xff
#define gtU16_MIN	0
#define gtU16_MAX	0xffff
#define gtU32_MIN	0
#define gtU32_MAX	0xffffffff
#define gtU64_MIN	0
#define gtU64_MAX	0xffffffffffffffffui64

#define gtF32_MIN	1.175494351e-38F
#define gtF32_MAX	3.402823466e+38F
#define gtF64_MIN	2.2250738585072014e-308
#define gtF64_MAX	1.7976931348623158e+308


#define gtSHORT_MIN		gtN16_MIN
#define gtSHORT_MAX		gtN16_MAX
#define gtUSHORT_MIN	gtU16_MIN
#define gtUSHORT_MAX	gtU16_MAX
#define gtWORD_MIN		gtU16_MIN
#define gtWORD_MAX		gtU16_MAX
#define gtINT_MIN		gtN32_MIN
#define gtINT_MAX		gtN32_MAX
#define gtLONG_MIN		gtN32_MIN
#define gtLONG_MAX		gtN32_MAX
#define gtULONG_MIN		gtU32_MIN
#define gtULONG_MAX		gtU32_MAX
#define gtDWORD_MIN		gtU32_MIN
#define gtDWORD_MAX		gtU32_MAX
#define gtLONGLONG_MIN	gtN64_MIN
#define gtLONGLONG_MAX	gtN64_MAX
#define gtUINT_MIN		gtU32_MIN
#define gtUINT_MAX		gtU32_MAX
//@}



//------------------------------------------------------------
//! @name ビット単位での変換など
//------------------------------------------------------------
//@{

// （ビッグ、リトル）エンディアンのバイト単位での反転するときに使用する
#define KN_2BYTE_INV(_var) _var = (0x00FF&(_var>>8)) | (0xFF00&(_var<<8))
#define KN_4BYTE_INV(_var) _var = (0x000000FF&(_var>>24)) | (0x0000FF00&(_var>>8)) | (0x00FF0000&(_var<<8))| (0xFF000000&(_var<<24))
#define KN_8BYTE_INV(_var) _var = (0x00000000000000FF&(_var>>56)) | (0x000000000000FF00&(_var>>40)) | (0x0000000000FF0000&(_var>>24))| (0x00000000FF000000&(_var>>8)) \
	(0x000000FF00000000 & (_var << 8)) | (0x0000FF0000000000 & (_var << 24)) | (0x00FF000000000000 & (_var << 40)) | (0xFF00000000000000 & (_var << 56))

#define KN_U8_SHIFT_U64(_var,_n) ((uint64_t)(_var)<<_n)
#define KN_U8_SHIFTuint32_t(_var,_n) ((uint32_t)(_var)<<_n)
#define KN_U64_ID(_0,_1,_2,_3,_4,_5,_6,_7) ((uint64_t)_0 | \
	KN_U8_SHIFT_U64(_1, 8) | KN_U8_SHIFT_U64(_2, 16) | KN_U8_SHIFT_U64(_3, 24) | \
	KN_U8_SHIFT_U64(_4, 32) | KN_U8_SHIFT_U64(_5, 40) | KN_U8_SHIFT_U64(_6, 48) | \
	KN_U8_SHIFT_U64(_7, 56))
#define MCuint32_t_ID(_0,_1,_2,_3) ((uint32_t)_0 | \
	KN_U8_SHIFTuint32_t(_1, 8) | KN_U8_SHIFTuint32_t(_2, 16) | KN_U8_SHIFTuint32_t(_3, 24))

#define Memcpy1Byte(_bff,_var) std::memcpy(_bff,(void*)_var,1)
#define Memcpy2Byte(_bff,_var) std::memcpy(_bff,(void*)_var,2)
#define Memcpy4Byte(_bff,_var) std::memcpy(_bff,(void*)_var,4)
#define Memcpy8Byte(_bff,_var) std::memcpy(_bff,(void*)_var,8)
//@}

//------------------------------------------------------------
//! @name 基本STLマクロ
//------------------------------------------------------------
//@{
#define gtMap		std::map			//!< STL mapと同様
#define gtUMap		std::unordered_map	//!< STL unordered_mapと同様
#define gtPair		std::pair			//!< STL pairと同様
#define gtList		std::list			//!< STL listと同様
#define gtVector	std::vector			//!< STL vectorと同様
#define gtStack		std::stack			//!< STL stackと同様
#define gtMkPair	std::make_pair		//!< STL make_pairと同様
#define gtQueue		std::queue			//!< STL queueと同様
#define gtSet		std::set			//!< STL setと同様
//@}

#include "string.inl"

//------------------------------------------------------------
//! @name gtMap 等で使用する
//------------------------------------------------------------
//@{
template <typename T> struct KN_Pointer_less
{
	bool operator () (const T *l, const T *r) const
	{
		return l < r;
	}
};

#if defined(KN_ANDROID)
inline int wstricmp(const wchar_t *s1, const wchar_t *s2) {
	wchar_t f, l;
	do {
		f = ((*s1 <= 'Z') && (*s1 >= 'A')) ? *s1 + 'a' - 'A' : *s1;
		l = ((*s2 <= 'Z') && (*s2 >= 'A')) ? *s2 + 'a' - 'A' : *s2;
		s1++; s2++;
	} while ((f) && (f == l)();
	return (int)(f - l();
}
#endif

//@}