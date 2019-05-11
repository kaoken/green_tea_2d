//-----------------------------------------------------------------------------------
// ファイル： mcSegment.h, mcSegment.inl
//
// 説　明　：
// 　線分を表す
//   
//　
// 履　歴　：
// 　2007/03/08 Ver.0.1 制作開始
//
//
// 情　報　：
// 　Copyright(c)2006 METAL CUBE All rights reserved worldwide..
// 　
//-----------------------------------------------------------------------------------
#pragma once

#include <Math/vector.h>

// [min, max]の範囲内までnをクランプ
inline float SegmentClamp(float n, float min, float max)
{
	if (n < min) return min;
	if (n > max) return max;
	return n;
}

//-----------------------------------------------------------------------------------
// [ 説明 ] public
//  点cと線分vABの間の距離の平方を返す
// [ 引数 ]
//  pvA	：[in] 基点
//  pvB	：[in] 終点
//  pvC	：[in] 点
// [ 戻り値 ]
//   関数の結果はS1(*pfS)とS2(*pfT)の間の距離の平方
//-----------------------------------------------------------------------------------
template<typename T_VECTOR>
float SqDistPointSegment(const T_VECTOR& a, const T_VECTOR& rvB, const T_VECTOR& rvC)
{
	T_VECTOR vAB = rvB - a, vAC = rvC - a, vBC = rvC - rvB;
	float fE = vAC.Dot(vAB);
	// cがvABの外側に射影される場合を扱う
	if (fE <= 0.0f) return vAC.Dot();
	float fF = vAB.Dot();
	if (fE >= fF) return vBC.Dot();
	// cがvAB上に射影される場合を扱う
	return vAC.Dot() - fE * fE / fF;
}
//-----------------------------------------------------------------------------------
// [ 説明 ] public
//  S1(*pfS)=P1+*pfS*(Q1-P1)およびS2(*pfT)=P2+*pfT*(Q2-P2)の
//  Sおよび*pfTを返す。
// [ 引数 ]
//  pvP1	：[in] 基点1
//  pvQ1	：[in] 終点1
//  pvP2	：[in] 基点2
//  pvQ2	：[in] 終点2
//  pfS		：[out] 0 ≦ s ≦ 1
//  pfT		：[out] 0 ≦ s ≦ 1
//  pvC1	：[out] 最近接点 基点
//  pvC2	：[out] 最近接点 終点
// [ 戻り値 ]
//   関数の結果はS1(*pfS)とS2(*pfT)の間の距離の平方
//-----------------------------------------------------------------------------------
template<typename T_VECTOR>
float ClosestPtSegmentSegment(const T_VECTOR& rvP1, const T_VECTOR& rvQ1, const T_VECTOR& rvP2, const T_VECTOR& rvQ2,
	float *pfS, float *pfT, T_VECTOR *pvC1 = nullptr, T_VECTOR *pvC2 = nullptr)
{
	T_VECTOR vD1 = rvQ1 - rvP1; // 線分S1の方向ベクトル
	T_VECTOR vD2 = rvQ2 - rvP2; // 線分S2の方向ベクトル
	T_VECTOR vR = rvP1 - rvP2;
	float fA = vD1.Dot(); // 線分S1の距離の平方、常に非負
	float fE = vD2.Dot(); // 線分S2の距離の平方、常に非負
	float fF = vD2.Dot(vR);

	// 片方あるいは両方の線分が点に縮退しているかどうかチェック
	if (fA <= 0.0001f && fE <= 0.0001f) {
		// 両方の線分が点に縮退
		*pfS = *pfT = 0.0f;
		if (pvC1) *pvC1 = rvP1;
		if (pvC2) *pvC2 = rvP2;
		return (rvP1 - rvP2).Dot((rvP1 - rvP2));
	}
	if (fA <= 0.0001f) {
		// 最初の線分が点に縮退
		*pfS = 0.0f;
		*pfT = fF / fE; // *pfS = 0 => *pfT = (fB**pfS + fF) / fE = fF / fE
		*pfT = SegmentClamp(*pfT, 0.0f, 1.0f);
	}
	else {
		float fC = vD1.Dot(vR);
		if (fE <= 0.0001f) {
			// 2番目の線分が点に縮退
			*pfT = 0.0f;
			*pfS = SegmentClamp(-fC / fA, 0.0f, 1.0f); // *pfT = 0 => *pfS = (fB**pfT - fC) / fA = -fC / fA
		}
		else {
			// ここから一般的な縮退の場合を開始
			float fB = vD1.Dot(vD2);
			float fDenom = fA*fE - fB*fB; // 常に非負

											// 線分が平行でない場合、L1上のL2に対する最近接点を計算、そして
											// 線分S1に対してクランプ。そうでない場合は任意*pfS(ここでは0)を選択
			if (fDenom != 0.0f) {
				*pfS = SegmentClamp((fB*fF - fC*fE) / fDenom, 0.0f, 1.0f);
			}
			else {
				*pfS = 0.0f;
			}

			//	// L2上のS1(*pfS)に対する最近接点を以下を用いて計算
			//	// *pfT = Dot((P1+D1*(*pfS))-P2,D2) / Dot(D2,D2) = (fB**pfS + fF) / fE
			//	*pfT = (fB*(*pfS) + fF) / fE;

			//	// *pfTが[0,1]の中にあれば終了。そうでなければ*pfTをクランプ、*pfSを*pfTの新しい値に対して以下を用いて再計算
			//	// *pfS = Dot((P2+D2*(*pfT))-P1,D1) / Dot(D1,D1)= (*pfT*fB - fC) / fA
			//	// そして*pfSを[0, 1]に対してクランプ
			//	if (*pfT < 0.0f) {
			//		*pfT = 0.0f;
			//		*pfS = SegmentClamp(-fC / fA, 0.0f, 1.0f);
			//	} else if (*pfT > 1.0f) {
			//		*pfT = 1.0f;
			//		*pfS = SegmentClamp((fB - fC) / fA, 0.0f, 1.0f);
			//	}
			//---------------------------------------------------------
			// 上記のコメント部分の最適化
			float fTnom = fB*(*pfS) + fF;
			if (fTnom < 0.0f) {
				*pfT = 0.0f;
				*pfS = SegmentClamp(-fC / fA, 0.0f, 1.0f);
			}
			else if (fTnom > fE) {
				*pfT = 1.0f;
				*pfS = SegmentClamp((fB - fC) / fA, 0.0f, 1.0f);
			}
			else {
				*pfT = fTnom / fE;
			}
		}

	}
	T_VECTOR vC1 = rvP1 + vD1 * *pfS;
	T_VECTOR vC2 = rvP2 + vD2 * *pfT;
	if (pvC1) *pvC1 = vC1;
	if (pvC2) *pvC2 = vC2;
	return (vC1 - vC2).Dot((vC1 - vC2));
}

