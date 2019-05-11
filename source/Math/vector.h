/*!
Copyright 2019 kaoken

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

@file vector.h
@brief 要素が2,3,4のベクトル構造体
*/
#pragma once


#include <Core/greenTea2D.h>
#include <Math/mathMacro.h>
#include <Box2D/Box2D.h>


#  undef min
#  undef max

struct gt2Vector2;
struct gt2Vector3;
struct gt2Vector4;

/*!
* @brief 2要素(x,y) ベクトル
*/
struct gt2Vector2
{
public:
	union
	{
		struct {
			float x; //!< 要素 x
			float y; //!< 要素 y
		};
		float v[2];	//!< v[0] = x, v[1] = y 
	};
public:
#ifdef B2_MATH_H
	gt2Vector2& operator= (const b2Vec2& Float2) { x = Float2.x; y = Float2.y; return *this; }
#endif

	/*!
	* @brief コンストラクタ
	*  x,yが０で初期化される
	*/
	gt2Vector2() { this->Init(); };
#ifdef B2_MATH_H
	/*!
	* @brief コンストラクタ
	*  rVで初期化される
	* @param [in] rV     b2Vec2ベクトル
	*/
	gt2Vector2(const b2Vec2 &rV) { *this = rV; };
#endif
	/*!
	* @brief コンストラクタ
	*  rVで初期化される
	* @param [in] rV     ベクトル
	*/
	gt2Vector2(const gt2Vector2 &rV) { *this = rV; };
	/*!
	* @brief コンストラクタ
	*   x=fx,y=fy といった感じに初期化される
	* @param [in] fx     x値
	* @param [in] fy     y値
	*/
	gt2Vector2(float fx, float fy) { x = fx; y = fy; }
	/*!
	* @brief x,yの値が０で初期化される
	* @return なし
	*/
	inline void Init() { x = y = 0; }
	/*!
	* @brief x,yの値がfloat型の最大値のFLT_MAXで初期化される
	* @return なし
	*/
	inline void InitMin() { x = y = FLT_MAX; }
	/*!
	* @brief x,yの値がfloat型の最小値のFLT_MAXで初期化される
	* @return なし
	*/
	inline void InitMax() { x = y = -FLT_MAX; }
	/**
	* @param [in] fx     x値
	* @param [in] fy     y値
	*/
	inline void Set(float fx, float fy) { x = fx; y = fy; }
	/*!
	* @brief 角度(0～360)からラジアン値に変換してx,yに代入する
	* @param [in] fx     角度(0～360)
	* @param [in] fy     角度(0～360)
	* @return なし
	*/
	inline void MakeRadianToDegrees(float fx, float fy)
	{
		x = GT2_INV_RADIAN * fx;
		y = GT2_INV_RADIAN * fy;
	}

	//##################################################################
	//##
	//## 代入演算子
	//##
	//##################################################################
	/*!
	* @brief 代入演算子 =
	*   通常の代入
	* @param [in] v     右辺のベクトルgt2Vector2
	* @return 加算されたベクトル値を返す
	*/
	inline gt2Vector2& operator = (const gt2Vector2& v)
	{
		x = v.x;
		y = v.y;
		return *this;
	}

	/*!
	* @brief 代入演算子 +=
	*   自身(this)のベクトル値を右辺のベクトル値を加算した値を自身(this)にセットする
	* @param [in] v     右辺のベクトルgt2Vector2
	* @return 加算されたベクトル値を返す
	*/
	inline gt2Vector2& operator += (const gt2Vector2& v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}
	/*!
	* @brief 代入演算子 -=
	*   自身(this)のベクトル値を右辺のベクトル値を減算した値を自身(this)にセットする
	* @param [in] v     右辺のベクトルgt2Vector2
	* @return 減算されたベクトル値を返す
	*/
	inline gt2Vector2& operator -= (const gt2Vector2& v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}
	/*!
	* @brief 代入演算子 *=
	*   自身(this)のベクトル値を右辺の１つの値を乗算した値を自身(this)にセットする
	* @param [in] v     右辺の1つの値
	* @return 乗算されたベクトル値を返す
	*/
	inline gt2Vector2& operator *= (float f)
	{
		x *= f;
		y *= f;
		return *this;
	}
	/*!
	* @brief 代入演算子 *=
	*   自身(this)のベクトル値を右辺の１つの値を除算した値を自身(this)にセットする
	* @param [in] v     右辺の1つの値
	* @return 除算されたベクトル値を返す
	*/
	inline gt2Vector2& operator /= (float f)
	{
		float fInv = 1.0f / f;
		x *= fInv;
		y *= fInv;
		return *this;
	}

	//##################################################################
	//##
	//## 単項演算子
	//##
	//##################################################################
	/*!
	* @brief 単項演算子 +
	*   +を付けただけで、特に値は変更なし
	* @return そのままのベクトル値を返す
	*/
	inline gt2Vector2 operator + () const
	{
		return *this;
	}
	/*!
	* @brief 単項演算子 -
	*   各要素に-1を乗算したベクトル値になる
	* @return 各要素に-1を乗算したベクトル値を返す
	*/
	inline gt2Vector2 operator - () const
	{
		return gt2Vector2(-x, -y);
	}


	//##################################################################
	//##
	//## 二項演算子
	//##
	//##################################################################
	/*!
	* @brief 二項演算子 +
	*   自身(this)のベクトルと"rV"ベクトルを加算する
	* @param [in] v     gt2Vector2
	* @return 自身(this)のベクトルと"rV"ベクトル値を加算した値を返す
	*/
	inline gt2Vector2 operator + (const gt2Vector2& v) const
	{
		return gt2Vector2(x + v.x, y + v.y);
	}
	/*!
	* @brief 二項演算子 -
	*   自身(this)のベクトルと"rV"ベクトルを減算する
	* @param [in] v     gt2Vector2
	* @return 自身(this)のベクトルと"rV"ベクトル値を減算した値を返す
	*/
	inline gt2Vector2 operator - (const gt2Vector2& v) const
	{
		return gt2Vector2(x - v.x, y - v.y);
	}
	/*!
	* @brief 二項演算子 *
	*   自身(this)のベクトルと"rV"ベクトルの要素ごと乗算する
	* @param [in] v     gt2Vector2
	* @return 自身(this)のベクトルと"rV"ベクトルの要素ごと乗算した値を返す
	*/
	inline gt2Vector2 operator * (const gt2Vector2& v) const
	{
		return gt2Vector2(x * v.x, y * v.y);
	}
	/*!
	* @brief 二項演算子 /
	*   自身(this)のベクトルと"rV"ベクトルの要素ごと除算する
	* @param [in] v     gt2Vector2
	* @return 自身(this)のベクトルと"rV"ベクトルの要素ごと除算した値を返す
	*/
	inline gt2Vector2 operator / (const gt2Vector2& v) const
	{
		return gt2Vector2(x / v.x, y / v.y);
	}
	/*!
	* @brief 二項演算子 +
	*   自身(this)のベクトルの要素ごに"f"の値を加算する
	* @param [in] f     1つの値
	* @return 自身(this)のベクトルの要素ごに"f"の値を加算した値を返す
	*/
	inline gt2Vector2 operator + (float f) const
	{
		return gt2Vector2(x + f, y + f);
	}
	/*!
	* @brief 二項演算子 -
	*   自身(this)のベクトルの要素ごに"f"の値を減算する
	* @param [in] f     1つの値
	* @return 自身(this)のベクトルの要素ごに"f"の値を減算した値を返す
	*/
	inline gt2Vector2 operator - (float f) const
	{
		return gt2Vector2(x - f, y - f);
	}
	/*!
	* @brief 二項演算子 *
	*   自身(this)のベクトルの要素ごに"f"の値を乗算する
	* @param [in] f     1つの値
	* @return 自身(this)のベクトルの要素ごに"f"の値を乗算した値を返す
	*/
	inline gt2Vector2 operator * (float f) const
	{
		return gt2Vector2(x * f, y * f);
	}
	/*!
	* @brief 二項演算子 /
	*   自身(this)のベクトルの要素ごに"f"の値を除算する
	* @param [in] f     1つの値
	* @return 自身(this)のベクトルの要素ごに"f"の値を除算した値を返す
	*/
	inline gt2Vector2 operator / (float f) const
	{
		float fInv = 1.0f / f;
		return gt2Vector2(x * fInv, y * fInv);
	}

	friend inline gt2Vector2 operator * (float f, const gt2Vector2& v)
	{
		return gt2Vector2(f * v.x, f * v.y);
	}


	//##################################################################
	//##
	//## 比較演算子
	//##
	//##################################################################
	/*!
	* @brief 比較演算子 ==
	*   自身(this)のベクトルと"rV"ベクトルの各要素が同じか比較する
	* @param [in] v     gt2Vector2
	* @return 自身(this)のベクトルと"rV"ベクトルの各要素を比較し、同一ならtrueを返す。
	*/
	inline bool operator == (const gt2Vector2& v) const
	{
		return x == v.x && y == v.y;
	}
	/*!
	* @brief 比較演算子 !=
	*   自身(this)のベクトルと"rV"ベクトルの各要素が違うか比較する
	* @param [in] v     gt2Vector2
	* @return 自身(this)のベクトルと"rV"ベクトルの各要素を比較し、違う場合trueを返す。
	*/
	inline bool operator != (const gt2Vector2& v) const
	{
		return x != v.x || y != v.y;
	}



	//##################################################################
	//##
	//## 
	//##
	//##################################################################

	/*!
	* @brief ベクトルの長さを返す。
	* @return ベクトルの長さを返す。
	*/
	inline float Length() const
	{
		return sqrtf(x * x + y * y);
	}
	/*!
	* @brief ベクトルの長さの 2 乗を返す。
	* @return ベクトルの長さの 2 乗を返す。
	*/
	inline float LengthSq() const
	{
		return x * x + y * y;
	}
	/*!
	* @brief 内積
	*   ベクトルの内積を求めます。
	* @return  内積を返す。
	*/
	inline float Dot() const
	{
		return x * x + y * y;
	}
	/*!
	* @brief 内積
	*   自身(this)のベクトルと"rV2"ベクトルを内積する
	* @param [in] rV     対象ベクトル
	* @return  内積を返す。
	*/
	inline float Dot(const gt2Vector2& rV) const
	{
		return x * rV.x + y * rV.y;
	}
	/*!
	* @brief 外積
	*   ベクトルの外積を計算し、z 成分を返す。
	* @param [in] rV     対象ベクトル
	* @return  内積を返す。
	*/
	inline float CCW(const gt2Vector2& rV) const
	{
		return x * rV.y - y * rV.x;
	}
	/*!
	* @brief ベクトルの加算
	*   自身(this)のベクトルと"rV"ベクトルを加算する。
	* @param [in] rV     入力 gt2Vector2 構造体
	* @return  加算されたベクトルを返す。
	*/
	inline gt2Vector2 Add(const gt2Vector2& rV) const
	{
		gt2Vector2 out;
		out.x = x + rV.x;
		out.y = y + rV.y;
		return out;
	}
	/*!
	* @brief ベクトルの減算
	*   自身(this)のベクトルと"rV"ベクトルを減算する。
	* @param [in] rV     入力 gt2Vector2 構造体
	* @return  減算されたベクトルを返す。
	*/
	inline gt2Vector2 Subtract(const gt2Vector2& rV) const
	{
		gt2Vector2 out;
		out.x = x - rV.x;
		out.y = y - rV.y;
		return out;
	}
	/*!
	* @brief 2つのベクトルの要素を比較し最小値の要素のベクトルを返す
	* @param [in] rV     入力 gt2Vector2 構造体
	* @return  最小値の要素のベクトルを返す
	*/
	inline gt2Vector2 Minimize(const gt2Vector2& rV) const
	{
		gt2Vector2 out;
		out.x = x < rV.x ? x : rV.x;
		out.y = y < rV.y ? y : rV.y;
		return out;
	}
	/*!
	* @brief 2つのベクトルの要素を比較し最大値の要素のベクトルを取得する
	* @param [in] rV     入力 gt2Vector2 構造体
	* @return  最大値の要素のベクトルを返す
	*/
	inline gt2Vector2 Maximize(const gt2Vector2& rV) const
	{
		gt2Vector2 out;
		out.x = x > rV.x ? x : rV.x;
		out.y = y > rV.y ? y : rV.y;
		return out;
	}
	/*!
	* @brief 自身(this)のベクトルを90°回転させたラジアン値を渡す
	* @return  身のベクトルを90°回転させたラジアン値を返す
	*/
	inline gt2Vector2 GetRot90() const
	{
		gt2Vector2 out;
		out.x = -y;
		out.y = x;
		return out;
	}
	/*!
	* @brief 自身(this)のベクトルを90°回転させた値を正規化した値を渡す。
	* @param [out] pOut     演算結果である gt2Vector2 構造体へのポインタ。
	* @return  自身(this)のベクトルを90°回転させた値を正規化した値を返す
	*/
	inline gt2Vector2 GetNormalizeRot90() const
	{
		gt2Vector2 out = this->GetRot90();
		out.Normalize();
		return out;
	}
	/*!
	* @brief ベクトルを正規化したベクトルを返します。
	* @param [out] pOut     演算結果である gt2Vector2 構造体へのポインタ。
	* @return  ベクトルを正規化したベクトルを返す。
	*/
	inline gt2Vector2* Normalize(gt2Vector2* pOut) const
	{
		float fL = this->Length();
		if (fL == 0.0f)
			return nullptr;

		*pOut = *this;

		fL = 1.0f / fL;
		pOut->x *= fL;
		pOut->y *= fL;

		return pOut;
	}
	/*!
	* @brief ベクトルを正規化したベクトルを返す。
	* @param [out] rOut     演算結果である gt2Vector2。
	* @return  なし
	*/
	inline void Normalize(gt2Vector2 &rOut) const
	{
		this->Normalize(&rOut);
	}

