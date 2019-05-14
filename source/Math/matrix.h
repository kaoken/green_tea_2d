/*!
Copyright (c) 2014 METAL CUBE

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

@file matrix.h
@brief �v�f��2x2,3x3,4x4�̃}�g���N�X�\����
*/

#pragma once

#include <Math/plane.h>
#include <Math/quaternion.h>
//#include <Box2D/Common/b2Math.h>
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
#  include <DirectXMath.h>
#endif

//#include <OgreMatrix3.h>
//#include <OgreMatrix4.h>
//#include <LinearMath/btMatrix3x3.h>


#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
#  define MY_XMMATRIX ((DirectX::XMMATRIX)(*((DirectX::XMMATRIX*) this)))
#  define CAST_XMMATRIX(_ptr) ((DirectX::XMMATRIX)(*((DirectX::XMMATRIX*) _ptr)))
#endif

//======================================================================================
//! @brief 4�~4 �̃}�g���b�N�X
//======================================================================================
struct gt2Matrix4x4
{
public:
	union {
		struct {
			float	_11, _12, _13, _14;
			float	_21, _22, _23, _24;
			float	_31, _32, _33, _34;
			float	_41, _42, _43, _44;
		};
		float m[4][4];
		float mm[16];
	};

public:
	//------------------------------------------------------------------------
	//
	//! @name �R���X�g���N�^
	//
	//------------------------------------------------------------------------
	//@{
	gt2Matrix4x4()
	{
		this->MakeIdentity();
	}
	explicit gt2Matrix4x4(const float *pArray)
	{
		memcpy(mm, pArray, 16 * sizeof(float));
	}
	gt2Matrix4x4(const gt2Matrix4x4& rM) { *this = rM; }
	gt2Matrix4x4(
		float f11, float f12, float f13, float f14,
		float f21, float f22, float f23, float f24,
		float f31, float f32, float f33, float f34,
		float f41, float f42, float f43, float f44
	) :
		_11(f11), _12(f12), _13(f13), _14(f14),
		_21(f21), _22(f22), _23(f23), _24(f24),
		_31(f31), _32(f32), _33(f33), _34(f34),
		_41(f41), _42(f42), _43(f43), _44(f44) {}
	//@}



	inline float&
		operator () (unsigned int Row, unsigned int Col)
	{
		return m[Row][Col];
	}
	inline float
		operator () (unsigned int Row, unsigned int Col) const
	{
		return m[Row][Col];
	}
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
	gt2Matrix4x4&   operator= (const DirectX::XMMATRIX& vf) { memcpy(this, &vf, sizeof(gt2Matrix4x4)); return *this; }

#endif

	//------------------------------------------------------------------------
	//
	//! @name �^�ϊ����Z�q
	//
	//------------------------------------------------------------------------
	//@{
	inline operator float* ()
	{
		return mm;
	}
	inline operator const float* () const
	{
		return mm;
	}
	//@}

	//------------------------------------------------------------------------
	//
	//! @name ������Z�q
	//
	//------------------------------------------------------------------------
	//@{
	//inline gt2Matrix4x4&   operator= (const btMatrix3x3& m) { memcpy(this, &m, sizeof(gt2Matrix4x4)); return *this; }
	//inline gt2Matrix4x4&   operator= (const Ogre::Matrix4& m) { memcpy(this, &m, sizeof(gt2Matrix4x4)); return *this; }

	inline gt2Matrix4x4& operator *= (const gt2Matrix4x4& rM)
	{
		*this = Multiply(*this, rM);
		return *this;
	}
	inline gt2Matrix4x4& operator += (const gt2Matrix4x4& rM)
	{
		_11 += rM._11; _12 += rM._12; _13 += rM._13; _14 += rM._14;
		_21 += rM._21; _22 += rM._22; _23 += rM._23; _24 += rM._24;
		_31 += rM._31; _32 += rM._32; _33 += rM._33; _34 += rM._34;
		_41 += rM._41; _42 += rM._42; _43 += rM._43; _44 += rM._44;
		return *this;
	}
	inline gt2Matrix4x4& operator -= (const gt2Matrix4x4& rM)
	{
		_11 -= rM._11; _12 -= rM._12; _13 -= rM._13; _14 -= rM._14;
		_21 -= rM._21; _22 -= rM._22; _23 -= rM._23; _24 -= rM._24;
		_31 -= rM._31; _32 -= rM._32; _33 -= rM._33; _34 -= rM._34;
		_41 -= rM._41; _42 -= rM._42; _43 -= rM._43; _44 -= rM._44;
		return *this;
	}
	inline gt2Matrix4x4& operator *= (float f)
	{
		_11 *= f; _12 *= f; _13 *= f; _14 *= f;
		_21 *= f; _22 *= f; _23 *= f; _24 *= f;
		_31 *= f; _32 *= f; _33 *= f; _34 *= f;
		_41 *= f; _42 *= f; _43 *= f; _44 *= f;
		return *this;
	}
	inline gt2Matrix4x4& operator /= (float f)
	{
		float fInv = 1.0f / f;
		_11 *= fInv; _12 *= fInv; _13 *= fInv; _14 *= fInv;
		_21 *= fInv; _22 *= fInv; _23 *= fInv; _24 *= fInv;
		_31 *= fInv; _32 *= fInv; _33 *= fInv; _34 *= fInv;
		_41 *= fInv; _42 *= fInv; _43 *= fInv; _44 *= fInv;
		return *this;
	}
	//@}
	//------------------------------------------------------------------------
	//
	//! @name �P�����Z�q
	//
	//------------------------------------------------------------------------
	//@{
	inline gt2Matrix4x4 operator + () const
	{
		return *this;
	}
	inline gt2Matrix4x4 operator - () const
	{
		return gt2Matrix4x4(-_11, -_12, -_13, -_14,
			-_21, -_22, -_23, -_24,
			-_31, -_32, -_33, -_34,
			-_41, -_42, -_43, -_44);
	}
	//@}

	//------------------------------------------------------------------------
	//
	//! @name 2 �����Z�q
	//
	//------------------------------------------------------------------------
	//@{
	inline gt2Matrix4x4 operator * (const gt2Matrix4x4& rM) const
	{
		return Multiply(*this, rM);
	}
	inline gt2Matrix4x4 operator + (const gt2Matrix4x4& rM) const
	{
		return gt2Matrix4x4(_11 + rM._11, _12 + rM._12, _13 + rM._13, _14 + rM._14,
			_21 + rM._21, _22 + rM._22, _23 + rM._23, _24 + rM._24,
			_31 + rM._31, _32 + rM._32, _33 + rM._33, _34 + rM._34,
			_41 + rM._41, _42 + rM._42, _43 + rM._43, _44 + rM._44);
	}
	inline gt2Matrix4x4 operator + (float f) const
	{
		return gt2Matrix4x4(
			_11 + f, _12 + f, _13 + f, _14 + f,
			_21 + f, _22 + f, _23 + f, _24 + f,
			_31 + f, _32 + f, _33 + f, _34 + f,
			_41 + f, _42 + f, _43 + f, _44 + f);
	}
	inline gt2Matrix4x4 operator - (const gt2Matrix4x4& rM) const
	{
		return gt2Matrix4x4(_11 - rM._11, _12 - rM._12, _13 - rM._13, _14 - rM._14,
			_21 - rM._21, _22 - rM._22, _23 - rM._23, _24 - rM._24,
			_31 - rM._31, _32 - rM._32, _33 - rM._33, _34 - rM._34,
			_41 - rM._41, _42 - rM._42, _43 - rM._43, _44 - rM._44);
	}
	inline gt2Matrix4x4 operator - (float f) const
	{
		return gt2Matrix4x4(
			_11 - f, _12 - f, _13 - f, _14 - f,
			_21 - f, _22 - f, _23 - f, _24 - f,
			_31 - f, _32 - f, _33 - f, _34 - f,
			_41 - f, _42 - f, _43 - f, _44 - f);
	}
	inline gt2Matrix4x4 operator * (float f) const
	{
		return gt2Matrix4x4(_11 * f, _12 * f, _13 * f, _14 * f,
			_21 * f, _22 * f, _23 * f, _24 * f,
			_31 * f, _32 * f, _33 * f, _34 * f,
			_41 * f, _42 * f, _43 * f, _44 * f);
	}
	inline gt2Matrix4x4 operator / (float f) const
	{
		float fInv = 1.0f / f;
		return gt2Matrix4x4(_11 * fInv, _12 * fInv, _13 * fInv, _14 * fInv,
			_21 * fInv, _22 * fInv, _23 * fInv, _24 * fInv,
			_31 * fInv, _32 * fInv, _33 * fInv, _34 * fInv,
			_41 * fInv, _42 * fInv, _43 * fInv, _44 * fInv);
	}
	inline gt2Matrix4x4 operator / (const gt2Matrix4x4& rM) const
	{
		return gt2Matrix4x4(
			_11 / rM._11, _12 / rM._12, _13 / rM._13, _14 / rM._14,
			_21 / rM._21, _22 / rM._22, _23 / rM._23, _24 / rM._24,
			_31 / rM._31, _32 / rM._32, _33 / rM._33, _34 / rM._34,
			_41 / rM._41, _42 / rM._42, _43 / rM._43, _44 / rM._44);
	}

	friend inline gt2Matrix4x4 operator * (float f, const gt2Matrix4x4& rM)
	{
		return gt2Matrix4x4(f * rM._11, f * rM._12, f * rM._13, f * rM._14,
			f * rM._21, f * rM._22, f * rM._23, f * rM._24,
			f * rM._31, f * rM._32, f * rM._33, f * rM._34,
			f * rM._41, f * rM._42, f * rM._43, f * rM._44);
	}
	//@}

	//------------------------------------------------------------------------
	//
	//! @name ��r���Z�q
	//
	//------------------------------------------------------------------------
	//@{
	inline bool operator == (const gt2Matrix4x4& rM) const
	{
		return 0 == memcmp(this, &rM, sizeof(gt2Matrix4x4));
	}
	inline bool operator != (const gt2Matrix4x4& rM) const
	{
		return !(*this == rM);
	}
	//@}

	//-----------------------------------------------------------------------------------
	//! @brief �ʒu���擾����
	//! @return gt2Vector3��Ԃ�
	//-----------------------------------------------------------------------------------
	inline gt2Vector3 GetTranslation() const
	{
		gt2Vector3 out;
		out.x = _41;
		out.y = _42;
		out.z = _43;
		return out;
	}
	//-----------------------------------------------------------------------------------
	//! @brief �ʒu���Z�b�g����
	//! @param [in] rV3 gt2Vector3 �\���̂ւ̃|�C���^�ֈʒu�����Z�b�g����B
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void SetTranslation(const gt2Vector3& rV3)
	{
		_41 = rV3.x;
		_42 = rV3.y;
		_43 = rV3.z;
	}
	//-----------------------------------------------------------------------------------
	//! @brief �ʒu���t�ɃZ�b�g����B�e�v�f��-1���|���Ă���
	//! @param [in] rV3 gt2Vector3 �\���̂ւ̃|�C���^�ֈʒu�����Z�b�g����B
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void SetInverseTranslation(const gt2Vector3& rV3)
	{
		_41 = -rV3.x;
		_42 = -rV3.y;
		_43 = -rV3.z;
	}
	//-----------------------------------------------------------------------------------
	//! @brief �X�P�[���l���Z�b�g����
	//! @param [in] rV3 gt2Vector3 �\���̂ւ̃|�C���^�փX�P�[���l�����Z�b�g����B
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void SetScale(const gt2Vector3& rV3)
	{
		_11 = rV3.x;
		_22 = rV3.y;
		_33 = rV3.z;
	}

	//-----------------------------------------------------------------------------------
	//! @brief �X�P�[���l���Z�b�g����
	//! @return gt2Vector3 �Œl���擾
	//-----------------------------------------------------------------------------------
	inline gt2Vector3 GetScale() const
	{
		gt2Vector3 out;
		out.x = _11;
		out.y = _22;
		out.z = _33;
		return out;
	}
	//-----------------------------------------------------------------------------------
	//! @brief ���w���]�̎擾
	//! @param [out] pvAxis ��]�����i�[����x�N�g���ւ̃|�C���^
	//! @param [out] pRadian ���W�A���P�ʂł̉�]�p�x���i�[����float�ւ̃|�C���^
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void GetRotationRadians(gt2Vector3* pvAxis, float* pRadian) const
	{
		float radianResult = acosf(0.5f * ((_11 + _22 + _33) - 1.f));
		*pRadian = radianResult;
		if (radianResult > 0.f) {
			if (radianResult < GT2_PI) {
				*pvAxis = gt2Vector3(_32 - _23, _13 - _31, _21 - _12);
				pvAxis->Normalize();
			}
			else {
				if (_11 >= _22) {
					if (_11 >= _33) {
						pvAxis->x = 0.5f * sqrtf(_11 - _22 - _33 + 1.f);
						float halfInverse = 0.5f / pvAxis->x;
						pvAxis->y = halfInverse * _12;
						pvAxis->z = halfInverse * _13;
					}
					else {
						pvAxis->z = 0.5f * sqrtf(_33 - _11 - _22 + 1.f);
						float halfInverse = 0.5f / pvAxis->z;
						pvAxis->x = halfInverse * _13;
						pvAxis->y = halfInverse * _23;
					}
				}
				else {
					if (_22 >= _33) {
						pvAxis->y = 0.5f * sqrtf(_22 - _11 - _33 + 1.f);
						float halfInverse = 0.5f / pvAxis->y;
						pvAxis->x = halfInverse * _12;
						pvAxis->z = halfInverse * _23;
					}
					else {
						pvAxis->z = 0.5f * sqrtf(_33 - _11 - _22 + 1.f);
						float halfInverse = 0.5f / pvAxis->z;
						pvAxis->x = halfInverse * _13;
						pvAxis->y = halfInverse * _23;
					}
				}
			}
		}
		else {
			*pvAxis = gt2Vector3(1.f, 0.f, 0.f);
		}
	}
	//-----------------------------------------------------------------------------------
	//! @brief ���w���]�̎擾
	//! @param [out] rvAxis ��]�����i�[����x�N�g���ւ̃|�C���^
	//! @param [out] rRadian ���W�A���P�ʂł̉�]�p�x���i�[����float�ւ̃|�C���^
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void GetRotationRadians(gt2Vector3& rvAxis, float& rRadian) const
	{
		this->GetRotationRadians(&rvAxis, &rRadian);
	}


	//-----------------------------------------------------------------------------------
	//! @brief x,y,z �ɉ�]�p�x����͂��A���̃N���X�̃}�g���b�N�X�ɃZ�b�g����
	//! @param [out] pOut gt2Vector3 �\���̂ւ̃|�C���^�֊p�x�l�����Z�b�g����B
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void SetRotationDegrees(const gt2Vector3* pRot)
	{
		this->SetRotationRadians(&(*pRot * GT2_INV_RADIAN));
	}
	//-----------------------------------------------------------------------------------
	//! @brief x,y,z �ɉ�]�p�x����͂��A���̃N���X�̃}�g���b�N�X�ɃZ�b�g����
	//! @param [in] rRot gt2Vector3 �\���̂֊p�x�l�����Z�b�g����B
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void SetRotationDegrees(const gt2Vector3& rRot)
	{
		this->SetRotationDegrees(&rRot);
	}


	//-----------------------------------------------------------------------------------
	//! @brief x,y,z �ɉ�]�p�x����͂��A���̃N���X�̃}�g���b�N�X�ɃZ�b�g����
	//!        �����ł͓]�u���ꂽ�}�g���b�N�X�ɃZ�b�g����
	//! @param [out] pRot gt2Vector3 �\���̂ւ̃|�C���^�֊p�x�l�����Z�b�g����B
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void SetInverseRotationDegrees(const gt2Vector3* pRot)
	{
		this->SetInverseRotationRadians(&(*pRot * GT2_INV_RADIAN));
	}
	//-----------------------------------------------------------------------------------
	//! @brief x,y,z �ɉ�]�p�x����͂��A���̃N���X�̃}�g���b�N�X�ɃZ�b�g����
	//!        �����ł͓]�u���ꂽ�}�g���b�N�X�ɃZ�b�g����
	//! @param [out] rRot gt2Vector3 �\���̂֊p�x�l�����Z�b�g����B
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void SetInverseRotationDegrees(const gt2Vector3& rRot)
	{
		this->SetInverseRotationDegrees(&rRot);
	}


	//-----------------------------------------------------------------------------------
	//! @brief �e���̃��W�A���l��Ԃ�
	//! @return ���W�A���l����Ԃ�
	//-----------------------------------------------------------------------------------
	inline gt2Vector3 GetRotationRadians() const
	{
		gt2Vector3 out;
		out.x = asin(-_23);
		if (out.x < GT2_HALF_PI) {
			if (out.x > -GT2_HALF_PI) {
				out.y = atan2(_13, _33);
				out.z = atan2(_21, _22);
			}
			else {
				out.y = -atan2(-_12, _11);
				out.z = 0.0f;
			}
		}
		else {
			out.y = atan2(-_12, _11);
			out.z = 0.0f;
		}

		if (out.y < 0)
			out.y += GT2_PI2;

		if (out.x < 0)
			out.x += GT2_PI2;

		if (out.z < 0)
			out.z += GT2_PI2;
		return out;
	}

