/*! @file  Circle.h
* @brief ２Dで使用できる円の構造体など
* @author kaoken
* @date 2014/03/19 作成開始
*/
#pragma once


#include <Math/Plane.h>


struct gt2Circle2;


bool GT2IntersectRayCircle(const gt2Vector2& rvP, const gt2Vector2& rvD, const gt2Circle2& rS, float *pT, gt2Vector2 *pQ);
bool GT2RayCircle(const gt2Vector2& rvP, const gt2Vector2& rvD, const gt2Circle2& rS);
bool MCMovingCircleCircle(const gt2Circle2& rS0, const gt2Circle2 &rS1, const gt2Vector2 &rV0, const gt2Vector2 &rV1, float *pfT);



//---------------------------------------
//!@brief 円 @n
//! 領域 R = { (x, y) | (x-c.x)^2 + (y-c.y)^2 <= r^2 }
//---------------------------------------
struct gt2Circle2
{
	gt2Vector2	c;	//!< 円の中心
	float		r;	//!< 円の半径
public:
	//-----------------------------------------------------------------------------------
	//! @brief コンストラクタ
	//-----------------------------------------------------------------------------------
	gt2Circle2() {
		Init();
	}
	//-----------------------------------------------------------------------------------
	//! @brief コンストラクタ
	//! @param [in] rC 円 
	//-----------------------------------------------------------------------------------
	gt2Circle2(const gt2Circle2 &rC) {
		Set(rC);
	}
	//-----------------------------------------------------------------------------------
	//! @brief コンストラクタ
	//! @param [in] fx x座標 
	//! @param [in] fy y座標
	//! @param [in] fr 半径
	//-----------------------------------------------------------------------------------
	gt2Circle2(const float fx, const float fy, const float fr) {
		Set(fx, fy, fr);
	}
	//-----------------------------------------------------------------------------------
	//! @brief コンストラクタ
	//! @param [in] rV 2次元ベクトル
	//! @param [in] fr 半径
	//-----------------------------------------------------------------------------------
	gt2Circle2(const gt2Vector2 &rV, const float fr) {
		Set(rV, fr);
	}
	//-----------------------------------------------------------------------------------
	//! @brief セットする
	//! @param [in] fx x座標 
	//! @param [in] fy y座標
	//! @param [in] fr 半径
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void Set(const float fx, const float fy, const float fr)
	{
		c.x = fx; c.y = fy;
		r = fr;
	}
	//-----------------------------------------------------------------------------------
	//! @brief セットする
	//! @param [in] rV 2次元ベクトル
	//! @param [in] fr 半径
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void Set(const gt2Vector2 &rV, const float fr)
	{
		c = rV;
		r = fr;
	}
	//-----------------------------------------------------------------------------------
	//! @brief セットする
	//! @param [in] rC 円
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void Set(const gt2Circle2 &rC)
	{
		*this = rC;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 各要素を0で初期化
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void Init() {
		c.Init();
		r = 0.0f;
	}

	//##################################################################
	//##
	//## 単項演算子
	//##
	//##################################################################
	//-----------------------------------------------------------------------------------
	//! @brief 単項演算子 + @n
	//! +を付けただけで、特に値は変更なし
	//! @return そのままのベクトル値を返す
	//-----------------------------------------------------------------------------------
	inline gt2Circle2 operator + () const
	{
		return *this;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 単項演算子 - n
	//! 各要素に-1を乗算したベクトル値になる
	//! @return 各要素に-1を乗算したベクトル値を返す
	//-----------------------------------------------------------------------------------
	inline gt2Circle2 operator - () const
	{
		return gt2Circle2(-c.x, -c.y, r);
	}


	//! @name 代入演算子
	//@{
	inline gt2Circle2& operator += (const gt2Vector2& v)
	{
		c += v;
		return *this;
	}
	inline gt2Circle2& operator += (const gt2Vector3& v)
	{
		c.x += v.x;
		c.y += v.y;
		return *this;
	}

	inline gt2Circle2& operator -= (const gt2Vector2& v)
	{
		c -= v;
		return *this;
	}
	inline gt2Circle2& operator -= (const gt2Vector3& v)
	{
		c.x -= v.x;
		c.y -= v.y;
		return *this;
	}

	inline gt2Circle2& operator *= (const gt2Vector2& v)
	{
		c.x *= v.x;
		c.y *= v.y;
		return *this;
	}
	inline gt2Circle2& operator *= (const gt2Vector3& v)
	{
		c.x *= v.x;
		c.y *= v.y;
		return *this;
	}

	inline gt2Circle2& operator /= (const gt2Vector2& v)
	{
		c.x /= v.x;
		c.y /= v.y;
		return *this;
	}
	inline gt2Circle2& operator /= (const gt2Vector3& v)
	{
		c.x /= v.x;
		c.y /= v.y;
		return *this;
	}
	//@}

	//! @name 単項演算子
	//@{
	inline gt2Circle2 operator + (const gt2Vector2& v) const
	{
		gt2Circle2 tmp;
		tmp.c = c + v;
		tmp.r = r;
		return tmp;
	}
	inline gt2Circle2 operator + (const gt2Vector3& v) const
	{
		gt2Circle2 tmp;
		tmp.c.x = c.x + v.x;
		tmp.c.y = c.y + v.y;
		tmp.r = r;
		return tmp;
	}

	inline gt2Circle2 operator - (const gt2Vector2& v) const
	{
		gt2Circle2 tmp;
		tmp.c = c - v;
		tmp.r = r;
		return tmp;
	}
	inline gt2Circle2 operator - (const gt2Vector3& v) const
	{
		gt2Circle2 tmp;
		tmp.c.x = c.x - v.x;
		tmp.c.y = c.y - v.y;
		tmp.r = r;
		return tmp;
	}

	inline gt2Circle2 operator * (const gt2Vector2& v) const
	{
		gt2Circle2 tmp;
		tmp.c.x = c.x * v.x;
		tmp.c.y = c.y * v.y;
		tmp.r = r;
		return tmp;
	}
	inline gt2Circle2 operator * (const gt2Vector3& v) const
	{
		gt2Circle2 tmp;
		tmp.c.x = c.x * v.x;
		tmp.c.y = c.y * v.y;
		tmp.r = r;
		return tmp;
	}

	inline gt2Circle2 operator / (const gt2Vector2& v) const
	{
		gt2Circle2 tmp;
		tmp.c.x = c.x / v.x;
		tmp.c.y = c.y / v.y;
		tmp.r = r;
		return tmp;
	}
	inline gt2Circle2 operator / (const gt2Vector3& v) const
	{
		gt2Circle2 tmp;
		tmp.c.x = c.x / v.x;
		tmp.c.y = c.y / v.y;
		tmp.r = r;
		return tmp;
	}
	//@}

	//! @name 比較演算子
	//@{
	//-----------------------------------------------------------------------------------
	//! @brief 比較演算子 == @n
	//!   自身(this)のベクトルと"rV"ベクトルの各要素が同じか比較する
	//! @param [in] v     gt2Vector2
	//! @return 自身(this)のベクトルと"rV"ベクトルの各要素を比較し、同一ならtrueを返す。
	//-----------------------------------------------------------------------------------
	inline bool operator == (const gt2Circle2& v) const
	{
		return c == v.c && r == v.r;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 比較演算子 != @n
	//!   自身(this)のベクトルと"rV"ベクトルの各要素が違うか比較する
	//! @param [in] v     gt2Vector2
	//! @return 自身(this)のベクトルと"rV"ベクトルの各要素を比較し、違う場合trueを返す。
	//-----------------------------------------------------------------------------------
	inline bool operator != (const gt2Circle2& v) const
	{
		return c != v.c || r != v.r;
	}
	//@}

	//-----------------------------------------------------------------------------------
	//! @brief 円　と 点によるあたり判定
	//! @param [in] point 点
	//! @return 重なっている場合は trueを返し、 重なっていない場合はfalseを返す
	//-----------------------------------------------------------------------------------
	inline bool CirclePoint(const gt2Vector2& point) const
	{
		float len = (point - c).Length();
		return r >= len;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 円　と 円によるあたり判定
	//! @param [in] rA 円A
	//! @param [in] rB 円B
	//! @return 重なっている場合は trueを返し、 重なっていない場合はfalseを返す
	//-----------------------------------------------------------------------------------
	static bool CircleCircle(const gt2Circle2& rA, const gt2Circle2& rB)
	{
		gt2Vector2 v;
		// 中心間の距離の平方を計算
		v = rA.c - rB.c;

		// 平方した郷里が平方した半径よりも小さい場合に円は交差している
		float fRadiusSum = rA.r + rB.r;
		return v.Dot() <= (fRadiusSum*fRadiusSum);
	}
	//-----------------------------------------------------------------------------------
	//! @brief 自身の円　と 円によるあたり判定
	//! @param [in] rCircle 円
	//! @return 重なっている場合は trueを返し、 重なっていない場合はfalseを返す
	//-----------------------------------------------------------------------------------
	inline bool CircleCircle(const gt2Circle2& rCircle) const
	{
		return CircleCircle(*this, rCircle);
	}
	//-----------------------------------------------------------------------------------
	//! @brief 光線r = p + td, |rvD| = 1が円sに対して交差しているかどうか。
	//! @param [in]  rvP 基点
	//! @param [in]  rvD 方向ベクトル
	//! @param [out] pT  0≦ｔ≦Tmax
	//! @param [out] pQ  交差した位置
	//! @return 交差している場合、交差している*pTの値および交差点*pQを返す
	//-----------------------------------------------------------------------------------
	inline bool IntersectRayCircle(const gt2Vector2& rvP, const gt2Vector2& rvD, float &rOutTime, gt2Vector2 &rQ) const
	{
		return GT2IntersectRayCircle(rvP, rvD, *this, &rOutTime, &rQ);
	}
	//-----------------------------------------------------------------------------------
	//! @brief 光線r = p + tdが自身の円と交差しているかどうかを判定
	//! @param [in]  rvP 基点
	//! @param [in]  rvD 方向ベクトル
	//! @return 交差している場合、true返す
	//-----------------------------------------------------------------------------------
	inline bool RayCircle(const gt2Vector2& rvP, const gt2Vector2& rvD) const
	{
		return GT2RayCircle(rvP, rvD, *this);
	}
	//-----------------------------------------------------------------------------------
	//! @brief X軸を起点とした左右反転の円を作り出す
	//! @param [in]  fX x座標
	//! @return  X軸を起点とした左右反転の円を返す
	//-----------------------------------------------------------------------------------
	inline gt2Circle2 MakeFlipHorizontal(const float fX) const
	{
		return gt2Circle2(fX - c.x, c.y, r);
	}
	//-----------------------------------------------------------------------------------
	//! @brief 光線r = p + td, |vDir| = 1が円sに対して交差しているかどうか。
	//! @param [in]  position  基点
	//! @param [in]  vDir  方向ベクトル
	//! @param [in]  rS    対象とする円
	//! @param [out] out1  接触点１
	//! @param [out] out2  接触点２
	//! @return 交差している場合、交差点の数を返す
	//-----------------------------------------------------------------------------------
	int IntersectRayCircle(const gt2Vector2& position, const gt2Vector2& vDir, gt2Vector2 &out1, gt2Vector2 &out2)
	{
		float t;
		gt2Vector2 vM = position - c;
		float a = vM.Dot(vDir);
		float b = vM.Dot() - r * r;
		// rの原点が*rSの外側にあり(c > 0)、rが*rSから離れていく方向を指している場合(a > 0)に終了
		if (b > 0 && a > 0) return 0;
		float discr = a*a - b;
		// 負の判別式は光線が円を外れている
		if (discr < 0) return 0;
		// これで光線は円と交差していることが分かり、交差する最小の値*pTを計算
		t = -a - sqrt(discr);
		// tが負である場合、光線は円の内側
		if (t < 0) {
			out1 = position + (t*-1) * vDir;
			return 1;
		}
		else if (discr == 0) {
			out1 = position + t * vDir;
			return 1;
		}
		out1 = position + t * vDir;
		out2 = position + (-a + sqrt(discr)) * vDir;
		return 2;
	}
};
