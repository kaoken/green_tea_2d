/*!
Copyright (c) 2013 METAL CUBE

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software. If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.

3. This notice may not be removed or altered from any source
distribution.
@file plane.h
@brief 平面を扱う構造体
*/
#pragma once

#include <Math/vector.h>


//-------------------------------------------------------
//! @brief 平面に対して、点の位置を表す
//-------------------------------------------------------
enum POSITION_PLANE_POINT
{
	POINT_IN_FRONT_OF_PLANE = 1,	//!< 平面の前に点がある
	POINT_BEHIND_PLANE,			//!< 平面の後ろに点がある
	POINT_ON_PLANE,				//!< 平面にまたがっている
};

//-------------------------------------------------------
//! @brief 平面半空間 2次元
//-------------------------------------------------------
struct gt2Plane2 {
	union {
		struct {
			gt2Vector2	vNormal;		//!< 平面の法線。平面上の点xに対してDot(n,x) = dが成立
			float		distance;		//!< 平面上のある与えられた点pに対してd = Dot(n,p)が成立
		};
		struct {
			float a, b, d;
		};
		float v[3];
	};
public:
	//! @name コンストラクタ
	//@{

	gt2Plane2()
	{
		this->Init();
	}

	gt2Plane2(const gt2Plane2 &p)
	{
		*this = p;
	}

	gt2Plane2(const float fa, const float fb, const float fd)
	{
		Set(fa, fb, fd);
	}

	gt2Plane2(const gt2Vector2& rV2, const float fd)
	{
		Set(rV2, fd);
	}

	gt2Plane2(const gt2Vector2& rvOrigin, const gt2Vector2& rvNormal)
	{
		Set(rvOrigin, rvNormal);
	}
	//@}

	//------------------------------------------------------------------------
	//
	//! @name キャスト演算子
	//
	//------------------------------------------------------------------------
	//@{
	operator float* ()
	{
		return (float *)&a;
	}

	operator const float* () const
	{
		return (const float *)&a;
	}
	//@}


	//------------------------------------------------------------------------
	//
	//! @name 代入演算子
	//
	//------------------------------------------------------------------------
	//@{
	gt2Plane2& operator = (const gt2Plane2 &p)
	{
		this->Set(p.a, p.b, p.d);
		return *this;
	}

	gt2Plane2& operator *= (float f)
	{
		a *= f;
		b *= f;
		d *= f;
		return *this;
	}

	gt2Plane2& operator /= (float f)
	{
		float fInv = 1.0f / f;
		a *= fInv;
		b *= fInv;
		d *= fInv;
		return *this;
	}
	//@}


	//------------------------------------------------------------------------
	//
	//! @name 単項演算子
	//
	//------------------------------------------------------------------------
	//@{
	gt2Plane2 operator + () const
	{
		return gt2Plane2(*this);
	}

	gt2Plane2 operator - () const
	{
		return gt2Plane2(-a, -b, -d);
	}
	//@}


	//------------------------------------------------------------------------
	//
	//! @name 2 項演算子
	//
	//------------------------------------------------------------------------
	//@{
	gt2Plane2 operator * (float f) const
	{
		return gt2Plane2(a * f, b * f, d * f);
	}

	gt2Plane2 operator / (float f) const
	{
		float fInv = 1.0f / f;
		return gt2Plane2(a * fInv, b * fInv, d * fInv);
	}

	friend gt2Plane2 operator * (float f, const gt2Plane2& p)
	{
		return gt2Plane2(f * p.a, f * p.b, f * p.d);
	}

	bool operator == (const gt2Plane2& p) const
	{
		return a == p.a && b == p.b && d == p.d;
	}

	bool operator != (const gt2Plane2& p) const
	{
		return a != p.a || b != p.b || d != p.d;
	}
	//@}

	//-----------------------------------------------------------------------------------
	//! @brief a,b,dの値をセットする
	//! @param [in] fa 値a
	//! @param [in] fb 値b
	//! @param [in] fd 値d
	//! @return なし
	//-----------------------------------------------------------------------------------
	void Set(float fa, float fb, float fd)
	{
		a = fa;
		b = fb;
		d = fd;
	}
	//-----------------------------------------------------------------------------------
	//! @brief v2, dの値をセットする
	//! @param [in] rV2 2要素ベクトル
	//! @param [in] fd 値d
	//! @return なし
	//-----------------------------------------------------------------------------------
	void Set(const gt2Vector2& rV2, const float fd)
	{
		vNormal = rV2;
		d = fd;
	}