	/*!
	* @brief 自身(this)のベクトルを正規化する。
	* @return  なし
	*/
	inline void Normalize()
	{
		float fL = this->Length();
		if (fL == 0.0f)
			return;

		fL = 1.0f / fL;
		x *= fL;
		y *= fL;
	}

	/*!
	* @brief ベクトルの要素を、指定された最大値と最小値の範囲にクランプします。
	* @param [in] rMin     最小範囲ベクトル
	* @param [in] rMax     最大範囲ベクトル
	* @return  なし
	*/
	void Clamp(const gt2Vector2& rMin, const gt2Vector2& rMax)
	{
		x = std::min(std::max(x, rMin.x), rMax.x);
		y = std::min(std::max(y, rMin.y), rMax.y);
	}
	/*!
	* @brief ベクトルをスケーリングする。
	* @param [in]  s      スケーリング値。
	* @return  ベクトルをスケーリングしたものを返す。
	*/
	inline gt2Vector2 Scale(float s) const
	{
		gt2Vector2 out;
		out.x = x * s;
		out.y = y * s;
		return out;
	}
	/*!
	* @brief ベクトル間の線形補間を実行する。
	* @param [in]  rV1   第 1 番目のベクトル
	* @param [in]  rV2   第 2 番目のベクトル
	* @param [in]  t     ベクトル間を線形補間するパラメータ。
	* @return  線形補間されたベクトルを返す。
	*/
	inline static gt2Vector2 Lerp(const gt2Vector2& rV1, const gt2Vector2& rV2, float t)
	{
		gt2Vector2 out;
		out.x = rV1.x + t * (rV2.x - rV1.x);
		out.y = rV1.y + t * (rV2.y - rV1.y);
		return out;
	}
	/*!
	* @brief ベクトル間の線形補間を実行する。
	*   第 1 番目のベクトルが、自身(this)です。
	* @param [in]  rV2   第 2 番目のベクトル
	* @param [in]  t     ベクトル間を線形補間するパラメータ。
	* @return  線形補間されたベクトルを返す。
	*/
	inline gt2Vector2 Lerp(const gt2Vector2& rV2, float t) const
	{
		return gt2Vector2::Lerp(*this, rV2, t);
	}

	/*!
	* @brief 0 ≦ t ≦ 1 の間でエルミート補間による滑らかな補間を行います。
	* @param [in]  rV1  1 番目のベクトル。
	* @param [in]  rV2  2 番目のベクトル。
	* @param [in]  t   ベクトル間を線形補間するパラメータ。範囲[0～1.0]
	* @return  補間されたベクトルを返す。
	*/
	inline static gt2Vector2 SmoothStep(const gt2Vector2& rV1, const gt2Vector2& rV2, float t)
	{
		t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
		t = t*t*(3.f - 2.f*t);
		return gt2Vector2::Lerp(rV1, rV2, t);
	}
	/*!
	* @brief 0 ≦ t ≦ 1 の間でエルミート補間による滑らかな補間を行います。
	*   第 1 番目のベクトルが、自身(this)です。
	* @param [in]  rV  2 番目のベクトル。
	* @param [in]  t   ベクトル間を線形補間するパラメータ。範囲[0～1.0]
	* @return  補間されたベクトルを返す。
	*/
	inline gt2Vector2 SmoothStep(const gt2Vector2& rV2, float t) const
	{
		return gt2Vector2::SmoothStep(*this, rV2, t);
	}
	/*!
	* @brief 指定された位置ベクトルを使用して、重心座標のポイントを返します。
	* @param [in]  rV1  第 1 の位置
	* @param [in]  rV2  第 2 の位置
	* @param [in]  rV3  第 3 の位置
	* @param [in]  f    加重係数。
	* @param [in]  g    加重係数。
	* @return  重心座標を返します。
	*/
	inline static gt2Vector2 Barycentric(const gt2Vector2& rV1, const gt2Vector2& rV2, const gt2Vector2& rV3, float f, float g)
	{
		return rV1 + f * (rV2 - rV1) + g * (rV3 - rV1);
	}
	/*!
	* @brief 指定された位置ベクトルを使用して、重心座標のポイントを返します。
	*   第 1 の位置が、自身(this)です。
	* @param [in]  rV2  第 2 の位置
	* @param [in]  rV3  第 3 の位置
	* @param [in]  f    加重係数。
	* @param [in]  g    加重係数。
	* @return  重心座標を返します。
	*/
	inline gt2Vector2 Barycentric(const gt2Vector2& rV2, const gt2Vector2& rV3, float f, float g) const
	{
		return gt2Vector2::Barycentric(*this, rV2, rV3, f, g);
	}
	/*!
	* @brief 指定された位置ベクトルを使用して、Catmull-Rom 補間を行います。
	* @param [in]  rV1  第 1 の位置
	* @param [in]  rV2  第 2 の位置
	* @param [in]  rV3  第 3 の位置
	* @param [in]  rV4  第 3 の位置
	* @param [in]  t    補間制御係数
	* @return  Catmull-Rom 補間の結果を返します。
	*/
	inline static gt2Vector2 CatmullRom(const gt2Vector2& rV1, const gt2Vector2& rV2, const gt2Vector2& rV3, const gt2Vector2& rV4, float t)
	{
		float t2 = t * t;
		float t3 = t * t2;
		return ((-t3 + 2 * t2 - t) * rV1 +
			(3 * t3 - 5 * t2 + 2) * rV2 +
			(-3 * t3 + 4 * t2 + t) * rV3 +
			(t3 - t2) * rV4) * 0.5f;
	}
	/*!
	* @brief 指定された位置ベクトルを使用して、Catmull-Rom 補間を行います。
	*   第 1 の位置が、自身(this)です。
	* @param [in]  rV2  第 2 の位置
	* @param [in]  rV3  第 3 の位置
	* @param [in]  rV4  第 3 の位置
	* @param [in]  t    補間制御係数
	* @return  Catmull-Rom 補間の結果を返します。
	*/
	inline gt2Vector2 CatmullRom(const gt2Vector2& rV2, const gt2Vector2& rV3, const gt2Vector2& rV4, float t) const
	{
		return gt2Vector2::CatmullRom(*this, rV2, rV3, rV4, t);
	}
	/*!
	* @brief 指定されたベクトルを使用して、エルミート スプライン補間を実行します。
	* @param [in]  rV1  補間が行われる第 1 の位置
	* @param [in]  rT1  第 1 の位置の接線ベクトル
	* @param [in]  rV2  補間が行われる第 2 の位置
	* @param [in]  rT2  第 2 の位置の接線ベクトル
	* @param [in]  t    補間制御係数
	* @return  補間が含まれたベクトルを返します。
	*/
	inline static gt2Vector2 Hermite(const gt2Vector2& rV1, const gt2Vector2& rT1, const gt2Vector2& rV2, const gt2Vector2& rT2, float t)
	{
		float t2 = t * t;
		float t3 = t * t2;
		return (2 * t3 - 3 * t2 + 1) * rV1 +
			(t3 - 2 * t2 + t) * rT1 +
			(-2 * t3 + 3 * t2) * rV2 +
			(t3 - t2) * rT2;
	}
	/*!
	* @brief 指定されたベクトルを使用して、エルミート スプライン補間を実行します。
	*   第 1 の位置が、自身(this)です。
	* @param [in]  rT1  第 1 の位置の接線ベクトル
	* @param [in]  rV2  補間が行われる第 2 の位置
	* @param [in]  rT2  第 2 の位置の接線ベクトル
	* @param [in]  t    補間制御係数
	* @return  補間が含まれたベクトルを返します。
	*/
	inline gt2Vector2 Hermite(const gt2Vector2& rT1, const gt2Vector2& rV2, const gt2Vector2& rT2, float t) const
	{
		return gt2Vector2::Hermite(*this, rT1, rV2, rT2, t);
	}
	/*!
	* @brief 2D 法線ベクトルによって 2D 入射ベクトルを反射します。
	* @param [in]  rvIncident  反射される 2D 入射ベクトル
	* @param [in]  rvNormal    入射ベクトルを反射する 2D 法線ベクトル
	* @return  反射後の入射角を返します。
	*/
	inline static gt2Vector2 Refract(const gt2Vector2& rvIncident, const gt2Vector2& rvNormal)
	{
		return rvIncident - (2 * rvIncident.Dot(rvNormal)) * rvNormal;
	}
	/*!
	* @brief 2D 法線ベクトルによって 2D 入射ベクトルを反射します。
	*   反射される 2D 入射ベクトルが、自身(this)です。
	* @param [in]  rvNormal    入射ベクトルを反射する 2D 法線ベクトル
	* @return  反射後の入射角を返します。
	*/
	inline gt2Vector2 Refract(const gt2Vector2& rvNormal) const
	{
		return gt2Vector2::Refract(*this, rvNormal);
	}
	/*!
	* @brief 2D 法線ベクトルによって 2D 入射ベクトルを反射します。
	* @param [in]  rvIncident      反射される 2D 入射ベクトル
	* @param [in]  rvNormal        入射ベクトルを反射する 2D 法線ベクトル
	* @param [in]  refractionIndex 屈折率。
	* @return  屈折された入射ベクトルを返します。屈折率、および入射ベクトルと法線ベクトル間の角度によって、
	*          結果が全反射になった場合は、< 0.0f, 0.0f > という形のベクトルが返されます。
	*/
	inline static gt2Vector2 Refract(const gt2Vector2& rvIncident, const gt2Vector2& rvNormal, float refractionIndex)
	{
		gt2Vector2 Result;
		float t = rvIncident.Dot(rvNormal);

		float r = 1.0f - refractionIndex * refractionIndex * (1.0f - t * t);
		if (r < 0.0f) // 全反射
		{
			Result.x = 0.0f;
			Result.y = 0.0f;
		}
		else {
			float s = refractionIndex * t + sqrtf(r);
			Result.x = refractionIndex * rvIncident.x - s * rvNormal.x;
			Result.y = refractionIndex * rvIncident.y - s * rvNormal.y;
		}
		return Result;
	}
	/*!
	* @brief 2D 法線ベクトルによって 2D 入射ベクトルを反射します。
	*   反射される 2D 入射ベクトルが、自身(this)です。
	* @param [in]  rvNormal        入射ベクトルを反射する 2D 法線ベクトル
	* @param [in]  refractionIndex 屈折率。
	* @return  屈折された入射ベクトルを返します。屈折率、および入射ベクトルと法線ベクトル間の角度によって、
	*          結果が全反射になった場合は、< 0.0f, 0.0f > という形のベクトルが返されます。
	*/
	inline gt2Vector2 Refract(const gt2Vector2& rvNormal, float refractionIndex) const
	{
		return gt2Vector2::Refract(*this, rvNormal, refractionIndex);
	}
	/*!
	* @brief lの長さをベクトルの長さとで割った値を、ベクトルの各要素に乗算した値をセットする
	* @param [in]  rV  運動ベクトル
	* @param [in]  l   長さ
	* @return  なし
	*/
	inline void SetMakeLength(const gt2Vector2& rV, float l)
	{
		float fLen = rV.Length();
		x = rV.x * l / fLen;
		y = rV.y * l / fLen;
	}
	/*!
	* @brief  x,y の値と内部の値と比較し、大きい値をそれぞれセットする
	* @param [in]  rV  ベクトル
	* @return  なし
	*/
	inline void SetMax(const gt2Vector2& rV)
	{
		this->SetMax(rV.x, rV.y);
	}
	/*!
	* @brief  x,y の値と内部の値と比較し、大きい値をそれぞれセットする
	* @param [in]  fx  要素 x
	* @param [in]  fy  要素 y
	* @return  なし
	*/
	inline void SetMax(float fx, float fy)
	{
		x = x>fx ? x : fx;
		y = y>fy ? y : fy;
	}
	/*!
	* @brief  x,y の値と内部の値と比較し、小さい値をそれぞれセットする
	* @param [in]  rV  ベクトル
	* @return  なし
	*/
	inline void SetMin(const gt2Vector2& rV2)
	{
		this->SetMin(rV2.x, rV2.y);
	}
	/*!
	* @brief  x,y の値と内部の値と比較し、小さい値をそれぞれセットする
	* @param [in]  fx  要素 x
	* @param [in]  fy  要素 y
	* @return  なし
	*/
	inline void SetMin(float fx, float fy)
	{
		x = x<fx ? x : fx;
		y = y<fy ? y : fy;
	}
	/*!
	* @brief   Radian値を取得する
	* @return   Radian値を取得する
	*/
	inline float GetAxisZRadian() const
	{
		if (y < 0)
		{
			// 180°以上
			float f = GT2_PI2 - acos(x);
			return f == GT2_PI2 ? 0 : f;
		}
		return acos(x);
	}
	/*!
	* @brief   角度を取得する
	* @return   角度を返す
	*/
	inline float GetAxisZAngle() const
	{
		return GetAxisZRadian() * GT2_RADIAN;
	}

