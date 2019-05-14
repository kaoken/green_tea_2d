//-----------------------------------------------------------------------------------
// �t�@�C���F gt2Sphere.h, gt2Sphere.inl
//
// ���@���@�F
// �@���̊֘A
//�@
// ���@���@�F
// �@2007/10/02 Ver.0.1 ����J�n
//
//
// ��@��@�F
// �@Copyright(c)2006 METAL CUBE All rights reserved worldwide..
// �@
//-----------------------------------------------------------------------------------
#pragma once
#include <Math/matrix.h>
//---------------------------------------
//! @brief ���� @n
//! �̈� R = { (x, y, z) | (x-c.x)^2 + (y-c.y)^2 + (z-c.z)^2 <= r^2 }
//---------------------------------------
struct gt2Sphere {
	gt2Vector3	c;	//!< ���̒��S
	float		r;	//!< ���̔��a
public:
	//-----------------------------------------------------------------------------------
	//! @brief �R���X�g���N�^
	//-----------------------------------------------------------------------------------
	inline gt2Sphere() {
		Init();
	}
	//-----------------------------------------------------------------------------------
	//! @brief �R���X�g���N�^
	//! @param [in]  rC      �ʒu
	//! @param [in]  radius  ���a
	//-----------------------------------------------------------------------------------
	inline gt2Sphere(const gt2Vector3 &rC, float radius) { Set(rC, radius); }
	//-----------------------------------------------------------------------------------
	//! @brief �R���X�g���N�^
	//! @param [in]  x      �ʒu x
	//! @param [in]  y      �ʒu y
	//! @param [in]  z      �ʒu z
	//! @param [in]  radius  ���a
	//-----------------------------------------------------------------------------------
	inline gt2Sphere(float x, float y, float z, float radius) { Set(x, y, z, radius); }

	//-----------------------------------------------------------------------------------
	//! @brief ���̂��Z�b�g����
	//! @param [in]  r      ����
	//! @return ����
	//-----------------------------------------------------------------------------------
	inline void Set(const gt2Sphere &r)
	{
		*this = r;
	}
	//-----------------------------------------------------------------------------------
	//! @brief �ʒu�ƁA���a���Z�b�g����
	//! @param [in]  rC      �ʒu
	//! @param [in]  radius  ���a
	//! @return ����
	//-----------------------------------------------------------------------------------
	inline void Set(const gt2Vector3 &rC, float radius)
	{
		c = rC; r = radius;
	}
	//-----------------------------------------------------------------------------------
	//! @brief �ʒu�ƁA���a���Z�b�g����
	//! @param [in]  rC      �ʒu
	//! @param [in]  radius  ���a
	//! @return ����
	//-----------------------------------------------------------------------------------
	inline void Set(float x, float y, float z, float radius)
	{
		c = gt2Vector3(x, y, z); r = radius;
	}

	//! @name ������Z�q
	//@{
	inline gt2Sphere& operator += (const gt2Vector3& v)
	{
		c += v;
		return *this;
	}

	inline gt2Sphere& operator -= (const gt2Vector3& v)
	{
		c -= v;
		return *this;
	}

	inline gt2Sphere& operator *= (const gt2Vector3& v)
	{
		c *= v;
		return *this;
	}

	inline gt2Sphere& operator /= (const gt2Vector3& v)
	{
		c /= v;
		return *this;
	}
	//@}

	//! @name �P���Z�q
	//@{
	inline gt2Sphere operator + () const
	{
		return *this;
	}
	inline gt2Sphere operator - () const
	{
		return gt2Sphere(-c, r);
	}
	//@}


	//! @name �񍀉��Z�q
	//@{
	inline gt2Sphere operator + (const gt2Vector3& v) const
	{
		gt2Sphere tmp;
		tmp.c = c + v;
		return tmp;
	}

