/*!
Copyright (c) 2013 METAL CUBE

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software. If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.

3. This notice may not be removed or altered from any source
distribution.
@file plane.h
@brief ���ʂ������\����
*/
#pragma once

#include <Math/vector.h>


//-------------------------------------------------------
//! @brief ���ʂɑ΂��āA�_�̈ʒu��\��
//-------------------------------------------------------
enum POSITION_PLANE_POINT
{
	POINT_IN_FRONT_OF_PLANE = 1,	//!< ���ʂ̑O�ɓ_������
	POINT_BEHIND_PLANE,			//!< ���ʂ̌��ɓ_������
	POINT_ON_PLANE,				//!< ���ʂɂ܂������Ă���
};

//-------------------------------------------------------
//! @brief ���ʔ���� 2����
//-------------------------------------------------------
struct gt2Plane2 {
	union {
		struct {
			gt2Vector2	vNormal;		//!< ���ʂ̖@���B���ʏ�̓_x�ɑ΂���Dot(n,x) = d������
			float		distance;		//!< ���ʏ�̂���^����ꂽ�_p�ɑ΂���d = Dot(n,p)������
		};
		struct {
			float a, b, d;
		};
		float v[3];
	};
public:
	//! @name �R���X�g���N�^
	//@{

	gt2Plane2()
	{
		this->Init();
	}

	gt2Plane2(const gt2Plane2 &p)
	{
		*this = p;
	}

	gt2Plane2(const float fa, const float fb, const float fd)
	{
		Set(fa, fb, fd);
	}

	gt2Plane2(const gt2Vector2& rV2, const float fd)
	{
		Set(rV2, fd);
	}

	gt2Plane2(const gt2Vector2& rvOrigin, const gt2Vector2& rvNormal)
	{
		Set(rvOrigin, rvNormal);
	}
	//@}

	//------------------------------------------------------------------------
	//
	//! @name �L���X�g���Z�q
	//
	//------------------------------------------------------------------------
	//@{
	operator float* ()
	{
		return (float *)&a;
	}

	operator const float* () const
	{
		return (const float *)&a;
	}
	//@}


	//------------------------------------------------------------------------
	//
	//! @name ������Z�q
	//
	//------------------------------------------------------------------------
	//@{
	gt2Plane2& operator = (const gt2Plane2 &p)
	{
		this->Set(p.a, p.b, p.d);
		return *this;
	}

	gt2Plane2& operator *= (float f)
	{
		a *= f;
		b *= f;
		d *= f;
		return *this;
	}

	gt2Plane2& operator /= (float f)
	{
		float fInv = 1.0f / f;
		a *= fInv;
		b *= fInv;
		d *= fInv;
		return *this;
	}
	//@}


	//------------------------------------------------------------------------
	//
	//! @name �P�����Z�q
	//
	//------------------------------------------------------------------------
	//@{
	gt2Plane2 operator + () const
	{
		return gt2Plane2(*this);
	}

	gt2Plane2 operator - () const
	{
		return gt2Plane2(-a, -b, -d);
	}
	//@}


	//------------------------------------------------------------------------
	//
	//! @name 2 �����Z�q
	//
	//------------------------------------------------------------------------
	//@{
	gt2Plane2 operator * (float f) const
	{
		return gt2Plane2(a * f, b * f, d * f);
	}

	gt2Plane2 operator / (float f) const
	{
		float fInv = 1.0f / f;
		return gt2Plane2(a * fInv, b * fInv, d * fInv);
	}

	friend gt2Plane2 operator * (float f, const gt2Plane2& p)
	{
		return gt2Plane2(f * p.a, f * p.b, f * p.d);
	}

	bool operator == (const gt2Plane2& p) const
	{
		return a == p.a && b == p.b && d == p.d;
	}

	bool operator != (const gt2Plane2& p) const
	{
		return a != p.a || b != p.b || d != p.d;
	}
	//@}

	//-----------------------------------------------------------------------------------
	//! @brief a,b,d�̒l���Z�b�g����
	//! @param [in] fa �la
	//! @param [in] fb �lb
	//! @param [in] fd �ld
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	void Set(float fa, float fb, float fd)
	{
		a = fa;
		b = fb;
		d = fd;
	}
	//-----------------------------------------------------------------------------------
	//! @brief v2, d�̒l���Z�b�g����
	//! @param [in] rV2 2�v�f�x�N�g��
	//! @param [in] fd �ld
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	void Set(const gt2Vector2& rV2, const float fd)
	{
		vNormal = rV2;
		d = fd;
	}

	//-----------------------------------------------------------------------------------
	//! @brief ��_�Ɩ@������Z�b�g����
	//! @param [in] rvOrigin ��_
	//! @param [in] rvNormal �@��
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	void Set(const gt2Vector2& rvOrigin, const gt2Vector2& rvNormal)
	{
		vNormal = rvNormal;
		d = vNormal.x*rvOrigin.x + vNormal.y*rvOrigin.y;
	}

