#include "Cylinder.h"


#define CEY_EPSIRON	0.00001f

// 線分S(*pfT)=vSA+*pfT(vSB-vSA), 0<=*pfT<=1の、vP, vQ, fRにより記述される円柱に対する交差
int IntersectSegmentCylinder(gt2Vector3 vSA, gt2Vector3 vSB, gt2Vector3 vP, gt2Vector3 vQ, float fR, float *pfT)
{
	gt2Vector3 vD = vQ - vP, vM = vSA - vP, vN = vSB - vSA;
	float fMD = vD.Dot(vM);
	float fND = vD.Dot(vN);
	float fDD = vD.Dot(vD);

	// 線分がどちらかの円柱の底面に対して完全に外側にあるかどうかを判定
	if (fMD < 0.0f && fMD + fND < 0.0f) return 0; // 線分が円柱の'vP'の側の外側にある
	if (fMD > fDD && fMD + fND > fDD) return 0;     // 線分が円柱の'vQ'の側の外側にある

	float fNN = vN.Dot();
	float fMN = vN.Dot(vM);
	float fA = fDD * fNN - fND * fND;
	float fK = vM.Dot() - fR * fR;
	float fC = fDD * fK - fMD * fMD;

	if (fabs(fA) < CEY_EPSIRON) {
		// 線分が円柱の軸に対して平行に走っている
		if (fC > 0.0f) return 0; // 'fA'および線分は円柱の外側にある
									// これで線分が円柱と交差していることが分かったので、どのように交差しているかを調べる
		if (fMD < 0.0f) *pfT = -fMN / fNN; // 線分は'vP'の側の底面と交差している
		else if (fMD > fDD) *pfT = (fND - fMN) / fNN; // 線分は'vQ'の側の底面と交差している
		else *pfT = 0.0f; // 'fA'は円柱の内側にある
		return 1;
	}
	float fB = fDD * fMN - fND * fMD;
	float fDiscr = fB * fB - fA * fC;
	if (fDiscr < 0.0f) return 0; // 実数解がないので交差はない
	float fT0;
	fT0 = *pfT = (-fB - sqrt(fDiscr)) / fA;

	if (fMD + *pfT * fND < 0.0f) {
		// 円柱の'vP'の側の外側で交差
		if (fND <= 0.0f) return 0; // 線分は底面から離れる方向を指している
		*pfT = -fMD / fND;
		// Dot(S(*pfT) - vP, S(*pfT) - vP) <= fR^2 の場合、交差している
		if (fK + *pfT * (2.0f * fMN + *pfT * fNN) <= 0.0f) return 1;
	}
	else if (fMD + *pfT * fND > fDD) {
		// 円柱の'vQ'の側の外側で交差
		if (fND >= 0.0f) return 0; // 線分は底面から離れる方向を指している
		*pfT = (fDD - fMD) / fND;
		// Dot(S(*pfT) - vQ, S(*pfT) - vQ) <= fR^2 の場合、交差している
		if (fK + fDD - 2.0f * fMD + *pfT * (2.0f * (fMN - fND) + *pfT * fNN) <= 0.0f) return 1;
	}
	*pfT = fT0;
	// セグメントがエンドキャップ間の円柱と交差する場合、交差。
	return *pfT < 0.0f || *pfT > 1.0f;
}
//-----------------------------------------------------------------------------------
// [ 説明 ] public
//  平面と円柱が衝突していた場合trueを返す
//
// [ 引数 ]
//  rPlane		：[in] gt2Plane3
//  cylinder	：[in] gt2Cylinder
//  pfT			：[out] 
// [ 戻り値 ]
//  成功した場合は S_OKを返す
//-----------------------------------------------------------------------------------
bool GT2PlaneCylinder(const gt2Plane3& rPlane, const gt2Cylinder &cylinder, float *pfT)
{
	float fSDist, fAbsNdW, fRoot, fCHeight;
	// シリンダ上の位置の符号付距離のDot(N,X)-dの端を計算
	// 下記がそれにあたる
	//   min = ((N・C)-d) - r*sqrt(1-(N・W)^2) - (h/2)*|(N・W)|
	//   max = ((N・C)-d) + r*sqrt(1-(N・W)^2) + (h/2)*|(N・W)|
	fCHeight = cylinder.GetHeight();
	fSDist = rPlane.DistanceTo(cylinder.segment.vStart);
	fAbsNdW = fabsf(rPlane.vNormal.Dot(cylinder.segment.GetDirection()));
	fRoot = sqrtf(fabsf(1.0f - fAbsNdW*fAbsNdW));
	*pfT = cylinder.r*fRoot + 0.5f*fCHeight*fAbsNdW;

	// 0が間隔にある場合のみ、交差が生じる [min,max]
	return fabsf(fSDist) <= *pfT;
	// max <= 0 場合の時のみ
	//return fSDist + (*pfT) <= 0.0f;
}
