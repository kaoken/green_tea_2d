/*! @file  OBB.h
* @brief OBB関連
* @author kaoken
* @date 2014/03/19 作成開始
*/

#pragma once


#include <Math/matrix.h>
#include <Math/Circle.h>

struct gt2OBB3D;

float MCComputeBestFitOBB(
	uint32_t vertexCount,
	void *pv,
	uint32_t pointerSrid,
	gt2OBB3D *pOBB
	);


//---------------------------------------
//! @brief OBB2D(Oriented Bounding Box)
//---------------------------------------
// 領域 R = { x | x = c+r*u[0]+s*u[1] }, |r|<=e.v[0], |s|<=e.v[1]
struct gt2OBB2D {
	gt2Vector2 c;		// OBBの中心点
	gt2Vector2 u[2];	// ローカルx, およびy軸
	gt2Vector2 e;		// OBBの各軸に沿って正の幅の半分の範囲
public:
	//-----------------------------------------------------------------------------------
	//! @brief 自身のOBB　と OBB(rB)によるあたり判定
	//! @param [in] rB gt2OBB3D構造体 B
	//! @return 重なっている場合は 1を返し、 重なっていない場合は０を返す
	//-----------------------------------------------------------------------------------
	inline bool OBB_OBB(const gt2OBB2D &rB) const
	{
		float fRA, fRB;
		gt2Matrix2x2 mR, mAbsR;

		// aの座標フレームの中でbを表現する回転行列を計算
		mR._11 = u[0].Dot(rB.u[0]);
		mR._12 = u[0].Dot(rB.u[1]);
		mR._21 = u[1].Dot(rB.u[0]);
		mR._22 = u[1].Dot(rB.u[1]);


		// 平行移動ベクトルvTを計算計算
		gt2Vector2 vT = rB.c - c;
		// 平行移動をaの座標フレームに変換
		vT = gt2Vector2(vT.Dot(u[0]), vT.Dot(u[1]));

		// 共通の部分式を計算。
		// 2つの辺が平行でそれらの外積がゼロベクトル(あるいはそれに近いベクトル)になる時に
		// 演算エラーが起きないようにイプシロンの項を追加(詳しくは本文を参照)
		mAbsR._11 = fabs(mR._11) + 0.0001f;
		mAbsR._12 = fabs(mR._12) + 0.0001f;
		mAbsR._21 = fabs(mR._21) + 0.0001f;
		mAbsR._22 = fabs(mR._22) + 0.0001f;


		// 軸L = A0, L = A1, L = A2を判定
		for (int i = 0; i < 2; i++) {
			fRA = e.v[i];
			fRB = rB.e.v[0] * mAbsR.m[i][0] + rB.e.v[1] * mAbsR.m[i][1];
			if (fabs(vT.v[i]) > fRA + fRB) return false;
		}

		// 軸L = B0, L = B1, L = B2を判定
		for (int i = 0; i < 2; i++) {
			fRA = e.v[0] * mAbsR.m[0][i] + e.v[1] * mAbsR.m[1][i];
			fRB = rB.e.v[i];
			if (fabs(vT.v[0] * mR.m[0][i] + vT.v[1] * mR.m[1][i]) > fRA + fRB) return false;
		}

		// 軸L = A0 x B0を判定
		fRA = e.v[2] * mAbsR._21;
		fRB = rB.e.v[2] * mAbsR._12;
		if (fabs(vT.v[2] * mR._21) > fRA + fRB) return false;

		// 軸L = A0 x B1を判定
		fRA = e.v[2] * mAbsR._22;
		fRB = rB.e.v[2] * mAbsR._11;
		if (fabs(vT.v[2] * mR._22) > fRA + fRB) return false;


		// 軸L = A1 x B0を判定
		fRA = e.v[2] * mAbsR._11;
		fRB = rB.e.v[2] * mAbsR._22;
		if (fabs(vT.v[2] * mR._11) > fRA + fRB) return false;

		// 軸L = A1 x B1を判定
		fRA = e.v[2] * mAbsR._12;
		fRB = rB.e.v[2] * mAbsR._21;
		if (fabs(vT.v[2] * mR._12) > fRA + fRB) return false;

		// 分離軸が見つからないので、OBBは交差している
		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief AABB　から OBBを作る。
	//! @param [in] rMin 最小点
	//! @param [in] rMax 最大点
	//! @return 無し
	//-----------------------------------------------------------------------------------
	inline void MakeOBB_AABB(const gt2Vector2 &rMin, const gt2Vector2 &rMax)
	{
		// 中心点
		c = (rMin + rMax)*0.5f;

		// OBBの各軸に沿って正の幅の半分の範囲
		e = rMax - c;
		e.x = fabsf(e.x);
		e.y = fabsf(e.y);

		// ローカルx, y, およびz軸
		u[0] = gt2Vector2(1.0f, 0.0f);
		u[1] = gt2Vector2(0.0f, 1.0f);

	}
	//-----------------------------------------------------------------------------------
	//! @brief AABB　から OBBを作る。
	//! @param [in] vertexCount  x
	//! @param [in] pv           x
	//! @param [in] pointerSrid  x
	//! @return 
	//-----------------------------------------------------------------------------------
	inline float MakeComputeBestFitOBB(uint32_t vertexCount, void *pv, uint32_t pointerSrid)
	{
		return 0;
	}
	//-----------------------------------------------------------------------------------
	//! @brief マトリクスから、OBBを変形させる
	//! @param [in] rMat 対象マトリクス
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void MyTransform(const gt2Matrix4x4 &rMat)
	{
		gt2Matrix4x4 mTmp;

		mTmp._11 = u[0].x;
		mTmp._12 = u[1].x;
		mTmp._13 = u[2].x;
		mTmp._14 = 0;

		mTmp._21 = u[0].y;
		mTmp._22 = u[1].y;
		mTmp._23 = u[2].y;
		mTmp._24 = 0;

		mTmp._31 = 0;
		mTmp._32 = 0;
		mTmp._33 = 1.0f;
		mTmp._34 = 0;

		mTmp._41 = c.x;
		mTmp._42 = c.y;
		mTmp._43 = 0;
		mTmp._44 = 1.0f;

		mTmp = mTmp * rMat;

		u[0].x = mTmp._11;
		u[1].x = mTmp._12;

		u[0].y = mTmp._21;
		u[1].y = mTmp._22;

		c.x = mTmp._41;
		c.y = mTmp._42;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 与えられた点pに対して、OBB 上(もしくは中)にあるrvPの最近接点を返す
	//! @param [in] rvP 点
	//! @return 最近接点を返す
	//-----------------------------------------------------------------------------------
	inline gt2Vector2 ClosestPtPointOBB(const gt2Vector2& rvP) const
	{
		gt2Vector2 ret;
		gt2Vector2 vD = rvP - c;
		// 箱の中心における結果から開始、そこから段階的に進める
		ret = c;
		// 各OBBの軸に対して...
		for (int i = 0; i < 2; i++)
		{
			// ...vDをその軸に射影して
			// 箱の中心からvDの軸に沿った距離を得る
			float fDist = vD.Dot(u[i]);
			// 箱の範囲よりも距離が大きい場合、箱までクランプ
			if (fDist > e.v[i]) fDist = e.v[i];
			if (fDist < -e.v[i]) fDist = -e.v[i];
			// ワールド座標を得るためにその距離だけ軸に沿って進める
			ret += fDist * u[i];
		}

	}
	//-----------------------------------------------------------------------------------
	//! @brief 球sがOBB bに交差している場合は真を返し、そうでなければ偽を返す
	//!  球の中心に対するOBB上の最近接点である点pも返す
	//! @param [in] rS	：[in] 球体
	//! @param [in] pvQ	：[out] 最近接点
	//! @return true & false
	//-----------------------------------------------------------------------------------
	inline bool CircleOBB(const gt2Circle2& rS, gt2Vector2 *pP) const
	{
		// 球の中心に対する最近接点であるOBB上にある点pを見つける
		*pP = this->ClosestPtPointOBB(rS.c);

		// 球とOBBが交差するのは、球の中心から点pまでの(平方した)距離が
		// (平方した)球の半径よりも小さい場合
		gt2Vector2 v = *pP - rS.c;
		return v.Dot() <= rS.r * rS.r;
	}
};






//---------------------------------------
//! @brief  OBB3D(Oriented Bounding Box)
//---------------------------------------
// 領域 R = { x | x = c+r*u[0]+s*u[1]+t*u[2] }, |r|<=e.v[0], |s|<=e.v[1], |t|<=e.v[2]
struct gt2OBB3D
{
	gt2Vector3 c;		// OBBの中心点
	gt2Vector3 u[3];	// ローカルx, y, およびz軸
	gt2Vector3 e;		// OBBの各軸に沿って正の幅の半分の範囲
public:
	//-----------------------------------------------------------------------------------
	//! @brief 自身のOBB　と OBB(rB)によるあたり判定
	//! @param [in] rB gt2OBB3D構造体 B
	//! @return 重なっている場合は 1を返し、 重なっていない場合は０を返す
	//-----------------------------------------------------------------------------------
	inline bool OBB_OBB(const gt2OBB3D &rB) const
	{
		float fRA, fRB;
		gt2Matrix4x4 mR, mAbsR;


		// aの座標フレームの中でbを表現する回転行列を計算
		mR._11 = u[0].Dot(rB.u[0]);
		mR._12 = u[0].Dot(rB.u[1]);
		mR._13 = u[0].Dot(rB.u[2]);
		mR._21 = u[1].Dot(rB.u[0]);
		mR._22 = u[1].Dot(rB.u[1]);
		mR._23 = u[1].Dot(rB.u[2]);
		mR._31 = u[2].Dot(rB.u[0]);
		mR._32 = u[2].Dot(rB.u[1]);
		mR._33 = u[2].Dot(rB.u[2]);


		// 平行移動ベクトルvTを計算計算
		gt2Vector3 vT = rB.c - c;
		// 平行移動をaの座標フレームに変換
		vT = gt2Vector3(vT.Dot(u[0]), vT.Dot(u[1]), vT.Dot(u[2]));

		// 共通の部分式を計算。
		// 2つの辺が平行でそれらの外積がゼロベクトル(あるいはそれに近いベクトル)になる時に
		// 演算エラーが起きないようにイプシロンの項を追加(詳しくは本文を参照)
		mAbsR._11 = fabs(mR._11) + 0.0001f;
		mAbsR._12 = fabs(mR._12) + 0.0001f;
		mAbsR._13 = fabs(mR._13) + 0.0001f;
		mAbsR._21 = fabs(mR._21) + 0.0001f;
		mAbsR._22 = fabs(mR._22) + 0.0001f;
		mAbsR._23 = fabs(mR._23) + 0.0001f;
		mAbsR._31 = fabs(mR._31) + 0.0001f;
		mAbsR._32 = fabs(mR._32) + 0.0001f;
		mAbsR._33 = fabs(mR._33) + 0.0001f;


		// 軸L = A0, L = A1, L = A2を判定
		for (int i = 0; i < 3; i++) {
			fRA = e.v[i];
			fRB = rB.e.v[0] * mAbsR.m[i][0] + rB.e.v[1] * mAbsR.m[i][1] + rB.e.v[2] * mAbsR.m[i][2];
			if (fabs(vT.v[i]) > fRA + fRB) return false;
		}

		// 軸L = B0, L = B1, L = B2を判定
		for (int i = 0; i < 3; i++) {
			fRA = e.v[0] * mAbsR.m[0][i] + e.v[1] * mAbsR.m[1][i] + e.v[2] * mAbsR.m[2][i];
			fRB = rB.e.v[i];
			if (fabs(vT.v[0] * mR.m[0][i] + vT.v[1] * mR.m[1][i] + vT.v[2] * mR.m[2][i]) > fRA + fRB) return false;
		}

		// 軸L = A0 x B0を判定
		fRA = e.v[1] * mAbsR._31 + e.v[2] * mAbsR._21;
		fRB = rB.e.v[1] * mAbsR._13 + rB.e.v[2] * mAbsR._12;
		if (fabs(vT.v[2] * mR._21 - vT.v[1] * mR._31) > fRA + fRB) return false;

		// 軸L = A0 x B1を判定
		fRA = e.v[1] * mAbsR._32 + e.v[2] * mAbsR._22;
		fRB = rB.e.v[0] * mAbsR._13 + rB.e.v[2] * mAbsR._11;
		if (fabs(vT.v[2] * mR._22 - vT.v[1] * mR._32) > fRA + fRB) return false;

		// 軸L = A0 x B2を判定
		fRA = e.v[1] * mAbsR._33 + e.v[2] * mAbsR._23;
		fRB = rB.e.v[0] * mAbsR._12 + rB.e.v[1] * mAbsR._11;
		if (fabs(vT.v[2] * mR._23 - vT.v[1] * mR._33) > fRA + fRB) return false;

		// 軸L = A1 x B0を判定
		fRA = e.v[0] * mAbsR._31 + e.v[2] * mAbsR._11;
		fRB = rB.e.v[1] * mAbsR._23 + rB.e.v[2] * mAbsR._22;
		if (fabs(vT.v[0] * mR._31 - vT.v[2] * mR._11) > fRA + fRB) return false;

		// 軸L = A1 x B1を判定
		fRA = e.v[0] * mAbsR._32 + e.v[2] * mAbsR._12;
		fRB = rB.e.v[0] * mAbsR._23 + rB.e.v[2] * mAbsR._21;
		if (fabs(vT.v[0] * mR._32 - vT.v[2] * mR._12) > fRA + fRB) return false;

		// 軸L = A1 x B2を判定
		fRA = e.v[0] * mAbsR._33 + e.v[2] * mAbsR._13;
		fRB = rB.e.v[0] * mAbsR._22 + rB.e.v[1] * mAbsR._21;
		if (fabs(vT.v[0] * mR._33 - vT.v[2] * mR._13) > fRA + fRB) return false;

		// 軸L = A2 x B0を判定
		fRA = e.v[0] * mAbsR._21 + e.v[1] * mAbsR._11;
		fRB = rB.e.v[1] * mAbsR._33 + rB.e.v[2] * mAbsR._32;
		if (fabs(vT.v[1] * mR._11 - vT.v[0] * mR._21) > fRA + fRB) return false;

		// 軸L = A2 x B1を判定
		fRA = e.v[0] * mAbsR._22 + e.v[1] * mAbsR._12;
		fRB = rB.e.v[0] * mAbsR._33 + rB.e.v[2] * mAbsR._31;
		if (fabs(vT.v[1] * mR._12 - vT.v[0] * mR._22) > fRA + fRB) return false;

		// 軸L = A2 x B2を判定
		fRA = e.v[0] * mAbsR._23 + e.v[1] * mAbsR._13;
		fRB = rB.e.v[0] * mAbsR._32 + rB.e.v[1] * mAbsR._31;
		if (fabs(vT.v[1] * mR._13 - vT.v[0] * mR._23) > fRA + fRB) return false;

		// 分離軸が見つからないので、OBBは交差している
		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief AABB　から OBBを作る。
	//! @param [in] rMin 最小点
	//! @param [in] rMax 最大点
	//! @return 無し
	//-----------------------------------------------------------------------------------
	inline void MakeOBB_AABB(const gt2Vector3 &rMin, const gt2Vector3 &rMax)
	{
		// 中心点
		c = (rMin + rMax)*0.5f;

		// OBBの各軸に沿って正の幅の半分の範囲
		e = rMax - c;
		e.x = fabsf(e.x);
		e.y = fabsf(e.y);
		e.z = fabsf(e.z);

		// ローカルx, y, およびz軸
		u[0] = gt2Vector3(1.0f, 0.0f, 0.0f);
		u[1] = gt2Vector3(0.0f, 1.0f, 0.0f);
		u[2] = gt2Vector3(0.0f, 0.0f, 1.0f);
	}
	inline float MakeComputeBestFitOBB(uint32_t vertexCount, void *pv, uint32_t pointerSrid)
	{
		return MCComputeBestFitOBB(vertexCount, pv, pointerSrid, this);
	}
	//-----------------------------------------------------------------------------------
	//! @brief マトリクスから、OBBを変形させる
	//! @param [in] rMat 対象マトリクス
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void MyTransform(const gt2Matrix4x4 *pMat)
	{
		gt2Matrix4x4 mTmp;

		mTmp._11 = u[0].x;
		mTmp._12 = u[1].x;
		mTmp._13 = u[2].x;
		mTmp._14 = 0;

		mTmp._21 = u[0].y;
		mTmp._22 = u[1].y;
		mTmp._23 = u[2].y;
		mTmp._24 = 0;

		mTmp._31 = u[0].z;
		mTmp._32 = u[1].z;
		mTmp._33 = u[2].z;
		mTmp._34 = 0;

		mTmp._41 = c.x;
		mTmp._42 = c.y;
		mTmp._43 = c.z;
		mTmp._44 = 1.0f;

		mTmp = mTmp * (*pMat);

		u[0].x = mTmp._11;
		u[1].x = mTmp._12;
		u[2].x = mTmp._13;

		u[0].y = mTmp._21;
		u[1].y = mTmp._22;
		u[2].y = mTmp._23;

		u[0].z = mTmp._31;
		u[1].z = mTmp._32;
		u[2].z = mTmp._33;

		c.x = mTmp._41;
		c.y = mTmp._42;
		c.z = mTmp._43;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 与えられた点pに対して、OBB 上(もしくは中)にあるrvPの最近接点を返す
	//! @param [in] rvP 点
	//! @return 最近接点を返す
	//-----------------------------------------------------------------------------------
	inline gt2Vector3 ClosestPtPointOBB(const gt2Vector3& rvP) const
	{
		gt2Vector3 ret;
		gt2Vector3 vD = rvP - c;
		// 箱の中心における結果から開始、そこから段階的に進める
		ret = c;
		// 各OBBの軸に対して...
		for (int i = 0; i < 3; i++)
		{
			// ...vDをその軸に射影して
			// 箱の中心からvDの軸に沿った距離を得る
			float fDist = vD.Dot(u[i]);
			// 箱の範囲よりも距離が大きい場合、箱までクランプ
			if (fDist > e.v[i]) fDist = e.v[i];
			if (fDist < -e.v[i]) fDist = -e.v[i];
			// ワールド座標を得るためにその距離だけ軸に沿って進める
			ret += fDist * u[i];
		}
		return ret;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 球sがOBB bに交差している場合は真を返し、そうでなければ偽を返す
	//!  球の中心に対するOBB上の最近接点である点pも返す
	//! @param [in] rS	：[in] 球体
	//! @param [in] pvQ	：[out] 最近接点
	//! @return true & false
	//-----------------------------------------------------------------------------------
	inline bool SphereOBB(const gt2Sphere& rS, gt2Vector3 *pP) const
	{
		// 球の中心に対する最近接点であるOBB上にある点pを見つける
		*pP = this->ClosestPtPointOBB(rS.c);

		// 球とOBBが交差するのは、球の中心から点pまでの(平方した)距離が
		// (平方した)球の半径よりも小さい場合
		gt2Vector3 v = *pP - rS.c;
		return v.Dot() <= rS.r * rS.r;
	}
};

//-----------------------------------------------------------------------------------
//! @brief 頂点群からOBBを作成する
//! @param [in]  vertexCount 頂点数
//! @param [in]  pv          頂点を含む構造体ポインタなど
//! @param [in]  pointerSrid pvポインタをスライドさせる数 x = pv + pointerSrid
//! @param [out] pOBB        作成されたOBBを格納するためのポインタ
//! @return 最小の軸の長さを返す。
//-----------------------------------------------------------------------------------
inline float MCComputeBestFitOBB(
	uint32_t vertexCount,
	void *pv,
	uint32_t pointerSrid,
	gt2OBB3D *pOBB
	)
{
#define OBB3D_V(_n) (*((gt2Vector3*)(pSrc+(pointerSrid+12)*_n)))
	gt2Matrix4x4 mTmp;
	gt2Vector3 vEx, vTmp, vMin, vMax, vE0, vE1, vE2;
	char *pSrc = (char*)pv;
	float fInv, fDot, fArea;
	float minArea = FLT_MAX;

	// 平均位置算出
	pOBB->c.Init();
	for (uint32_t i = 0; i < vertexCount; i++) {
		pOBB->c += OBB3D_V(i);
	}
	fInv = 1.0f / vertexCount;
	pOBB->c *= fInv;
	//
	float fXX, fXY, fXZ, fYY, fYZ, fZZ;
	fXX = fXY = fXZ = fYY = fYZ = fZZ = 0.0f;
	for (uint32_t i = 0; i < vertexCount; i++) {
		vTmp = OBB3D_V(i) - pOBB->c;
		fXX += vTmp.x*vTmp.x;
		fXY += vTmp.x*vTmp.y;
		fXZ += vTmp.x*vTmp.z;

		fYY += vTmp.y*vTmp.y;
		fYZ += vTmp.y*vTmp.z;

		fZZ += vTmp.z*vTmp.z;
	}
	fXX *= fInv;
	fXY *= fInv;
	fXZ *= fInv;
	fYY *= fInv;
	fYZ *= fInv;
	fZZ *= fInv;

	mTmp._11 = fXX; mTmp._12 = fXY; mTmp._13 = fXZ;
	mTmp._21 = fXY; mTmp._22 = fYY; mTmp._23 = fYZ;
	mTmp._31 = fXZ; mTmp._32 = fYZ; mTmp._33 = fZZ;


	// すべての辺を通じてループ; vertexCountを法として、jはiを1だけ離れて追う
	for (uint32_t i = 0, j = vertexCount - 1; i < vertexCount; j = i, i++) {
		// 現在の辺e0 (e0x,e0y) を得て、正規化
		vE0 = OBB3D_V(i) - OBB3D_V(j);
		vE0.Normalize();

		// 辺e0に対して垂直な軸e1を得る
		vE1 = gt2Vector3(vE0.z, vE0.y, vE0.x); // = Perp2D(e0)

		vE0.Cross(vE2, vE1);
		vE2.Normalize();

		// 最大となる幅を得るためにすべての点をループ
		vMin.InitMax();
		vMax.InitMin();
		for (uint32_t k = 0; k < vertexCount; k++) {
			// 点を軸e0およびe1に射影
			// 両方の軸に沿って最大値と最小値を記録し続ける
			gt2Vector3 vD = OBB3D_V(k) - OBB3D_V(j);

			fDot = vD.Dot(vE0);
			if (fDot < vMin.x) vMin.x = fDot;
			if (fDot > vMax.x) vMax.x = fDot;
			fDot = vD.Dot(vE1);
			if (fDot < vMin.y) vMin.y = fDot;
			if (fDot > vMax.y) vMax.y = fDot;
			fDot = vD.Dot(vE2);
			if (fDot < vMin.z) vMin.z = fDot;
			if (fDot > vMax.z) vMax.z = fDot;
		}
		vEx = vMax - vMin;
		fArea = vEx.x * vEx.y * vEx.z;

		// これまでで最良のものであれば、面積、中心、そして軸を記憶
		if (fArea < minArea) {
			minArea = fArea;
			vTmp = vMin + vMax;
			pOBB->c = OBB3D_V(j) + 0.5f * (vTmp.x * vE0 + vTmp.y * vE1 + vTmp.z * vE2);
			pOBB->u[0] = vE0;
			pOBB->u[1] = vE1;
			pOBB->u[2] = vE2;
			vEx *= 0.5f;
			pOBB->e = vEx;
		}
	}
#undef OBB3D_V
	return minArea;
}
