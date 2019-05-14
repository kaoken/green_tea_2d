//-----------------------------------------------------------------------------------
// �t�@�C���F gt2Capsule3D.h, gt2Capsule3D.inl
//
// ���@���@�F
// �@�J�v�Z���֘A
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

#include <Math/vector.h>
#include <Math/Segment.h>
#include <Math/Sphere.h>


struct gt2Capsule3D;


bool GT2SphereCapsule(const gt2Sphere& rSp, const gt2Capsule3D& rCp);
bool GT2CapsuleCapsule(const gt2Capsule3D& rCP1, const gt2Capsule3D& rCP2);
bool GT2PlaneCapsule(const gt2Plane3& rPlane, const gt2Capsule3D& rCapsule);

//---------------------------------------
// �J�v�Z���i���̂��g�p�j
//---------------------------------------
// �̈� R = { x | (x - [s.a + (s.b - s.a)*t])^2 <= r }, 0 <= t <= 1
typedef struct gt2Capsule3D {
	union {
		struct {
			mcSegment3 segment;	// ���ԕ��̐���
		};
		struct {
			gt2Vector3 vStart, vEnd;
		};
	};
	float r;		// ���a

public:
	gt2Capsule3D() {}

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
	inline gt2Capsule3D& operator = (const gt2Capsule3D& v)
	{
		r = v.r;
		segment = v.segment;
		return *this;
	}

	bool SphereCapsule(const gt2Sphere& rSp) const
	{
		return GT2SphereCapsule(rSp, *this);
	}
	bool CapsuleCapsule(const gt2Capsule3D& rCP2) const
	{
		return GT2CapsuleCapsule(*this, rCP2);
	}

}gt2Capsule3D;
