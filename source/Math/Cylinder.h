//-----------------------------------------------------------------------------------
// �t�@�C���F gt2Cylinder.h, gt2Cylinder.inl
//
// ���@���@�F
// �@�~����\��
//   
//�@
// ���@���@�F
// �@2007/03/08 Ver.0.1 ����J�n
//
//
// ��@��@�F
// �@Copyright(c)2006 METAL CUBE All rights reserved worldwide..
// �@
//-----------------------------------------------------------------------------------
#pragma once

#include <math.h>
#include "vector.h"
#include "plane.h"
#include "segment.h"

struct gt2Cylinder;

int IntersectSegmentCylinder(gt2Vector3 vSA, gt2Vector3 vSB, gt2Vector3 vP, gt2Vector3 vQ, float fR, float *pfT);
bool GT2PlaneCylinder(const gt2Plane3& rPlane, const gt2Cylinder &cylinder, float *pfT);

typedef struct gt2Cylinder
{
	float		r;	// ���a
	union {
		struct {
			gt2Vector3	vP;	// �n�_
			gt2Vector3	vQ;	// �I�_
		};
		struct {
			mcSegment3	segment;
		};
	};
public:
	float GetHeight() const
	{
		return (vQ - vP).Length();
	}

	int IntersectSegmentCylinder(gt2Vector3 vSA, gt2Vector3 vSB, float *pfT)
	{
		return ::IntersectSegmentCylinder(vSA, vSB, vP, vQ, r, pfT);
	}
	bool PlaneCylinder(const gt2Plane3& rPlane, const gt2Cylinder &cylinder) const
	{
		float fT;
		return GT2PlaneCylinder(rPlane, cylinder, &fT);
	}

}gt2Cylinder, MCCylinder;

