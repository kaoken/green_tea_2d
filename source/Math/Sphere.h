//-----------------------------------------------------------------------------------
// ファイル： gt2Sphere.h, gt2Sphere.inl
//
// 説　明　：
// 　球体関連
//　
// 履　歴　：
// 　2007/10/02 Ver.0.1 制作開始
//
//
// 情　報　：
// 　Copyright(c)2006 METAL CUBE All rights reserved worldwide..
// 　
//-----------------------------------------------------------------------------------
#pragma once
#include <Math/matrix.h>
//---------------------------------------
//! @brief 球体 @n
//! 領域 R = { (x, y, z) | (x-c.x)^2 + (y-c.y)^2 + (z-c.z)^2 <= r^2 }
//---------------------------------------
struct gt2Sphere {
	gt2Vector3	c;	//!< 球の中心
	float		r;	//!< 球の半径
public:
	//-----------------------------------------------------------------------------------
	//! @brief コンストラクタ
	//-----------------------------------------------------------------------------------
	inline gt2Sphere() {
		Init();
	}
	//-----------------------------------------------------------------------------------
	//! @brief コンストラクタ
	//! @param [in]  rC      位置
	//! @param [in]  radius  半径
	//-----------------------------------------------------------------------------------
	inline gt2Sphere(const gt2Vector3 &rC, float radius) { Set(rC, radius); }
	//-----------------------------------------------------------------------------------
	//! @brief コンストラクタ
	//! @param [in]  x      位置 x
	//! @param [in]  y      位置 y
	//! @param [in]  z      位置 z
	//! @param [in]  radius  半径
	//-----------------------------------------------------------------------------------
	inline gt2Sphere(float x, float y, float z, float radius) { Set(x, y, z, radius); }

