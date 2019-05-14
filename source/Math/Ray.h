//-----------------------------------------------------------------------------------
// �t�@�C���F mcRay.h, mcRay.inl
//
// ���@���@�F
// �@������\��
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
#include <Math/vector.h>

enum CLASSIFICATION
{
	MMM, MMP, MPM, MPP, PMM, PMP, PPM, PPP
};
typedef struct gt2Ray2
{
	CLASSIFICATION classification;		// MMM, MMP, etc.
	gt2Vector2 vOrigin;		// �����N��
	gt2Vector2 vDirection;	// ����
	gt2Vector2 vInver;		// ���������̋t��

public:
	gt2Ray2()
	{
		this->Init();
	}
	gt2Ray2(const gt2Vector2 &vO, const gt2Vector2 &vD)
	{
		this->Make(vO, vD);
	}
	void Make(const gt2Vector2 &vO, const gt2Vector2 &vD)
	{
		vOrigin = vO;
		vDirection = vD;

		vInver.x = vDirection.x != 0.0f ? 1.0f / vDirection.x : 0.0f;
		vInver.y = vDirection.y != 0.0f ? 1.0f / vDirection.y : 0.0f;


		if (vDirection.x < 0) {
			if (vDirection.y < 0) {
				classification = MMP;
			}
			else {
				classification = MPP;
			}
		}
		else {
			if (vDirection.y < 0) {
				classification = PMP;
			}
			else {
				classification = PPP;
			}
		}

	}

	void Init()
	{
		ZeroMemory(this, sizeof(gt2Ray2));
	}


}gt2Ray2;



typedef struct gt2Ray3
{
	CLASSIFICATION classification;		// MMM, MMP, etc.
	gt2Vector3 vOrigin;		// �����N��
	gt2Vector3 vDirection;	// ����
	gt2Vector3 vInver;	// ���������̋t��

public:
	gt2Ray3()
	{
		this->Init();
	}
	gt2Ray3(const gt2Vector3 &vO, const gt2Vector3 &vD)
	{
		this->Make(vO, vD);
	}
	void Make(const gt2Vector3 &vO, const gt2Vector3 &vD)
	{
		vOrigin = vO;
		vDirection = vD;

		vInver.x = vDirection.x != 0.0f ? 1.0f / vDirection.x : 0.0f;
		vInver.y = vDirection.y != 0.0f ? 1.0f / vDirection.y : 0.0f;
		vInver.z = vDirection.z != 0.0f ? 1.0f / vDirection.z : 0.0f;


		if (vDirection.x < 0) {
			if (vDirection.y < 0) {
				if (vDirection.z < 0)
					classification = MMM;
				else
					classification = MMP;
			}
			else {
				if (vDirection.z < 0)
					classification = MPM;
				else
					classification = MPP;
			}
		}
		else {
			if (vDirection.y < 0) {
				if (vDirection.z < 0)
					classification = PMM;
				else
					classification = PMP;
			}
			else {
				if (vDirection.z < 0)
					classification = PPM;
				else
					classification = PPP;
			}
		}

	}

	void Init()
	{
		ZeroMemory(this, sizeof(gt2Ray3));
	}

}gt2Ray3;