	/*!
	* @brief   自身のx,y の値を少数を四捨五入する
	* @return   なし
	*/
	inline void MyRound()
	{
		x = floor(x + 0.5f);
		y = floor(y + 0.5f);
	}
	/*!
	* @brief   自身のx,y の値の少数を切り捨て
	* @return   なし
	*/
	inline void MyFloor()
	{
		x = floor(x);
		y = floor(y);
	}
	/*!
	* @brief   自身のx,yのそれぞれを角度からラジアン値へ
	* @return   なし
	*/
	inline void ToRadianFromAngle()
	{
		x *= GT2_RADIAN;
		y *= GT2_RADIAN;
	}
	/*!
	* @brief   自身のx,yのそれぞれをラジアンから角度値へ
	* @return   なし
	*/
	inline void ToAngleFromRadian()
	{
		x *= GT2_INV_RADIAN;
		y *= GT2_INV_RADIAN;
	}
};
const gt2Vector2 g_VF2IdentityR0 = gt2Vector2(1, 0);
const gt2Vector2 g_VF2IdentityR1 = gt2Vector2(0, 1);









/*!
* @brief 3要素(x,y,z) ベクトル
*/
typedef struct gt2Vector3
{
public:
	union {
		struct {
			float x;	//!< 要素 x
			float y;	//!< 要素 y
			float z;	//!< 要素 z
		};
		float v[3];		//!< v[0] = x, v[1] = y, v[2] = z
	};
public:

	/*!
	* @brief コンストラクタ
	*  x,y,zが０で初期化される
	*/
	gt2Vector3() { this->Init(); }
	/*!
	* @brief コンストラクタ
	*   x,y,zがpfポインタの値により初期化される
	* @param [in] pf     3要素以上のfloat情報があるポインタ
	*/
	gt2Vector3(const float * pF) { x = pF[0]; y = pF[1]; z = pF[2]; }
	/*!
	* @brief コンストラクタ
	*  rVで初期化される
	* @param [in] rV     ベクトル
	*/
	gt2Vector3(const gt2Vector3& rV3) { *this = rV3; }
	/*!
	* @brief コンストラクタ
	*   x=fx,y=fy,z=fz といった感じに初期化される
	* @param [in] fx     x値
	* @param [in] fy     y値
	* @param [in] fz     y値
	*/
	gt2Vector3(float fx, float fy, float fz) { x = fx; y = fy; z = fz; }

#ifdef B2_MATH_H
	gt2Vector3& operator= (const b2Vec3& v3) { x = v3.x; y = v3.y; z = v3.z; return *this; }
#endif

#if defined(MC_DIRECTX)
	//gt2Vector3&   operator= (const DirectX::XMFLOAT2& vf) { x = vf.x; y = vf.y; return *this; }
	//gt2Vector3&   operator= (const DirectX::XMFLOAT3& vf) { x = vf.x; y = vf.y; z = vf.z; return *this; }
	//gt2Vector3&   operator= (const DirectX::XMFLOAT4& vf) { x = vf.x; y = vf.y; z = vf.z; return *this; }
	//gt2Vector3&   operator= (const DirectX::XMVECTOR& vf) { x = vf.m128_f32[0]; y = vf.m128_f32[1]; z = vf.m128_f32[2]; return *this; }

	//DirectX::XMFLOAT2 GetXMFLOAT2() const { DirectX::XMFLOAT2 t; t.x = x; t.y = y; return t; }
	//DirectX::XMFLOAT3 GetXMFLOAT3() const { DirectX::XMFLOAT3 t; t.x = x; t.y = y; t.z = z; return t; }
	//DirectX::XMFLOAT4 GetXMFLOAT4() const { DirectX::XMFLOAT4 t; t.x = x; t.y = y; t.z = z; t.w = 0; return t; }
	//DirectX::XMVECTOR GetXMVECTOR() const { DirectX::XMVECTOR t; t.m128_f32[0] = x; t.m128_f32[1] = y; t.m128_f32[2] = z; t.m128_f32[3] = 0; return t; }

#endif

	/*!
	* @brief x,y,zの値が０で初期化される
	* @return なし
	*/
	inline void Init() { x = y = z = 0; }
	/*!
	* @brief x,y,zの値がfloat型の最小値のFLT_MAXで初期化される
	* @return なし
	*/
	inline void InitMin() { x = y = z = FLT_MAX; }
	/*!
	* @brief x,y,zの値がfloat型の最小値のFLT_MAXで初期化される
	* @return なし
	*/
	inline void InitMax() { x = y = z = -FLT_MAX; }
	/**
	* @param [in] fx     x値
	* @param [in] fy     y値
	* @param [in] fz     z値
	*/
	inline void Set(float fx, float fy, float fz) { x = fx; y = fy; z = fz; }

	//------------------------------------------------------------------------
	//
	// 代入演算子
	//
	//------------------------------------------------------------------------
	/*!
	* @brief 代入演算子 =
	*   通常の代入
	* @param [in] v     右辺のベクトルgt2Vector3
	* @return 加算されたベクトル値を返す
	*/
	inline gt2Vector3& operator = (const gt2Vector3& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}
	/*!
	* @brief 代入演算子 =
	*   自身(this)のベクトル値へ右辺の2要素のベクトルを代入する。zは常に０。
	* @param [in] rV     右辺の2要素ベクトル
	* @return 代入された2要素のベクトルを元に3要素のベクトルを返す。
	*/
	inline gt2Vector3& operator = (const gt2Vector2& rV)
	{
		x = rV.x;
		y = rV.y;
		z = 0.0f;

		return *this;
	}

	/*!
	* @brief 代入演算子 +=
	*   自身(this)のベクトル値を右辺のベクトル値を加算した値を自身(this)にセットする
	* @param [in] rV     右辺のベクトルgt2Vector3
	* @return 加算されたベクトル値を返す
	*/
	inline gt2Vector3& operator += (const gt2Vector3& rV)
	{
		x += rV.x;
		y += rV.y;
		z += rV.z;

		return *this;
	}
	/*!
	* @brief 代入演算子 -=
	*   自身(this)のベクトル値を右辺のベクトル値を減算した値を自身(this)にセットする
	* @param [in] rV     右辺のベクトルgt2Vector3
	* @return 減算されたベクトル値を返す
	*/
	inline gt2Vector3& operator -= (const gt2Vector3& rV)
	{
		x -= rV.x;
		y -= rV.y;
		z -= rV.z;

		return *this;
	}
	inline gt2Vector3& operator *= (const gt2Vector3& v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}

	inline gt2Vector3& operator /= (const gt2Vector3& v)
	{
		x /= v.x;
		y /= v.y;
		z /= v.z;
		return *this;
	}

	/*!
	* @brief 代入演算子 *=
	*   自身(this)のベクトル値を右辺の１つの値を乗算した値を自身(this)にセットする
	* @param [in] f     右辺の1つの値
	* @return 乗算されたベクトル値を返す
	*/
	inline gt2Vector3& operator *= (float f)
	{
		x *= f;
		y *= f;
		z *= f;

		return *this;
	}
	/*!
	* @brief 代入演算子 *=
	*   自身(this)のベクトル値を右辺の１つの値を除算した値を自身(this)にセットする
	* @param [in] f     右辺の1つの値
	* @return 除算されたベクトル値を返す
	*/
	inline gt2Vector3& operator /= (float f)
	{
		x /= f;
		y /= f;
		z /= f;

		return *this;
	}

	//##################################################################
	//##
	//## 単項演算子
	//##
	//##################################################################
	/*!
	* @brief 単項演算子 +
	*   +を付けただけで、特に値は変更なし
	* @return そのままのベクトル値を返す
	*/
	inline gt2Vector3 operator + () const
	{
		return *this;
	}
	/*!
	* @brief 単項演算子 -
	*   各要素に-1を乗算したベクトル値になる
	* @return 各要素に-1を乗算したベクトル値を返す
	*/
	inline gt2Vector3 operator - () const
	{
		return gt2Vector3(-x, -y, -z);
	}

	//##################################################################
	//##
	//## 二単項演算子
	//##
	//##################################################################
	/*!
	* @brief 二項演算子 +
	*   自身(this)のベクトルと"rV"ベクトルを加算する
	* @param [in] rV     gt2Vector3
	* @return 自身(this)のベクトルと"rV"ベクトル値を加算した値を返す
	*/
	inline gt2Vector3 operator + (const gt2Vector3& rV) const
	{
		gt2Vector3 vTmp;

		vTmp.x = x + rV.x;
		vTmp.y = y + rV.y;
		vTmp.z = z + rV.z;

		return vTmp;
	}
	/*!
	* @brief 二項演算子 -
	*   自身(this)のベクトルと"rV"ベクトルを減算する
	* @param [in] rV     gt2Vector3
	* @return 自身(this)のベクトルと"rV"ベクトル値を減算した値を返す
	*/
	inline gt2Vector3 operator - (const gt2Vector3& rV) const
	{
		gt2Vector3 vTmp;

		vTmp.x = x - rV.x;
		vTmp.y = y - rV.y;
		vTmp.z = z - rV.z;

		return vTmp;
	}
	/*!
	* @brief 二項演算子 +
	*   自身(this)のベクトルの要素ごに"f"の値を加算する
	* @param [in] f     1つの値
	* @return 自身(this)のベクトルの要素ごに"f"の値を加算した値を返す
	*/
	inline gt2Vector3 operator + (float f) const
	{
		gt2Vector3 vTmp;

		vTmp.x = x + f;
		vTmp.y = y + f;
		vTmp.z = z + f;

		return vTmp;
	}
	/*!
	* @brief 二項演算子 -
	*   自身(this)のベクトルの要素ごに"f"の値を減算する
	* @param [in] f     1つの値
	* @return 自身(this)のベクトルの要素ごに"f"の値を減算した値を返す
	*/
	inline gt2Vector3 operator - (float f) const
	{
		gt2Vector3 vTmp;

		vTmp.x = x - f;
		vTmp.y = y - f;
		vTmp.z = z - f;

		return vTmp;
	}
	/*!
	* @brief 二項演算子 *
	*   自身(this)のベクトルの要素ごに"f"の値を乗算する
	* @param [in] f     1つの値
	* @return 自身(this)のベクトルの要素ごに"f"の値を乗算した値を返す
	*/
	inline gt2Vector3 operator * (float f) const
	{
		gt2Vector3 vTmp;

		vTmp.x = x * f;
		vTmp.y = y * f;
		vTmp.z = z * f;

		return vTmp;
	}

	friend inline gt2Vector3 operator * (float f, const gt2Vector3& rV3)
	{
		return rV3 * f;
	}
	/*!
	* @brief 二項演算子 *
	*   自身(this)のベクトルと"rV"ベクトルの要素ごと乗算する
	* @param [in] rV     gt2Vector3
	* @return 自身(this)のベクトルと"rV"ベクトルの要素ごと乗算した値を返す
	*/
	inline gt2Vector3 operator * (const gt2Vector3& rV) const
	{
		gt2Vector3 vTmp;

		vTmp.x = x * rV.x;
		vTmp.y = y * rV.y;
		vTmp.z = z * rV.z;

		return vTmp;
	}

	friend inline gt2Vector3 operator + (float f, const gt2Vector3& rV3)
	{
		return rV3 + f;
	}

	friend inline gt2Vector3 operator - (float f, const gt2Vector3& rV3)
	{
		return rV3 - f;
	}
	/*!
	* @brief 二項演算子 /
	*   自身(this)のベクトルの要素ごに"f"の値を除算する
	* @param [in] f     1つの値
	* @return 自身(this)のベクトルの要素ごに"f"の値を除算した値を返す
	*/
	inline gt2Vector3 operator / (float f) const
	{
		gt2Vector3 vTmp;

		vTmp.x = x / f;
		vTmp.y = y / f;
		vTmp.z = z / f;

		return vTmp;
	}
	/*!
	* @brief 二項演算子 /
	*   自身(this)のベクトルと"rV"ベクトルの要素ごと除算する
	* @param [in] rV     gt2Vector2
	* @return 自身(this)のベクトルと"rV"ベクトルの要素ごと除算した値を返す
	*/
	inline gt2Vector3 operator / (const gt2Vector3& rV) const
	{
		gt2Vector3 vTmp;

		vTmp.x = x / rV.x;
		vTmp.y = y / rV.y;
		vTmp.z = z / rV.z;

		return vTmp;
	}


	//##################################################################
	//##
	//## 比較演算子
	//##
	//##################################################################
	/*!
	* @brief 比較演算子 ==
	*   自身(this)のベクトルと"rV"ベクトルの各要素が同じか比較する
	* @param [in] rV     gt2Vector3
	* @return 自身(this)のベクトルと"rV"ベクトルの各要素を比較し、同一ならtrueを返す。
	*/
	inline bool operator == (const gt2Vector3& rV) const
	{
		return x == rV.x && y == rV.y && z == rV.z;
	}
	/*!
	* @brief 比較演算子 !=
	*   自身(this)のベクトルと"rV"ベクトルの各要素が違うか比較する
	* @param [in] rV     gt2Vector3
	* @return 自身(this)のベクトルと"rV"ベクトルの各要素を比較し、違う場合trueを返す。
	*/
	inline bool operator != (const gt2Vector3& rV) const
	{
		return !(*this == rV);
	}



	//##################################################################
	//##
	//## 
	//##
	//##################################################################
	/*!
	* @brief  gt2Vector2の値を返す。
	* @return  gt2Vector2
	*/
	inline gt2Vector2 GetV2() const { return gt2Vector2(x,y); }

	/*!
	* @brief  x,y,z の値と内部の値と比較し、大きい値をそれぞれセットする
	* @param [in]  rV  ベクトル
	* @return  なし
	*/
	inline void SetMax(const gt2Vector3& rV)
	{
		this->SetMax(rV.x, rV.y, rV.z);
	}
	/*!
	* @brief  x,y,z の値と内部の値と比較し、大きい値をそれぞれセットする
	* @param [in]  fx  要素 x
	* @param [in]  fy  要素 y
	* @param [in]  fz  要素 z
	* @return  なし
	*/
	inline void SetMax(float fx, float fy, float fz)
	{
		x = x>fx ? x : fx;
		y = y>fy ? y : fy;
		z = z>fz ? z : fz;
	}
	/*!
	* @brief   自身のx,y,z の値を少数を四捨五入する
	* @return   なし
	*/
	inline void MyRound()
	{
		x = floor(x + 0.5f);
		y = floor(y + 0.5f);
		z = floor(z + 0.5f);
	}
	/*!
	* @brief   自身のx,y,z の値の少数を切り捨て
	* @return   なし
	*/
	inline void MyFloor()
	{
		x = floor(x);
		y = floor(y);
		z = floor(z);
	}
	/*!
	* @brief   自身のx,y,zのそれぞれを角度からラジアン値へ
	* @return   なし
	*/
	inline void ToRadianFromAngle()
	{
		x *= GT2_RADIAN;
		y *= GT2_RADIAN;
		z *= GT2_RADIAN;
	}
	/*!
	* @brief   自身のx,y,zのそれぞれをラジアンから角度値へ
	* @return   なし
	*/
	inline void ToAngleFromRadian()
	{
		x *= GT2_INV_RADIAN;
		y *= GT2_INV_RADIAN;
		z *= GT2_INV_RADIAN;
	}

	/*!
	* @brief  x,y,z の値と内部の値と比較し、小さい値をそれぞれセットする
	* @param [in]  rV  ベクトル
	* @return  なし
	*/
	inline void SetMin(const gt2Vector3& rV)
	{
		this->SetMin(rV.x, rV.y, rV.z);
	}
	/*!
	* @brief  x,y,z の値と内部の値と比較し、小さい値をそれぞれセットする
	* @param [in]  fx  要素 x
	* @param [in]  fy  要素 y
	* @param [in]  fz  要素 z
	* @return  なし
	*/
	inline void SetMin(float fx, float fy, float fz)
	{
		x = x<fx ? x : fx;
		y = y<fy ? y : fy;
		z = z<fz ? z : fz;
	}
	/*!
	* @brief 角度(0～360)からラジアン値に変換してx,y,zに代入する
	* @param [in] fx     角度(0～360)
	* @param [in] fy     角度(0～360)
	* @param [in] fz     角度(0～360)
	* @return なし
	*/
	inline void MakeRadianToDegrees(float fx, float fy, float fz)
	{
		x = GT2_INV_RADIAN * fx;
		y = GT2_INV_RADIAN * fy;
		z = GT2_INV_RADIAN * fz;
	}

	/*!
	* @brief ベクトルの長さを返す。
	* @return ベクトルの長さを返す。
	*/
	inline float Length() const
	{
		return sqrt(x*x + y*y + z*z);
	}
	/*!
	* @brief ベクトルの長さの 2 乗を返す。
	* @return ベクトルの長さの 2 乗を返す。
	*/
	inline float LengthSq() const
	{
		return x*x + y*y + z*z;
	}
	/*!
	* @brief 内積
	*   ベクトルの内積を求めます。
	* @return  内積を返す。
	*/
	inline float Dot() const
	{
		return x*x + y*y + z*z;
	}
	/*!
	* @brief 内積
	*   自身(this)のベクトルと"rV"ベクトルを内積する
	* @param [in] rV     対象ベクトル
	* @return  内積を返す。
	*/
	inline float Dot(const gt2Vector3& rV) const
	{
		return x*rV.x + y*rV.y + z*rV.z;
	}
	/*!
	* @brief 外積
	*   v = rV1 × rV2
	* @param [in] rV1     1つめの対象ベクトル
	* @param [in] rV2     2つめの対象ベクトル
	* @return  外積したベクトルを返す。
	*/
	inline static gt2Vector3 Cross(const gt2Vector3& rV1, const gt2Vector3& rV2)
	{
		gt2Vector3 out;
		out.x = rV1.y*rV2.z - rV1.z*rV2.y;
		out.y = -(rV1.x*rV2.z - rV1.z*rV2.x);
		out.z = rV1.x*rV2.y - rV1.y*rV2.x;
		return out;
	}
	/*!
	* @brief 外積
	*   v = 自身(this) × rV
	* @param [in] rV     2つめの対象ベクトル
	* @return  外積されたベクトルを返す。
	*/
	inline gt2Vector3 Cross(const gt2Vector3& rV) const
	{
		return gt2Vector3::Cross(*this, rV);
	}
	/*!
	* @brief ベクトルの加算
	*   自身(this)のベクトルと"rV"ベクトルを加算する。
	* @param [in] rV     入力 gt2Vector2 構造体
	* @return  加算されたベクトルを返す。
	*/
	inline gt2Vector3 Add(const gt2Vector3& rV) const
	{
		gt2Vector3 out;
		out.x = x + rV.x;
		out.y = y + rV.y;
		out.z = z + rV.z;
		return out;
	}
	/*!
	* @brief ベクトルの減算
	*   自身(this)のベクトルと"rV"ベクトルを減算する。
	* @param [in] rV     入力 gt2Vector4 構造体
	* @return  減算されたベクトルを返す。
	*/
	inline gt2Vector3 Subtract(const gt2Vector3& rV) const
	{
		gt2Vector3 out;
		out.x = x - rV.x;
		out.y = y - rV.y;
		out.z = z - rV.z;
		return out;
	}
	/*!
	* @brief 2つのベクトルの要素を比較し最小値の要素のベクトルを返す
	* @param [in] rV     入力 gt2Vector3 構造体
	* @return  最小値の要素のベクトルを返す
	*/
	inline gt2Vector3 Minimize(const gt2Vector3& rV) const
	{
		gt2Vector3 out;
		out.x = x < rV.x ? x : rV.x;
		out.y = y < rV.y ? y : rV.y;
		out.z = z < rV.z ? z : rV.z;
		return out;
	}
	/*!
	* @brief 2つのベクトルの要素を比較し最大値の要素のベクトルを取得する
	* @param [in] rV     入力 gt2Vector3 構造体
	* @return  最大値の要素のベクトルを返す
	*/
	inline gt2Vector3 Maximize(const gt2Vector3& rV) const
	{
		gt2Vector3 out;
		out.x = x > rV.x ? x : rV.x;
		out.y = y > rV.y ? y : rV.y;
		out.z = z > rV.z ? z : rV.z;
		return out;
	}
	/*!
	* @brief 三重積 U・V×W
	* @param [in] rV     頂点V
	* @param [in] pW     頂点W
	* @return  三重積のベクトルを返す
	*/
	inline float ScalarTriple(const gt2Vector3& rV, const gt2Vector3* pW) const
	{
		return float((x * (rV.y*pW->z - rV.z*pW->y)) +
			(y * (-rV.x*pW->z + rV.z*pW->x)) +
			(z * (rV.x*pW->y - rV.y*pW->x)));

	}
	/*!
	* @brief 三重積 U・V×W
	* @param [in] rV     頂点V
	* @param [in] rW     頂点W
	* @return  三重積のベクトルを返す
	*/
	inline float ScalarTriple(const gt2Vector3& rV, const gt2Vector3& rW) const
	{
		return this->ScalarTriple(rV, &rW);
	}
	/*!
	* @brief ベクトルをスケーリングする。
	* @param [in]  s      スケーリング値。
	* @return  ベクトルをスケーリングしたものを返す。
	*/
	inline gt2Vector3 Scale(float s) const
	{
		return gt2Vector3(x * s, y * s, z * s);
	}
	/*!
	* @brief ベクトル間の線形補間を実行する。
	* @param [in]  rV1   第 1 番目のベクトル
	* @param [in]  rV2   第 2 番目のベクトル
	* @param [in]  t     ベクトル間を線形補間するパラメータ。
	* @return  線形補間されたベクトルを返す。
	*/
	inline static gt2Vector3 Lerp(const gt2Vector3& rV1, const gt2Vector3& rV2, float t)
	{
		return gt2Vector3(
			rV1.x + t * (rV2.x - rV1.x),
			rV1.y + t * (rV2.y - rV1.y),
			rV1.z + t * (rV2.z - rV1.z)
		);
	}
	/*!
	* @brief ベクトル間の線形補間を実行する。
	*   第 1 番目のベクトルが、自身(this)です。
	* @param [in]  rV2   第 2 番目のベクトル
	* @param [in]  t     ベクトル間を線形補間するパラメータ。
	* @return  線形補間されたベクトルを返す。
	*/
	inline gt2Vector3 Lerp(const gt2Vector3& rV2, float t) const
	{
		return gt2Vector3::Lerp(*this, rV2, t);
	}

	/*!
	* @brief 0 ≦ t ≦ 1 の間でエルミート補間による滑らかな補間を行います。
	* @param [in]  rV1  1 番目のベクトル。
	* @param [in]  rV2  2 番目のベクトル。
	* @param [in]  t   ベクトル間を線形補間するパラメータ。範囲[0～1.0]
	* @return  補間されたベクトルを返す。
	*/
	inline static gt2Vector3 SmoothStep(const gt2Vector3& rV1, const gt2Vector3& rV2, float t)
	{
		t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
		t = t*t*(3.f - 2.f*t);
		return gt2Vector3::Lerp(rV1, rV2, t);
	}
	/*!
	* @brief 0 ≦ t ≦ 1 の間でエルミート補間による滑らかな補間を行います。
	*   第 1 番目のベクトルが、自身(this)です。
	* @param [in]  rV  2 番目のベクトル。
	* @param [in]  t   ベクトル間を線形補間するパラメータ。範囲[0～1.0]
	* @return  補間されたベクトルを返す。
	*/
	inline gt2Vector3 SmoothStep(const gt2Vector3& rV2, float t) const
	{
		return gt2Vector3::SmoothStep(*this, rV2, t);
	}
	/*!
	* @brief 指定された位置ベクトルを使用して、重心座標のポイントを返します。
	* @param [in]  rV1  第 1 の位置
	* @param [in]  rV2  第 2 の位置
	* @param [in]  rV3  第 3 の位置
	* @param [in]  f    加重係数。
	* @param [in]  g    加重係数。
	* @return  重心座標を返します。
	*/
	inline static gt2Vector3 Barycentric(const gt2Vector3& rV1, const gt2Vector3& rV2, const gt2Vector3& rV3, float f, float g)
	{
		return rV1 + f * (rV2 - rV1) + g * (rV3 - rV1);
	}
	/*!
	* @brief 指定された位置ベクトルを使用して、重心座標のポイントを返します。
	*   第 1 の位置が、自身(this)です。
	* @param [in]  rV2  第 2 の位置
	* @param [in]  rV3  第 3 の位置
	* @param [in]  f    加重係数。
	* @param [in]  g    加重係数。
	* @return  重心座標を返します。
	*/
	inline gt2Vector3 Barycentric(const gt2Vector3& rV2, const gt2Vector3& rV3, float f, float g) const
	{
		return gt2Vector3::Barycentric(*this, rV2, rV3, f, g);
	}
	/*!
	* @brief 指定された位置ベクトルを使用して、Catmull-Rom 補間を行います。
	* @param [in]  rV1  第 1 の位置
	* @param [in]  rV2  第 2 の位置
	* @param [in]  rV3  第 3 の位置
	* @param [in]  rV4  第 3 の位置
	* @param [in]  t    補間制御係数
	* @return  Catmull-Rom 補間の結果を返します。
	*/
	inline static gt2Vector3 CatmullRom(const gt2Vector3& rV1, const gt2Vector3& rV2, const gt2Vector3& rV3, const gt2Vector3& rV4, float t)
	{
		float t2 = t * t;
		float t3 = t * t2;
		return ((-t3 + 2 * t2 - t) * rV1 +
			(3 * t3 - 5 * t2 + 2) * rV2 +
			(-3 * t3 + 4 * t2 + t) * rV3 +
			(t3 - t2) * rV4) * 0.5f;
	}
	/*!
	* @brief 指定された位置ベクトルを使用して、Catmull-Rom 補間を行います。
	*   第 1 の位置が、自身(this)です。
	* @param [in]  rV2  第 2 の位置
	* @param [in]  rV3  第 3 の位置
	* @param [in]  rV4  第 3 の位置
	* @param [in]  t    補間制御係数
	* @return  Catmull-Rom 補間の結果を返します。
	*/
	inline gt2Vector3 CatmullRom(const gt2Vector3& rV2, const gt2Vector3& rV3, const gt2Vector3& rV4, float t) const
	{
		return gt2Vector3::CatmullRom(*this, rV2, rV3, rV4, t);
	}
	/*!
	* @brief 指定されたベクトルを使用して、エルミート スプライン補間を実行します。
	* @param [in]  rV1  補間が行われる第 1 の位置
	* @param [in]  rT1  第 1 の位置の接線ベクトル
	* @param [in]  rV2  補間が行われる第 2 の位置
	* @param [in]  rT2  第 2 の位置の接線ベクトル
	* @param [in]  t    補間制御係数
	* @return  補間が含まれたベクトルを返します。
	*/
	inline static gt2Vector3 Hermite(const gt2Vector3& rV1, const gt2Vector3& rT1, const gt2Vector3& rV2, const gt2Vector3& rT2, float t)
	{
		float t2 = t * t;
		float t3 = t * t2;
		return (2 * t3 - 3 * t2 + 1) * rV1 +
			(t3 - 2 * t2 + t) * rT1 +
			(-2 * t3 + 3 * t2) * rV2 +
			(t3 - t2) * rT2;
	}
	/*!
	* @brief 指定されたベクトルを使用して、エルミート スプライン補間を実行します。
	*   第 1 の位置が、自身(this)です。
	* @param [in]  rT1  第 1 の位置の接線ベクトル
	* @param [in]  rV2  補間が行われる第 2 の位置
	* @param [in]  rT2  第 2 の位置の接線ベクトル
	* @param [in]  t    補間制御係数
	* @return  補間が含まれたベクトルを返します。
	*/
	inline gt2Vector3 Hermite(const gt2Vector3& rT1, const gt2Vector3& rV2, const gt2Vector3& rT2, float t) const
	{
		return gt2Vector3::Hermite(*this, rT1, rV2, rT2, t);
	}
	/*!
	* @brief 3D 法線ベクトルによって 3D 入射ベクトルを反射します。
	* @param [in]  rvIncident  反射される 3D 入射ベクトル
	* @param [in]  rvNormal    入射ベクトルを反射する 3D 法線ベクトル
	* @return  反射後の入射角を返します。
	*/
	inline static gt2Vector3 Refract(const gt2Vector3& rvIncident, const gt2Vector3& rvNormal)
	{
		return rvIncident - (2 * rvIncident.Dot(rvNormal)) * rvNormal;
	}
	/*!
	* @brief 3D 法線ベクトルによって 3D 入射ベクトルを反射します。
	*   反射される 3D 入射ベクトルが、自身(this)です。
	* @param [in]  rvNormal    入射ベクトルを反射する 3D 法線ベクトル
	* @return  反射後の入射角を返します。
	*/
	inline gt2Vector3 Refract(const gt2Vector3& rvNormal) const
	{
		return gt2Vector3::Refract(*this, rvNormal);
	}
	/*!
	* @brief 3D 法線ベクトルによって 3D 入射ベクトルを反射します。
	* @param [in]  rvIncident      反射される 3D 入射ベクトル
	* @param [in]  rvNormal        入射ベクトルを反射する 3D 法線ベクトル
	* @param [in]  refractionIndex 屈折率。
	* @return  屈折された入射ベクトルを返します。屈折率、および入射ベクトルと法線ベクトル間の角度によって、
	*          結果が全反射になった場合は、< 0.0f, 0.0f, 0.0f > という形のベクトルが返されます。
	*/
	inline static gt2Vector3 Refract(const gt2Vector3& rvIncident, const gt2Vector3& rvNormal, float refractionIndex)
	{
		gt2Vector3 Result;
		float t = rvIncident.Dot(rvNormal);

		float r = 1.0f - refractionIndex * refractionIndex * (1.0f - t * t);
		if (r < 0.0f) // 全反射
		{
			Result.x = 0.0f;
			Result.y = 0.0f;
			Result.z = 0.0f;
		}
		else {
			float s = refractionIndex * t + sqrtf(r);
			Result.x = refractionIndex * rvIncident.x - s * rvNormal.x;
			Result.y = refractionIndex * rvIncident.y - s * rvNormal.y;
			Result.z = refractionIndex * rvIncident.z - s * rvNormal.z;
		}
		return Result;
	}
	/*!
	* @brief 3D 法線ベクトルによって 2D 入射ベクトルを反射します。
	*   反射される 3D 入射ベクトルが、自身(this)です。
	* @param [in]  rvNormal        入射ベクトルを反射する 3D 法線ベクトル
	* @param [in]  refractionIndex 屈折率。
	* @return  屈折された入射ベクトルを返します。屈折率、および入射ベクトルと法線ベクトル間の角度によって、
	*          結果が全反射になった場合は、< 0.0f, 0.0f, 0.0f > という形のベクトルが返されます。
	*/
	inline gt2Vector3 Refract(const gt2Vector3& rvNormal, float refractionIndex) const
	{
		return gt2Vector3::Refract(*this, rvNormal, refractionIndex);
	}
	/*!
	* @brief lの長さをベクトルの長さとで割った値を、ベクトルの各要素に乗算した値をセットする
	* @param [in]  rV  運動ベクトル
	* @param [in]  l   長さ
	* @return  なし
	*/
	inline void SetMakeLength(const gt2Vector3& rV, float fL) {
		float fLen = rV.Length();
		x = rV.x * fL / fLen;
		y = rV.y * fL / fLen;
		z = rV.z * fL / fLen;
	}
	/*!
	* @brief 自身(this)のベクトルを正規化する。
	* @return  なし
	*/
	inline void Normalize()
	{
		float fL = this->Length();
		if (fL == 0.0f)
			return;

		fL = 1.0f / fL;
		x *= fL;
		y *= fL;
		z *= fL;
	}
	/*!
	* @brief ベクトルを正規化したベクトルを返します。
	* @param [out] pOut     演算結果である gt2Vector3 構造体へのポインタ。
	* @return  ベクトルを正規化したベクトルを返す。
	*/
	inline gt2Vector3* Normalize(gt2Vector3* pOut) const
	{
		float fL = this->Length();
		if (fL == 0.0f) {
			*pOut = gt2Vector3(0.0f, 0.0f, 0.0f);
			return pOut;
		}
		*pOut = *this;

		fL = 1.0f / fL;
		pOut->x *= fL;
		pOut->y *= fL;
		pOut->z *= fL;
		return pOut;
	}
	/*!
	* @brief ベクトルを正規化したベクトルを返す。
	* @param [out] rOut     演算結果である gt2Vector3。
	* @return  なし
	*/
	inline void Normalize(gt2Vector3& rOut) const
	{
		this->Normalize(&rOut);
	}

	/*!
	* @brief ベクトルの要素を、指定された最大値と最小値の範囲にクランプします。
	* @param [in] rMin     最小範囲ベクトル
	* @param [in] rMax     最大範囲ベクトル
	* @return  なし
	*/
	void Clamp(const gt2Vector3& rMin, const gt2Vector3& rMax)
	{
		x = std::min(std::max(x, rMin.x), rMax.x);
		y = std::min(std::max(y, rMin.y), rMax.y);
		z = std::min(std::max(z, rMin.z), rMax.z);
	}

} gt2Vector3, *LPMC_VECTOR3;
const gt2Vector3 g_VF3IdentityR0 = gt2Vector3(1, 0, 0);
const gt2Vector3 g_VF3IdentityR1 = gt2Vector3(0, 1, 0);
const gt2Vector3 g_VF3IdentityR2 = gt2Vector3(0, 0, 1);

