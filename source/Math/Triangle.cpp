#include <Math/Triangle.h>


#define TRI_EPSIRON	0.00001f
float TriArea2D(float x1, float y1, float x2, float y2, float x3, float y3)
{
	return (x1 - x2)*(y2 - y3) - (x2 - x3)*(y1 - y2);
}
//-----------------------------------------------------------------------------------
// [ 説明 ]
//  重心座標(*pU, *pV, *pW)の計算
//  三角形(a, rvB, rvC)に対する点 rvP
//
// [ 引数 ]
//  a	：[in] 頂点
//  rvB	：[in] 頂点
//  rvC	：[in] 頂点
//  rvP	：[in] 頂点
//  pU	：[out] 重心座標U
//  pV	：[out] 重心座標V
//  pW	：[out] 重心座標W
// [ 戻り値 ]
//  無し
//-----------------------------------------------------------------------------------
void TriBarycentric(
	const gt2Vector3& a,
	const gt2Vector3& rvB,
	const gt2Vector3& rvC,
	const gt2Vector3& rvP,
	float *pU, float *pV, float *pW
)
{
	// 正規化されていない三角形の法線
	gt2Vector3 vM = (rvB - a).Cross(rvC - a);
	// 比率を表す*pU(U)および*pV(V)に対する、分子となる部分と(分子が1である)分母となる部分
	float nu, nv, ood;
	// 射影する平面を決定する絶対値成分
	float x = abs(vM.x), y = abs(vM.y), z = abs(vM.z);

	// 射影が最大となる平面において面積を計算
	if (x >= y && x >= z) {
		// xが最大の場合、yz平面に対して射影
		nu = TriArea2D(rvP.y, rvP.z, rvB.y, rvB.z, rvC.y, rvC.z); // yz平面におけるPBCの面積
		nv = TriArea2D(rvP.y, rvP.z, rvC.y, rvC.z, a.y, a.z); // yz平面におけるPCAの面積
		ood = 1.0f / vM.x;                             // 1/(2*yz平面におけるABCの面積)
	}
	else if (y >= x && y >= z) {
		// yが最大の場合、xz平面に対して射影 
		nu = TriArea2D(rvP.x, rvP.z, rvB.x, rvB.z, rvC.x, rvC.z);
		nv = TriArea2D(rvP.x, rvP.z, rvC.x, rvC.z, a.x, a.z);
		ood = 1.0f / -vM.y;
	}
	else {
		// zが最大の場合、xy平面に対して射影 
		nu = TriArea2D(rvP.x, rvP.y, rvB.x, rvB.y, rvC.x, rvC.y);
		nv = TriArea2D(rvP.x, rvP.y, rvC.x, rvC.y, a.x, a.y);
		ood = 1.0f / vM.z;
	}
	*pU = nu * ood;
	*pV = nv * ood;
	*pW = 1.0f - *pU - *pV;
}
//-----------------------------------------------------------------------------------
// [ 説明 ]
//  三角形(A,B,C)の中に点(P)が含まれるか判定する
//
// [ 引数 ]
//  a	：[in] 頂点
//  rvB	：[in] 頂点
//  rvC	：[in] 頂点
//  rvP	：[in] 頂点
// [ 戻り値 ]
//  含まれている場合trueを返す
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
// [ 説明 ]
//  三角形(A,B,C)から点(P)への最近接点を導き出す
//
// [ 引数 ]
//  a	：[in] 頂点
//  rvB	：[in] 頂点
//  rvC	：[in] 頂点
//  rvP	：[in] 頂点
// [ 戻り値 ]
//  最近接点を返す
//-----------------------------------------------------------------------------------
gt2Vector3 TriClosestPtPoint(const gt2Vector3& rvP, const gt2Vector3& a, const gt2Vector3& rvB, const gt2Vector3& rvC)
{
	// PがAの外側の頂点領域の中にあるかどうかチェック
	gt2Vector3 vAB = rvB - a;
	gt2Vector3 vAC = rvC - a;
	gt2Vector3 vAP = rvP - a;
	float d1 = vAB.Dot(vAP);
	float d2 = vAC.Dot(vAP);
	if (d1 <= 0.0f && d2 <= 0.0f) return a; // 重心座標(1,0,0)

												// PがBの外側の頂点領域の中にあるかどうかチェック
	gt2Vector3 vBP = rvP - rvB;
	float d3 = vAB.Dot(vBP);
	float d4 = vAC.Dot(vBP);
	if (d3 >= 0.0f && d4 <= d3) return rvB; // 重心座標(0,1,0)

											// PがABの辺領域の中にあるかどうかチェックし、あればPのAB上に対する射影を返す
	float vc = d1*d4 - d3*d2;
	if (vc <= 0.0f && d1 >= 0.0f && d3 <= 0.0f) {
		float v = d1 / (d1 - d3);
		return a + v * vAB; // 重心座標(1-v,v,0)
	}

	// PがCの外側の頂点領域の中にあるかどうかチェック
	gt2Vector3 vCP = rvP - rvC;
	float d5 = vAB.Dot(vCP);
	float d6 = vAC.Dot(vCP);
	if (d6 >= 0.0f && d5 <= d6) return rvC; // 重心座標(0,0,1)

											// PがACの辺領域の中にあるかどうかチェックし、あればPのAC上に対する射影を返す
	float vb = d5*d2 - d1*d6;
	if (vb <= 0.0f && d2 >= 0.0f && d6 <= 0.0f) {
		float w = d2 / (d2 - d6);
		return a + w * vAC; // 重心座標(1-w,0,w)
	}

	// PがBCの辺領域の中にあるかどうかチェックし、あればPのBC上に対する射影を返す
	float va = d3*d6 - d5*d4;
	if (va <= 0.0f && (d4 - d3) >= 0.0f && (d5 - d6) >= 0.0f) {
		float w = (d4 - d3) / ((d4 - d3) + (d5 - d6));
		return rvB + w * (rvC - rvB); // 重心座標(0,1-w,w)
	}

	// Pは面領域の中にある。Qをその重心座標(u,v,w)を用いて計算
	float denom = 1.0f / (va + vb + vc);
	float v = vb * denom;
	float w = vc * denom;
	return a + vAB * v + vAC * w; // = urvA + *pVrvB + wrvC, u = va * denom = 1.0f - v - w
}
//-----------------------------------------------------------------------------------
// [ 説明 ]
//  与えられた線分pqおよび三角形abcに対して、線分が三角形と交差しているかどうかを返す
//  交差している場合、交差点の重心座標(u,v,w)も返す
//
// [ 引数 ]
//  rvP	：[in] 頂点 P (光線)
//  rvQ	：[in] 頂点 Q (光線)
//  a	：[in] 頂点 A（三角形）
//  rvB	：[in] 頂点 B（三角形）
//  rvC	：[in] 頂点 C（三角形）
//  pU	：[out] 重心座標U
//  pV	：[out] 重心座標V
//  pW	：[out] 重心座標W
//  pT	：[out] パラメータ
// [ 戻り値 ]
//  最近接点を返す
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

	// 三角形の法線を計算。同じ三角形に対して複数の線分が交差する場合は
	// あらかじめ計算しておくか、あるいはキャッシュしておくことも可能
	gt2Vector3 vN = vAB.Cross(vAC);

	// 分母dを計算。d <= 0の場合、線分は三角形に平行であるか、
	// あるいは三角形から離れていく方向を指しているので、早期に終了
	float d = vQP.Dot(vN);
	if (d <= 0.0f) return false;

	// pqと三角形の平面の交差の値*pTを計算。
	// 0 <= *pTの場合に光線は交差。線分は0 <= *pT <= 1の場合に交差。
	// 交差が三角形を貫通することが分かるまでdによる除算を遅延
	gt2Vector3 vAP = rvP - a;
	*pT = vAP.Dot(vN);
	if (*pT < 0.0f) return false;
	if (!bRay && *pT > d) return false; // 線分に対して。光線に対する判定ではコードのこの行は除外

										// 重心座標の成分を計算し範囲内にあるかどうか判定
	gt2Vector3 vE = vQP.Cross(vAP);
	*pV = vAC.Dot(vE);
	if (*pV < 0.0f || *pV > d) return false;
	*pW = -vAB.Dot(vE);
	if (*pW < 0.0f || *pV + *pW > d) return false;

	// 線分/光線は三角形と交差。遅延した除算を実行し
	// 最後に重心座標の成分を計算
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

	// 三角形の法線を計算。同じ三角形に対して複数の線分が交差する場合は
	// あらかじめ計算しておくか、あるいはキャッシュしておくことも可能
	gt2Vector3 vN = vAB.Cross(vAC);

	// 分母dを計算。d <= 0の場合、線分は三角形に平行であるか、
	// あるいは三角形から離れていく方向を指しているので、早期に終了
	float d = vQP.Dot(vN);
	if (d <= 0.0f) return false;

	// pqと三角形の平面の交差の値*pTを計算。
	// 0 <= *pTの場合に光線は交差。線分は0 <= *pT <= 1の場合に交差。
	// 交差が三角形を貫通することが分かるまでdによる除算を遅延
	gt2Vector3 vAP = rvP - a;
	fT = vAP.Dot(vN);
	if (fT < 0.0f) return false;
	if (fT > d) return false; // 線分に対して。

								// 重心座標の成分を計算し範囲内にあるかどうか判定
	gt2Vector3 vE = vQP.Cross(vAP);
	float v = vAC.Dot(vE);
	if (v < 0.0f || v > d) return false;
	float fW = -vAB.Dot(vE);
	if (fW < 0.0f || v + fW > d) return false;

	return true;
}

