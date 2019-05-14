#include "Cylinder.h"


#define CEY_EPSIRON	0.00001f

// ����S(*pfT)=vSA+*pfT(vSB-vSA), 0<=*pfT<=1�́AvP, vQ, fR�ɂ��L�q�����~���ɑ΂������
int IntersectSegmentCylinder(gt2Vector3 vSA, gt2Vector3 vSB, gt2Vector3 vP, gt2Vector3 vQ, float fR, float *pfT)
{
	gt2Vector3 vD = vQ - vP, vM = vSA - vP, vN = vSB - vSA;
	float fMD = vD.Dot(vM);
	float fND = vD.Dot(vN);
	float fDD = vD.Dot(vD);

	// �������ǂ��炩�̉~���̒�ʂɑ΂��Ċ��S�ɊO���ɂ��邩�ǂ����𔻒�
	if (fMD < 0.0f && fMD + fND < 0.0f) return 0; // �������~����'vP'�̑��̊O���ɂ���
	if (fMD > fDD && fMD + fND > fDD) return 0;     // �������~����'vQ'�̑��̊O���ɂ���

	float fNN = vN.Dot();
	float fMN = vN.Dot(vM);
	float fA = fDD * fNN - fND * fND;
	float fK = vM.Dot() - fR * fR;
	float fC = fDD * fK - fMD * fMD;

	if (fabs(fA) < CEY_EPSIRON) {
		// �������~���̎��ɑ΂��ĕ��s�ɑ����Ă���
		if (fC > 0.0f) return 0; // 'fA'����ѐ����͉~���̊O���ɂ���
									// ����Ő������~���ƌ������Ă��邱�Ƃ����������̂ŁA�ǂ̂悤�Ɍ������Ă��邩�𒲂ׂ�
		if (fMD < 0.0f) *pfT = -fMN / fNN; // ������'vP'�̑��̒�ʂƌ������Ă���
		else if (fMD > fDD) *pfT = (fND - fMN) / fNN; // ������'vQ'�̑��̒�ʂƌ������Ă���
		else *pfT = 0.0f; // 'fA'�͉~���̓����ɂ���
		return 1;
	}
	float fB = fDD * fMN - fND * fMD;
	float fDiscr = fB * fB - fA * fC;
	if (fDiscr < 0.0f) return 0; // ���������Ȃ��̂Ō����͂Ȃ�
	float fT0;
	fT0 = *pfT = (-fB - sqrt(fDiscr)) / fA;

	if (fMD + *pfT * fND < 0.0f) {
		// �~����'vP'�̑��̊O���Ō���
		if (fND <= 0.0f) return 0; // �����͒�ʂ��痣���������w���Ă���
		*pfT = -fMD / fND;
		// Dot(S(*pfT) - vP, S(*pfT) - vP) <= fR^2 �̏ꍇ�A�������Ă���
		if (fK + *pfT * (2.0f * fMN + *pfT * fNN) <= 0.0f) return 1;
	}
	else if (fMD + *pfT * fND > fDD) {
		// �~����'vQ'�̑��̊O���Ō���
		if (fND >= 0.0f) return 0; // �����͒�ʂ��痣���������w���Ă���
		*pfT = (fDD - fMD) / fND;
		// Dot(S(*pfT) - vQ, S(*pfT) - vQ) <= fR^2 �̏ꍇ�A�������Ă���
		if (fK + fDD - 2.0f * fMD + *pfT * (2.0f * (fMN - fND) + *pfT * fNN) <= 0.0f) return 1;
	}
	*pfT = fT0;
	// �Z�O�����g���G���h�L���b�v�Ԃ̉~���ƌ�������ꍇ�A�����B
	return *pfT < 0.0f || *pfT > 1.0f;
}
//-----------------------------------------------------------------------------------
// [ ���� ] public
//  ���ʂƉ~�����Փ˂��Ă����ꍇtrue��Ԃ�
//
// [ ���� ]
//  rPlane		�F[in] gt2Plane3
//  cylinder	�F[in] gt2Cylinder
//  pfT			�F[out] 
// [ �߂�l ]
//  ���������ꍇ�� S_OK��Ԃ�
//-----------------------------------------------------------------------------------
bool GT2PlaneCylinder(const gt2Plane3& rPlane, const gt2Cylinder &cylinder, float *pfT)
{
	float fSDist, fAbsNdW, fRoot, fCHeight;
	// �V�����_��̈ʒu�̕����t������Dot(N,X)-d�̒[���v�Z
	// ���L������ɂ�����
	//   min = ((N�EC)-d) - r*sqrt(1-(N�EW)^2) - (h/2)*|(N�EW)|
	//   max = ((N�EC)-d) + r*sqrt(1-(N�EW)^2) + (h/2)*|(N�EW)|
	fCHeight = cylinder.GetHeight();
	fSDist = rPlane.DistanceTo(cylinder.segment.vStart);
	fAbsNdW = fabsf(rPlane.vNormal.Dot(cylinder.segment.GetDirection()));
	fRoot = sqrtf(fabsf(1.0f - fAbsNdW*fAbsNdW));
	*pfT = cylinder.r*fRoot + 0.5f*fCHeight*fAbsNdW;

	// 0���Ԋu�ɂ���ꍇ�̂݁A������������ [min,max]
	return fabsf(fSDist) <= *pfT;
	// max <= 0 �ꍇ�̎��̂�
	//return fSDist + (*pfT) <= 0.0f;
}
