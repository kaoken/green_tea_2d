/*! @file  gt2AABB2D.h
* @brief gt2AABB2D�֘A
* @author kaoken
* @date 2014/03/19 �쐬�J�n
*/
#pragma once

#include <Math/matrix.h>
#include <Math/Circle.h>
#include <Math/Sphere.h>
#include <Box2D/Box2D.h>


//---------------------------------------
//!@brief gt2AABB2D(Axis Aligned Bounding Box) 3D @n
//! �̈� R = { (x, y, z) | min.x<=x<=max.x, min.y<=y<=max.y, min.z<=z<=max.z }
//---------------------------------------
struct gt2AABB3D
{
	gt2Vector3 vMin;	//!< �ő�l�̗v�f
	gt2Vector3 vMax;	//!< �ŏ��l�̗v�f
	//-----------------------------------------------------------------------------------
	//! @brief �R���X�g���N�^
	//-----------------------------------------------------------------------------------
	inline gt2AABB3D() { Init(); }
	//-----------------------------------------------------------------------------------
	//! @brief �R���X�g���N�^
	//! @param [in] rMin �ő�l�̗v�f
	//! @param [in] rMax �ŏ��l�̗v�f
	//-----------------------------------------------------------------------------------
	inline gt2AABB3D(const gt2Vector3 &rMin, const gt2Vector3 &rMax){ Set(vMin, vMax); }
	//-----------------------------------------------------------------------------------
	//! @brief �R���X�g���N�^
	//! @param [in] minX �ŏ��l��X�̒l
	//! @param [in] minY �ŏ��l��Y�̒l
	//! @param [in] minZ �ŏ��l��Y�̒l
	//! @param [in] maxX �ő�l��X�̒l
	//! @param [in] maxY �ő�l��Y�̒l
	//! @param [in] maxZ �ő�l��Y�̒l
	//-----------------------------------------------------------------------------------
	inline gt2AABB3D(float minX, float minY, float minZ, float maxX, float maxY, float maxZ){ Set(minX, minY, minZ, maxX, maxY, maxZ); }
	//-----------------------------------------------------------------------------------
	//! @brief �R���X�g���N�^
	//! @param [in] minX �ŏ��l��X�̒l
	//! @param [in] minY �ŏ��l��Y�̒l
	//! @param [in] minZ �ŏ��l��Y�̒l
	//! @param [in] maxX �ő�l��X�̒l
	//! @param [in] maxY �ő�l��Y�̒l
	//! @param [in] maxZ �ő�l��Y�̒l
	//-----------------------------------------------------------------------------------
	inline gt2AABB3D(const gt2AABB3D& aabb){ Set(aabb); }

	//-----------------------------------------------------------------------------------
	//! @brief �l���Z�b�g����
	//! @param [in] rMin �ŏ��l�̗v�f
	//! @param [in] rMax �ő�l�̗v�f
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void Set(const gt2Vector3 &rMin, const gt2Vector3 &rMax) { vMin = rMin; vMax = rMax; }
	//-----------------------------------------------------------------------------------
	//! @brief �l���Z�b�g����
	//! @param [in] minX �ŏ��l��X�̒l
	//! @param [in] minY �ŏ��l��Y�̒l
	//! @param [in] minZ �ŏ��l��Y�̒l
	//! @param [in] maxX �ő�l��X�̒l
	//! @param [in] maxY �ő�l��Y�̒l
	//! @param [in] maxZ �ő�l��Y�̒l
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void Set(float minX, float minY, float minZ, float maxX, float maxY, float maxZ) { vMin = gt2Vector3(minX, minY, minZ); vMax = gt2Vector3(maxX, maxY, maxZ); }
	//-----------------------------------------------------------------------------------
	//! @brief �l���Z�b�g����
	//! @param [in] aabb gt2AABB3D
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void Set(const gt2AABB3D& aabb) { *this = aabb; }

	//! @name ������Z�q
	//@{
	inline gt2AABB3D& operator += (const gt2Vector3& v)
	{
		vMax += v;
		vMin += v;
		return *this;
	}

	inline gt2AABB3D& operator -= (const gt2Vector3& v)
	{
		vMax -= v;
		vMin -= v;
		return *this;
	}

	inline gt2AABB3D& operator *= (const gt2Vector3& v)
	{
		vMax.x *= v.x;
		vMax.y *= v.y;
		vMax.z *= v.z;
		vMin.x *= v.x;
		vMin.y *= v.y;
		vMin.z *= v.z;
		return *this;
	}

	inline gt2AABB3D& operator /= (const gt2Vector3& v)
	{
		vMax.x /= v.x;
		vMax.y /= v.y;
		vMax.z /= v.z;
		vMin.x /= v.x;
		vMin.y /= v.y;
		vMin.z /= v.z;
		return *this;
	}
	//@}

	//! @name �P���Z�q
	//@{
	inline gt2AABB3D operator + () const
	{
		return *this;
	}
	inline gt2AABB3D operator - () const
	{
		return gt2AABB3D(-vMin, -vMax);
	}
	//@}


	//! @name �񍀉��Z�q
	//@{
	inline gt2AABB3D operator + (const gt2Vector3& v) const
	{
		gt2AABB3D tmp;
		tmp.vMax = vMax + v;
		tmp.vMin = vMin + v;
		return tmp;
	}

	inline gt2AABB3D operator - (const gt2Vector3& v) const
	{
		gt2AABB3D tmp;
		tmp.vMax = vMax - v;
		tmp.vMin = vMin - v;
		return tmp;
	}

	inline gt2AABB3D operator * (const gt2Vector3& v) const
	{
		gt2AABB3D tmp;
		tmp.vMax.x = vMax.x * v.x;
		tmp.vMax.y = vMax.y * v.y;
		tmp.vMin.x = vMin.x * v.x;
		tmp.vMin.y = vMin.y * v.y;
		return tmp;
	}

	inline gt2AABB3D operator / (const gt2Vector3& v) const
	{
		gt2AABB3D tmp;
		tmp.vMax.x = vMax.x / v.x;
		tmp.vMax.y = vMax.y / v.y;
		tmp.vMin.x = vMin.x / v.x;
		tmp.vMin.y = vMin.y / v.y;
		return tmp;
	}
	//@}

	//! @name ��r���Z�q
	//@{
	inline bool operator == (const gt2AABB3D& v) const
	{
		return vMin == v.vMin && vMax == v.vMax;
	}
	inline bool operator != (const gt2AABB3D& v) const
	{
		return vMin != v.vMin || vMax != v.vMax;
	}
	//@}