	//-----------------------------------------------------------------------------------
	//! @brief x,y,z �Ƀ��W�A���l����͂��A���̃N���X�̃}�g���b�N�X�ɃZ�b�g����
	//! @param [in] pRot gt2Vector3 �\���̂ւ̃|�C���^�փ��W�A���l�����Z�b�g����B
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void SetRotationRadians(const gt2Vector3* pRot)
	{
		double cr = cos(pRot->x);
		double sr = sin(pRot->x);
		double cp = cos(pRot->y);
		double sp = sin(pRot->y);
		double cy = cos(pRot->z);
		double sy = sin(pRot->z);

		_11 = (float)(cp*cy);
		_12 = (float)(cp*sy);
		_13 = (float)(-sp);

		float srsp = (float)(sr*sp);
		float crsp = (float)(cr*sp);

		_21 = (float)(srsp*cy - cr*sy);
		_22 = (float)(srsp*sy + cr*cy);
		_23 = (float)(sr*cp);

		_31 = (float)(crsp*cy + sr*sy);
		_32 = (float)(crsp*sy - sr*cy);
		_33 = (float)(cr*cp);
	}
	//-----------------------------------------------------------------------------------
	//! @brief x,y,z �Ƀ��W�A���l����͂��A���̃N���X�̃}�g���b�N�X�ɃZ�b�g����
	//! @param [in] rRot gt2Vector3 �\���̂փ��W�A���l�����Z�b�g����B
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void SetRotationRadians(const gt2Vector3& rRot)
	{
		this->SetRotationRadians(&rRot);
	}

	//-----------------------------------------------------------------------------------
	//! @brief XYZ����]�̎擾
	//! @return �e���ɂ����郉�W�A���P�ʂł̉�]�p�x
	//-----------------------------------------------------------------------------------
	inline gt2Vector3 GetRotationDegrees() const
	{
		return GetRotationRadians() * GT2_RADIAN;
	}

	//-----------------------------------------------------------------------------------
	//! @brief �e���̊p�x�̒l������
	//! @param [out] pvRadian gt2Vector3 �\���̂ւ̃|�C���^�֊p�x�l�����擾����B
	//! @return �������P��ł����true
	//-----------------------------------------------------------------------------------
	inline bool GetRotationXYZ(gt2Vector3* pvRadian) const
	{
		bool bRet;
		float yRadian = asin(-_31);
		pvRadian->y = yRadian;
		if (yRadian < GT2_HALF_PI) {
			if (yRadian > -GT2_HALF_PI) {
				pvRadian->x = atan2f(_32, _33);
				pvRadian->z = atan2f(_21, _11);
				bRet = true;
			}
			else {
				pvRadian->x = -atan2f(_12, _22);
				pvRadian->z = 0.f;
				bRet = false;
			}
		}
		else {
			pvRadian->x = atan2f(_12, _22);
			pvRadian->z = 0.f;
			bRet = false;
		}

		if (pvRadian->y < 0)
			pvRadian->y += GT2_PI2;
		if (pvRadian->x < 0)
			pvRadian->x += GT2_PI2;
		if (pvRadian->z < 0)
			pvRadian->z += GT2_PI2;

		return bRet;
	}
	//-----------------------------------------------------------------------------------
	//! @brief �e���̊p�x�̒l������
	//! @param [out] rvRadian gt2Vector3 �\���̂֊p�x�l�����擾����B
	//! @return �������P��ł����true
	//-----------------------------------------------------------------------------------
	inline bool GetRotationXYZ(gt2Vector3 &rvRadian) const
	{
		return this->GetRotationXYZ(&rvRadian);
	}

	//-----------------------------------------------------------------------------------
	//! @brief �e���̊p�x�̒l������
	//! @param [out] pvRadian gt2Vector3 �\���̂ւ̃|�C���^�֊p�x�l�����擾����B
	//! @return �������P��ł����true
	//-----------------------------------------------------------------------------------
	inline bool GetRotationXZY(gt2Vector3* pvRadian) const
	{
		bool bRet;

		float zRadian = asinf(_21);
		pvRadian->z = zRadian;
		if (zRadian < GT2_HALF_PI) {
			if (zRadian > -GT2_HALF_PI) {
				pvRadian->x = atan2f(-_23, _22);
				pvRadian->y = atan2f(-_31, _11);
				bRet = true;
			}
			else {
				pvRadian->x = -atan2f(_13, _33);
				pvRadian->y = 0.f;
				bRet = false;
			}
		}
		else {
			pvRadian->x = atan2f(_13, _33);
			pvRadian->y = 0.f;
			bRet = false;
		}

		if (pvRadian->y < 0)
			pvRadian->y += GT2_PI2;
		if (pvRadian->x < 0)
			pvRadian->x += GT2_PI2;
		if (pvRadian->z < 0)
			pvRadian->z += GT2_PI2;

		return bRet;
	}
	//-----------------------------------------------------------------------------------
	//! @brief �e���̊p�x�̒l������
	//! @param [out] rvRadian gt2Vector3 �\���̂֊p�x�l�����擾����B
	//! @return �������P��ł����true
	//-----------------------------------------------------------------------------------
	inline bool GetRotationXZY(gt2Vector3 &rvRadian) const
	{
		return this->GetRotationXZY(&rvRadian);
	}

	//-----------------------------------------------------------------------------------
	//! @brief �e���̊p�x�̒l������
	//! @param [out] pvRadian gt2Vector3 �\���̂ւ̃|�C���^�֊p�x�l�����擾����B
	//! @return �������P��ł����true
	//-----------------------------------------------------------------------------------
	inline bool GetRotationYXZ(gt2Vector3* pvRadian) const
	{
		bool bRet;
		float xRadian = asinf(_32);
		pvRadian->x = xRadian;
		if (xRadian < GT2_HALF_PI) {
			if (xRadian > -GT2_HALF_PI) {
				pvRadian->y = atan2f(-_31, _33);
				pvRadian->z = atan2f(-_12, _22);
				bRet = true;
			}
			else {
				pvRadian->y = -atan2f(-_21, _11);
				pvRadian->z = 0.f;
				bRet = false;
			}
		}
		else {
			pvRadian->y = atan2f(-_21, _11);
			pvRadian->z = 0.f;
			bRet = false;
		}

		if (pvRadian->y < 0)
			pvRadian->y += GT2_PI2;
		if (pvRadian->x < 0)
			pvRadian->x += GT2_PI2;
		if (pvRadian->z < 0)
			pvRadian->z += GT2_PI2;

		return bRet;
	}
	//-----------------------------------------------------------------------------------
	//! @brief �e���̊p�x�̒l������
	//! @param [out] rvRadian gt2Vector3 �\���̂֊p�x�l�����擾����B
	//! @return �������P��ł����true
	//-----------------------------------------------------------------------------------
	inline bool GetRotationYXZ(gt2Vector3 &rvRadian) const
	{
		return this->GetRotationYXZ(&rvRadian);
	}

	//-----------------------------------------------------------------------------------
	//! @brief �e���̊p�x�̒l������
	//! @param [out] pvRadian gt2Vector3 �\���̂ւ̃|�C���^�֊p�x�l�����擾����B
	//! @return �������P��ł����true
	//-----------------------------------------------------------------------------------
	inline bool GetRotationYZX(gt2Vector3* pvRadian) const
	{
		bool bRet;
		float zRadian = asin(-_12);
		pvRadian->z = zRadian;
		if (zRadian < GT2_HALF_PI) {
			if (zRadian > -GT2_HALF_PI) {
				pvRadian->y = atan2(_13, _11);
				pvRadian->x = atan2(_32, _22);
				bRet = true;
			}
			else {
				pvRadian->y = -atan2(_23, _33);
				pvRadian->x = 0.f;
				bRet = false;
			}
		}
		else {
			pvRadian->y = atan2(_23, _33);
			pvRadian->x = 0.f;
			bRet = false;
		}

		if (pvRadian->y < 0)
			pvRadian->y += GT2_PI2;
		if (pvRadian->x < 0)
			pvRadian->x += GT2_PI2;
		if (pvRadian->z < 0)
			pvRadian->z += GT2_PI2;

		return bRet;
	}
	//-----------------------------------------------------------------------------------
	//! @brief �e���̊p�x�̒l������
	//! @param [out] rvRadian gt2Vector3 �\���̂֊p�x�l�����擾����B
	//! @return �������P��ł����true
	//-----------------------------------------------------------------------------------
	inline bool GetRotationYZX(gt2Vector3 &rvRadian) const
	{
		return this->GetRotationYZX(&rvRadian);
	}

	//-----------------------------------------------------------------------------------
	//! @brief �e���̊p�x�̒l������
	//! @param [out] pvRadian gt2Vector3 �\���̂ւ̃|�C���^�֊p�x�l�����擾����B
	//! @return �������P��ł����true
	//-----------------------------------------------------------------------------------
	inline bool GetRotationZXY(gt2Vector3* pvRadian) const
	{
		bool bRet;
		float xRadian = asin(-_23);
		pvRadian->x = xRadian;
		if (xRadian < GT2_HALF_PI) {
			if (xRadian > -GT2_HALF_PI) {
				pvRadian->z = atan2(_21, _22);
				pvRadian->y = atan2(_13, _33);
				bRet = true;
			}
			else {
				pvRadian->z = -atan2(_31, _11);
				pvRadian->y = 0.f;
				bRet = false;
			}
		}
		else {
			pvRadian->z = atan2(_31, _11);
			pvRadian->y = 0.f;
			bRet = false;
		}

		if (pvRadian->y < 0)
			pvRadian->y += GT2_PI2;
		if (pvRadian->x < 0)
			pvRadian->x += GT2_PI2;
		if (pvRadian->z < 0)
			pvRadian->z += GT2_PI2;

		return bRet;
	}
	//-----------------------------------------------------------------------------------
	//! @brief �e���̊p�x�̒l������
	//! @param [out] rvRadian gt2Vector3 �\���̂֊p�x�l�����擾����B
	//! @return �������P��ł����true
	//-----------------------------------------------------------------------------------
	inline bool GetRotationZXY(gt2Vector3 &rvRadian) const
	{
		return this->GetRotationZXY(&rvRadian);
	}

	//-----------------------------------------------------------------------------------
	//! @brief �e���̊p�x�̒l������
	//! @param [out] pvRadian gt2Vector3 �\���̂ւ̃|�C���^�֊p�x�l�����擾����B
	//! @return �������P��ł����true
	//-----------------------------------------------------------------------------------
	inline bool GetRotationZYX(gt2Vector3* pvRadian) const
	{
		bool bRet;
		float yRadian = asinf(_13);
		pvRadian->y = yRadian;
		if (yRadian < GT2_HALF_PI) {
			if (yRadian > -GT2_HALF_PI) {
				pvRadian->z = atan2f(-_12, _11);
				pvRadian->x = atan2f(-_23, _33);
				bRet = true;
			}
			else {
				pvRadian->z = -atan2f(-_21, _31);
				pvRadian->x = 0.f;
				bRet = false;
			}
		}
		else {
			pvRadian->z = atan2f(_21, -_31);
			pvRadian->x = 0.f;
			bRet = false;
		}

		if (pvRadian->y < 0)
			pvRadian->y += GT2_PI2;
		if (pvRadian->x < 0)
			pvRadian->x += GT2_PI2;
		if (pvRadian->z < 0)
			pvRadian->z += GT2_PI2;

		return bRet;
	}
	//-----------------------------------------------------------------------------------
	//! @brief �e���̊p�x�̒l������
	//! @param [out] rvRadian gt2Vector3 �\���̂֊p�x�l�����擾����B
	//! @return �������P��ł����true
	//-----------------------------------------------------------------------------------
	inline bool GetRotationZYX(gt2Vector3 &rvRadian) const
	{
		return this->GetRotationZYX(&rvRadian);
	}

	//-----------------------------------------------------------------------------------
	//! @brief x,y,z �Ƀ��W�A���l����͂��A���̃N���X�̃}�g���b�N�X�ɃZ�b�g����B
	//!        �����ł͓]�u���ꂽ�}�g���b�N�X�ɃZ�b�g����
	//! @param [in] pRot gt2Vector3 �\���̂ւ̃|�C���^�փ��W�A���l�����Z�b�g����B
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void SetInverseRotationRadians(const gt2Vector3* pRot)
	{
		double cr = cos(pRot->x);
		double sr = sin(pRot->x);
		double cp = cos(pRot->y);
		double sp = sin(pRot->y);
		double cy = cos(pRot->z);
		double sy = sin(pRot->z);

		_11 = (float)(cp*cy);
		_21 = (float)(cp*sy);
		_31 = (float)(-sp);

		double srsp = sr*sp;
		double crsp = cr*sp;

		_12 = (float)(srsp*cy - cr*sy);
		_22 = (float)(srsp*sy + cr*cy);
		_32 = (float)(sr*cp);

		_13 = (float)(crsp*cy + sr*sy);
		_23 = (float)(crsp*sy - sr*cy);
		_33 = (float)(cr*cp);
	}
	//-----------------------------------------------------------------------------------
	//! @brief x,y,z �Ƀ��W�A���l����͂��A���̃N���X�̃}�g���b�N�X�ɃZ�b�g����B
	//!        �����ł͓]�u���ꂽ�}�g���b�N�X�ɃZ�b�g����
	//! @param [in] rRot gt2Vector3 �\���̂փ��W�A���l�����Z�b�g����B
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void SetInverseRotationRadians(const gt2Vector3 &rRot)
	{
		this->SetInverseRotationRadians(&rRot);
	}

	//-----------------------------------------------------------------------------------
	//! @brief �P�ʍs����쐬����B
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakeIdentity()
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixIdentity();
#else
		memset(mm, 0, 16 * sizeof(float));
		_11 = _22 = _33 = _44 = 1.0f;
#endif
	}
	//-----------------------------------------------------------------------------------
	//! @brief �s�񂪒P�ʍs�񂩂ǂ����𔻒肷��B
	//! @param [in] rRot gt2Vector3 �\���̂փ��W�A���l�����Z�b�g����B
	//! @return �s�񂪒P�ʍs��ł���ꍇ�A���̊֐��� true ��Ԃ��B@n
	//! ����ȊO�̏ꍇ�́Afalse ��Ԃ��B
	//-----------------------------------------------------------------------------------
	inline bool IsIdentity() const
	{
		for (int i = 0; i<4; ++i) {
			for (int j = 0; j<4; ++j)
				if (j != i)
				{
					if ((*this).m[i][j] < -0.0000001f ||
						(*this).m[i][j] > 0.0000001f)
						return false;
				}
				else
				{
					if ((*this).m[i][j] < 0.9999999f ||
						(*this).m[i][j] > 1.0000001f)
						return false;
				}
		}
		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief ���ƂȂ�ʒu�isrc)���炱�̃}�g���N�X�����ɉ�]�����ʒu��Ԃ�
	//! @param [in]  src ���ƂȂ�ʒu
	//! @return  ��]�����ʒu
	//-----------------------------------------------------------------------------------
	inline gt2Vector3 RotateVector3(const gt2Vector3& src) const
	{
		gt2Vector3 out;
		out.x = src.x*_11 + src.y*_21 + src.z*_31;
		out.y = src.x*_12 + src.y*_22 + src.z*_32;
		out.z = src.x*_13 + src.y*_23 + src.z*_33;
		return out;
	}

	//-----------------------------------------------------------------------------------
	//! @brief ���ƂȂ�ʒu�isrc)���炱�̋t�}�g���N�X�����ɉ�]�����ʒu��Ԃ�
	//! @param [in]  src ���ƂȂ�ʒu
	//! @return  ��]�����ʒu
	//-----------------------------------------------------------------------------------
	inline gt2Vector3 InverseRotateVector3(const gt2Vector3& src) const
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		DirectX::XMVECTOR out;
		gt2Vector3 out2;
		DirectX::XMMatrixInverse(&out, (DirectX::FXMMATRIX)*this);
		out2 = out;
		return out2;
#else
		gt2Vector3 out;
		out.x = src.x*_11 + src.y*_12 + src.z*_13;
		out.y = src.x*_21 + src.y*_22 + src.z*_23;
		out.z = src.x*_31 + src.y*_32 + src.z*_33;
		return out;
