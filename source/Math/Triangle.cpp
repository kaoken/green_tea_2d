#include <Math/Triangle.h>


#define TRI_EPSIRON	0.00001f
float TriArea2D(float x1, float y1, float x2, float y2, float x3, float y3)
{
	return (x1 - x2)*(y2 - y3) - (x2 - x3)*(y1 - y2);
}
//-----------------------------------------------------------------------------------
// [ ���� ]
//  �d�S���W(*pU, *pV, *pW)�̌v�Z
//  �O�p�`(a, rvB, rvC)�ɑ΂���_ rvP
//
// [ ���� ]
//  a	�F[in] ���_
//  rvB	�F[in] ���_
//  rvC	�F[in] ���_
//  rvP	�F[in] ���_
//  pU	�F[out] �d�S���WU
//  pV	�F[out] �d�S���WV
//  pW	�F[out] �d�S���WW
// [ �߂�l ]
//  ����
//-----------------------------------------------------------------------------------
void TriBarycentric(
	const gt2Vector3& a,
	const gt2Vector3& rvB,
	const gt2Vector3& rvC,
	const gt2Vector3& rvP,
	float *pU, float *pV, float *pW
)
{
	// ���K������Ă��Ȃ��O�p�`�̖@��
	gt2Vector3 vM = (rvB - a).Cross(rvC - a);
	// �䗦��\��*pU(U)�����*pV(V)�ɑ΂���A���q�ƂȂ镔����(���q��1�ł���)����ƂȂ镔��
	float nu, nv, ood;
	// �ˉe���镽�ʂ����肷���Βl����
	float x = abs(vM.x), y = abs(vM.y), z = abs(vM.z);

	// �ˉe���ő�ƂȂ镽�ʂɂ����Ėʐς��v�Z
	if (x >= y && x >= z) {
		// x���ő�̏ꍇ�Ayz���ʂɑ΂��Ďˉe
		nu = TriArea2D(rvP.y, rvP.z, rvB.y, rvB.z, rvC.y, rvC.z); // yz���ʂɂ�����PBC�̖ʐ�
		nv = TriArea2D(rvP.y, rvP.z, rvC.y, rvC.z, a.y, a.z); // yz���ʂɂ�����PCA�̖ʐ�
		ood = 1.0f / vM.x;                             // 1/(2*yz���ʂɂ�����ABC�̖ʐ�)
	}
	else if (y >= x && y >= z) {
		// y���ő�̏ꍇ�Axz���ʂɑ΂��Ďˉe 
		nu = TriArea2D(rvP.x, rvP.z, rvB.x, rvB.z, rvC.x, rvC.z);
		nv = TriArea2D(rvP.x, rvP.z, rvC.x, rvC.z, a.x, a.z);
		ood = 1.0f / -vM.y;
	}
	else {
		// z���ő�̏ꍇ�Axy���ʂɑ΂��Ďˉe 
		nu = TriArea2D(rvP.x, rvP.y, rvB.x, rvB.y, rvC.x, rvC.y);
		nv = TriArea2D(rvP.x, rvP.y, rvC.x, rvC.y, a.x, a.y);
		ood = 1.0f / vM.z;
	}
	*pU = nu * ood;
	*pV = nv * ood;
	*pW = 1.0f - *pU - *pV;
}
//-----------------------------------------------------------------------------------
// [ ���� ]
//  �O�p�`(A,B,C)�̒��ɓ_(P)���܂܂�邩���肷��
//
// [ ���� ]
//  a	�F[in] ���_
//  rvB	�F[in] ���_
//  rvC	�F[in] ���_
//  rvP	�F[in] ���_
// [ �߂�l ]
//  �܂܂�Ă���ꍇtrue��Ԃ�
//-----------------------------------------------------------------------------------
bool TestPointTriangle(const gt2Vector3& rPA, const gt2Vector3& rPB, const gt2Vector3& rPC, const gt2Vector3& rP)
{
	/*	gt2Vector3 e10=*rPB-*rPA;
	gt2Vector3 e20=*rPC-*rPA;
	float a = e10.Dot(e10);
	float b = e10.Dot(e20);
	float c = e20.Dot(e20);
	float ac_bb=(a*c)-(b*b);
	gt2Vector3 vp(rP->x-rPA->x, rP->y-rPA->y, rP->z-rPA->z);
	float d = vp.Dot(e10);
	float e = vp.Dot(e20);
	float x = (d*c)-(e*b);
	float y = (e*a)-(d*b);
	float z = x+y-ac_bb;
	return (( N_CAST(uint32_t&, z)& ~(N_CAST(uint32_t&, x)|N_CAST(uint32_t&, y)) ) & 0x80000000) > 0;*/

	float u, v, w;
	TriBarycentric(rPA, rPB, rPC, rP, &u, &v, &w);
	return v >= 0.0f && w >= 0.0f && (v + w) <= 1.0f;
}
//-----------------------------------------------------------------------------------
// [ ���� ]
//  �O�p�`(A,B,C)����_(P)�ւ̍ŋߐړ_�𓱂��o��
//
// [ ���� ]
//  a	�F[in] ���_
//  rvB	�F[in] ���_
//  rvC	�F[in] ���_
//  rvP	�F[in] ���_
// [ �߂�l ]
//  �ŋߐړ_��Ԃ�
//-----------------------------------------------------------------------------------
gt2Vector3 TriClosestPtPoint(const gt2Vector3& rvP, const gt2Vector3& a, const gt2Vector3& rvB, const gt2Vector3& rvC)
{
	// P��A�̊O���̒��_�̈�̒��ɂ��邩�ǂ����`�F�b�N
	gt2Vector3 vAB = rvB - a;
	gt2Vector3 vAC = rvC - a;
	gt2Vector3 vAP = rvP - a;
	float d1 = vAB.Dot(vAP);
	float d2 = vAC.Dot(vAP);
	if (d1 <= 0.0f && d2 <= 0.0f) return a; // �d�S���W(1,0,0)

												// P��B�̊O���̒��_�̈�̒��ɂ��邩�ǂ����`�F�b�N
	gt2Vector3 vBP = rvP - rvB;
	float d3 = vAB.Dot(vBP);
	float d4 = vAC.Dot(vBP);
	if (d3 >= 0.0f && d4 <= d3) return rvB; // �d�S���W(0,1,0)

											// P��AB�̕ӗ̈�̒��ɂ��邩�ǂ����`�F�b�N���A�����P��AB��ɑ΂���ˉe��Ԃ�
	float vc = d1*d4 - d3*d2;
	if (vc <= 0.0f && d1 >= 0.0f && d3 <= 0.0f) {
		float v = d1 / (d1 - d3);
		return a + v * vAB; // �d�S���W(1-v,v,0)
	}

	// P��C�̊O���̒��_�̈�̒��ɂ��邩�ǂ����`�F�b�N
	gt2Vector3 vCP = rvP - rvC;
	float d5 = vAB.Dot(vCP);
	float d6 = vAC.Dot(vCP);
	if (d6 >= 0.0f && d5 <= d6) return rvC; // �d�S���W(0,0,1)

											// P��AC�̕ӗ̈�̒��ɂ��邩�ǂ����`�F�b�N���A�����P��AC��ɑ΂���ˉe��Ԃ�
	float vb = d5*d2 - d1*d6;
	if (vb <= 0.0f && d2 >= 0.0f && d6 <= 0.0f) {
		float w = d2 / (d2 - d6);
		return a + w * vAC; // �d�S���W(1-w,0,w)
	}

	// P��BC�̕ӗ̈�̒��ɂ��邩�ǂ����`�F�b�N���A�����P��BC��ɑ΂���ˉe��Ԃ�
	float va = d3*d6 - d5*d4;
	if (va <= 0.0f && (d4 - d3) >= 0.0f && (d5 - d6) >= 0.0f) {
		float w = (d4 - d3) / ((d4 - d3) + (d5 - d6));
		return rvB + w * (rvC - rvB); // �d�S���W(0,1-w,w)
	}

	// P�͖ʗ̈�̒��ɂ���BQ�����̏d�S���W(u,v,w)��p���Čv�Z
	float denom = 1.0f / (va + vb + vc);
	float v = vb * denom;
	float w = vc * denom;
	return a + vAB * v + vAC * w; // = urvA + *pVrvB + wrvC, u = va * denom = 1.0f - v - w
}
//-----------------------------------------------------------------------------------
// [ ���� ]
//  �^����ꂽ����pq����юO�p�`abc�ɑ΂��āA�������O�p�`�ƌ������Ă��邩�ǂ�����Ԃ�
//  �������Ă���ꍇ�A�����_�̏d�S���W(u,v,w)���Ԃ�
//
// [ ���� ]
//  rvP	�F[in] ���_ P (����)
//  rvQ	�F[in] ���_ Q (����)
//  a	�F[in] ���_ A�i�O�p�`�j
//  rvB	�F[in] ���_ B�i�O�p�`�j
//  rvC	�F[in] ���_ C�i�O�p�`�j
//  pU	�F[out] �d�S���WU
//  pV	�F[out] �d�S���WV
//  pW	�F[out] �d�S���WW
//  pT	�F[out] �p�����[�^
// [ �߂�l ]
//  �ŋߐړ_��Ԃ�
//-----------------------------------------------------------------------------------
bool TriIntersectSegment(
	bool bRay,
	const gt2Vector3& rvP, const gt2Vector3& rvQ,
	const gt2Vector3& a, const gt2Vector3& rvB, const gt2Vector3& rvC,
	float *pU, float *pV, float *pW, float* pT
)
{
	gt2Vector3 vAB = rvB - a;
	gt2Vector3 vAC = rvC - a;
	gt2Vector3 vQP = rvP - rvQ;

	// �O�p�`�̖@�����v�Z�B�����O�p�`�ɑ΂��ĕ����̐�������������ꍇ��
	// ���炩���ߌv�Z���Ă������A���邢�̓L���b�V�����Ă������Ƃ��\
	gt2Vector3 vN = vAB.Cross(vAC);

	// ����d���v�Z�Bd <= 0�̏ꍇ�A�����͎O�p�`�ɕ��s�ł��邩�A
	// ���邢�͎O�p�`���痣��Ă����������w���Ă���̂ŁA�����ɏI��
	float d = vQP.Dot(vN);
	if (d <= 0.0f) return false;

	// pq�ƎO�p�`�̕��ʂ̌����̒l*pT���v�Z�B
	// 0 <= *pT�̏ꍇ�Ɍ����͌����B������0 <= *pT <= 1�̏ꍇ�Ɍ����B
	// �������O�p�`���ђʂ��邱�Ƃ�������܂�d�ɂ�鏜�Z��x��
	gt2Vector3 vAP = rvP - a;
	*pT = vAP.Dot(vN);
	if (*pT < 0.0f) return false;
	if (!bRay && *pT > d) return false; // �����ɑ΂��āB�����ɑ΂��锻��ł̓R�[�h�̂��̍s�͏��O

										// �d�S���W�̐������v�Z���͈͓��ɂ��邩�ǂ�������
	gt2Vector3 vE = vQP.Cross(vAP);
	*pV = vAC.Dot(vE);
	if (*pV < 0.0f || *pV > d) return false;
	*pW = -vAB.Dot(vE);
	if (*pW < 0.0f || *pV + *pW > d) return false;

	// ����/�����͎O�p�`�ƌ����B�x���������Z�����s��
	// �Ō�ɏd�S���W�̐������v�Z
	float ood = 1.0f / d;
	*pT *= ood;
	*pV *= ood;
	*pW *= ood;
	*pU = 1.0f - *pV - *pW;

	return true;
}
bool TriIntersectLine(
	const gt2Vector3& rvP, const gt2Vector3& rvQ,
	const gt2Vector3& a, const gt2Vector3& rvB, const gt2Vector3& rvC
)
{
	float fT;
	gt2Vector3 vAB = rvB - a;
	gt2Vector3 vAC = rvC - a;
	gt2Vector3 vQP = rvP - rvQ;

	// �O�p�`�̖@�����v�Z�B�����O�p�`�ɑ΂��ĕ����̐�������������ꍇ��
	// ���炩���ߌv�Z���Ă������A���邢�̓L���b�V�����Ă������Ƃ��\
	gt2Vector3 vN = vAB.Cross(vAC);

	// ����d���v�Z�Bd <= 0�̏ꍇ�A�����͎O�p�`�ɕ��s�ł��邩�A
	// ���邢�͎O�p�`���痣��Ă����������w���Ă���̂ŁA�����ɏI��
	float d = vQP.Dot(vN);
	if (d <= 0.0f) return false;

	// pq�ƎO�p�`�̕��ʂ̌����̒l*pT���v�Z�B
	// 0 <= *pT�̏ꍇ�Ɍ����͌����B������0 <= *pT <= 1�̏ꍇ�Ɍ����B
	// �������O�p�`���ђʂ��邱�Ƃ�������܂�d�ɂ�鏜�Z��x��
	gt2Vector3 vAP = rvP - a;
	fT = vAP.Dot(vN);
	if (fT < 0.0f) return false;
	if (fT > d) return false; // �����ɑ΂��āB

								// �d�S���W�̐������v�Z���͈͓��ɂ��邩�ǂ�������
	gt2Vector3 vE = vQP.Cross(vAP);
	float v = vAC.Dot(vE);
	if (v < 0.0f || v > d) return false;
	float fW = -vAB.Dot(vE);
	if (fW < 0.0f || v + fW > d) return false;

	return true;
}

