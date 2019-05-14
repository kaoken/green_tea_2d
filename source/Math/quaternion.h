/*
Copyright (c) <''2013''> <''METAL CUBE''>

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
*/
#pragma once

#include <Core/greenTea2D.h>
#include <Math/vector.h>


#define Q_EPSILON 0.0001f	//!< �C�v�V�����l

/*!
* @brief �N�H�[�^�j�I��
* @author kaoken
* @date 2014/01/17 �쐬�J�n
*/
struct gt2Quaternion
{
public:
	union {
		struct {
			float x, y, z, w;	//!< �e�v�f
		};
		float q[4];				//!< �z��ɂ��e�v�f
	};
public:
	/*!
	* @brief �R���X�g���N�^
	*  �e�v�f���O�ŏ����������
	*/
	gt2Quaternion()
	{
		this->Init();
	}
	/*!
	* @brief �R���X�g���N�^
	*   x,y��pf�|�C���^�̒l�ɂ�菉���������
	* @param [in] pf     4�v�f�ȏ��float��񂪂���|�C���^
	*/
	gt2Quaternion(const float * pf)
	{
		memcpy(q, pf, 4 * sizeof(float));
	}
	/*!
	* @brief �R���X�g���N�^
	*  rQ�ŏ����������
	* @param [in] rQ     �N�H�[�^�j�I��
	*/
	gt2Quaternion(const gt2Quaternion& rQ)
	{
		*this = rQ;
	}
	/*!
	* @brief �R���X�g���N�^
	*   x=fx,y=fy,z=fz,w=fw �Ƃ����������ɏ����������
	* @param [in] fx     x�l
	* @param [in] fy     y�l
	* @param [in] fz     y�l
	* @param [in] fw     w�l
	*/
	gt2Quaternion(float fx, float fy, float fz, float fw)
	{
		x = fx; y = fy; z = fz; w = fw;
	}

#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
	gt2Quaternion&   operator= (const DirectX::XMVECTOR& vf) { x = vf.m128_f32[0]; y = vf.m128_f32[1]; z = vf.m128_f32[2]; w = vf.m128_f32[3]; return *this; }

	DirectX::XMVECTOR GetXMVECTOR() const { DirectX::XMVECTOR t; t.m128_f32[0] = x; t.m128_f32[1] = y; t.m128_f32[2] = z; t.m128_f32[3] = w; return t; }
#endif

	//------------------------------------------------------------------------
	// �^�ϊ�
	//------------------------------------------------------------------------
	inline
		operator float* ()
	{
		return q;
	}
	inline
		operator const float* () const
	{
		return q;
	}
	//------------------------------------------------------------------------
	//
	// ������Z�q
	//
	//------------------------------------------------------------------------
	/*!
	* @brief ������Z�q -=
	*   ���g(this)�̃N�H�[�^�j�I�����E�ӂ̃N�H�[�^�j�I�������Z�����l�����g(this)�ɃZ�b�g����
	* @param [in] rQ     �E�ӂ̃N�H�[�^�j�I��
	* @return ���Z���ꂽ�N�H�[�^�j�I����Ԃ�
	*/
	inline gt2Quaternion& operator += (const gt2Quaternion& rQ)
	{
		x += rQ.x;
		y += rQ.y;
		z += rQ.z;
		w += rQ.w;

		return *this;
	}
	/*!
	* @brief ������Z�q -=
	*   ���g(this)�̃N�H�[�^�j�I�����E�ӂ̃N�H�[�^�j�I�������Z�����l�����g(this)�ɃZ�b�g����
	* @param [in] rQ     �E�ӂ̃N�H�[�^�j�I��
	* @return ���Z���ꂽ�N�H�[�^�j�I����Ԃ�
	*/
	inline gt2Quaternion& operator -= (const gt2Quaternion& rQ)
	{
		x -= rQ.x;
		y -= rQ.y;
		z -= rQ.z;
		w -= rQ.w;

		return *this;
	}
	/*!
	* @brief ������Z�q *=
	*   ���g(this)�̃N�H�[�^�j�I�����E�ӂ̂P�̒l����Z�����l�����g(this)�ɃZ�b�g����
	* @param [in] f     �E�ӂ�1�̒l
	* @return ��Z���ꂽ�N�H�[�^�j�I����Ԃ�
	*/
	inline gt2Quaternion& operator *= (const gt2Quaternion& rQ)
	{
		*this = rQ * (*this);
		return *this;
	}
	/*!
	* @brief ������Z�q *=
	*   ���g(this)�̃N�H�[�^�j�I�����E�ӂ̂P�̒l����Z�����l�����g(this)�ɃZ�b�g����
	* @param [in] f     �E�ӂ�1�̒l
	* @return ��Z���ꂽ�N�H�[�^�j�I����Ԃ�
	*/
	inline gt2Quaternion& operator *= (float f)
	{
		x *= f;
		y *= f;
		z *= f;
		w *= f;

		return *this;
	}
	/*!
	* @brief ������Z�q *=
	*   ���g(this)�̃N�H�[�^�j�I�����E�ӂ̂P�̒l�����Z�����l�����g(this)�ɃZ�b�g����
	* @param [in] f     �E�ӂ�1�̒l
	* @return ���Z���ꂽ�N�H�[�^�j�I����Ԃ�
	*/
	inline gt2Quaternion& operator /= (float f)
	{
		x /= f;
		y /= f;
		z /= f;
		w /= f;

		return *this;
	}
	//##################################################################
	//##
	//## �P�����Z�q
	//##
	//##################################################################
	/*!
	* @brief �P�����Z�q +
	*   +��t���������ŁA���ɒl�͕ύX�Ȃ�
	* @return ���̂܂܂̃N�H�[�^�j�I����Ԃ�
	*/
	inline gt2Quaternion operator + () const
	{
		return *this;
	}
	/*!
	* @brief �P�����Z�q -
	*   �e�v�f��-1����Z�����N�H�[�^�j�I���ɂȂ�
	* @return �e�v�f��-1����Z�����N�H�[�^�j�I����Ԃ�
	*/
	inline gt2Quaternion operator - () const
	{
		return gt2Quaternion(-x, -y, -z, -w);
	}
	/*!
	* @brief �P�����Z�q ~
	*   ���������N�H�[�^�j�I���ɂȂ�
	* @return ���������N�H�[�^�j�I����Ԃ�
	*/
	inline gt2Quaternion
		operator ~ () const
	{
		return gt2Quaternion(-x, -y, -z, w);
	}

