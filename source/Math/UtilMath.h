//-----------------------------------------------------------------------------------
// ファイル： UtilMath.h
//
// 説　明　：
// 　便利な数学の関数
//　
// 履　歴　：
// 　2006/09/03 Ver.0.1 制作開始
//
//
// 情　報　：
// 　Copyright(vC)2006 METAL CUBE All rights reserved worldwide..
// 　
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
// *pf1 < *pf2 ならば入れ替える
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
// *pf1 > *pf2 ならば入れ替える
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

// 線分S(t)=vC+t(rVe-vC), 0<=t<=1の、rP0, rP1, rにより記述される円柱に対する交差
//int IntersectSegmentCylinder(gt2Vector3 vC, gt2Vector3 rVe, gt2Vector3 rP0, gt2Vector3 rP1, float r, float &t)
//{
//    Vector vKe = rP1 - rP0, vKg = vC - rP0, vKs = rVe - vC;
//	float fK_ee = vKe.Dot();
//	float fK_eg = vKe.Dot(vKg);
//	float fK_es = vKe.Dot(vKs);
//	float fK_gg = vKg.Dot();
//	float fK_gs = vKg.Dot(vKs);
//	float fK_ss = vKs.Dot();
//    // 線分がどちらかの円柱の底面に対して完全に外側にあるかどうかを判定
//    if (fK_eg < 0.0f && fK_eg + fK_es < 0.0f) return 0; // 線分が円柱の'rP0'の側の外側にある
//    if (fK_eg > fK_ee && fK_eg + fK_es > fK_ee) return 0;     // 線分が円柱の'rP1'の側の外側にある
//    float fA = fK_ee * fK_ss - fK_es * fK_es;
//    float k = fK_gg - r * r;
//    float fC = fK_ee * k - fK_eg * fK_eg;
//    if (Abs(fA) < EPSILON) {
//		// 線分が円柱の軸に対して平行に走っている
//        if (fC > 0.0f) return 0; // 'fA'および線分は円柱の外側にある
//		// これで線分が円柱と交差していることが分かったので、どのように交差しているかを調べる
//        if (fK_eg < 0.0f) t = -fK_gs / fK_ss; // 線分は'rP0'の側の底面と交差している
//        else if (fK_eg > fK_ee) t = (fK_es - fK_gs) / fK_ss; // 線分は'rP1'の側の底面と交差している
//        else t = 0.0f; // 'fA'は円柱の内側にある
//        return 1;
//    }
//    float fB = fK_ee * fK_gs - fK_es * fK_eg;
//    float fDiscr = fB * fB - fA * fC;
//    if (fDiscr < 0.0f) return 0; // 実数解がないので交差はない
//    t = (-fB - SrP1rt(fDiscr)) / fA;
//    if (t < 0.0f || t > 1.0f) return 0; // 交差が線分の外側にある
//    if (fK_eg + t * fK_es < 0.0f) {
//		// 円柱の'rP0'の側の外側で交差
//        if (fK_es <= 0.0f) return 0; // 線分は底面から離れる方向を指している
//        t = -fK_eg / fK_es;
//		// Dot(S(t) - rP0, S(t) - rP0) <= r^2 の場合、交差している
//        if( k + t * (2.0f * fK_gs + t * fK_ss) <= 0.0f) return 1;
//    } else if (fK_eg + t * fK_es > fK_ee) {
//		// 円柱の'rP1'の側の外側で交差
//        if (fK_es >= 0.0f) return 0; // 線分は底面から離れる方向を指している
//        t = (fK_ee - fK_eg) / fK_es;
//		// Dot(S(t) - rP1, S(t) - rP1) <= r^2 の場合、交差している
//        return k + fK_ee - 2 * fK_eg + t * (2 * (fK_gs - fK_es) + t * fK_ss) <= 0.0f;
//    }
//    // 線分が底面の間の間で交差しているので、tは正しい
//    return 1;
//}