//-----------------------------------------------------------------------------------
// [ ���� ]
//  �^����ꂽ�����iP,Q)����є����v���̎O�p�`(A,B,C)�ɑ΂��āA
//  �������O�p�`���ђʂ��Ă��邩�ǂ�����Ԃ�
//  �ђʂ��Ă���ꍇ�A�����_pvCross��Ԃ�
//
// [ ���� ]
//  rvP	�F[in] ���_ P (����)
//  rvQ	�F[in] ���_ Q (����)
//  a	�F[in] ���_ A�i�O�p�`�j
//  rvB	�F[in] ���_ B�i�O�p�`�j
//  rvC	�F[in] ���_ C�i�O�p�`�j
//  pvCross	�F[out] �����_
// [ �߂�l ]
//  �������Ă����ꍇ��true��Ԃ��B
//-----------------------------------------------------------------------------------
bool TriIntersectLineCrossingPoin(
	const gt2Vector3& rvP, const gt2Vector3& rvQ,
	const gt2Vector3& a, const gt2Vector3& rvB, const gt2Vector3& rvC,
	gt2Vector3* pvCross
)
{
	float u, v, fW, fT;


	if (TriIntersectSegment(false, rvP, rvQ, a, rvB, rvC, &u, &v, &fW, &fT)) {
		*pvCross = a * u + rvB * v + rvC * fW;
		return true;
	}
	return false;
}