	//-----------------------------------------------------------------------------------
	//! @brief �^����ꂽ���݂̃C�v�V�����ɂ����݂̂��镽�ʂɑ΂��ē_vP�𕪗�
	//! @param [in] vP ��_
	//! @param [in] fPlaneThicknessEpsilon �C�v�V�����l
	//! @return ���ʂɑ΂��Ă̓_�̈ʒu��Ԃ�
	//-----------------------------------------------------------------------------------
	POSITION_PLANE_POINT ClassifyPointToPlane(const gt2Vector2 &vP, float fPlaneThicknessEpsilon) const
	{
		//================================
		// �_�̕��ʂ���̕����t�������v�Z
		//================================
		float fDist = this->DistanceTo(vP);

		//================================
		// �����t��������ɂ���vP�𕪗�
		//================================
		if (fDist > fPlaneThicknessEpsilon) {
			// ���ʂ̌����̃C�v�V�����l���傫������
			return POINT_IN_FRONT_OF_PLANE;
		}
		else if (fDist < -fPlaneThicknessEpsilon) {
			// ���ʂ̌����̃C�v�V�����l��菬��������
			return POINT_BEHIND_PLANE;
		}

		return POINT_ON_PLANE;
	}
	//-----------------------------------------------------------------------------------
	//! @brief ���ʂɑ΂���rvPoint�̓_�𐂒��ˉe�����Ƃ��̓_�Ƃ̑傫��pT��Ԃ�@n
	//!  �߂�l���}�C�i�X�̏ꍇ�͗��ʁA�v���X�̎��͕\�ʂɓ_rvPoint������@n
	//!  ���ʂ̖@���͐��K������Ă��镨�Ƃ���B
	//! @param [in] rvPoint �����ˉe����_
	//! @return ���ʂ���w�肵���_�܂ł̋���
	//-----------------------------------------------------------------------------------
	float DistanceTo(const gt2Vector2& rvPoint) const
	{
		return vNormal.Dot(rvPoint) - distance;
	}

	//-----------------------------------------------------------------------------------
	//! @brief ���ʂɑ΂���pvPoint�̓_�𐂒��ˉe�����Ƃ��̓_pOut���o�͂���@n
	//! ���ʂ̖@���͐��K������Ă��镨�Ƃ���B
	//! @param [in] rV �����ˉe����_
	//! @return ���ʂ���w�肵���_�܂ł̋���
	//-----------------------------------------------------------------------------------
	gt2Vector2 GetClosestPtPoint(const gt2Vector2& rvPoint) const
	{
		return rvPoint - (vNormal.Dot(rvPoint) - distance) * vNormal;
	}


	//-----------------------------------------------------------------------------------
	//! @brief �\�ʂɌ����Ă��邩�H
	//! @param [in] rN �@��
	//! @return ���������݂��Ȃ��ꍇ��false��Ԃ��B
	//-----------------------------------------------------------------------------------
	bool IsFrontFacingTo(const gt2Vector2& rN) const
	{
		return vNormal.Dot(rN) <= 0.0f;
	}
	//-----------------------------------------------------------------------------------
	//! @brief ����������B
	//! @return ����
	//-----------------------------------------------------------------------------------
	void Init()
	{
		a = b = d = 0;
	}
	//-----------------------------------------------------------------------------------
	//! @brief ���K������
	//! @return ����
	//-----------------------------------------------------------------------------------
	void Normalize()
	{
		float f = 1.0f / vNormal.Length();
		assert(f != 0.0f);

		if (f) {
			vNormal *= f;  distance *= f;
		}
	}


	//-----------------------------------------------------------------------------------
	//! @brief ��(vA, vB)�͕���(this)���܂����ł������_���o��
	//! @param [in]  a  �n�_
	//! @param [in]  rvB  �I�_
	//! @param [out] pOut �����_
	//! @return �����_�̒l���擾�ł����ꍇtrue��Ԃ��B�����łȂ����false��Ԃ�
	//-----------------------------------------------------------------------------------
	bool IntersectEdgeAgainst(const gt2Vector2 &a, const gt2Vector2 &rvB, gt2Vector2* pOut) const
	{
		gt2Vector2 vRet;
		float fT;

		return this->IntersectSegment(a, rvB, &fT, pOut);
	}
	//-----------------------------------------------------------------------------------
	//! @brief ��(vA, vB)�͕���(this)���܂����ł������_���o��
	//! @param [in]  a  �n�_
	//! @param [in]  rvB  �I�_
	//! @param [out] rOut �����_
	//! @return �����_�̒l���擾�ł����ꍇtrue��Ԃ��B�����łȂ����false��Ԃ�
	//-----------------------------------------------------------------------------------
	bool IntersectEdgeAgainst(const gt2Vector2 &a, const gt2Vector2 &rvB, gt2Vector2& rOut) const
	{
		return this->IntersectEdgeAgainst(a, rvB, &rOut);
	}