#endif
	}

	//-----------------------------------------------------------------------------------
	//! @brief ���ƂȂ�ʒu�isrc)���炱�̃}�g���N�X�����ɕό`�����ʒu��Ԃ�
	//! @param [in]  src ���ƂȂ�ʒu
	//! @return  �ό`�����ʒu
	//-----------------------------------------------------------------------------------
	inline gt2Vector3 TransformVector3(const gt2Vector3& src) const
	{
		gt2Vector3 out;
		out.x = src.x*_11 + src.y*_21 + src.z*_31 + _41;
		out.y = src.x*_12 + src.y*_22 + src.z*_32 + _42;
		out.z = src.x*_13 + src.y*_23 + src.z*_33 + _43;
		return out;
	}

	//-----------------------------------------------------------------------------------
	//! @brief ���ƂȂ�ʒu�isrc)���炱�̃}�g���N�X�����ɋt�Ɉړ������ʒu��Ԃ�
	//! @param [in]  src ���ƂȂ�ʒu
	//! @return  �t�Ɉړ������ʒu
	//-----------------------------------------------------------------------------------
	inline gt2Vector3 InverseTranslateVector3(const gt2Vector3& src) const
	{
		gt2Vector3 out;
		out.x = src.x - _41;
		out.y = src.y - _42;
		out.z = src.z - _43;
		return out;
	}

	//-----------------------------------------------------------------------------------
	//! @brief ���ƂȂ�ʒu�isrc)���炱�̋t�}�g���N�X�����Ɉړ������ʒu��Ԃ�
	//! @param [in]  src ���ƂȂ�ʒu
	//! @return  �ړ������ʒu
	//-----------------------------------------------------------------------------------
	inline gt2Vector3 TranslateVector3(const gt2Vector3& src) const
	{
		gt2Vector3 out;
		out.x = src.x + _41;
		out.y = src.y + _42;
		out.z = src.z + _43;
		return out;
	}

	//-----------------------------------------------------------------------------------
	//! @brief �s��̋t�s����v�Z����B
	//! @param [out]  pDeterminant �s��̍s�񎮂��܂� float �l�ւ̃|�C���^�B
	//!                            �s�񎮂��s�v�̏ꍇ�́A���̃p�����[�^�� nullptr ��ݒ肷��B
	//! @param [out]  pOut         ���Z���ʂł��� gt2Matrix4x4 �\���̂ւ̃|�C���^�B
	//! @return  �t�s��̌v�Z�����s�����ꍇ�́Afalse ��Ԃ��B
	//-----------------------------------------------------------------------------------
	inline bool GetInverse(float *pDeterminant, gt2Matrix4x4* pOut) const
	{
		float d;

		d = (_11 * _22 - _12 * _21) * (_33 * _44 - _34 * _43) -
			(_11 * _23 - _13 * _21) * (_32 * _44 - _34 * _42) +
			(_11 * _24 - _14 * _21) * (_32 * _43 - _33 * _42) +
			(_12 * _23 - _13 * _22) * (_31 * _44 - _34 * _41) -
			(_12 * _24 - _14 * _22) * (_31 * _43 - _33 * _41) +
			(_13 * _24 - _14 * _23) * (_31 * _42 - _32 * _41);

		if (d == 0.0f)
			return false;

		d = 1.0f / d;

		pOut->_11 = d * (_22 * (_33 * _44 - _34 * _43) + _23 * (_34 * _42 - _32 * _44) + _24 * (_32 * _43 - _33 * _42));
		pOut->_12 = d * (_32 * (_13 * _44 - _14 * _43) + _33 * (_14 * _42 - _12 * _44) + _34 * (_12 * _43 - _13 * _42));
		pOut->_13 = d * (_42 * (_13 * _24 - _14 * _23) + _43 * (_14 * _22 - _12 * _24) + _44 * (_12 * _23 - _13 * _22));
		pOut->_14 = d * (_12 * (_24 * _33 - _23 * _34) + _13 * (_22 * _34 - _24 * _32) + _14 * (_23 * _32 - _22 * _33));
		pOut->_21 = d * (_23 * (_31 * _44 - _34 * _41) + _24 * (_33 * _41 - _31 * _43) + _21 * (_34 * _43 - _33 * _44));
		pOut->_22 = d * (_33 * (_11 * _44 - _14 * _41) + _34 * (_13 * _41 - _11 * _43) + _31 * (_14 * _43 - _13 * _44));
		pOut->_23 = d * (_43 * (_11 * _24 - _14 * _21) + _44 * (_13 * _21 - _11 * _23) + _41 * (_14 * _23 - _13 * _24));
		pOut->_24 = d * (_13 * (_24 * _31 - _21 * _34) + _14 * (_21 * _33 - _23 * _31) + _11 * (_23 * _34 - _24 * _33));
		pOut->_31 = d * (_24 * (_31 * _42 - _32 * _41) + _21 * (_32 * _44 - _34 * _42) + _22 * (_34 * _41 - _31 * _44));
		pOut->_32 = d * (_34 * (_11 * _42 - _12 * _41) + _31 * (_12 * _44 - _14 * _42) + _32 * (_14 * _41 - _11 * _44));
		pOut->_33 = d * (_44 * (_11 * _22 - _12 * _21) + _41 * (_12 * _24 - _14 * _22) + _42 * (_14 * _21 - _11 * _24));
		pOut->_34 = d * (_14 * (_22 * _31 - _21 * _32) + _11 * (_24 * _32 - _22 * _34) + _12 * (_21 * _34 - _24 * _31));
		pOut->_41 = d * (_21 * (_33 * _42 - _32 * _43) + _22 * (_31 * _43 - _33 * _41) + _23 * (_32 * _41 - _31 * _42));
		pOut->_42 = d * (_31 * (_13 * _42 - _12 * _43) + _32 * (_11 * _43 - _13 * _41) + _33 * (_12 * _41 - _11 * _42));
		pOut->_43 = d * (_41 * (_13 * _22 - _12 * _23) + _42 * (_11 * _23 - _13 * _21) + _43 * (_12 * _21 - _11 * _22));
		pOut->_44 = d * (_11 * (_22 * _33 - _23 * _32) + _12 * (_23 * _31 - _21 * _33) + _13 * (_21 * _32 - _22 * _31));

		if (pDeterminant != nullptr) *pDeterminant = d;
		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief �s��̋t�s����v�Z����B
	//! @param [out]  rDeterminant �s��̍s�񎮂��܂ޒl
	//! @param [out]  rOut         ���Z���ʂł��� gt2Matrix4x4 �\����
	//! @return  �t�s��̌v�Z�����s�����ꍇ�́Afalse ��Ԃ��B
	//-----------------------------------------------------------------------------------
	inline bool GetInverse(float &rDeterminant, gt2Matrix4x4& rOut) const
	{
		return this->GetInverse(&rDeterminant, &rOut);
	}

	//-----------------------------------------------------------------------------------
	//! @brief �A�t�B���ϊ��s����쐬���܂��B
	//! @param [in] scaling            �e�����̃X�P�[�����O�W���̃x�N�g���B
	//! @param [in] rotationOrigin     ��]�̒��S�����w���B
	//! @param [in] rotationQuaternion ��]�v���B
	//! @param [in] translation        �ʒu�I�t�Z�b�g�B
	//! @return  �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakeAffineTransformation(const gt2Vector3 &scaling, const gt2Vector3 &rotationOrigin, const gt2Quaternion &rotationQuaternion, const gt2Vector3 &translation)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		DirectX::XMVECTOR a, b, c, d;
		a = scaling.GetXMVECTOR();
		b = rotationOrigin.GetXMVECTOR();
		c = rotationQuaternion.GetXMVECTOR();
		d = translation.GetXMVECTOR();
		*this = DirectX::XMMatrixAffineTransformation(a, b, c, d);
#else
		// M = MScaling * Inverse(MRotationOrigin) * MRotation * MRotationOrigin * MTranslation;
		gt2Matrix4x4 mRotation;
		this->MakeScale(scaling);
		mRotation.MakeRotationQuaternion(rotationQuaternion);

		_41 -= rotationOrigin.x; _42 -= rotationOrigin.y; _43 -= rotationOrigin.z;

		*this *= mRotation;
		_41 += rotationOrigin.x; _42 += rotationOrigin.y; _43 += rotationOrigin.z;
		_41 += translation.x;    _42 += translation.y;    _43 += translation.z;
#endif
	}
	//-----------------------------------------------------------------------------------
	//! @brief 2D �A�t�B���ϊ��s����쐬���܂��B
	//! @param [in] scaling            2�����̃X�P�[�����O�W���̃x�N�g���B
	//! @param [in] rotationOrigin     2�����̉�]�̒��S���w���B
	//! @param [in] rotation           ��]�̃��W�A���p�B
	//! @param [in] translation        2�����x�N�g���ϊ��I�t�Z�b�g�B
	//! @return  �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakeAffineTransformation2D(const gt2Vector2 &scaling, const gt2Vector2 &rotationOrigin, const float rotation, const gt2Vector2 &translation)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		DirectX::XMVECTOR a, b, c;
		a = scaling.GetXMVECTOR();
		b = rotationOrigin.GetXMVECTOR();
		c = translation.GetXMVECTOR();
		*this = DirectX::XMMatrixAffineTransformation2D(a, b, rotation, c);
#else
		// M = MScaling * Inverse(MRotationOrigin) * MRotation * MRotationOrigin * MTranslation;
		gt2Matrix4x4 mRotation;
		this->MakeScale(gt2Vector3(scaling.x, scaling.y, 0));
		mRotation.MakeRotationZ(rotation);

		_41 -= rotationOrigin.x; _42 -= rotationOrigin.y;

		*this *= mRotation;
		_41 += rotationOrigin.x; _42 += rotationOrigin.y;;
		_41 += translation.x;    _42 += translation.y;
#endif
	}

	//-----------------------------------------------------------------------------------
	//! @brief �Ίp������pIn �ŗ^�����C���̐�����0�ł���s���Ԃ��D
	//! @param [in]  pIn gt2Vector3 �\���̂ւ̃|�C���^�ֈʒu�����擾����B
	//! @param [in]  k  k �Ԗڂ̑Ίp��̃��X�g�̗v�f�̒l�D
	//! @return  �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakeDiagonal(const gt2Vector4* pIn, int k)
	{
		if (k < -3 || k > 3) return;

		_11 = _12 = _13 = 0.0f;
		_21 = _22 = _23 = 0.0f;
		_31 = _32 = _33 = 0.0f;

		if (k < 0) {
			k = abs(k) * 5;
		}
		mm[k] = pIn->x;
		if ((k += 5) > 15)return;
		mm[k] = pIn->y;
		if ((k += 5) > 15)return;
		mm[k] = pIn->z;
		if ((k += 5) > 15)return;
		mm[k] = pIn->w;
	}
	//-----------------------------------------------------------------------------------
	//! @brief �Ίp������pIn �ŗ^�����C���̐�����0�ł���s���Ԃ��D
	//! @param [in]  rIn gt2Vector3 �\���̂ֈʒu�����擾����B
	//! @param [in]  k  k �Ԗڂ̑Ίp��̃��X�g�̗v�f�̒l�D
	//! @return  �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakeDiagonal(const gt2Vector4 &rIn, int k)
	{
		this->MakeDiagonal(&rIn, k);
	}


	//-----------------------------------------------------------------------------------
	//! @brief �ʒu���w���x�N�g������A���M�̃}�g���N�X�����ւ���
	//! @param [in]  rV3 �ʒu���
	//! @return  �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakeTranslation(const gt2Vector3& rV3)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixTranslation(rV3.x, rV3.y, rV3.z);
#else
		this->MakeIdentity();
		this->SetTranslation(rV3);
#endif
	}
	//-----------------------------------------------------------------------------------
	//! @brief �X�P�[���l���w���x�N�g������A���M�̃}�g���N�X�����ւ���
	//! @param [in]  rV3 �X�P�[���l
	//! @return  �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakeScale(const gt2Vector3& rV3)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixScaling(rV3.x, rV3.y, rV3.z);
#else

		this->MakeIdentity();
		this->SetScale(rV3);
#endif
	}

	//-----------------------------------------------------------------------------------
	//! @brief ����Ɋ�Â��āA������W�n���ߎˉe�s����쐬����B
	//! @param [in]  fovy   �����̎��� (���W�A���P��)�B
	//! @param [in]  aspect �r���[��Ԃ̕��������ŏ�Z���Ē�`�����A�X�y�N�g��B
	//! @param [in]  zn     �߂��r���[���ʂ� Z �l�B
	//! @param [in]  zf     �����r���[���ʂ� Z �l�B
	//! @return  �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakePerspectiveFovLH(float fovy, float aspect, float zn, float zf)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixPerspectiveFovLH(fovy, aspect, zn, zf);
#else

		//xScale     0          0               0
		//0        yScale       0               0
		//0          0       zf/(zf-zn)         1
		//0          0       -zn*zf/(zf-zn)     0
		//where:
		//yScale = cot(fovY/2)

		//xScale = aspect ratio * yScale

		float yScale = (float)(1.0 / tan(fovy*0.5f));
		float xScale = yScale / aspect;

		_11 = xScale;
		_12 = 0.0f;
		_13 = 0.0f;
		_14 = 0.0f;

		_21 = 0.0f;
		_22 = yScale;
		_23 = 0.0f;
		_24 = 0.0f;

		_31 = 0.0f;
		_32 = 0.0f;
		_33 = zf / (zf - zn); // DirectX �o�[�W����
								//		_33 = zf+zn/(zn-zf); // OpenGL �o�[�W����
		_34 = 1.0f;

		_41 = 0.0f;
		_42 = 0.0f;
		_43 = -zn*zf / (zf - zn); // DirectX �o�[�W����
									//		_43 = 2.0f*zn*zf/(zn-zf); // OpenGL �o�[�W����
		_44 = 0.0f;
#endif
	}
	//-----------------------------------------------------------------------------------
	//! @brief ����Ɋ�Â��āA�E����W�n���ߎˉe�s����쐬����B
	//! @param [in]  fovy   �����̎��� (���W�A���P��)�B
	//! @param [in]  aspect �r���[��Ԃ̕��������ŏ�Z���Ē�`�����A�X�y�N�g��B
	//! @param [in]  zn     �߂��r���[���ʂ� Z �l�B
	//! @param [in]  zf     �����r���[���ʂ� Z �l�B
	//! @return  �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakePerspectiveFovRH(float fovy, float aspect, float zn, float zf)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixPerspectiveFovRH(fovy, aspect, zn, zf);
#else
		//xScale     0          0              0
		//0        yScale       0              0
		//0        0        zf/(zn-zf)        -1
		//0        0        zn*zf/(zn-zf)      0
		//where:
		//yScale = cot(fovY/2)

		//xScale = aspect ratio * yScale
		float yScale = (float)(1.0 / tan(fovy / 2.0));
		float xScale = yScale / aspect;

		_11 = xScale;
		_12 = 0.0f;
		_13 = 0.0f;
		_14 = 0.0f;

		_21 = 0.0f;
		_22 = yScale;
		_23 = 0.0f;
		_24 = 0.0f;

		_31 = 0.0f;
		_32 = 0.0f;
		_33 = zf / (zn - zf);
		_34 = -1.0f;

		_41 = 0.0f;
		_42 = 0.0f;
		_43 = zn*zf / (zn - zf);
		_44 = 0.0f;
#endif
	}

	//-----------------------------------------------------------------------------------
	//! @brief ������W�n���ˉe�s����쐬����B
	//! @param [in]  w  �r���[ �{�����[���̕��B
	//! @param [in]  h  �r���[ �{�����[���̍����B
	//! @param [in]  zn �r���[ �{�����[���̍ŏ� z �l�B������� z �ƌĂт܂��B
	//! @param [in]  zf �r���[ �{�����[���̍ő� z �l�B������� z �ƌĂт܂��B
	//! @return  �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakeOrthographicLH(float w, float h, float zn, float zf)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixOrthographicLH(w, h, zn, zf);
#else
		_11 = 2 / w;
		_12 = 0;
		_13 = 0;
		_14 = 0;

		_21 = 0;
		_22 = 2 / h;
		_23 = 0;
		_24 = 0;

		_31 = 0;
		_32 = 0;
		_33 = 1 / (zf - zn);
		_34 = 0;

		_41 = 0;
		_42 = 0;
		_43 = zn / (zn - zf);
		_44 = 1;
#endif
	}
	//-----------------------------------------------------------------------------------
	//! @brief �E����W�n���ˉe�s����쐬����B
	//! @param [in]  w  �r���[ �{�����[���̕��B
	//! @param [in]  h  �r���[ �{�����[���̍����B
	//! @param [in]  zn �r���[ �{�����[���̍ŏ� z �l�B������� z �ƌĂт܂��B
	//! @param [in]  zf �r���[ �{�����[���̍ő� z �l�B������� z �ƌĂт܂��B
	//! @return  �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakeOrthographicRH(float w, float h, float zn, float zf)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixOrthographicRH(w, h, zn, zf);
