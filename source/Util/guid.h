/*! @file  guid.h
* @brief MetalCube.hファイル内から呼び出されるので、ほかから呼び出さないように！
*  GUIDを扱う
* @author kaoken
* @date 2014/03/19 作成開始
*/
#pragma once
#include <Core/greenTea2D.h>


//------------------------------------------------------------
//! @brief GUIDをメソッドのみで拡張
//! グローバル一意識別子
//------------------------------------------------------------
struct gt2GUID
{
	union {
		struct {
			uint32_t	Data1;
			uint16_t	Data2;
			uint16_t	Data3;
			uint8_t	Data4[8];
		};
		struct {
			uint64_t a[2];
		};
	};

	//! コンストラクタ
	gt2GUID()
	{
		Set(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	}

	//! コンストラクタ
	gt2GUID(const gt2GUID &r)
	{
		*this = r;
	}
#if defined(_WIN32) || defined(_WIN64)
	//! コンストラクタ
	gt2GUID(const GUID &r)
	{
		std::memcpy(this, &r, sizeof(GUID));
	}
#endif
	//! コンストラクタ
	gt2GUID(uint32_t d1, uint16_t d2, uint16_t d3,
		uint8_t d4_1, uint8_t d4_2, uint8_t d4_3, uint8_t d4_4,
		uint8_t d4_5, uint8_t d4_6, uint8_t d4_7, uint8_t d4_8)
	{
		Set(d1, d2, d3, d4_1, d4_2, d4_3, d4_4, d4_5, d4_6, d4_7, d4_8);
	}

#if defined(_WIN32) || defined(_WIN64)
	//! @name 代入演算子
	//@{
	inline gt2GUID& operator = (const GUID& r)
	{
		std::memcpy(this, &r, sizeof(GUID));
	}
	//@}
#endif
	//! @name 比較演算子
	//@{
	inline bool operator == (const gt2GUID& r) const
	{
		return a[0] == r.a[0] && a[1] == r.a[1];
	}
	inline bool operator != (const gt2GUID& r) const
	{
		return !(*this == r);
	}
	inline bool operator > (const gt2GUID &r) const {
		if (a[0] > r.a[0]) return true;
		else if (a[0] == r.a[0]) {
			if (a[1] > r.a[1]) return true;
		}
		return false;
	}
	inline bool operator >= (const gt2GUID &r) const {
		if (a[0] > r.a[0]) return true;
		else if (a[0] == r.a[0]) {
			if (a[1] >= r.a[1]) return true;
		}
		return false;
	}
	inline bool operator < (const gt2GUID &r) const {
		if (a[0] < r.a[0]) return true;
		else if (a[0] == r.a[0]) {
			if (a[1] < r.a[1]) return true;
		}
		return false;
	}
	inline bool operator <= (const gt2GUID &r) const {
		if (a[0] < r.a[0]) return true;
		else if (a[0] == r.a[0]) {
			if (a[1] <= r.a[1]) return true;
		}
		return false;
	}
	//@}

	/**
	* 指定した整数とバイトを使用して、Guid 構造体の値をセットする
	* @param [in] d1    GUID の最初の 4 バイト。
	* @param [in] d2    GUID の次の 2 バイト。
	* @param [in] d3    GUID の次の 2 バイト。
	* @param [in] d4_1  GUID の次のバイト。
	* @param [in] d4_2  GUID の次のバイト。
	* @param [in] d4_3  GUID の次のバイト。
	* @param [in] d4_4  GUID の次のバイト。
	*/
	inline void Set(uint32_t d1, uint16_t d2, uint16_t d3,
		uint8_t d4_1, uint8_t d4_2, uint8_t d4_3, uint8_t d4_4,
		uint8_t d4_5, uint8_t d4_6, uint8_t d4_7, uint8_t d4_8)
	{
		Data1 = d1;
		Data2 = d2;
		Data3 = d3;
		Data4[0] = d4_1; Data4[1] = d4_2; Data4[2] = d4_3; Data4[3] = d4_4;
		Data4[4] = d4_5; Data4[5] = d4_6; Data4[6] = d4_7; Data4[7] = d4_8;
	}
	//! 初期化のままか？
	inline bool IsZero() { return  a[0] == 0 && a[1] == 0; }

	/**
		* GUIDを文字列で取得する
		* @return GUIDを文字列を返す
		*/
	inline TString GetStrID()const
	{
		TChar szTmp[256];
		gt2_sprintf(szTmp, _T("{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}"),
			Data1,
			Data2,
			Data3,
			Data4[0], Data4[1],
			Data4[2], Data4[3], Data4[4], Data4[5], Data4[6], Data4[7]
			);
		return TString(szTmp);
	}
};
struct gt2GUID_less
{
	bool operator () (const gt2GUID &l, const gt2GUID &r) const
	{
		return l < r;
	}
};