	//-----------------------------------------------------------------------------------
	//! @brief ����AB������p(this)�ƌ������Ă��邩�ǂ����𔻒�B�������Ă���Ό����_��Ԃ�
	//! @param [in]  a  �n�_
	//! @param [in]  rvB  �I�_
	//! @param [out] pT  ���ʂƌ�����������̂��钼��ab�ƌ�������l
	//! @param [out] pOut �����_
	//! @return �����̒lt����ь����_Q�ƂƂ���true��Ԃ��B�����łȂ����false��Ԃ�
	//-----------------------------------------------------------------------------------
	bool IntersectSegment(const gt2Vector2 &a, const gt2Vector2 &rvB, float *pT, gt2Vector2 *pOut) const
	{
		// ���ʂƌ�����������̂��钼��ab�ƌ�������t�̒l���v�Z
		gt2Vector2 vAB = rvB - a;
		*pT = (distance - vNormal.Dot(a)) / vNormal.Dot(vAB);

		// t��[0..1]�̒��ɂ���ꍇ�A�����_���v�Z���ĕԂ�
		if (*pT >= 0.0f && *pT <= 1.0f) {
			*pOut = a + (vAB * *pT);
			return true;
		}
		// �����łȂ��ꍇt��+INF, -INF, NaN, ���邢��[0..1]�̒��ɂ͂Ȃ��̂ŁA�����Ȃ�
		return false;
	}
	//-----------------------------------------------------------------------------------
	//! @brief ����AB������p(this)�ƌ������Ă��邩�ǂ����𔻒�B�������Ă���Ό����_��Ԃ�
	//! @param [in]  a  �n�_
	//! @param [in]  rvB  �I�_
	//! @param [out] rT   ���ʂƌ�����������̂��钼��ab�ƌ�������l
	//! @param [out] rOut �����_
	//! @return �����̒lt����ь����_Q�ƂƂ���true��Ԃ��B�����łȂ����false��Ԃ�
	//-----------------------------------------------------------------------------------
	bool IntersectSegment(const gt2Vector2 &a, const gt2Vector2 &rvB, float &rT, gt2Vector2& rOut) const
	{
		return this->IntersectSegment(a, rvB, &rT, &rOut);
	}


	//-----------------------------------------------------------------------------------
	//! @brief ����AB������p(this)�ƌ������Ă��邩�ǂ����𔻒�B�������Ă���Ό����_��Ԃ�
	//! @param [in]  a      �n�_
	//! @param [in]  rV       �x���V�e�B�[
	//! @param [in]  fEpsilon ���ʂ̌���
	//! @param [out] pT       ���ʂƌ�����������̂��钼��ab�ƌ�������l
	//! @param [out] pOut     �����_
	//! @return �����̒lt����ь����_Q�ƂƂ���true��Ԃ��B�����łȂ����false��Ԃ�
	//-----------------------------------------------------------------------------------
	int IntersectLine(const gt2Vector2 &a, const gt2Vector2 &rV, float fEpsilon, float *pT, gt2Vector2 *pOut) const
	{
		// ���ʌ����_�̊Ԋu�𓾂�:
		// ���̈ʒu���畽�ʂ܂ł̋������v�Z���܂��B
		float signedDistToPlane = this->DistanceTo(a);
		// 
		float normalDotVelocity = vNormal.Dot(rV);
		// ���̂����ʂɕ��s���ɂȂ��Ă��邩�H:
		if (normalDotVelocity == 0.0f) {
			if (fabs(signedDistToPlane) >= fEpsilon) {
				// ����fEpsilon���̕��ʂɖ��ߍ��܂�Ă��Ȃ�
				// �Փ˂��ĂȂ�
				return 0;
			}
			// ���͕̂��ʂɖ��ߍ��܂�Ă��܂��B
			*pT = 0.0f;
			*pOut = this->GetClosestPtPoint(a);
			return 2;
		}
		else {
			// ���ʂƌ�����������̂��钼��ab�ƌ�������t�̒l���v�Z
			*pT = (distance - vNormal.Dot(a)) / vNormal.Dot(rV);

			// t��[0..1]�̒��ɂ���ꍇ�A�����_���v�Z���ĕԂ�
			if (*pT >= 0.0f && *pT <= 1.0f) {
				*pOut = a + (rV * *pT);
				return 1;
			}
			// �����łȂ��ꍇt��+INF, -INF, NaN, ���邢��[0..1]�̒��ɂ͂Ȃ��̂ŁA�����Ȃ�

		}
		return 0;
	}
	//-----------------------------------------------------------------------------------
	//! @brief ����AB������p(this)�ƌ������Ă��邩�ǂ����𔻒�B�������Ă���Ό����_��Ԃ�
	//! @param [in]  a      �n�_
	//! @param [in]  rV       �x���V�e�B�[
	//! @param [in]  fEpsilon ���ʂ̌���
	//! @param [out] rT       ���ʂƌ�����������̂��钼��ab�ƌ�������l
	//! @param [out] rOut     �����_
	//! @return �����̒lt����ь����_Q�ƂƂ���true��Ԃ��B�����łȂ����false��Ԃ�
	//-----------------------------------------------------------------------------------
	int IntersectLine(const gt2Vector2 &a, const gt2Vector2 &rV, float fEpsilon, float &rT, gt2Vector2 &rOut) const
	{
		return this->IntersectLine(a, rV, fEpsilon, &rT, &rOut);
	}

