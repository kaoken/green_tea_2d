/*!
Copyright 2019 kaoken

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

@file vector.h
@brief �v�f��2,3,4�̃x�N�g���\����
*/
#pragma once


#include <Core/greenTea2D.h>
#include <Math/mathMacro.h>
#include <Box2D/Box2D.h>


#  undef min
#  undef max

struct gt2Vector2;
struct gt2Vector3;
struct gt2Vector4;

/*!
* @brief 2�v�f(x,y) �x�N�g��
*/
struct gt2Vector2
{
public:
	union
	{
		struct {
			float x; //!< �v�f x
			float y; //!< �v�f y
		};
		float v[2];	//!< v[0] = x, v[1] = y 
	};
public:
#ifdef B2_MATH_H
	gt2Vector2& operator= (const b2Vec2& Float2) { x = Float2.x; y = Float2.y; return *this; }
#endif

	/*!
	* @brief �R���X�g���N�^
	*  x,y���O�ŏ����������
	*/
	gt2Vector2() { this->Init(); };
#ifdef B2_MATH_H
	/*!
	* @brief �R���X�g���N�^
	*  rV�ŏ����������
	* @param [in] rV     b2Vec2�x�N�g��
	*/
	gt2Vector2(const b2Vec2 &rV) { *this = rV; };
#endif
	/*!
	* @brief �R���X�g���N�^
	*  rV�ŏ����������
	* @param [in] rV     �x�N�g��
	*/
	gt2Vector2(const gt2Vector2 &rV) { *this = rV; };
	/*!
	* @brief �R���X�g���N�^
	*   x=fx,y=fy �Ƃ����������ɏ����������
	* @param [in] fx     x�l
	* @param [in] fy     y�l
	*/
	gt2Vector2(float fx, float fy) { x = fx; y = fy; }
	/*!
	* @brief x,y�̒l���O�ŏ����������
	* @return �Ȃ�
	*/
	inline void Init() { x = y = 0; }
	/*!
	* @brief x,y�̒l��float�^�̍ő�l��FLT_MAX�ŏ����������
	* @return �Ȃ�
	*/
	inline void InitMin() { x = y = FLT_MAX; }
	/*!
	* @brief x,y�̒l��float�^�̍ŏ��l��FLT_MAX�ŏ����������
	* @return �Ȃ�
	*/
	inline void InitMax() { x = y = -FLT_MAX; }
	/**
	* @param [in] fx     x�l
	* @param [in] fy     y�l
	*/
	inline void Set(float fx, float fy) { x = fx; y = fy; }
	/*!
	* @brief �p�x(0�`360)���烉�W�A���l�ɕϊ�����x,y�ɑ������
	* @param [in] fx     �p�x(0�`360)
	* @param [in] fy     �p�x(0�`360)
	* @return �Ȃ�
	*/
	inline void MakeRadianToDegrees(float fx, float fy)
	{
		x = GT2_INV_RADIAN * fx;
		y = GT2_INV_RADIAN * fy;
	}

	//##################################################################
	//##
	//## ������Z�q
	//##
	//##################################################################
	/*!
	* @brief ������Z�q =
	*   �ʏ�̑��
	* @param [in] v     �E�ӂ̃x�N�g��gt2Vector2
	* @return ���Z���ꂽ�x�N�g���l��Ԃ�
	*/
	inline gt2Vector2& operator = (const gt2Vector2& v)
	{
		x = v.x;
		y = v.y;
		return *this;
	}