	//##################################################################
	//##
	//## ��P�����Z�q
	//##
	//##################################################################
	/*!
	* @brief �񍀉��Z�q +
	*   ���g(this)�̃x�N�g����"rQ"�x�N�g�������Z����
	* @param [in] rQ     �N�H�[�^�j�I��
	* @return ���g(this)�̃N�H�[�^�j�I����"rQ"�N�H�[�^�j�I�������Z�����l��Ԃ�
	*/
	inline gt2Quaternion operator + (const gt2Quaternion& rQ) const
	{
		return gt2Quaternion(
			x + rQ.x,
			y + rQ.y,
			z + rQ.z,
			w + rQ.w
		);
	}
	/*!
	* @brief �񍀉��Z�q -
	*   ���g(this)�̃N�H�[�^�j�I����"v"�N�H�[�^�j�I�������Z����
	* @param [in] rV     �N�H�[�^�j�I��
	* @return ���g(this)�̃N�H�[�^�j�I����"v"�N�H�[�^�j�I�������Z�����l��Ԃ�
	*/
	inline gt2Quaternion operator - (const gt2Quaternion& rQ) const
	{
		return gt2Quaternion(
			x - rQ.x,
			y - rQ.y,
			z - rQ.z,
			w - rQ.w
		);
	}
	/*!
	* @brief �񍀉��Z�q *
	*   ���g(this)�̃N�H�[�^�j�I����"rQ"�N�H�[�^�j�I������Z����
	* @param [in] rQ     �N�H�[�^�j�I��
	* @return ���g(this)�̃N�H�[�^�j�I����"v"�N�H�[�^�j�I������Z�����l��Ԃ�
	*/
	inline gt2Quaternion operator * (const gt2Quaternion& rQ) const
	{
		return gt2Quaternion(
			(rQ.w * x) + (rQ.x * w) + (rQ.y * z) - (rQ.z * y),
			(rQ.w * y) + (rQ.y * w) + (rQ.z * x) - (rQ.x * z),
			(rQ.w * z) + (rQ.z * w) + (rQ.x * y) - (rQ.y * x),
			(rQ.w * w) - (rQ.x * x) - (rQ.y * y) - (rQ.z * z)
		);
	}
	/*!
	* @brief �񍀉��Z�q *
	*   ���g(this)�̃N�H�[�^�j�I����"rV"�x�N�g������Z����
	* @param [in] rV     �x�N�g��
	* @return ���g(this)�̃N�H�[�^�j�I����"rV"�x�N�g������Z�����l��Ԃ�
	*/
	inline gt2Quaternion operator * (const gt2Vector3& rV) const
	{
		return	gt2Quaternion(
			-(x*rV.x + y*rV.y + z*rV.z),
			w*rV.x + z*rV.y - y*rV.z,
			w*rV.y + x*rV.z - z*rV.x,
			w*rV.z + y*rV.x - x*rV.y);
	}
	/*!
	* @brief �񍀉��Z�q *
	*   ���g(this)�̃N�H�[�^�j�I���̗v�f����"f"�̒l����Z����
	* @param [in] f     1�̒l
	* @return ���g(this)�̃N�H�[�^�j�I���̗v�f����"f"�̒l����Z�����l��Ԃ�
	*/
	inline gt2Quaternion operator * (float f) const
	{
		gt2Quaternion tmp;
		tmp.w = w * f;
		tmp.x = x * f;
		tmp.y = y * f;
		tmp.z = z * f;
		return tmp;
	}

