//-----------------------------------------------------------------------------------
// �t�@�C���F UtilMath.h
//
// ���@���@�F
// �@�֗��Ȑ��w�̊֐�
//�@
// ���@���@�F
// �@2006/09/03 Ver.0.1 ����J�n
//
//
// ��@��@�F
// �@Copyright(vC)2006 METAL CUBE All rights reserved worldwide..
// �@
//-----------------------------------------------------------------------------------
#pragma once

#include <Core/greenTea2D.h>
#include <Math/vector.h>
#include <Math/plane.h>

/*
int MATH3DLineOrient(gt2Vector3 vA, gt2Vector3 vB, gt2Vector3 vC)
{
	//            |Ax Ab Ac 1|
	// f(vA,vB,vC) = |Bx Bb Bc 1|
	//            |Cx Cb Cc 1|
	//
	return 1;
}*/
void Math3DBarycentric(gt2Vector3 vA, gt2Vector3 vB, gt2Vector3 vC,
	gt2Vector3 vP, gt2Vector3 *pvCenter);
float MathSqDistPointSegment(const gt2Vector3 &vA, const gt2Vector3 &vB, const gt2Vector3 &vC);
float MathClosestPtSegmentSegment(
	const gt2Vector3 &rP1, const gt2Vector3 &rQ1, const gt2Vector3 &rP2, const gt2Vector3 &rQ2,
	float &s, float &t, gt2Vector3 &rC1, gt2Vector3 &rC2, const float fEPSILON = 0.0f
);
bool FindLowestRootInInterval(float fA, float fB, float fC, float *pTime);
//
// *pf1 < *pf2 �Ȃ�Γ���ւ���
inline int fF1MinSwap(float *pf1, float *pf2)
{
	if (*pf1 < *pf2) {
		float tmp = *pf1;
		*pf1 = *pf2;
		*pf2 = tmp;
		return 1;
	}
	return 0;
}
// *pf1 > *pf2 �Ȃ�Γ���ւ���
inline int fF1MaxSwap(float *pf1, float *pf2)
{
	if (*pf1 > *pf2) {
		float tmp = *pf1;
		*pf1 = *pf2;
		*pf2 = tmp;
		return 1;
	}
	return 0;
}
void RandInit(uint32_t u);
void RandInitNowTime();
void RandInitDevice();
int RandInt();
int RandRangeInt(int nMin, int nMax);
float RandFloat();
float RandRangeFloat(float a, float b);
double RandDouble();
double RandRangeDouble(double a, double b);

// ����S(t)=vC+t(rVe-vC), 0<=t<=1�́ArP0, rP1, r�ɂ��L�q�����~���ɑ΂������
//int IntersectSegmentCylinder(gt2Vector3 vC, gt2Vector3 rVe, gt2Vector3 rP0, gt2Vector3 rP1, float r, float &t)
//{
//    Vector vKe = rP1 - rP0, vKg = vC - rP0, vKs = rVe - vC;
//	float fK_ee = vKe.Dot();
//	float fK_eg = vKe.Dot(vKg);
//	float fK_es = vKe.Dot(vKs);
//	float fK_gg = vKg.Dot();
//	float fK_gs = vKg.Dot(vKs);
//	float fK_ss = vKs.Dot();
//    // �������ǂ��炩�̉~���̒�ʂɑ΂��Ċ��S�ɊO���ɂ��邩�ǂ����𔻒�
//    if (fK_eg < 0.0f && fK_eg + fK_es < 0.0f) return 0; // �������~����'rP0'�̑��̊O���ɂ���
//    if (fK_eg > fK_ee && fK_eg + fK_es > fK_ee) return 0;     // �������~����'rP1'�̑��̊O���ɂ���
//    float fA = fK_ee * fK_ss - fK_es * fK_es;
//    float k = fK_gg - r * r;
//    float fC = fK_ee * k - fK_eg * fK_eg;
//    if (Abs(fA) < EPSILON) {
//		// �������~���̎��ɑ΂��ĕ��s�ɑ����Ă���
//        if (fC > 0.0f) return 0; // 'fA'����ѐ����͉~���̊O���ɂ���
//		// ����Ő������~���ƌ������Ă��邱�Ƃ����������̂ŁA�ǂ̂悤�Ɍ������Ă��邩�𒲂ׂ�
//        if (fK_eg < 0.0f) t = -fK_gs / fK_ss; // ������'rP0'�̑��̒�ʂƌ������Ă���
//        else if (fK_eg > fK_ee) t = (fK_es - fK_gs) / fK_ss; // ������'rP1'�̑��̒�ʂƌ������Ă���
//        else t = 0.0f; // 'fA'�͉~���̓����ɂ���
//        return 1;
//    }
//    float fB = fK_ee * fK_gs - fK_es * fK_eg;
//    float fDiscr = fB * fB - fA * fC;
//    if (fDiscr < 0.0f) return 0; // ���������Ȃ��̂Ō����͂Ȃ�
//    t = (-fB - SrP1rt(fDiscr)) / fA;
//    if (t < 0.0f || t > 1.0f) return 0; // �����������̊O���ɂ���
//    if (fK_eg + t * fK_es < 0.0f) {
//		// �~����'rP0'�̑��̊O���Ō���
//        if (fK_es <= 0.0f) return 0; // �����͒�ʂ��痣���������w���Ă���
//        t = -fK_eg / fK_es;
//		// Dot(S(t) - rP0, S(t) - rP0) <= r^2 �̏ꍇ�A�������Ă���
//        if( k + t * (2.0f * fK_gs + t * fK_ss) <= 0.0f) return 1;
//    } else if (fK_eg + t * fK_es > fK_ee) {
//		// �~����'rP1'�̑��̊O���Ō���
//        if (fK_es >= 0.0f) return 0; // �����͒�ʂ��痣���������w���Ă���
//        t = (fK_ee - fK_eg) / fK_es;
//		// Dot(S(t) - rP1, S(t) - rP1) <= r^2 �̏ꍇ�A�������Ă���
//        return k + fK_ee - 2 * fK_eg + t * (2 * (fK_gs - fK_es) + t * fK_ss) <= 0.0f;
//    }
//    // ��������ʂ̊Ԃ̊ԂŌ������Ă���̂ŁAt�͐�����
//    return 1;
//}
