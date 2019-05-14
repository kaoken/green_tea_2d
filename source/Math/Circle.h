/*! @file  Circle.h
* @brief �QD�Ŏg�p�ł���~�̍\���̂Ȃ�
* @author kaoken
* @date 2014/03/19 �쐬�J�n
*/
#pragma once


#include <Math/Plane.h>


struct gt2Circle2;


bool GT2IntersectRayCircle(const gt2Vector2& rvP, const gt2Vector2& rvD, const gt2Circle2& rS, float *pT, gt2Vector2 *pQ);
bool GT2RayCircle(const gt2Vector2& rvP, const gt2Vector2& rvD, const gt2Circle2& rS);
bool MCMovingCircleCircle(const gt2Circle2& rS0, const gt2Circle2 &rS1, const gt2Vector2 &rV0, const gt2Vector2 &rV1, float *pfT);



//---------------------------------------
//!@brief �~ @n
//! �̈� R = { (x, y) | (x-c.x)^2 + (y-c.y)^2 <= r^2 }
//---------------------------------------
struct gt2Circle2
{
	gt2Vector2	c;	//!< �~�̒��S
	float		r;	//!< �~�̔��a
public:
	//-----------------------------------------------------------------------------------
	//! @brief �R���X�g���N�^
	//-----------------------------------------------------------------------------------
	gt2Circle2() {
		Init();
	}
	//-----------------------------------------------------------------------------------
	//! @brief �R���X�g���N�^
	//! @param [in] rC �~ 
	//-----------------------------------------------------------------------------------
	gt2Circle2(const gt2Circle2 &rC) {
		Set(rC);
	}
	//-----------------------------------------------------------------------------------
	//! @brief �R���X�g���N�^
	//! @param [in] fx x���W 
	//! @param [in] fy y���W
	//! @param [in] fr ���a
	//-----------------------------------------------------------------------------------
	gt2Circle2(const float fx, const float fy, const float fr) {
		Set(fx, fy, fr);
	}
	//-----------------------------------------------------------------------------------
	//! @brief �R���X�g���N�^
	//! @param [in] rV 2�����x�N�g��
	//! @param [in] fr ���a
	//-----------------------------------------------------------------------------------
	gt2Circle2(const gt2Vector2 &rV, const float fr) {
		Set(rV, fr);
	}
	//-----------------------------------------------------------------------------------
	//! @brief �Z�b�g����
	//! @param [in] fx x���W 
	//! @param [in] fy y���W
	//! @param [in] fr ���a
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void Set(const float fx, const float fy, const float fr)
	{
		c.x = fx; c.y = fy;
		r = fr;
	}
	//-----------------------------------------------------------------------------------
	//! @brief �Z�b�g����
	//! @param [in] rV 2�����x�N�g��
	//! @param [in] fr ���a
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void Set(const gt2Vector2 &rV, const float fr)
	{
		c = rV;
		r = fr;
	}
	//-----------------------------------------------------------------------------------
	//! @brief �Z�b�g����
	//! @param [in] rC �~
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void Set(const gt2Circle2 &rC)
	{
		*this = rC;
	}
	//-----------------------------------------------------------------------------------
	//! @brief �e�v�f��0�ŏ�����
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void Init() {
		c.Init();
		r = 0.0f;
	}

	//##################################################################
	//##
	//## �P�����Z�q
	//##
	//##################################################################
	//-----------------------------------------------------------------------------------
	//! @brief �P�����Z�q + @n
	//! +��t���������ŁA���ɒl�͕ύX�Ȃ�
	//! @return ���̂܂܂̃x�N�g���l��Ԃ�
	//-----------------------------------------------------------------------------------
	inline gt2Circle2 operator + () const
	{
		return *this;
	}
	//-----------------------------------------------------------------------------------
	//! @brief �P�����Z�q - n
	//! �e�v�f��-1����Z�����x�N�g���l�ɂȂ�
	//! @return �e�v�f��-1����Z�����x�N�g���l��Ԃ�
	//-----------------------------------------------------------------------------------
	inline gt2Circle2 operator - () const
	{
		return gt2Circle2(-c.x, -c.y, r);
	}


	//! @name ������Z�q
	//@{
	inline gt2Circle2& operator += (const gt2Vector2& v)
	{
		c += v;
		return *this;
	}
	inline gt2Circle2& operator += (const gt2Vector3& v)
	{
		c.x += v.x;
		c.y += v.y;
		return *this;
	}

	inline gt2Circle2& operator -= (const gt2Vector2& v)
	{
		c -= v;
		return *this;
	}
	inline gt2Circle2& operator -= (const gt2Vector3& v)
	{
		c.x -= v.x;
		c.y -= v.y;
		return *this;
	}