	friend inline gt2Quaternion operator * (float f, const gt2Quaternion& rQ)
	{
		return rQ * f;
	}

	/*!
	* @brief �񍀉��Z�q *
	*   ���g(this)�̃N�H�[�^�j�I���̗v�f����"f"�̒l�����Z����
	* @param [in] f     1�̒l
	* @return ���g(this)�̃N�H�[�^�j�I���̗v�f����"f"�̒l�����Z�����l��Ԃ�
	*/
	inline gt2Quaternion operator / (float f) const
	{
		gt2Quaternion tmp;
		tmp.w = w / f;
		tmp.x = x / f;
		tmp.y = y / f;
		tmp.z = z / f;
		return tmp;
	}

	friend inline gt2Quaternion operator * (const gt2Vector3& rV, const gt2Quaternion& rQ)
	{
		return	gt2Quaternion(-(rQ.x*rV.x + rQ.y*rV.y + rQ.z*rV.z),
			rQ.w*rV.x + rQ.z*rV.y - rQ.y*rV.z,
			rQ.w*rV.y + rQ.x*rV.z - rQ.z*rV.x,
			rQ.w*rV.z + rQ.y*rV.x - rQ.x*rV.y);
	}
	/*
	friend inline gt2Quaternion
	operator * (const gt2Quaternion& rQ, const gt2Vector3& rV )
	{
	return	gt2Quaternion(	-(rQ.x*rV.x + rQ.y*rV.y + rQ.z*rV.z),
	rQ.w*rV.x + rQ.z*rV.y - rQ.y*rV.z,
	rQ.w*rV.y + rQ.x*rV.z - rQ.z*rV.x,
	rQ.w*rV.z + rQ.y*rV.x - rQ.x*rV.y);
	}*/

	//##################################################################
	//##
	//## ��r���Z�q
	//##
	//##################################################################
	/*!
	* @brief ��r���Z�q ==
	*   ���g(this)�̃N�H�[�^�j�I����"rQ"�N�H�[�^�j�I���̊e�v�f����������r����
	* @param [in] rQ     �N�H�[�^�j�I��
	* @return ���g(this)�̃N�H�[�^�j�I����"rQ"�N�H�[�^�j�I���̊e�v�f����������r���A����Ȃ�true��Ԃ��B
	*/
	inline bool operator == (const gt2Quaternion& rQ) const
	{
		for (int i = 0; i < 4; ++i)
			if (q[i] != rQ.q[i])
				return false;

		return true;
	}
	/*!
	* @brief ��r���Z�q !=
	*   ���g(this)�̃N�H�[�^�j�I����"rQ"�N�H�[�^�j�I���̊e�v�f���Ⴄ����r����
	* @param [in] rQ     �N�H�[�^�j�I��
	* @return ���g(this)�̃N�H�[�^�j�I����"rQ"�N�H�[�^�j�I���̊e�v�f���Ⴄ����r���A�Ⴄ�Ȃ�true��Ԃ��B
	*/
	inline bool operator != (const gt2Quaternion& rQ) const
	{
		return !(*this == rQ);
	}



