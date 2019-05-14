#include "Capsule.h"


bool GT2SphereCapsule(const gt2Sphere& rSp, const gt2Capsule3D& rCp)
{
	// ���̒��S�ƃJ�v�Z���̐����̊Ԃ�(��������)�������v�Z
	float dist2 = rCp.segment.SqDistPointSegment(rSp.c);

	// (��������)������(��������)���a�̑��a�����������ꍇ�́A�Փ�
	float radius = rSp.r + rCp.r;
	return dist2 <= radius * radius;
}

bool GT2CapsuleCapsule(const gt2Capsule3D& rCP1, const gt2Capsule3D& rCP2)
{
	// �J�v�Z���̓����̍\���̊Ԃ�(��������)�������v�Z
	float fS, fT;
	gt2Vector3 vC1, vC2;
	float dist2 = rCP1.segment.ClosestPtSegmentSegment(&rCP2.segment, &fS, &fT, &vC1, &vC2);

	// (��������)������(��������)���a�̑��a�����������ꍇ�́A�Փ�
	float radius = rCP1.r + rCP2.r;
	return dist2 <= radius * radius;
}
bool GT2PlaneCapsule(const gt2Plane3& rPlane, const gt2Capsule3D& rCapsule)
{
	float fPDist, fNDist;
	fPDist = rPlane.DistanceTo(rCapsule.vEnd);
	fNDist = rPlane.DistanceTo(rCapsule.vStart);
	if (fPDist*fNDist <= 0.0f) {
		// ���ʂɃJ�v�Z�����܂������Ă���
		return true;
	}

	return fabsf(fPDist) <= rCapsule.r || fabsf(fNDist) <= rCapsule.r;
}