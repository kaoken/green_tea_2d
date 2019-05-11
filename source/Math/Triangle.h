//-----------------------------------------------------------------------------------
// ファイル： gt2Triangle3D.h, gt2Triangle3D.inl
//
// 説　明　：
// 　3要素の3頂点からなる三角形
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

float TriArea2D(float x1, float y1, float x2, float y2, float x3, float y3);
void TriBarycentric(
	const gt2Vector3& a,
	const gt2Vector3& rvB,
	const gt2Vector3& rvC,
	const gt2Vector3& rvP,
	float *pU, float *pV, float *pW
);
bool TestPointTriangle(const gt2Vector3& rPA, const gt2Vector3& rPB, const gt2Vector3& rPC, const gt2Vector3& rP);

gt2Vector3 TriClosestPtPoint(
	const gt2Vector3& rvP,
	const gt2Vector3& a,
	const gt2Vector3& rvB,
	const gt2Vector3& rvC
);

bool TriIntersectSegment(
	bool bRay,
	const gt2Vector3& rvP, const gt2Vector3& rvQ,
	const gt2Vector3& a, const gt2Vector3& rvB, const gt2Vector3& rvC,
	float *pU, float *pV, float *pW, float* pT
);
bool TriIntersectLine(
	const gt2Vector3& rvP, const gt2Vector3& rvQ,
	const gt2Vector3& a, const gt2Vector3& rvB, const gt2Vector3& rvC
);
bool TriIntersectLineCrossingPoin(
	const gt2Vector3& rvP, const gt2Vector3& rvQ,
	const gt2Vector3& a, const gt2Vector3& rvB, const gt2Vector3& rvC,
	gt2Vector3* pvCross
);
bool TriIntersectRayCrossingPoin(
	const gt2Vector3& rvP, const gt2Vector3& rvQ,
	const gt2Vector3& a, const gt2Vector3& rvB, const gt2Vector3& rvC,
	gt2Vector3* pvCross
);




typedef struct gt2Triangle3D
{
	gt2Vector3	vA;
	gt2Vector3	vB;
	gt2Vector3	vC;
public:

	gt2Triangle3D()
	{
		memset((void*)this, 0, sizeof(gt2Triangle3D));
	}
	gt2Triangle3D(const float *pf)
	{
		memcpy((void*)this, (void*)pf, sizeof(gt2Triangle3D));
	}
	gt2Triangle3D(const gt2Vector3 aV[])
	{
		vA = aV[0];
		vB = aV[1];
		vC = aV[2];
	}
	gt2Triangle3D(
			const gt2Vector3& a,
			const gt2Vector3& rvB,
			const gt2Vector3& rvC
		)
	{
		vA = a;
		vB = rvB;
		vC = rvC;
	}

	inline void Barycentric(const gt2Vector3& rvP, float *pU, float *pV, float *pW)
	{
		return TriBarycentric(vA, vB, vC, rvP, pU, pV, pW);
	}
	inline gt2Vector3 ClosestPtPoint(const gt2Vector3& rvP)
	{
		return TriClosestPtPoint(rvP, vA, vB, vC);
	}
	inline bool IntersectSegment(
		bool bRay,
		const gt2Vector3& rvP, const gt2Vector3& rvQ,
		float *pU, float *pV, float *pW, float* pT
	)
	{
		return TriIntersectSegment(
			bRay, rvP, rvQ,
			vA, vB, vC,
			pU, pV, pW, pT
		);
	}
	inline bool IntersectLineCrossingPoin(
		const gt2Vector3& rvP, const gt2Vector3& rvQ,
		gt2Vector3* pvCross
	)
	{
		return TriIntersectLineCrossingPoin(
			rvP, rvQ,
			vA, vB, vC,
			pvCross
		);
	}
	inline bool IntersectRayCrossingPoin(
		const gt2Vector3& rvP, const gt2Vector3& rvQ,
		gt2Vector3* pvCross
	)
	{
		return TriIntersectRayCrossingPoin(
			rvP, rvQ,
			vA, vB, vC,
			pvCross
		);
	}

}gt2Triangle3D;