#define MCVectorF3_CAST_P(_p) \
(reinterpret_cast<gt2Vector3*>(&_p))
#define MCVectorF3_CAST(_p) \
(*(reinterpret_cast<gt2Vector3*>(&_p)))








/*!
* @brief 4要素(x,y,z,w) ベクトル
*/
typedef struct gt2Vector4
{
public:
	union {
		struct {
			float x;	//!< 要素 x
			float y;	//!< 要素 y
			float z;	//!< 要素 z
			float w;	//!< 要素 w
		};
		float v[4];		//!< v[0] = x, v[1] = y, v[2] = z, v[3] = w
	};
public:
	/*!
	* @brief コンストラクタ
	*  x,y,z,wが０で初期化される
	*/
	gt2Vector4() { this->Init(); }
	/*!
	* @brief コンストラクタ
	*   x,y,z,wがpfポインタの値により初期化される
	* @param [in] pf     4要素以上のfloat情報があるポインタ
	*/
	gt2Vector4(const float * pF) { x = pF[0]; y = pF[1]; z = pF[2]; w = pF[3]; }
	/*!
	* @brief コンストラクタ
	*  rVで初期化される
	* @param [in] rV     ベクトル
	*/
	gt2Vector4(const gt2Vector4& rV) { *this = rV; }
	/*!
	* @brief コンストラクタ
	*   x=fx,y=fy,z=fz,w=fw といった感じに初期化される
	* @param [in] fx     x値
	* @param [in] fy     y値
	* @param [in] fz     y値
	* @param [in] fw     w値
	*/
	gt2Vector4(float fx, float fy, float fz, float fw) { x = fx; y = fy; z = fz; w = fw; }


#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
	gt2Vector4&   operator= (const DirectX::XMFLOAT2& vf) { x = vf.x; y = vf.y; return *this; }
	gt2Vector4&   operator= (const DirectX::XMFLOAT3& vf) { x = vf.x; y = vf.y; z = vf.z; return *this; }
	gt2Vector4&   operator= (const DirectX::XMFLOAT4& vf) { x = vf.x; y = vf.y; z = vf.z; w = vf.w; return *this; }
	gt2Vector4&   operator= (const DirectX::XMVECTOR& vf) { x = vf.m128_f32[0]; y = vf.m128_f32[1]; z = vf.m128_f32[2]; w = vf.m128_f32[3]; return *this; }

	DirectX::XMFLOAT2 GetXMFLOAT2() const { DirectX::XMFLOAT2 t; t.x = x; t.y = y; return t; }
	DirectX::XMFLOAT3 GetXMFLOAT3() const { DirectX::XMFLOAT3 t; t.x = x; t.y = y; t.z = z; return t; }
	DirectX::XMFLOAT4 GetXMFLOAT4() const { DirectX::XMFLOAT4 t; t.x = x; t.y = y; t.z = z; t.w = w; return t; }
	DirectX::XMVECTOR GetXMVECTOR() const { DirectX::XMVECTOR tmp; memcpy(&tmp, this, sizeof(gt2Vector4)); return tmp; }

#endif
	/*!
	* @brief x,y,z,wの値が０で初期化される
	* @return なし
	*/
	inline void Init() { x = y = z = w = 0; }
	/*!
	* @brief x,y,z,wの値がfloat型の最小値のFLT_MAXで初期化される
	* @return なし
	*/
	inline void InitMin() { x = y = z = w = FLT_MAX; }
	/*!
	* @brief x,y,z,wの値がfloat型の最小値のFLT_MAXで初期化される
	* @return なし
	*/
	inline void InitMax() { x = y = z = w = -FLT_MAX; }

	/**
	* @param [in] fx     x値
	* @param [in] fy     y値
	* @param [in] fz     z値
	* @param [in] fw     w値
	*/
	inline void Set(float fx, float fy, float fz, float fw) { x = fx; y = fy; z = fz; w = fw; }

	//------------------------------------------------------------------------
	//
	// 代入演算子
	//
	//------------------------------------------------------------------------
	/*!
	* @brief 代入演算子 =
	*   通常の代入
	* @param [in] v     右辺のベクトルgt2Vector4
	* @return 加算されたベクトル値を返す
	*/
	inline gt2Vector4& operator = (const gt2Vector4& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
		return *this;
	}
	/*!
	* @brief 代入演算子 =
	*   自身(this)のベクトル値へ右辺の2要素のベクトルを代入する。zは常に０。
	* @param [in] rV     右辺の2要素ベクトル
	* @return 代入された2要素のベクトルを元に3要素のベクトルを返す。
	*/
	inline gt2Vector4& operator = (const gt2Vector2& rV)
	{
		x = rV.x;
		y = rV.y;
		z = w = 0.0f;

		return *this;
	}
	/*!
	* @brief 代入演算子 =
	*   自身(this)のベクトル値へ右辺の2要素のベクトルを代入する。zは常に０。
	* @param [in] rV     右辺の3要素ベクトル
	* @return 代入された2要素のベクトルを元に3要素のベクトルを返す。
	*/
	inline gt2Vector4& operator = (const gt2Vector3& rV)
	{
		x = rV.x;
		y = rV.y;
		z = rV.z;
		w = 0.0f;

		return *this;
	}
	/*!
	* @brief 代入演算子 +=
	*   自身(this)のベクトル値を右辺のベクトル値を加算した値を自身(this)にセットする
	* @param [in] rV     右辺のベクトルgt2Vector4
	* @return 加算されたベクトル値を返す
	*/
	inline gt2Vector4& operator += (const gt2Vector4& rV)
	{
		x += rV.x;
		y += rV.y;
		z += rV.z;
		w += rV.w;

		return *this;
	}
	/*!
	* @brief 代入演算子 -=
	*   自身(this)のベクトル値を右辺のベクトル値を減算した値を自身(this)にセットする
	* @param [in] rV     右辺のベクトルgt2Vector3
	* @return 減算されたベクトル値を返す
	*/
	inline gt2Vector4& operator -= (const gt2Vector4& rV)
	{
		x -= rV.x;
		y -= rV.y;
		z -= rV.z;
		w -= rV.w;

		return *this;
	}
	/*!
	* @brief 代入演算子 *=
	*   自身(this)のベクトル値を右辺の１つの値を乗算した値を自身(this)にセットする
	* @param [in] f     右辺の1つの値
	* @return 乗算されたベクトル値を返す
	*/
	inline gt2Vector4& operator *= (float f)
	{
		x *= f;
		y *= f;
		z *= f;
		w *= f;

		return *this;
	}
	/*!
	* @brief 代入演算子 *=
	*   自身(this)のベクトル値を右辺の１つの値を除算した値を自身(this)にセットする
	* @param [in] f     右辺の1つの値
	* @return 除算されたベクトル値を返す
	*/
	inline gt2Vector4& operator /= (float f)
	{
		x /= f;
		y /= f;
		z /= f;
		w /= f;

		return *this;
	}
	//##################################################################
	//##
	//## 単項演算子
	//##
	//##################################################################
	/*!
	* @brief 単項演算子 +
	*   +を付けただけで、特に値は変更なし
	* @return そのままのベクトル値を返す
	*/
	inline gt2Vector4 operator + () const
	{
		return *this;
	}
	/*!
	* @brief 単項演算子 -
	*   各要素に-1を乗算したベクトル値になる
	* @return 各要素に-1を乗算したベクトル値を返す
	*/
	inline gt2Vector4 operator - () const
	{
		return gt2Vector4(-x, -y, -z, -w);
	}


	//##################################################################
	//##
	//## 二単項演算子
	//##
	//##################################################################
	/*!
	* @brief 二項演算子 +
	*   自身(this)のベクトルと"rV"ベクトルを加算する
	* @param [in] rV     gt2Vector4
	* @return 自身(this)のベクトルと"rV"ベクトル値を加算した値を返す
	*/
	inline gt2Vector4 operator + (const gt2Vector4& rV) const
	{
		gt2Vector4 vTmp;

		vTmp.x = x + rV.x;
		vTmp.y = y + rV.y;
		vTmp.z = z + rV.z;
		vTmp.w = w + rV.w;

		return vTmp;
	}
	/*!
	* @brief 二項演算子 +
	*   自身(this)のベクトルの要素ごに"f"の値を加算する
	* @param [in] f     1つの値
	* @return 自身(this)のベクトルの要素ごに"f"の値を加算した値を返す
	*/
	inline gt2Vector4 operator + (float f) const
	{
		gt2Vector4 vTmp;

		vTmp.x = x + f;
		vTmp.y = y + f;
		vTmp.z = z + f;
		vTmp.w = w + f;

		return vTmp;
	}
	/*!
	* @brief 二項演算子 -
	*   自身(this)のベクトルと"rV"ベクトルを減算する
	* @param [in] rV     gt2Vector4
	* @return 自身(this)のベクトルと"rV"ベクトル値を減算した値を返す
	*/
	inline gt2Vector4 operator - (const gt2Vector4& rV) const
	{
		gt2Vector4 vTmp;

		vTmp.x = x - rV.x;
		vTmp.y = y - rV.y;
		vTmp.z = z - rV.z;
		vTmp.w = w - rV.w;

		return vTmp;
	}
	/*!
	* @brief 二項演算子 -
	*   自身(this)のベクトルの要素ごに"f"の値を減算する
	* @param [in] f     1つの値
	* @return 自身(this)のベクトルの要素ごに"f"の値を減算した値を返す
	*/
	inline gt2Vector4 operator - (float f) const
	{
		gt2Vector4 vTmp;

		vTmp.x = x - f;
		vTmp.y = y - f;
		vTmp.z = z - f;
		vTmp.w = w - f;

		return vTmp;
	}
	/*!
	* @brief 二項演算子 *
	*   自身(this)のベクトルの要素ごに"f"の値を乗算する
	* @param [in] f     1つの値
	* @return 自身(this)のベクトルの要素ごに"f"の値を乗算した値を返す
	*/
	inline gt2Vector4 operator * (float f) const
	{
		gt2Vector4 vTmp;

		vTmp.x = x * f;
		vTmp.y = y * f;
		vTmp.z = z * f;
		vTmp.w = w * f;

		return vTmp;
	}
	/*!
	* @brief 二項演算子 /
	*   自身(this)のベクトルの要素ごに"f"の値を除算する
	* @param [in] f     1つの値
	* @return 自身(this)のベクトルの要素ごに"f"の値を除算した値を返す
	*/
	inline gt2Vector4 operator / (float f) const
	{
		gt2Vector4 vTmp;

		vTmp.x = x / f;
		vTmp.y = y / f;
		vTmp.z = z / f;
		vTmp.w = w / f;

		return vTmp;
	}
	/*!
	* @brief 二項演算子 /
	*   自身(this)のベクトルと"rV"ベクトルの要素ごと除算する
	* @param [in] rV     gt2Vector2
	* @return 自身(this)のベクトルと"rV"ベクトルの要素ごと除算した値を返す
	*/
	inline gt2Vector4 operator / (const gt2Vector4& rV) const
	{
		gt2Vector4 vTmp;

		vTmp.x = x / rV.x;
		vTmp.y = y / rV.y;
		vTmp.z = z / rV.z;
		vTmp.w = w / rV.w;

		return vTmp;
	}
	friend inline gt2Vector4 operator * (float f, const gt2Vector4& rV)
	{
		return rV * f;
	}
	/*!
	* @brief 二項演算子 *
	*   自身(this)のベクトルと"rV"ベクトルの要素ごと乗算する
	* @param [in] rV     gt2Vector3
	* @return 自身(this)のベクトルと"rV"ベクトルの要素ごと乗算した値を返す
	*/
	inline gt2Vector4 operator * (const gt2Vector4& rV) const
	{
		gt2Vector4 vTmp;

		vTmp.x = x * rV.x;
		vTmp.y = y * rV.y;
		vTmp.z = z * rV.z;
		vTmp.w = w * rV.w;

		return vTmp;
	}



	//##################################################################
	//##
	//## 比較演算子
	//##
	//##################################################################
	/*!
	* @brief 比較演算子 ==
	*   自身(this)のベクトルと"rV"ベクトルの各要素が同じか比較する
	* @param [in] rV     gt2Vector4
	* @return 自身(this)のベクトルと"rV"ベクトルの各要素を比較し、同一ならtrueを返す。
	*/
	inline bool operator == (const gt2Vector4& rV) const
	{
		return x == rV.x && y == rV.y && z == rV.z && w == rV.w;
	}
	/*!
	* @brief 比較演算子 !=
	*   自身(this)のベクトルと"rV"ベクトルの各要素が違うか比較する
	* @param [in] rV     gt2Vector4
	* @return 自身(this)のベクトルと"rV"ベクトルの各要素を比較し、違う場合trueを返す。
	*/
	inline bool operator != (const gt2Vector4& rV) const
	{
		return !(*this == rV);
	}



	//##################################################################
	//##
	//## 
	//##
	//##################################################################
	/*!
	* @brief  gt2Vector2の値を返す。
	* @return  gt2Vector2
	*/
	inline gt2Vector2 GetV2() const { return gt2Vector2(x, y); }
	/*!
	* @brief  gt2Vector3の値を返す。
	* @return  gt2Vector3
	*/
	inline gt2Vector3 GetV3() const { return gt2Vector3(x, y, z); }

	/*!
	* @brief  x,y,z,w の値と内部の値と比較し、大きい値をそれぞれセットする
	* @param [in]  rV  ベクトル
	* @return  なし
	*/
	inline void SetMax(const gt2Vector4& rV)
	{
		this->SetMax(rV.x, rV.y, rV.z, rV.w);
	}
	/*!
	* @brief  x,y,z,w の値と内部の値と比較し、大きい値をそれぞれセットする
	* @param [in]  fx  要素 x
	* @param [in]  fy  要素 y
	* @param [in]  fz  要素 z
	* @param [in]  fw  要素 w
	* @return  なし
	*/
	inline void SetMax(float fx, float fy, float fz, float fw)
	{
		x = x>fx ? x : fx;
		y = y>fy ? y : fy;
		z = z>fz ? z : fz;
		w = w>fw ? w : fw;
	}
	/*!
	* @brief   自身のx,y,z,w の値を少数を四捨五入する
	* @return   なし
	*/
	inline void MyRound()
	{
		x = floor(x + 0.5f);
		y = floor(y + 0.5f);
		z = floor(z + 0.5f);
		w = floor(w + 0.5f);
	}
	/*!
	* @brief   自身のx,y,z,w の値の少数を切り捨て
	* @return   なし
	*/
	inline void MyFloor()
	{
		x = floor(x);
		y = floor(y);
		z = floor(z);
		w = floor(w);
	}
	/*!
	* @brief   自身のx,y,z,wのそれぞれを角度からラジアン値へ
	* @return   なし
	*/
	inline void ToRadianFromAngle()
	{
		x *= GT2_RADIAN;
		y *= GT2_RADIAN;
		z *= GT2_RADIAN;
		w *= GT2_RADIAN;
	}
	/*!
	* @brief   自身のx,y,z,wのそれぞれをラジアンから角度値へ
	* @return   なし
	*/
	inline void ToAngleFromRadian()
	{
		x *= GT2_INV_RADIAN;
		y *= GT2_INV_RADIAN;
		z *= GT2_INV_RADIAN;
		w *= GT2_INV_RADIAN;
	}

	/*!
	* @brief  x,y,z,w の値と内部の値と比較し、小さい値をそれぞれセットする
	* @param [in]  rV  ベクトル
	* @return  なし
	*/
	inline void SetMin(const gt2Vector4& rV)
	{
		this->SetMin(rV.x, rV.y, rV.z, rV.w);
	}
	/*!
	* @brief  x,y,z,w の値と内部の値と比較し、小さい値をそれぞれセットする
	* @param [in]  fx  要素 x
	* @param [in]  fy  要素 y
	* @param [in]  fz  要素 z
	* @param [in]  fw  要素 w
	* @return  なし
	*/
	inline void SetMin(float fx, float fy, float fz, float fw)
	{
		x = x<fx ? x : fx;
		y = y<fy ? y : fy;
		z = z<fz ? z : fz;
		w = w<fw ? w : fw;
	}
	/*!
	* @brief 角度(0～360)からラジアン値に変換してx,y,zに代入する
	* @param [in] fx     角度(0～360)
	* @param [in] fy     角度(0～360)
	* @param [in] fz     角度(0～360)
	* @param [in] fw     角度(0～360)
	* @return なし
	*/
	inline void MakeRadianToDegrees(float fx, float fy, float fz, float fw)
	{
		x = GT2_INV_RADIAN * fx;
		y = GT2_INV_RADIAN * fy;
		z = GT2_INV_RADIAN * fz;
		w = GT2_INV_RADIAN * fw;
	}
	/*!
	* @brief ベクトルの長さを返す。
	* @return ベクトルの長さを返す。
	*/
	inline float Length() const
	{
		return sqrt(x*x + y*y + z*z + w*w);
	}
	/*!
	* @brief ベクトルの長さの 2 乗を返す。
	* @return ベクトルの長さの 2 乗を返す。
	*/
	inline float LengthSq() const
	{
		return x*x + y*y + z*z + w*w;
	}
	/*!
	* @brief 内積
	*   ベクトルの内積を求めます。
	* @return  内積を返す。
	*/
	inline float Dot() const
	{
		return x*x + y*y + z*z;
	}
	/*!
	* @brief 内積
	*   自身(this)のベクトルと"rV"ベクトルを内積する
	* @param [in] rV     対象ベクトル
	* @return  内積を返す。
	*/
	inline float Dot(const gt2Vector4& rV3) const
	{
		return x*rV3.x + y*rV3.y + z*rV3.z + w*rV3.w;
	}
	/*!
	* @brief 外積
	*   v = rV1 × rV2 × rV3
	* @param [in] rV1     1つめの対象ベクトル
	* @param [in] rV2     2つめの対象ベクトル
	* @param [in] rV3     3つめの対象ベクトル
	* @return  外積したベクトルを返す。
	*/
	inline static gt2Vector4 Cross(const gt2Vector4& rV1, const gt2Vector4& rV2, const gt2Vector4& rV3)
	{
		return gt2Vector4(
			rV1.z*rV2.y*rV3.w - rV1.y*rV2.z*rV3.w - rV1.z*rV2.w*rV3.y + rV1.w*rV2.z*rV3.y + rV1.y*rV2.w*rV3.z - rV1.w*rV2.y*rV3.z,
			-rV1.z*rV2.x*rV3.w + rV1.x*rV2.z*rV3.w + rV1.z*rV2.w*rV3.x - rV1.w*rV2.z*rV3.x - rV1.x*rV2.w*rV3.z + rV1.w*rV2.x*rV3.z,
			rV1.y*rV2.x*rV3.w - rV1.x*rV2.y*rV3.w - rV1.y*rV2.w*rV3.x + rV1.w*rV2.y*rV3.x + rV1.x*rV2.w*rV3.y - rV1.w*rV2.x*rV3.y,
			-rV1.z*rV2.y*rV3.x + rV1.y*rV2.z*rV3.x + rV1.z*rV2.x*rV3.y - rV1.x*rV2.z*rV3.y - rV1.y*rV2.x*rV3.z + rV1.x*rV2.y*rV3.z
		);
	}
	/*!
	* @brief 外積
	*   v = *this × rV2 × rV3
	*  1つめのベクトルは自信(this)です。
	* @param [in] rV2     2つめの対象ベクトル
	* @param [in] rV3     3つめの対象ベクトル
	* @return  外積したベクトルを返す。
	*/
	inline gt2Vector4 Cross(const gt2Vector4& rV2, const gt2Vector4& rV3) const
	{
		return gt2Vector4::Cross(*this, rV2, rV3);
	}
	/*!
	* @brief ベクトルの加算
	*   自身(this)のベクトルと"rV"ベクトルを加算する。
	* @param [in] rV     入力 gt2Vector2 構造体
	* @return  加算されたベクトルを返す。
	*/
	inline gt2Vector4 Add(const gt2Vector4& rV) const
	{
		return gt2Vector4(
			x + rV.x,
			y + rV.y,
			z + rV.z,
			w + rV.w
		);
	}
	/*!
	* @brief ベクトルの減算
	*   自身(this)のベクトルと"rV"ベクトルを減算する。
	* @param [in] rV     入力 gt2Vector4 構造体
	* @return  減算されたベクトルを返す。
	*/
	inline gt2Vector4 Subtract(const gt2Vector4& rV) const
	{
		return gt2Vector4(
			x - rV.x,
			y - rV.y,
			z - rV.z,
			w - rV.w
		);
	}
	/*!
	* @brief 2つのベクトルの要素を比較し最小値の要素のベクトルを返す
	* @param [in] rV     入力 gt2Vector4 構造体
	* @return  最小値の要素のベクトルを返す
	*/
	inline gt2Vector4 Minimize(const gt2Vector4& rV) const
	{
		return gt2Vector4(
			x < rV.x ? x : rV.x,
			y < rV.y ? y : rV.y,
			z < rV.z ? z : rV.z,
			w < rV.w ? w : rV.w);
	}
	/*!
	* @brief 2つのベクトルの要素を比較し最大値の要素のベクトルを取得する
	* @param [in] rV     入力 gt2Vector4 構造体
	* @return  最大値の要素のベクトルを返す
	*/
	inline gt2Vector4 Maximize(const gt2Vector4& rV) const
	{
		return gt2Vector4(
			x > rV.x ? x : rV.x,
			y > rV.y ? y : rV.y,
			z > rV.z ? z : rV.z,
			w > rV.w ? w : rV.w);
	}
	/*!
	* @brief ベクトルをスケーリングする。
	* @param [in]  s      スケーリング値。
	* @return  ベクトルをスケーリングしたものを返す。
	*/
	inline gt2Vector4 Scale(float s) const
	{
		return gt2Vector4(x * s, y * s, z * s, w * s);
	}
	/*!
	* @brief ベクトル間の線形補間を実行する。
	* @param [in]  rV1   第 1 番目のベクトル
	* @param [in]  rV2   第 2 番目のベクトル
	* @param [in]  t     ベクトル間を線形補間するパラメータ。
	* @return  線形補間されたベクトルを返す。
	*/
	inline static gt2Vector4 Lerp(const gt2Vector4& rV1, const gt2Vector4& rV2, float t)
	{
		return gt2Vector4(
			rV1.x + t * (rV2.x - rV1.x),
			rV1.y + t * (rV2.y - rV1.y),
			rV1.z + t * (rV2.z - rV1.z),
			rV1.w + t * (rV2.w - rV1.w)
		);
	}
	/*!
	* @brief ベクトル間の線形補間を実行する。
	*   第 1 番目のベクトルが、自身(this)です。
	* @param [in]  rV2   第 2 番目のベクトル
	* @param [in]  t     ベクトル間を線形補間するパラメータ。
	* @return  線形補間されたベクトルを返す。
	*/
	inline gt2Vector4 Lerp(const gt2Vector4& rV2, float t) const
	{
		return gt2Vector4::Lerp(*this, rV2, t);
	}
	/*!
	* @brief 0 ≦ t ≦ 1 の間でエルミート補間による滑らかな補間を行います。
	* @param [in]  rV1  1 番目のベクトル。
	* @param [in]  rV2  2 番目のベクトル。
	* @param [in]  t   ベクトル間を線形補間するパラメータ。範囲[0～1.0]
	* @return  補間されたベクトルを返す。
	*/
	inline static gt2Vector4 SmoothStep(const gt2Vector4& rV1, const gt2Vector4& rV2, float t)
	{
		t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
		t = t*t*(3.f - 2.f*t);
		return gt2Vector4::Lerp(rV1, rV2, t);
	}
	/*!
	* @brief 0 ≦ t ≦ 1 の間でエルミート補間による滑らかな補間を行います。
	*   第 1 番目のベクトルが、自身(this)です。
	* @param [in]  rV  2 番目のベクトル。
	* @param [in]  t   ベクトル間を線形補間するパラメータ。範囲[0～1.0]
	* @return  補間されたベクトルを返す。
	*/
	inline gt2Vector4 SmoothStep(const gt2Vector4& rV2, float t) const
	{
		return gt2Vector4::SmoothStep(*this, rV2, t);
	}
	/*!
	* @brief 指定された位置ベクトルを使用して、重心座標のポイントを返します。
	* @param [in]  rV1  第 1 の位置
	* @param [in]  rV2  第 2 の位置
	* @param [in]  rV3  第 3 の位置
	* @param [in]  f    加重係数。
	* @param [in]  g    加重係数。
	* @return  重心座標を返します。
	*/
	inline static gt2Vector4 Barycentric(const gt2Vector4& rV1, const gt2Vector4& rV2, const gt2Vector4& rV3, float f, float g)
	{
		return rV1 + f * (rV2 - rV1) + g * (rV3 - rV1);
	}
	/*!
	* @brief 指定された位置ベクトルを使用して、重心座標のポイントを返します。
	*   第 1 の位置が、自身(this)です。
	* @param [in]  rV2  第 2 の位置
	* @param [in]  rV3  第 3 の位置
	* @param [in]  f    加重係数。
	* @param [in]  g    加重係数。
	* @return  重心座標を返します。
	*/
	inline gt2Vector4 Barycentric(const gt2Vector4& rV2, const gt2Vector4& rV3, float f, float g) const
	{
		return gt2Vector4::Barycentric(*this, rV2, rV3, f, g);
	}
	/*!
	* @brief 指定された位置ベクトルを使用して、Catmull-Rom 補間を行います。
	* @param [in]  rV1  第 1 の位置
	* @param [in]  rV2  第 2 の位置
	* @param [in]  rV3  第 3 の位置
	* @param [in]  rV4  第 3 の位置
	* @param [in]  t    補間制御係数
	* @return  Catmull-Rom 補間の結果を返します。
	*/
	inline static gt2Vector4 CatmullRom(const gt2Vector4& rV1, const gt2Vector4& rV2, const gt2Vector4& rV3, const gt2Vector4& rV4, float t)
	{
		float t2 = t * t;
		float t3 = t * t2;
		return ((-t3 + 2 * t2 - t) * rV1 +
			(3 * t3 - 5 * t2 + 2) * rV2 +
			(-3 * t3 + 4 * t2 + t) * rV3 +
			(t3 - t2) * rV4) * 0.5f;
	}
	/*!
	* @brief 指定された位置ベクトルを使用して、Catmull-Rom 補間を行います。
	*   第 1 の位置が、自身(this)です。
	* @param [in]  rV2  第 2 の位置
	* @param [in]  rV3  第 3 の位置
	* @param [in]  rV4  第 3 の位置
	* @param [in]  t    補間制御係数
	* @return  Catmull-Rom 補間の結果を返します。
	*/
	inline gt2Vector4 CatmullRom(const gt2Vector4& rV2, const gt2Vector4& rV3, const gt2Vector4& rV4, float t) const
	{
		return gt2Vector4::CatmullRom(*this, rV2, rV3, rV4, t);
	}
	/*!
	* @brief 指定されたベクトルを使用して、エルミート スプライン補間を実行します。
	* @param [in]  rV1  補間が行われる第 1 の位置
	* @param [in]  rT1  第 1 の位置の接線ベクトル
	* @param [in]  rV2  補間が行われる第 2 の位置
	* @param [in]  rT2  第 2 の位置の接線ベクトル
	* @param [in]  t    補間制御係数
	* @return  補間が含まれたベクトルを返します。
	*/
	inline static gt2Vector4 Hermite(const gt2Vector4& rV1, const gt2Vector4& rT1, const gt2Vector4& rV2, const gt2Vector4& rT2, float t)
	{
		float t2 = t * t;
		float t3 = t * t2;
		return (2 * t3 - 3 * t2 + 1) * rV1 +
			(t3 - 2 * t2 + t) * rT1 +
			(-2 * t3 + 3 * t2) * rV2 +
			(t3 - t2) * rT2;
	}
	/*!
	* @brief 指定されたベクトルを使用して、エルミート スプライン補間を実行します。
	*   第 1 の位置が、自身(this)です。
	* @param [in]  rT1  第 1 の位置の接線ベクトル
	* @param [in]  rV2  補間が行われる第 2 の位置
	* @param [in]  rT2  第 2 の位置の接線ベクトル
	* @param [in]  t    補間制御係数
	* @return  補間が含まれたベクトルを返します。
	*/
	inline gt2Vector4 Hermite(const gt2Vector4& rT1, const gt2Vector4& rV2, const gt2Vector4& rT2, float t) const
	{
		return gt2Vector4::Hermite(*this, rT1, rV2, rT2, t);
	}
	/*!
	* @brief 4D 法線ベクトルによって 4D 入射ベクトルを反射します。
	* @param [in]  rvIncident  反射される 4D 入射ベクトル
	* @param [in]  rvNormal    入射ベクトルを反射する 4D 法線ベクトル
	* @return  反射後の入射角を返します。
	*/
	inline static gt2Vector4 Refract(const gt2Vector4& rvIncident, const gt2Vector4& rvNormal)
	{
		return rvIncident - (2 * rvIncident.Dot(rvNormal)) * rvNormal;
	}
	/*!
	* @brief 4D 法線ベクトルによって 4D 入射ベクトルを反射します。
	*   反射される 4D 入射ベクトルが、自身(this)です。
	* @param [in]  rvNormal    入射ベクトルを反射する 4D 法線ベクトル
	* @return  反射後の入射角を返します。
	*/
	inline gt2Vector4 Refract(const gt2Vector4& rvNormal) const
	{
		return gt2Vector4::Refract(*this, rvNormal);
	}
	/*!
	* @brief 4D 法線ベクトルによって 4D 入射ベクトルを反射します。
	* @param [in]  rvIncident      反射される 4D 入射ベクトル
	* @param [in]  rvNormal        入射ベクトルを反射する 4D 法線ベクトル
	* @param [in]  refractionIndex 屈折率。
	* @return  屈折された入射ベクトルを返します。屈折率、および入射ベクトルと法線ベクトル間の角度によって、
	*          結果が全反射になった場合は、< 0.0f, 0.0f, 0.0f, 0.0f > という形のベクトルが返されます。
	*/
	inline static gt2Vector4 Refract(const gt2Vector4& rvIncident, const gt2Vector4& rvNormal, float refractionIndex)
	{
		gt2Vector4 Result;
		float t = rvIncident.Dot(rvNormal);

		float r = 1.0f - refractionIndex * refractionIndex * (1.0f - t * t);
		if (r < 0.0f) // 全反射
		{
			Result.x = 0.0f;
			Result.y = 0.0f;
			Result.z = 0.0f;
			Result.w = 0.0f;
		}
		else {
			float s = refractionIndex * t + sqrtf(r);
			Result.x = refractionIndex * rvIncident.x - s * rvNormal.x;
			Result.y = refractionIndex * rvIncident.y - s * rvNormal.y;
			Result.z = refractionIndex * rvIncident.z - s * rvNormal.z;
			Result.w = refractionIndex * rvIncident.w - s * rvNormal.w;
		}
		return Result;
	}
	/*!
	* @brief 4D 法線ベクトルによって 4D 入射ベクトルを反射します。
	*   反射される 4D 入射ベクトルが、自身(this)です。
	* @param [in]  rvNormal        入射ベクトルを反射する 4D 法線ベクトル
	* @param [in]  refractionIndex 屈折率。
	* @return  屈折された入射ベクトルを返します。屈折率、および入射ベクトルと法線ベクトル間の角度によって、
	*          結果が全反射になった場合は、< 0.0f, 0.0f, 0.0f > という形のベクトルが返されます。
	*/
	inline gt2Vector4 Refract(const gt2Vector4& rvNormal, float refractionIndex) const
	{
		return gt2Vector4::Refract(*this, rvNormal, refractionIndex);
	}

	/*!
	* @brief lの長さをベクトルの長さとで割った値を、ベクトルの各要素に乗算した値をセットする
	* @param [in]  rV  運動ベクトル
	* @param [in]  l   長さ
	* @return  なし
	*/
	inline void SetMakeLength(const gt2Vector4& rV, float fL) {
		float fLen = rV.Length();
		x = rV.x * fL / fLen;
		y = rV.y * fL / fLen;
		z = rV.z * fL / fLen;
		w = rV.w * fL / fLen;
	}
	/*!
	* @brief 自身(this)のベクトルを正規化する。
	* @return  なし
	*/
	inline void Normalize()
	{
		gt2Vector4 vTmp;

		float fL = this->Length();
		if (fL == 0.0f)
			return;

		fL = 1.0f / fL;
		x *= fL;
		y *= fL;
		z *= fL;
		w *= fL;
	}
	/*!
	* @brief ベクトルを正規化したベクトルを返します。
	* @param [out] pOut     演算結果である gt2Vector3 構造体へのポインタ。
	* @return  ベクトルを正規化したベクトルを返す。
	*/
	inline gt2Vector4* Normalize(gt2Vector4* pOut) const
	{
		gt2Vector4 vTmp;

		float fL = this->Length();
		if (fL == 0.0f) {
			*pOut = gt2Vector4(0.0f, 0.0f, 0.0f, 0.0f);
			return pOut;
		}
		*pOut = *this;

		fL = 1.0f / fL;
		pOut->x *= fL;
		pOut->y *= fL;
		pOut->z *= fL;
		pOut->w *= fL;
		return pOut;
	}
	/*!
	* @brief ベクトルを正規化したベクトルを返す。
	* @param [out] rOut     演算結果である gt2Vector3。
	* @return  なし
	*/
	inline void Normalize(gt2Vector4& rOut) const
	{
		this->Normalize(&rOut);
	}
	/*!
	* @brief ベクトルの要素を、指定された最大値と最小値の範囲にクランプします。
	* @param [in] rMin     最小範囲ベクトル
	* @param [in] rMax     最大範囲ベクトル
	* @return  なし
	*/
	void Clamp(const gt2Vector4& rMin, const gt2Vector4& rMax)
	{
		x = std::min(std::max(x, rMin.x), rMax.x);
		y = std::min(std::max(y, rMin.y), rMax.y);
		z = std::min(std::max(z, rMin.z), rMax.z);
		w = std::min(std::max(w, rMin.w), rMax.w);
	}
} gt2Vector4, *LPMCVECTOR4;
const gt2Vector4 g_VF4IdentityR0 = gt2Vector4(1, 0, 0, 0);
const gt2Vector4 g_VF4IdentityR1 = gt2Vector4(0, 1, 0, 0);
const gt2Vector4 g_VF4IdentityR2 = gt2Vector4(0, 0, 1, 0);
const gt2Vector4 g_VF4IdentityR3 = gt2Vector4(0, 0, 0, 1);

// エラー用
const gt2Vector2 g_VectorF2_NaN = gt2Vector2(NAN, NAN);
const gt2Vector3 g_VectorF3_NaN = gt2Vector3(NAN, NAN, NAN);
const gt2Vector4 g_VectorF4_NaN = gt2Vector4(NAN, NAN, NAN, NAN);