//-----------------------------------------------------------------------------------
// [ 説明 ]
//  与えられた直線（P,Q)および反時計回りの三角形(A,B,C)に対して、
//  直線が三角形を貫通しているかどうかを返す
//  貫通している場合、交差点pvCrossを返す
//
// [ 引数 ]
//  rvP	：[in] 頂点 P (直線)
//  rvQ	：[in] 頂点 Q (直線)
//  a	：[in] 頂点 A（三角形）
//  rvB	：[in] 頂点 B（三角形）
//  rvC	：[in] 頂点 C（三角形）
//  pvCross	：[out] 交差点
// [ 戻り値 ]
//  交差していた場合はtrueを返す。
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
// [ 説明 ]
//  与えられた光線（P,Q)および反時計回りの三角形(A,B,C)に対して、
//  光線三角形を貫通しているかどうかを返す
//  貫通している場合、交差点pvCrossを返す
//
// [ 引数 ]
//  rvP	：[in] 頂点 P (直線)
//  rvQ	：[in] 頂点 Q (直線)
//  a	：[in] 頂点 A（三角形）
//  rvB	：[in] 頂点 B（三角形）
//  rvC	：[in] 頂点 C（三角形）
//  pvCross	：[out] 交差点
// [ 戻り値 ]
//  交差していた場合はtrueを返す。
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