	inline gt2Circle2& operator *= (const gt2Vector2& v)
	{
		c.x *= v.x;
		c.y *= v.y;
		return *this;
	}
	inline gt2Circle2& operator *= (const gt2Vector3& v)
	{
		c.x *= v.x;
		c.y *= v.y;
		return *this;
	}

	inline gt2Circle2& operator /= (const gt2Vector2& v)
	{
		c.x /= v.x;
		c.y /= v.y;
		return *this;
	}
	inline gt2Circle2& operator /= (const gt2Vector3& v)
	{
		c.x /= v.x;
		c.y /= v.y;
		return *this;
	}
	//@}

	//! @name �P�����Z�q
	//@{
	inline gt2Circle2 operator + (const gt2Vector2& v) const
	{
		gt2Circle2 tmp;
		tmp.c = c + v;
		tmp.r = r;
		return tmp;
	}
	inline gt2Circle2 operator + (const gt2Vector3& v) const
	{
		gt2Circle2 tmp;
		tmp.c.x = c.x + v.x;
		tmp.c.y = c.y + v.y;
		tmp.r = r;
		return tmp;
	}

	inline gt2Circle2 operator - (const gt2Vector2& v) const
	{
		gt2Circle2 tmp;
		tmp.c = c - v;
		tmp.r = r;
		return tmp;
	}
	inline gt2Circle2 operator - (const gt2Vector3& v) const
	{
		gt2Circle2 tmp;
		tmp.c.x = c.x - v.x;
		tmp.c.y = c.y - v.y;
		tmp.r = r;
		return tmp;
	}

	inline gt2Circle2 operator * (const gt2Vector2& v) const
	{
		gt2Circle2 tmp;
		tmp.c.x = c.x * v.x;
		tmp.c.y = c.y * v.y;
		tmp.r = r;
		return tmp;
	}
	inline gt2Circle2 operator * (const gt2Vector3& v) const
	{
		gt2Circle2 tmp;
		tmp.c.x = c.x * v.x;
		tmp.c.y = c.y * v.y;
		tmp.r = r;
		return tmp;
	}

	inline gt2Circle2 operator / (const gt2Vector2& v) const
	{
		gt2Circle2 tmp;
		tmp.c.x = c.x / v.x;
		tmp.c.y = c.y / v.y;
		tmp.r = r;
		return tmp;
	}
	inline gt2Circle2 operator / (const gt2Vector3& v) const
	{
		gt2Circle2 tmp;
		tmp.c.x = c.x / v.x;
		tmp.c.y = c.y / v.y;
		tmp.r = r;
		return tmp;
	}
	//@}

	//! @name ��r���Z�q
	//@{
	//-----------------------------------------------------------------------------------
	//! @brief ��r���Z�q == @n
	//!   ���g(this)�̃x�N�g����"rV"�x�N�g���̊e�v�f����������r����
	//! @param [in] v     gt2Vector2
	//! @return ���g(this)�̃x�N�g����"rV"�x�N�g���̊e�v�f���r���A����Ȃ�true��Ԃ��B
	//-----------------------------------------------------------------------------------
	inline bool operator == (const gt2Circle2& v) const
	{
		return c == v.c && r == v.r;
	}
	//-----------------------------------------------------------------------------------
	//! @brief ��r���Z�q != @n
	//!   ���g(this)�̃x�N�g����"rV"�x�N�g���̊e�v�f���Ⴄ����r����
	//! @param [in] v     gt2Vector2
	//! @return ���g(this)�̃x�N�g����"rV"�x�N�g���̊e�v�f���r���A�Ⴄ�ꍇtrue��Ԃ��B
	//-----------------------------------------------------------------------------------
	inline bool operator != (const gt2Circle2& v) const
	{
		return c != v.c || r != v.r;
	}
	//@}