#else
		_11 = 2 / w;
		_12 = 0;
		_13 = 0;
		_14 = 0;

		_21 = 0;
		_22 = 2 / h;
		_23 = 0;
		_24 = 0;

		_31 = 0;
		_32 = 0;
		_33 = 1 / (zn - zf);
		_34 = 0;

		_41 = 0;
		_42 = 0;
		_43 = zn / (zn - zf);
		_44 = -1;
#endif
	}
	//-----------------------------------------------------------------------------------
	//! @brief ������W�n���ߎˉe�s����쐬����B
	//! @param [in]  w  �߂��r���[���ʂł̃r���[ �{�����[���̕��B
	//! @param [in]  h  �߂��r���[���ʂł̃r���[ �{�����[���̍����B
	//! @param [in]  zn �߂��r���[���ʂ� Z �l�B
	//! @param [in]  zf �����r���[���ʂ� Z �l�B
	//! @return  �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakePerspectiveLH(float w, float h, float zn, float zf)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixPerspectiveLH(w, h, zn, zf);
#else
		_11 = 2 * zn / w;
		_12 = 0;
		_13 = 0;
		_14 = 0;

		_21 = 0;
		_22 = 2 * zn / h;
		_23 = 0;
		_24 = 0;

		_31 = 0;
		_32 = 0;
		_33 = zf / (zf - zn);
		_34 = 1;

		_41 = 0;
		_42 = 0;
		_43 = zn*zf / (zn - zf);
		_44 = 0;
#endif
	}
	//-----------------------------------------------------------------------------------
	//! @brief �E����W�n���ߎˉe�s����쐬����B
	//! @param [in]  w  �߂��r���[���ʂł̃r���[ �{�����[���̕��B
	//! @param [in]  h  �߂��r���[���ʂł̃r���[ �{�����[���̍����B
	//! @param [in]  zn �߂��r���[���ʂ� Z �l�B
	//! @param [in]  zf �����r���[���ʂ� Z �l�B
	//! @return  �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakePerspectiveRH(float w, float h, float zn, float zf)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixPerspectiveRH(w, h, zn, zf);
#else
		_11 = 2 * zn / w;
		_12 = 0;
		_13 = 0;
		_14 = 0;

		_21 = 0;
		_22 = 2 * zn / h;
		_23 = 0;
		_24 = 0;

		_31 = 0;
		_32 = 0;
		_33 = zf / (zn - zf);
		_34 = -1;

		_41 = 0;
		_42 = 0;
		_43 = zn*zf / (zn - zf);
		_44 = 0;
#endif
	}
	//-----------------------------------------------------------------------------------
	//! @brief ������W�n�̃J�X�^�������ˉe�s����쐬���܂��B
	//! @param [in]  viewLeft   �j�A�N���b�s���O�ʂł̃N���b�s���O����̍�����x���W�B
	//! @param [in]  viewRight  �j�A�N���b�s���O�ʂł̃N���b�s���O����̉E����x���W�B
	//! @param [in]  viewBottom �j�A�N���b�s���O�ʂł̃N���b�s���O����̒�ʑ���y���W�B
	//! @param [in]  viewTop    �j�A�N���b�s���O�ʂŃN���b�s���O����̏㑤��Y���W�B
	//! @param [in]  nearZ      �j�A�N���b�v�ʂ܂ł̋����B
	//! @param [in]  farZ       �t�@�[�N���b�s���O�ʂ܂ł̋����B
	//! @return  �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakeOrthographicOffCenterLH(float viewLeft, float viewRight, float viewBottom, float viewTop, float nearZ, float farZ)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixOrthographicOffCenterLH(viewLeft, viewRight, viewBottom, viewTop, nearZ, farZ);
#else
		float reciprocalWidth = 1.0f / (viewRight - viewLeft);
		float reciprocalHeight = 1.0f / (viewTop - viewBottom);
		float fRange = 1.0f / (farZ - nearZ);

		_11 = reciprocalWidth + reciprocalWidth;
		_12 = 0.0f;
		_13 = 0.0f;
		_14 = 0.0f;

		_21 = 0.0f;
		_22 = reciprocalHeight + reciprocalHeight;
		_23 = 0.0f;
		_24 = 0.0f;

		_31 = 0.0f;
		_32 = 0.0f;
		_33 = fRange;
		_34 = 0.0f;

		_41 = -(viewLeft + viewRight) * reciprocalWidth;
		_42 = -(viewTop + viewBottom) * reciprocalHeight;
		_43 = -fRange * nearZ;
		_44 = 1.0f;
#endif
	}
	//-----------------------------------------------------------------------------------
	//! @brief �E����W�n�̃J�X�^�������ˉe�s����쐬���܂��B
	//! @param [in]  viewLeft   �j�A�N���b�s���O�ʂł̃N���b�s���O����̍�����x���W�B
	//! @param [in]  viewRight  �j�A�N���b�s���O�ʂł̃N���b�s���O����̉E����x���W�B
	//! @param [in]  viewBottom �j�A�N���b�s���O�ʂł̃N���b�s���O����̒�ʑ���y���W�B
	//! @param [in]  viewTop    �j�A�N���b�s���O�ʂŃN���b�s���O����̏㑤��Y���W�B
	//! @param [in]  nearZ      �j�A�N���b�v�ʂ܂ł̋����B
	//! @param [in]  farZ       �t�@�[�N���b�s���O�ʂ܂ł̋����B
	//! @return  �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakeOrthographicOffCenterRH(float viewLeft, float viewRight, float viewBottom, float viewTop, float nearZ, float farZ)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixOrthographicOffCenterRH(viewLeft, viewRight, viewBottom, viewTop, nearZ, farZ);
#else
		float reciprocalWidth = 1.0f / (viewRight - viewLeft);
		float reciprocalHeight = 1.0f / (viewTop - viewBottom);
		float fRange = 1.0f / (nearZ - farZ);

		_11 = reciprocalWidth + reciprocalWidth;
		_12 = 0.0f;
		_13 = 0.0f;
		_14 = 0.0f;

		_21 = 0.0f;
		_22 = reciprocalHeight + reciprocalHeight;
		_23 = 0.0f;
		_24 = 0.0f;

		_31 = 0.0f;
		_32 = 0.0f;
		_33 = fRange;
		_34 = 0.0f;

		_41 = -(viewLeft + viewRight) * reciprocalWidth;
		_42 = -(viewTop + viewBottom) * reciprocalHeight;
		_43 = -fRange * nearZ;
		_44 = 1.0f;
#endif
	}

	//-----------------------------------------------------------------------------------
	//! @brief ������W�n�p�[�X�y�N�e�B�u�ˉe�s��̃J�X�^���o�[�W�������\�z���܂��B
	//! @param [in]  viewLeft   �j�A�N���b�s���O�ʂł̃N���b�s���O����̍�����x���W�B
	//! @param [in]  viewRight  �j�A�N���b�s���O�ʂł̃N���b�s���O����̉E����x���W�B
	//! @param [in]  viewBottom �j�A�N���b�s���O�ʂł̃N���b�s���O����̒�ʑ���y���W�B
	//! @param [in]  viewTop    �j�A�N���b�s���O�ʂŃN���b�s���O����̏㑤��Y���W�B
	//! @param [in]  nearZ      �j�A�N���b�v�ʂ܂ł̋����B
	//! @param [in]  farZ       �t�@�[�N���b�s���O�ʂ܂ł̋����B
	//! @return  �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakePerspectiveOffCenterLH(float viewLeft, float viewRight, float viewBottom, float viewTop, float nearZ, float farZ)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixPerspectiveOffCenterLH(viewLeft, viewRight, viewBottom, viewTop, nearZ, farZ);
#else
		float twoNearZ = nearZ + nearZ;
		float reciprocalWidth = 1.0f / (viewRight - viewLeft);
		float reciprocalHeight = 1.0f / (viewTop - viewBottom);
		float fRange = farZ / (farZ - nearZ);

		_11 = twoNearZ * reciprocalWidth;
		_12 = 0.0f;
		_13 = 0.0f;
		_14 = 0.0f;

		_21 = 0.0f;
		_22 = twoNearZ * reciprocalHeight;
		_23 = 0.0f;
		_24 = 0.0f;

		_31 = -(viewLeft + viewRight) * reciprocalWidth;
		_32 = -(viewTop + viewBottom) * reciprocalHeight;
		_33 = fRange;
		_34 = 1.0f;

		_41 = 0.0f;
		_42 = 0.0f;
		_43 = -fRange * nearZ;
		_44 = 0.0f;
#endif
	}
	//-----------------------------------------------------------------------------------
	//! @brief �E����W�n�p�[�X�y�N�e�B�u�ˉe�s��̃J�X�^���o�[�W�������\�z���܂��B
	//! @param [in]  viewLeft   �j�A�N���b�s���O�ʂł̃N���b�s���O����̍�����x���W�B
	//! @param [in]  viewRight  �j�A�N���b�s���O�ʂł̃N���b�s���O����̉E����x���W�B
	//! @param [in]  viewBottom �j�A�N���b�s���O�ʂł̃N���b�s���O����̒�ʑ���y���W�B
	//! @param [in]  viewTop    �j�A�N���b�s���O�ʂŃN���b�s���O����̏㑤��Y���W�B
	//! @param [in]  nearZ      �j�A�N���b�v�ʂ܂ł̋����B
	//! @param [in]  farZ       �t�@�[�N���b�s���O�ʂ܂ł̋����B
	//! @return  �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakePerspectiveOffCenterRH(float viewLeft, float viewRight, float viewBottom, float viewTop, float nearZ, float farZ)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixPerspectiveOffCenterRH(viewLeft, viewRight, viewBottom, viewTop, nearZ, farZ);
#else
		float twoNearZ = nearZ + nearZ;
		float reciprocalWidth = 1.0f / (viewRight - viewLeft);
		float reciprocalHeight = 1.0f / (viewTop - viewBottom);
		float fRange = farZ / (nearZ - farZ);

		_11 = twoNearZ * reciprocalWidth;
		_12 = 0.0f;
		_13 = 0.0f;
		_14 = 0.0f;

		_21 = 0.0f;
		_22 = twoNearZ * reciprocalHeight;
		_23 = 0.0f;
		_24 = 0.0f;

		_31 = (viewLeft + viewRight) * reciprocalWidth;
		_32 = (viewTop + viewBottom) * reciprocalHeight;
		_33 = fRange;
		_34 = -1.0f;

		_41 = 0.0f;
		_42 = 0.0f;
		_43 = fRange * nearZ;
		_44 = 0.0f;
#endif
	}
	//-----------------------------------------------------------------------------------
	//! @brief �W�I���g���𕽖ʂɎˉe����g�����X�t�H�[���s����쐬���܂��B
	//! @param [in]  w  ���C�g�̈ʒu���L�q���� 4D �x�N�g���B���C�g�� w �v�f�� 0.0f �̏ꍇ�A
	//!                 ���_���烉�C�g�܂ł̌����̓f�B���N�V���i�� ���C�g��\���܂��B
	//!                 ���C�g�� w �v�f�� 1.0f �̏ꍇ�A���C�g�̓|�C���g���C�g
	//! @param [in]  rPlane  ���
	//! @return  �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakedShadowMatrix(const gt2Vector4& rLight, const gt2Plane3& rPlane)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixShadow(rPlane.GetXMVECTOR(), rLight.GetXMVECTOR());
#else
		gt2Vector3 vTmp(rLight.v);
		gt2Vector3 vN;
		rPlane.vNormal.Normalize(&vN);
		float d = vN.Dot(vTmp);

		_11 = vN.x * rLight.x + d;
		_12 = vN.x * rLight.y;
		_13 = vN.x * rLight.z;
		_14 = vN.x * rLight.w;

		_21 = vN.y * rLight.x;
		_22 = vN.y * rLight.y + d;
		_23 = vN.y * rLight.z;
		_24 = vN.y * rLight.w;

		_31 = vN.z * rLight.x;
		_32 = vN.z * rLight.y;
		_33 = vN.z * rLight.z + d;
		_34 = vN.z * rLight.w;

		_41 = rPlane.distance * rLight.x + d;
		_42 = rPlane.distance * rLight.y;
		_43 = rPlane.distance * rLight.z;
		_44 = rPlane.distance * rLight.w;
#endif
	}
	//-----------------------------------------------------------------------------------
	//! @brief XY���ʓ���2�����̕ϊ��s����쐬���܂��B
	//! @param [in]  scalingOrigin   �X�P�[�����O�̒��S���L�q���A2�����̃x�N�g���B
	//! @param [in]  scalingOrientation  ��]�W�����X�P�[�����O����B
	//! @param [in]  scaling         x���Ay���̃X�P�[�����O���q���܂�2D�x�N�^�[�B
	//! @param [in]  rotationOrigin  ��]�̒��S���L�q���A2�����̃x�N�g���B
	//! @param [in]  rotation        ��]�p�x�i���W�A���P�ʁj�B
	//! @param [in]  translation     x���Ay���ɉ������ړ����L�q����2D�x�N�^�[�B
	//! @return  �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakeTransformation2D(
		const gt2Vector2 &scalingOrigin,
		const float scalingOrientation,
		const gt2Vector2 &scaling,
		const gt2Vector3 &rotationOrigin,
		const float rotation,
		const gt2Vector3 &translation
	)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixTransformation2D(
			scalingOrigin.GetXMVECTOR(),
			scalingOrientation,
			scaling.GetXMVECTOR(),
			rotationOrigin.GetXMVECTOR(),
			rotation,
			translation.GetXMVECTOR());
#else
		// M = Inverse(MScalingOrigin) * Transpose(MScalingOrientation) * MScaling * MScalingOrientation *
		//         MScalingOrigin * Inverse(MRotationOrigin) * MRotation * MRotationOrigin * MTranslation;

		gt2Matrix4x4 MScalingOriginI, MScalingOrientation, MScalingOrientationT, MScaling, MRotation;


		MScalingOriginI.MakeTranslation(gt2Vector3(scalingOrigin.x, scalingOrigin.y, 0.0)*-1);
		MScalingOrientation.MakeRotationZ(scalingOrientation);
		MScalingOrientationT = MScalingOrientation.GetTranspose();
		MScaling.MakeScale(gt2Vector3(scaling.x, scaling.y, 0.0));
		MRotation.MakeRotationZ(rotation);

		*this = MScalingOriginI * MScalingOrientationT;
		*this *= MScaling;
		*this *= MScalingOrientation;
		_31 = scalingOrigin.x;  _32 = scalingOrigin.y;
		_31 -= rotationOrigin.x; _32 -= rotationOrigin.y; _33;
		*this *= MRotation;
		_31 += rotationOrigin.x; _32 += rotationOrigin.y; _33 += rotationOrigin.z;
		_31 += translation.x;    _32 += translation.y;    _33 += translation.z;
#endif
	}
	//-----------------------------------------------------------------------------------
	//! @brief �ϊ��s����쐬���܂��B
	//! @param [in]  scalingOrigin      �X�P�[�����O�̒��S���L�q����3D�x�N�g���B
	//! @param [in]  scalingOrientationQuaternion  �X�P�[�����O�̌������������l���B
	//! @param [in]  scaling            x���Ay���Az���̃X�P�[�����O���q���܂�3D�x�N�^�[�B
	//! @param [in]  rotationOrigin     ��]�̒��S���L�q����3D�x�N�g���B
	//! @param [in]  rotationQuaternion RotationOrigin�Ŏ�����A���_�𒆐S�Ƃ�����]���L�q�����l���B
	//! @param [in]  translation        x���Ay���Az���ɉ������ړ����L�q����3D�x�N�^�[�B
	//! @return  �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakeTransformation(
		const gt2Vector3 &scalingOrigin,
		const gt2Quaternion &scalingOrientationQuaternion,
		const gt2Vector3 &scaling,
		const gt2Vector3 &rotationOrigin,
		const gt2Quaternion &rotationQuaternion,
		const gt2Vector3 &translation
	)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixTransformation(
			scalingOrigin.GetXMVECTOR(),
			scalingOrientationQuaternion.GetXMVECTOR(),
			scaling.GetXMVECTOR(),
			rotationOrigin.GetXMVECTOR(),
			rotationQuaternion.GetXMVECTOR(),
			translation.GetXMVECTOR());
#else
		// M = Inverse(MScalingOrigin) * Transpose(MScalingOrientation) * MScaling * MScalingOrientation *
		//         MScalingOrigin * Inverse(MRotationOrigin) * MRotation * MRotationOrigin * MTranslation;

		gt2Matrix4x4 MScalingOriginI, MScalingOrientation, MScalingOrientationT, MScaling, MRotation;
		MScalingOriginI.MakeTranslation(scalingOrigin*-1);
		MScalingOrientation.MakeRotationQuaternion(scalingOrientationQuaternion);
		MScalingOrientationT = MScalingOrientation.GetTranspose();
		MScaling.MakeScale(scaling);
		MRotation.MakeRotationQuaternion(rotationQuaternion);


		*this = MScalingOriginI * MScalingOrientationT;
		*this *= MScaling;
		*this *= MScalingOrientation;
		_31 = scalingOrigin.x;  _32 = scalingOrigin.y;  _33 = scalingOrigin.z;
		_31 -= rotationOrigin.x; _32 -= rotationOrigin.y; _33 -= rotationOrigin.z;
		*this *= MRotation;
		_31 += rotationOrigin.x; _32 += rotationOrigin.y; _33 += rotationOrigin.z;
		_31 += translation.x;    _32 += translation.y;    _33 += translation.z;