	/*!
	* @brief ������Z�q +=
	*   ���g(this)�̃x�N�g���l���E�ӂ̃x�N�g���l�����Z�����l�����g(this)�ɃZ�b�g����
	* @param [in] v     �E�ӂ̃x�N�g��gt2Vector2
	* @return ���Z���ꂽ�x�N�g���l��Ԃ�
	*/
	inline gt2Vector2& operator += (const gt2Vector2& v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}
	/*!
	* @brief ������Z�q -=
	*   ���g(this)�̃x�N�g���l���E�ӂ̃x�N�g���l�����Z�����l�����g(this)�ɃZ�b�g����
	* @param [in] v     �E�ӂ̃x�N�g��gt2Vector2
	* @return ���Z���ꂽ�x�N�g���l��Ԃ�
	*/
	inline gt2Vector2& operator -= (const gt2Vector2& v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}
	/*!
	* @brief ������Z�q *=
	*   ���g(this)�̃x�N�g���l���E�ӂ̂P�̒l����Z�����l�����g(this)�ɃZ�b�g����
	* @param [in] v     �E�ӂ�1�̒l
	* @return ��Z���ꂽ�x�N�g���l��Ԃ�
	*/
	inline gt2Vector2& operator *= (float f)
	{
		x *= f;
		y *= f;
		return *this;
	}
	/*!
	* @brief ������Z�q *=
	*   ���g(this)�̃x�N�g���l���E�ӂ̂P�̒l�����Z�����l�����g(this)�ɃZ�b�g����
	* @param [in] v     �E�ӂ�1�̒l
	* @return ���Z���ꂽ�x�N�g���l��Ԃ�
	*/
	inline gt2Vector2& operator /= (float f)
	{
		float fInv = 1.0f / f;
		x *= fInv;
		y *= fInv;
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
	* @return ���̂܂܂̃x�N�g���l��Ԃ�
	*/
	inline gt2Vector2 operator + () const
	{
		return *this;
	}
	/*!
	* @brief �P�����Z�q -
	*   �e�v�f��-1����Z�����x�N�g���l�ɂȂ�
	* @return �e�v�f��-1����Z�����x�N�g���l��Ԃ�
	*/
	inline gt2Vector2 operator - () const
	{
		return gt2Vector2(-x, -y);
	}


	//##################################################################
	//##
	//## �񍀉��Z�q
	//##
	//##################################################################
	/*!
	* @brief �񍀉��Z�q +
	*   ���g(this)�̃x�N�g����"rV"�x�N�g�������Z����
	* @param [in] v     gt2Vector2
	* @return ���g(this)�̃x�N�g����"rV"�x�N�g���l�����Z�����l��Ԃ�
	*/
	inline gt2Vector2 operator + (const gt2Vector2& v) const
	{
		return gt2Vector2(x + v.x, y + v.y);
	}
	/*!
	* @brief �񍀉��Z�q -
	*   ���g(this)�̃x�N�g����"rV"�x�N�g�������Z����
	* @param [in] v     gt2Vector2
	* @return ���g(this)�̃x�N�g����"rV"�x�N�g���l�����Z�����l��Ԃ�
	*/
	inline gt2Vector2 operator - (const gt2Vector2& v) const
	{
		return gt2Vector2(x - v.x, y - v.y);
	}
	/*!
	* @brief �񍀉��Z�q *
	*   ���g(this)�̃x�N�g����"rV"�x�N�g���̗v�f���Ə�Z����
	* @param [in] v     gt2Vector2
	* @return ���g(this)�̃x�N�g����"rV"�x�N�g���̗v�f���Ə�Z�����l��Ԃ�
	*/
	inline gt2Vector2 operator * (const gt2Vector2& v) const
	{
		return gt2Vector2(x * v.x, y * v.y);
	}
	/*!
	* @brief �񍀉��Z�q /
	*   ���g(this)�̃x�N�g����"rV"�x�N�g���̗v�f���Ə��Z����
	* @param [in] v     gt2Vector2
	* @return ���g(this)�̃x�N�g����"rV"�x�N�g���̗v�f���Ə��Z�����l��Ԃ�
	*/
	inline gt2Vector2 operator / (const gt2Vector2& v) const
	{
		return gt2Vector2(x / v.x, y / v.y);
	}
	/*!
	* @brief �񍀉��Z�q +
	*   ���g(this)�̃x�N�g���̗v�f����"f"�̒l�����Z����
	* @param [in] f     1�̒l
	* @return ���g(this)�̃x�N�g���̗v�f����"f"�̒l�����Z�����l��Ԃ�
	*/
	inline gt2Vector2 operator + (float f) const
	{
		return gt2Vector2(x + f, y + f);
	}
	/*!
	* @brief �񍀉��Z�q -
	*   ���g(this)�̃x�N�g���̗v�f����"f"�̒l�����Z����
	* @param [in] f     1�̒l
	* @return ���g(this)�̃x�N�g���̗v�f����"f"�̒l�����Z�����l��Ԃ�
	*/
	inline gt2Vector2 operator - (float f) const
	{
		return gt2Vector2(x - f, y - f);
	}
	/*!
	* @brief �񍀉��Z�q *
	*   ���g(this)�̃x�N�g���̗v�f����"f"�̒l����Z����
	* @param [in] f     1�̒l
	* @return ���g(this)�̃x�N�g���̗v�f����"f"�̒l����Z�����l��Ԃ�
	*/
	inline gt2Vector2 operator * (float f) const
	{
		return gt2Vector2(x * f, y * f);
	}
	/*!
	* @brief �񍀉��Z�q /
	*   ���g(this)�̃x�N�g���̗v�f����"f"�̒l�����Z����
	* @param [in] f     1�̒l
	* @return ���g(this)�̃x�N�g���̗v�f����"f"�̒l�����Z�����l��Ԃ�
	*/
	inline gt2Vector2 operator / (float f) const
	{
		float fInv = 1.0f / f;
		return gt2Vector2(x * fInv, y * fInv);
	}

	friend inline gt2Vector2 operator * (float f, const gt2Vector2& v)
	{
		return gt2Vector2(f * v.x, f * v.y);
	}


	//##################################################################
	//##
	//## ��r���Z�q
	//##
	//##################################################################
	/*!
	* @brief ��r���Z�q ==
	*   ���g(this)�̃x�N�g����"rV"�x�N�g���̊e�v�f����������r����
	* @param [in] v     gt2Vector2
	* @return ���g(this)�̃x�N�g����"rV"�x�N�g���̊e�v�f���r���A����Ȃ�true��Ԃ��B
	*/
	inline bool operator == (const gt2Vector2& v) const
	{
		return x == v.x && y == v.y;
	}
	/*!
	* @brief ��r���Z�q !=
	*   ���g(this)�̃x�N�g����"rV"�x�N�g���̊e�v�f���Ⴄ����r����
	* @param [in] v     gt2Vector2
	* @return ���g(this)�̃x�N�g����"rV"�x�N�g���̊e�v�f���r���A�Ⴄ�ꍇtrue��Ԃ��B
	*/
	inline bool operator != (const gt2Vector2& v) const
	{
		return x != v.x || y != v.y;
	}



	//##################################################################
	//##
	//## 
	//##
	//##################################################################

	/*!
	* @brief �x�N�g���̒�����Ԃ��B
	* @return �x�N�g���̒�����Ԃ��B
	*/
	inline float Length() const
	{
		return sqrtf(x * x + y * y);
	}
	/*!
	* @brief �x�N�g���̒����� 2 ���Ԃ��B
	* @return �x�N�g���̒����� 2 ���Ԃ��B
	*/
	inline float LengthSq() const
	{
		return x * x + y * y;
	}
	/*!
	* @brief ����
	*   �x�N�g���̓��ς����߂܂��B
	* @return  ���ς�Ԃ��B
	*/
	inline float Dot() const
	{
		return x * x + y * y;
	}
	/*!
	* @brief ����
	*   ���g(this)�̃x�N�g����"rV2"�x�N�g������ς���
	* @param [in] rV     �Ώۃx�N�g��
	* @return  ���ς�Ԃ��B
	*/
	inline float Dot(const gt2Vector2& rV) const
	{
		return x * rV.x + y * rV.y;
	}
	/*!
	* @brief �O��
	*   �x�N�g���̊O�ς��v�Z���Az ������Ԃ��B
	* @param [in] rV     �Ώۃx�N�g��
	* @return  ���ς�Ԃ��B
	*/
	inline float CCW(const gt2Vector2& rV) const
	{
		return x * rV.y - y * rV.x;
	}
	/*!
	* @brief �x�N�g���̉��Z
	*   ���g(this)�̃x�N�g����"rV"�x�N�g�������Z����B
	* @param [in] rV     ���� gt2Vector2 �\����
	* @return  ���Z���ꂽ�x�N�g����Ԃ��B
	*/
	inline gt2Vector2 Add(const gt2Vector2& rV) const
	{
		gt2Vector2 out;
		out.x = x + rV.x;
		out.y = y + rV.y;
		return out;
	}
	/*!
	* @brief �x�N�g���̌��Z
	*   ���g(this)�̃x�N�g����"rV"�x�N�g�������Z����B
	* @param [in] rV     ���� gt2Vector2 �\����
	* @return  ���Z���ꂽ�x�N�g����Ԃ��B
	*/
	inline gt2Vector2 Subtract(const gt2Vector2& rV) const
	{
		gt2Vector2 out;
		out.x = x - rV.x;
		out.y = y - rV.y;
		return out;
	}
	/*!
	* @brief 2�̃x�N�g���̗v�f���r���ŏ��l�̗v�f�̃x�N�g����Ԃ�
	* @param [in] rV     ���� gt2Vector2 �\����
	* @return  �ŏ��l�̗v�f�̃x�N�g����Ԃ�
	*/
	inline gt2Vector2 Minimize(const gt2Vector2& rV) const
	{
		gt2Vector2 out;
		out.x = x < rV.x ? x : rV.x;
		out.y = y < rV.y ? y : rV.y;
		return out;
	}
	/*!
	* @brief 2�̃x�N�g���̗v�f���r���ő�l�̗v�f�̃x�N�g�����擾����
	* @param [in] rV     ���� gt2Vector2 �\����
	* @return  �ő�l�̗v�f�̃x�N�g����Ԃ�
	*/
	inline gt2Vector2 Maximize(const gt2Vector2& rV) const
	{
		gt2Vector2 out;
		out.x = x > rV.x ? x : rV.x;
		out.y = y > rV.y ? y : rV.y;
		return out;
	}
	/*!
	* @brief ���g(this)�̃x�N�g����90����]���������W�A���l��n��
	* @return  �g�̃x�N�g����90����]���������W�A���l��Ԃ�
	*/
	inline gt2Vector2 GetRot90() const
	{
		gt2Vector2 out;
		out.x = -y;
		out.y = x;
		return out;
	}
	/*!
	* @brief ���g(this)�̃x�N�g����90����]�������l�𐳋K�������l��n���B
	* @param [out] pOut     ���Z���ʂł��� gt2Vector2 �\���̂ւ̃|�C���^�B
	* @return  ���g(this)�̃x�N�g����90����]�������l�𐳋K�������l��Ԃ�
	*/
	inline gt2Vector2 GetNormalizeRot90() const
	{
		gt2Vector2 out = this->GetRot90();
		out.Normalize();
		return out;
	}
	/*!
	* @brief �x�N�g���𐳋K�������x�N�g����Ԃ��܂��B
	* @param [out] pOut     ���Z���ʂł��� gt2Vector2 �\���̂ւ̃|�C���^�B
	* @return  �x�N�g���𐳋K�������x�N�g����Ԃ��B
	*/
	inline gt2Vector2* Normalize(gt2Vector2* pOut) const
	{
		float fL = this->Length();
		if (fL == 0.0f)
			return nullptr;

		*pOut = *this;

		fL = 1.0f / fL;
		pOut->x *= fL;
		pOut->y *= fL;

		return pOut;
	}
	/*!
	* @brief �x�N�g���𐳋K�������x�N�g����Ԃ��B
	* @param [out] rOut     ���Z���ʂł��� gt2Vector2�B
	* @return  �Ȃ�
	*/
	inline void Normalize(gt2Vector2 &rOut) const
	{
		this->Normalize(&rOut);
	}

	/*!
	* @brief ���g(this)�̃x�N�g���𐳋K������B
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
	}

	/*!
	* @brief �x�N�g���̗v�f���A�w�肳�ꂽ�ő�l�ƍŏ��l�͈̔͂ɃN�����v���܂��B
	* @param [in] rMin     �ŏ��͈̓x�N�g��
	* @param [in] rMax     �ő�͈̓x�N�g��
	* @return  �Ȃ�
	*/
	void Clamp(const gt2Vector2& rMin, const gt2Vector2& rMax)
	{
		x = std::min(std::max(x, rMin.x), rMax.x);
		y = std::min(std::max(y, rMin.y), rMax.y);
	}
	/*!
	* @brief �x�N�g�����X�P�[�����O����B
	* @param [in]  s      �X�P�[�����O�l�B
	* @return  �x�N�g�����X�P�[�����O�������̂�Ԃ��B
	*/
	inline gt2Vector2 Scale(float s) const
	{
		gt2Vector2 out;
		out.x = x * s;
		out.y = y * s;
		return out;
	}
	/*!
	* @brief �x�N�g���Ԃ̐��`��Ԃ����s����B
	* @param [in]  rV1   �� 1 �Ԗڂ̃x�N�g��
	* @param [in]  rV2   �� 2 �Ԗڂ̃x�N�g��
	* @param [in]  t     �x�N�g���Ԃ���`��Ԃ���p�����[�^�B
	* @return  ���`��Ԃ��ꂽ�x�N�g����Ԃ��B
	*/
	inline static gt2Vector2 Lerp(const gt2Vector2& rV1, const gt2Vector2& rV2, float t)
	{
		gt2Vector2 out;
		out.x = rV1.x + t * (rV2.x - rV1.x);
		out.y = rV1.y + t * (rV2.y - rV1.y);
		return out;
	}
	/*!
	* @brief �x�N�g���Ԃ̐��`��Ԃ����s����B
	*   �� 1 �Ԗڂ̃x�N�g�����A���g(this)�ł��B
	* @param [in]  rV2   �� 2 �Ԗڂ̃x�N�g��
	* @param [in]  t     �x�N�g���Ԃ���`��Ԃ���p�����[�^�B
	* @return  ���`��Ԃ��ꂽ�x�N�g����Ԃ��B
	*/
	inline gt2Vector2 Lerp(const gt2Vector2& rV2, float t) const
	{
		return gt2Vector2::Lerp(*this, rV2, t);
	}

	/*!
	* @brief 0 �� t �� 1 �̊ԂŃG���~�[�g��Ԃɂ�銊�炩�ȕ�Ԃ��s���܂��B
	* @param [in]  rV1  1 �Ԗڂ̃x�N�g���B
	* @param [in]  rV2  2 �Ԗڂ̃x�N�g���B
	* @param [in]  t   �x�N�g���Ԃ���`��Ԃ���p�����[�^�B�͈�[0�`1.0]
	* @return  ��Ԃ��ꂽ�x�N�g����Ԃ��B
	*/
	inline static gt2Vector2 SmoothStep(const gt2Vector2& rV1, const gt2Vector2& rV2, float t)
	{
		t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
		t = t*t*(3.f - 2.f*t);
		return gt2Vector2::Lerp(rV1, rV2, t);
	}
	/*!
	* @brief 0 �� t �� 1 �̊ԂŃG���~�[�g��Ԃɂ�銊�炩�ȕ�Ԃ��s���܂��B
	*   �� 1 �Ԗڂ̃x�N�g�����A���g(this)�ł��B
	* @param [in]  rV  2 �Ԗڂ̃x�N�g���B
	* @param [in]  t   �x�N�g���Ԃ���`��Ԃ���p�����[�^�B�͈�[0�`1.0]
	* @return  ��Ԃ��ꂽ�x�N�g����Ԃ��B
	*/
	inline gt2Vector2 SmoothStep(const gt2Vector2& rV2, float t) const
	{
		return gt2Vector2::SmoothStep(*this, rV2, t);
	}
	/*!
	* @brief �w�肳�ꂽ�ʒu�x�N�g�����g�p���āA�d�S���W�̃|�C���g��Ԃ��܂��B
	* @param [in]  rV1  �� 1 �̈ʒu
	* @param [in]  rV2  �� 2 �̈ʒu
	* @param [in]  rV3  �� 3 �̈ʒu
	* @param [in]  f    ���d�W���B
	* @param [in]  g    ���d�W���B
	* @return  �d�S���W��Ԃ��܂��B
	*/
	inline static gt2Vector2 Barycentric(const gt2Vector2& rV1, const gt2Vector2& rV2, const gt2Vector2& rV3, float f, float g)
	{
		return rV1 + f * (rV2 - rV1) + g * (rV3 - rV1);
	}
	/*!
	* @brief �w�肳�ꂽ�ʒu�x�N�g�����g�p���āA�d�S���W�̃|�C���g��Ԃ��܂��B
	*   �� 1 �̈ʒu���A���g(this)�ł��B
	* @param [in]  rV2  �� 2 �̈ʒu
	* @param [in]  rV3  �� 3 �̈ʒu
	* @param [in]  f    ���d�W���B
	* @param [in]  g    ���d�W���B
	* @return  �d�S���W��Ԃ��܂��B
	*/
	inline gt2Vector2 Barycentric(const gt2Vector2& rV2, const gt2Vector2& rV3, float f, float g) const
	{
		return gt2Vector2::Barycentric(*this, rV2, rV3, f, g);
	}
	/*!
	* @brief �w�肳�ꂽ�ʒu�x�N�g�����g�p���āACatmull-Rom ��Ԃ��s���܂��B
	* @param [in]  rV1  �� 1 �̈ʒu
	* @param [in]  rV2  �� 2 �̈ʒu
	* @param [in]  rV3  �� 3 �̈ʒu
	* @param [in]  rV4  �� 3 �̈ʒu
	* @param [in]  t    ��Ԑ���W��
	* @return  Catmull-Rom ��Ԃ̌��ʂ�Ԃ��܂��B
	*/
	inline static gt2Vector2 CatmullRom(const gt2Vector2& rV1, const gt2Vector2& rV2, const gt2Vector2& rV3, const gt2Vector2& rV4, float t)
	{
		float t2 = t * t;
		float t3 = t * t2;
		return ((-t3 + 2 * t2 - t) * rV1 +
			(3 * t3 - 5 * t2 + 2) * rV2 +
			(-3 * t3 + 4 * t2 + t) * rV3 +
			(t3 - t2) * rV4) * 0.5f;
	}
	/*!
	* @brief �w�肳�ꂽ�ʒu�x�N�g�����g�p���āACatmull-Rom ��Ԃ��s���܂��B
	*   �� 1 �̈ʒu���A���g(this)�ł��B
	* @param [in]  rV2  �� 2 �̈ʒu
	* @param [in]  rV3  �� 3 �̈ʒu
	* @param [in]  rV4  �� 3 �̈ʒu
	* @param [in]  t    ��Ԑ���W��
	* @return  Catmull-Rom ��Ԃ̌��ʂ�Ԃ��܂��B
	*/
	inline gt2Vector2 CatmullRom(const gt2Vector2& rV2, const gt2Vector2& rV3, const gt2Vector2& rV4, float t) const
	{
		return gt2Vector2::CatmullRom(*this, rV2, rV3, rV4, t);
	}
	/*!
	* @brief �w�肳�ꂽ�x�N�g�����g�p���āA�G���~�[�g �X�v���C����Ԃ����s���܂��B
	* @param [in]  rV1  ��Ԃ��s����� 1 �̈ʒu
	* @param [in]  rT1  �� 1 �̈ʒu�̐ڐ��x�N�g��
	* @param [in]  rV2  ��Ԃ��s����� 2 �̈ʒu
	* @param [in]  rT2  �� 2 �̈ʒu�̐ڐ��x�N�g��
	* @param [in]  t    ��Ԑ���W��
	* @return  ��Ԃ��܂܂ꂽ�x�N�g����Ԃ��܂��B
	*/
	inline static gt2Vector2 Hermite(const gt2Vector2& rV1, const gt2Vector2& rT1, const gt2Vector2& rV2, const gt2Vector2& rT2, float t)
	{
		float t2 = t * t;
		float t3 = t * t2;
		return (2 * t3 - 3 * t2 + 1) * rV1 +
			(t3 - 2 * t2 + t) * rT1 +
			(-2 * t3 + 3 * t2) * rV2 +
			(t3 - t2) * rT2;
	}
	/*!
	* @brief �w�肳�ꂽ�x�N�g�����g�p���āA�G���~�[�g �X�v���C����Ԃ����s���܂��B
	*   �� 1 �̈ʒu���A���g(this)�ł��B
	* @param [in]  rT1  �� 1 �̈ʒu�̐ڐ��x�N�g��
	* @param [in]  rV2  ��Ԃ��s����� 2 �̈ʒu
	* @param [in]  rT2  �� 2 �̈ʒu�̐ڐ��x�N�g��
	* @param [in]  t    ��Ԑ���W��
	* @return  ��Ԃ��܂܂ꂽ�x�N�g����Ԃ��܂��B
	*/
	inline gt2Vector2 Hermite(const gt2Vector2& rT1, const gt2Vector2& rV2, const gt2Vector2& rT2, float t) const
	{
		return gt2Vector2::Hermite(*this, rT1, rV2, rT2, t);
	}
	/*!
	* @brief 2D �@���x�N�g���ɂ���� 2D ���˃x�N�g���𔽎˂��܂��B
	* @param [in]  rvIncident  ���˂���� 2D ���˃x�N�g��
	* @param [in]  rvNormal    ���˃x�N�g���𔽎˂��� 2D �@���x�N�g��
	* @return  ���ˌ�̓��ˊp��Ԃ��܂��B
	*/
	inline static gt2Vector2 Refract(const gt2Vector2& rvIncident, const gt2Vector2& rvNormal)
	{
		return rvIncident - (2 * rvIncident.Dot(rvNormal)) * rvNormal;
	}
	/*!
	* @brief 2D �@���x�N�g���ɂ���� 2D ���˃x�N�g���𔽎˂��܂��B
	*   ���˂���� 2D ���˃x�N�g�����A���g(this)�ł��B
	* @param [in]  rvNormal    ���˃x�N�g���𔽎˂��� 2D �@���x�N�g��
	* @return  ���ˌ�̓��ˊp��Ԃ��܂��B
	*/
	inline gt2Vector2 Refract(const gt2Vector2& rvNormal) const
	{
		return gt2Vector2::Refract(*this, rvNormal);
	}
	/*!
	* @brief 2D �@���x�N�g���ɂ���� 2D ���˃x�N�g���𔽎˂��܂��B
	* @param [in]  rvIncident      ���˂���� 2D ���˃x�N�g��
	* @param [in]  rvNormal        ���˃x�N�g���𔽎˂��� 2D �@���x�N�g��
	* @param [in]  refractionIndex ���ܗ��B
	* @return  ���܂��ꂽ���˃x�N�g����Ԃ��܂��B���ܗ��A����ѓ��˃x�N�g���Ɩ@���x�N�g���Ԃ̊p�x�ɂ���āA
	*          ���ʂ��S���˂ɂȂ����ꍇ�́A< 0.0f, 0.0f > �Ƃ����`�̃x�N�g�����Ԃ���܂��B
	*/
	inline static gt2Vector2 Refract(const gt2Vector2& rvIncident, const gt2Vector2& rvNormal, float refractionIndex)
	{
		gt2Vector2 Result;
		float t = rvIncident.Dot(rvNormal);

		float r = 1.0f - refractionIndex * refractionIndex * (1.0f - t * t);
		if (r < 0.0f) // �S����
		{
			Result.x = 0.0f;
			Result.y = 0.0f;
		}
		else {
			float s = refractionIndex * t + sqrtf(r);
			Result.x = refractionIndex * rvIncident.x - s * rvNormal.x;
			Result.y = refractionIndex * rvIncident.y - s * rvNormal.y;
		}
		return Result;
	}
	/*!
	* @brief 2D �@���x�N�g���ɂ���� 2D ���˃x�N�g���𔽎˂��܂��B
	*   ���˂���� 2D ���˃x�N�g�����A���g(this)�ł��B
	* @param [in]  rvNormal        ���˃x�N�g���𔽎˂��� 2D �@���x�N�g��
	* @param [in]  refractionIndex ���ܗ��B
	* @return  ���܂��ꂽ���˃x�N�g����Ԃ��܂��B���ܗ��A����ѓ��˃x�N�g���Ɩ@���x�N�g���Ԃ̊p�x�ɂ���āA
	*          ���ʂ��S���˂ɂȂ����ꍇ�́A< 0.0f, 0.0f > �Ƃ����`�̃x�N�g�����Ԃ���܂��B
	*/
	inline gt2Vector2 Refract(const gt2Vector2& rvNormal, float refractionIndex) const
	{
		return gt2Vector2::Refract(*this, rvNormal, refractionIndex);
	}
	/*!
	* @brief l�̒������x�N�g���̒����ƂŊ������l���A�x�N�g���̊e�v�f�ɏ�Z�����l���Z�b�g����
	* @param [in]  rV  �^���x�N�g��
	* @param [in]  l   ����
	* @return  �Ȃ�
	*/
	inline void SetMakeLength(const gt2Vector2& rV, float l)
	{
		float fLen = rV.Length();
		x = rV.x * l / fLen;
		y = rV.y * l / fLen;
	}
	/*!
	* @brief  x,y �̒l�Ɠ����̒l�Ɣ�r���A�傫���l�����ꂼ��Z�b�g����
	* @param [in]  rV  �x�N�g��
	* @return  �Ȃ�
	*/
	inline void SetMax(const gt2Vector2& rV)
	{
		this->SetMax(rV.x, rV.y);
	}
	/*!
	* @brief  x,y �̒l�Ɠ����̒l�Ɣ�r���A�傫���l�����ꂼ��Z�b�g����
	* @param [in]  fx  �v�f x
	* @param [in]  fy  �v�f y
	* @return  �Ȃ�
	*/
	inline void SetMax(float fx, float fy)
	{
		x = x>fx ? x : fx;
		y = y>fy ? y : fy;
	}
	/*!
	* @brief  x,y �̒l�Ɠ����̒l�Ɣ�r���A�������l�����ꂼ��Z�b�g����
	* @param [in]  rV  �x�N�g��
	* @return  �Ȃ�
	*/
	inline void SetMin(const gt2Vector2& rV2)
	{
		this->SetMin(rV2.x, rV2.y);
	}
	/*!
	* @brief  x,y �̒l�Ɠ����̒l�Ɣ�r���A�������l�����ꂼ��Z�b�g����
	* @param [in]  fx  �v�f x
	* @param [in]  fy  �v�f y
	* @return  �Ȃ�
	*/
	inline void SetMin(float fx, float fy)
	{
		x = x<fx ? x : fx;
		y = y<fy ? y : fy;
	}
	/*!
	* @brief   Radian�l���擾����
	* @return   Radian�l���擾����
	*/
	inline float GetAxisZRadian() const
	{
		if (y < 0)
		{
			// 180���ȏ�
			float f = GT2_PI2 - acos(x);
			return f == GT2_PI2 ? 0 : f;
		}
		return acos(x);
	}
	/*!
	* @brief   �p�x���擾����
	* @return   �p�x��Ԃ�
	*/
	inline float GetAxisZAngle() const
	{
		return GetAxisZRadian() * GT2_RADIAN;
	}

	/*!
	* @brief   ���g��x,y �̒l���������l�̌ܓ�����
	* @return   �Ȃ�
	*/
	inline void MyRound()
	{
		x = floor(x + 0.5f);
		y = floor(y + 0.5f);
	}
	/*!
	* @brief   ���g��x,y �̒l�̏�����؂�̂�
	* @return   �Ȃ�
	*/
	inline void MyFloor()
	{
		x = floor(x);
		y = floor(y);
	}
	/*!
	* @brief   ���g��x,y�̂��ꂼ����p�x���烉�W�A���l��
	* @return   �Ȃ�
	*/
	inline void ToRadianFromAngle()
	{
		x *= GT2_RADIAN;
		y *= GT2_RADIAN;
	}
	/*!
	* @brief   ���g��x,y�̂��ꂼ������W�A������p�x�l��
	* @return   �Ȃ�
	*/
	inline void ToAngleFromRadian()
	{
		x *= GT2_INV_RADIAN;
		y *= GT2_INV_RADIAN;
	}
};
const gt2Vector2 g_VF2IdentityR0 = gt2Vector2(1, 0);
const gt2Vector2 g_VF2IdentityR1 = gt2Vector2(0, 1);









/*!
* @brief 3�v�f(x,y,z) �x�N�g��
*/
typedef struct gt2Vector3
{
public:
	union {
		struct {
			float x;	//!< �v�f x
			float y;	//!< �v�f y
			float z;	//!< �v�f z
		};
		float v[3];		//!< v[0] = x, v[1] = y, v[2] = z
	};
public:

	/*!
	* @brief �R���X�g���N�^
	*  x,y,z���O�ŏ����������
	*/
	gt2Vector3() { this->Init(); }
	/*!
	* @brief �R���X�g���N�^
	*   x,y,z��pf�|�C���^�̒l�ɂ�菉���������
	* @param [in] pf     3�v�f�ȏ��float��񂪂���|�C���^
	*/
	gt2Vector3(const float * pF) { x = pF[0]; y = pF[1]; z = pF[2]; }
	/*!
	* @brief �R���X�g���N�^
	*  rV�ŏ����������
	* @param [in] rV     �x�N�g��
	*/
	gt2Vector3(const gt2Vector3& rV3) { *this = rV3; }
	/*!
	* @brief �R���X�g���N�^
	*   x=fx,y=fy,z=fz �Ƃ����������ɏ����������
	* @param [in] fx     x�l
	* @param [in] fy     y�l
	* @param [in] fz     y�l
	*/
	gt2Vector3(float fx, float fy, float fz) { x = fx; y = fy; z = fz; }

#ifdef B2_MATH_H
	gt2Vector3& operator= (const b2Vec3& v3) { x = v3.x; y = v3.y; z = v3.z; return *this; }
#endif

#if defined(MC_DIRECTX)
	//gt2Vector3&   operator= (const DirectX::XMFLOAT2& vf) { x = vf.x; y = vf.y; return *this; }
	//gt2Vector3&   operator= (const DirectX::XMFLOAT3& vf) { x = vf.x; y = vf.y; z = vf.z; return *this; }
	//gt2Vector3&   operator= (const DirectX::XMFLOAT4& vf) { x = vf.x; y = vf.y; z = vf.z; return *this; }
	//gt2Vector3&   operator= (const DirectX::XMVECTOR& vf) { x = vf.m128_f32[0]; y = vf.m128_f32[1]; z = vf.m128_f32[2]; return *this; }

	//DirectX::XMFLOAT2 GetXMFLOAT2() const { DirectX::XMFLOAT2 t; t.x = x; t.y = y; return t; }
	//DirectX::XMFLOAT3 GetXMFLOAT3() const { DirectX::XMFLOAT3 t; t.x = x; t.y = y; t.z = z; return t; }
	//DirectX::XMFLOAT4 GetXMFLOAT4() const { DirectX::XMFLOAT4 t; t.x = x; t.y = y; t.z = z; t.w = 0; return t; }
	//DirectX::XMVECTOR GetXMVECTOR() const { DirectX::XMVECTOR t; t.m128_f32[0] = x; t.m128_f32[1] = y; t.m128_f32[2] = z; t.m128_f32[3] = 0; return t; }

#endif

	/*!
	* @brief x,y,z�̒l���O�ŏ����������
	* @return �Ȃ�
	*/
	inline void Init() { x = y = z = 0; }
	/*!
	* @brief x,y,z�̒l��float�^�̍ŏ��l��FLT_MAX�ŏ����������
	* @return �Ȃ�
	*/
	inline void InitMin() { x = y = z = FLT_MAX; }
	/*!
	* @brief x,y,z�̒l��float�^�̍ŏ��l��FLT_MAX�ŏ����������
	* @return �Ȃ�
	*/
	inline void InitMax() { x = y = z = -FLT_MAX; }
	/**
	* @param [in] fx     x�l
	* @param [in] fy     y�l
	* @param [in] fz     z�l
	*/
	inline void Set(float fx, float fy, float fz) { x = fx; y = fy; z = fz; }

	//------------------------------------------------------------------------
	//
	// ������Z�q
	//
	//------------------------------------------------------------------------
	/*!
	* @brief ������Z�q =
	*   �ʏ�̑��
	* @param [in] v     �E�ӂ̃x�N�g��gt2Vector3
	* @return ���Z���ꂽ�x�N�g���l��Ԃ�
	*/
	inline gt2Vector3& operator = (const gt2Vector3& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}
	/*!
	* @brief ������Z�q =
	*   ���g(this)�̃x�N�g���l�։E�ӂ�2�v�f�̃x�N�g����������Bz�͏�ɂO�B
	* @param [in] rV     �E�ӂ�2�v�f�x�N�g��
	* @return ������ꂽ2�v�f�̃x�N�g��������3�v�f�̃x�N�g����Ԃ��B
	*/
	inline gt2Vector3& operator = (const gt2Vector2& rV)
	{
		x = rV.x;
		y = rV.y;
		z = 0.0f;

		return *this;
	}

	/*!
	* @brief ������Z�q +=
	*   ���g(this)�̃x�N�g���l���E�ӂ̃x�N�g���l�����Z�����l�����g(this)�ɃZ�b�g����
	* @param [in] rV     �E�ӂ̃x�N�g��gt2Vector3
	* @return ���Z���ꂽ�x�N�g���l��Ԃ�
	*/
	inline gt2Vector3& operator += (const gt2Vector3& rV)
	{
		x += rV.x;
		y += rV.y;
		z += rV.z;

		return *this;
	}
	/*!
	* @brief ������Z�q -=
	*   ���g(this)�̃x�N�g���l���E�ӂ̃x�N�g���l�����Z�����l�����g(this)�ɃZ�b�g����
	* @param [in] rV     �E�ӂ̃x�N�g��gt2Vector3
	* @return ���Z���ꂽ�x�N�g���l��Ԃ�
	*/
	inline gt2Vector3& operator -= (const gt2Vector3& rV)
	{
		x -= rV.x;
		y -= rV.y;
		z -= rV.z;

		return *this;
	}
	inline gt2Vector3& operator *= (const gt2Vector3& v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}

	inline gt2Vector3& operator /= (const gt2Vector3& v)
	{
		x /= v.x;
		y /= v.y;
		z /= v.z;
		return *this;
	}

	/*!
	* @brief ������Z�q *=
	*   ���g(this)�̃x�N�g���l���E�ӂ̂P�̒l����Z�����l�����g(this)�ɃZ�b�g����
	* @param [in] f     �E�ӂ�1�̒l
	* @return ��Z���ꂽ�x�N�g���l��Ԃ�
	*/
	inline gt2Vector3& operator *= (float f)
	{
		x *= f;
		y *= f;
		z *= f;

		return *this;
	}
	/*!
	* @brief ������Z�q *=
	*   ���g(this)�̃x�N�g���l���E�ӂ̂P�̒l�����Z�����l�����g(this)�ɃZ�b�g����
	* @param [in] f     �E�ӂ�1�̒l
	* @return ���Z���ꂽ�x�N�g���l��Ԃ�
	*/
	inline gt2Vector3& operator /= (float f)
	{
		x /= f;
		y /= f;
		z /= f;

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
	* @return ���̂܂܂̃x�N�g���l��Ԃ�
	*/
	inline gt2Vector3 operator + () const
	{
		return *this;
	}
	/*!
	* @brief �P�����Z�q -
	*   �e�v�f��-1����Z�����x�N�g���l�ɂȂ�
	* @return �e�v�f��-1����Z�����x�N�g���l��Ԃ�
	*/
	inline gt2Vector3 operator - () const
	{
		return gt2Vector3(-x, -y, -z);
	}

	//##################################################################
	//##
	//## ��P�����Z�q
	//##
	//##################################################################
	/*!
	* @brief �񍀉��Z�q +
	*   ���g(this)�̃x�N�g����"rV"�x�N�g�������Z����
	* @param [in] rV     gt2Vector3
	* @return ���g(this)�̃x�N�g����"rV"�x�N�g���l�����Z�����l��Ԃ�
	*/
	inline gt2Vector3 operator + (const gt2Vector3& rV) const
	{
		gt2Vector3 vTmp;

		vTmp.x = x + rV.x;
		vTmp.y = y + rV.y;
		vTmp.z = z + rV.z;

		return vTmp;
	}
	/*!
	* @brief �񍀉��Z�q -
	*   ���g(this)�̃x�N�g����"rV"�x�N�g�������Z����
	* @param [in] rV     gt2Vector3
	* @return ���g(this)�̃x�N�g����"rV"�x�N�g���l�����Z�����l��Ԃ�
	*/
	inline gt2Vector3 operator - (const gt2Vector3& rV) const
	{
		gt2Vector3 vTmp;

		vTmp.x = x - rV.x;
		vTmp.y = y - rV.y;
		vTmp.z = z - rV.z;

		return vTmp;
	}
	/*!
	* @brief �񍀉��Z�q +
	*   ���g(this)�̃x�N�g���̗v�f����"f"�̒l�����Z����
	* @param [in] f     1�̒l
	* @return ���g(this)�̃x�N�g���̗v�f����"f"�̒l�����Z�����l��Ԃ�
	*/
	inline gt2Vector3 operator + (float f) const
	{
		gt2Vector3 vTmp;

		vTmp.x = x + f;
		vTmp.y = y + f;
		vTmp.z = z + f;

		return vTmp;
	}
	/*!
	* @brief �񍀉��Z�q -
	*   ���g(this)�̃x�N�g���̗v�f����"f"�̒l�����Z����
	* @param [in] f     1�̒l
	* @return ���g(this)�̃x�N�g���̗v�f����"f"�̒l�����Z�����l��Ԃ�
	*/
	inline gt2Vector3 operator - (float f) const
	{
		gt2Vector3 vTmp;

		vTmp.x = x - f;
		vTmp.y = y - f;
		vTmp.z = z - f;

		return vTmp;
	}
	/*!
	* @brief �񍀉��Z�q *
	*   ���g(this)�̃x�N�g���̗v�f����"f"�̒l����Z����
	* @param [in] f     1�̒l
	* @return ���g(this)�̃x�N�g���̗v�f����"f"�̒l����Z�����l��Ԃ�
	*/
	inline gt2Vector3 operator * (float f) const
	{
		gt2Vector3 vTmp;

		vTmp.x = x * f;
		vTmp.y = y * f;
		vTmp.z = z * f;

		return vTmp;
	}

	friend inline gt2Vector3 operator * (float f, const gt2Vector3& rV3)
	{
		return rV3 * f;
	}
	/*!
	* @brief �񍀉��Z�q *
	*   ���g(this)�̃x�N�g����"rV"�x�N�g���̗v�f���Ə�Z����
	* @param [in] rV     gt2Vector3
	* @return ���g(this)�̃x�N�g����"rV"�x�N�g���̗v�f���Ə�Z�����l��Ԃ�
	*/
	inline gt2Vector3 operator * (const gt2Vector3& rV) const
	{
		gt2Vector3 vTmp;

		vTmp.x = x * rV.x;
		vTmp.y = y * rV.y;
		vTmp.z = z * rV.z;

		return vTmp;
	}

	friend inline gt2Vector3 operator + (float f, const gt2Vector3& rV3)
	{
		return rV3 + f;
	}

	friend inline gt2Vector3 operator - (float f, const gt2Vector3& rV3)
	{
		return rV3 - f;
	}
	/*!
	* @brief �񍀉��Z�q /
	*   ���g(this)�̃x�N�g���̗v�f����"f"�̒l�����Z����
	* @param [in] f     1�̒l
	* @return ���g(this)�̃x�N�g���̗v�f����"f"�̒l�����Z�����l��Ԃ�
	*/
	inline gt2Vector3 operator / (float f) const
	{
		gt2Vector3 vTmp;

		vTmp.x = x / f;
		vTmp.y = y / f;
		vTmp.z = z / f;

		return vTmp;
	}
	/*!
	* @brief �񍀉��Z�q /
	*   ���g(this)�̃x�N�g����"rV"�x�N�g���̗v�f���Ə��Z����
	* @param [in] rV     gt2Vector2
	* @return ���g(this)�̃x�N�g����"rV"�x�N�g���̗v�f���Ə��Z�����l��Ԃ�
	*/
	inline gt2Vector3 operator / (const gt2Vector3& rV) const
	{
		gt2Vector3 vTmp;

		vTmp.x = x / rV.x;
		vTmp.y = y / rV.y;
		vTmp.z = z / rV.z;

		return vTmp;
	}


	//##################################################################
	//##
	//## ��r���Z�q
	//##
	//##################################################################
	/*!
	* @brief ��r���Z�q ==
	*   ���g(this)�̃x�N�g����"rV"�x�N�g���̊e�v�f����������r����
	* @param [in] rV     gt2Vector3
	* @return ���g(this)�̃x�N�g����"rV"�x�N�g���̊e�v�f���r���A����Ȃ�true��Ԃ��B
	*/
	inline bool operator == (const gt2Vector3& rV) const
	{
		return x == rV.x && y == rV.y && z == rV.z;
	}
	/*!
	* @brief ��r���Z�q !=
	*   ���g(this)�̃x�N�g����"rV"�x�N�g���̊e�v�f���Ⴄ����r����
	* @param [in] rV     gt2Vector3
	* @return ���g(this)�̃x�N�g����"rV"�x�N�g���̊e�v�f���r���A�Ⴄ�ꍇtrue��Ԃ��B
	*/
	inline bool operator != (const gt2Vector3& rV) const
	{
		return !(*this == rV);
	}



	//##################################################################
	//##
	//## 
	//##
	//##################################################################
	/*!
	* @brief  gt2Vector2�̒l��Ԃ��B
	* @return  gt2Vector2
	*/
	inline gt2Vector2 GetV2() const { return gt2Vector2(x,y); }

	/*!
	* @brief  x,y,z �̒l�Ɠ����̒l�Ɣ�r���A�傫���l�����ꂼ��Z�b�g����
	* @param [in]  rV  �x�N�g��
	* @return  �Ȃ�
	*/
	inline void SetMax(const gt2Vector3& rV)
	{
		this->SetMax(rV.x, rV.y, rV.z);
	}
	/*!
	* @brief  x,y,z �̒l�Ɠ����̒l�Ɣ�r���A�傫���l�����ꂼ��Z�b�g����
	* @param [in]  fx  �v�f x
	* @param [in]  fy  �v�f y
	* @param [in]  fz  �v�f z
	* @return  �Ȃ�
	*/
	inline void SetMax(float fx, float fy, float fz)
	{
		x = x>fx ? x : fx;
		y = y>fy ? y : fy;
		z = z>fz ? z : fz;
	}
	/*!
	* @brief   ���g��x,y,z �̒l���������l�̌ܓ�����
	* @return   �Ȃ�
	*/
	inline void MyRound()
	{
		x = floor(x + 0.5f);
		y = floor(y + 0.5f);
		z = floor(z + 0.5f);
	}
	/*!
	* @brief   ���g��x,y,z �̒l�̏�����؂�̂�
	* @return   �Ȃ�
	*/
	inline void MyFloor()
	{
		x = floor(x);
		y = floor(y);
		z = floor(z);
	}
	/*!
	* @brief   ���g��x,y,z�̂��ꂼ����p�x���烉�W�A���l��
	* @return   �Ȃ�
	*/
	inline void ToRadianFromAngle()
	{
		x *= GT2_RADIAN;
		y *= GT2_RADIAN;
		z *= GT2_RADIAN;
	}
	/*!
	* @brief   ���g��x,y,z�̂��ꂼ������W�A������p�x�l��
	* @return   �Ȃ�
	*/
	inline void ToAngleFromRadian()
	{
		x *= GT2_INV_RADIAN;
		y *= GT2_INV_RADIAN;
		z *= GT2_INV_RADIAN;
	}

	/*!
	* @brief  x,y,z �̒l�Ɠ����̒l�Ɣ�r���A�������l�����ꂼ��Z�b�g����
	* @param [in]  rV  �x�N�g��
	* @return  �Ȃ�
	*/
	inline void SetMin(const gt2Vector3& rV)
	{
		this->SetMin(rV.x, rV.y, rV.z);
	}
	/*!
	* @brief  x,y,z �̒l�Ɠ����̒l�Ɣ�r���A�������l�����ꂼ��Z�b�g����
	* @param [in]  fx  �v�f x
	* @param [in]  fy  �v�f y
	* @param [in]  fz  �v�f z
	* @return  �Ȃ�
	*/
	inline void SetMin(float fx, float fy, float fz)
	{
		x = x<fx ? x : fx;
		y = y<fy ? y : fy;
		z = z<fz ? z : fz;
	}
	/*!
	* @brief �p�x(0�`360)���烉�W�A���l�ɕϊ�����x,y,z�ɑ������
	* @param [in] fx     �p�x(0�`360)
	* @param [in] fy     �p�x(0�`360)
	* @param [in] fz     �p�x(0�`360)
	* @return �Ȃ�
	*/
	inline void MakeRadianToDegrees(float fx, float fy, float fz)
	{
		x = GT2_INV_RADIAN * fx;
		y = GT2_INV_RADIAN * fy;
		z = GT2_INV_RADIAN * fz;
	}

	/*!
	* @brief �x�N�g���̒�����Ԃ��B
	* @return �x�N�g���̒�����Ԃ��B
	*/
	inline float Length() const
	{
		return sqrt(x*x + y*y + z*z);
	}
	/*!
	* @brief �x�N�g���̒����� 2 ���Ԃ��B
	* @return �x�N�g���̒����� 2 ���Ԃ��B
	*/
	inline float LengthSq() const
	{
		return x*x + y*y + z*z;
	}
	/*!
	* @brief ����
	*   �x�N�g���̓��ς����߂܂��B
	* @return  ���ς�Ԃ��B
	*/
	inline float Dot() const
	{
		return x*x + y*y + z*z;
	}
	/*!
	* @brief ����
	*   ���g(this)�̃x�N�g����"rV"�x�N�g������ς���
	* @param [in] rV     �Ώۃx�N�g��
	* @return  ���ς�Ԃ��B
	*/
	inline float Dot(const gt2Vector3& rV) const
	{
		return x*rV.x + y*rV.y + z*rV.z;
	}
	/*!
	* @brief �O��
	*   v = rV1 �~ rV2
	* @param [in] rV1     1�߂̑Ώۃx�N�g��
	* @param [in] rV2     2�߂̑Ώۃx�N�g��
	* @return  �O�ς����x�N�g����Ԃ��B
	*/
	inline static gt2Vector3 Cross(const gt2Vector3& rV1, const gt2Vector3& rV2)
	{
		gt2Vector3 out;
		out.x = rV1.y*rV2.z - rV1.z*rV2.y;
		out.y = -(rV1.x*rV2.z - rV1.z*rV2.x);
		out.z = rV1.x*rV2.y - rV1.y*rV2.x;
		return out;
	}
	/*!
	* @brief �O��
	*   v = ���g(this) �~ rV
	* @param [in] rV     2�߂̑Ώۃx�N�g��
	* @return  �O�ς��ꂽ�x�N�g����Ԃ��B
	*/
	inline gt2Vector3 Cross(const gt2Vector3& rV) const
	{
		return gt2Vector3::Cross(*this, rV);
	}
	/*!
	* @brief �x�N�g���̉��Z
	*   ���g(this)�̃x�N�g����"rV"�x�N�g�������Z����B
	* @param [in] rV     ���� gt2Vector2 �\����
	* @return  ���Z���ꂽ�x�N�g����Ԃ��B
	*/
	inline gt2Vector3 Add(const gt2Vector3& rV) const
	{
		gt2Vector3 out;
		out.x = x + rV.x;
		out.y = y + rV.y;
		out.z = z + rV.z;
		return out;
	}
	/*!
	* @brief �x�N�g���̌��Z
	*   ���g(this)�̃x�N�g����"rV"�x�N�g�������Z����B
	* @param [in] rV     ���� gt2Vector4 �\����
	* @return  ���Z���ꂽ�x�N�g����Ԃ��B
	*/
	inline gt2Vector3 Subtract(const gt2Vector3& rV) const
	{
		gt2Vector3 out;
		out.x = x - rV.x;
		out.y = y - rV.y;
		out.z = z - rV.z;
		return out;
	}
	/*!
	* @brief 2�̃x�N�g���̗v�f���r���ŏ��l�̗v�f�̃x�N�g����Ԃ�
	* @param [in] rV     ���� gt2Vector3 �\����
	* @return  �ŏ��l�̗v�f�̃x�N�g����Ԃ�
	*/
	inline gt2Vector3 Minimize(const gt2Vector3& rV) const
	{
		gt2Vector3 out;
		out.x = x < rV.x ? x : rV.x;
		out.y = y < rV.y ? y : rV.y;
		out.z = z < rV.z ? z : rV.z;
		return out;
	}
	/*!
	* @brief 2�̃x�N�g���̗v�f���r���ő�l�̗v�f�̃x�N�g�����擾����
	* @param [in] rV     ���� gt2Vector3 �\����
	* @return  �ő�l�̗v�f�̃x�N�g����Ԃ�
	*/
	inline gt2Vector3 Maximize(const gt2Vector3& rV) const
	{
		gt2Vector3 out;
		out.x = x > rV.x ? x : rV.x;
		out.y = y > rV.y ? y : rV.y;
		out.z = z > rV.z ? z : rV.z;
		return out;
	}
	/*!
	* @brief �O�d�� U�EV�~W
	* @param [in] rV     ���_V
	* @param [in] pW     ���_W
	* @return  �O�d�ς̃x�N�g����Ԃ�
	*/
	inline float ScalarTriple(const gt2Vector3& rV, const gt2Vector3* pW) const
	{
		return float((x * (rV.y*pW->z - rV.z*pW->y)) +
			(y * (-rV.x*pW->z + rV.z*pW->x)) +
			(z * (rV.x*pW->y - rV.y*pW->x)));

	}
	/*!
	* @brief �O�d�� U�EV�~W
	* @param [in] rV     ���_V
	* @param [in] rW     ���_W
	* @return  �O�d�ς̃x�N�g����Ԃ�
	*/
	inline float ScalarTriple(const gt2Vector3& rV, const gt2Vector3& rW) const
	{
		return this->ScalarTriple(rV, &rW);
	}
	/*!
	* @brief �x�N�g�����X�P�[�����O����B
	* @param [in]  s      �X�P�[�����O�l�B
	* @return  �x�N�g�����X�P�[�����O�������̂�Ԃ��B
	*/
	inline gt2Vector3 Scale(float s) const
	{
		return gt2Vector3(x * s, y * s, z * s);
	}
	/*!
	* @brief �x�N�g���Ԃ̐��`��Ԃ����s����B
	* @param [in]  rV1   �� 1 �Ԗڂ̃x�N�g��
	* @param [in]  rV2   �� 2 �Ԗڂ̃x�N�g��
	* @param [in]  t     �x�N�g���Ԃ���`��Ԃ���p�����[�^�B
	* @return  ���`��Ԃ��ꂽ�x�N�g����Ԃ��B
	*/
	inline static gt2Vector3 Lerp(const gt2Vector3& rV1, const gt2Vector3& rV2, float t)
	{
		return gt2Vector3(
			rV1.x + t * (rV2.x - rV1.x),
			rV1.y + t * (rV2.y - rV1.y),
			rV1.z + t * (rV2.z - rV1.z)
		);
	}
	/*!
	* @brief �x�N�g���Ԃ̐��`��Ԃ����s����B
	*   �� 1 �Ԗڂ̃x�N�g�����A���g(this)�ł��B
	* @param [in]  rV2   �� 2 �Ԗڂ̃x�N�g��
	* @param [in]  t     �x�N�g���Ԃ���`��Ԃ���p�����[�^�B
	* @return  ���`��Ԃ��ꂽ�x�N�g����Ԃ��B
	*/
	inline gt2Vector3 Lerp(const gt2Vector3& rV2, float t) const
	{
		return gt2Vector3::Lerp(*this, rV2, t);
	}

	/*!
	* @brief 0 �� t �� 1 �̊ԂŃG���~�[�g��Ԃɂ�銊�炩�ȕ�Ԃ��s���܂��B
	* @param [in]  rV1  1 �Ԗڂ̃x�N�g���B
	* @param [in]  rV2  2 �Ԗڂ̃x�N�g���B
	* @param [in]  t   �x�N�g���Ԃ���`��Ԃ���p�����[�^�B�͈�[0�`1.0]
	* @return  ��Ԃ��ꂽ�x�N�g����Ԃ��B
	*/
	inline static gt2Vector3 SmoothStep(const gt2Vector3& rV1, const gt2Vector3& rV2, float t)
	{
		t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
		t = t*t*(3.f - 2.f*t);
		return gt2Vector3::Lerp(rV1, rV2, t);
	}
	/*!
	* @brief 0 �� t �� 1 �̊ԂŃG���~�[�g��Ԃɂ�銊�炩�ȕ�Ԃ��s���܂��B
	*   �� 1 �Ԗڂ̃x�N�g�����A���g(this)�ł��B
	* @param [in]  rV  2 �Ԗڂ̃x�N�g���B
	* @param [in]  t   �x�N�g���Ԃ���`��Ԃ���p�����[�^�B�͈�[0�`1.0]
	* @return  ��Ԃ��ꂽ�x�N�g����Ԃ��B
	*/
	inline gt2Vector3 SmoothStep(const gt2Vector3& rV2, float t) const
	{
		return gt2Vector3::SmoothStep(*this, rV2, t);
	}
	/*!
	* @brief �w�肳�ꂽ�ʒu�x�N�g�����g�p���āA�d�S���W�̃|�C���g��Ԃ��܂��B
	* @param [in]  rV1  �� 1 �̈ʒu
	* @param [in]  rV2  �� 2 �̈ʒu
	* @param [in]  rV3  �� 3 �̈ʒu
	* @param [in]  f    ���d�W���B
	* @param [in]  g    ���d�W���B
	* @return  �d�S���W��Ԃ��܂��B
	*/
	inline static gt2Vector3 Barycentric(const gt2Vector3& rV1, const gt2Vector3& rV2, const gt2Vector3& rV3, float f, float g)
	{
		return rV1 + f * (rV2 - rV1) + g * (rV3 - rV1);
	}
	/*!
	* @brief �w�肳�ꂽ�ʒu�x�N�g�����g�p���āA�d�S���W�̃|�C���g��Ԃ��܂��B
	*   �� 1 �̈ʒu���A���g(this)�ł��B
	* @param [in]  rV2  �� 2 �̈ʒu
	* @param [in]  rV3  �� 3 �̈ʒu
	* @param [in]  f    ���d�W���B
	* @param [in]  g    ���d�W���B
	* @return  �d�S���W��Ԃ��܂��B
	*/
	inline gt2Vector3 Barycentric(const gt2Vector3& rV2, const gt2Vector3& rV3, float f, float g) const
	{
		return gt2Vector3::Barycentric(*this, rV2, rV3, f, g);
	}
	/*!
	* @brief �w�肳�ꂽ�ʒu�x�N�g�����g�p���āACatmull-Rom ��Ԃ��s���܂��B
	* @param [in]  rV1  �� 1 �̈ʒu
	* @param [in]  rV2  �� 2 �̈ʒu
	* @param [in]  rV3  �� 3 �̈ʒu
	* @param [in]  rV4  �� 3 �̈ʒu
	* @param [in]  t    ��Ԑ���W��
	* @return  Catmull-Rom ��Ԃ̌��ʂ�Ԃ��܂��B
	*/
	inline static gt2Vector3 CatmullRom(const gt2Vector3& rV1, const gt2Vector3& rV2, const gt2Vector3& rV3, const gt2Vector3& rV4, float t)
	{
		float t2 = t * t;
		float t3 = t * t2;
		return ((-t3 + 2 * t2 - t) * rV1 +
			(3 * t3 - 5 * t2 + 2) * rV2 +
			(-3 * t3 + 4 * t2 + t) * rV3 +
			(t3 - t2) * rV4) * 0.5f;
	}
	/*!
	* @brief �w�肳�ꂽ�ʒu�x�N�g�����g�p���āACatmull-Rom ��Ԃ��s���܂��B
	*   �� 1 �̈ʒu���A���g(this)�ł��B
	* @param [in]  rV2  �� 2 �̈ʒu
	* @param [in]  rV3  �� 3 �̈ʒu
	* @param [in]  rV4  �� 3 �̈ʒu
	* @param [in]  t    ��Ԑ���W��
	* @return  Catmull-Rom ��Ԃ̌��ʂ�Ԃ��܂��B
	*/
	inline gt2Vector3 CatmullRom(const gt2Vector3& rV2, const gt2Vector3& rV3, const gt2Vector3& rV4, float t) const
	{
		return gt2Vector3::CatmullRom(*this, rV2, rV3, rV4, t);
	}
	/*!
	* @brief �w�肳�ꂽ�x�N�g�����g�p���āA�G���~�[�g �X�v���C����Ԃ����s���܂��B
	* @param [in]  rV1  ��Ԃ��s����� 1 �̈ʒu
	* @param [in]  rT1  �� 1 �̈ʒu�̐ڐ��x�N�g��
	* @param [in]  rV2  ��Ԃ��s����� 2 �̈ʒu
	* @param [in]  rT2  �� 2 �̈ʒu�̐ڐ��x�N�g��
	* @param [in]  t    ��Ԑ���W��
	* @return  ��Ԃ��܂܂ꂽ�x�N�g����Ԃ��܂��B
	*/
	inline static gt2Vector3 Hermite(const gt2Vector3& rV1, const gt2Vector3& rT1, const gt2Vector3& rV2, const gt2Vector3& rT2, float t)
	{
		float t2 = t * t;
		float t3 = t * t2;
		return (2 * t3 - 3 * t2 + 1) * rV1 +
			(t3 - 2 * t2 + t) * rT1 +
			(-2 * t3 + 3 * t2) * rV2 +
			(t3 - t2) * rT2;
	}
	/*!
	* @brief �w�肳�ꂽ�x�N�g�����g�p���āA�G���~�[�g �X�v���C����Ԃ����s���܂��B
	*   �� 1 �̈ʒu���A���g(this)�ł��B
	* @param [in]  rT1  �� 1 �̈ʒu�̐ڐ��x�N�g��
	* @param [in]  rV2  ��Ԃ��s����� 2 �̈ʒu
	* @param [in]  rT2  �� 2 �̈ʒu�̐ڐ��x�N�g��
	* @param [in]  t    ��Ԑ���W��
	* @return  ��Ԃ��܂܂ꂽ�x�N�g����Ԃ��܂��B
	*/
	inline gt2Vector3 Hermite(const gt2Vector3& rT1, const gt2Vector3& rV2, const gt2Vector3& rT2, float t) const
	{
		return gt2Vector3::Hermite(*this, rT1, rV2, rT2, t);
	}
	/*!
	* @brief 3D �@���x�N�g���ɂ���� 3D ���˃x�N�g���𔽎˂��܂��B
	* @param [in]  rvIncident  ���˂���� 3D ���˃x�N�g��
	* @param [in]  rvNormal    ���˃x�N�g���𔽎˂��� 3D �@���x�N�g��
	* @return  ���ˌ�̓��ˊp��Ԃ��܂��B
	*/
	inline static gt2Vector3 Refract(const gt2Vector3& rvIncident, const gt2Vector3& rvNormal)
	{
		return rvIncident - (2 * rvIncident.Dot(rvNormal)) * rvNormal;
	}
	/*!
	* @brief 3D �@���x�N�g���ɂ���� 3D ���˃x�N�g���𔽎˂��܂��B
	*   ���˂���� 3D ���˃x�N�g�����A���g(this)�ł��B
	* @param [in]  rvNormal    ���˃x�N�g���𔽎˂��� 3D �@���x�N�g��
	* @return  ���ˌ�̓��ˊp��Ԃ��܂��B
	*/
	inline gt2Vector3 Refract(const gt2Vector3& rvNormal) const
	{
		return gt2Vector3::Refract(*this, rvNormal);
	}
	/*!
	* @brief 3D �@���x�N�g���ɂ���� 3D ���˃x�N�g���𔽎˂��܂��B
	* @param [in]  rvIncident      ���˂���� 3D ���˃x�N�g��
	* @param [in]  rvNormal        ���˃x�N�g���𔽎˂��� 3D �@���x�N�g��
	* @param [in]  refractionIndex ���ܗ��B
	* @return  ���܂��ꂽ���˃x�N�g����Ԃ��܂��B���ܗ��A����ѓ��˃x�N�g���Ɩ@���x�N�g���Ԃ̊p�x�ɂ���āA
	*          ���ʂ��S���˂ɂȂ����ꍇ�́A< 0.0f, 0.0f, 0.0f > �Ƃ����`�̃x�N�g�����Ԃ���܂��B
	*/
	inline static gt2Vector3 Refract(const gt2Vector3& rvIncident, const gt2Vector3& rvNormal, float refractionIndex)
	{
		gt2Vector3 Result;
		float t = rvIncident.Dot(rvNormal);

		float r = 1.0f - refractionIndex * refractionIndex * (1.0f - t * t);
		if (r < 0.0f) // �S����
		{
			Result.x = 0.0f;
			Result.y = 0.0f;
			Result.z = 0.0f;
		}
		else {
			float s = refractionIndex * t + sqrtf(r);
			Result.x = refractionIndex * rvIncident.x - s * rvNormal.x;
			Result.y = refractionIndex * rvIncident.y - s * rvNormal.y;
			Result.z = refractionIndex * rvIncident.z - s * rvNormal.z;
		}
		return Result;
	}
	/*!
	* @brief 3D �@���x�N�g���ɂ���� 2D ���˃x�N�g���𔽎˂��܂��B
	*   ���˂���� 3D ���˃x�N�g�����A���g(this)�ł��B
	* @param [in]  rvNormal        ���˃x�N�g���𔽎˂��� 3D �@���x�N�g��
	* @param [in]  refractionIndex ���ܗ��B
	* @return  ���܂��ꂽ���˃x�N�g����Ԃ��܂��B���ܗ��A����ѓ��˃x�N�g���Ɩ@���x�N�g���Ԃ̊p�x�ɂ���āA
	*          ���ʂ��S���˂ɂȂ����ꍇ�́A< 0.0f, 0.0f, 0.0f > �Ƃ����`�̃x�N�g�����Ԃ���܂��B
	*/
	inline gt2Vector3 Refract(const gt2Vector3& rvNormal, float refractionIndex) const
	{
		return gt2Vector3::Refract(*this, rvNormal, refractionIndex);
	}
	/*!
	* @brief l�̒������x�N�g���̒����ƂŊ������l���A�x�N�g���̊e�v�f�ɏ�Z�����l���Z�b�g����
	* @param [in]  rV  �^���x�N�g��
	* @param [in]  l   ����
	* @return  �Ȃ�
	*/
	inline void SetMakeLength(const gt2Vector3& rV, float fL) {
		float fLen = rV.Length();
		x = rV.x * fL / fLen;
		y = rV.y * fL / fLen;
		z = rV.z * fL / fLen;
	}
	/*!
	* @brief ���g(this)�̃x�N�g���𐳋K������B
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
	}
	/*!
	* @brief �x�N�g���𐳋K�������x�N�g����Ԃ��܂��B
	* @param [out] pOut     ���Z���ʂł��� gt2Vector3 �\���̂ւ̃|�C���^�B
	* @return  �x�N�g���𐳋K�������x�N�g����Ԃ��B
	*/
	inline gt2Vector3* Normalize(gt2Vector3* pOut) const
	{
		float fL = this->Length();
		if (fL == 0.0f) {
			*pOut = gt2Vector3(0.0f, 0.0f, 0.0f);
			return pOut;
		}
		*pOut = *this;

		fL = 1.0f / fL;
		pOut->x *= fL;
		pOut->y *= fL;
		pOut->z *= fL;
		return pOut;
	}
	/*!
	* @brief �x�N�g���𐳋K�������x�N�g����Ԃ��B
	* @param [out] rOut     ���Z���ʂł��� gt2Vector3�B
	* @return  �Ȃ�
	*/
	inline void Normalize(gt2Vector3& rOut) const
	{
		this->Normalize(&rOut);
	}

	/*!
	* @brief �x�N�g���̗v�f���A�w�肳�ꂽ�ő�l�ƍŏ��l�͈̔͂ɃN�����v���܂��B
	* @param [in] rMin     �ŏ��͈̓x�N�g��
	* @param [in] rMax     �ő�͈̓x�N�g��
	* @return  �Ȃ�
	*/
	void Clamp(const gt2Vector3& rMin, const gt2Vector3& rMax)
	{
		x = std::min(std::max(x, rMin.x), rMax.x);
		y = std::min(std::max(y, rMin.y), rMax.y);
		z = std::min(std::max(z, rMin.z), rMax.z);
	}

} gt2Vector3, *LPMC_VECTOR3;
const gt2Vector3 g_VF3IdentityR0 = gt2Vector3(1, 0, 0);
const gt2Vector3 g_VF3IdentityR1 = gt2Vector3(0, 1, 0);
const gt2Vector3 g_VF3IdentityR2 = gt2Vector3(0, 0, 1);

#define MCVectorF3_CAST_P(_p) \
(reinterpret_cast<gt2Vector3*>(&_p))
#define MCVectorF3_CAST(_p) \
(*(reinterpret_cast<gt2Vector3*>(&_p)))








/*!
* @brief 4�v�f(x,y,z,w) �x�N�g��
*/
typedef struct gt2Vector4
{
public:
	union {
		struct {
			float x;	//!< �v�f x
			float y;	//!< �v�f y
			float z;	//!< �v�f z
			float w;	//!< �v�f w
		};
		float v[4];		//!< v[0] = x, v[1] = y, v[2] = z, v[3] = w
	};
public:
	/*!
	* @brief �R���X�g���N�^
	*  x,y,z,w���O�ŏ����������
	*/
	gt2Vector4() { this->Init(); }
	/*!
	* @brief �R���X�g���N�^
	*   x,y,z,w��pf�|�C���^�̒l�ɂ�菉���������
	* @param [in] pf     4�v�f�ȏ��float��񂪂���|�C���^
	*/
	gt2Vector4(const float * pF) { x = pF[0]; y = pF[1]; z = pF[2]; w = pF[3]; }
	/*!
	* @brief �R���X�g���N�^
	*  rV�ŏ����������
	* @param [in] rV     �x�N�g��
	*/
	gt2Vector4(const gt2Vector4& rV) { *this = rV; }
	/*!
	* @brief �R���X�g���N�^
	*   x=fx,y=fy,z=fz,w=fw �Ƃ����������ɏ����������
	* @param [in] fx     x�l
	* @param [in] fy     y�l
	* @param [in] fz     y�l
	* @param [in] fw     w�l
	*/
	gt2Vector4(float fx, float fy, float fz, float fw) { x = fx; y = fy; z = fz; w = fw; }


#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
	gt2Vector4&   operator= (const DirectX::XMFLOAT2& vf) { x = vf.x; y = vf.y; return *this; }
	gt2Vector4&   operator= (const DirectX::XMFLOAT3& vf) { x = vf.x; y = vf.y; z = vf.z; return *this; }
	gt2Vector4&   operator= (const DirectX::XMFLOAT4& vf) { x = vf.x; y = vf.y; z = vf.z; w = vf.w; return *this; }
	gt2Vector4&   operator= (const DirectX::XMVECTOR& vf) { x = vf.m128_f32[0]; y = vf.m128_f32[1]; z = vf.m128_f32[2]; w = vf.m128_f32[3]; return *this; }

	DirectX::XMFLOAT2 GetXMFLOAT2() const { DirectX::XMFLOAT2 t; t.x = x; t.y = y; return t; }
	DirectX::XMFLOAT3 GetXMFLOAT3() const { DirectX::XMFLOAT3 t; t.x = x; t.y = y; t.z = z; return t; }
	DirectX::XMFLOAT4 GetXMFLOAT4() const { DirectX::XMFLOAT4 t; t.x = x; t.y = y; t.z = z; t.w = w; return t; }
	DirectX::XMVECTOR GetXMVECTOR() const { DirectX::XMVECTOR tmp; memcpy(&tmp, this, sizeof(gt2Vector4)); return tmp; }

#endif
	/*!
	* @brief x,y,z,w�̒l���O�ŏ����������
	* @return �Ȃ�
	*/
	inline void Init() { x = y = z = w = 0; }
	/*!
	* @brief x,y,z,w�̒l��float�^�̍ŏ��l��FLT_MAX�ŏ����������
	* @return �Ȃ�
	*/
	inline void InitMin() { x = y = z = w = FLT_MAX; }
	/*!
	* @brief x,y,z,w�̒l��float�^�̍ŏ��l��FLT_MAX�ŏ����������
	* @return �Ȃ�
	*/
	inline void InitMax() { x = y = z = w = -FLT_MAX; }

	/**
	* @param [in] fx     x�l
	* @param [in] fy     y�l
	* @param [in] fz     z�l
	* @param [in] fw     w�l
	*/
	inline void Set(float fx, float fy, float fz, float fw) { x = fx; y = fy; z = fz; w = fw; }

	//------------------------------------------------------------------------
	//
	// ������Z�q
	//
	//------------------------------------------------------------------------
	/*!
	* @brief ������Z�q =
	*   �ʏ�̑��
	* @param [in] v     �E�ӂ̃x�N�g��gt2Vector4
	* @return ���Z���ꂽ�x�N�g���l��Ԃ�
	*/
	inline gt2Vector4& operator = (const gt2Vector4& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
		return *this;
	}
	/*!
	* @brief ������Z�q =
	*   ���g(this)�̃x�N�g���l�։E�ӂ�2�v�f�̃x�N�g����������Bz�͏�ɂO�B
	* @param [in] rV     �E�ӂ�2�v�f�x�N�g��
	* @return ������ꂽ2�v�f�̃x�N�g��������3�v�f�̃x�N�g����Ԃ��B
	*/
	inline gt2Vector4& operator = (const gt2Vector2& rV)
	{
		x = rV.x;
		y = rV.y;
		z = w = 0.0f;

		return *this;
	}
	/*!
	* @brief ������Z�q =
	*   ���g(this)�̃x�N�g���l�։E�ӂ�2�v�f�̃x�N�g����������Bz�͏�ɂO�B
	* @param [in] rV     �E�ӂ�3�v�f�x�N�g��
	* @return ������ꂽ2�v�f�̃x�N�g��������3�v�f�̃x�N�g����Ԃ��B
	*/
	inline gt2Vector4& operator = (const gt2Vector3& rV)
	{
		x = rV.x;
		y = rV.y;
		z = rV.z;
		w = 0.0f;

		return *this;
	}
	/*!
	* @brief ������Z�q +=
	*   ���g(this)�̃x�N�g���l���E�ӂ̃x�N�g���l�����Z�����l�����g(this)�ɃZ�b�g����
	* @param [in] rV     �E�ӂ̃x�N�g��gt2Vector4
	* @return ���Z���ꂽ�x�N�g���l��Ԃ�
	*/
	inline gt2Vector4& operator += (const gt2Vector4& rV)
	{
		x += rV.x;
		y += rV.y;
		z += rV.z;
		w += rV.w;

		return *this;
	}
	/*!
	* @brief ������Z�q -=
	*   ���g(this)�̃x�N�g���l���E�ӂ̃x�N�g���l�����Z�����l�����g(this)�ɃZ�b�g����
	* @param [in] rV     �E�ӂ̃x�N�g��gt2Vector3
	* @return ���Z���ꂽ�x�N�g���l��Ԃ�
	*/
	inline gt2Vector4& operator -= (const gt2Vector4& rV)
	{
		x -= rV.x;
		y -= rV.y;
		z -= rV.z;
		w -= rV.w;

		return *this;
	}
	/*!
	* @brief ������Z�q *=
	*   ���g(this)�̃x�N�g���l���E�ӂ̂P�̒l����Z�����l�����g(this)�ɃZ�b�g����
	* @param [in] f     �E�ӂ�1�̒l
	* @return ��Z���ꂽ�x�N�g���l��Ԃ�
	*/
	inline gt2Vector4& operator *= (float f)
	{
		x *= f;
		y *= f;
		z *= f;
		w *= f;

		return *this;
	}
	/*!
	* @brief ������Z�q *=
	*   ���g(this)�̃x�N�g���l���E�ӂ̂P�̒l�����Z�����l�����g(this)�ɃZ�b�g����
	* @param [in] f     �E�ӂ�1�̒l
	* @return ���Z���ꂽ�x�N�g���l��Ԃ�
	*/
	inline gt2Vector4& operator /= (float f)
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
	* @return ���̂܂܂̃x�N�g���l��Ԃ�
	*/
	inline gt2Vector4 operator + () const
	{
		return *this;
	}
	/*!
	* @brief �P�����Z�q -
	*   �e�v�f��-1����Z�����x�N�g���l�ɂȂ�
	* @return �e�v�f��-1����Z�����x�N�g���l��Ԃ�
	*/
	inline gt2Vector4 operator - () const
	{
		return gt2Vector4(-x, -y, -z, -w);
	}


	//##################################################################
	//##
	//## ��P�����Z�q
	//##
	//##################################################################
	/*!
	* @brief �񍀉��Z�q +
	*   ���g(this)�̃x�N�g����"rV"�x�N�g�������Z����
	* @param [in] rV     gt2Vector4
	* @return ���g(this)�̃x�N�g����"rV"�x�N�g���l�����Z�����l��Ԃ�
	*/
	inline gt2Vector4 operator + (const gt2Vector4& rV) const
	{
		gt2Vector4 vTmp;

		vTmp.x = x + rV.x;
		vTmp.y = y + rV.y;
		vTmp.z = z + rV.z;
		vTmp.w = w + rV.w;

		return vTmp;
	}
	/*!
	* @brief �񍀉��Z�q +
	*   ���g(this)�̃x�N�g���̗v�f����"f"�̒l�����Z����
	* @param [in] f     1�̒l
	* @return ���g(this)�̃x�N�g���̗v�f����"f"�̒l�����Z�����l��Ԃ�
	*/
	inline gt2Vector4 operator + (float f) const
	{
		gt2Vector4 vTmp;

		vTmp.x = x + f;
		vTmp.y = y + f;
		vTmp.z = z + f;
		vTmp.w = w + f;

		return vTmp;
	}
	/*!
	* @brief �񍀉��Z�q -
	*   ���g(this)�̃x�N�g����"rV"�x�N�g�������Z����
	* @param [in] rV     gt2Vector4
	* @return ���g(this)�̃x�N�g����"rV"�x�N�g���l�����Z�����l��Ԃ�
	*/
	inline gt2Vector4 operator - (const gt2Vector4& rV) const
	{
		gt2Vector4 vTmp;

		vTmp.x = x - rV.x;
		vTmp.y = y - rV.y;
		vTmp.z = z - rV.z;
		vTmp.w = w - rV.w;

		return vTmp;
	}
	/*!
	* @brief �񍀉��Z�q -
	*   ���g(this)�̃x�N�g���̗v�f����"f"�̒l�����Z����
	* @param [in] f     1�̒l
	* @return ���g(this)�̃x�N�g���̗v�f����"f"�̒l�����Z�����l��Ԃ�
	*/
	inline gt2Vector4 operator - (float f) const
	{
		gt2Vector4 vTmp;

		vTmp.x = x - f;
		vTmp.y = y - f;
		vTmp.z = z - f;
		vTmp.w = w - f;

		return vTmp;
	}
	/*!
	* @brief �񍀉��Z�q *
	*   ���g(this)�̃x�N�g���̗v�f����"f"�̒l����Z����
	* @param [in] f     1�̒l
	* @return ���g(this)�̃x�N�g���̗v�f����"f"�̒l����Z�����l��Ԃ�
	*/
	inline gt2Vector4 operator * (float f) const
	{
		gt2Vector4 vTmp;

		vTmp.x = x * f;
		vTmp.y = y * f;
		vTmp.z = z * f;
		vTmp.w = w * f;

		return vTmp;
	}
	/*!
	* @brief �񍀉��Z�q /
	*   ���g(this)�̃x�N�g���̗v�f����"f"�̒l�����Z����
	* @param [in] f     1�̒l
	* @return ���g(this)�̃x�N�g���̗v�f����"f"�̒l�����Z�����l��Ԃ�
	*/
	inline gt2Vector4 operator / (float f) const
	{
		gt2Vector4 vTmp;

		vTmp.x = x / f;
		vTmp.y = y / f;
		vTmp.z = z / f;
		vTmp.w = w / f;

		return vTmp;
	}
	/*!
	* @brief �񍀉��Z�q /
	*   ���g(this)�̃x�N�g����"rV"�x�N�g���̗v�f���Ə��Z����
	* @param [in] rV     gt2Vector2
	* @return ���g(this)�̃x�N�g����"rV"�x�N�g���̗v�f���Ə��Z�����l��Ԃ�
	*/
	inline gt2Vector4 operator / (const gt2Vector4& rV) const
	{
		gt2Vector4 vTmp;

		vTmp.x = x / rV.x;
		vTmp.y = y / rV.y;
		vTmp.z = z / rV.z;
		vTmp.w = w / rV.w;

		return vTmp;
	}
	friend inline gt2Vector4 operator * (float f, const gt2Vector4& rV)
	{
		return rV * f;
	}
	/*!
	* @brief �񍀉��Z�q *
	*   ���g(this)�̃x�N�g����"rV"�x�N�g���̗v�f���Ə�Z����
	* @param [in] rV     gt2Vector3
	* @return ���g(this)�̃x�N�g����"rV"�x�N�g���̗v�f���Ə�Z�����l��Ԃ�
	*/
	inline gt2Vector4 operator * (const gt2Vector4& rV) const
	{
		gt2Vector4 vTmp;

		vTmp.x = x * rV.x;
		vTmp.y = y * rV.y;
		vTmp.z = z * rV.z;
		vTmp.w = w * rV.w;

		return vTmp;
	}



	//##################################################################
	//##
	//## ��r���Z�q
	//##
	//##################################################################
	/*!
	* @brief ��r���Z�q ==
	*   ���g(this)�̃x�N�g����"rV"�x�N�g���̊e�v�f����������r����
	* @param [in] rV     gt2Vector4
	* @return ���g(this)�̃x�N�g����"rV"�x�N�g���̊e�v�f���r���A����Ȃ�true��Ԃ��B
	*/
	inline bool operator == (const gt2Vector4& rV) const
	{
		return x == rV.x && y == rV.y && z == rV.z && w == rV.w;
	}
	/*!
	* @brief ��r���Z�q !=
	*   ���g(this)�̃x�N�g����"rV"�x�N�g���̊e�v�f���Ⴄ����r����
	* @param [in] rV     gt2Vector4
	* @return ���g(this)�̃x�N�g����"rV"�x�N�g���̊e�v�f���r���A�Ⴄ�ꍇtrue��Ԃ��B
	*/
	inline bool operator != (const gt2Vector4& rV) const
	{
		return !(*this == rV);
	}



	//##################################################################
	//##
	//## 
	//##
	//##################################################################
	/*!
	* @brief  gt2Vector2�̒l��Ԃ��B
	* @return  gt2Vector2
	*/
	inline gt2Vector2 GetV2() const { return gt2Vector2(x, y); }
	/*!
	* @brief  gt2Vector3�̒l��Ԃ��B
	* @return  gt2Vector3
	*/
	inline gt2Vector3 GetV3() const { return gt2Vector3(x, y, z); }

	/*!
	* @brief  x,y,z,w �̒l�Ɠ����̒l�Ɣ�r���A�傫���l�����ꂼ��Z�b�g����
	* @param [in]  rV  �x�N�g��
	* @return  �Ȃ�
	*/
	inline void SetMax(const gt2Vector4& rV)
	{
		this->SetMax(rV.x, rV.y, rV.z, rV.w);
	}
	/*!
	* @brief  x,y,z,w �̒l�Ɠ����̒l�Ɣ�r���A�傫���l�����ꂼ��Z�b�g����
	* @param [in]  fx  �v�f x
	* @param [in]  fy  �v�f y
	* @param [in]  fz  �v�f z
	* @param [in]  fw  �v�f w
	* @return  �Ȃ�
	*/
	inline void SetMax(float fx, float fy, float fz, float fw)
	{
		x = x>fx ? x : fx;
		y = y>fy ? y : fy;
		z = z>fz ? z : fz;
		w = w>fw ? w : fw;
	}
	/*!
	* @brief   ���g��x,y,z,w �̒l���������l�̌ܓ�����
	* @return   �Ȃ�
	*/
	inline void MyRound()
	{
		x = floor(x + 0.5f);
		y = floor(y + 0.5f);
		z = floor(z + 0.5f);
		w = floor(w + 0.5f);
	}
	/*!
	* @brief   ���g��x,y,z,w �̒l�̏�����؂�̂�
	* @return   �Ȃ�
	*/
	inline void MyFloor()
	{
		x = floor(x);
		y = floor(y);
		z = floor(z);
		w = floor(w);
	}
	/*!
	* @brief   ���g��x,y,z,w�̂��ꂼ����p�x���烉�W�A���l��
	* @return   �Ȃ�
	*/
	inline void ToRadianFromAngle()
	{
		x *= GT2_RADIAN;
		y *= GT2_RADIAN;
		z *= GT2_RADIAN;
		w *= GT2_RADIAN;
	}
	/*!
	* @brief   ���g��x,y,z,w�̂��ꂼ������W�A������p�x�l��
	* @return   �Ȃ�
	*/
	inline void ToAngleFromRadian()
	{
		x *= GT2_INV_RADIAN;
		y *= GT2_INV_RADIAN;
		z *= GT2_INV_RADIAN;
		w *= GT2_INV_RADIAN;
	}

	/*!
	* @brief  x,y,z,w �̒l�Ɠ����̒l�Ɣ�r���A�������l�����ꂼ��Z�b�g����
	* @param [in]  rV  �x�N�g��
	* @return  �Ȃ�
	*/
	inline void SetMin(const gt2Vector4& rV)
	{
		this->SetMin(rV.x, rV.y, rV.z, rV.w);
	}
	/*!
	* @brief  x,y,z,w �̒l�Ɠ����̒l�Ɣ�r���A�������l�����ꂼ��Z�b�g����
	* @param [in]  fx  �v�f x
	* @param [in]  fy  �v�f y
	* @param [in]  fz  �v�f z
	* @param [in]  fw  �v�f w
	* @return  �Ȃ�
	*/
	inline void SetMin(float fx, float fy, float fz, float fw)
	{
		x = x<fx ? x : fx;
		y = y<fy ? y : fy;
		z = z<fz ? z : fz;
		w = w<fw ? w : fw;
	}
	/*!
	* @brief �p�x(0�`360)���烉�W�A���l�ɕϊ�����x,y,z�ɑ������
	* @param [in] fx     �p�x(0�`360)
	* @param [in] fy     �p�x(0�`360)
	* @param [in] fz     �p�x(0�`360)
	* @param [in] fw     �p�x(0�`360)
	* @return �Ȃ�
	*/
	inline void MakeRadianToDegrees(float fx, float fy, float fz, float fw)
	{
		x = GT2_INV_RADIAN * fx;
		y = GT2_INV_RADIAN * fy;
		z = GT2_INV_RADIAN * fz;
		w = GT2_INV_RADIAN * fw;
	}
	/*!
	* @brief �x�N�g���̒�����Ԃ��B
	* @return �x�N�g���̒�����Ԃ��B
	*/
	inline float Length() const
	{
		return sqrt(x*x + y*y + z*z + w*w);
	}
	/*!
	* @brief �x�N�g���̒����� 2 ���Ԃ��B
	* @return �x�N�g���̒����� 2 ���Ԃ��B
	*/
	inline float LengthSq() const
	{
		return x*x + y*y + z*z + w*w;
	}
	/*!
	* @brief ����
	*   �x�N�g���̓��ς����߂܂��B
	* @return  ���ς�Ԃ��B
	*/
	inline float Dot() const
	{
		return x*x + y*y + z*z;
	}
	/*!
	* @brief ����
	*   ���g(this)�̃x�N�g����"rV"�x�N�g������ς���
	* @param [in] rV     �Ώۃx�N�g��
	* @return  ���ς�Ԃ��B
	*/
	inline float Dot(const gt2Vector4& rV3) const
	{
		return x*rV3.x + y*rV3.y + z*rV3.z + w*rV3.w;
	}
	/*!
	* @brief �O��
	*   v = rV1 �~ rV2 �~ rV3
	* @param [in] rV1     1�߂̑Ώۃx�N�g��
	* @param [in] rV2     2�߂̑Ώۃx�N�g��
	* @param [in] rV3     3�߂̑Ώۃx�N�g��
	* @return  �O�ς����x�N�g����Ԃ��B
	*/
	inline static gt2Vector4 Cross(const gt2Vector4& rV1, const gt2Vector4& rV2, const gt2Vector4& rV3)
	{
		return gt2Vector4(
			rV1.z*rV2.y*rV3.w - rV1.y*rV2.z*rV3.w - rV1.z*rV2.w*rV3.y + rV1.w*rV2.z*rV3.y + rV1.y*rV2.w*rV3.z - rV1.w*rV2.y*rV3.z,
			-rV1.z*rV2.x*rV3.w + rV1.x*rV2.z*rV3.w + rV1.z*rV2.w*rV3.x - rV1.w*rV2.z*rV3.x - rV1.x*rV2.w*rV3.z + rV1.w*rV2.x*rV3.z,
			rV1.y*rV2.x*rV3.w - rV1.x*rV2.y*rV3.w - rV1.y*rV2.w*rV3.x + rV1.w*rV2.y*rV3.x + rV1.x*rV2.w*rV3.y - rV1.w*rV2.x*rV3.y,
			-rV1.z*rV2.y*rV3.x + rV1.y*rV2.z*rV3.x + rV1.z*rV2.x*rV3.y - rV1.x*rV2.z*rV3.y - rV1.y*rV2.x*rV3.z + rV1.x*rV2.y*rV3.z
		);
	}
	/*!
	* @brief �O��
	*   v = *this �~ rV2 �~ rV3
	*  1�߂̃x�N�g���͎��M(this)�ł��B
	* @param [in] rV2     2�߂̑Ώۃx�N�g��
	* @param [in] rV3     3�߂̑Ώۃx�N�g��
	* @return  �O�ς����x�N�g����Ԃ��B
	*/
	inline gt2Vector4 Cross(const gt2Vector4& rV2, const gt2Vector4& rV3) const
	{
		return gt2Vector4::Cross(*this, rV2, rV3);
	}
	/*!
	* @brief �x�N�g���̉��Z
	*   ���g(this)�̃x�N�g����"rV"�x�N�g�������Z����B
	* @param [in] rV     ���� gt2Vector2 �\����
	* @return  ���Z���ꂽ�x�N�g����Ԃ��B
	*/
	inline gt2Vector4 Add(const gt2Vector4& rV) const
	{
		return gt2Vector4(
			x + rV.x,
			y + rV.y,
			z + rV.z,
			w + rV.w
		);
	}
	/*!
	* @brief �x�N�g���̌��Z
	*   ���g(this)�̃x�N�g����"rV"�x�N�g�������Z����B
	* @param [in] rV     ���� gt2Vector4 �\����
	* @return  ���Z���ꂽ�x�N�g����Ԃ��B
	*/
	inline gt2Vector4 Subtract(const gt2Vector4& rV) const
	{
		return gt2Vector4(
			x - rV.x,
			y - rV.y,
			z - rV.z,
			w - rV.w
		);
	}
	/*!
	* @brief 2�̃x�N�g���̗v�f���r���ŏ��l�̗v�f�̃x�N�g����Ԃ�
	* @param [in] rV     ���� gt2Vector4 �\����
	* @return  �ŏ��l�̗v�f�̃x�N�g����Ԃ�
	*/
	inline gt2Vector4 Minimize(const gt2Vector4& rV) const
	{
		return gt2Vector4(
			x < rV.x ? x : rV.x,
			y < rV.y ? y : rV.y,
			z < rV.z ? z : rV.z,
			w < rV.w ? w : rV.w);
	}
	/*!
	* @brief 2�̃x�N�g���̗v�f���r���ő�l�̗v�f�̃x�N�g�����擾����
	* @param [in] rV     ���� gt2Vector4 �\����
	* @return  �ő�l�̗v�f�̃x�N�g����Ԃ�
	*/
	inline gt2Vector4 Maximize(const gt2Vector4& rV) const
	{
		return gt2Vector4(
			x > rV.x ? x : rV.x,
			y > rV.y ? y : rV.y,
			z > rV.z ? z : rV.z,
			w > rV.w ? w : rV.w);
	}
	/*!
	* @brief �x�N�g�����X�P�[�����O����B
	* @param [in]  s      �X�P�[�����O�l�B
	* @return  �x�N�g�����X�P�[�����O�������̂�Ԃ��B
	*/
	inline gt2Vector4 Scale(float s) const
	{
		return gt2Vector4(x * s, y * s, z * s, w * s);
	}
	/*!
	* @brief �x�N�g���Ԃ̐��`��Ԃ����s����B
	* @param [in]  rV1   �� 1 �Ԗڂ̃x�N�g��
	* @param [in]  rV2   �� 2 �Ԗڂ̃x�N�g��
	* @param [in]  t     �x�N�g���Ԃ���`��Ԃ���p�����[�^�B
	* @return  ���`��Ԃ��ꂽ�x�N�g����Ԃ��B
	*/
	inline static gt2Vector4 Lerp(const gt2Vector4& rV1, const gt2Vector4& rV2, float t)
	{
		return gt2Vector4(
			rV1.x + t * (rV2.x - rV1.x),
			rV1.y + t * (rV2.y - rV1.y),
			rV1.z + t * (rV2.z - rV1.z),
			rV1.w + t * (rV2.w - rV1.w)
		);
	}
	/*!
	* @brief �x�N�g���Ԃ̐��`��Ԃ����s����B
	*   �� 1 �Ԗڂ̃x�N�g�����A���g(this)�ł��B
	* @param [in]  rV2   �� 2 �Ԗڂ̃x�N�g��
	* @param [in]  t     �x�N�g���Ԃ���`��Ԃ���p�����[�^�B
	* @return  ���`��Ԃ��ꂽ�x�N�g����Ԃ��B
	*/
	inline gt2Vector4 Lerp(const gt2Vector4& rV2, float t) const
	{
		return gt2Vector4::Lerp(*this, rV2, t);
	}
	/*!
	* @brief 0 �� t �� 1 �̊ԂŃG���~�[�g��Ԃɂ�銊�炩�ȕ�Ԃ��s���܂��B
	* @param [in]  rV1  1 �Ԗڂ̃x�N�g���B
	* @param [in]  rV2  2 �Ԗڂ̃x�N�g���B
	* @param [in]  t   �x�N�g���Ԃ���`��Ԃ���p�����[�^�B�͈�[0�`1.0]
	* @return  ��Ԃ��ꂽ�x�N�g����Ԃ��B
	*/
	inline static gt2Vector4 SmoothStep(const gt2Vector4& rV1, const gt2Vector4& rV2, float t)
	{
		t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
		t = t*t*(3.f - 2.f*t);
		return gt2Vector4::Lerp(rV1, rV2, t);
	}
	/*!
	* @brief 0 �� t �� 1 �̊ԂŃG���~�[�g��Ԃɂ�銊�炩�ȕ�Ԃ��s���܂��B
	*   �� 1 �Ԗڂ̃x�N�g�����A���g(this)�ł��B
	* @param [in]  rV  2 �Ԗڂ̃x�N�g���B
	* @param [in]  t   �x�N�g���Ԃ���`��Ԃ���p�����[�^�B�͈�[0�`1.0]
	* @return  ��Ԃ��ꂽ�x�N�g����Ԃ��B
	*/
	inline gt2Vector4 SmoothStep(const gt2Vector4& rV2, float t) const
	{
		return gt2Vector4::SmoothStep(*this, rV2, t);
	}
	/*!
	* @brief �w�肳�ꂽ�ʒu�x�N�g�����g�p���āA�d�S���W�̃|�C���g��Ԃ��܂��B
	* @param [in]  rV1  �� 1 �̈ʒu
	* @param [in]  rV2  �� 2 �̈ʒu
	* @param [in]  rV3  �� 3 �̈ʒu
	* @param [in]  f    ���d�W���B
	* @param [in]  g    ���d�W���B
	* @return  �d�S���W��Ԃ��܂��B
	*/
	inline static gt2Vector4 Barycentric(const gt2Vector4& rV1, const gt2Vector4& rV2, const gt2Vector4& rV3, float f, float g)
	{
		return rV1 + f * (rV2 - rV1) + g * (rV3 - rV1);
	}
	/*!
	* @brief �w�肳�ꂽ�ʒu�x�N�g�����g�p���āA�d�S���W�̃|�C���g��Ԃ��܂��B
	*   �� 1 �̈ʒu���A���g(this)�ł��B
	* @param [in]  rV2  �� 2 �̈ʒu
	* @param [in]  rV3  �� 3 �̈ʒu
	* @param [in]  f    ���d�W���B
	* @param [in]  g    ���d�W���B
	* @return  �d�S���W��Ԃ��܂��B
	*/
	inline gt2Vector4 Barycentric(const gt2Vector4& rV2, const gt2Vector4& rV3, float f, float g) const
	{
		return gt2Vector4::Barycentric(*this, rV2, rV3, f, g);
	}
	/*!
	* @brief �w�肳�ꂽ�ʒu�x�N�g�����g�p���āACatmull-Rom ��Ԃ��s���܂��B
	* @param [in]  rV1  �� 1 �̈ʒu
	* @param [in]  rV2  �� 2 �̈ʒu
	* @param [in]  rV3  �� 3 �̈ʒu
	* @param [in]  rV4  �� 3 �̈ʒu
	* @param [in]  t    ��Ԑ���W��
	* @return  Catmull-Rom ��Ԃ̌��ʂ�Ԃ��܂��B
	*/
	inline static gt2Vector4 CatmullRom(const gt2Vector4& rV1, const gt2Vector4& rV2, const gt2Vector4& rV3, const gt2Vector4& rV4, float t)
	{
		float t2 = t * t;
		float t3 = t * t2;
		return ((-t3 + 2 * t2 - t) * rV1 +
			(3 * t3 - 5 * t2 + 2) * rV2 +
			(-3 * t3 + 4 * t2 + t) * rV3 +
			(t3 - t2) * rV4) * 0.5f;
	}
	/*!
	* @brief �w�肳�ꂽ�ʒu�x�N�g�����g�p���āACatmull-Rom ��Ԃ��s���܂��B
	*   �� 1 �̈ʒu���A���g(this)�ł��B
	* @param [in]  rV2  �� 2 �̈ʒu
	* @param [in]  rV3  �� 3 �̈ʒu
	* @param [in]  rV4  �� 3 �̈ʒu
	* @param [in]  t    ��Ԑ���W��
	* @return  Catmull-Rom ��Ԃ̌��ʂ�Ԃ��܂��B
	*/
	inline gt2Vector4 CatmullRom(const gt2Vector4& rV2, const gt2Vector4& rV3, const gt2Vector4& rV4, float t) const
	{
		return gt2Vector4::CatmullRom(*this, rV2, rV3, rV4, t);
	}
	/*!
	* @brief �w�肳�ꂽ�x�N�g�����g�p���āA�G���~�[�g �X�v���C����Ԃ����s���܂��B
	* @param [in]  rV1  ��Ԃ��s����� 1 �̈ʒu
	* @param [in]  rT1  �� 1 �̈ʒu�̐ڐ��x�N�g��
	* @param [in]  rV2  ��Ԃ��s����� 2 �̈ʒu
	* @param [in]  rT2  �� 2 �̈ʒu�̐ڐ��x�N�g��
	* @param [in]  t    ��Ԑ���W��
	* @return  ��Ԃ��܂܂ꂽ�x�N�g����Ԃ��܂��B
	*/
	inline static gt2Vector4 Hermite(const gt2Vector4& rV1, const gt2Vector4& rT1, const gt2Vector4& rV2, const gt2Vector4& rT2, float t)
	{
		float t2 = t * t;
		float t3 = t * t2;
		return (2 * t3 - 3 * t2 + 1) * rV1 +
			(t3 - 2 * t2 + t) * rT1 +
			(-2 * t3 + 3 * t2) * rV2 +
			(t3 - t2) * rT2;
	}
	/*!
	* @brief �w�肳�ꂽ�x�N�g�����g�p���āA�G���~�[�g �X�v���C����Ԃ����s���܂��B
	*   �� 1 �̈ʒu���A���g(this)�ł��B
	* @param [in]  rT1  �� 1 �̈ʒu�̐ڐ��x�N�g��
	* @param [in]  rV2  ��Ԃ��s����� 2 �̈ʒu
	* @param [in]  rT2  �� 2 �̈ʒu�̐ڐ��x�N�g��
	* @param [in]  t    ��Ԑ���W��
	* @return  ��Ԃ��܂܂ꂽ�x�N�g����Ԃ��܂��B
	*/
	inline gt2Vector4 Hermite(const gt2Vector4& rT1, const gt2Vector4& rV2, const gt2Vector4& rT2, float t) const
	{
		return gt2Vector4::Hermite(*this, rT1, rV2, rT2, t);
	}
	/*!
	* @brief 4D �@���x�N�g���ɂ���� 4D ���˃x�N�g���𔽎˂��܂��B
	* @param [in]  rvIncident  ���˂���� 4D ���˃x�N�g��
	* @param [in]  rvNormal    ���˃x�N�g���𔽎˂��� 4D �@���x�N�g��
	* @return  ���ˌ�̓��ˊp��Ԃ��܂��B
	*/
	inline static gt2Vector4 Refract(const gt2Vector4& rvIncident, const gt2Vector4& rvNormal)
	{
		return rvIncident - (2 * rvIncident.Dot(rvNormal)) * rvNormal;
	}
	/*!
	* @brief 4D �@���x�N�g���ɂ���� 4D ���˃x�N�g���𔽎˂��܂��B
	*   ���˂���� 4D ���˃x�N�g�����A���g(this)�ł��B
	* @param [in]  rvNormal    ���˃x�N�g���𔽎˂��� 4D �@���x�N�g��
	* @return  ���ˌ�̓��ˊp��Ԃ��܂��B
	*/
	inline gt2Vector4 Refract(const gt2Vector4& rvNormal) const
	{
		return gt2Vector4::Refract(*this, rvNormal);
	}
	/*!
	* @brief 4D �@���x�N�g���ɂ���� 4D ���˃x�N�g���𔽎˂��܂��B
	* @param [in]  rvIncident      ���˂���� 4D ���˃x�N�g��
	* @param [in]  rvNormal        ���˃x�N�g���𔽎˂��� 4D �@���x�N�g��
	* @param [in]  refractionIndex ���ܗ��B
	* @return  ���܂��ꂽ���˃x�N�g����Ԃ��܂��B���ܗ��A����ѓ��˃x�N�g���Ɩ@���x�N�g���Ԃ̊p�x�ɂ���āA
	*          ���ʂ��S���˂ɂȂ����ꍇ�́A< 0.0f, 0.0f, 0.0f, 0.0f > �Ƃ����`�̃x�N�g�����Ԃ���܂��B
	*/
	inline static gt2Vector4 Refract(const gt2Vector4& rvIncident, const gt2Vector4& rvNormal, float refractionIndex)
	{
		gt2Vector4 Result;
		float t = rvIncident.Dot(rvNormal);

		float r = 1.0f - refractionIndex * refractionIndex * (1.0f - t * t);
		if (r < 0.0f) // �S����
		{
			Result.x = 0.0f;
			Result.y = 0.0f;
			Result.z = 0.0f;
			Result.w = 0.0f;
		}
		else {
			float s = refractionIndex * t + sqrtf(r);
			Result.x = refractionIndex * rvIncident.x - s * rvNormal.x;
			Result.y = refractionIndex * rvIncident.y - s * rvNormal.y;
			Result.z = refractionIndex * rvIncident.z - s * rvNormal.z;
			Result.w = refractionIndex * rvIncident.w - s * rvNormal.w;
		}
		return Result;
	}
	/*!
	* @brief 4D �@���x�N�g���ɂ���� 4D ���˃x�N�g���𔽎˂��܂��B
	*   ���˂���� 4D ���˃x�N�g�����A���g(this)�ł��B
	* @param [in]  rvNormal        ���˃x�N�g���𔽎˂��� 4D �@���x�N�g��
	* @param [in]  refractionIndex ���ܗ��B
	* @return  ���܂��ꂽ���˃x�N�g����Ԃ��܂��B���ܗ��A����ѓ��˃x�N�g���Ɩ@���x�N�g���Ԃ̊p�x�ɂ���āA
	*          ���ʂ��S���˂ɂȂ����ꍇ�́A< 0.0f, 0.0f, 0.0f > �Ƃ����`�̃x�N�g�����Ԃ���܂��B
	*/
	inline gt2Vector4 Refract(const gt2Vector4& rvNormal, float refractionIndex) const
	{
		return gt2Vector4::Refract(*this, rvNormal, refractionIndex);
	}

	/*!
	* @brief l�̒������x�N�g���̒����ƂŊ������l���A�x�N�g���̊e�v�f�ɏ�Z�����l���Z�b�g����
	* @param [in]  rV  �^���x�N�g��
	* @param [in]  l   ����
	* @return  �Ȃ�
	*/
	inline void SetMakeLength(const gt2Vector4& rV, float fL) {
		float fLen = rV.Length();
		x = rV.x * fL / fLen;
		y = rV.y * fL / fLen;
		z = rV.z * fL / fLen;
		w = rV.w * fL / fLen;
	}
	/*!
	* @brief ���g(this)�̃x�N�g���𐳋K������B
	* @return  �Ȃ�
	*/
	inline void Normalize()
	{
		gt2Vector4 vTmp;

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
	* @brief �x�N�g���𐳋K�������x�N�g����Ԃ��܂��B
	* @param [out] pOut     ���Z���ʂł��� gt2Vector3 �\���̂ւ̃|�C���^�B
	* @return  �x�N�g���𐳋K�������x�N�g����Ԃ��B
	*/
	inline gt2Vector4* Normalize(gt2Vector4* pOut) const
	{
		gt2Vector4 vTmp;

		float fL = this->Length();
		if (fL == 0.0f) {
			*pOut = gt2Vector4(0.0f, 0.0f, 0.0f, 0.0f);
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
	* @brief �x�N�g���𐳋K�������x�N�g����Ԃ��B
	* @param [out] rOut     ���Z���ʂł��� gt2Vector3�B
	* @return  �Ȃ�
	*/
	inline void Normalize(gt2Vector4& rOut) const
	{
		this->Normalize(&rOut);
	}
	/*!
	* @brief �x�N�g���̗v�f���A�w�肳�ꂽ�ő�l�ƍŏ��l�͈̔͂ɃN�����v���܂��B
	* @param [in] rMin     �ŏ��͈̓x�N�g��
	* @param [in] rMax     �ő�͈̓x�N�g��
	* @return  �Ȃ�
	*/
	void Clamp(const gt2Vector4& rMin, const gt2Vector4& rMax)
	{
		x = std::min(std::max(x, rMin.x), rMax.x);
		y = std::min(std::max(y, rMin.y), rMax.y);
		z = std::min(std::max(z, rMin.z), rMax.z);
		w = std::min(std::max(w, rMin.w), rMax.w);
	}
} gt2Vector4, *LPMCVECTOR4;
const gt2Vector4 g_VF4IdentityR0 = gt2Vector4(1, 0, 0, 0);
const gt2Vector4 g_VF4IdentityR1 = gt2Vector4(0, 1, 0, 0);
const gt2Vector4 g_VF4IdentityR2 = gt2Vector4(0, 0, 1, 0);
const gt2Vector4 g_VF4IdentityR3 = gt2Vector4(0, 0, 0, 1);

// �G���[�p
const gt2Vector2 g_VectorF2_NaN = gt2Vector2(NAN, NAN);
const gt2Vector3 g_VectorF3_NaN = gt2Vector3(NAN, NAN, NAN);
const gt2Vector4 g_VectorF4_NaN = gt2Vector4(NAN, NAN, NAN, NAN);