	//##################################################################
	//##
	//## 
	//##
	//##################################################################
	/*!
	* @brief �N�H�[�^�j�I���̃x�N�g���������\�����Ɋւ����]�p�x�𒊏o����B
	* @return ��]�p�x��Ԃ��B
	*/
	inline float GetAngle() const
	{
		return	(float)(2 * acos(w));
	}
	/*!
	* @brief �N�H�[�^�j�I���̃x�N�g���������\����]�̎��ɉ������P�ʃx�N�g����Ԃ��B
	* @return �P�ʃx�N�g����Ԃ��B
	*/
	inline gt2Vector3 GetAxis() const
	{
		gt2Vector3 vRet;
		float fLSq;

		vRet = gt2Vector3(x, y, z);

		fLSq = vRet.Length();

		if (fLSq <= Q_EPSILON) {
			vRet.Init();
			return vRet;
		}
		else {
			fLSq = 1.0f / fLSq;
			return vRet * fLSq;
		}

	}
	/*!
	* @brief �N�H�[�^�j�I���̃x�N�g���������\����]�̎��ɉ������P�ʃx�N�g����Ԃ��B
	* @return �P�ʃx�N�g����Ԃ��B
	*/
	inline gt2Vector3 GetEuler() const
	{
		gt2Vector3 vRet;

		float sqw = w*w;
		float sqx = x*x;
		float sqy = y*y;
		float sqz = z*z;
		float fUnit = sqx + sqy + sqz + sqw;
		float fTest = x*y + z*w;
		float fE = 0.499f*fUnit;
		if (fTest > fE) {
			vRet.y = 2.0f * atan2f(x, w);
			vRet.z = GT2_HALF_PI;
			vRet.x = 0.0f;
		}
		else if (fTest < -fE) {
			vRet.y = -2.0f * atan2f(x, w);
			vRet.z = -GT2_HALF_PI;
			vRet.x = 0.0f;
		}
		else {
			vRet.y = atan2f(2.0f*y*w - 2.0f*x*z, sqx - sqy - sqz + sqw);
			vRet.z = asinf(2.0f*fTest / fUnit);
			vRet.x = atan2f(2.0f*x*w - 2.0f*y*z, -sqx + sqy - sqz + sqw);
		}


		if (vRet.y < 0)
			vRet.y += GT2_PI2;

		if (vRet.x < 0)
			vRet.x += GT2_PI2;

		if (vRet.z < 0)
			vRet.z += GT2_PI2;

		return vRet;
	}