#endif
	}
	//-----------------------------------------------------------------------------------
	//! @brief �J�����̈ʒu�A������A����уJ�����̌������g�p���č�����W�n�̃r���[�s����쐬���܂��B
	//! @param [in]  rEye  �J�����̈ʒu�B 
	//! @param [in]  rEyeDirection   �J�����̌����B
	//! @param [in]  rUp   �J�����̌����܂ŁA��ʓI��<��0.0f�A1.0f�́A��0.0f>�B
	//-----------------------------------------------------------------------------------
	inline void MakeCameraLookToLH(
		const gt2Vector3& rEye,
		const gt2Vector3& rEyeDirection,
		const gt2Vector3& rUp = gt2Vector3(0, 1, 0))
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		DirectX::XMVECTOR a, b, c;
		a = rEye.GetXMVECTOR();
		b = rEyeDirection.GetXMVECTOR();
		c = rUp.GetXMVECTOR();
		*this = DirectX::XMMatrixLookToLH(a, b, c);
#else
		//zaxis = normal(rEyeDirection)
		//xaxis = normal(cross(Up, zaxis))
		//yaxis = cross(zaxis, xaxis)

		// xaxis.x           yaxis.x           zaxis.x          0
		// xaxis.y           yaxis.y           zaxis.y          0
		// xaxis.z           yaxis.z           zaxis.z          0
		//-dot(xaxis, eye)  -dot(yaxis, eye)  -dot(zaxis, eye)  1

		gt2Vector3 zaxis = rEyeDirection;
		zaxis.Normalize();

		gt2Vector3 xaxis;
		xaxis = rUp.Cross(zaxis);
		xaxis.Normalize();

		gt2Vector3 yaxis;
		yaxis = zaxis.Cross(xaxis);

		_11 = xaxis.x;
		_12 = yaxis.x;
		_13 = zaxis.x;
		_14 = 0;

		_21 = xaxis.y;
		_22 = yaxis.y;
		_23 = zaxis.y;
		_24 = 0;

		_31 = xaxis.z;
		_32 = yaxis.z;
		_33 = zaxis.z;
		_34 = 0;

		_41 = -xaxis.Dot(rEye);
		_42 = -yaxis.Dot(rEye);
		_43 = -zaxis.Dot(rEye);
		_44 = 1.0f;
#endif
	}
	//-----------------------------------------------------------------------------------
	//! @brief �J�����̈ʒu�A������A����уJ�����̌������g�p���ĉE����W�n�̃r���[�s����쐬���܂��B
	//! @param [in]  rEye  �J�����̈ʒu�B 
	//! @param [in]  rEyeDirection   �J�����̌����B
	//! @param [in]  rUp   �J�����̌����܂ŁA��ʓI��<��0.0f�A1.0f�́A��0.0f>�B
	//! @return  �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakeCameraLookToRH(
		const gt2Vector3& rEye,
		const gt2Vector3& rEyeDirection,
		const gt2Vector3& rUp = gt2Vector3(0, 1, 0))
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		DirectX::XMVECTOR a, b, c;
		a = rEye.GetXMVECTOR();
		b = rEyeDirection.GetXMVECTOR();
		c = rUp.GetXMVECTOR();
		*this = DirectX::XMMatrixLookToRH(a, b, c);
#else
		this->MakeCameraLookToLH(rEye, rEyeDirection*-1, rUp);
#endif
	}

	//-----------------------------------------------------------------------------------
	//! @brief ������W�n�r���[�s����쐬����B
	//! @param [in]  rEye  �J�����̈ʒu�B 
	//! @param [in]  rAt   �œ_�̈ʒu�B 
	//! @param [in]  rUp   �J�����̌����܂ŁA��ʓI��<��0.0f�A1.0f�́A��0.0f>�B
	//-----------------------------------------------------------------------------------
	inline void MakeCameraLookAtLH(
		const gt2Vector3& rEye,
		const gt2Vector3& rAt,
		const gt2Vector3& rUp = gt2Vector3(0, 1, 0))
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		DirectX::XMVECTOR a, b, c;
		a = rEye.GetXMVECTOR();
		b = rAt.GetXMVECTOR();
		c = rUp.GetXMVECTOR();
		*this = DirectX::XMMatrixLookAtLH(a, b, c);
#else
		this->MakeCameraLookToLH(rEye, rAt - rEye, rUp);
#endif
	}
	//-----------------------------------------------------------------------------------
	//! @brief �E����W�n�r���[�s����쐬����B
	//! @param [in]  rEye  �J�����̈ʒu�B 
	//! @param [in]  rAt   �œ_�̈ʒu�B 
	//! @param [in]  rUp   �J�����̌����܂ŁA��ʓI��<��0.0f�A1.0f�́A��0.0f>�B
	//! @return  �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakeCameraLookAtRH(
		const gt2Vector3& rEye,
		const gt2Vector3& rAt,
		const gt2Vector3& rUp = gt2Vector3(0, 1, 0))
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		DirectX::XMVECTOR a, b, c;
		a = rEye.GetXMVECTOR();
		b = rAt.GetXMVECTOR();
		c = rUp.GetXMVECTOR();
		*this = DirectX::XMMatrixLookAtRH(a, b, c);
#else
		this->MakeCameraLookToRH(rEye, rAt - rEye, rUp);
#endif
	}

	//-----------------------------------------------------------------------------------
	//! @brief �C�ӂ̖@���x�N�g���𒆐S�ɉ�]����s����쐬���܂��B
	//! @param [in]  rV     ��]�����L�q����@���x�N�g���B
	//! @param [in]  fAngle ��]�̊p�x (���W�A���P��)�B@n
	//!                     �p�x�́A��]���𒆐S�ɂ��Č��_���������������v���Œ�`�������̂ł�
	//! @return  �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakeRotationNormal(const gt2Vector3& rV, float fAngle)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixRotationNormal(rV.GetXMVECTOR(), fAngle();
#else
		gt2Vector3 vTemp = rV;
		float fSina, fCosa, fOmca;

		fSina = (float)sin(fAngle);
		fCosa = (float)cos(fAngle);
		fOmca = 1.0f - fCosa;
		//vTemp.Normalize();

		this->MakeIdentity();

		_11 = fOmca * vTemp.x * vTemp.x + fCosa;
		_21 = fOmca * vTemp.x * vTemp.y - fSina * vTemp.z;
		_31 = fOmca * vTemp.x * vTemp.z + fSina * vTemp.y;
		_12 = fOmca * vTemp.y * vTemp.x + fSina * vTemp.z;
		_22 = fOmca * vTemp.y * vTemp.y + fCosa;
		_32 = fOmca * vTemp.y * vTemp.z - fSina * vTemp.x;
		_13 = fOmca * vTemp.z * vTemp.x - fSina * vTemp.y;
		_23 = fOmca * vTemp.z * vTemp.y + fSina * vTemp.x;
		_33 = fOmca * vTemp.z * vTemp.z + fCosa;
#endif
	}
	//-----------------------------------------------------------------------------------
	//! @brief �^����ꂽ���ʂ��x�N�g���𔽉f����悤�ɐ݌v���ꂽ�ϊ��s����쐬���܂��B
	//! @param [in]  rP     ���˕���
	//! @return  �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakeReflect(const gt2Plane3& rP)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixReflect(rP.GetXMVECTOR());
#else
		gt2Plane3 pl = rP;
		pl.Normalize();
		gt2Vector3 vS = pl.vNormal * -2.0f;
		_11 = (pl.a * vS.x) + 1; _12 = pl.a * vS.y;      _13 = pl.a * vS.z;      _14 = 0.0f;
		_21 = pl.b * vS.x;      _22 = (pl.b * vS.y) + 1; _23 = pl.b * vS.z;      _24 = 0.0f;
		_31 = pl.c * vS.x;      _32 = pl.c * vS.y;      _33 = (pl.c * vS.z) + 1; _34 = 0.0f;
		_41 = pl.d * vS.x;      _42 = pl.d * vS.y;      _43 = pl.d * vS.z;      _44 = 1.0f;
#endif
	}

	//-----------------------------------------------------------------------------------
	//! @brief �C�ӂ̎�����]���ɂ��ĉ�]����s����쐬����B
	//! @param [in]  rV     ��]�����L�q����x�N�g��
	//! @param [in]  fAngle ��]�̊p�x (���W�A���P��)�B�p�x�́A��]������Ƃ��A���_���玞�v���̕����Ŏw�肵�܂��B
	//! @return  �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakeRotationAxis(const gt2Vector3& rV, float fAngle)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixRotationAxis(rV.GetXMVECTOR(), fAngle();
#else
		gt2Vector3 vTemp = rV;
		float fSina, fCosa, fOmca;

		fSina = (float)sin(fAngle);
		fCosa = (float)cos(fAngle);
		fOmca = 1.0f - fCosa;
		vTemp.Normalize();

		this->MakeIdentity();

		_11 = fOmca * vTemp.x * vTemp.x + fCosa;
		_21 = fOmca * vTemp.x * vTemp.y - fSina * vTemp.z;
		_31 = fOmca * vTemp.x * vTemp.z + fSina * vTemp.y;
		_12 = fOmca * vTemp.y * vTemp.x + fSina * vTemp.z;
		_22 = fOmca * vTemp.y * vTemp.y + fCosa;
		_32 = fOmca * vTemp.y * vTemp.z - fSina * vTemp.x;
		_13 = fOmca * vTemp.z * vTemp.x - fSina * vTemp.y;
		_23 = fOmca * vTemp.z * vTemp.y + fSina * vTemp.x;
		_33 = fOmca * vTemp.z * vTemp.z + fCosa;
#endif
	}


	//-----------------------------------------------------------------------------------
	//! @brief �N�H�[�^�j�I�������]�s����쐬���܂��B
	//! @param [in]  rQ       �N�H�[�^�j�I��
	//! @param [in]  rvCenter �A���J�[�ʒu
	//! @return  �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakeRotationQuaternion(const gt2Quaternion& rQ, const gt2Vector3& rvCenter)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixRotationQuaternion(rQ.GetXMVECTOR());

		float a1, a2, a3;
		a1 = rvCenter.x;
		a2 = rvCenter.y;
		a3 = rvCenter.z;

		_14 = a1 - a1 * _11 - a2 * _12 - a3 * _13;
		_24 = a2 - a1 * _21 - a2 * _22 - a3 * _23;
		_34 = a3 - a1 * _31 - a2 * _32 - a3 * _33;
#else
		float sqw = rQ.w*rQ.w;
		float sqx = rQ.x*rQ.x;
		float sqy = rQ.y*rQ.y;
		float sqz = rQ.z*rQ.z;
		_11 = sqx - sqy - sqz + sqw; // since sqw + sqx + sqy + sqz =1
		_22 = -sqx + sqy - sqz + sqw;
		_33 = -sqx - sqy + sqz + sqw;

		float tmp1 = rQ.x*rQ.y;
		float tmp2 = rQ.z*rQ.w;
		_12 = 2.0f * (tmp1 + tmp2);
		_21 = 2.0f * (tmp1 - tmp2);

		tmp1 = rQ.x*rQ.z;
		tmp2 = rQ.y*rQ.w;
		_13 = 2.0f * (tmp1 - tmp2);
		_31 = 2.0f * (tmp1 + tmp2);

		tmp1 = rQ.y*rQ.z;
		tmp2 = rQ.x*rQ.w;
		_23 = 2.0f * (tmp1 + tmp2);
		_32 = 2.0f * (tmp1 - tmp2);

		float a1, a2, a3;
		a1 = rvCenter.x;
		a2 = rvCenter.y;
		a3 = rvCenter.z;

		_14 = a1 - a1 * _11 - a2 * _12 - a3 * _13;
		_24 = a2 - a1 * _21 - a2 * _22 - a3 * _23;
		_34 = a3 - a1 * _31 - a2 * _32 - a3 * _33;
		_41 = _42 = _43 = 0.0f;
		_44 = 1.0f;
#endif
	}
	//-----------------------------------------------------------------------------------
	//! @brief �N�H�[�^�j�I�������]�s����쐬���܂��B
	//! @param [in]  rQ �N�H�[�^�j�I��
	//! @return  �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakeRotationQuaternion(const gt2Quaternion& rQ)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixRotationQuaternion(rQ.GetXMVECTOR());
#else
		_11 = 1.0f - (rQ.y * rQ.y + rQ.z * rQ.z) * 2.0f;
		_12 = 2.0f * (rQ.x * rQ.y + rQ.z * rQ.w);
		_13 = 2.0f * (rQ.x * rQ.z - rQ.y * rQ.w);
		_21 = 2.0f * (rQ.x * rQ.y - rQ.z * rQ.w);
		_22 = 1.0f - (rQ.x * rQ.x + rQ.z * rQ.z) * 2.0f;
		_23 = 2.0f * (rQ.y * rQ.z + rQ.x * rQ.w);
		_31 = 2.0f * (rQ.x * rQ.z + rQ.y * rQ.w);
		_32 = 2.0f * (rQ.y * rQ.z - rQ.x * rQ.w);
		_33 = 1.0f - (rQ.x * rQ.x + rQ.y * rQ.y) * 2.0f;

		//float sqw = rQ.w*rQ.w;
		//float sqx = rQ.x*rQ.x;
		//float sqy = rQ.y*rQ.y;
		//float sqz = rQ.z*rQ.z;
		//   // invs (�t�̕�������) �N�H�[�^�j�I�����܂����K������Ȃ��ꍇ�A�P�ɗv������܂��B
		//float invs = 1.0f / (sqx + sqy + sqz + sqw);
		//_11 = ( sqx - sqy - sqz + sqw)*invs ; // since sqw + sqx + sqy + sqz =1/invs*invs
		//_22 = (-sqx + sqy - sqz + sqw)*invs ;
		//_33 = (-sqx - sqy + sqz + sqw)*invs ;
		//float tmp1 = rQ.x*rQ.y;
		//float tmp2 = rQ.z*rQ.w;
		//_12 = 2.0f * (tmp1 + tmp2)*invs ;
		//_21 = 2.0f * (tmp1 - tmp2)*invs ;
		//tmp1 = rQ.x*rQ.z;
		//tmp2 = rQ.y*rQ.w;
		//_13 = 2.0f * (tmp1 - tmp2)*invs ;
		//_31 = 2.0f * (tmp1 + tmp2)*invs ;
		//tmp1 = rQ.y*rQ.z;
		//tmp2 = rQ.x*rQ.w;
		//_23 = 2.0f * (tmp1 + tmp2)*invs ;
		//_32 = 2.0f * (tmp1 - tmp2)*invs ;

		_41 = _42 = _43 = 0.0f;
		_44 = 1.0f;
#endif
	}


	//-----------------------------------------------------------------------------------
	//! @brief x ������]���ɂ��ĉ�]����s����쐬����B
	//! @param [in]  fAngle ��]�̊p�x (���W�A���P��)�B@n
	//!                     �p�x�́A��]���𒆐S�ɂ��Č��_���������������v���Œ�`�������̂ł�
	//! @return  �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakeRotationX(float fAngle)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixRotationX(fAngle);
#else
		float fCosa = cosf(fAngle);
		float fSina = sinf(fAngle);

		this->MakeIdentity();

		_22 = fCosa; _23 = fSina;
		_32 = -fSina; _33 = fCosa;