	//-----------------------------------------------------------------------------------
	//! @brief 球体をセットする
	//! @param [in]  r      球体
	//! @return 無し
	//-----------------------------------------------------------------------------------
	inline void Set(const gt2Sphere &r)
	{
		*this = r;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 位置と、半径をセットする
	//! @param [in]  rC      位置
	//! @param [in]  radius  半径
	//! @return 無し
	//-----------------------------------------------------------------------------------
	inline void Set(const gt2Vector3 &rC, float radius)
	{
		c = rC; r = radius;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 位置と、半径をセットする
	//! @param [in]  rC      位置
	//! @param [in]  radius  半径
	//! @return 無し
	//-----------------------------------------------------------------------------------
	inline void Set(float x, float y, float z, float radius)
	{
		c = gt2Vector3(x, y, z); r = radius;
	}

	//! @name 代入演算子
	//@{
	inline gt2Sphere& operator += (const gt2Vector3& v)
	{
		c += v;
		return *this;
	}

	inline gt2Sphere& operator -= (const gt2Vector3& v)
	{
		c -= v;
		return *this;
	}

	inline gt2Sphere& operator *= (const gt2Vector3& v)
	{
		c *= v;
		return *this;
	}

	inline gt2Sphere& operator /= (const gt2Vector3& v)
	{
		c /= v;
		return *this;
	}
	//@}

	//! @name 単演算子
	//@{
	inline gt2Sphere operator + () const
	{
		return *this;
	}
	inline gt2Sphere operator - () const
	{
		return gt2Sphere(-c, r);
	}
	//@}


	//! @name 二項演算子
	//@{
	inline gt2Sphere operator + (const gt2Vector3& v) const
	{
		gt2Sphere tmp;
		tmp.c = c + v;
		return tmp;
	}

	inline gt2Sphere operator - (const gt2Vector3& v) const
	{
		gt2Sphere tmp;
		tmp.c = c - v;
		return tmp;
	}

	inline gt2Sphere operator * (const gt2Vector3& v) const
	{
		gt2Sphere tmp;
		tmp.c = c * v;
		return tmp;
	}

	inline gt2Sphere operator / (const gt2Vector3& v) const
	{
		gt2Sphere tmp;
		tmp.c = c / v;
		return tmp;
	}
	//@}

	//! @name 比較演算子
	//@{
	inline bool operator == (const gt2Sphere& v) const
	{
		return c == v.c && r == v.r;
	}
	inline bool operator != (const gt2Sphere& v) const
	{
		return c != v.c || r != v.r;
	}
	//@}

	//-----------------------------------------------------------------------------------
	//! @brief 光線r = p + td, |vD| = 1が球sに対して交差しているかどうか。
	//! @param [in]  rvP  基点
	//! @param [in]  vD  方向ベクトル
	//! @param [in]  rS   対象とする球体
	//! @param [out] pT   0≦ｔ≦Tmax
	//! @param [out] pQ   交差した位置
	//! @return 交差している場合、交差している*pTの値および交差点*pQを返す
	//-----------------------------------------------------------------------------------
	static inline bool IntersectRaySphere(const gt2Vector3& rvP, const gt2Vector3& vD, const gt2Sphere& rS, float *pT, gt2Vector3 *pQ)
	{
		gt2Vector3 vM = rvP - rS.c;
		float fB = vM.Dot(vD);
		float fC = vM.Dot() - rS.r * rS.r;
		// rの原点が*rSの外側にあり(c > 0)、rが*rSから離れていく方向を指している場合(fB > 0)に終了
		if (fC > 0.0f && fB > 0.0f) return false;
		float fDiscr = fB*fB - fC;
		// 負の判別式は光線が球を外れていることに一致
		if (fDiscr < 0.0f) return 0;
		// これで光線は球と交差していることが分かり、交差する最小の値*pTを計算
		*pT = -fB - (float)sqrt(fDiscr);
		// *pTが負である場合、光線は球の内側から開始しているので*pTをゼロにクランプ
		if (*pT < 0.0f) *pT = 0.0f;
		*pQ = rvP + *pT * vD;
		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 光線r = p + tdが球sと交差しているかどうかを判定
	//! @param [in] rvP  基点
	//! @param [in] vD  方向ベクトル
	//! @param [in] rS   対象とする球体
	//! @return 交差している場合、true返す
	//-----------------------------------------------------------------------------------
	static inline bool RaySphere(const gt2Vector3& rvP, const gt2Vector3& vD, const gt2Sphere& rS)
	{
		gt2Vector3 vM = rvP - rS.c;
		float fC = vM.Dot() - rS.r * rS.r;
		// 少なくとも1つの実数解が存在している場合、交差している
		if (fC <= 0.0f) return true;
		float fB = vM.Dot(vD);
		// 光線の原点が球の外側にあり光線が球から離れた方向を指している場合には早期に終了
		if (fB > 0.0f) return false;
		float fDiscr = fB*fB - fC;
		// 負の判別式は光線が球を外れていることに一致
		if (fDiscr < 0.0f) return false;
		// これで光線は球と交差している
		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 球　と 球によるあたり判定
	//! @param [in] pA gt2Sphereポインタ
	//! @param [in] pB gt2Sphereポインタ
	//! @return 重なっている場合は trueを返し、 重なっていない場合はfalseを返す
	//-----------------------------------------------------------------------------------
	static inline bool SphereSphere(const gt2Sphere& rA, const gt2Sphere& rB)
	{
		gt2Vector3 v;
		// 中心間の距離の平方を計算
		v = rA.c - rB.c;

		// 平方した郷里が平方した半径よりも小さい場合に球は交差している
		float fRadiusSum = rA.r + rB.r;
		return v.Dot() <= (fRadiusSum*fRadiusSum);
	}




	//-----------------------------------------------------------------------------------
	//! @brief 初期化
	//-----------------------------------------------------------------------------------
	inline void Init() {
		c.Init();
		r = 0.0f;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 球　と 球によるあたり判定
	//! @param [in] sphere gt2Sphere
	//! @return 重なっている場合は trueを返し、 重なっていない場合はfalseを返す
	//-----------------------------------------------------------------------------------
	inline bool SphereSphere(const gt2Sphere& sphere) const
	{
		return SphereSphere(*this, sphere);
	}
	//-----------------------------------------------------------------------------------
	//! @brief 光線r = p + td, |vD| = 1が球sに対して交差しているかどうか。
	//! @param [in]  rvP  基点
	//! @param [in]  vD  方向ベクトル
	//! @param [out] pT   0≦ｔ≦Tmax
	//! @param [out] pQ   交差した位置
	//! @return 交差している場合、交差している*pTの値および交差点*pQを返す
	//-----------------------------------------------------------------------------------
	inline bool IntersectRaySphere(const gt2Vector3& rvP, const gt2Vector3& vD, float *pT, gt2Vector3 *pQ) const
	{
		return IntersectRaySphere(rvP, vD, *this, pT, pQ);
	}
	//-----------------------------------------------------------------------------------
	//! @brief 光線r = p + td, |vD| = 1が球sに対して交差しているかどうか。
	//! @param [in]  rvP  基点
	//! @param [in]  vD  方向ベクトル
	//! @param [out] rT   0≦ｔ≦Tmax
	//! @param [out] rQ   交差した位置
	//! @return 交差している場合、交差している*pTの値および交差点*pQを返す
	//-----------------------------------------------------------------------------------
	inline bool IntersectRaySphere(const gt2Vector3& rvP, const gt2Vector3& vD, float &rT, gt2Vector3 &rQ) const
	{
		return this->IntersectRaySphere(rvP, vD, &rT, &rQ);
	}
	//-----------------------------------------------------------------------------------
	//! @brief 光線r = p + tdが球sと交差しているかどうかを判定
	//! @param [in] rvP 基点
	//! @param [in] vD 方向ベクトル
	//! @return 交差している場合、true返す
	//-----------------------------------------------------------------------------------
	inline bool RaySphere(const gt2Vector3& rvP, const gt2Vector3& vD) const
	{
		return RaySphere(rvP, vD, *this);
	}
	//-----------------------------------------------------------------------------------
	// [ 説明 ] public
	//  vDの方向に時間間隔fT0 <= *pfT <= fT1の間だけ運動している球 s0
	//  s0（この球体）
	// [ 引数 ]
	//  vD	：[in] s0の方向ベクトル
	//  fT0	：[in] 最小時間
	//  fT1	：[in] 最大時間
	//  s1	：[in] 球体１
	//  pfT	：[out] 時間を返す
	// [ 戻り値 ]
	//  静止している球s1に対して交差。交差が見つかれば衝突の時間*pfTを返す
	//-----------------------------------------------------------------------------------
	bool MovingSphereSphereTime(const gt2Vector3& vD, float fT0, float fT1, const gt2Sphere& s1, float *pfT) const
	{
		// 時間間隔fT0からfT1までの間に、*pS0の運動している球の境界を計算
		gt2Sphere b;
		float fMid = (fT0 + fT1) * 0.5f;
		b.c = this->c + vD * fMid;
		b.r = (fMid - fT0) * vD.Length() + this->r;
		// 境界球がs1と重ならない場合、従ってこの時間間隔では衝突はない。
		if (!b.SphereSphere(s1)) return false;

		// 衝突を除外することはできない。より精密な判定のために再帰的に判定が行われる、
		// 再帰を停止するために、時間間隔が十分に小さくなった時に衝突が仮定される
		if (fT1 - fT0 < 0.0001f) {
			*pfT = fT0;
			return true;
		}

		// 間隔の前半部分の半分における判定を再帰的に行い、衝突が検知された場合は戻る
		if (this->MovingSphereSphereTime(vD, fT0, fMid, s1, pfT)) return true;

		// 間隔の後半部分の半分における判定を再帰的に行う
		return this->MovingSphereSphereTime(vD, fMid, fT1, s1, pfT);
	}
	bool MovingSphereSphereTime(const gt2Vector3& vD, float fT0, float fT1, const gt2Sphere& s1, float &outT) const 
	{
		return this->MovingSphereSphereTime(vD, fT0, fT1, s1, &outT);
	}
	//-----------------------------------------------------------------------------------
	// [ 説明 ] public
	//  動いている球体の当たり判定
	// [ 引数 ]
	//  球体０(this)
	//  v0	：[in] この(s0)球体のベロシティー
	//  s1	：[in] 球体１
	//  v1	：[in] s1の球体のベロシティー
	//  pfT	：[out] 時間
	// [ 戻り値 ]
	//  静止している球 s1 に対して交差している場合はtrueを返し、衝突の時間*pfTも返す
	//-----------------------------------------------------------------------------------
	bool MovingSphereSphere(const gt2Vector3& v0, const gt2Sphere& s1, const gt2Vector3& v1, float *pfT) const
	{
		// 球s1をs0の半径にまで拡張
		gt2Sphere S1Ex = s1;
		S1Ex.r += this->r;
		// s0およびs1の両方からs1の運動を引き算し、s1を静止させる
		gt2Vector3 v = v0 - v1;
		// これで、方向のある線分 s = s0.c + tv, v = (v0-v1)/||v0-v1|| を
		// 拡張した球に対して交差させることができる
		gt2Vector3 vQ;
		float fVLen = v.Length();
		v /= fVLen;
		if (S1Ex.IntersectRaySphere(this->c, v, pfT, &vQ)) {
			return *pfT <= fVLen;
		}
		return 0;
	}
	bool MovingSphereSphere(const gt2Vector3& v0, const gt2Sphere& s1, const gt2Vector3& v1, float &outT) const
	{
		return this->MovingSphereSphere(v0, s1, v1, &outT);
	}
};