	/*!
	* @brief �d�S���W�̃N�H�[�^�j�I����Ԃ��B
	* @warning
	*  �d�S���W���v�Z���邽�߁ABaryCentric �֐��͎��Ɏ������ʐ��`��ԏ�������������B
	*  MakeSlerp(MakeSlerp(rQ, rQ, f+g), MakeSlerp(rQ, rQ, f+g), g/(f+g))
	* @param [in] rQ1	1�߂̃N�H�[�^�j�I��
	* @param [in] rQ2	2�߂̃N�H�[�^�j�I��
	* @param [in] rQ3	3�߂̃N�H�[�^�j�I��
	* @param [in] fF	���d�W���B
	* @param [in] fG	���d�W���B
	* @return �Ȃ�
	*/
	inline void MakeBaryCentric(
		const gt2Quaternion& rQ1,
		const gt2Quaternion& rQ2,
		const gt2Quaternion& rQ3,
		float fF,
		float fG
	)
	{
		gt2Quaternion tmp1, tmp2;
		tmp1.MakeSlerp(rQ1, rQ2, fF + fG);
		tmp2.MakeSlerp(rQ1, rQ3, fF + fG);
		this->MakeSlerp(tmp1, tmp2, fG / (fF + fG));
	}
	/*!
	* @brief ����
	*   �N�H�[�^�j�I���̓��ς����߂܂��B
	* @return  ���ς�Ԃ��B
	*/
	inline float Dot() const
	{
		return x*x + y*y + z*z + w*w;
	}
	/*!
	* @brief ����
	*   ���g(this)�̃N�H�[�^�j�I����"rV"�N�H�[�^�j�I������ς���
	* @param [in] rQ     �N�H�[�^�j�I��
	* @return  ���ς�Ԃ��B
	*/
	inline float Dot(const gt2Quaternion& rQ) const
	{
		return (x * rQ.x) + (y * rQ.y) + (z * rQ.z) + (w * rQ.w);
	}
	/*!
	* @brief �w���֐����v�Z����B
	* @param [in] rQ     �N�H�[�^�j�I��
	* @return  �Ȃ�
	*/
	inline void MakeExp(const gt2Quaternion& rQ)
	{
		float fMag, fTheta, fC, fS;
		gt2Vector3 v;

		fMag = expf(rQ.w);
		fTheta = sqrtf(rQ.x*rQ.x + rQ.y*rQ.y + rQ.z*rQ.z);  //really v = |u|sin(phi)

		if (fTheta > 1.0e-20) {
			v.x = rQ.x / fTheta;
			v.y = rQ.y / fTheta;
			v.z = rQ.z / fTheta;
		}
		else {
			v.x = v.y = v.z = 0.0f;
		}
		fC = (float)cos(fTheta);
		fS = (float)sin(fTheta);

		w = fMag*fC;
		x = fMag*fS*v.x;
		y = fMag*fS*v.y;
		z = fMag*fS*v.z;
	}
	/*!
	* @brief �P�ʃN�H�[�^�j�I�����쐬����B
	* @return  �Ȃ�
	*/
	inline void MakeIdentity()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 1.0f;
	}
	/*!
	* @brief �N�H�[�^�j�I�����������āA�Đ��K�����A�Z�b�g����B
	* @param [in] rQ     �N�H�[�^�j�I��
	* @return  �Ȃ�
	*/
	inline void MakeInverse(const gt2Quaternion& rQ)
	{
		rQ.Normalize(this);

		x *= -1;
		y *= -1;
		z *= -1;
		//w = w;
	}
	/*!
	* @brief ����������
	* @return  �Ȃ�
	*/
	inline void Init()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 1.0f;
	}
	/*!
	* @brief �N�H�[�^�j�I�����P�ʃN�H�[�^�j�I���ł��邩�ǂ����𔻒肷��B
	* @return  �N�H�[�^�j�I�����P�ʃN�H�[�^�j�I���̏ꍇ�Atrue ��Ԃ�,����ȊO�̏ꍇ�́Afalse��Ԃ��B
	*/
	inline bool IsIdentity() const
	{
		if (w == 1.0f && x == 0.0f && y == 0.0f && z == 0.0f)
			return true;

		return false;
	}
	/*!
	* @brief �N�H�[�^�j�I���̒�����Ԃ��B
	* @return  �N�H�[�^�j�I���̒�����Ԃ��B
	*/
	inline float Length() const
	{
		return (float)sqrt(x * x + y * y + z * z + w * w);
	}
	/*!
	* @brief �N�H�[�^�j�I���̒����� 2 ���Ԃ�
	* @return  �N�H�[�^�j�I���̒����� 2 ���Ԃ��B
	*/
	inline float LengthSq() const
	{
		float f = this->Length();
		return f*f;
	}
	/*!
	* @brief ���R�ΐ����v�Z���A�Z�b�g����B
	* @return  �Ȃ�
	*/
	inline void MakeLn(const gt2Quaternion& rQ)
	{
		float fQm;
		//float fN;
		float fW;
		//fN = (float)Sqr(rQ.x * rQ.x + rQ.y * rQ.y + rQ.z * rQ.z + rQ.w * rQ.w)
		fQm = (float)sqrt(rQ.x * rQ.x + rQ.y * rQ.y + rQ.z * rQ.z);

		fW = (float)atan2(fQm, rQ.w) / fQm;
		x = fW * rQ.x;
		y = fW * rQ.y;
		z = fW * rQ.z;
		w = 0;	//Log(n)
	}
	/*!
	* @brief �N�H�[�^�j�I���̋������쐬
	* @param [in] rQ     �N�H�[�^�j�I��
	* @return  �Ȃ�
	*/
	inline void MakeConjugate(const gt2Quaternion& rQ)
	{
		x = -rQ.x;
		y = -rQ.y;
		z = -rQ.z;
		w = rQ.w;
	}
	/*!
	* @brief ���g(this)�̃N�H�[�^�j�I���𐳋K������B
	* @return  �Ȃ�
	*/
	inline void Normalize()
	{
		float fL = this->Length();
		if (fL == 0.0f)
			return;

		fL = 1.0f / fL;
		x *= fL;
		y *= fL;
		z *= fL;
		w *= fL;
	}
	/*!
	* @brief �N�H�[�^�j�I���𐳋K�������N�H�[�^�j�I����Ԃ��܂��B
	* @param [out] pOut     �N�H�[�^�j�I���̃|�C���^�B
	* @return  �N�H�[�^�j�I���𐳋K�������x�N�g����Ԃ��B
	*/
	inline gt2Quaternion* Normalize(gt2Quaternion* pOut) const
	{
		float fL = this->Length();
		if (fL == 0.0f) {
			*pOut = gt2Quaternion(0.0f, 0.0f, 0.0f, 0.0f);
			return pOut;
		}
		*pOut = *this;

		fL = 1.0f / fL;
		pOut->x *= fL;
		pOut->y *= fL;
		pOut->z *= fL;
		pOut->w *= fL;
		return pOut;
	}
	/*!
	* @brief ���g�̃N�H�[�^�j�I���𐳋K������B
	* @param [out] rOut     �N�H�[�^�j�I��
	* @return  �Ȃ�
	*/
	inline void Normalize(gt2Quaternion& rOut) const
	{
		this->Normalize(&rOut);
	}
	/*!
	* @brief ���g(this) �� rQP�ɂ���ĉ�]���܂��B
	*   *pOut = (*this) * rQP * ~(*this);
	* @param [out] pOut    ��]�����N�H�[�^�j�I��
	* @param [in]  pQP     ��]�N�H�[�^�j�I��
	* @return  pOut�Ɠ����|�C���^
	*/
	inline gt2Quaternion* Rotate(gt2Quaternion* pOut, const gt2Quaternion& rQP) const
	{
		*pOut = (*this) * rQP * ~(*this);
		return pOut;
	}
	/*!
	* @brief ���g(this) �� rQP�ɂ���ĉ�]���܂��B
	*   �߂�l = (*this) * rQP * ~(*this);
	* @param [in] pQP     �N�H�[�^�j�I��
	* @return  rQP�ɂ���ĉ�]�����N�H�[�^�j�I��
	*/
	inline gt2Quaternion Rotate(const gt2Quaternion& rQP) const
	{
		gt2Quaternion out;
		this->Rotate(&out, rQP);
		return out;
	}
	/*!
	* @brief �x�N�g��rV �� �P�ʎl����(*this)�ɂ���ĉ�]���܂��B
	*   �߂�l = (*this) * rV * ~(*this);
	* @param [out] pOut    �P�ʎl����(*this)�ɂ���ĉ�]�����x�N�g��
	* @param [in]  rV      �R�v�f�x�N�g��
	* @return  pOut�Ɠ����|�C���^
	*/
	inline gt2Vector3* VecRotate(gt2Vector3* pOut, const gt2Vector3& rV) const
	{
		gt2Quaternion qTmp;

		qTmp = (*this) * rV * ~(*this);
		pOut->x = qTmp.x;
		pOut->y = qTmp.y;
		pOut->z = qTmp.z;
		return pOut;
	}
	/*!
	* @brief �x�N�g��rV �� �P�ʎl����(*this)�ɂ���ĉ�]���܂��B
	*   �߂�l = (*this) * rV * ~(*this);
	* @param [in]  rV      �R�v�f�x�N�g��
	* @return  �ʎl����(*this)�ɂ���ĉ�]�����x�N�g��
	*/
	inline gt2Vector3 VecRotate(const gt2Vector3& rV) const
	{
		gt2Vector3 out;
		this->VecRotate(&out, rV);
		return out;
	}
	/*!
	* @brief ���[�E�s�b�`�E���[�����w�肵�ăN�H�[�^�j�I�����쐬����B
	* @param [in]  fYaw	  y ���𒆐S�Ƃ��郈�[ (���W�A���P��)�B
	* @param [in]  pitch x ���𒆐S�Ƃ���s�b�` (���W�A���P��)�B
	* @param [in]  fRoll  z ���𒆐S�Ƃ��郍�[�� (���W�A���P��)�B
	* @return  �Ȃ�
	*/
	inline void MakeRotationYawPitchRoll(float fYaw, float pitch, float fRoll)
	{
		float fCosY, fSinY, fCosR;
		float fSinR, fCosP, fSinP;

		fCosY = cosf(fYaw * 0.5f);
		fSinY = sinf(fYaw * 0.5f);
		fCosP = cosf(pitch * 0.5f);
		fSinP = sinf(pitch * 0.5f);
		fCosR = cosf(fRoll * 0.5f);
		fSinR = sinf(fRoll * 0.5f);

		x = fCosR * fSinP * fCosY + fSinR * fCosP * fSinY;
		y = fCosR * fCosP * fSinY - fSinR * fSinP * fCosY;
		z = fSinR * fCosP * fCosY - fCosR * fSinP * fSinY;
		w = fCosR * fCosP * fCosY + fSinR * fSinP * fSinY;
	}
	/*!
	* @brief ���ʐ��`��Ԃ��g���āA2 �̃N�H�[�^�j�I���Ԃ��Ԃ���B
	* @param [in]  rQ1	 1�߂̃N�I�[�^�j�I��
	* @param [in]  rQ2	 2�߂̃N�I�[�^�j�I��
	* @param [in]  totalTime	 ��Ԃ���N�H�[�^�j�I���Ԃ̊Ԋu�������p�����[�^�B
	* @return  �⊮�����N�H�[�^�j�I����Ԃ�
	*/
	inline static gt2Quaternion Slerp(const gt2Quaternion& rQ1, const gt2Quaternion& rQ2, float t)
	{
		// Slerp(t; p, q) = { sin( (1-t)��)p + sin(t��)q } / sin(��)
		gt2Quaternion qTmp2;
		float cosHalfTheta, halfTheta, sinHalfTheta, ratioA, ratioB, IsinT;

		if (t <= 0.0f)
			return rQ1;

		if (t >= 1.0f)
			return rQ2;

		// ���ς�����
		cosHalfTheta = rQ1.Dot(rQ2);
		if (fabs(cosHalfTheta) >= 1.0f)
			return rQ1;

		qTmp2 = rQ2;

		// �ꎞ�ϐ��쐬.
		halfTheta = (float)acos(cosHalfTheta);
		sinHalfTheta = (float)sqrt(1.0f - cosHalfTheta*cosHalfTheta);

		if (cosHalfTheta < 0.0f) {
			qTmp2 = -qTmp2;
			cosHalfTheta *= -1.0f;
		}

		// theta = 180�x�̏ꍇ�A���̌�A���ʂ͊��S�ɂ͒�`����Ȃ�
		// rQ1�܂���rQ2�ɐ����ȔC�ӂ̎��̂܂��ŉ�]���邱�Ƃ��ł���
		if (fabs(sinHalfTheta) < Q_EPSILON) {//�C�v�V�����l�̐ݒ�ɂ��W��
			ratioA = ratioB = 0.5f;
		}
		else if (cosHalfTheta > 0.99999) { //�C�v�V�����l�̐ݒ�ɂ��W��
			ratioA = 1.0f - t;
			ratioB = t;
		}
		else {
			IsinT = 1.0f / sinHalfTheta;
			ratioA = (float)sin((1.0f - t) * halfTheta) * IsinT;
			ratioB = (float)sin(t * halfTheta) * IsinT;
		}
		// �N�H�[�^�j�I���̌v�Z
		return gt2Quaternion(
			(rQ1.x * ratioA + qTmp2.x * ratioB),
			(rQ1.y * ratioA + qTmp2.y * ratioB),
			(rQ1.z * ratioA + qTmp2.z * ratioB),
			(rQ1.w * ratioA + qTmp2.w * ratioB)
		);
	}
	/*!
	* @brief ���ʐ��`��Ԃ��g���āA2 �̃N�H�[�^�j�I���Ԃ��Ԃ���B
	* @param [in]  rQ1	 1�߂̃N�I�[�^�j�I��
	* @param [in]  rQ2	 2�߂̃N�I�[�^�j�I��
	* @param [in]  t	 ��Ԃ���N�H�[�^�j�I���Ԃ̊Ԋu�������p�����[�^�B
	* @return  �Ȃ�
	*/
	inline void MakeSlerp(const gt2Quaternion& rQ1, const gt2Quaternion& rQ2, float t)
	{
		*this = gt2Quaternion::Slerp(rQ1, rQ2, t);
	}
	/*!
	* @brief ���ʐ��`��Ԃ��g���āA�N�H�[�^�j�I���Ԃ��Ԃ���B
	* @param [in]  rQ  �N�H�[�^�j�I��q
	* @param [in]  rA  �N�H�[�^�j�I��A
	* @param [in]  rB  �N�H�[�^�j�I��B
	* @param [in]  rC  �N�H�[�^�j�I��C
	* @param [in]  t   ��Ԃ���N�H�[�^�j�I���Ԃ̊Ԋu�������p�����[�^�B
	* @return  �⊮�����N�H�[�^�j�I����Ԃ�
	*/
	inline static gt2Quaternion Squad(
		const gt2Quaternion& rQ,
		const gt2Quaternion& rA,
		const gt2Quaternion& rB,
		const gt2Quaternion& rC,
		float totalTime
	)
	{
		gt2Quaternion tmp1;
		gt2Quaternion tmp2;
		gt2Quaternion out;

		tmp1.MakeSlerp(rQ, rC, totalTime);
		tmp2.MakeSlerp(rA, rB, totalTime);
		out.MakeSlerp(tmp1, tmp2, 2.0f * totalTime * (1.0f - totalTime));
		return out;
	}
	/*!
	* @brief ���ʐ��`��Ԃ��g���āA�N�H�[�^�j�I���Ԃ��Ԃ���B
	* @param [in]  rQ  �N�H�[�^�j�I��q
	* @param [in]  rA  �N�H�[�^�j�I��A
	* @param [in]  rB  �N�H�[�^�j�I��B
	* @param [in]  rC  �N�H�[�^�j�I��C
	* @param [in]  t   ��Ԃ���N�H�[�^�j�I���Ԃ̊Ԋu�������p�����[�^�B
	* @return  �Ȃ�
	*/
	inline void MakeSquad(
		const gt2Quaternion& rQ,
		const gt2Quaternion& rA,
		const gt2Quaternion& rB,
		const gt2Quaternion& rC,
		float t
	)
	{
		*this = gt2Quaternion::Squad(rQ, rA, rB, rC, t);
	}
	/*!
	* @brief �C�ӂ̎�����]���Ƃ��ăN�H�[�^�j�I������]�����܂��B
	* @param [in]  rV     �N�H�[�^�j�I���̉�]�����w�肷��Agt2Vector3 �\���̂ւ̃|�C���^�B
	* @param [in]  fAngle ��]�̊p�x (���W�A���P��)�B
	* @return  �Ȃ�
	*/
	inline void MakeRotationAxis(const gt2Vector3& rV, float fAngle)
	{
		float fHalfAngle = 0.5f * fAngle;
		float fSin = (float)sin(fHalfAngle);
		w = (float)cos(fHalfAngle);
		x = fSin * rV.x;
		y = fSin * rV.y;
		z = fSin * rV.z;
	}
	/*!
	* @brief �N�H�[�^�j�I���Ԃ̐��`��Ԃ����s����B
	* @param [in]  rQ1   �� 1 �Ԗڂ̃N�H�[�^�j�I��
	* @param [in]  rQ2   �� 2 �Ԗڂ̃N�H�[�^�j�I��
	* @param [in]  t     �x�N�g���Ԃ���`��Ԃ���p�����[�^�B
	* @return  ���`��Ԃ��ꂽ�N�H�[�^�j�I����Ԃ��B
	*/
	inline static gt2Quaternion Lerp(const gt2Quaternion& rQ1, const gt2Quaternion& rQ2, float t)
	{
		return (rQ1 + t * (rQ2 - rQ1));
	}
	/*!
	* @brief �N�H�[�^�j�I���Ԃ̐��`��Ԃ����s����B
	*   �� 1 �Ԗڂ̃N�H�[�^�j�I�����A���g(this)�ł��B
	* @param [in]  rQ2   �� 2 �Ԗڂ̃N�H�[�^�j�I��
	* @param [in]  t     �x�N�g���Ԃ���`��Ԃ���p�����[�^�B
	* @return  ���`��Ԃ��ꂽ�N�H�[�^�j�I����Ԃ��B
	*/
	inline gt2Quaternion Lerp(const gt2Quaternion& rQ2, float t) const
	{
		return gt2Quaternion::Lerp(*this, rQ2, t);
	}
	/*!
	* @brief 2 �� Quaternion ��A�����܂��B���ʂ́A�ŏ��̉�]�Ƃ���ɑ��� 2 �Ԗڂ̉�]��\���܂��B
	* @param [in]  rQ1   �V���[�Y���̍ŏ��� Quaternion ��]�B
	* @param [in]  rQ2   �V���[�Y���� 2 �Ԗڂ� Quaternion ��]�B
	* @return  ��]�����N�H�[�^�j�I����Ԃ��B
	*/
	inline static gt2Quaternion Concatenate(const gt2Quaternion& rQ1, const gt2Quaternion& rQ2)
	{
		return gt2Quaternion(
			(rQ1.w * rQ2.x) + (rQ1.x * rQ2.w) + (rQ1.y * rQ2.z) - (rQ1.z * rQ2.y),
			(rQ1.w * rQ2.y) + (rQ1.y * rQ2.w) + (rQ1.z * rQ2.x) - (rQ1.x * rQ2.z),
			(rQ1.w * rQ2.z) + (rQ1.z * rQ2.w) + (rQ1.x * rQ2.y) - (rQ1.y * rQ2.x),
			(rQ1.w * rQ2.w) - (rQ1.x * rQ2.x) - (rQ1.y * rQ2.y) - (rQ1.z * rQ2.z)
		);
	}


};

// �G���[�p
const gt2Quaternion g_QuaternionF_NaN = gt2Quaternion(NAN, NAN, NAN, NAN);