#endif
	}

	//-----------------------------------------------------------------------------------
	//! @brief XYZ����]�̐ݒ�
	//! @param [in]  rvRadian radian �e���ɂ����郉�W�A���P�ʂł̉�]�p�x
	//! @return  �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakeRotationXYZ(const gt2Vector3& rvRadian)
	{
		this->MakeIdentity();
		float sinX = sinf(rvRadian.x);
		float cosX = cosf(rvRadian.x);
		float sinY = sinf(rvRadian.y);
		float cosY = cosf(rvRadian.y);
		float sinZ = sinf(rvRadian.z);
		float cosZ = cosf(rvRadian.z);
		_11 = cosY * cosZ;
		_12 = sinX * sinY * cosZ - cosX * sinZ;
		_13 = cosX * sinY * cosZ + sinX * sinZ;

		_21 = cosY * sinZ;
		_22 = sinX * sinY * sinZ + cosX * cosZ;
		_23 = cosX * sinY * sinZ - sinX * cosZ;

		_31 = -sinY;
		_32 = sinX * cosY;
		_33 = cosX * cosY;
	}

	//-----------------------------------------------------------------------------------
	//! @brief XZY����]�̐ݒ�
	//! @param [in]  rvRadian radian �e���ɂ����郉�W�A���P�ʂł̉�]�p�x
	//! @return  �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakeRotationXZY(const gt2Vector3& rvRadian)
	{
		this->MakeIdentity();

		float sinX = sinf(rvRadian.x);
		float cosX = cosf(rvRadian.x);
		float sinY = sinf(rvRadian.y);
		float cosY = cosf(rvRadian.y);
		float sinZ = sinf(rvRadian.z);
		float cosZ = cosf(rvRadian.z);

		_11 = cosY * cosZ;
		_12 = -sinZ;
		_13 = cosZ * sinY;

		_21 = sinX * sinY + cosX * cosY * sinZ;
		_22 = cosX * cosZ;
		_23 = -cosY * sinX + cosX * sinY * sinZ;

		_31 = -cosX * sinY + cosY * sinX * sinZ;
		_32 = cosZ * sinX;
		_33 = cosX * cosY + sinX * sinY * sinZ;
	}

	//-----------------------------------------------------------------------------------
	//! @brief y ������]���ɂ��ĉ�]����s����쐬����B
	//! @param [in]  fAngle ��]�̊p�x (���W�A���P��)�B@n
	//!                     �p�x�́A��]���𒆐S�ɂ��Č��_���������������v���Œ�`�������̂ł�
	//! @return  �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakeRotationY(float fAngle)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixRotationY(fAngle);
#else
		float fCosa;
		float fSina;
		fCosa = (float)cos(fAngle);
		fSina = (float)sin(fAngle);

		this->MakeIdentity();

		_11 = fCosa; _13 = -fSina;
		_31 = fSina; _33 = fCosa;
#endif
	}

	//-----------------------------------------------------------------------------------
	//! @brief YXZ����]�̐ݒ�
	//! @param [in]  rvRadian �e���ɂ����郉�W�A���P�ʂł̉�]�p�x
	//! @return  �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakeRotationYXZ(const gt2Vector3& rvRadian)
	{
		this->MakeIdentity();

		float sinX = sinf(rvRadian.x);
		float cosX = cosf(rvRadian.x);
		float sinY = sinf(rvRadian.y);
		float cosY = cosf(rvRadian.y);
		float sinZ = sinf(rvRadian.z);
		float cosZ = cosf(rvRadian.z);

		_11 = cosY * cosZ + sinX * sinY * sinZ;
		_12 = cosZ * sinX * sinY - cosY * sinZ;
		_13 = cosX * sinY;

		_21 = cosX * sinZ;
		_22 = cosX * cosZ;
		_23 = -sinX;

		_31 = -cosZ * sinY + cosY * sinX * sinZ;
		_32 = cosY * cosZ * sinX + sinY * sinZ;
		_33 = cosX * cosY;
	}

	//-----------------------------------------------------------------------------------
	//! @brief YZX����]�̐ݒ�
	//! @param [in]  rvRadian �e���ɂ����郉�W�A���P�ʂł̉�]�p�x
	//! @return  �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakeRotationYZX(const gt2Vector3& rvRadian)
	{
		this->MakeIdentity();

		float sinX = sinf(rvRadian.x);
		float cosX = cosf(rvRadian.x);
		float sinY = sinf(rvRadian.y);
		float cosY = cosf(rvRadian.y);
		float sinZ = sinf(rvRadian.z);
		float cosZ = cosf(rvRadian.z);


		_11 = cosY * cosZ;
		_12 = sinX * sinY - cosX * cosY * sinZ;
		_13 = cosX * sinY + cosY * sinX * sinZ;

		_21 = sinZ;
		_22 = cosX * cosZ;
		_23 = -cosZ * sinX;

		_31 = -cosZ * sinY;
		_32 = cosY * sinX + cosX * sinY * sinZ;
		_33 = cosX * cosY - sinX * sinY * sinZ;
	}
	//-----------------------------------------------------------------------------------
	//! @brief z ������]���ɂ��ĉ�]����s����쐬����B
	//! @param [in]  fAngle ��]�̊p�x (���W�A���P��)�B@n
	//!                     �p�x�́A��]���𒆐S�ɂ��Č��_���������������v���Œ�`�������̂ł�
	//! @return  �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakeRotationZ(float fAngle)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixRotationZ(fAngle);
#else
		float fCosa;
		float fSina;
		fCosa = (float)cos(fAngle);
		fSina = (float)sin(fAngle);

		this->MakeIdentity();

		_11 = fCosa; _12 = fSina;
		_21 = -fSina; _22 = fCosa;
#endif
	}

	//-----------------------------------------------------------------------------------
	//! @brief ZXY����]�̐ݒ�
	//! @param [in]  rvRadian �e���ɂ����郉�W�A���P�ʂł̉�]�p�x
	//! @return  �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakeRotationZXY(const gt2Vector3& rvRadian)
	{
		this->MakeIdentity();

		float sinX = sinf(rvRadian.x);
		float cosX = cosf(rvRadian.x);
		float sinY = sinf(rvRadian.y);
		float cosY = cosf(rvRadian.y);
		float sinZ = sinf(rvRadian.z);
		float cosZ = cosf(rvRadian.z);

		_11 = cosY * cosZ - sinX * sinY * sinZ;
		_12 = -cosX * sinZ;
		_13 = cosZ * sinY + cosY * sinX * sinZ;

		_21 = cosZ * sinX * sinY + cosY * sinZ;
		_22 = cosX * cosZ;
		_23 = -cosY * cosZ * sinX + sinY * sinZ;

		_31 = -cosX * sinY;
		_32 = sinX;
		_33 = cosX * cosY;
	}

	//-----------------------------------------------------------------------------------
	//! @brief ZYX����]�̐ݒ�
	//! @param [in]  rvRadian �e���ɂ����郉�W�A���P�ʂł̉�]�p�x
	//! @return  �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakeRotationZYX(const gt2Vector3& rvRadian)
	{
		this->MakeIdentity();

		float sinX = sinf(rvRadian.x);
		float cosX = cosf(rvRadian.x);
		float sinY = sinf(rvRadian.y);
		float cosY = cosf(rvRadian.y);
		float sinZ = sinf(rvRadian.z);
		float cosZ = cosf(rvRadian.z);

		_11 = cosY * cosZ;
		_12 = cosX * cosZ + sinX * sinY * sinZ;
		_13 = cosX * cosZ * sinY + sinX * sinZ;

		_21 = cosY * sinZ;
		_22 = cosX * cosZ;
		_23 = -cosZ * sinX + cosX * sinY * sinZ;

		_31 = -sinY;
		_32 = cosY * sinX;
		_33 = cosX * cosY;
	}

	//-----------------------------------------------------------------------------------
	//! @brief ���[�A�s�b�`�A���[�����w�肵�čs����쐬����B
	//! @param [in]  yaw   y ���𒆐S�Ƃ��郈�[ (���W�A���P��)�B
	//! @param [in]  pitch x ���𒆐S�Ƃ��郈�[ (���W�A���P��)�B
	//! @param [in]  roll  z ���𒆐S�Ƃ��郈�[ (���W�A���P��)�B
	//! @return  �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakeRotationYawPitchRoll(float yaw, float pitch, float roll)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
#else
		float fCY = cosf(yaw);
		float fSY = sinf(yaw);
		float fCP = cosf(pitch);
		float fSP = sinf(pitch);
		float fCR = cosf(roll);
		float fSR = sinf(roll);
		_11 = fCY *  fCR;
		_12 = -fSP * -fSY *  fCR + fCP * fSR;
		_13 = fCP * -fSY *  fCR + fSP * fSR;

		_21 = fCY * -fSR;
		_22 = -fSP * -fSY * -fSR + fCP * fCR;
		_23 = fCP * -fSY * -fSR + fSP * fCR;

		_31 = fSY;
		_32 = -fSP *  fCY;
		_33 = fCP *  fCY;
#endif
	}
	//-----------------------------------------------------------------------------------
	//! @brief ���[�A�s�b�`�A���[�����w�肵�čs����쐬����B
	//! @param [in]  v   x:Pitch, y:Yaw, z:Roll
	//! @return  �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakeRollPitchYawFromVector(const gt2Vector3 &v)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixRotationRollPitchYawFromVector(v.GetXMVECTOR());
#else
		this->MakeRotationYawPitchRoll(v.y, v.x, v.z);
#endif
	}

	//-----------------------------------------------------------------------------------
	//! @brief 2 �̍s��̐ς��v�Z���A���ʂ�Ԃ��B
	//! @param [in]  rM   �Ώۍs��
	//! @return  ���Z���ʂ�Ԃ�
	//-----------------------------------------------------------------------------------
	inline gt2Matrix4x4 Multiply(const gt2Matrix4x4& rM) const
	{
		return *this * rM;
	}

	//-----------------------------------------------------------------------------------
	//! @brief 2 �̍s��̐ς��v�Z���A���ʂ�Ԃ��BrM1�~rM2
	//! @param [in]  rM1   �Ώۍs�� 1
	//! @param [in]  rM2   �Ώۍs�� 2
	//! @return  ���Z���ʂ�Ԃ�
	//-----------------------------------------------------------------------------------
	inline static gt2Matrix4x4 Multiply(const gt2Matrix4x4& rM1, const gt2Matrix4x4& rM2)
	{
		gt2Matrix4x4 out;
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		out = DirectX::XMMatrixMultiply((DirectX::XMMATRIX)rM1, (DirectX::XMMATRIX)rM2();
#else
		out._11 = rM1._11*rM2._11 + rM1._12*rM2._21 + rM1._13*rM2._31 + rM1._14*rM2._41;
		out._12 = rM1._11*rM2._12 + rM1._12*rM2._22 + rM1._13*rM2._32 + rM1._14*rM2._42;
		out._13 = rM1._11*rM2._13 + rM1._12*rM2._23 + rM1._13*rM2._33 + rM1._14*rM2._43;
		out._14 = rM1._11*rM2._14 + rM1._12*rM2._24 + rM1._13*rM2._34 + rM1._14*rM2._44;

		out._21 = rM1._21*rM2._11 + rM1._22*rM2._21 + rM1._23*rM2._31 + rM1._24*rM2._41;
		out._22 = rM1._21*rM2._12 + rM1._22*rM2._22 + rM1._23*rM2._32 + rM1._24*rM2._42;
		out._23 = rM1._21*rM2._13 + rM1._22*rM2._23 + rM1._23*rM2._33 + rM1._24*rM2._43;
		out._24 = rM1._21*rM2._14 + rM1._22*rM2._24 + rM1._23*rM2._34 + rM1._24*rM2._44;

		out._31 = rM1._31*rM2._11 + rM1._32*rM2._21 + rM1._33*rM2._31 + rM1._34*rM2._41;
		out._32 = rM1._31*rM2._12 + rM1._32*rM2._22 + rM1._33*rM2._32 + rM1._34*rM2._42;
		out._33 = rM1._31*rM2._13 + rM1._32*rM2._23 + rM1._33*rM2._33 + rM1._34*rM2._43;
		out._34 = rM1._31*rM2._14 + rM1._32*rM2._24 + rM1._33*rM2._34 + rM1._34*rM2._44;

		out._41 = rM1._41*rM2._11 + rM1._42*rM2._21 + rM1._43*rM2._31 + rM1._44*rM2._41;
		out._42 = rM1._41*rM2._12 + rM1._42*rM2._22 + rM1._43*rM2._32 + rM1._44*rM2._42;
		out._43 = rM1._41*rM2._13 + rM1._42*rM2._23 + rM1._43*rM2._33 + rM1._44*rM2._43;
		out._44 = rM1._41*rM2._14 + rM1._42*rM2._24 + rM1._43*rM2._34 + rM1._44*rM2._44;
#endif
		return out;
	}

	//-----------------------------------------------------------------------------------
	//! @brief 2 �̍s��̐ς̓]�u�s����v�Z���܂��B
	//! @param [in]  rM1   �Ώۍs�� 1
	//! @param [in]  rM2   �Ώۍs�� 2
	//! @return  M1 �� M2 �̐ς̓]�u�s���Ԃ��܂��B
	//-----------------------------------------------------------------------------------
	inline static gt2Matrix4x4 MultiplyTranspose(const gt2Matrix4x4& rM1, const gt2Matrix4x4& rM2)
	{
		gt2Matrix4x4 out;
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		out = DirectX::XMMatrixMultiplyTranspose((DirectX::XMMATRIX)rM1, (DirectX::XMMATRIX)rM2();
#else
		out = Multiply(rM1, rM2);
		out = out.GetTranspose();
#endif
		return out;
	}



	//-----------------------------------------------------------------------------------
	//! @brief �s��̓]�u�s���Ԃ��B
	//! @return  �s��̓]�u�s���Ԃ��B
	//-----------------------------------------------------------------------------------
	inline gt2Matrix4x4 GetTranspose() const
	{
		gt2Matrix4x4 out;
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		out = DirectX::XMMatrixTranspose((DirectX::XMMATRIX)*this);
#else
		for (int c = 0; c<4; ++c)
			for (int r = 0; r<4; ++r)
				out.m[r][c] = m[c][r];
#endif
		return out;
	}


	//-----------------------------------------------------------------------------------
	//! @brief ��]�s�񂩂�N�H�[�^�j�I�����쐬����B
	//! @return  �N�H�[�^�j�I������Ԃ�
	//-----------------------------------------------------------------------------------
	inline gt2Quaternion GetRotationQuaternion() const
	{
		gt2Quaternion out;
		float fS, fD;
		float fTrace = _11 + _22 + _33 + 1.0f;
		if (fTrace > 0.0f) {
			fS = 0.5f / sqrtf(fTrace);
			out.w = 0.25f / fS;
			out.x = (_32 - _23) * fS;
			out.y = (_13 - _31) * fS;
			out.z = (_21 - _12) * fS;
		}
		else {
			if (_11 > _22 && _11 > _33) {
				fS = 2.0f * sqrtf(1.0f + _11 - _22 - _33);
				fD = 1.0f / fS;
				out.w = (_23 - _32) * fD;
				out.x = 0.25f * fS;
				out.y = (_12 + _21) * fD;
				out.z = (_13 + _31) * fD;
			}
			else if (_22 > _33) {
				fS = 2.0f * sqrtf(1.0f + _22 - _11 - _33);
				fD = 1.0f / fS;
				out.w = (_13 - _31) * fD;
				out.x = (_12 + _21) * fD;
				out.y = 0.25f * fS;
				out.z = (_23 + _32) * fD;
			}
			else {
				fS = 2.0f * sqrtf(1.0f + _33 - _11 - _22);
				fD = 1.0f / fS;
				out.w = (_12 - _21) * fD;
				out.x = (_13 + _31) * fD;
				out.y = (_23 + _32) * fD;
				out.z = 0.25f * fS;
			}
		}

		return out;
	}

	//-----------------------------------------------------------------------------------
	//! @brief �W���� 3D �ϊ��s����A�X�J���[�����A��]�����A���s�ړ������ɕ�������B
	//! @param [out] pOutScale       x�Ay�Az ���ɉ����ēK�p�����X�P�[�����O�W�����܂ޏo�� gt2Vector3 �ւ̃|�C���^�B
	//! @param [out] pOutRotation    ��]���L�q���� gt2Quaternion �\���̂ւ̃|�C���^�B
	//! @param [out] pOutPosition ���s�ړ����L�q���� MCXVECTOR3 �x�N�g���ւ̃|�C���^�B
	//! @return  �Ȃ�
	//-----------------------------------------------------------------------------------
	inline bool GetMatrixDecompose(
		gt2Vector3 *pOutScale,
		gt2Quaternion *pOutRotation,
		gt2Vector3 *pOutPosition
	) const
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		DirectX::XMVECTOR a, b, c;
		DirectX::XMMatrixDecompose(&a, &b, &c, (DirectX::FXMMATRIX)*this);
		*pOutScale = a;
		*pOutRotation = b;
		*pOutPosition = c;
#else
		//gt2Vector3 vCols1(_11, _12, _13);
		//gt2Vector3 vCols2(_21, _22, _23);
		//gt2Vector3 vCols3(_31, _32, _33);

		//pOutScale->x = vCols1.Length();
		//pOutScale->y = vCols2.Length();
		//pOutScale->z = vCols3.Length();

		//pOutPosition->x = _41 / (pOutScale->x == 0 ? 1 : pOutScale->x);
		//pOutPosition->y = _42 / (pOutScale->y == 0 ? 1 : pOutScale->y);
		//pOutPosition->z = _43 / (pOutScale->z == 0 ? 1 : pOutScale->z);

		//*pOutRotation = this->GetRotationQuaternion();
		//----------------------------------------------------
		static const gt2Vector3 *pvCanonicalBasis[3] = {
			&g_VF3IdentityR0,
			&g_VF3IdentityR1,
			&g_VF3IdentityR2
		};

		assert(pOutScale != nullptr);
		assert(pOutRotation != nullptr);
		assert(pOutPosition != nullptr);

		// �ʒu�̎擾
		pOutPosition->x = _41;
		pOutPosition->y = _42;
		pOutPosition->z = _43;

		gt2Vector3 *ppvBasis[3];
		gt2Matrix4x4 matTemp;
		ppvBasis[0] = (gt2Vector3*)matTemp.m[0];
		ppvBasis[1] = (gt2Vector3*)matTemp.m[1];
		ppvBasis[2] = (gt2Vector3*)matTemp.m[2];

		memcpy(matTemp.m[0], m[0], sizeof(gt2Vector4));
		memcpy(matTemp.m[1], m[1], sizeof(gt2Vector4));
		memcpy(matTemp.m[2], m[2], sizeof(gt2Vector4));
		memcpy(matTemp.m[3], g_VF4IdentityR3.v, sizeof(gt2Vector4));

		float *pfScales = pOutScale->v;

		size_t a, b, c;
		pfScales[0] = ppvBasis[0]->Length();
		pfScales[1] = ppvBasis[1]->Length();
		pfScales[2] = ppvBasis[2]->Length();

		MC_3RANKDECOMPOSE(a, b, c, pfScales[0], pfScales[1], pfScales[2]);

		if (pfScales[a] < GT2_DECOMP_EPSILON)
		{
			ppvBasis[a][0] = pvCanonicalBasis[a][0];
		}
		ppvBasis[a]->Normalize();

		if (pfScales[b] < GT2_DECOMP_EPSILON)
		{
			size_t aa, bb, cc;
			float fAbsX, fAbsY, fAbsZ;

			fAbsX = fabsf(ppvBasis[a]->x);
			fAbsY = fabsf(ppvBasis[a]->y);
			fAbsZ = fabsf(ppvBasis[a]->z);

			MC_3RANKDECOMPOSE(aa, bb, cc, fAbsX, fAbsY, fAbsZ);
			*ppvBasis[b] = ppvBasis[a]->Cross(*pvCanonicalBasis[cc]);
		}
		ppvBasis[b]->Normalize();

		if (pfScales[c] < GT2_DECOMP_EPSILON)
		{
			*ppvBasis[c] = ppvBasis[a]->Cross(*pvCanonicalBasis[b]);
		}
		ppvBasis[c]->Normalize();

		float fDet = matTemp.GetDeterminant();

		// ���W�n�̗�������`�F�b�N���邽�߂ɃN���C�}�[�̃��[�����g�p���Ă��܂��B
		if (fDet < 0.0f)
		{
			// �X�P�[����ے肵�Ax����̊��x�N�g���𔽓]�����č��W�n��؂�ւ���
			pfScales[a] = -pfScales[a];
			*ppvBasis[a] *= -1;

			fDet = -fDet;
		}

		fDet -= 1.0f;
		fDet *= fDet;

		if (GT2_DECOMP_EPSILON < fDet)
		{
			// ����������SRT�s��
			return false;
		}

		// �s�񂩂�N�H�[�^�j�I���𐶐�
		*pOutRotation = matTemp.GetRotationQuaternion();
#endif
		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief �s��̍s�񎮂��v�Z���܂��B
	//! @return  �s�񎮂�Ԃ��܂�
	//-----------------------------------------------------------------------------------
	inline float GetDeterminant()
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		auto ret = DirectX::XMMatrixDeterminant((DirectX::FXMMATRIX)*this);

		return ret.m128_f32[0];
#else
		return (_11 * _22 - _12 * _21) * (_33 * _44 - _34 * _43) -
			(_11 * _23 - _13 * _21) * (_32 * _44 - _34 * _42) +
			(_11 * _24 - _14 * _21) * (_32 * _43 - _33 * _42) +
			(_12 * _23 - _13 * _22) * (_31 * _44 - _34 * _41) -
			(_12 * _24 - _14 * _22) * (_31 * _43 - _33 * _41) +
			(_13 * _24 - _14 * _23) * (_31 * _42 - _32 * _41);
#endif
	}
	//-----------------------------------------------------------------------------------
	//! @brief �s��͒P�ʍs��ł��邩�ǂ������e�X�g���܂��B
	//! @return  �P�ʍs��̏ꍇtrue
	//-----------------------------------------------------------------------------------
	inline bool IsIdentity()
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		return DirectX::XMMatrixIsIdentity((DirectX::FXMMATRIX)*this);
#else
		return
			_11 == 1 && _12 == 0 && _13 == 0 && _14 == 0 &&
			_21 == 0 && _22 == 1 && _23 == 0 && _24 == 0 &&
			_31 == 0 && _32 == 1 && _33 == 0 && _34 == 0 &&
			_41 == 0 && _42 == 1 && _43 == 0 && _44 == 0;
#endif
	}
	//-----------------------------------------------------------------------------------
	//! @brief �s��̗v�f�̂����ꂩ�����܂��͕��̖�����ł��邩�ǂ������e�X�g���܂��B
	//! @return  ������̏ꍇtrue
	//-----------------------------------------------------------------------------------
	inline bool IsInfinite()
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		return DirectX::XMMatrixIsInfinite((DirectX::FXMMATRIX)*this);
#else
		size_t i = 16;
		const uint32_t *pWork = (const uint32_t *)(m[0]);
		do {
			// �������j�b�g�ɒl���t�F�b�`
			uint32_t uTest = pWork[0];
			// �L�����폜
			uTest &= 0x7FFFFFFFU;
			// INF is 0x7F800000
			if (uTest == 0x7F800000U) {
				break;      // INF��������܂���
			}
			++pWork;        // ���̃G���g���[
		} while (--i);
		return (i != 0);      // i == 0 �̏ꍇ�����}�b�`���Ȃ�
#endif
	}
	//-----------------------------------------------------------------------------------
	//! @brief �s��̗v�f�̂����ꂩ��NaN���ǂ������e�X�g����B
	//! @return  NaN�̏ꍇtrue
	//-----------------------------------------------------------------------------------
	inline bool IsNaN()
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		return DirectX::XMMatrixIsNaN((DirectX::FXMMATRIX)*this);
#else

		size_t i = 16;
		const uint32_t *pWork = (const uint32_t *)(m[0]);
		do {
			// �������j�b�g�ɒl���t�F�b�`
			uint32_t uTest = pWork[0];
			// �L�����폜
			uTest &= 0x7FFFFFFFU;
			// NaN �� 0x7FFFFFFF �C���N���[�V�u����� 0x7F800001
			uTest -= 0x7F800001U;
			if (uTest<0x007FFFFFU) {
				break;      // NaN��������܂���
			}
			++pWork;        // ���̃G���g���[
		} while (--i);
		return (i != 0);      // i == 0 �̏ꍇ�����}�b�`���Ȃ�
#endif
	}

	//-----------------------------------------------------------------------------------
	//! @brief �W���� 3D �ϊ��s����A�X�J���[�����A��]�����A���s�ړ������ɕ�������B
	//! @param [out] rOutScale       x�Ay�Az ���ɉ����ēK�p�����X�P�[�����O�W�����܂ޏo�� gt2Vector3 �ւ̃|�C���^�B
	//! @param [out] rOutRotation    ��]���L�q���� gt2Quaternion �\���̂ւ̃|�C���^�B
	//! @param [out] rOutTranslation ���s�ړ����L�q���� MCXVECTOR3 �x�N�g���ւ̃|�C���^�B
	//! @return  �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void GetMatrixDecompose(
		gt2Vector3& rOutScale,
		gt2Quaternion& rpOutRotation,
		gt2Vector3& rOutPosition
	) const
	{
		this->GetMatrixDecompose(&rOutScale, &rpOutRotation, &rOutPosition);
	}


	//-----------------------------------------------------------------------------------
	//! @brief �J�����̌����̃x�N�g�����擾����
	//! @return  �J�����̌����̃x�N�g�����擾����
	//-----------------------------------------------------------------------------------
	inline gt2Vector3 GetLookAt() const
	{
		gt2Vector3 ret = gt2Vector3(_13, _23, _33);
		ret.Normalize();
		return ret;
	}

	//-----------------------------------------------------------------------------------
	//! @brief �w�肳�ꂽ�s��ɂ��x�N�g�� (x, y, z) �����W�ϊ�����B
	//! @param [in]  rV3    3�v�f�x�N�g��
	//! @return  ���Z���ʂ�Ԃ�
	//-----------------------------------------------------------------------------------
	inline gt2Vector4 Vec3Transform(const gt2Vector3& rV3) const
	{
		gt2Vector4 out;
		out.x = rV3.x * (_11)+rV3.y * (_21)+rV3.z * (_31)+(_41);
		out.y = rV3.x * (_12)+rV3.y * (_22)+rV3.z * (_32)+(_42);
		out.z = rV3.x * (_13)+rV3.y * (_23)+rV3.z * (_33)+(_43);
		out.w = rV3.x * (_14)+rV3.y * (_24)+rV3.z * (_34)+(_44);
		return out;
	}

	//-----------------------------------------------------------------------------------
	//! @brief �w�肳�ꂽ�s��ɂ�� 4D �x�N�g�������W�ϊ�����B
	//! @param [in]  rV4    4�v�f�x�N�g��
	//! @return  ���Z���ʂ�Ԃ�
	//-----------------------------------------------------------------------------------
	inline gt2Vector4 Vec4Transform(const gt2Vector4& rV4) const
	{
		gt2Vector4 out;
		out.x = rV4.x * (_11)+rV4.y * (_21)+rV4.z * (_31)+rV4.w * (_41);
		out.y = rV4.x * (_12)+rV4.y * (_22)+rV4.z * (_32)+rV4.w * (_42);
		out.z = rV4.x * (_13)+rV4.y * (_23)+rV4.z * (_33)+rV4.w * (_43);
		out.w = rV4.x * (_14)+rV4.y * (_24)+rV4.z * (_34)+rV4.w * (_44);
		return out;
	}

	//-----------------------------------------------------------------------------------
	//! @brief �����_���W�����
	//! @param [in]  rvHear    ���_�x�N�g��
	//! @param [in]  rvLookAt  ���_��x�N�g��
	//! @return  �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakeLookAt(const gt2Vector3& rvHear, const gt2Vector3& rvLookAt)
	{
		gt2Matrix4x4  matTemp, matTemp2, matRotX, matRotY;
		gt2Vector3  vDist;
		float     mag_xz, mag_xyz;
		float     cos_x, sin_x, cos_y, sin_y;

		vDist = rvLookAt - rvHear;
		mag_xyz = vDist.Length();
		vDist.y = 0.0f;
		mag_xz = vDist.Length();
		vDist = rvLookAt - rvHear;

		if (1e-6f > mag_xyz) mag_xyz = 0.0001f;
		if (1e-6f > mag_xz)  mag_xz = 0.0001f;

		cos_y = vDist.z / mag_xz;
		sin_y = vDist.x / mag_xz;
		cos_x = mag_xz / mag_xyz;
		sin_x = -vDist.y / mag_xyz;

		// MAKE MATRIX
		matTemp.SetTranslation(rvHear);

		matRotX.MakeIdentity();
		matRotX._22 = cos_x;
		matRotX._23 = sin_x;
		matRotX._32 = -sin_x;
		matRotX._33 = cos_x;

		matRotY.MakeIdentity();
		matRotY._11 = cos_y;
		matRotY._13 = -sin_y;
		matRotY._31 = sin_y;
		matRotY._33 = cos_y;

		matTemp2 = matRotX * matRotY;
		*this = matTemp2 * matTemp;
	}

	//-----------------------------------------------------------------------------------
	//! @brief �r���{�[�h�}�g���b�N�X�쐬�B��]�}�g���b�N�X�͎��̔C�ӂ̃Z�b�g����쐬@n
	//!        �}�g���b�N�X�̍ŏ���3�J�����ɂ����̎��l���i�[����B
	//! @param [in]  rRight    �x�N�g��
	//! @param [in]  rUp       �A�b�v�x�N�g��
	//! @param [in]  rLook     ���_�x�N�g��
	//! @param [in]  rPos      �ʒu�x�N�g��
	//! @return  �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakeBillboardMatrix(const gt2Vector3& rRight, const gt2Vector3& rUp, const gt2Vector3& rLook, const gt2Vector3& rPos)
	{
		_11 = rRight.x;
		_12 = rRight.y;
		_13 = rRight.z;
		_14 = 0.0f;
		_21 = rUp.x;
		_22 = rUp.y;
		_23 = rUp.z;
		_24 = 0.0f;
		_31 = rLook.x;
		_32 = rLook.y;
		_33 = rLook.z;
		_34 = 0.0f;
		_41 = rPos.x;
		_42 = rPos.y;
		_43 = rPos.z;
		_44 = 1.0f;
	}
};


//======================================================================================
//! @brief 2�~2 �̃}�g���b�N�X
//======================================================================================
struct gt2Matrix2x2 {
	union {
		struct {
			float _11, _12;
			float _21, _22;
		};
		float m[2][2];
		float mm[4];
	};

	//! @name �R���X�g���N�^
	//@{
	inline gt2Matrix2x2()
	{
		this->MakeIdentity();
	}
	inline gt2Matrix2x2(const float * pF)
	{
		memcpy(this, pF, sizeof(gt2Matrix2x2));
	}
	inline gt2Matrix2x2(const gt2Matrix2x2& rM)
	{
		*this = rM;
	}
	inline gt2Matrix2x2(
		float f11, float f12,
		float f21, float f22
	) : _11(f11), _12(f12),
		_21(f21), _22(f22)
	{
	}
	//@}


	//gt2Matrix2x2& operator= (const b2Mat22& m22) { memcpy(this, &m22, sizeof(b2Mat22)); return *this; }

	//! @name  2 �����Z�q
	//@{
	inline gt2Matrix2x2
		operator * (const gt2Matrix2x2& tmp) const
	{
		gt2Matrix2x2 ret;
		ret._11 = _11*tmp._11 + _12*tmp._21;
		ret._12 = _11*tmp._12 + _12*tmp._22;

		ret._21 = _21*tmp._11 + _22*tmp._21;
		ret._22 = _21*tmp._12 + _22*tmp._22;


		return ret;
	}
	inline gt2Matrix2x2
		operator + (const gt2Matrix2x2& tmp) const
	{
		gt2Matrix2x2 ret;
		ret._11 = _11 + tmp._11;
		ret._12 = _12 + tmp._12;

		ret._21 = _21 + tmp._21;
		ret._22 = _22 + tmp._22;
		return ret;
	}
	inline gt2Matrix2x2
		operator - (const gt2Matrix2x2& tmp) const
	{
		gt2Matrix2x2 ret;
		ret._11 = _11 - tmp._11;
		ret._12 = _12 - tmp._12;

		ret._21 = _21 - tmp._21;
		ret._22 = _22 - tmp._22;
		return ret;
	}
	inline gt2Matrix2x2
		operator * (const float &tmp) const
	{
		gt2Matrix2x2 ret;
		ret._11 = _11*tmp;
		ret._12 = _12*tmp;

		ret._21 = _21*tmp;
		ret._22 = _22*tmp;

		return ret;
	}
	inline gt2Matrix2x2
		operator / (const float &tmp) const
	{
		gt2Matrix2x2 ret;
		float factor = 1.0f / tmp;

		ret._11 = _11*factor;
		ret._12 = _12*factor;

		ret._21 = _21*factor;
		ret._22 = _22*factor;
		return ret;
	}
	//@}

	//-----------------------------------------------------------------------------------
	//! @brief  �s��̋t�s����v�Z����B
	//! @param [out]  pDeterminant �s��̍s�񎮂��܂� float �l�ւ̃|�C���^�B@n
	//!                            �s�񎮂��s�v�̏ꍇ�́A���̃p�����[�^�� nullptr ��ݒ肷��B
	//! @param [out]  pOut         ���Z���ʂł��� gt2Matrix4x4 �\���̂ւ̃|�C���^�B
	//! @return �t�s��̌v�Z�����s�����ꍇ�́Afalse ��Ԃ��B
	//-----------------------------------------------------------------------------------
	inline bool GetInverse(float *pDeterminant, gt2Matrix2x2* pOut) const
	{
		float d;

		d = (_11 *_22) - (_21*_12);


		if (d == 0.0f)
			return false;

		d = 1.0f / d;


		pOut->_11 = d * _22;
		pOut->_12 = -d * _12;
		pOut->_21 = -d * _21;
		pOut->_22 = d * _11;


		if (pDeterminant != nullptr) *pDeterminant = d;

		return true;
	}

	//-----------------------------------------------------------------------------------
	//! @brief  4x4�s���2x2�s��ɃN���b�v����
	//! @param [in]  rMX gt2Matrix4x4
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void ClipMCXMATRIX(const gt2Matrix4x4 &rMX) {
		m[0][0] = rMX._11; m[0][1] = rMX._12;
		m[1][0] = rMX._21; m[1][1] = rMX._22;
	}