struct gt2Segment2
{
	gt2Vector2	vStart;	// 始点
	gt2Vector2	vEnd;	// 終点
public:
	// 長さを取得
	inline float GetHeight() const { return (vEnd - vStart).Length(); };
	// 方向を取得
	inline gt2Vector2* GetDirection(gt2Vector2* pOut) const {
		(vEnd - vStart).Normalize(pOut);
		return pOut;
	};
	inline gt2Vector2* GetCenterPoint(gt2Vector2* pOut) const {
		*pOut = (vEnd + vStart)*0.5f;
		return pOut;
	};
	//-----------------------------------------------------------------------------------
	// [ 説明 ] public
	//  点cと線分vABの間の距離の平方を返す
	// [ 引数 ]
	//  pvC	：[in] 点
	// [ 戻り値 ]
	//   関数の結果はS1(*pfS)とS2(*pfT)の間の距離の平方
	//-----------------------------------------------------------------------------------
	float SqDistPointSegment(const gt2Vector2& rvC) const
	{
		return ::SqDistPointSegment(vStart, vEnd, rvC);
	}

	//-----------------------------------------------------------------------------------
	// [ 説明 ] public
	//  S1(*pfS)=P1+*pfS*(Q1-P1)およびS2(*pfT)=P2+*pfT*(Q2-P2)の
	//  最近接点C1およびC2を計算、Sおよび*pfTを返す。
	// [ 引数 ]
	//  pvPQ2	：[in] 線分
	//  pfS		：[out] 0 ≦ s ≦ 1
	//  pfT		：[out] 0 ≦ s ≦ 1
	//  pvC1	：[out] 最近接点 基点
	//  pvC2	：[out] 最近接点 終点
	// [ 戻り値 ]
	//   関数の結果はS1(*pfS)とS2(*pfT)の間の距離の平方
	//-----------------------------------------------------------------------------------
	float ClosestPtSegmentSegment(
			const gt2Segment2 *pvPQ2,
			float *pfS, float *pfT, gt2Vector2 *pvC1, gt2Vector2 *pvC2) const
	{
		return ::ClosestPtSegmentSegment(vStart, vEnd, pvPQ2->vStart, pvPQ2->vEnd, pfS, pfT, pvC1, pvC2);
	}
	//-----------------------------------------------------------------------------------
	// [ 引数 ]
	//  pvPQ2	：[in] 線分
	//  pfS		：[out] 0 ≦ s ≦ 1
	//  pfT		：[out] 0 ≦ s ≦ 1
	//  pvC		：[out] 最近接点
	//-----------------------------------------------------------------------------------
	float ClosestPtSegmentSegment(const gt2Segment2 *pvPQ2,
			float *pfS, float *pfT, gt2Segment2 *pvC) const
	{
		return ::ClosestPtSegmentSegment(vStart, vEnd, pvPQ2->vStart, pvPQ2->vEnd, pfS, pfT, &pvC->vStart, &pvC->vEnd);
	}
	//-----------------------------------------------------------------------------------
	// [ 引数 ]
	//  pvP2	：[in] 基点2
	//  pvQ2	：[in] 終点2
	//  pfS		：[out] 0 ≦ s ≦ 1
	//  pfT		：[out] 0 ≦ s ≦ 1
	//  pvC1	：[out] 最近接点 基点
	//  pvC2	：[out] 最近接点 終点
	//-----------------------------------------------------------------------------------
	float ClosestPtSegmentSegment(
			const gt2Vector2& rvP2, const gt2Vector2& rvQ2,
			float *pfS, float *pfT, gt2Vector2 *pvC1, gt2Vector2 *pvC2) const
	{
		return ::ClosestPtSegmentSegment(vStart, vEnd, rvP2, rvQ2, pfS, pfT, pvC1, pvC2);
	}


};