	//-----------------------------------------------------------------------------------
	//! @brief �e�v�f��0�ŏ�����
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void Init()
	{
		vMin.Init();
		vMax.Init();
	}
	//-----------------------------------------------------------------------------------
	//! @brief vMax�́AFLT_MIN�AvMin�́AFLT_MAX�Ŋe�v�f��������
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void InitMinMax()
	{
		vMin.InitMax();
		vMax.InitMin();
	}
	//-----------------------------------------------------------------------------------
	//! @brief ���g��gt2AABB2D�@�� �Ώۂ�gt2AABB2D�ɂ��u�[�����Z��AND����������B@n
	//!  �Ԓl��true�̏ꍇ�ApOut�ɏo�͂����B
	//! @param [in]  aabb �ΏۂƂȂ�gt2AABB2D
	//! @param [out] pOut  �V���ɍ��ꂽgt2AABB2D
	//! @return �d�Ȃ��Ă���ꍇ�� true��Ԃ��A �d�Ȃ��Ă��Ȃ��ꍇ��false��Ԃ�
	//-----------------------------------------------------------------------------------
	inline bool BooleanOperation_AND(const gt2AABB3D& aabb, gt2AABB3D *pOut)
	{
		//            @-++-----+--@
		// 1. @=====@ | ||     |  |
		// 2.     @===+=@|     |  |
		// 3.         |  @=====@  |
		// 4.         |        @==+==@
		// 5.         |           |  @=====@
		// 6.       @=+===========+==@
		//----------------------------
		// X��
		if (vMin.x <= aabb.vMin.x){
			if (aabb.vMax.x <= vMax.x){
				// 6.
				pOut->vMin.x = aabb.vMin.x;
				pOut->vMax.x = aabb.vMax.x;
			}
			else if (aabb.vMin.x <= vMax.x){
				// 2.
				pOut->vMin.x = aabb.vMin.x;
				pOut->vMax.x = vMax.x;
			}
			else /*if( vMax.x < aabb.vMin.x )*/ {
				// 1.
				return false;
			}
		}
		else if (vMin.x <= aabb.vMax.x){
			if (vMax.x <= aabb.vMax.x){
				// 3.
				pOut->vMin.x = vMin.x;
				pOut->vMax.x = vMax.x;
			}
			else /*if( vMax.x > aabb.vMax.x )*/{
				// 4.
				pOut->vMin.x = vMin.x;
				pOut->vMax.x = aabb.vMax.x;
			}
		}
		else{
			// 5.
			return false;
		}
		//----------------------------
		// Y��
		if (vMin.y <= aabb.vMin.y){
			if (aabb.vMax.y <= vMax.y){
				// 6.
				pOut->vMin.y = aabb.vMin.y;
				pOut->vMax.y = aabb.vMax.y;
			}
			else if (aabb.vMin.y <= vMax.y){
				// 2.
				pOut->vMin.y = aabb.vMin.y;
				pOut->vMax.y = vMax.y;
			}
			else /*if( vMax.y < aabb.vMin.y )*/ {
				// 1.
				return false;
			}
		}
		else if (vMin.y <= aabb.vMax.y){
			if (vMax.y <= aabb.vMax.y){
				// 3.
				pOut->vMin.y = vMin.y;
				pOut->vMax.y = vMax.y;
			}
			else /*if( vMax.y > aabb.vMax.y )*/{
				// 4.
				pOut->vMin.y = vMin.y;
				pOut->vMax.y = aabb.vMax.y;
			}
		}
		else{
			// 5.
			return false;
		}
		//----------------------------
		// Z��
		if (vMin.z <= aabb.vMin.z){
			if (aabb.vMax.z <= vMax.z){
				// 6.
				pOut->vMin.z = aabb.vMin.z;
				pOut->vMax.z = aabb.vMax.z;
			}
			else if (aabb.vMin.z <= vMax.z){
				// 2.
				pOut->vMin.z = aabb.vMin.z;
				pOut->vMax.z = vMax.z;
			}
			else /*if( vMax.z < aabb.vMin.z )*/ {
				// 1.
				return false;
			}
		}
		else if (vMin.z <= aabb.vMax.z){
			if (vMax.z <= aabb.vMax.z){
				// 3.
				pOut->vMin.z = vMin.z;
				pOut->vMax.z = vMax.z;
			}
			else /*if( vMax.z > aabb.vMax.z )*/{
				// 4.
				pOut->vMin.z = vMin.z;
				pOut->vMax.z = aabb.vMax.z;
			}
		}
		else{
			// 5.
			return false;
		}
		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief ���g��gt2AABB2D�@�� �Ώۂ�gt2AABB2D�ɂ��u�[�����Z��AND����������B@n
	//!  �Ԓl��true�̏ꍇ�ApOut�ɏo�͂����B
	//! @param [in]  aabb �ΏۂƂȂ�gt2AABB2D
	//! @param [out] rOut  �V���ɍ��ꂽgt2AABB2D
	//! @return �d�Ȃ��Ă���ꍇ�� true��Ԃ��A �d�Ȃ��Ă��Ȃ��ꍇ��false��Ԃ�
	//-----------------------------------------------------------------------------------
	inline bool BooleanOperation_AND(const gt2AABB3D& aabb, gt2AABB3D &rOut)
	{
		return BooleanOperation_AND(aabb, &rOut);
	}
	//-----------------------------------------------------------------------------------
	//! @brief gt2AABB2D�@�� gt2AABB2D�ɂ�邠���蔻��
	//! @param [in] aabb �ΏۂƂ���gt2AABB2D
	//! @return �d�Ȃ��Ă���ꍇ�� true��Ԃ��A �d�Ȃ��Ă��Ȃ��ꍇ��false��Ԃ�
	//-----------------------------------------------------------------------------------
	inline bool AABB_AABB(const gt2AABB3D& aabb) const
	{
		// ���鎲�ɉ����ĕ������Ă���ꍇ�͌������Ȃ����̂Ƃ��ďI��
		if (vMax.x < aabb.vMin.x || vMin.x > aabb.vMax.x) return false;
		if (vMax.y < aabb.vMin.y || vMin.y > aabb.vMax.y) return false;
		if (vMax.z < aabb.vMin.z || vMin.z > aabb.vMax.z) return false;
		// ���ׂĂ̎��ɉ����ďd�Ȃ��Ă���ꍇ��gt2AABB2D�͌������Ă���
		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief gt2AABB2D�@�� ���̂ɂ�邠���蔻��
	//! @param [in] rS �ΏۂƂ��鋅��
	//! @return �d�Ȃ��Ă���ꍇ�� true��Ԃ��A �d�Ȃ��Ă��Ȃ��ꍇ��false��Ԃ�
	//-----------------------------------------------------------------------------------
	inline bool AABB_Sphere(const gt2Sphere& rS) const
	{
		gt2Vector3 v = this->ClosestPtPoint(rS.c);

		v -= rS.c;
		return v.Dot() <= rS.r * rS.r;
	}

	//-----------------------------------------------------------------------------------
	//! @brief �w�肵���_(rP)���A���g��gt2AABB2D���ɑ��݂��邩�H
	//! @param [in] rP �ΏۂƂ���_
	//! @return �d�Ȃ��Ă���ꍇ�� true��Ԃ��A �d�Ȃ��Ă��Ȃ��ꍇ��false��Ԃ�
	//-----------------------------------------------------------------------------------
	inline bool AABB_Point(const gt2Vector3& rP) const
	{
		// ���鎲�ɉ����ĕ������Ă���ꍇ�͌������Ȃ����̂Ƃ��ďI��
		if (vMax.x < rP.x || vMin.x > rP.x) return false;
		if (vMax.y < rP.y || vMin.y > rP.y) return false;
		if (vMax.y < rP.z || vMin.y > rP.z) return false;
		// ���ׂĂ̎��ɉ����ďd�Ȃ��Ă���ꍇ��gt2AABB2D�͌������Ă���
		return true;
	}

	//-----------------------------------------------------------------------------------
	//! @brief ���̑��xrvMe�����rvB�ł��ꂼ��^�����Ă��邱�̎��g��gt2AABB2D�����'aabb'���������邩? @n
	//!  ��������ꍇ�ɂ́A�ŏ�����эŌ�̐ڐG���Ԃ�pfTFirst�����pfTLast�ɕԂ�
	//! @param [in]  aabb    �ΏۂƂ���gt2AABB2D
	//! @param [in]  rvMe     ���g��gt2AABB2D�̑��x
	//! @param [in]  rvB      aabb�̑��x
	//! @param [out] pfTFirst �ŏ��̐ڐG���Ԃ��Ԃ����
	//! @param [out] pfTLast  �Ō�̐ڐG���Ԃ��Ԃ����
	//! @return �d�Ȃ��Ă���ꍇ�� true��Ԃ��A �d�Ȃ��Ă��Ȃ��ꍇ��false��Ԃ�
	//-----------------------------------------------------------------------------------
	inline bool IntersectMovingAABBAABB(
		const gt2AABB3D& aabb,
		const gt2Vector3& rvMe, const gt2Vector3& rvB,
		float *pfTFirst, float *pfTLast
		) const
	{
		// �ŏ��̎��_��'pvMe'�����'pvB'���d�Ȃ��Ă���ꍇ�C�����ɏI��
		if (this->AABB_AABB(aabb)) {
			*pfTFirst = *pfTLast = 0.0f;
			return true;
		}

		// ���Α��x�𗘗p���A�����I��'pvMe'��Î~���Ă�����̂Ƃ��Ĉ���
		gt2Vector3 v = rvMe - rvB;

		// �ŏ�����эŌ�̐ڐG���Ԃ�������
		*pfTFirst = 0.0f;
		*pfTLast = 1.0f;

		// �e���ɑ΂��āA�ŏ�����эŌ�̐ڐG���Ԃ��A��������Ό��肷��
		//----------------
		// X���ɑ΂���
		//----------------
		if (v.x < 0.0f) {
			if (aabb.vMax.x < vMin.x) return false; // �����͂Ȃ�����ĉ^�����Ă���
			if (vMax.x < aabb.vMin.x) *pfTFirst = std::max((vMax.x - aabb.vMin.x) / v.x, *pfTFirst);
			if (aabb.vMax.x > vMin.x) *pfTLast = std::min((vMin.x - aabb.vMax.x) / v.x, *pfTLast);
		}
		if (v.x > 0.0f) {
			if (aabb.vMin.x > vMax.x) return false; // �����͂Ȃ�����ĉ^�����Ă���
			if (aabb.vMax.x < vMin.x) *pfTFirst = std::max((vMin.x - aabb.vMax.x) / v.x, *pfTFirst);
			if (vMax.x > aabb.vMin.x) *pfTLast = std::min((vMax.x - aabb.vMin.x) / v.x, *pfTLast);
		}
		// �ŏ��̐ڐG���Ō�̐ڐG�̌�ɔ�������ꍇ�́A�����͂��蓾�Ȃ�
		if (*pfTFirst > *pfTLast) return false;
		//----------------
		// Y���ɑ΂���
		//----------------
		if (v.y < 0.0f) {
			if (aabb.vMax.y < vMin.y) return false; // �����͂Ȃ�����ĉ^�����Ă���
			if (vMax.y < aabb.vMin.y) *pfTFirst = std::max((vMax.y - aabb.vMin.y) / v.y, *pfTFirst);
			if (aabb.vMax.y > vMin.y) *pfTLast = std::min((vMin.y - aabb.vMax.y) / v.y, *pfTLast);
		}
		if (v.y > 0.0f) {
			if (aabb.vMin.y > vMax.y) return false; // �����͂Ȃ�����ĉ^�����Ă���
			if (aabb.vMax.y < vMin.y) *pfTFirst = std::max((vMin.y - aabb.vMax.y) / v.y, *pfTFirst);
			if (vMax.y > aabb.vMin.y) *pfTLast = std::min((vMax.y - aabb.vMin.y) / v.y, *pfTLast);
		}
		// �ŏ��̐ڐG���Ō�̐ڐG�̌�ɔ�������ꍇ�́A�����͂��蓾�Ȃ�
		if (*pfTFirst > *pfTLast) return false;
		//----------------
		// Z���ɑ΂���
		//----------------
		if (v.z < 0.0f) {
			if (aabb.vMax.z < vMin.z) return false; // �����͂Ȃ�����ĉ^�����Ă���
			if (vMax.z < aabb.vMin.z) *pfTFirst = std::max((vMax.z - aabb.vMin.z) / v.z, *pfTFirst);
			if (aabb.vMax.z > vMin.z) *pfTLast = std::min((vMin.z - aabb.vMax.z) / v.z, *pfTLast);
		}
		if (v.z > 0.0f) {
			if (aabb.vMin.z > vMax.z) return false; // �����͂Ȃ�����ĉ^�����Ă���
			if (aabb.vMax.z < vMin.z) *pfTFirst = std::max((vMin.z - aabb.vMax.z) / v.z, *pfTFirst);
			if (vMax.z > aabb.vMin.z) *pfTLast = std::min((vMax.z - aabb.vMin.z) / v.z, *pfTLast);
		}
		// �ŏ��̐ڐG���Ō�̐ڐG�̌�ɔ�������ꍇ�́A�����͂��蓾�Ȃ�
		if (*pfTFirst > *pfTLast) return false;

		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief ���̑��xrvMe�����rvB�ł��ꂼ��^�����Ă��邱�̎��g��gt2AABB2D�����'aabb'���������邩? @n
	//!  ��������ꍇ�ɂ́A�ŏ�����эŌ�̐ڐG���Ԃ�pfTFirst�����pfTLast�ɕԂ�
	//! @param [in]  aabb    �ΏۂƂ���gt2AABB2D
	//! @param [in]  rvMe     ���g��gt2AABB2D�̑��x
	//! @param [in]  rvB      aabb�̑��x
	//! @param [out] rTFirst �ŏ��̐ڐG���Ԃ��Ԃ����
	//! @param [out] pfTLast  �Ō�̐ڐG���Ԃ��Ԃ����
	//! @return �d�Ȃ��Ă���ꍇ�� true��Ԃ��A �d�Ȃ��Ă��Ȃ��ꍇ��false��Ԃ�
	//-----------------------------------------------------------------------------------
	inline bool IntersectMovingAABBAABB(
		const gt2AABB3D& aabb,
		const gt2Vector3& rvMe, const gt2Vector3& rvB,
		float &rTFirst, float &rTLast) const
	{
		return IntersectMovingAABBAABB(aabb, rvMe, rvB, &rTFirst, &rTLast);
	}
	//-----------------------------------------------------------------------------------
	//! @brief gt2AABB2D�̃A���J�[�ʒu���擾����
	//! @return gt2AABB2D�̃A���J�[�ʒu��Ԃ�
	//-----------------------------------------------------------------------------------
	inline gt2Vector3 GetCenter() const
	{
		return (vMin + vMax) * 0.5f;
	}
	//-----------------------------------------------------------------------------------
	//! @brief gt2AABB2D�̃A���J�[�ʒu��(0,0)�Ƃ����Ƃ���gt2AABB2D��Ԃ�
	//! @return gt2AABB2D�̃A���J�[�ʒu��(0,0)�Ƃ����Ƃ���gt2AABB2D��Ԃ�
	//-----------------------------------------------------------------------------------
	inline gt2AABB3D GetCenterZeroBase() const
	{
		float x = (vMax.x - vMin.x) * 0.5f;
		float y = (vMax.y - vMin.y) * 0.5f;
		float z = (vMax.z - vMin.z) * 0.5f;

		return gt2AABB3D(gt2Vector3(-x, -y, -z), gt2Vector3(x, y, z));
	}

	//-----------------------------------------------------------------------------------
	//! @brief gt2AABB2D�̃A���J�[�ʒu����̊e�������擾����
	//! @return gt2AABB2D�̃A���J�[�ʒu����̊e������Ԃ�
	//-----------------------------------------------------------------------------------
	inline gt2Vector3 GetLengthFromCenter() const
	{
		gt2Vector3 tmp;
		tmp = (vMin + vMax) * 0.5f;
		return vMax - tmp;
	}
	//-----------------------------------------------------------------------------------
	//! @brief gt2AABB2D�̃A���J�[�ʒu����̊e�����ƃA���J�[�ʒu�擾����
	//! @param [out] pvOutLen    gt2AABB2D�̃A���J�[�ʒu����̊e����
	//! @param [out] pvOutCenter gt2AABB2D�̃A���J�[�ʒu
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void GetLengthFromCenter(gt2Vector3* pvOutLen, gt2Vector3* pvOutCenter) const
	{
		*pvOutCenter = (vMin + vMax) * 0.5f;
		*pvOutLen = vMax - *pvOutCenter;
	}
	//-----------------------------------------------------------------------------------
	//! @brief gt2AABB2D�̃A���J�[�ʒu����̊e�����ƃA���J�[�ʒu�擾����
	//! @param [out] pvOutLen    gt2AABB2D�̃A���J�[�ʒu����̊e����
	//! @param [out] pvOutCenter gt2AABB2D�̃A���J�[�ʒu
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void GetLengthFromCenter(gt2Vector3 &rvOutLen, gt2Vector3 &rvOutCenter) const
	{
		GetLengthFromCenter(&rvOutLen, &rvOutCenter);
	}
	//-----------------------------------------------------------------------------------
	//! @brief gt2AABB2D����8���_�ɕ�������pvOut�ɃZ�b�g����
	//! @param [out] pvOut 8�����_�f�[�^������|�C���^
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void Get8Vertexs(gt2Vector3* pvOut) const
	{
		pvOut[0].x = vMin.x; pvOut[1].x = vMax.x; pvOut[2].x = vMax.x; pvOut[3].x = vMin.x;
		pvOut[0].y = vMin.y; pvOut[1].y = vMin.y; pvOut[2].y = vMin.y; pvOut[3].y = vMin.y;
		pvOut[0].z = vMin.z; pvOut[1].z = vMin.z; pvOut[2].z = vMax.z; pvOut[3].z = vMax.z;
		//----
		pvOut[4].x = vMin.x; pvOut[5].x = vMax.x; pvOut[6].x = vMax.x; pvOut[7].x = vMin.x;
		pvOut[4].y = vMax.y; pvOut[5].y = vMax.y; pvOut[6].y = vMax.y; pvOut[7].y = vMax.y;
		pvOut[4].z = vMin.z; pvOut[5].z = vMin.z; pvOut[6].z = vMax.z; pvOut[7].z = vMax.z;
	}

	//-----------------------------------------------------------------------------------
	//! @brief �^����ꂽ�_rP�ɑ΂��āA����gt2AABB2D�̂����������͒��ɂ���rP�̍ŋߐړ_��Ԃ�
	//! @param [in] rP �^����ꂽ�_
	//! @return �ŋߐړ_
	//-----------------------------------------------------------------------------------
	inline gt2Vector3 ClosestPtPoint(const gt2Vector3 &rP) const
	{
		gt2Vector3 ret;
		if (rP.x < vMin.x) ret.x = vMin.x;
		if (rP.y < vMin.y) ret.y = vMin.y;
		if (rP.z < vMin.z) ret.z = vMin.z;
		if (rP.x > vMax.x) ret.x = vMax.x;
		if (rP.y > vMax.y) ret.y = vMax.y;
		if (rP.z > vMax.z) ret.z = vMax.z;
		return ret;
	}
	//-----------------------------------------------------------------------------------
	//! @brief �_rP�ƁA����gt2AABB2D�̊Ԃ̋����̕������v�Z
	//! @param [in] rP �^����ꂽ�_
	//! @return �����̕����l
	//-----------------------------------------------------------------------------------
	inline float  SqDistPoint(const gt2Vector3 &rP) const
	{
		float sqDist = 0.0f;
		if (rP.x < vMin.x) sqDist += (vMin.x - rP.x) * (vMin.x - rP.x);
		if (rP.y < vMin.y) sqDist += (vMin.y - rP.y) * (vMin.x - rP.y);
		if (rP.z < vMin.z) sqDist += (vMin.z - rP.z) * (vMin.z - rP.z);
		if (rP.x > vMax.x) sqDist += (vMax.x - rP.x) * (vMax.x - rP.x);
		if (rP.y > vMax.y) sqDist += (vMax.y - rP.y) * (vMax.x - rP.y);
		if (rP.z > vMax.z) sqDist += (vMax.z - rP.z) * (vMax.z - rP.z);
		return sqDist;
	}

	//-----------------------------------------------------------------------------------
	//! @brief �}�g���N�X������gt2AABB2D����蒼��
	//! @param [in] rM �}�g���N�X
	//! @return �ό`���gt2AABB2D��Ԃ�
	//-----------------------------------------------------------------------------------
	inline gt2AABB3D GetReMakeAABB(const gt2Matrix4x4& rM) const
	{
		int i;
		gt2Vector3 aV[8], vMx, vMn;

		this->Get8Vertexs(aV);

		for (i = 0; i < 8; ++i){
			aV[i] = rM.TransformVector3(aV[i]);
			vMx.SetMax(aV[i]);
			vMn.SetMax(aV[i]);
		}
		return gt2AABB3D(vMn, vMx);
	}
	//-----------------------------------------------------------------------------------
	//! @brief  �Ώ�gt2AABB2D�Ɋ�{�ʒu�𑫂���gt2AABB2D���ړ���������gt2AABB2D�����
	//! @param [in] rBase    ���ƂȂ�gt2AABB2D
	//! @param [in] rBasePos ���ƂȂ錻�݈ʒu
	//! @param [in] rVel     rBasePos�����_�Ƃ����^���x�N�g��
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakeMoveAABB(const gt2AABB3D& rBase, const gt2Vector3 &rBasePos, const gt2Vector3 &rVel)
	{
		gt2AABB3D tmp;

		vMin = rBase.vMin + rBasePos;
		vMax = rBase.vMax + rBasePos;
		tmp = *this;
		tmp.vMin += rVel;
		tmp.vMax += rVel;
		vMin.SetMin(tmp.vMin);
		vMax.SetMax(tmp.vMax);
	}
	//-----------------------------------------------------------------------------------
	//! @brief  �Ώ�gt2AABB2D�Ɋ�{�ʒu�𑫂���gt2AABB2D���ړ���������gt2AABB2D�����
	//! @param [in] rBase    ���ƂȂ鋅��
	//! @param [in] rVel     rBasePos�����_�Ƃ����^���x�N�g��
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakeMoveAABB(const gt2Sphere& rBase, const gt2Vector3 &rVel)
	{
		gt2AABB3D tmp;

		vMin = rBase.c - rBase.r;
		vMax = rBase.c + rBase.r;
		tmp = *this;
		tmp.vMin += rVel;
		tmp.vMax += rVel;
		vMin.SetMin(tmp.vMin);
		vMax.SetMax(tmp.vMax);
	}
	//-----------------------------------------------------------------------------------
	//! @brief  �Ώۈʒu�ɁA�e���̒���������gt2AABB2D����ړ���������gt2AABB2D�����
	//! @param [in] rSize    ���ƂȂ�e���̃T�C�Y�����g�p����gt2AABB2D
	//! @param [in] rBasePos ���ƂȂ錻�݈ʒu
	//! @param [in] rVel     rBasePos�����_�Ƃ����^���x�N�g��
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakeMovePoint(const gt2AABB3D& rSize, const gt2Vector3 &rBasePos, const gt2Vector3 &rVel)
	{
		this->MakeMovePoint((rSize.vMax - rSize.vMin) * 0.5f, rBasePos, rVel);
	}
	//-----------------------------------------------------------------------------------
	//! @brief 2�̒��_����gt2AABB2D���쐬
	//! @param [in] a ���_A
	//! @param [in] rvB ���_B
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakeFromeSegment(const gt2Vector3& a, const gt2Vector3& rvB)
	{
		vMin.InitMin();
		vMax.InitMax();
		vMin.SetMin(a); vMin.SetMin(rvB);
		vMax.SetMax(a); vMax.SetMax(rvB);
	}
	//-----------------------------------------------------------------------------------
	//! @brief   �Ώۈʒu�ɁA�e���̒���������gt2AABB2D����ړ���������gt2AABB2D�����
	//! @param [in] rL       gt2AABB2D�̊e���̔����̒���
	//! @param [in] rBasePos ���ƂȂ錻�݈ʒu
	//! @param [in] rVel     rBasePos�����_�Ƃ����^���x�N�g��
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakeMovePoint(const gt2Vector3& rL, const gt2Vector3 &rBasePos, const gt2Vector3 &rVel)
	{
		this->InitMinMax();
		vMin.SetMin(rBasePos - rL);
		vMax.SetMax(rBasePos + rL);
		vMin.SetMin((rBasePos + rVel) - rL);
		vMax.SetMax((rBasePos + rVel) + rL);
	}
	//-----------------------------------------------------------------------------------
	//! @brief 3�̒��_����gt2AABB2D���쐬
	//! @param [in] a ���_A
	//! @param [in] rvB ���_B
	//! @param [in] rvC ���_C
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakeFromeTriangle(const gt2Vector3& a, const gt2Vector3& rvB, const gt2Vector3& rvC)
	{
		vMin.InitMin();
		vMax.InitMax();
		vMin.SetMin(a); vMin.SetMin(rvB); vMin.SetMin(rvC);
		vMax.SetMax(a); vMax.SetMax(rvB); vMax.SetMax(rvC);
	}
	//-----------------------------------------------------------------------------------
	//! @brief ���g��gt2AABB2D��V����gt2AABB2D�̍ő�A�ŏ��̗v�f�l�����ɍ�蒼��
	//! @param [in] aabb �ΏۂƂ���gt2AABB2D
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void ReMakeMinMax(const gt2AABB3D& aabb)
	{
		vMin.SetMin(aabb.vMin);
		vMax.SetMax(aabb.vMax);
	}

	//-----------------------------------------------------------------------------------
	//! @brief ���g��gt2AABB2D��V����gt2AABB2D�𑫂��Ċg��������
	//! @param [in] a ���_A
	//! @param [in] rvB ���_B
	//! @param [in] rvC ���_C
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void ReMakeExtension(const gt2AABB3D& aabb)
	{
		vMin.SetMin(aabb.vMin); vMin.SetMin(aabb.vMax);
		vMax.SetMax(aabb.vMin); vMax.SetMax(aabb.vMax);
	}
	//-----------------------------------------------------------------------------------
	//! @brief ���g��gt2AABB2D��8��(���_)�𒷂�R�������g������
	//! @param [in] fR ���a
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void ReMakeExtension(float fR)
	{
		vMin.x -= fR; vMin.y -= fR;
		vMax.x += fR; vMax.y += fR;
	}
	//-----------------------------------------------------------------------------------
	//! @brief gt2AABB2D�����ʂƌ������Ă��邩�H
	//! @param [in] rPlane �Ώە���
	//! @return 0�̏ꍇ�A�������Ă���B-1�̏ꍇ�A�����ɂ���B1�̏ꍇ�A�\���ɂ���
	//-----------------------------------------------------------------------------------
	inline int  AABB_Plane(const gt2Plane3 &rPlane) const
	{
		gt2Vector3 vC = (vMax + vMin) * 0.5f;
		gt2Vector3 vE = vMax - vC;

		float fR = vE.x * fabs(rPlane.vNormal.x) + vE.y * fabs(rPlane.vNormal.y) + vE.z * fabs(rPlane.vNormal.z);
		float fS = rPlane.vNormal.Dot(vC) - rPlane.distance;

		if (fabs(fS) <= fR){
			// �������Ă���
			return 0;
		}
		else if (fS < 0){
			// �����ɂ���
			return -1;
		}

		// �\���ɂ���
		return 1;
	}
};



//---------------------------------------
//!@brief gt2AABB2D(Axis Aligned Bounding Box) 2D @n
//! �̈� R = { (x, y) | min.x<=x<=max.x, min.y<=y<=max.y }
//---------------------------------------
struct gt2AABB2D
{
	gt2Vector2 vMin;	//!< �ő�l�̗v�f
	gt2Vector2 vMax;	//!< �ŏ��l�̗v�f

	//-----------------------------------------------------------------------------------
	//! @brief �R���X�g���N�^
	//-----------------------------------------------------------------------------------
	inline  gt2AABB2D()
	{
		this->Init();
	}

#ifdef B2_MATH_H
	inline  gt2AABB2D(const b2AABB &aabb) {
		vMin = aabb.lowerBound;
		vMax = aabb.upperBound;
	}
#endif

	//-----------------------------------------------------------------------------------
	//! @brief �R���X�g���N�^
	//! @param [in] rMin �ŏ��l�̗v�f
	//! @param [in] rMax �ő�l�̗v�f
	//-----------------------------------------------------------------------------------
	inline  gt2AABB2D(const gt2Vector2 &rMin, const gt2Vector2 &rMax){ Set(rMin, rMax); }

	//-----------------------------------------------------------------------------------
	//! @brief �R���X�g���N�^
	//! @param [in] minX �ŏ��l��X�̒l
	//! @param [in] minY �ŏ��l��Y�̒l
	//! @param [in] maxX �ő�l��X�̒l
	//! @param [in] maxY �ő�l��Y�̒l
	//-----------------------------------------------------------------------------------
	inline  gt2AABB2D(float minX, float minY, float maxX, float maxY){ Set(minX, minY, maxX, maxY); }

	//-----------------------------------------------------------------------------------
	//! @brief �R���X�g���N�^
	//! @param [in] aabb gt2AABB2D
	//-----------------------------------------------------------------------------------
	inline  gt2AABB2D(const gt2AABB2D& aabb){ Set(aabb); }


#ifdef B2_MATH_H
	//-----------------------------------------------------------------------------------
	//! @brief �l���Z�b�g����
	//! @param [in] aabb b2AABB
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void Set(const b2AABB &aabb) {
		vMin = aabb.lowerBound;
		vMax = aabb.upperBound;
	}
#endif
	//-----------------------------------------------------------------------------------
	//! @brief �l���Z�b�g����
	//! @param [in] rMin �ŏ��l�̗v�f
	//! @param [in] rMax �ő�l�̗v�f
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void Set(const gt2Vector2 &rMin, const gt2Vector2 &rMax) { vMin = rMin; vMax = rMax; }
	//-----------------------------------------------------------------------------------
	//! @brief �l���Z�b�g����
	//! @param [in] minX �ŏ��l��X�̒l
	//! @param [in] minY �ŏ��l��Y�̒l
	//! @param [in] maxX �ő�l��X�̒l
	//! @param [in] maxY �ő�l��Y�̒l
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void Set(float minX, float minY, float maxX, float maxY) { vMin = gt2Vector2(minX, minY); vMax = gt2Vector2(maxX,maxY); }
	//-----------------------------------------------------------------------------------
	//! @brief �l���Z�b�g����
	//! @param [in] aabb gt2AABB2D
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void Set(const gt2AABB2D& aabb) { *this = aabb; }


	//! @name ������Z�q
	//@{
#ifdef B2_MATH_H
	inline gt2AABB2D& operator = (const b2AABB &aabb) {
		vMin = aabb.lowerBound;
		vMax = aabb.upperBound;
		return *this;
	}
#endif		
	inline gt2AABB2D& operator += (const gt2Vector2& v)
	{
		vMax += v;
		vMin += v;
		return *this;
	}
	inline gt2AABB2D& operator += (const gt2Vector3& v)
	{
		vMax.x += v.x;
		vMax.y += v.y;
		vMin.x += v.x;
		vMin.y += v.y;
		return *this;
	}

	inline gt2AABB2D& operator -= (const gt2Vector2& v)
	{
		vMax -= v;
		vMin -= v;
		return *this;
	}
	inline gt2AABB2D& operator -= (const gt2Vector3& v)
	{
		vMax.x -= v.x;
		vMax.y -= v.y;
		vMin.x -= v.x;
		vMin.y -= v.y;
		return *this;
	}

	inline gt2AABB2D& operator *= (const gt2Vector2& v)
	{
		vMax.x *= v.x;
		vMax.y *= v.y;
		vMin.x *= v.x;
		vMin.y *= v.y;
		return *this;
	}
	inline gt2AABB2D& operator *= (const gt2Vector3& v)
	{
		vMax.x *= v.x;
		vMax.y *= v.y;
		vMin.x *= v.x;
		vMin.y *= v.y;
		return *this;
	}

	inline gt2AABB2D& operator /= (const gt2Vector2& v)
	{
		vMax.x /= v.x;
		vMax.y /= v.y;
		vMin.x /= v.x;
		vMin.y /= v.y;
		return *this;
	}
	inline gt2AABB2D& operator /= (const gt2Vector3& v)
	{
		vMax.x /= v.x;
		vMax.y /= v.y;
		vMin.x /= v.x;
		vMin.y /= v.y;
		return *this;
	}
	//@}

	//! @name �P���Z�q
	//@{
	inline gt2AABB2D operator + () const
	{
		return *this;
	}
	inline gt2AABB2D operator - () const
	{
		return gt2AABB2D(-vMin, -vMax);
	}
	//@}


	//! @name �񍀉��Z�q
	//@{
	inline gt2AABB2D operator + (const gt2Vector2& v) const
	{
		gt2AABB2D tmp;
		tmp.vMax = vMax + v;
		tmp.vMin = vMin + v;
		return tmp;
	}
	inline gt2AABB2D operator + (const gt2Vector3& v) const
	{
		gt2AABB2D tmp;
		tmp.vMax.x = vMax.x + v.x;
		tmp.vMax.y = vMax.y + v.y;
		tmp.vMin.x = vMin.x + v.x;
		tmp.vMin.y = vMin.y + v.y;
		return tmp;
	}

	inline gt2AABB2D operator - (const gt2Vector2& v) const
	{
		gt2AABB2D tmp;
		tmp.vMax = vMax - v;
		tmp.vMin = vMin - v;
		return tmp;
	}
	inline gt2AABB2D operator - (const gt2Vector3& v) const
	{
		gt2AABB2D tmp;
		tmp.vMax.x = vMax.x - v.x;
		tmp.vMax.y = vMax.y - v.y;
		tmp.vMin.x = vMin.x - v.x;
		tmp.vMin.y = vMin.y - v.y;
		return tmp;
	}

	inline gt2AABB2D operator * (const gt2Vector2& v) const
	{
		gt2AABB2D tmp;
		tmp.vMax.x = vMax.x * v.x;
		tmp.vMax.y = vMax.y * v.y;
		tmp.vMin.x = vMin.x * v.x;
		tmp.vMin.y = vMin.y * v.y;
		return tmp;
	}
	inline gt2AABB2D operator * (const gt2Vector3& v) const
	{
		gt2AABB2D tmp;
		tmp.vMax.x = vMax.x * v.x;
		tmp.vMax.y = vMax.y * v.y;
		tmp.vMin.x = vMin.x * v.x;
		tmp.vMin.y = vMin.y * v.y;
		return tmp;
	}

	inline gt2AABB2D operator / (const gt2Vector2& v) const
	{
		gt2AABB2D tmp;
		tmp.vMax.x = vMax.x / v.x;
		tmp.vMax.y = vMax.y / v.y;
		tmp.vMin.x = vMin.x / v.x;
		tmp.vMin.y = vMin.y / v.y;
		return tmp;
	}
	inline gt2AABB2D operator / (const gt2Vector3& v) const
	{
		gt2AABB2D tmp;
		tmp.vMax.x = vMax.x / v.x;
		tmp.vMax.y = vMax.y / v.y;
		tmp.vMin.x = vMin.x / v.x;
		tmp.vMin.y = vMin.y / v.y;
		return tmp;
	}
	//@}

	//! @name ��r���Z�q
	//@{
	inline bool operator == (const gt2AABB2D& v) const
	{
		return vMin == v.vMin && vMax == v.vMax;
	}
	inline bool operator != (const gt2AABB2D& v) const
	{
		return vMin != v.vMin || vMax != v.vMax;
	}
	//@}

	//-----------------------------------------------------------------------------------
	//! @brief �e�v�f��0�ŏ�����
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void Init()
	{
		vMin.Init();
		vMax.Init();
	}
	//-----------------------------------------------------------------------------------
	//! @brief vMax�́AFLT_MAX�AvMin�́AFLT_MIN�Ŋe�v�f��������
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void InitMinMax()
	{
		vMin.InitMax();
		vMax.InitMin();
	}
	//-----------------------------------------------------------------------------------
	//! @brief�@vMin(x, y - (h - 1)) �AvMax(x + (w - 1), y)��gt2AABB2D�����
	//! @param [in] x x���W
	//! @param [in] y y���W
	//! @param [in] w ��
	//! @param [in] h ����
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void Set_X_Y_W_H(float x, float y, float w, float h)
	{
		vMin.x = x;
		vMin.y = y - (h - 1);
		vMax.x = x + (w - 1);
		vMax.y = y;
	}
	//-----------------------------------------------------------------------------------
	//! @brief ���g��gt2AABB2D�@�� �Ώۂ�gt2AABB2D�ɂ��u�[�����Z��AND����������B@n
	//!  �Ԓl��true�̏ꍇ�ApOut�ɏo�͂����B
	//! @param [out] rOut  �V���ɍ��ꂽgt2AABB2D
	//! @param [in]  aabb �ΏۂƂȂ�gt2AABB2D
	//! @return �d�Ȃ��Ă���ꍇ�� true��Ԃ��A �d�Ȃ��Ă��Ȃ��ꍇ��false��Ԃ�
	//-----------------------------------------------------------------------------------
	inline bool BooleanOperation_AND(const gt2AABB2D& aabb, gt2AABB2D &rOut)
	{
		return BooleanOperation_AND(aabb, &rOut);
	}
	//-----------------------------------------------------------------------------------
	//! @brief ���g��gt2AABB2D�@�� �Ώۂ�gt2AABB2D�ɂ��u�[�����Z��AND����������B@n
	//!  �Ԓl��true�̏ꍇ�ApOut�ɏo�͂����B
	//! @param [in]  aabb �ΏۂƂȂ�gt2AABB2D
	//! @param [out] pOut  �V���ɍ��ꂽgt2AABB2D
	//! @return �d�Ȃ��Ă���ꍇ�� true��Ԃ��A �d�Ȃ��Ă��Ȃ��ꍇ��false��Ԃ�
	//-----------------------------------------------------------------------------------
	inline bool BooleanOperation_AND(const gt2AABB2D& aabb, gt2AABB2D *pOut)
	{
		//            @-++-----+--@
		// 1. @=====@ | ||     |  |
		// 2.     @===+=@|     |  |
		// 3.         |  @=====@  |
		// 4.         |        @==+==@
		// 5.         |           |  @=====@
		// 6.       @=+===========+==@
		//----------------------------
		// X��
		if (vMin.x <= aabb.vMin.x){
			if (aabb.vMax.x <= vMax.x){
				// 6.
				pOut->vMin.x = aabb.vMin.x;
				pOut->vMax.x = aabb.vMax.x;
			}
			else if (aabb.vMin.x <= vMax.x){
				// 2.
				pOut->vMin.x = aabb.vMin.x;
				pOut->vMax.x = vMax.x;
			}
			else /*if( vMax.x < aabb.vMin.x )*/ {
				// 1.
				return false;
			}
		}
		else if (vMin.x <= aabb.vMax.x){
			if (vMax.x <= aabb.vMax.x){
				// 3.
				pOut->vMin.x = vMin.x;
				pOut->vMax.x = vMax.x;
			}
			else /*if( vMax.x > aabb.vMax.x )*/{
				// 4.
				pOut->vMin.x = vMin.x;
				pOut->vMax.x = aabb.vMax.x;
			}
		}
		else{
			// 5.
			return false;
		}
		//----------------------------
		// Y��
		if (vMin.y <= aabb.vMin.y){
			if (aabb.vMax.y <= vMax.y){
				// 6.
				pOut->vMin.y = aabb.vMin.y;
				pOut->vMax.y = aabb.vMax.y;
			}
			else if (aabb.vMin.y <= vMax.y){
				// 2.
				pOut->vMin.y = aabb.vMin.y;
				pOut->vMax.y = vMax.y;
			}
			else /*if( vMax.y < aabb.vMin.y )*/ {
				// 1.
				return false;
			}
		}
		else if (vMin.y <= aabb.vMax.y){
			if (vMax.y <= aabb.vMax.y){
				// 3.
				pOut->vMin.y = vMin.y;
				pOut->vMax.y = vMax.y;
			}
			else /*if( vMax.y > aabb.vMax.y )*/{
				// 4.
				pOut->vMin.y = vMin.y;
				pOut->vMax.y = aabb.vMax.y;
			}
		}
		else{
			// 5.
			return false;
		}
		return true;
	}

	//-----------------------------------------------------------------------------------
	//! @brief gt2AABB2D�@�� gt2AABB2D�ɂ�邠���蔻��
	//! @param [in] aabb �ΏۂƂ���gt2AABB2D
	//! @return �d�Ȃ��Ă���ꍇ�� true��Ԃ��A �d�Ȃ��Ă��Ȃ��ꍇ��false��Ԃ�
	//-----------------------------------------------------------------------------------
	inline bool AABB_AABB(const gt2AABB2D& aabb) const
	{
		// ���鎲�ɉ����ĕ������Ă���ꍇ�͌������Ȃ����̂Ƃ��ďI��
		if (vMax.x < aabb.vMin.x || vMin.x > aabb.vMax.x) return false;
		if (vMax.y < aabb.vMin.y || vMin.y > aabb.vMax.y) return false;
		// ���ׂĂ̎��ɉ����ďd�Ȃ��Ă���ꍇ��gt2AABB2D�͌������Ă���
		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief gt2AABB2D�@�� �~�ɂ�邠���蔻��
	//! @param [in] rCIRCLE �ΏۂƂ���~
	//! @return �d�Ȃ��Ă���ꍇ�� true��Ԃ��A �d�Ȃ��Ă��Ȃ��ꍇ��false��Ԃ�
	//-----------------------------------------------------------------------------------
	inline bool AABB_CIRCLE(const gt2Circle2& rCIRCLE) const
	{
		gt2Vector2 v = this->ClosestPtPoint(rCIRCLE.c);

		v -= rCIRCLE.c;
		return v.Dot() <= rCIRCLE.r * rCIRCLE.r;
	}
	//-----------------------------------------------------------------------------------
	//! @brief �w�肵���_(rP)���A���g��gt2AABB2D���ɑ��݂��邩�H
	//! @param [in] rP �ΏۂƂ���_
	//! @return �d�Ȃ��Ă���ꍇ�� true��Ԃ��A �d�Ȃ��Ă��Ȃ��ꍇ��false��Ԃ�
	//-----------------------------------------------------------------------------------
	inline bool AABB_Point(const gt2Vector2& rP) const
	{
		// ���鎲�ɉ����ĕ������Ă���ꍇ�͌������Ȃ����̂Ƃ��ďI��
		if (vMax.x < rP.x || vMin.x > rP.x) return false;
		if (vMax.y < rP.y || vMin.y > rP.y) return false;
		// ���ׂĂ̎��ɉ����ďd�Ȃ��Ă���ꍇ��gt2AABB2D�͌������Ă���
		return true;
	}

	//-----------------------------------------------------------------------------------
	//! @brief ���̑��xrvMe�����rvB�ł��ꂼ��^�����Ă��邱�̎��g��gt2AABB2D�����'aabb'���������邩? @n
	//!  ��������ꍇ�ɂ́A�ŏ�����эŌ�̐ڐG���Ԃ�pfTFirst�����pfTLast�ɕԂ�
	//! @param [in]  aabb    �ΏۂƂ���gt2AABB2D
	//! @param [in]  rvMe     ���g��gt2AABB2D�̑��x
	//! @param [in]  rvB      aabb�̑��x
	//! @param [out] rTFirst �ŏ��̐ڐG���Ԃ��Ԃ����
	//! @param [out] rTLast  �Ō�̐ڐG���Ԃ��Ԃ����
	//! @return �d�Ȃ��Ă���ꍇ�� true��Ԃ��A �d�Ȃ��Ă��Ȃ��ꍇ��false��Ԃ�
	//-----------------------------------------------------------------------------------
	inline bool IntersectMovingAABBAABB(
		const gt2AABB2D& aabb,
		const gt2Vector2& rvMe, const gt2Vector2& rvB,
		float &rTFirst, float &rTLast
		) const
	{
		return IntersectMovingAABBAABB(aabb, rvMe, rvB, &rTFirst, &rTLast);
	}
	//-----------------------------------------------------------------------------------
	//! @brief ���̑��xrvMe�����rvB�ł��ꂼ��^�����Ă��邱�̎��g��gt2AABB2D�����'aabb'���������邩? @n
	//!  ��������ꍇ�ɂ́A�ŏ�����эŌ�̐ڐG���Ԃ�pfTFirst�����pfTLast�ɕԂ�
	//! @param [in]  aabb    �ΏۂƂ���gt2AABB2D
	//! @param [in]  rvMe     ���g��gt2AABB2D�̑��x
	//! @param [in]  rvB      aabb�̑��x
	//! @param [out] pfTFirst �ŏ��̐ڐG���Ԃ��Ԃ����
	//! @param [out] pfTLast  �Ō�̐ڐG���Ԃ��Ԃ����
	//! @return �d�Ȃ��Ă���ꍇ�� true��Ԃ��A �d�Ȃ��Ă��Ȃ��ꍇ��false��Ԃ�
	//-----------------------------------------------------------------------------------
	inline bool IntersectMovingAABBAABB(
		const gt2AABB2D& aabb,
		const gt2Vector2& rvMe, const gt2Vector2& rvB,
		float *pfTFirst, float *pfTLast
		) const
	{
		// �ŏ��̎��_��'pvMe'�����'pvB'���d�Ȃ��Ă���ꍇ�C�����ɏI��
		if (this->AABB_AABB(aabb)) {
			*pfTFirst = *pfTLast = 0.0f;
			return true;
		}

		// ���Α��x�𗘗p���A�����I��'pvMe'��Î~���Ă�����̂Ƃ��Ĉ���
		gt2Vector2 v = rvMe - rvB;

		// �ŏ�����эŌ�̐ڐG���Ԃ�������
		*pfTFirst = 0.0f;
		*pfTLast = 1.0f;

		// �e���ɑ΂��āA�ŏ�����эŌ�̐ڐG���Ԃ��A��������Ό��肷��
		//----------------
		// X���ɑ΂���
		//----------------
		if (v.x < 0.0f) {
			if (aabb.vMax.x < vMin.x) return false; // �����͂Ȃ�����ĉ^�����Ă���
			if (vMax.x < aabb.vMin.x) *pfTFirst = std::max((vMax.x - aabb.vMin.x) / v.x, *pfTFirst);
			if (aabb.vMax.x > vMin.x) *pfTLast = std::min((vMin.x - aabb.vMax.x) / v.x, *pfTLast);
		}
		if (v.x > 0.0f) {
			if (aabb.vMin.x > vMax.x) return false; // �����͂Ȃ�����ĉ^�����Ă���
			if (aabb.vMax.x < vMin.x) *pfTFirst = std::max((vMin.x - aabb.vMax.x) / v.x, *pfTFirst);
			if (vMax.x > aabb.vMin.x) *pfTLast = std::min((vMax.x - aabb.vMin.x) / v.x, *pfTLast);
		}
		// �ŏ��̐ڐG���Ō�̐ڐG�̌�ɔ�������ꍇ�́A�����͂��蓾�Ȃ�
		if (*pfTFirst > *pfTLast) return false;
		//----------------
		// Y���ɑ΂���
		//----------------
		if (v.y < 0.0f) {
			if (aabb.vMax.y < vMin.y) return false; // �����͂Ȃ�����ĉ^�����Ă���
			if (vMax.y < aabb.vMin.y) *pfTFirst = std::max((vMax.y - aabb.vMin.y) / v.y, *pfTFirst);
			if (aabb.vMax.y > vMin.y) *pfTLast = std::min((vMin.y - aabb.vMax.y) / v.y, *pfTLast);
		}
		if (v.y > 0.0f) {
			if (aabb.vMin.y > vMax.y) return false; // �����͂Ȃ�����ĉ^�����Ă���
			if (aabb.vMax.y < vMin.y) *pfTFirst = std::max((vMin.y - aabb.vMax.y) / v.y, *pfTFirst);
			if (vMax.y > aabb.vMin.y) *pfTLast = std::min((vMax.y - aabb.vMin.y) / v.y, *pfTLast);
		}
		// �ŏ��̐ڐG���Ō�̐ڐG�̌�ɔ�������ꍇ�́A�����͂��蓾�Ȃ�
		if (*pfTFirst > *pfTLast) return false;

		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief gt2AABB2D�̃A���J�[�ʒu���擾����
	//! @param [out] x x���W
	//! @param [out] y y���W
	//! @param [out] w ��
	//! @param [out] h ����
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void Get_X_Y_W_H(float &x, float &y, float &w, float &h) const
	{
		Get_X_Y_W_H(&x, &y, &w, &h);
	}
	//-----------------------------------------------------------------------------------
	//! @brief gt2AABB2D�̃A���J�[�ʒu���擾����
	//! @param [out] px x���W
	//! @param [out] py y���W
	//! @param [out] pw ��
	//! @param [out] ph ����
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void Get_X_Y_W_H(float *px, float *py, float *pw, float *ph) const
	{
		*px = vMin.x;
		*py = vMax.y;
		*pw = vMax.x - vMin.x + 1;
		*ph = vMax.y - vMin.y + 1;
	}
	//-----------------------------------------------------------------------------------
	//! @brief gt2AABB2D�̃A���J�[�ʒu���擾����
	//! @return gt2AABB2D�̃A���J�[�ʒu��Ԃ�
	//-----------------------------------------------------------------------------------
	inline gt2Vector2 GetCenter() const
	{
		return (vMin + vMax) * 0.5f;
	}
	//-----------------------------------------------------------------------------------
	//! @brief gt2AABB2D�̃A���J�[�ʒu��(0,0)�Ƃ����Ƃ���gt2AABB2D��Ԃ�
	//! @return gt2AABB2D�̃A���J�[�ʒu��(0,0)�Ƃ����Ƃ���gt2AABB2D��Ԃ�
	//-----------------------------------------------------------------------------------
	inline gt2AABB2D GetCenterZeroBase() const
	{
		float x = (vMax.x - vMin.x) * 0.5f;
		float y = (vMax.y - vMin.y) * 0.5f;

		return gt2AABB2D(gt2Vector2(-x, -y), gt2Vector2(x, y));
	}
	//-----------------------------------------------------------------------------------
	//! @brief gt2AABB2D�̃A���J�[�ʒu����̊e�������擾����
	//! @return gt2AABB2D�̃A���J�[�ʒu����̊e������Ԃ�
	//-----------------------------------------------------------------------------------
	inline gt2Vector2 GetLengthFromCenter() const
	{
		gt2Vector2 tmp;
		tmp = (vMin + vMax) * 0.5f;
		return vMax - tmp;
	}
	//-----------------------------------------------------------------------------------
	//! @brief gt2AABB2D�̃A���J�[�ʒu����̊e�����ƃA���J�[�ʒu�擾����
	//! @param [out] rvOutLen    gt2AABB2D�̃A���J�[�ʒu����̊e����
	//! @param [out] rvOutCenter gt2AABB2D�̃A���J�[�ʒu
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void GetLengthFromCenter(gt2Vector2& rvOutLen, gt2Vector2& rvOutCenter) const
	{
		GetLengthFromCenter(&rvOutLen, &rvOutCenter);
	}
	//-----------------------------------------------------------------------------------
	//! @brief gt2AABB2D�̃A���J�[�ʒu����̊e�����ƃA���J�[�ʒu�擾����
	//! @param [out] pvOutLen    gt2AABB2D�̃A���J�[�ʒu����̊e����
	//! @param [out] pvOutCenter gt2AABB2D�̃A���J�[�ʒu
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void GetLengthFromCenter(gt2Vector2* pvOutLen, gt2Vector2* pvOutCenter) const
	{
		*pvOutCenter = (vMin + vMax) * 0.5f;
		*pvOutLen = vMax - *pvOutCenter;
	}
	//-----------------------------------------------------------------------------------
	//! @brief gt2AABB2D����4���_�ɕ�������pvOut�ɃZ�b�g����
	//! @param [out] pvOut 4�����_�f�[�^������|�C���^
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void Get4Vertexs(gt2Vector2* pvOut) const
	{
		pvOut[0].x = vMin.x; pvOut[1].x = vMax.x; pvOut[2].x = vMax.x; pvOut[3].x = vMin.x;
		pvOut[0].y = vMin.y; pvOut[1].y = vMin.y; pvOut[2].y = vMax.y; pvOut[3].y = vMax.y;
	}
	//-----------------------------------------------------------------------------------
	//! @brief gt2AABB2D����4���_�ɕ�������pvOut�ɃZ�b�g����
	//! @param [out] pvOut 4�����_�f�[�^������|�C���^
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void Get4Vertexs(gt2Vector3* pvOut) const
	{
		pvOut[0].x = vMin.x; pvOut[1].x = vMax.x; pvOut[2].x = vMax.x; pvOut[3].x = vMin.x;
		pvOut[0].y = vMin.y; pvOut[1].y = vMin.y; pvOut[2].y = vMax.y; pvOut[3].y = vMax.y;
		pvOut[0].z = 0.0f; pvOut[1].z = 0.0f; pvOut[2].z = 0.0f; pvOut[3].z = 0.0f;
	}
	//-----------------------------------------------------------------------------------
	//! @brief �^����ꂽ�_rP�ɑ΂��āA����gt2AABB2D�̂����������͒��ɂ���rP�̍ŋߐړ_��Ԃ�
	//! @param [in] rP �^����ꂽ�_
	//! @return �ŋߐړ_
	//-----------------------------------------------------------------------------------
	inline gt2Vector2 ClosestPtPoint(const gt2Vector2 &rP) const
	{
		gt2Vector2 ret;
		if (rP.x < vMin.x) ret.x = vMin.x;
		if (rP.x > vMax.x) ret.x = vMax.x;
		if (rP.y < vMin.y) ret.y = vMin.y;
		if (rP.y > vMax.y) ret.y = vMax.y;
		return ret;
	}
	//-----------------------------------------------------------------------------------
	//! @brief �_rP�ƁA����gt2AABB2D�̊Ԃ̋����̕������v�Z
	//! @param [in] rP �^����ꂽ�_
	//! @return �����̕����l
	//-----------------------------------------------------------------------------------
	inline float  SqDistPoint(const gt2Vector2 &rP) const
	{
		float sqDist = 0.0f;
		if (rP.x < vMin.x) sqDist += (vMin.x - rP.x) * (vMin.x - rP.x);
		if (rP.x > vMax.x) sqDist += (vMax.x - rP.x) * (vMax.x - rP.x);
		if (rP.y < vMin.y) sqDist += (vMin.y - rP.y) * (vMin.x - rP.y);
		if (rP.y > vMax.y) sqDist += (vMax.y - rP.y) * (vMax.x - rP.y);
		return sqDist;
	}

	//-----------------------------------------------------------------------------------
	//! @brief �}�g���N�X������gt2AABB2D����蒼��
	//! @param [in] rM �}�g���N�X
	//! @return �ό`���gt2AABB2D��Ԃ�
	//-----------------------------------------------------------------------------------
	inline gt2AABB2D GetReMakeAABB(const gt2Matrix4x4& rM) const
	{
		int i;
		gt2Vector3 aV3[4];
		gt2Vector2 aV[4], vMx, vMn;

		for (i = 0; i<4; ++i){
			aV3[i] = aV[i];
		}

		this->Get4Vertexs(aV3);

		for (i = 0; i<4; ++i){
			aV3[i] = rM.TransformVector3(aV3[i]);
			vMx.SetMax(gt2Vector2(aV3[i].x, aV3[i].y));
			vMn.SetMax(gt2Vector2(aV3[i].x, aV3[i].y));
		}
		return gt2AABB2D(vMn, vMx);
	}
	//-----------------------------------------------------------------------------------
	//! @brief  ���g��gt2AABB2D��X�����N�_�Ƃ������E���]��gt2AABB2D�����
	//! @param [in] fX    X�̒l
	//! @return X�����N�_�Ƃ������E���]��gt2AABB2D��Ԃ�
	//-----------------------------------------------------------------------------------
	inline gt2AABB2D MakeFlipHorizontal(float fX) const
	{
		gt2AABB2D ret = *this;
		ret.vMin.x = fX - vMax.x;
		ret.vMax.x = fX - vMin.x;
		return ret;
	}
	//-----------------------------------------------------------------------------------
	//! @brief  �Ώ�gt2AABB2D�Ɋ�{�ʒu�𑫂���gt2AABB2D���ړ���������gt2AABB2D�����
	//! @param [in] rBase    ���ƂȂ�gt2AABB2D
	//! @param [in] rBasePos ���ƂȂ錻�݈ʒu
	//! @param [in] rVel     rBasePos�����_�Ƃ����^���x�N�g��
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakeMoveAABB(const gt2AABB2D& rBase, const gt2Vector2 &rBasePos, const gt2Vector2 &rVel)
	{
		gt2AABB2D tmp;

		vMin = rBase.vMin + rBasePos;
		vMax = rBase.vMax + rBasePos;
		tmp = *this;
		tmp.vMin += rVel;
		tmp.vMax += rVel;
		vMin.SetMin(tmp.vMin);
		vMax.SetMax(tmp.vMax);
	}
	//-----------------------------------------------------------------------------------
	//! @brief �^���x�N�g�����ꂽ�傫���������gt2AABB2D
	//! @param [in] rBase    ���ƂȂ�~
	//! @param [in] rBasePos ���ƂȂ錻�݈ʒu
	//! @param [in] rVel     rBasePos�����_�Ƃ����^���x�N�g��
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakeMoveAABB(const gt2Circle2& rBase, const gt2Vector2 &rBasePos, const gt2Vector2 &rVel)
	{
		gt2AABB2D tmp;

		tmp.vMax.x = rBase.c.x + rBase.r;
		tmp.vMax.y = rBase.c.y + rBase.r;
		tmp.vMin.x = rBase.c.x - rBase.r;
		tmp.vMin.y = rBase.c.y - rBase.r;

		this->MakeMoveAABB(tmp, rBasePos, rVel);
	}
	//-----------------------------------------------------------------------------------
	//! @brief  �Ώۈʒu�ɁA�e���̒���������gt2AABB2D����ړ���������gt2AABB2D�����
	//! @param [in] rSize    ���ƂȂ�e���̃T�C�Y�����g�p����gt2AABB2D
	//! @param [in] rBasePos ���ƂȂ錻�݈ʒu
	//! @param [in] rVel     rBasePos�����_�Ƃ����^���x�N�g��
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakeMovePoint(const gt2AABB2D& rSize, const gt2Vector2 &rBasePos, const gt2Vector2 &rVel)
	{
		this->MakeMovePoint((rSize.vMax - rSize.vMin) * 0.5f, rBasePos, rVel);
	}
	//-----------------------------------------------------------------------------------
	//! @brief   �Ώۈʒu�ɁA�e���̒���������gt2AABB2D����ړ���������gt2AABB2D�����
	//! @param [in] rL       gt2AABB2D�̊e���̔����̒���
	//! @param [in] rBasePos ���ƂȂ錻�݈ʒu
	//! @param [in] rVel     rBasePos�����_�Ƃ����^���x�N�g��
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakeMovePoint(const gt2Vector2& rL, const gt2Vector2 &rBasePos, const gt2Vector2 &rVel)
	{
		this->InitMinMax();
		vMin.SetMin(rBasePos - rL);
		vMax.SetMax(rBasePos + rL);
		vMin.SetMin((rBasePos + rVel) - rL);
		vMax.SetMax((rBasePos + rVel) + rL);
	}
	//-----------------------------------------------------------------------------------
	//! @brief 2�̒��_����gt2AABB2D���쐬
	//! @param [in] a ���_A
	//! @param [in] rvB ���_B
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void MakeFromeSegment(const gt2Vector2& a, const gt2Vector2& rvB)
	{
		vMin.InitMin();
		vMax.InitMax();
		vMin.SetMin(a); vMin.SetMin(rvB);
		vMax.SetMax(a); vMax.SetMax(rvB);
	}
	//-----------------------------------------------------------------------------------
	//! @brief ���g��gt2AABB2D��V����gt2AABB2D�̍ő�A�ŏ��̗v�f�l�����ɍ�蒼��
	//! @param [in] aabb �ΏۂƂ���gt2AABB2D
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void ReMakeMinMax(const gt2AABB2D& aabb)
	{
		vMin.SetMin(aabb.vMin);
		vMax.SetMax(aabb.vMax);
	}

	//-----------------------------------------------------------------------------------
	//! @brief ���g��gt2AABB2D��V����gt2AABB2D�𑫂��Ċg��������
	//! @param [in] aabb �ΏۂƂ���gt2AABB2D
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void ReMakeExtension(const gt2AABB2D& aabb)
	{
		gt2Vector2 vLen;
		vLen = aabb.GetLengthFromCenter();
		vMin.x -= vLen.x; vMin.y -= vLen.y;
		vMax.x += vLen.x; vMax.y += vLen.y;
	}
	//-----------------------------------------------------------------------------------
	//! @brief ���g��gt2AABB2D�̎l��(���_)�𒷂�R�������g������
	//! @param [in] fR ���a
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void ReMakeExtension(float fR)
	{
		vMin.x -= fR; vMin.y -= fR;
		vMax.x += fR; vMax.y += fR;
	}
	//-----------------------------------------------------------------------------------
	//! @brief gt2AABB2D�����ʂƌ������Ă��邩�H
	//! @param [in] rPlane �Ώە���
	//! @return 0�̏ꍇ�A�������Ă���B-1�̏ꍇ�A�����ɂ���B1�̏ꍇ�A�\���ɂ���
	//-----------------------------------------------------------------------------------
	inline int  AABB_Plane(const gt2Plane2 &rPlane) const
	{
		gt2Vector2 vC = (vMax + vMin) * 0.5f;
		gt2Vector2 vE = vMax - vC;

		float fR = vE.x * fabs(rPlane.vNormal.x) + vE.y * fabs(rPlane.vNormal.y);
		float fS = rPlane.vNormal.Dot(vC) - rPlane.distance;

		if (fabs(fS) <= fR){
			// �������Ă���
			return 0;
		}
		else if (fS < 0){
			// �����ɂ���
			return -1;
		}

		// �\���ɂ���
		return 1;
	}
};