	//-----------------------------------------------------------------------------------
	//! @brief  �}�g���b�N�X��2�v�f�̃x�N�g�����|����
	//! @param [in]  rV �ΏۂƂ���x�N�g��
	//! @return ���Z���ʂ�Ԃ�
	//-----------------------------------------------------------------------------------
	inline gt2Vector2 MultiplyD3DXVECTOR2(const gt2Vector2 &rV) const {
		gt2Vector2 out;
		int i;
		for (i = 0; i<2; ++i) {
			out.v[i] = (m[i][0] * rV.x) + (m[i][1] * rV.y);
		}
		return out;
	}

	//-----------------------------------------------------------------------------------
	//! @brief  �Ίp������fA~fC �ŗ^�����C���̐�����0�ł���s���Ԃ��D
	//! @param [in]  rIn gt2Vector2 �\���̂ւ̃|�C���^�ֈʒu�����擾����B
	//! @param [in]  k  k �Ԗڂ̑Ίp��̃��X�g�̗v�f�̒l�D
	//! @return ���Z���ʂ�Ԃ�
	//-----------------------------------------------------------------------------------
	inline void MakeDiagonal(const gt2Vector2 &rIn, int k)
	{
		if (k < -1 || k > 1) return;

		memset(this, 0, sizeof(gt2Matrix2x2));

		if (k < 0) {
			k = abs(k) * 2;
		}
		mm[k] = rIn.x;
		if ((k += 2) > 2)return;
		mm[k] = rIn.y;
	}

	//-----------------------------------------------------------------------------------
	//! @brief  �P�ʍs����쐬����B
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakeIdentity()
	{
		memset(mm, 0, sizeof(gt2Matrix2x2));
		_11 = _22 = 1.0f;
	}
};
#undef MY_XMMATRIX
#undef CAST_XMMATRIX


	
//======================================================================================
//! @brief 3�~3 �̃}�g���b�N�X
//======================================================================================
struct gt2Matrix3x3
{
	union {
		struct {
			float _11, _12, _13;
			float _21, _22, _23;
			float _31, _32, _33;
		};
		float m[3][3];
		float mm[9];
	};

	//! @name �R���X�g���N�^
	//@{
	gt2Matrix3x3()
	{
		this->MakeIdentity();
	}
	gt2Matrix3x3(const float * pF)
	{
		memcpy(this, pF, sizeof(gt2Matrix3x3));
	}
	gt2Matrix3x3(const gt2Matrix3x3& rM)
	{
		*this = rM;
	}
	gt2Matrix3x3(
		float f11, float f12, float f13,
		float f21, float f22, float f23,
		float f31, float f32, float f33
	) : _11(f11), _12(f12), _13(f13),
		_21(f21), _22(f22), _23(f23),
		_31(f31), _32(f32), _33(f33)
	{
	}
	//@}

	//------------------------------------------------------------------------
	//
	//! @name ������Z�q
	//
	//------------------------------------------------------------------------
	//@{
	//inline gt2Matrix3x3& operator= (const Ogre::Matrix3& m) { memcpy(this, &m, sizeof(Ogre::Matrix3)(); return *this; }
	//inline gt2Matrix3x3& operator= (const b2Mat33& m33) { memcpy(this, &m33, sizeof(b2Mat33)); return *this; }

	inline gt2Matrix3x3& operator *= (const gt2Matrix3x3& rM)
	{
		_11 = _11*rM._11 + _12*rM._21 + _13*rM._31;
		_12 = _11*rM._12 + _12*rM._22 + _13*rM._32;
		_13 = _11*rM._13 + _12*rM._23 + _13*rM._33;

		_21 = _21*rM._11 + _22*rM._21 + _23*rM._31;
		_22 = _21*rM._12 + _22*rM._22 + _23*rM._32;
		_23 = _21*rM._13 + _22*rM._23 + _23*rM._33;

		_31 = _31*rM._11 + _32*rM._21 + _33*rM._31;
		_32 = _31*rM._12 + _32*rM._22 + _33*rM._32;
		_33 = _31*rM._13 + _32*rM._23 + _33*rM._33;
		return *this;
	}
	inline gt2Matrix3x3& operator += (const gt2Matrix3x3& rM)
	{
		_11 += rM._11; _12 += rM._12; _13 += rM._13;
		_21 += rM._21; _22 += rM._22; _23 += rM._23;
		_31 += rM._31; _32 += rM._32; _33 += rM._33;
		return *this;
	}
	inline gt2Matrix3x3& operator -= (const gt2Matrix3x3& rM)
	{
		_11 -= rM._11; _12 -= rM._12; _13 -= rM._13;
		_21 -= rM._21; _22 -= rM._22; _23 -= rM._23;
		_31 -= rM._31; _32 -= rM._32; _33 -= rM._33;
		return *this;
	}
	inline gt2Matrix3x3& operator *= (float f)
	{
		_11 *= f; _12 *= f; _13 *= f;
		_21 *= f; _22 *= f; _23 *= f;
		_31 *= f; _32 *= f; _33 *= f;
		return *this;
	}
	inline gt2Matrix3x3& operator /= (float f)
	{
		float fInv = 1.0f / f;
		_11 *= fInv; _12 *= fInv; _13 *= fInv;
		_21 *= fInv; _22 *= fInv; _23 *= fInv;
		_31 *= fInv; _32 *= fInv; _33 *= fInv;
		return *this;
	}
	//@}

	//------------------------------------------------------------------------
	//
	//! @name �P�����Z�q
	//
	//------------------------------------------------------------------------
	//@{
	inline gt2Matrix3x3 operator + () const
	{
		return *this;
	}
	inline gt2Matrix3x3 operator - () const
	{
		return gt2Matrix3x3(-_11, -_12, -_13,
			-_21, -_22, -_23,
			-_31, -_32, -_33);
	}
	//@}

	//------------------------------------------------------------------------
	//
	//! @name 2 �����Z�q
	//
	//------------------------------------------------------------------------
	//@{
	inline gt2Matrix3x3
		operator * (const gt2Matrix3x3& tmp) const
	{
		gt2Matrix3x3 ret;
		ret._11 = _11*tmp._11 + _12*tmp._21 + _13*tmp._31;
		ret._12 = _11*tmp._12 + _12*tmp._22 + _13*tmp._32;
		ret._13 = _11*tmp._13 + _12*tmp._23 + _13*tmp._33;

		ret._21 = _21*tmp._11 + _22*tmp._21 + _23*tmp._31;
		ret._22 = _21*tmp._12 + _22*tmp._22 + _23*tmp._32;
		ret._23 = _21*tmp._13 + _22*tmp._23 + _23*tmp._33;

		ret._31 = _31*tmp._11 + _32*tmp._21 + _33*tmp._31;
		ret._32 = _31*tmp._12 + _32*tmp._22 + _33*tmp._32;
		ret._33 = _31*tmp._13 + _32*tmp._23 + _33*tmp._33;

		return ret;
	}
	inline gt2Matrix3x3
		operator + (const gt2Matrix3x3& tmp) const
	{
		gt2Matrix3x3 ret;
		ret._11 = _11 + tmp._11;
		ret._12 = _12 + tmp._12;
		ret._13 = _13 + tmp._13;

		ret._21 = _21 + tmp._21;
		ret._22 = _22 + tmp._22;
		ret._23 = _23 + tmp._23;

		ret._31 = _31 + tmp._31;
		ret._32 = _32 + tmp._32;
		ret._33 = _33 + tmp._33;
		return ret;
	}
	inline gt2Matrix3x3 operator - (const gt2Matrix3x3& rM) const
	{
		return gt2Matrix3x3(
			_11 - rM._11, _12 - rM._12, _13 - rM._13,
			_21 - rM._21, _22 - rM._22, _23 - rM._23,
			_31 - rM._31, _32 - rM._32, _33 - rM._33);
	}

	inline gt2Matrix3x3
		operator * (const float &tmp) const
	{
		gt2Matrix3x3 ret;
		ret._11 = _11*tmp;
		ret._12 = _12*tmp;
		ret._13 = _13*tmp;

		ret._21 = _21*tmp;
		ret._22 = _22*tmp;
		ret._23 = _23*tmp;

		ret._31 = _31*tmp;
		ret._32 = _32*tmp;
		ret._33 = _33*tmp;
		return ret;
	}
	inline gt2Matrix3x3
		operator / (const float &tmp) const
	{
		gt2Matrix3x3 ret;
		float factor = 1.0f / tmp;

		ret._11 = _11*factor;
		ret._12 = _12*factor;
		ret._13 = _13*factor;

		ret._21 = _21*factor;
		ret._22 = _22*factor;
		ret._23 = _23*factor;

		ret._31 = _31*factor;
		ret._32 = _32*factor;
		ret._33 = _33*factor;
		return ret;
	}
	inline gt2Matrix3x3 operator + (float f) const
	{
		return gt2Matrix3x3(
			_11 + f, _12 + f, _13 + f,
			_21 + f, _22 + f, _23 + f,
			_31 + f, _32 + f, _33 + f);
	}
	inline gt2Matrix3x3 operator - (float f) const
	{
		return gt2Matrix3x3(
			_11 - f, _12 - f, _13 - f,
			_21 - f, _22 - f, _23 - f,
			_31 - f, _32 - f, _33 - f);
	}
	inline gt2Matrix3x3 operator * (float f) const
	{
		return gt2Matrix3x3(
			_11 * f, _12 * f, _13 * f,
			_21 * f, _22 * f, _23 * f,
			_31 * f, _32 * f, _33 * f);
	}
	inline gt2Matrix3x3 operator / (float f) const
	{
		float fInv = 1.0f / f;
		return gt2Matrix3x3(
			_11 * fInv, _12 * fInv, _13 * fInv,
			_21 * fInv, _22 * fInv, _23 * fInv,
			_31 * fInv, _32 * fInv, _33 * fInv);
	}
	inline gt2Matrix3x3 operator / (const gt2Matrix3x3& rM) const
	{
		return gt2Matrix3x3(
			_11 / rM._11, _12 / rM._12, _13 / rM._13,
			_21 / rM._21, _22 / rM._22, _23 / rM._23,
			_31 / rM._31, _32 / rM._32, _33 / rM._33);
	}
	//@}

	//! @name ��r���Z�q
	//@{
	inline bool operator == (const gt2Matrix3x3& rM) const
	{
		return 0 == memcmp(this, &rM, sizeof(gt2Matrix3x3));
	}
	inline bool operator != (const gt2Matrix3x3& rM) const
	{
		return !(*this == rM);
	}
	//@}

	//-----------------------------------------------------------------------------------
	//! @brief �s��̋t�s����v�Z����B
	//! @param [out] pDeterminant  �s��̍s�񎮂��܂� float �l�ւ̃|�C���^�B@n
	//!                           �s�񎮂��s�v�̏ꍇ�́A���̃p�����[�^�� nullptr ��ݒ肷��B
	//! @param [out] pOut          ���Z���ʂł��� gt2Matrix4x4 �\���̂ւ̃|�C���^�B
	//! @return �t�s��̌v�Z�����s�����ꍇ�́Afalse ��Ԃ��B
	//-----------------------------------------------------------------------------------
	inline bool GetInverse(float *pDeterminant, gt2Matrix3x3* pOut) const
	{
		float d;

		d = _11*(_33 * _22 - _32 * _23) -
			_21*(_33 * _12 - _32 * _13) +
			_31*(_23 * _12 - _22 * _13);


		if (d == 0.0f)
			return false;

		d = 1.0f / d;


		pOut->_11 = d *  (_22*_33 - _23*_32);
		pOut->_12 = d * -(_12*_33 - _13*_32);
		pOut->_13 = d * -(_12*_33 - _13*_22);
		pOut->_21 = d * -(_21*_33 - _23*_31);
		pOut->_22 = d *  (_11*_33 - _13*_31);
		pOut->_23 = d * -(_11*_23 - _13*_21);
		pOut->_31 = d *  (_21*_32 - _22*_31);
		pOut->_32 = d * -(_11*_32 - _12*_31);
		pOut->_33 = d *  (_11*_22 - _12*_21);


		if (pDeterminant != nullptr) *pDeterminant = d;

		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief �s��̋t�s����v�Z����B
	//! @param [out] rDeterminant  �s��̍s�񎮂��܂� float �l�B@n
	//!                            �s�񎮂��s�v�̏ꍇ�́A���̃p�����[�^�� nullptr ��ݒ肷��B
	//! @param [out] rOut          ���Z���ʂł��� gt2Matrix4x4 �\���́B
	//! @return �t�s��̌v�Z�����s�����ꍇ�́Afalse ��Ԃ��B
	//-----------------------------------------------------------------------------------
	inline bool GetInverse(float &rDeterminant, gt2Matrix3x3& rOut) const
	{
		return this->GetInverse(&rDeterminant, &rOut);
	}
	//-----------------------------------------------------------------------------------
	//! @brief 4x4�s���3x3�s��ɃN���b�v����
	//! @param [in] pMX  gt2Matrix4x4�|�C���^
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void ClipMCXMATRIX(const gt2Matrix4x4 *pMX) {
		m[0][0] = pMX->_11; m[0][1] = pMX->_12; m[0][2] = pMX->_13;
		m[1][0] = pMX->_21; m[1][1] = pMX->_22; m[1][2] = pMX->_23;
		m[2][0] = pMX->_31; m[2][1] = pMX->_32; m[2][2] = pMX->_33;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 4x4�s���3x3�s��ɃN���b�v����
	//! @param [in] rMX  gt2Matrix4x4
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void ClipMCXMATRIX(const gt2Matrix4x4 &rMX)
	{
		this->ClipMCXMATRIX(&rMX);
	}

	//-----------------------------------------------------------------------------------
	//! @brief �}�g���b�N�X��3�v�f�̃x�N�g�����|����
	//! @param [in] rV  3�v�f�̃x�N�g��
	//! @return ���Z���ʂ�Ԃ�
	//-----------------------------------------------------------------------------------
	inline gt2Vector3 Multiply(const gt2Vector3& rV) const
	{
		gt2Vector3 out;
		out.x = (m[0][0] * rV.x) + (m[0][1] * rV.y) + (m[0][2] * rV.z);
		out.y = (m[1][0] * rV.x) + (m[1][1] * rV.y) + (m[1][2] * rV.z);
		out.z = (m[2][0] * rV.x) + (m[2][1] * rV.y) + (m[2][2] * rV.z);
		return out;
	}

	//-----------------------------------------------------------------------------------
	//! @brief �Ίp������fA~fC �ŗ^�����C���̐�����0�ł���s���Ԃ��D
	//! @param [in] rV  3�v�f�x�N�g��
	//! @param [in] k   �Ԗڂ̑Ίp��̃��X�g�̗v�f�̒l�D
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakeDiagonal(const gt2Vector3& rIn, int k)
	{
		if (k < -2 || k > 2) return;

		memset(this, 0, sizeof(gt2Matrix3x3));

		if (k < 0) {
			k = abs(k) * 4;
		}
		mm[k] = rIn.x;
		if ((k += 4) > 8)return;
		mm[k] = rIn.y;
		if ((k += 4) > 8)return;
		mm[k] = rIn.z;
	}
	//-----------------------------------------------------------------------------------
	//! @brief �N�H�[�^�j�I�������]�s����쐬���܂��B
	//! @param [in] rQ  �N�I�[�^�j�I��
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakeRotationQuaternion(const gt2Quaternion& rQ)
	{
		_11 = 1.0f - (rQ.y * rQ.y + rQ.z * rQ.z) * 2.0f;
		_12 = 2.0f * (rQ.x * rQ.y + rQ.z * rQ.w);
		_13 = 2.0f * (rQ.x * rQ.z - rQ.y * rQ.w);
		_21 = 2.0f * (rQ.x * rQ.y - rQ.z * rQ.w);
		_22 = 1.0f - (rQ.x * rQ.x + rQ.z * rQ.z) * 2.0f;
		_23 = 2.0f * (rQ.y * rQ.z + rQ.x * rQ.w);
		_31 = 2.0f * (rQ.x * rQ.z + rQ.y * rQ.w);
		_32 = 2.0f * (rQ.y * rQ.z - rQ.x * rQ.w);
		_33 = 1.0f - (rQ.x * rQ.x + rQ.y * rQ.y) * 2.0f;
	}
	//-----------------------------------------------------------------------------------
	//! @brief �P�ʍs����쐬����B
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakeIdentity()
	{
		memset(mm, 0, sizeof(gt2Matrix3x3));
		_11 = _22 = _33 = 1.0f;
	}
};
// �G���[�p
const gt2Matrix2x2 g_Matrix2x2_NaN = gt2Matrix2x2(NAN, NAN, NAN, NAN);
const gt2Matrix3x3 g_Matrix3x3_NaN = gt2Matrix3x3(NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN);
const gt2Matrix4x4 g_Matrix4x4_NaN = gt2Matrix4x4(NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN);