	//-----------------------------------------------------------------------------------
	//! @brief ����AB������p(this)�ƌ������Ă��邩�ǂ����𔻒�B�������Ă���Ό����_��Ԃ�
	//! @param [in]  a     �n�_
	//! @param [in]  rV      �x���V�e�B�[
	//! @param [out] pT      ���ʂƌ�����������̂��钼��ab�ƌ�������l
	//! @param [out] pOut    �����_
	//! @return �����̒lt����ь����_Q�ƂƂ���true��Ԃ��B�����łȂ����false��Ԃ�
	//-----------------------------------------------------------------------------------
	int IntersectLine(const gt2Vector2 &a, const gt2Vector2 &rV, float *pT, gt2Vector2 *pOut) const
	{
		// ���ʌ����_�̊Ԋu�𓾂�:
		// ���̈ʒu���畽�ʂ܂ł̋������v�Z���܂��B
		float signedDistToPlane = this->DistanceTo(a);
		// 
		float normalDotVelocity = vNormal.Dot(rV);
		// ���̂����ʂɕ��s���ɂȂ��Ă��邩�H:
		if (normalDotVelocity == 0.0f) {
			if (fabs(signedDistToPlane) != 0.0f) {
				// �Փ˂��ĂȂ�
				return 0;
			}
			// ���͕̂��ʂɖ��ߍ��܂�Ă��܂��B
			*pT = 0.0f;
			*pOut = this->GetClosestPtPoint(a);
			return 2;
		}
		else {
			// ���ʂƌ�����������̂��钼��ab�ƌ�������t�̒l���v�Z
			*pT = (distance - vNormal.Dot(a)) / vNormal.Dot(rV);

			// t��[0..1]�̒��ɂ���ꍇ�A�����_���v�Z���ĕԂ�
			if (*pT >= 0.0f && *pT <= 1.0f) {
				*pOut = a + (rV * *pT);
				return 1;
			}
			// �����łȂ��ꍇt��+INF, -INF, NaN, ���邢��[0..1]�̒��ɂ͂Ȃ��̂ŁA�����Ȃ�

		}
		return 0;
	}
	//-----------------------------------------------------------------------------------
	//! @brief ����AB������p(this)�ƌ������Ă��邩�ǂ����𔻒�B�������Ă���Ό����_��Ԃ�
	//! @param [in]  a      �n�_
	//! @param [in]  rV       �x���V�e�B�[
	//! @param [out] rT      ���ʂƌ�����������̂��钼��ab�ƌ�������l
	//! @param [out] rOut     �����_
	//! @return �����̒lt����ь����_Q�ƂƂ���true��Ԃ��B�����łȂ����false��Ԃ�
	//-----------------------------------------------------------------------------------
	int IntersectLine(const gt2Vector2 &a, const gt2Vector2 &rV, float &rT, gt2Vector2 &rOut) const
	{
		return this->IntersectLine(a, rV, &rT, &rOut);
	}
};











//-------------------------------------------------------
//! @brief ���ʔ���� 3����
//-------------------------------------------------------
struct gt2Plane3 {
	union {
		struct {
			gt2Vector3	vNormal;		//!< ���ʂ̖@���B���ʏ�̓_x�ɑ΂���Dot(n,x) = d������
			float		distance;		//!< ���ʏ�̂���^����ꂽ�_p�ɑ΂���d = Dot(n,p)������
		};
		struct {
			float a, b, c, d;
		};
		float v[4];
	};
public:
	//! @name �R���X�g���N�^
	//@{
	gt2Plane3()
	{
		this->Init();
	}

	gt2Plane3(const gt2Plane3 &p)
	{
		*this = p;
	}

	gt2Plane3(const float fa, const float fb, const float fc, const float fd)
	{
		a = fa;
		b = fb;
		c = fc;
		d = fd;
	}

	gt2Plane3(const gt2Vector3& rV3, const float fd)
	{
		vNormal = rV3;
		d = fd;
	}

	gt2Plane3(const gt2Vector3& rvOrigin, const gt2Vector3& rvNormal)
	{
		vNormal = rvNormal;
		d = vNormal.x*rvOrigin.x + vNormal.y*rvOrigin.y + vNormal.z*rvOrigin.z;
	}
	//@}

#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
	gt2Plane3&  operator= (const DirectX::XMVECTOR& vf) { a = vf.m128_f32[0]; b = vf.m128_f32[1]; c = vf.m128_f32[2]; d = vf.m128_f32[3]; return *this; }

