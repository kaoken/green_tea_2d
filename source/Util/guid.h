/*! @file  guid.h
* @brief MetalCube.h�t�@�C��������Ăяo�����̂ŁA�ق�����Ăяo���Ȃ��悤�ɁI
*  GUID������
* @author kaoken
* @date 2014/03/19 �쐬�J�n
*/
#pragma once
#include <Core/greenTea2D.h>


//------------------------------------------------------------
//! @brief GUID�����\�b�h�݂̂Ŋg��
//! �O���[�o����ӎ��ʎq
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

	//! �R���X�g���N�^
	gt2GUID()
	{
		Set(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	}

	//! �R���X�g���N�^
	gt2GUID(const gt2GUID &r)
	{
		*this = r;
	}
#if defined(_WIN32) || defined(_WIN64)
	//! �R���X�g���N�^
	gt2GUID(const GUID &r)
	{
		std::memcpy(this, &r, sizeof(GUID));
	}
#endif
	//! �R���X�g���N�^
	gt2GUID(uint32_t d1, uint16_t d2, uint16_t d3,
		uint8_t d4_1, uint8_t d4_2, uint8_t d4_3, uint8_t d4_4,
		uint8_t d4_5, uint8_t d4_6, uint8_t d4_7, uint8_t d4_8)
	{
		Set(d1, d2, d3, d4_1, d4_2, d4_3, d4_4, d4_5, d4_6, d4_7, d4_8);
	}

#if defined(_WIN32) || defined(_WIN64)
	//! @name ������Z�q
	//@{
	inline gt2GUID& operator = (const GUID& r)
	{
		std::memcpy(this, &r, sizeof(GUID));
	}
	//@}
#endif
	//! @name ��r���Z�q
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
	* �w�肵�������ƃo�C�g���g�p���āAGuid �\���̂̒l���Z�b�g����
	* @param [in] d1    GUID �̍ŏ��� 4 �o�C�g�B
	* @param [in] d2    GUID �̎��� 2 �o�C�g�B
	* @param [in] d3    GUID �̎��� 2 �o�C�g�B
	* @param [in] d4_1  GUID �̎��̃o�C�g�B
	* @param [in] d4_2  GUID �̎��̃o�C�g�B
	* @param [in] d4_3  GUID �̎��̃o�C�g�B
	* @param [in] d4_4  GUID �̎��̃o�C�g�B
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
	//! �������̂܂܂��H
	inline bool IsZero() { return  a[0] == 0 && a[1] == 0; }

	/**
		* GUID�𕶎���Ŏ擾����
		* @return GUID�𕶎����Ԃ�
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