	//-----------------------------------------------------------------------------------
	//! @brief 基点と法線からセットする
	//! @param [in] rvOrigin 基点
	//! @param [in] rvNormal 法線
	//! @return なし
	//-----------------------------------------------------------------------------------
	void Set(const gt2Vector2& rvOrigin, const gt2Vector2& rvNormal)
	{
		vNormal = rvNormal;
		d = vNormal.x*rvOrigin.x + vNormal.y*rvOrigin.y;
	}

	//-----------------------------------------------------------------------------------
	//! @brief 与えられた厚みのイプシロンにより厚みのある平面に対して点vPを分類
	//! @param [in] vP 基点
	//! @param [in] fPlaneThicknessEpsilon イプシロン値
	//! @return 平面に対しての点の位置を返す
	//-----------------------------------------------------------------------------------
	POSITION_PLANE_POINT ClassifyPointToPlane(const gt2Vector2 &vP, float fPlaneThicknessEpsilon) const
	{
		//================================
		// 点の平面からの符号付距離を計算
		//================================
		float fDist = this->DistanceTo(vP);

		//================================
		// 符号付距離を基にしてvPを分類
		//================================
		if (fDist > fPlaneThicknessEpsilon) {
			// 平面の厚さのイプシロン値より大きかった
			return POINT_IN_FRONT_OF_PLANE;
		}
		else if (fDist < -fPlaneThicknessEpsilon) {
			// 平面の厚さのイプシロン値より小さかった
			return POINT_BEHIND_PLANE;
		}

		return POINT_ON_PLANE;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 平面に対してrvPointの点を垂直射影したときの点との大きさpTを返す@n
	//!  戻り値がマイナスの場合は裏面、プラスの時は表面に点rvPointがある@n
	//!  平面の法線は正規化されている物とする。
	//! @param [in] rvPoint 垂直射影する点
	//! @return 平面から指定した点までの距離
	//-----------------------------------------------------------------------------------
	float DistanceTo(const gt2Vector2& rvPoint) const
	{
		return vNormal.Dot(rvPoint) - distance;
	}

	//-----------------------------------------------------------------------------------
	//! @brief 平面に対してpvPointの点を垂直射影したときの点pOutを出力する@n
	//! 平面の法線は正規化されている物とする。
	//! @param [in] rV 垂直射影する点
	//! @return 平面から指定した点までの距離
	//-----------------------------------------------------------------------------------
	gt2Vector2 GetClosestPtPoint(const gt2Vector2& rvPoint) const
	{
		return rvPoint - (vNormal.Dot(rvPoint) - distance) * vNormal;
	}


	//-----------------------------------------------------------------------------------
	//! @brief 表面に向いているか？
	//! @param [in] rN 法線
	//! @return 直線が存在しない場合はfalseを返す。
	//-----------------------------------------------------------------------------------
	bool IsFrontFacingTo(const gt2Vector2& rN) const
	{
		return vNormal.Dot(rN) <= 0.0f;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 初期化する。
	//! @return 無し
	//-----------------------------------------------------------------------------------
	void Init()
	{
		a = b = d = 0;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 正規化する
	//! @return 無し
	//-----------------------------------------------------------------------------------
	void Normalize()
	{
		float f = 1.0f / vNormal.Length();
		assert(f != 0.0f);

		if (f) {
			vNormal *= f;  distance *= f;
		}
	}


	//-----------------------------------------------------------------------------------
	//! @brief 辺(vA, vB)は平面(this)をまたいでい交差点を出力
	//! @param [in]  a  始点
	//! @param [in]  rvB  終点
	//! @param [out] pOut 交差点
	//! @return 交差点の値が取得できた場合trueを返す。そうでなければfalseを返す
	//-----------------------------------------------------------------------------------
	bool IntersectEdgeAgainst(const gt2Vector2 &a, const gt2Vector2 &rvB, gt2Vector2* pOut) const
	{
		gt2Vector2 vRet;
		float fT;

		return this->IntersectSegment(a, rvB, &fT, pOut);
	}
	//-----------------------------------------------------------------------------------
	//! @brief 辺(vA, vB)は平面(this)をまたいでい交差点を出力
	//! @param [in]  a  始点
	//! @param [in]  rvB  終点
	//! @param [out] rOut 交差点
	//! @return 交差点の値が取得できた場合trueを返す。そうでなければfalseを返す
	//-----------------------------------------------------------------------------------
	bool IntersectEdgeAgainst(const gt2Vector2 &a, const gt2Vector2 &rvB, gt2Vector2& rOut) const
	{
		return this->IntersectEdgeAgainst(a, rvB, &rOut);
	}


	//-----------------------------------------------------------------------------------
	//! @brief 線分ABが平面p(this)と交差しているかどうかを判定。交差していれば交差点を返す
	//! @param [in]  a  始点
	//! @param [in]  rvB  終点
	//! @param [out] pT  平面と交差する方向のある直線abと交差する値
	//! @param [out] pOut 交差点
	//! @return 交差の値tおよび交差点Qとともにtrueを返す。そうでなければfalseを返す
	//-----------------------------------------------------------------------------------
	bool IntersectSegment(const gt2Vector2 &a, const gt2Vector2 &rvB, float *pT, gt2Vector2 *pOut) const
	{
		// 平面と交差する方向のある直線abと交差するtの値を計算
		gt2Vector2 vAB = rvB - a;
		*pT = (distance - vNormal.Dot(a)) / vNormal.Dot(vAB);

		// tが[0..1]の中にある場合、交差点を計算して返す
		if (*pT >= 0.0f && *pT <= 1.0f) {
			*pOut = a + (vAB * *pT);
			return true;
		}
		// そうでない場合tは+INF, -INF, NaN, あるいは[0..1]の中にはないので、交差なし
		return false;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 線分ABが平面p(this)と交差しているかどうかを判定。交差していれば交差点を返す
	//! @param [in]  a  始点
	//! @param [in]  rvB  終点
	//! @param [out] rT   平面と交差する方向のある直線abと交差する値
	//! @param [out] rOut 交差点
	//! @return 交差の値tおよび交差点Qとともにtrueを返す。そうでなければfalseを返す
	//-----------------------------------------------------------------------------------
	bool IntersectSegment(const gt2Vector2 &a, const gt2Vector2 &rvB, float &rT, gt2Vector2& rOut) const
	{
		return this->IntersectSegment(a, rvB, &rT, &rOut);
	}


	//-----------------------------------------------------------------------------------
	//! @brief 線分ABが平面p(this)と交差しているかどうかを判定。交差していれば交差点を返す
	//! @param [in]  a      始点
	//! @param [in]  rV       ベロシティー
	//! @param [in]  fEpsilon 平面の厚み
	//! @param [out] pT       平面と交差する方向のある直線abと交差する値
	//! @param [out] pOut     交差点
	//! @return 交差の値tおよび交差点Qとともにtrueを返す。そうでなければfalseを返す
	//-----------------------------------------------------------------------------------
	int IntersectLine(const gt2Vector2 &a, const gt2Vector2 &rV, float fEpsilon, float *pT, gt2Vector2 *pOut) const
	{
		// 平面交差点の間隔を得る:
		// 球体位置から平面までの距離を計算します。
		float signedDistToPlane = this->DistanceTo(a);
		// 
		float normalDotVelocity = vNormal.Dot(rV);
		// 球体が平面に平行をになっているか？:
		if (normalDotVelocity == 0.0f) {
			if (fabs(signedDistToPlane) >= fEpsilon) {
				// 厚みfEpsilon内の平面に埋め込まれていない
				// 衝突してない
				return 0;
			}
			// 球体は平面に埋め込まれています。
			*pT = 0.0f;
			*pOut = this->GetClosestPtPoint(a);
			return 2;
		}
		else {
			// 平面と交差する方向のある直線abと交差するtの値を計算
			*pT = (distance - vNormal.Dot(a)) / vNormal.Dot(rV);

			// tが[0..1]の中にある場合、交差点を計算して返す
			if (*pT >= 0.0f && *pT <= 1.0f) {
				*pOut = a + (rV * *pT);
				return 1;
			}
			// そうでない場合tは+INF, -INF, NaN, あるいは[0..1]の中にはないので、交差なし

		}
		return 0;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 線分ABが平面p(this)と交差しているかどうかを判定。交差していれば交差点を返す
	//! @param [in]  a      始点
	//! @param [in]  rV       ベロシティー
	//! @param [in]  fEpsilon 平面の厚み
	//! @param [out] rT       平面と交差する方向のある直線abと交差する値
	//! @param [out] rOut     交差点
	//! @return 交差の値tおよび交差点Qとともにtrueを返す。そうでなければfalseを返す
	//-----------------------------------------------------------------------------------
	int IntersectLine(const gt2Vector2 &a, const gt2Vector2 &rV, float fEpsilon, float &rT, gt2Vector2 &rOut) const
	{
		return this->IntersectLine(a, rV, fEpsilon, &rT, &rOut);
	}

	//-----------------------------------------------------------------------------------
	//! @brief 線分ABが平面p(this)と交差しているかどうかを判定。交差していれば交差点を返す
	//! @param [in]  a     始点
	//! @param [in]  rV      ベロシティー
	//! @param [out] pT      平面と交差する方向のある直線abと交差する値
	//! @param [out] pOut    交差点
	//! @return 交差の値tおよび交差点Qとともにtrueを返す。そうでなければfalseを返す
	//-----------------------------------------------------------------------------------
	int IntersectLine(const gt2Vector2 &a, const gt2Vector2 &rV, float *pT, gt2Vector2 *pOut) const
	{
		// 平面交差点の間隔を得る:
		// 球体位置から平面までの距離を計算します。
		float signedDistToPlane = this->DistanceTo(a);
		// 
		float normalDotVelocity = vNormal.Dot(rV);
		// 球体が平面に平行をになっているか？:
		if (normalDotVelocity == 0.0f) {
			if (fabs(signedDistToPlane) != 0.0f) {
				// 衝突してない
				return 0;
			}
			// 球体は平面に埋め込まれています。
			*pT = 0.0f;
			*pOut = this->GetClosestPtPoint(a);
			return 2;
		}
		else {
			// 平面と交差する方向のある直線abと交差するtの値を計算
			*pT = (distance - vNormal.Dot(a)) / vNormal.Dot(rV);

			// tが[0..1]の中にある場合、交差点を計算して返す
			if (*pT >= 0.0f && *pT <= 1.0f) {
				*pOut = a + (rV * *pT);
				return 1;
			}
			// そうでない場合tは+INF, -INF, NaN, あるいは[0..1]の中にはないので、交差なし

		}
		return 0;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 線分ABが平面p(this)と交差しているかどうかを判定。交差していれば交差点を返す
	//! @param [in]  a      始点
	//! @param [in]  rV       ベロシティー
	//! @param [out] rT      平面と交差する方向のある直線abと交差する値
	//! @param [out] rOut     交差点
	//! @return 交差の値tおよび交差点Qとともにtrueを返す。そうでなければfalseを返す
	//-----------------------------------------------------------------------------------
	int IntersectLine(const gt2Vector2 &a, const gt2Vector2 &rV, float &rT, gt2Vector2 &rOut) const
	{
		return this->IntersectLine(a, rV, &rT, &rOut);
	}
};











//-------------------------------------------------------
//! @brief 平面半空間 3次元
//-------------------------------------------------------
struct gt2Plane3 {
	union {
		struct {
			gt2Vector3	vNormal;		//!< 平面の法線。平面上の点xに対してDot(n,x) = dが成立
			float		distance;		//!< 平面上のある与えられた点pに対してd = Dot(n,p)が成立
		};
		struct {
			float a, b, c, d;
		};
		float v[4];
	};
public:
	//! @name コンストラクタ
	//@{
	gt2Plane3()
	{
		this->Init();
	}

	gt2Plane3(const gt2Plane3 &p)
	{
		*this = p;
	}

	gt2Plane3(const float fa, const float fb, const float fc, const float fd)
	{
		a = fa;
		b = fb;
		c = fc;
		d = fd;
	}

	gt2Plane3(const gt2Vector3& rV3, const float fd)
	{
		vNormal = rV3;
		d = fd;
	}

	gt2Plane3(const gt2Vector3& rvOrigin, const gt2Vector3& rvNormal)
	{
		vNormal = rvNormal;
		d = vNormal.x*rvOrigin.x + vNormal.y*rvOrigin.y + vNormal.z*rvOrigin.z;
	}
	//@}

#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
	gt2Plane3&  operator= (const DirectX::XMVECTOR& vf) { a = vf.m128_f32[0]; b = vf.m128_f32[1]; c = vf.m128_f32[2]; d = vf.m128_f32[3]; return *this; }

	DirectX::XMVECTOR GetXMVECTOR() const { DirectX::XMVECTOR t; t.m128_f32[0] = a; t.m128_f32[1] = b; t.m128_f32[2] = c; t.m128_f32[3] = d; return t; }
#endif


	//------------------------------------------------------------------------
	//
	//! @name キャスト演算子
	//
	//------------------------------------------------------------------------
	//@{
	operator float* ()
	{
		return (float *)&a;
	}

	operator const float* () const
	{
		return (const float *)&a;
	}
	//@}

	//------------------------------------------------------------------------
	//
	//! @name 代入演算子
	//
	//------------------------------------------------------------------------
	//@{
	gt2Plane3& operator = (const gt2Plane3 &p)
	{
		this->Set(p.a, p.b, p.c, p.d);
		return *this;
	}

	gt2Plane3& operator *= (const float f)
	{
		a *= f;
		b *= f;
		c *= f;
		d *= f;
		return *this;
	}

	gt2Plane3& operator /= (const float f)
	{
		float fInv = 1.0f / f;
		a *= fInv;
		b *= fInv;
		c *= fInv;
		d *= fInv;
		return *this;
	}
	//@}


	//------------------------------------------------------------------------
	//
	//! @name 単項演算子
	//
	//------------------------------------------------------------------------
	//@{
	gt2Plane3 operator + () const
	{
		return gt2Plane3(*this);
	}
	gt2Plane3 operator - () const
	{
		return gt2Plane3(-a, -b, -c, -d);
	}
	//@}


	//------------------------------------------------------------------------
	//
	//! @name 二項演算子
	//
	//------------------------------------------------------------------------
	//@{
	gt2Plane3 operator * (const float f) const
	{
		return gt2Plane3(a * f, b * f, c * f, d * f);
	}

	gt2Plane3 operator / (const float f) const
	{
		float fInv = 1.0f / f;
		return gt2Plane3(a * fInv, b * fInv, c * fInv, d * fInv);
	}

	friend gt2Plane3 operator * (const float f, const gt2Plane3& p)
	{
		return gt2Plane3(f * p.a, f * p.b, f * p.c, f * p.d);
	}
	//@}

	//------------------------------------------------------------------------
	//
	//! @name 比較演算子
	//
	//------------------------------------------------------------------------
	//@{
	bool operator == (const gt2Plane3& p) const
	{
		return a == p.a && b == p.b && c == p.c && d == p.d;
	}

	bool operator != (const gt2Plane3& p) const
	{
		return a != p.a || b != p.b || c != p.c || d != p.d;
	}
	//@}


	//-----------------------------------------------------------------------------------
	//! @brief a,b,c,dの値をセットする
	//! @param [in] fa 値a
	//! @param [in] fb 値b
	//! @param [in] fc 値c
	//! @param [in] fd 値d
	//! @return なし
	//-----------------------------------------------------------------------------------
	void Set(float fa, float fb, float fc, float fd)
	{
		a = fa;
		b = fb;
		c = fc;
		d = fd;
	}
	//-----------------------------------------------------------------------------------
	//! @brief v3, dの値をセットする
	//! @param [in] rV3 3要素ベクトル
	//! @param [in] fd 値d
	//! @return なし
	//-----------------------------------------------------------------------------------
	void Set(const gt2Vector3& rV3, const float fd)
	{
		vNormal = rV3;
		d = fd;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 基点と法線からセットする
	//! @param [in] rvOrigin 基点
	//! @param [in] rvNormal 法線
	//! @return なし
	//-----------------------------------------------------------------------------------
	void Set(const gt2Vector3& rvOrigin, const gt2Vector3& rvNormal)
	{
		vNormal = rvNormal;
		d = vNormal.x*rvOrigin.x + vNormal.y*rvOrigin.y + vNormal.z*rvOrigin.z;
	}

	//-----------------------------------------------------------------------------------
	//! @brief 与えられた厚みのイプシロンにより厚みのある平面に対して点vPを分類
	//! @param [in] vP 基点
	//! @param [in] fPlaneThicknessEpsilon イプシロン値
	//! @return 平面に対しての点の位置を返す
	//-----------------------------------------------------------------------------------
	POSITION_PLANE_POINT ClassifyPointToPlane(const gt2Vector3 &vP, float fPlaneThicknessEpsilon) const
	{
		//================================
		// 点の平面からの符号付距離を計算
		//================================
		float fDist = vNormal.Dot(vP) - distance;

		//================================
		// 符号付距離を基にしてvPを分類
		//================================
		if (fDist > fPlaneThicknessEpsilon) {
			// 平面の厚さのイプシロン値より大きかった
			return POINT_IN_FRONT_OF_PLANE;
		}
		else if (fDist < -fPlaneThicknessEpsilon) {
			// 平面の厚さのイプシロン値より小さかった
			return POINT_BEHIND_PLANE;
		}

		return POINT_ON_PLANE;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 平面に対してrvPointの点を垂直射影したときの点との大きさpTを返す@n
	//!  戻り値がマイナスの場合は裏面、プラスの時は表面に点rvPointがある@n
	//!  平面の法線は正規化されている物とする。
	//! @param [in] rvPoint 垂直射影する点
	//! @return 平面から指定した点までの距離
	//-----------------------------------------------------------------------------------
	float DistanceTo(const gt2Vector3& rV) const
	{
		return vNormal.Dot(rV) - distance;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 平面に対してpvPointの点を垂直射影したときの点pOutを出力する@n
	//! 平面の法線は正規化されている物とする。
	//! @param [in] rV 垂直射影する点
	//! @return 平面から指定した点までの距離
	//-----------------------------------------------------------------------------------
	gt2Vector3 GetClosestPtPoint(const gt2Vector3& rvPoint) const
	{
		return rvPoint - (vNormal.Dot(rvPoint) - distance) * vNormal;
	}
	//-----------------------------------------------------------------------------------
	//! @brief この平面に対してもう一つの平面rPlaneに対して、それらの交差である直線
	//!   L = pOutP + t * pOutN 
	//!  を計算し、直線が存在しない場合はfalseを返す
	//!  平面の法線は正規化されている物とする。
	//! @param [in]  rPlane 平面
	//! @param [out] pOutN  交差直線の方向
	//! @param [out] pOutP  交差直線上の点の位置
	//! @return 直線が存在しない場合はfalseを返す。
	//-----------------------------------------------------------------------------------
	bool IntersectPlanes(const gt2Plane3& rPlane, gt2Vector3* pOutN, gt2Vector3* pOutP) const
	{
		// 交差直線の方向を計算
		*pOutN = vNormal.Cross(rPlane.vNormal);

		// pOutNが０の場合、平面は平行か離れている
		// あるいは一致しているので、交差しているとは考えられない
		float fDenom = pOutN->Dot();
		if (fDenom < 0.0001f) return false;

		// 交差直線上の点の位置
		*pOutP = pOutN->Cross((distance*rPlane.vNormal - rPlane.d*vNormal));
		*pOutP /= fDenom;

		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief この平面に対してもう一つの平面rPlaneに対して、それらの交差である直線
	//!   L = rOutPoint + t * rOutN 
	//!  を計算し、直線が存在しない場合はfalseを返す
	//!  平面の法線は正規化されている物とする。
	//! @param [in]  rPlane     平面
	//! @param [out] rOutN      交差直線の方向
	//! @param [out] rOutPoint  交差直線上の点の位置
	//! @return 直線が存在しない場合はfalseを返す。
	//-----------------------------------------------------------------------------------
	bool IntersectPlanes(const gt2Plane3& rPlane, gt2Vector3& rOutN, gt2Vector3 &rOutPoint) const
	{
		return this->IntersectPlanes(rPlane, &rOutN, &rOutPoint);
	}

	//-----------------------------------------------------------------------------------
	//! @brief 表面に向いているか？
	//! @param [in] rN 法線
	//! @return 直線が存在しない場合はfalseを返す。
	//-----------------------------------------------------------------------------------
	bool IsFrontFacingTo(const gt2Vector3& rV) const
	{
		return vNormal.Dot(rV) <= 0.0f;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 初期化する。
	//! @return 無し
	//-----------------------------------------------------------------------------------
	void Init()
	{
		a = b = c = d = 0;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 3つの同一直線上にない点が(時計回りの順に)与えられた場合に、平面の方程式を計算
	//! @return 無し
	//-----------------------------------------------------------------------------------
	void MakeComputePlane(const gt2Vector3 &vA, const gt2Vector3 &vB, const gt2Vector3 &vC)
	{
		vNormal = (vB - vA).Cross((vC - vA));

		vNormal.Normalize();
		distance = vNormal.Dot(vA);
	}
	//-----------------------------------------------------------------------------------
	//! @brief 正規化する
	//! @return 無し
	//-----------------------------------------------------------------------------------
	void Normalize()
	{
		float f = 1.0f / vNormal.Length();
#ifdef MC_DEBUG
		assert(f != 0.0f);
#endif

		if (f) {
			vNormal *= f;  distance *= f;
		}
	}
	//-----------------------------------------------------------------------------------
	//! @brief 辺(vA, vB)は平面(this)をまたいでい交差点を出力
	//! @param [in]  a  始点
	//! @param [in]  rvB  終点
	//! @param [out] pOut 交差点
	//! @return 交差点の値が取得できた場合trueを返す。そうでなければfalseを返す
	//-----------------------------------------------------------------------------------
	bool IntersectEdgeAgainst(const gt2Vector3 &a, const gt2Vector3 &rvB, gt2Vector3* pOut) const
	{
		gt2Vector3 vRet;
		float fT;

		return this->IntersectSegment(a, rvB, &fT, pOut);
	}
	//-----------------------------------------------------------------------------------
	//! @brief 辺(vA, vB)は平面(this)をまたいでい交差点を出力
	//! @param [in]  a  始点
	//! @param [in]  rvB  終点
	//! @param [out] rOut 交差点
	//! @return 交差点の値が取得できた場合trueを返す。そうでなければfalseを返す
	//-----------------------------------------------------------------------------------
	bool IntersectEdgeAgainst(const gt2Vector3 &a, const gt2Vector3 &rvB, gt2Vector3 &rOut) const
	{
		return this->IntersectEdgeAgainst(a, rvB, &rOut);
	}
	//-----------------------------------------------------------------------------------
	//! @brief 線分ABが平面p(this)と交差しているかどうかを判定。交差していれば交差点を返す
	//! @param [in]  a  始点
	//! @param [in]  rvB  終点
	//! @param [out] pT  平面と交差する方向のある直線abと交差する値
	//! @param [out] pOut 交差点
	//! @return 交差の値tおよび交差点Qとともにtrueを返す。そうでなければfalseを返す
	//-----------------------------------------------------------------------------------
	bool IntersectSegment(const gt2Vector3 &a, const gt2Vector3 &rvB, float *pT, gt2Vector3 *pOut) const
	{
		// 平面と交差する方向のある直線abと交差するtの値を計算
		gt2Vector3 vAB = rvB - a;
		*pT = (distance - vNormal.Dot(a)) / vNormal.Dot(vAB);

		// tが[0..1]の中にある場合、交差点を計算して返す
		if (*pT >= 0.0f && *pT <= 1.0f) {
			*pOut = a + (vAB * *pT);
			return true;
		}
		// そうでない場合tは+INF, -INF, NaN, あるいは[0..1]の中にはないので、交差なし
		return false;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 線分ABが平面p(this)と交差しているかどうかを判定。交差していれば交差点を返す
	//! @param [in]  a  始点
	//! @param [in]  rvB  終点
	//! @param [out] rT   平面と交差する方向のある直線abと交差する値
	//! @param [out] rOut 交差点
	//! @return 交差の値tおよび交差点Qとともにtrueを返す。そうでなければfalseを返す
	//-----------------------------------------------------------------------------------
	bool IntersectSegment(const gt2Vector3 &a, const gt2Vector3 &rvB, float &rT, gt2Vector3 &rOut) const
	{
		return this->IntersectSegment(a, rvB, &rT, &rOut);
	}


	//-----------------------------------------------------------------------------------
	//! @brief 線分ABが平面p(this)と交差しているかどうかを判定。交差していれば交差点を返す
	//! @param [in]  a      始点
	//! @param [in]  rV       ベロシティー
	//! @param [in]  fEpsilon 平面の厚み
	//! @param [out] pT       平面と交差する方向のある直線abと交差する値
	//! @param [out] pOut     交差点
	//! @return 交差の値tおよび交差点Qとともにtrueを返す。そうでなければfalseを返す
	//-----------------------------------------------------------------------------------
	int IntersectLine(const gt2Vector3 &a, const gt2Vector3 &rV, float fEpsilon, float *pT, gt2Vector3 *pOut) const
	{
		// 平面交差点の間隔を得る:
		// 球体位置から平面までの距離を計算します。
		float signedDistToPlane = this->DistanceTo(a);
		// 
		float normalDotVelocity = vNormal.Dot(rV);
		// 球体が平面に平行をになっているか？:
		if (normalDotVelocity == 0.0f) {
			if (fabs(signedDistToPlane) >= fEpsilon) {
				// 厚みfEpsilon内の平面に埋め込まれていない
				// 衝突してない
				return 0;
			}
			// 球体は平面に埋め込まれています。
			*pT = 0.0f;
			*pOut = this->GetClosestPtPoint(a);
			return 2;
		}
		else {
			// 平面と交差する方向のある直線abと交差するtの値を計算
			*pT = (distance - vNormal.Dot(a)) / vNormal.Dot(rV);

			// tが[0..1]の中にある場合、交差点を計算して返す
			if (*pT >= 0.0f && *pT <= 1.0f) {
				*pOut = a + (rV * *pT);
				return 1;
			}
			// そうでない場合tは+INF, -INF, NaN, あるいは[0..1]の中にはないので、交差なし

		}
		return 0;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 線分ABが平面p(this)と交差しているかどうかを判定。交差していれば交差点を返す
	//! @param [in]  a      始点
	//! @param [in]  rV       ベロシティー
	//! @param [in]  fEpsilon 平面の厚み
	//! @param [out] rT       平面と交差する方向のある直線abと交差する値
	//! @param [out] rOut     交差点
	//! @return 交差の値tおよび交差点Qとともにtrueを返す。そうでなければfalseを返す
	//-----------------------------------------------------------------------------------
	int IntersectLine(const gt2Vector3 &a, const gt2Vector3 &rV, float fEpsilon, float &rT, gt2Vector3 &rOut) const
	{
		return this->IntersectLine(a, rV, fEpsilon, &rT, &rOut);
	}

	//-----------------------------------------------------------------------------------
	//! @brief 線分ABが平面p(this)と交差しているかどうかを判定。交差していれば交差点を返す
	//! @param [in]  a     始点
	//! @param [in]  rV      ベロシティー
	//! @param [out] pT      平面と交差する方向のある直線abと交差する値
	//! @param [out] pOut    交差点
	//! @return 交差の値tおよび交差点Qとともにtrueを返す。そうでなければfalseを返す
	//-----------------------------------------------------------------------------------
	int IntersectLine(const gt2Vector3 &a, const gt2Vector3 &rV, float *pT, gt2Vector3 *pOut) const
	{
		// 平面交差点の間隔を得る:
		// 球体位置から平面までの距離を計算します。
		float signedDistToPlane = this->DistanceTo(a);
		// 
		float normalDotVelocity = vNormal.Dot(rV);
		// 球体が平面に平行をになっているか？:
		if (normalDotVelocity == 0.0f) {
			if (fabs(signedDistToPlane) != 0.0f) {
				// 衝突してない
				return 0;
			}
			// 球体は平面に埋め込まれています。
			*pT = 0.0f;
			*pOut = this->GetClosestPtPoint(a);
			return 2;
		}
		else {
			// 平面と交差する方向のある直線abと交差するtの値を計算
			*pT = (distance - vNormal.Dot(a)) / vNormal.Dot(rV);

			// tが[0..1]の中にある場合、交差点を計算して返す
			if (*pT >= 0.0f && *pT <= 1.0f) {
				*pOut = a + (rV * *pT);
				return 1;
			}
			// そうでない場合tは+INF, -INF, NaN, あるいは[0..1]の中にはないので、交差なし

		}
		return 0;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 線分ABが平面p(this)と交差しているかどうかを判定。交差していれば交差点を返す
	//! @param [in]  a      始点
	//! @param [in]  rV       ベロシティー
	//! @param [out] rT      平面と交差する方向のある直線abと交差する値
	//! @param [out] rOut     交差点
	//! @return 交差の値tおよび交差点Qとともにtrueを返す。そうでなければfalseを返す
	//-----------------------------------------------------------------------------------
	int IntersectLine(const gt2Vector3 &a, const gt2Vector3 &rV, float &rT, gt2Vector3 &rOut) const
	{
		return this->IntersectLine(a, rV, &rT, &rOut);
	}
};