	DirectX::XMVECTOR GetXMVECTOR() const { DirectX::XMVECTOR t; t.m128_f32[0] = a; t.m128_f32[1] = b; t.m128_f32[2] = c; t.m128_f32[3] = d; return t; }
#endif


	//------------------------------------------------------------------------
	//
	//! @name �L���X�g���Z�q
	//
	//------------------------------------------------------------------------
	//@{
	operator float* ()
	{
		return (float *)&a;
	}

	operator const float* () const
	{
		return (const float *)&a;
	}
	//@}

	//------------------------------------------------------------------------
	//
	//! @name ������Z�q
	//
	//------------------------------------------------------------------------
	//@{
	gt2Plane3& operator = (const gt2Plane3 &p)
	{
		this->Set(p.a, p.b, p.c, p.d);
		return *this;
	}

	gt2Plane3& operator *= (const float f)
	{
		a *= f;
		b *= f;
		c *= f;
		d *= f;
		return *this;
	}

	gt2Plane3& operator /= (const float f)
	{
		float fInv = 1.0f / f;
		a *= fInv;
		b *= fInv;
		c *= fInv;
		d *= fInv;
		return *this;
	}
	//@}


	//------------------------------------------------------------------------
	//
	//! @name �P�����Z�q
	//
	//------------------------------------------------------------------------
	//@{
	gt2Plane3 operator + () const
	{
		return gt2Plane3(*this);
	}
	gt2Plane3 operator - () const
	{
		return gt2Plane3(-a, -b, -c, -d);
	}
	//@}


	//------------------------------------------------------------------------
	//
	//! @name �񍀉��Z�q
	//
	//------------------------------------------------------------------------
	//@{
	gt2Plane3 operator * (const float f) const
	{
		return gt2Plane3(a * f, b * f, c * f, d * f);
	}

	gt2Plane3 operator / (const float f) const
	{
		float fInv = 1.0f / f;
		return gt2Plane3(a * fInv, b * fInv, c * fInv, d * fInv);
	}

	friend gt2Plane3 operator * (const float f, const gt2Plane3& p)
	{
		return gt2Plane3(f * p.a, f * p.b, f * p.c, f * p.d);
	}
	//@}

	//------------------------------------------------------------------------
	//
	//! @name ��r���Z�q
	//
	//------------------------------------------------------------------------
	//@{
	bool operator == (const gt2Plane3& p) const
	{
		return a == p.a && b == p.b && c == p.c && d == p.d;
	}

	bool operator != (const gt2Plane3& p) const
	{
		return a != p.a || b != p.b || c != p.c || d != p.d;
	}
	//@}


	//-----------------------------------------------------------------------------------
	//! @brief a,b,c,d�̒l���Z�b�g����
	//! @param [in] fa �la
	//! @param [in] fb �lb
	//! @param [in] fc �lc
	//! @param [in] fd �ld
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	void Set(float fa, float fb, float fc, float fd)
	{
		a = fa;
		b = fb;
		c = fc;
		d = fd;
	}
	//-----------------------------------------------------------------------------------
	//! @brief v3, d�̒l���Z�b�g����
	//! @param [in] rV3 3�v�f�x�N�g��
	//! @param [in] fd �ld
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	void Set(const gt2Vector3& rV3, const float fd)
	{
		vNormal = rV3;
		d = fd;
	}
	//-----------------------------------------------------------------------------------
	//! @brief ��_�Ɩ@������Z�b�g����
	//! @param [in] rvOrigin ��_
	//! @param [in] rvNormal �@��
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	void Set(const gt2Vector3& rvOrigin, const gt2Vector3& rvNormal)
	{
		vNormal = rvNormal;
		d = vNormal.x*rvOrigin.x + vNormal.y*rvOrigin.y + vNormal.z*rvOrigin.z;
	}