//-----------------------------------------------------------------------------------
// [ ���� ]
//  �^����ꂽ�����iP,Q)����є����v���̎O�p�`(A,B,C)�ɑ΂��āA
//  �����O�p�`���ђʂ��Ă��邩�ǂ�����Ԃ�
//  �ђʂ��Ă���ꍇ�A�����_pvCross��Ԃ�
//
// [ ���� ]
//  rvP	�F[in] ���_ P (����)
//  rvQ	�F[in] ���_ Q (����)
//  a	�F[in] ���_ A�i�O�p�`�j
//  rvB	�F[in] ���_ B�i�O�p�`�j
//  rvC	�F[in] ���_ C�i�O�p�`�j
//  pvCross	�F[out] �����_
// [ �߂�l ]
//  �������Ă����ꍇ��true��Ԃ��B
//-----------------------------------------------------------------------------------
bool TryIntersectRayCrossingPoin(
	const gt2Vector3& rvP, const gt2Vector3& rvQ,
	const gt2Vector3& a, const gt2Vector3& rvB, const gt2Vector3& rvC,
	gt2Vector3* pvCross
)
{
	bool bRet;
	float u, v, fW, fT;

	bRet = TriIntersectSegment(true, rvP, rvQ, a, rvB, rvC, &u, &v, &fW, &fT);
	if (bRet || (fT >= 0.0f && fT <= 1.0f)) {
		*pvCross = rvP + fT * (rvQ - rvP);
		return true;
	}
	return false;
}