	//-----------------------------------------------------------------------------------
	//! @brief �~�@�� �_�ɂ�邠���蔻��
	//! @param [in] point �_
	//! @return �d�Ȃ��Ă���ꍇ�� true��Ԃ��A �d�Ȃ��Ă��Ȃ��ꍇ��false��Ԃ�
	//-----------------------------------------------------------------------------------
	inline bool CirclePoint(const gt2Vector2& point) const
	{
		float len = (point - c).Length();
		return r >= len;
	}
	//-----------------------------------------------------------------------------------
	//! @brief �~�@�� �~�ɂ�邠���蔻��
	//! @param [in] rA �~A
	//! @param [in] rB �~B
	//! @return �d�Ȃ��Ă���ꍇ�� true��Ԃ��A �d�Ȃ��Ă��Ȃ��ꍇ��false��Ԃ�
	//-----------------------------------------------------------------------------------
	static bool CircleCircle(const gt2Circle2& rA, const gt2Circle2& rB)
	{
		gt2Vector2 v;
		// ���S�Ԃ̋����̕������v�Z
		v = rA.c - rB.c;

		// �������������������������a�����������ꍇ�ɉ~�͌������Ă���
		float fRadiusSum = rA.r + rB.r;
		return v.Dot() <= (fRadiusSum*fRadiusSum);
	}
	//-----------------------------------------------------------------------------------
	//! @brief ���g�̉~�@�� �~�ɂ�邠���蔻��
	//! @param [in] rCircle �~
	//! @return �d�Ȃ��Ă���ꍇ�� true��Ԃ��A �d�Ȃ��Ă��Ȃ��ꍇ��false��Ԃ�
	//-----------------------------------------------------------------------------------
	inline bool CircleCircle(const gt2Circle2& rCircle) const
	{
		return CircleCircle(*this, rCircle);
	}
	//-----------------------------------------------------------------------------------
	//! @brief ����r = p + td, |rvD| = 1���~s�ɑ΂��Č������Ă��邩�ǂ����B
	//! @param [in]  rvP ��_
	//! @param [in]  rvD �����x�N�g��
	//! @param [out] pT  0������Tmax
	//! @param [out] pQ  ���������ʒu
	//! @return �������Ă���ꍇ�A�������Ă���*pT�̒l����ь����_*pQ��Ԃ�
	//-----------------------------------------------------------------------------------
	inline bool IntersectRayCircle(const gt2Vector2& rvP, const gt2Vector2& rvD, float &rOutTime, gt2Vector2 &rQ) const
	{
		return GT2IntersectRayCircle(rvP, rvD, *this, &rOutTime, &rQ);
	}
	//-----------------------------------------------------------------------------------
	//! @brief ����r = p + td�����g�̉~�ƌ������Ă��邩�ǂ����𔻒�
	//! @param [in]  rvP ��_
	//! @param [in]  rvD �����x�N�g��
	//! @return �������Ă���ꍇ�Atrue�Ԃ�
	//-----------------------------------------------------------------------------------
	inline bool RayCircle(const gt2Vector2& rvP, const gt2Vector2& rvD) const
	{
		return GT2RayCircle(rvP, rvD, *this);
	}
	//-----------------------------------------------------------------------------------
	//! @brief X�����N�_�Ƃ������E���]�̉~�����o��
	//! @param [in]  fX x���W
	//! @return  X�����N�_�Ƃ������E���]�̉~��Ԃ�
	//-----------------------------------------------------------------------------------
	inline gt2Circle2 MakeFlipHorizontal(const float fX) const
	{
		return gt2Circle2(fX - c.x, c.y, r);
	}
	//-----------------------------------------------------------------------------------
	//! @brief ����r = p + td, |vDir| = 1���~s�ɑ΂��Č������Ă��邩�ǂ����B
	//! @param [in]  position  ��_
	//! @param [in]  vDir  �����x�N�g��
	//! @param [in]  rS    �ΏۂƂ���~
	//! @param [out] out1  �ڐG�_�P
	//! @param [out] out2  �ڐG�_�Q
	//! @return �������Ă���ꍇ�A�����_�̐���Ԃ�
	//-----------------------------------------------------------------------------------
	int IntersectRayCircle(const gt2Vector2& position, const gt2Vector2& vDir, gt2Vector2 &out1, gt2Vector2 &out2)
	{
		float t;
		gt2Vector2 vM = position - c;
		float a = vM.Dot(vDir);
		float b = vM.Dot() - r * r;
		// r�̌��_��*rS�̊O���ɂ���(c > 0)�Ar��*rS���痣��Ă����������w���Ă���ꍇ(a > 0)�ɏI��
		if (b > 0 && a > 0) return 0;
		float discr = a*a - b;
		// ���̔��ʎ��͌������~���O��Ă���
		if (discr < 0) return 0;
		// ����Ō����͉~�ƌ������Ă��邱�Ƃ�������A��������ŏ��̒l*pT���v�Z
		t = -a - sqrt(discr);
		// t�����ł���ꍇ�A�����͉~�̓���
		if (t < 0) {
			out1 = position + (t*-1) * vDir;
			return 1;
		}
		else if (discr == 0) {
			out1 = position + t * vDir;
			return 1;
		}
		out1 = position + t * vDir;
		out2 = position + (-a + sqrt(discr)) * vDir;
		return 2;
	}
};