	//-----------------------------------------------------------------------------------
	//! @brief �^����ꂽ���݂̃C�v�V�����ɂ����݂̂��镽�ʂɑ΂��ē_vP�𕪗�
	//! @param [in] vP ��_
	//! @param [in] fPlaneThicknessEpsilon �C�v�V�����l
	//! @return ���ʂɑ΂��Ă̓_�̈ʒu��Ԃ�
	//-----------------------------------------------------------------------------------
	POSITION_PLANE_POINT ClassifyPointToPlane(const gt2Vector3 &vP, float fPlaneThicknessEpsilon) const
	{
		//================================
		// �_�̕��ʂ���̕����t�������v�Z
		//================================
		float fDist = vNormal.Dot(vP) - distance;

		//================================
		// �����t��������ɂ���vP�𕪗�
		//================================
		if (fDist > fPlaneThicknessEpsilon) {
			// ���ʂ̌����̃C�v�V�����l���傫������
			return POINT_IN_FRONT_OF_PLANE;
		}
		else if (fDist < -fPlaneThicknessEpsilon) {
			// ���ʂ̌����̃C�v�V�����l��菬��������
			return POINT_BEHIND_PLANE;
		}

		return POINT_ON_PLANE;
	}
	//-----------------------------------------------------------------------------------
	//! @brief ���ʂɑ΂���rvPoint�̓_�𐂒��ˉe�����Ƃ��̓_�Ƃ̑傫��pT��Ԃ�@n
	//!  �߂�l���}�C�i�X�̏ꍇ�͗��ʁA�v���X�̎��͕\�ʂɓ_rvPoint������@n
	//!  ���ʂ̖@���͐��K������Ă��镨�Ƃ���B
	//! @param [in] rvPoint �����ˉe����_
	//! @return ���ʂ���w�肵���_�܂ł̋���
	//-----------------------------------------------------------------------------------
	float DistanceTo(const gt2Vector3& rV) const
	{
		return vNormal.Dot(rV) - distance;
	}
	//-----------------------------------------------------------------------------------
	//! @brief ���ʂɑ΂���pvPoint�̓_�𐂒��ˉe�����Ƃ��̓_pOut���o�͂���@n
	//! ���ʂ̖@���͐��K������Ă��镨�Ƃ���B
	//! @param [in] rV �����ˉe����_
	//! @return ���ʂ���w�肵���_�܂ł̋���
	//-----------------------------------------------------------------------------------
	gt2Vector3 GetClosestPtPoint(const gt2Vector3& rvPoint) const
	{
		return rvPoint - (vNormal.Dot(rvPoint) - distance) * vNormal;
	}
	//-----------------------------------------------------------------------------------
	//! @brief ���̕��ʂɑ΂��Ă�����̕���rPlane�ɑ΂��āA�����̌����ł��钼��
	//!   L = pOutP + t * pOutN 
	//!  ���v�Z���A���������݂��Ȃ��ꍇ��false��Ԃ�
	//!  ���ʂ̖@���͐��K������Ă��镨�Ƃ���B
	//! @param [in]  rPlane ����
	//! @param [out] pOutN  ���������̕���
	//! @param [out] pOutP  ����������̓_�̈ʒu
	//! @return ���������݂��Ȃ��ꍇ��false��Ԃ��B
	//-----------------------------------------------------------------------------------
	bool IntersectPlanes(const gt2Plane3& rPlane, gt2Vector3* pOutN, gt2Vector3* pOutP) const
	{
		// ���������̕������v�Z
		*pOutN = vNormal.Cross(rPlane.vNormal);

		// pOutN���O�̏ꍇ�A���ʂ͕��s������Ă���
		// ���邢�͈�v���Ă���̂ŁA�������Ă���Ƃ͍l�����Ȃ�
		float fDenom = pOutN->Dot();
		if (fDenom < 0.0001f) return false;

		// ����������̓_�̈ʒu
		*pOutP = pOutN->Cross((distance*rPlane.vNormal - rPlane.d*vNormal));
		*pOutP /= fDenom;

		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief ���̕��ʂɑ΂��Ă�����̕���rPlane�ɑ΂��āA�����̌����ł��钼��
	//!   L = rOutPoint + t * rOutN 
	//!  ���v�Z���A���������݂��Ȃ��ꍇ��false��Ԃ�
	//!  ���ʂ̖@���͐��K������Ă��镨�Ƃ���B
	//! @param [in]  rPlane     ����
	//! @param [out] rOutN      ���������̕���
	//! @param [out] rOutPoint  ����������̓_�̈ʒu
	//! @return ���������݂��Ȃ��ꍇ��false��Ԃ��B
	//-----------------------------------------------------------------------------------
	bool IntersectPlanes(const gt2Plane3& rPlane, gt2Vector3& rOutN, gt2Vector3 &rOutPoint) const
	{
		return this->IntersectPlanes(rPlane, &rOutN, &rOutPoint);
	}

	//-----------------------------------------------------------------------------------
	//! @brief �\�ʂɌ����Ă��邩�H
	//! @param [in] rN �@��
	//! @return ���������݂��Ȃ��ꍇ��false��Ԃ��B
	//-----------------------------------------------------------------------------------
	bool IsFrontFacingTo(const gt2Vector3& rV) const
	{
		return vNormal.Dot(rV) <= 0.0f;
	}
	//-----------------------------------------------------------------------------------
	//! @brief ����������B
	//! @return ����
	//-----------------------------------------------------------------------------------
	void Init()
	{
		a = b = c = d = 0;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 3�̓��꒼����ɂȂ��_��(���v���̏���)�^����ꂽ�ꍇ�ɁA���ʂ̕��������v�Z
	//! @return ����
	//-----------------------------------------------------------------------------------
	void MakeComputePlane(const gt2Vector3 &vA, const gt2Vector3 &vB, const gt2Vector3 &vC)
	{
		vNormal = (vB - vA).Cross((vC - vA));

		vNormal.Normalize();
		distance = vNormal.Dot(vA);
	}
	//-----------------------------------------------------------------------------------
	//! @brief ���K������
	//! @return ����
	//-----------------------------------------------------------------------------------
	void Normalize()
	{
		float f = 1.0f / vNormal.Length();
#ifdef MC_DEBUG
		assert(f != 0.0f);
#endif

		if (f) {
			vNormal *= f;  distance *= f;
		}
	}
	//-----------------------------------------------------------------------------------
	//! @brief ��(vA, vB)�͕���(this)���܂����ł������_���o��
	//! @param [in]  a  �n�_
	//! @param [in]  rvB  �I�_
	//! @param [out] pOut �����_
	//! @return �����_�̒l���擾�ł����ꍇtrue��Ԃ��B�����łȂ����false��Ԃ�
	//-----------------------------------------------------------------------------------
	bool IntersectEdgeAgainst(const gt2Vector3 &a, const gt2Vector3 &rvB, gt2Vector3* pOut) const
	{
		gt2Vector3 vRet;
		float fT;

		return this->IntersectSegment(a, rvB, &fT, pOut);
	}
	//-----------------------------------------------------------------------------------
	//! @brief ��(vA, vB)�͕���(this)���܂����ł������_���o��
	//! @param [in]  a  �n�_
	//! @param [in]  rvB  �I�_
	//! @param [out] rOut �����_
	//! @return �����_�̒l���擾�ł����ꍇtrue��Ԃ��B�����łȂ����false��Ԃ�
	//-----------------------------------------------------------------------------------
	bool IntersectEdgeAgainst(const gt2Vector3 &a, const gt2Vector3 &rvB, gt2Vector3 &rOut) const
	{
		return this->IntersectEdgeAgainst(a, rvB, &rOut);
	}
	//-----------------------------------------------------------------------------------
	//! @brief ����AB������p(this)�ƌ������Ă��邩�ǂ����𔻒�B�������Ă���Ό����_��Ԃ�
	//! @param [in]  a  �n�_
	//! @param [in]  rvB  �I�_
	//! @param [out] pT  ���ʂƌ�����������̂��钼��ab�ƌ�������l
	//! @param [out] pOut �����_
	//! @return �����̒lt����ь����_Q�ƂƂ���true��Ԃ��B�����łȂ����false��Ԃ�
	//-----------------------------------------------------------------------------------
	bool IntersectSegment(const gt2Vector3 &a, const gt2Vector3 &rvB, float *pT, gt2Vector3 *pOut) const
	{
		// ���ʂƌ�����������̂��钼��ab�ƌ�������t�̒l���v�Z
		gt2Vector3 vAB = rvB - a;
		*pT = (distance - vNormal.Dot(a)) / vNormal.Dot(vAB);

		// t��[0..1]�̒��ɂ���ꍇ�A�����_���v�Z���ĕԂ�
		if (*pT >= 0.0f && *pT <= 1.0f) {
			*pOut = a + (vAB * *pT);
			return true;
		}
		// �����łȂ��ꍇt��+INF, -INF, NaN, ���邢��[0..1]�̒��ɂ͂Ȃ��̂ŁA�����Ȃ�
		return false;
	}
	//-----------------------------------------------------------------------------------
	//! @brief ����AB������p(this)�ƌ������Ă��邩�ǂ����𔻒�B�������Ă���Ό����_��Ԃ�
	//! @param [in]  a  �n�_
	//! @param [in]  rvB  �I�_
	//! @param [out] rT   ���ʂƌ�����������̂��钼��ab�ƌ�������l
	//! @param [out] rOut �����_
	//! @return �����̒lt����ь����_Q�ƂƂ���true��Ԃ��B�����łȂ����false��Ԃ�
	//-----------------------------------------------------------------------------------
	bool IntersectSegment(const gt2Vector3 &a, const gt2Vector3 &rvB, float &rT, gt2Vector3 &rOut) const
	{
		return this->IntersectSegment(a, rvB, &rT, &rOut);
	}


	//-----------------------------------------------------------------------------------
	//! @brief ����AB������p(this)�ƌ������Ă��邩�ǂ����𔻒�B�������Ă���Ό����_��Ԃ�
	//! @param [in]  a      �n�_
	//! @param [in]  rV       �x���V�e�B�[
	//! @param [in]  fEpsilon ���ʂ̌���
	//! @param [out] pT       ���ʂƌ�����������̂��钼��ab�ƌ�������l
	//! @param [out] pOut     �����_
	//! @return �����̒lt����ь����_Q�ƂƂ���true��Ԃ��B�����łȂ����false��Ԃ�
	//-----------------------------------------------------------------------------------
	int IntersectLine(const gt2Vector3 &a, const gt2Vector3 &rV, float fEpsilon, float *pT, gt2Vector3 *pOut) const
	{
		// ���ʌ����_�̊Ԋu�𓾂�:
		// ���̈ʒu���畽�ʂ܂ł̋������v�Z���܂��B
		float signedDistToPlane = this->DistanceTo(a);
		// 
		float normalDotVelocity = vNormal.Dot(rV);
		// ���̂����ʂɕ��s���ɂȂ��Ă��邩�H:
		if (normalDotVelocity == 0.0f) {
			if (fabs(signedDistToPlane) >= fEpsilon) {
				// ����fEpsilon���̕��ʂɖ��ߍ��܂�Ă��Ȃ�
				// �Փ˂��ĂȂ�
				return 0;
			}
			// ���͕̂��ʂɖ��ߍ��܂�Ă��܂��B
			*pT = 0.0f;
			*pOut = this->GetClosestPtPoint(a);
			return 2;
		}
		else {
			// ���ʂƌ�����������̂��钼��ab�ƌ�������t�̒l���v�Z
			*pT = (distance - vNormal.Dot(a)) / vNormal.Dot(rV);

			// t��[0..1]�̒��ɂ���ꍇ�A�����_���v�Z���ĕԂ�
			if (*pT >= 0.0f && *pT <= 1.0f) {
				*pOut = a + (rV * *pT);
				return 1;
			}
			// �����łȂ��ꍇt��+INF, -INF, NaN, ���邢��[0..1]�̒��ɂ͂Ȃ��̂ŁA�����Ȃ�

		}
		return 0;
	}
	//-----------------------------------------------------------------------------------
	//! @brief ����AB������p(this)�ƌ������Ă��邩�ǂ����𔻒�B�������Ă���Ό����_��Ԃ�
	//! @param [in]  a      �n�_
	//! @param [in]  rV       �x���V�e�B�[
	//! @param [in]  fEpsilon ���ʂ̌���
	//! @param [out] rT       ���ʂƌ�����������̂��钼��ab�ƌ�������l
	//! @param [out] rOut     �����_
	//! @return �����̒lt����ь����_Q�ƂƂ���true��Ԃ��B�����łȂ����false��Ԃ�
	//-----------------------------------------------------------------------------------
	int IntersectLine(const gt2Vector3 &a, const gt2Vector3 &rV, float fEpsilon, float &rT, gt2Vector3 &rOut) const
	{
		return this->IntersectLine(a, rV, fEpsilon, &rT, &rOut);
	}

	//-----------------------------------------------------------------------------------
	//! @brief ����AB������p(this)�ƌ������Ă��邩�ǂ����𔻒�B�������Ă���Ό����_��Ԃ�
	//! @param [in]  a     �n�_
	//! @param [in]  rV      �x���V�e�B�[
	//! @param [out] pT      ���ʂƌ�����������̂��钼��ab�ƌ�������l
	//! @param [out] pOut    �����_
	//! @return �����̒lt����ь����_Q�ƂƂ���true��Ԃ��B�����łȂ����false��Ԃ�
	//-----------------------------------------------------------------------------------
	int IntersectLine(const gt2Vector3 &a, const gt2Vector3 &rV, float *pT, gt2Vector3 *pOut) const
	{
		// ���ʌ����_�̊Ԋu�𓾂�:
		// ���̈ʒu���畽�ʂ܂ł̋������v�Z���܂��B
		float signedDistToPlane = this->DistanceTo(a);
		// 
		float normalDotVelocity = vNormal.Dot(rV);
		// ���̂����ʂɕ��s���ɂȂ��Ă��邩�H:
		if (normalDotVelocity == 0.0f) {
			if (fabs(signedDistToPlane) != 0.0f) {
				// �Փ˂��ĂȂ�
				return 0;
			}
			// ���͕̂��ʂɖ��ߍ��܂�Ă��܂��B
			*pT = 0.0f;
			*pOut = this->GetClosestPtPoint(a);
			return 2;
		}
		else {
			// ���ʂƌ�����������̂��钼��ab�ƌ�������t�̒l���v�Z
			*pT = (distance - vNormal.Dot(a)) / vNormal.Dot(rV);

			// t��[0..1]�̒��ɂ���ꍇ�A�����_���v�Z���ĕԂ�
			if (*pT >= 0.0f && *pT <= 1.0f) {
				*pOut = a + (rV * *pT);
				return 1;
			}
			// �����łȂ��ꍇt��+INF, -INF, NaN, ���邢��[0..1]�̒��ɂ͂Ȃ��̂ŁA�����Ȃ�

		}
		return 0;
	}
	//-----------------------------------------------------------------------------------
	//! @brief ����AB������p(this)�ƌ������Ă��邩�ǂ����𔻒�B�������Ă���Ό����_��Ԃ�
	//! @param [in]  a      �n�_
	//! @param [in]  rV       �x���V�e�B�[
	//! @param [out] rT      ���ʂƌ�����������̂��钼��ab�ƌ�������l
	//! @param [out] rOut     �����_
	//! @return �����̒lt����ь����_Q�ƂƂ���true��Ԃ��B�����łȂ����false��Ԃ�
	//-----------------------------------------------------------------------------------
	int IntersectLine(const gt2Vector3 &a, const gt2Vector3 &rV, float &rT, gt2Vector3 &rOut) const
	{
		return this->IntersectLine(a, rV, &rT, &rOut);
	}
};