	inline gt2Sphere operator - (const gt2Vector3& v) const
	{
		gt2Sphere tmp;
		tmp.c = c - v;
		return tmp;
	}

	inline gt2Sphere operator * (const gt2Vector3& v) const
	{
		gt2Sphere tmp;
		tmp.c = c * v;
		return tmp;
	}

	inline gt2Sphere operator / (const gt2Vector3& v) const
	{
		gt2Sphere tmp;
		tmp.c = c / v;
		return tmp;
	}
	//@}

	//! @name ��r���Z�q
	//@{
	inline bool operator == (const gt2Sphere& v) const
	{
		return c == v.c && r == v.r;
	}
	inline bool operator != (const gt2Sphere& v) const
	{
		return c != v.c || r != v.r;
	}
	//@}

	//-----------------------------------------------------------------------------------
	//! @brief ����r = p + td, |vD| = 1����s�ɑ΂��Č������Ă��邩�ǂ����B
	//! @param [in]  rvP  ��_
	//! @param [in]  vD  �����x�N�g��
	//! @param [in]  rS   �ΏۂƂ��鋅��
	//! @param [out] pT   0������Tmax
	//! @param [out] pQ   ���������ʒu
	//! @return �������Ă���ꍇ�A�������Ă���*pT�̒l����ь����_*pQ��Ԃ�
	//-----------------------------------------------------------------------------------
	static inline bool IntersectRaySphere(const gt2Vector3& rvP, const gt2Vector3& vD, const gt2Sphere& rS, float *pT, gt2Vector3 *pQ)
	{
		gt2Vector3 vM = rvP - rS.c;
		float fB = vM.Dot(vD);
		float fC = vM.Dot() - rS.r * rS.r;
		// r�̌��_��*rS�̊O���ɂ���(c > 0)�Ar��*rS���痣��Ă����������w���Ă���ꍇ(fB > 0)�ɏI��
		if (fC > 0.0f && fB > 0.0f) return false;
		float fDiscr = fB*fB - fC;
		// ���̔��ʎ��͌����������O��Ă��邱�ƂɈ�v
		if (fDiscr < 0.0f) return 0;
		// ����Ō����͋��ƌ������Ă��邱�Ƃ�������A��������ŏ��̒l*pT���v�Z
		*pT = -fB - (float)sqrt(fDiscr);
		// *pT�����ł���ꍇ�A�����͋��̓�������J�n���Ă���̂�*pT���[���ɃN�����v
		if (*pT < 0.0f) *pT = 0.0f;
		*pQ = rvP + *pT * vD;
		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief ����r = p + td����s�ƌ������Ă��邩�ǂ����𔻒�
	//! @param [in] rvP  ��_
	//! @param [in] vD  �����x�N�g��
	//! @param [in] rS   �ΏۂƂ��鋅��
	//! @return �������Ă���ꍇ�Atrue�Ԃ�
	//-----------------------------------------------------------------------------------
	static inline bool RaySphere(const gt2Vector3& rvP, const gt2Vector3& vD, const gt2Sphere& rS)
	{
		gt2Vector3 vM = rvP - rS.c;
		float fC = vM.Dot() - rS.r * rS.r;
		// ���Ȃ��Ƃ�1�̎����������݂��Ă���ꍇ�A�������Ă���
		if (fC <= 0.0f) return true;
		float fB = vM.Dot(vD);
		// �����̌��_�����̊O���ɂ�������������痣�ꂽ�������w���Ă���ꍇ�ɂ͑����ɏI��
		if (fB > 0.0f) return false;
		float fDiscr = fB*fB - fC;
		// ���̔��ʎ��͌����������O��Ă��邱�ƂɈ�v
		if (fDiscr < 0.0f) return false;
		// ����Ō����͋��ƌ������Ă���
		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief ���@�� ���ɂ�邠���蔻��
	//! @param [in] pA gt2Sphere�|�C���^
	//! @param [in] pB gt2Sphere�|�C���^
	//! @return �d�Ȃ��Ă���ꍇ�� true��Ԃ��A �d�Ȃ��Ă��Ȃ��ꍇ��false��Ԃ�
	//-----------------------------------------------------------------------------------
	static inline bool SphereSphere(const gt2Sphere& rA, const gt2Sphere& rB)
	{
		gt2Vector3 v;
		// ���S�Ԃ̋����̕������v�Z
		v = rA.c - rB.c;

		// �������������������������a�����������ꍇ�ɋ��͌������Ă���
		float fRadiusSum = rA.r + rB.r;
		return v.Dot() <= (fRadiusSum*fRadiusSum);
	}




	//-----------------------------------------------------------------------------------
	//! @brief ������
	//-----------------------------------------------------------------------------------
	inline void Init() {
		c.Init();
		r = 0.0f;
	}
	//-----------------------------------------------------------------------------------
	//! @brief ���@�� ���ɂ�邠���蔻��
	//! @param [in] sphere gt2Sphere
	//! @return �d�Ȃ��Ă���ꍇ�� true��Ԃ��A �d�Ȃ��Ă��Ȃ��ꍇ��false��Ԃ�
	//-----------------------------------------------------------------------------------
	inline bool SphereSphere(const gt2Sphere& sphere) const
	{
		return SphereSphere(*this, sphere);
	}
	//-----------------------------------------------------------------------------------
	//! @brief ����r = p + td, |vD| = 1����s�ɑ΂��Č������Ă��邩�ǂ����B
	//! @param [in]  rvP  ��_
	//! @param [in]  vD  �����x�N�g��
	//! @param [out] pT   0������Tmax
	//! @param [out] pQ   ���������ʒu
	//! @return �������Ă���ꍇ�A�������Ă���*pT�̒l����ь����_*pQ��Ԃ�
	//-----------------------------------------------------------------------------------
	inline bool IntersectRaySphere(const gt2Vector3& rvP, const gt2Vector3& vD, float *pT, gt2Vector3 *pQ) const
	{
		return IntersectRaySphere(rvP, vD, *this, pT, pQ);
	}
	//-----------------------------------------------------------------------------------
	//! @brief ����r = p + td, |vD| = 1����s�ɑ΂��Č������Ă��邩�ǂ����B
	//! @param [in]  rvP  ��_
	//! @param [in]  vD  �����x�N�g��
	//! @param [out] rT   0������Tmax
	//! @param [out] rQ   ���������ʒu
	//! @return �������Ă���ꍇ�A�������Ă���*pT�̒l����ь����_*pQ��Ԃ�
	//-----------------------------------------------------------------------------------
	inline bool IntersectRaySphere(const gt2Vector3& rvP, const gt2Vector3& vD, float &rT, gt2Vector3 &rQ) const
	{
		return this->IntersectRaySphere(rvP, vD, &rT, &rQ);
	}
	//-----------------------------------------------------------------------------------
	//! @brief ����r = p + td����s�ƌ������Ă��邩�ǂ����𔻒�
	//! @param [in] rvP ��_
	//! @param [in] vD �����x�N�g��
	//! @return �������Ă���ꍇ�Atrue�Ԃ�
	//-----------------------------------------------------------------------------------
	inline bool RaySphere(const gt2Vector3& rvP, const gt2Vector3& vD) const
	{
		return RaySphere(rvP, vD, *this);
	}
	//-----------------------------------------------------------------------------------
	// [ ���� ] public
	//  vD�̕����Ɏ��ԊԊufT0 <= *pfT <= fT1�̊Ԃ����^�����Ă��鋅 s0
	//  s0�i���̋��́j
	// [ ���� ]
	//  vD	�F[in] s0�̕����x�N�g��
	//  fT0	�F[in] �ŏ�����
	//  fT1	�F[in] �ő厞��
	//  s1	�F[in] ���̂P
	//  pfT	�F[out] ���Ԃ�Ԃ�
	// [ �߂�l ]
	//  �Î~���Ă��鋅s1�ɑ΂��Č����B������������ΏՓ˂̎���*pfT��Ԃ�
	//-----------------------------------------------------------------------------------
	bool MovingSphereSphereTime(const gt2Vector3& vD, float fT0, float fT1, const gt2Sphere& s1, float *pfT) const
	{
		// ���ԊԊufT0����fT1�܂ł̊ԂɁA*pS0�̉^�����Ă��鋅�̋��E���v�Z
		gt2Sphere b;
		float fMid = (fT0 + fT1) * 0.5f;
		b.c = this->c + vD * fMid;
		b.r = (fMid - fT0) * vD.Length() + this->r;
		// ���E����s1�Əd�Ȃ�Ȃ��ꍇ�A�]���Ă��̎��ԊԊu�ł͏Փ˂͂Ȃ��B
		if (!b.SphereSphere(s1)) return false;

		// �Փ˂����O���邱�Ƃ͂ł��Ȃ��B��萸���Ȕ���̂��߂ɍċA�I�ɔ��肪�s����A
		// �ċA���~���邽�߂ɁA���ԊԊu���\���ɏ������Ȃ������ɏՓ˂����肳���
		if (fT1 - fT0 < 0.0001f) {
			*pfT = fT0;
			return true;
		}

		// �Ԋu�̑O�������̔����ɂ����锻����ċA�I�ɍs���A�Փ˂����m���ꂽ�ꍇ�͖߂�
		if (this->MovingSphereSphereTime(vD, fT0, fMid, s1, pfT)) return true;

		// �Ԋu�̌㔼�����̔����ɂ����锻����ċA�I�ɍs��
		return this->MovingSphereSphereTime(vD, fMid, fT1, s1, pfT);
	}
	bool MovingSphereSphereTime(const gt2Vector3& vD, float fT0, float fT1, const gt2Sphere& s1, float &outT) const 
	{
		return this->MovingSphereSphereTime(vD, fT0, fT1, s1, &outT);
	}
	//-----------------------------------------------------------------------------------
	// [ ���� ] public
	//  �����Ă��鋅�̂̓����蔻��
	// [ ���� ]
	//  ���̂O(this)
	//  v0	�F[in] ����(s0)���̂̃x���V�e�B�[
	//  s1	�F[in] ���̂P
	//  v1	�F[in] s1�̋��̂̃x���V�e�B�[
	//  pfT	�F[out] ����
	// [ �߂�l ]
	//  �Î~���Ă��鋅 s1 �ɑ΂��Č������Ă���ꍇ��true��Ԃ��A�Փ˂̎���*pfT���Ԃ�
	//-----------------------------------------------------------------------------------
	bool MovingSphereSphere(const gt2Vector3& v0, const gt2Sphere& s1, const gt2Vector3& v1, float *pfT) const
	{
		// ��s1��s0�̔��a�ɂ܂Ŋg��
		gt2Sphere S1Ex = s1;
		S1Ex.r += this->r;
		// s0�����s1�̗�������s1�̉^���������Z���As1��Î~������
		gt2Vector3 v = v0 - v1;
		// ����ŁA�����̂������ s = s0.c + tv, v = (v0-v1)/||v0-v1|| ��
		// �g���������ɑ΂��Č��������邱�Ƃ��ł���
		gt2Vector3 vQ;
		float fVLen = v.Length();
		v /= fVLen;
		if (S1Ex.IntersectRaySphere(this->c, v, pfT, &vQ)) {
			return *pfT <= fVLen;
		}
		return 0;
	}
	bool MovingSphereSphere(const gt2Vector3& v0, const gt2Sphere& s1, const gt2Vector3& v1, float &outT) const
	{
		return this->MovingSphereSphere(v0, s1, v1, &outT);
	}
};