struct mcSegment3
{
	gt2Vector3	vStart;	// 始点
	gt2Vector3	vEnd;	// 終点
public:
	mcSegment3() { Init(); }
	mcSegment3(const gt2Vector3 &s, const gt2Vector3 &e) {
		vStart = s;
		vEnd = e;
	}
	// 長さを取得
	inline float GetHeight() const { return (vEnd - vStart).Length(); };
	// 方向を取得
	inline gt2Vector3 GetDirection() const {
		gt2Vector3 out;
		(vEnd - vStart).Normalize(&out);
		return out;
	};
	inline gt2Vector3 GetCenterPoint() const {
		gt2Vector3 out = (vEnd + vStart)*0.5f;
		return out;
	};
	void Init() { vStart.Init(); vEnd.Init(); }
	//-----------------------------------------------------------------------------------
	// [ 説明 ] public
	//  点cと線分vABの間の距離の平方を返す
	// [ 引数 ]
	//  pvC	：[in] 点
	// [ 戻り値 ]
	//   関数の結果はS1(*pfS)とS2(*pfT)の間の距離の平方
	//-----------------------------------------------------------------------------------
	float SqDistPointSegment(const gt2Vector3& rvC) const
	{
		return ::SqDistPointSegment(vStart, vEnd, rvC);
	}

	//-----------------------------------------------------------------------------------
	// [ 説明 ] public
	//  S1(*pfS)=P1+*pfS*(Q1-P1)およびS2(*pfT)=P2+*pfT*(Q2-P2)の
	//  最近接点C1およびC2を計算、Sおよび*pfTを返す。
	// [ 引数 ]
	//  pvPQ2	：[in] 線分
	//  pfS		：[out] 0 ≦ s ≦ 1
	//  pfT		：[out] 0 ≦ s ≦ 1
	//  pvC1	：[out] 最近接点 基点
	//  pvC2	：[out] 最近接点 終点
	// [ 戻り値 ]
	//   関数の結果はS1(*pfS)とS2(*pfT)の間の距離の平方
	//-----------------------------------------------------------------------------------
	float ClosestPtSegmentSegment(
			const mcSegment3 *pvPQ2,
			float *pfS, float *pfT, gt2Vector3 *pvC1, gt2Vector3 *pvC2) const
	{
		return ::ClosestPtSegmentSegment(vStart, vEnd, pvPQ2->vStart, pvPQ2->vEnd, pfS, pfT, pvC1, pvC2);
	}
	//-----------------------------------------------------------------------------------
	// [ 引数 ]
	//  pvPQ2	：[in] 線分
	//  pfS		：[out] 0 ≦ s ≦ 1
	//  pfT		：[out] 0 ≦ s ≦ 1
	//  pvC		：[out] 最近接点
	//-----------------------------------------------------------------------------------
	float ClosestPtSegmentSegment(const mcSegment3 *pvPQ2,
			float *pfS, float *pfT, mcSegment3 *pvC) const
	{
		return ::ClosestPtSegmentSegment(vStart, vEnd, pvPQ2->vStart, pvPQ2->vEnd, pfS, pfT, &pvC->vStart, &pvC->vEnd);
	}
	//-----------------------------------------------------------------------------------
	// [ 引数 ]
	//  pvP2	：[in] 基点2
	//  pvQ2	：[in] 終点2
	//  pfS		：[out] 0 ≦ s ≦ 1
	//  pfT		：[out] 0 ≦ s ≦ 1
	//  pvC1	：[out] 最近接点 基点
	//  pvC2	：[out] 最近接点 終点
	//-----------------------------------------------------------------------------------
	float ClosestPtSegmentSegment(
			const gt2Vector3& rvP2, const gt2Vector3& rvQ2,
			float *pfS, float *pfT, gt2Vector3 *pvC1, gt2Vector3 *pvC2) const
	{
		return ::ClosestPtSegmentSegment(vStart, vEnd, rvP2, rvQ2, pfS, pfT, pvC1, pvC2);
	}
};
