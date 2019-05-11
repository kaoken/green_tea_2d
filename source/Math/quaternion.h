/*
Copyright (c) <''2013''> <''METAL CUBE''>

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
*/
#pragma once

#include <Core/greenTea2D.h>
#include <Math/vector.h>


#define Q_EPSILON 0.0001f	//!< イプシロン値

/*!
* @brief クォータニオン
* @author kaoken
* @date 2014/01/17 作成開始
*/
struct gt2Quaternion
{
public:
	union {
		struct {
			float x, y, z, w;	//!< 各要素
		};
		float q[4];				//!< 配列による各要素
	};
public:
	/*!
	* @brief コンストラクタ
	*  各要素が０で初期化される
	*/
	gt2Quaternion()
	{
		this->Init();
	}
	/*!
	* @brief コンストラクタ
	*   x,yがpfポインタの値により初期化される
	* @param [in] pf     4要素以上のfloat情報があるポインタ
	*/
	gt2Quaternion(const float * pf)
	{
		memcpy(q, pf, 4 * sizeof(float));
	}
	/*!
	* @brief コンストラクタ
	*  rQで初期化される
	* @param [in] rQ     クォータニオン
	*/
	gt2Quaternion(const gt2Quaternion& rQ)
	{
		*this = rQ;
	}
	/*!
	* @brief コンストラクタ
	*   x=fx,y=fy,z=fz,w=fw といった感じに初期化される
	* @param [in] fx     x値
	* @param [in] fy     y値
	* @param [in] fz     y値
	* @param [in] fw     w値
	*/
	gt2Quaternion(float fx, float fy, float fz, float fw)
	{
		x = fx; y = fy; z = fz; w = fw;
	}

#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
	gt2Quaternion&   operator= (const DirectX::XMVECTOR& vf) { x = vf.m128_f32[0]; y = vf.m128_f32[1]; z = vf.m128_f32[2]; w = vf.m128_f32[3]; return *this; }

	DirectX::XMVECTOR GetXMVECTOR() const { DirectX::XMVECTOR t; t.m128_f32[0] = x; t.m128_f32[1] = y; t.m128_f32[2] = z; t.m128_f32[3] = w; return t; }
#endif

	//------------------------------------------------------------------------
	// 型変換
	//------------------------------------------------------------------------
	inline
		operator float* ()
	{
		return q;
	}
	inline
		operator const float* () const
	{
		return q;
	}
	//------------------------------------------------------------------------
	//
	// 代入演算子
	//
	//------------------------------------------------------------------------
	/*!
	* @brief 代入演算子 -=
	*   自身(this)のクォータニオンを右辺のクォータニオンを減算した値を自身(this)にセットする
	* @param [in] rQ     右辺のクォータニオン
	* @return 加算されたクォータニオンを返す
	*/
	inline gt2Quaternion& operator += (const gt2Quaternion& rQ)
	{
		x += rQ.x;
		y += rQ.y;
		z += rQ.z;
		w += rQ.w;

		return *this;
	}
	/*!
	* @brief 代入演算子 -=
	*   自身(this)のクォータニオンを右辺のクォータニオンを減算した値を自身(this)にセットする
	* @param [in] rQ     右辺のクォータニオン
	* @return 減算されたクォータニオンを返す
	*/
	inline gt2Quaternion& operator -= (const gt2Quaternion& rQ)
	{
		x -= rQ.x;
		y -= rQ.y;
		z -= rQ.z;
		w -= rQ.w;

		return *this;
	}
	/*!
	* @brief 代入演算子 *=
	*   自身(this)のクォータニオンを右辺の１つの値を乗算した値を自身(this)にセットする
	* @param [in] f     右辺の1つの値
	* @return 乗算されたクォータニオンを返す
	*/
	inline gt2Quaternion& operator *= (const gt2Quaternion& rQ)
	{
		*this = rQ * (*this);
		return *this;
	}
	/*!
	* @brief 代入演算子 *=
	*   自身(this)のクォータニオンを右辺の１つの値を乗算した値を自身(this)にセットする
	* @param [in] f     右辺の1つの値
	* @return 乗算されたクォータニオンを返す
	*/
	inline gt2Quaternion& operator *= (float f)
	{
		x *= f;
		y *= f;
		z *= f;
		w *= f;

		return *this;
	}
	/*!
	* @brief 代入演算子 *=
	*   自身(this)のクォータニオンを右辺の１つの値を除算した値を自身(this)にセットする
	* @param [in] f     右辺の1つの値
	* @return 除算されたクォータニオンを返す
	*/
	inline gt2Quaternion& operator /= (float f)
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
	* @return そのままのクォータニオンを返す
	*/
	inline gt2Quaternion operator + () const
	{
		return *this;
	}
	/*!
	* @brief 単項演算子 -
	*   各要素に-1を乗算したクォータニオンになる
	* @return 各要素に-1を乗算したクォータニオンを返す
	*/
	inline gt2Quaternion operator - () const
	{
		return gt2Quaternion(-x, -y, -z, -w);
	}
	/*!
	* @brief 単項演算子 ~
	*   共役したクォータニオンになる
	* @return 共役したクォータニオンを返す
	*/
	inline gt2Quaternion
		operator ~ () const
	{
		return gt2Quaternion(-x, -y, -z, w);
	}

	//##################################################################
	//##
	//## 二単項演算子
	//##
	//##################################################################
	/*!
	* @brief 二項演算子 +
	*   自身(this)のベクトルと"rQ"ベクトルを加算する
	* @param [in] rQ     クォータニオン
	* @return 自身(this)のクォータニオンと"rQ"クォータニオンを加算した値を返す
	*/
	inline gt2Quaternion operator + (const gt2Quaternion& rQ) const
	{
		return gt2Quaternion(
			x + rQ.x,
			y + rQ.y,
			z + rQ.z,
			w + rQ.w
		);
	}
	/*!
	* @brief 二項演算子 -
	*   自身(this)のクォータニオンと"v"クォータニオンを減算する
	* @param [in] rV     クォータニオン
	* @return 自身(this)のクォータニオンと"v"クォータニオンを減算した値を返す
	*/
	inline gt2Quaternion operator - (const gt2Quaternion& rQ) const
	{
		return gt2Quaternion(
			x - rQ.x,
			y - rQ.y,
			z - rQ.z,
			w - rQ.w
		);
	}
	/*!
	* @brief 二項演算子 *
	*   自身(this)のクォータニオンと"rQ"クォータニオンを乗算する
	* @param [in] rQ     クォータニオン
	* @return 自身(this)のクォータニオンと"v"クォータニオンを乗算した値を返す
	*/
	inline gt2Quaternion operator * (const gt2Quaternion& rQ) const
	{
		return gt2Quaternion(
			(rQ.w * x) + (rQ.x * w) + (rQ.y * z) - (rQ.z * y),
			(rQ.w * y) + (rQ.y * w) + (rQ.z * x) - (rQ.x * z),
			(rQ.w * z) + (rQ.z * w) + (rQ.x * y) - (rQ.y * x),
			(rQ.w * w) - (rQ.x * x) - (rQ.y * y) - (rQ.z * z)
		);
	}
	/*!
	* @brief 二項演算子 *
	*   自身(this)のクォータニオンと"rV"ベクトルを乗算する
	* @param [in] rV     ベクトル
	* @return 自身(this)のクォータニオンと"rV"ベクトルを乗算した値を返す
	*/
	inline gt2Quaternion operator * (const gt2Vector3& rV) const
	{
		return	gt2Quaternion(
			-(x*rV.x + y*rV.y + z*rV.z),
			w*rV.x + z*rV.y - y*rV.z,
			w*rV.y + x*rV.z - z*rV.x,
			w*rV.z + y*rV.x - x*rV.y);
	}
	/*!
	* @brief 二項演算子 *
	*   自身(this)のクォータニオンの要素ごに"f"の値を乗算する
	* @param [in] f     1つの値
	* @return 自身(this)のクォータニオンの要素ごに"f"の値を乗算した値を返す
	*/
	inline gt2Quaternion operator * (float f) const
	{
		gt2Quaternion tmp;
		tmp.w = w * f;
		tmp.x = x * f;
		tmp.y = y * f;
		tmp.z = z * f;
		return tmp;
	}

	friend inline gt2Quaternion operator * (float f, const gt2Quaternion& rQ)
	{
		return rQ * f;
	}

	/*!
	* @brief 二項演算子 *
	*   自身(this)のクォータニオンの要素ごに"f"の値を除算する
	* @param [in] f     1つの値
	* @return 自身(this)のクォータニオンの要素ごに"f"の値を除算した値を返す
	*/
	inline gt2Quaternion operator / (float f) const
	{
		gt2Quaternion tmp;
		tmp.w = w / f;
		tmp.x = x / f;
		tmp.y = y / f;
		tmp.z = z / f;
		return tmp;
	}

	friend inline gt2Quaternion operator * (const gt2Vector3& rV, const gt2Quaternion& rQ)
	{
		return	gt2Quaternion(-(rQ.x*rV.x + rQ.y*rV.y + rQ.z*rV.z),
			rQ.w*rV.x + rQ.z*rV.y - rQ.y*rV.z,
			rQ.w*rV.y + rQ.x*rV.z - rQ.z*rV.x,
			rQ.w*rV.z + rQ.y*rV.x - rQ.x*rV.y);
	}
	/*
	friend inline gt2Quaternion
	operator * (const gt2Quaternion& rQ, const gt2Vector3& rV )
	{
	return	gt2Quaternion(	-(rQ.x*rV.x + rQ.y*rV.y + rQ.z*rV.z),
	rQ.w*rV.x + rQ.z*rV.y - rQ.y*rV.z,
	rQ.w*rV.y + rQ.x*rV.z - rQ.z*rV.x,
	rQ.w*rV.z + rQ.y*rV.x - rQ.x*rV.y);
	}*/

	//##################################################################
	//##
	//## 比較演算子
	//##
	//##################################################################
	/*!
	* @brief 比較演算子 ==
	*   自身(this)のクォータニオンと"rQ"クォータニオンの各要素が同じか比較する
	* @param [in] rQ     クォータニオン
	* @return 自身(this)のクォータニオンと"rQ"クォータニオンの各要素が同じか比較し、同一ならtrueを返す。
	*/
	inline bool operator == (const gt2Quaternion& rQ) const
	{
		for (int i = 0; i < 4; ++i)
			if (q[i] != rQ.q[i])
				return false;

		return true;
	}
	/*!
	* @brief 比較演算子 !=
	*   自身(this)のクォータニオンと"rQ"クォータニオンの各要素が違うか比較する
	* @param [in] rQ     クォータニオン
	* @return 自身(this)のクォータニオンと"rQ"クォータニオンの各要素が違うか比較し、違うならtrueを返す。
	*/
	inline bool operator != (const gt2Quaternion& rQ) const
	{
		return !(*this == rQ);
	}



	//##################################################################
	//##
	//## 
	//##
	//##################################################################
	/*!
	* @brief クォータニオンのベクトル部分が表す軸に関する回転角度を抽出する。
	* @return 回転角度を返す。
	*/
	inline float GetAngle() const
	{
		return	(float)(2 * acos(w));
	}
	/*!
	* @brief クォータニオンのベクトル部分が表す回転の軸に沿った単位ベクトルを返す。
	* @return 単位ベクトルを返す。
	*/
	inline gt2Vector3 GetAxis() const
	{
		gt2Vector3 vRet;
		float fLSq;

		vRet = gt2Vector3(x, y, z);

		fLSq = vRet.Length();

		if (fLSq <= Q_EPSILON) {
			vRet.Init();
			return vRet;
		}
		else {
			fLSq = 1.0f / fLSq;
			return vRet * fLSq;
		}

	}
	/*!
	* @brief クォータニオンのベクトル部分が表す回転の軸に沿った単位ベクトルを返す。
	* @return 単位ベクトルを返す。
	*/
	inline gt2Vector3 GetEuler() const
	{
		gt2Vector3 vRet;

		float sqw = w*w;
		float sqx = x*x;
		float sqy = y*y;
		float sqz = z*z;
		float fUnit = sqx + sqy + sqz + sqw;
		float fTest = x*y + z*w;
		float fE = 0.499f*fUnit;
		if (fTest > fE) {
			vRet.y = 2.0f * atan2f(x, w);
			vRet.z = GT2_HALF_PI;
			vRet.x = 0.0f;
		}
		else if (fTest < -fE) {
			vRet.y = -2.0f * atan2f(x, w);
			vRet.z = -GT2_HALF_PI;
			vRet.x = 0.0f;
		}
		else {
			vRet.y = atan2f(2.0f*y*w - 2.0f*x*z, sqx - sqy - sqz + sqw);
			vRet.z = asinf(2.0f*fTest / fUnit);
			vRet.x = atan2f(2.0f*x*w - 2.0f*y*z, -sqx + sqy - sqz + sqw);
		}


		if (vRet.y < 0)
			vRet.y += GT2_PI2;

		if (vRet.x < 0)
			vRet.x += GT2_PI2;

		if (vRet.z < 0)
			vRet.z += GT2_PI2;

		return vRet;
	}

	/*!
	* @brief 重心座標のクォータニオンを返す。
	* @warning
	*  重心座標を計算するため、BaryCentric 関数は次に示す球面線形補間処理を実装する。
	*  MakeSlerp(MakeSlerp(rQ, rQ, f+g), MakeSlerp(rQ, rQ, f+g), g/(f+g))
	* @param [in] rQ1	1つめのクォータニオン
	* @param [in] rQ2	2つめのクォータニオン
	* @param [in] rQ3	3つめのクォータニオン
	* @param [in] fF	加重係数。
	* @param [in] fG	加重係数。
	* @return なし
	*/
	inline void MakeBaryCentric(
		const gt2Quaternion& rQ1,
		const gt2Quaternion& rQ2,
		const gt2Quaternion& rQ3,
		float fF,
		float fG
	)
	{
		gt2Quaternion tmp1, tmp2;
		tmp1.MakeSlerp(rQ1, rQ2, fF + fG);
		tmp2.MakeSlerp(rQ1, rQ3, fF + fG);
		this->MakeSlerp(tmp1, tmp2, fG / (fF + fG));
	}
	/*!
	* @brief 内積
	*   クォータニオンの内積を求めます。
	* @return  内積を返す。
	*/
	inline float Dot() const
	{
		return x*x + y*y + z*z + w*w;
	}
	/*!
	* @brief 内積
	*   自身(this)のクォータニオンと"rV"クォータニオンを内積する
	* @param [in] rQ     クォータニオン
	* @return  内積を返す。
	*/
	inline float Dot(const gt2Quaternion& rQ) const
	{
		return (x * rQ.x) + (y * rQ.y) + (z * rQ.z) + (w * rQ.w);
	}
	/*!
	* @brief 指数関数を計算する。
	* @param [in] rQ     クォータニオン
	* @return  なし
	*/
	inline void MakeExp(const gt2Quaternion& rQ)
	{
		float fMag, fTheta, fC, fS;
		gt2Vector3 v;

		fMag = expf(rQ.w);
		fTheta = sqrtf(rQ.x*rQ.x + rQ.y*rQ.y + rQ.z*rQ.z);  //really v = |u|sin(phi)

		if (fTheta > 1.0e-20) {
			v.x = rQ.x / fTheta;
			v.y = rQ.y / fTheta;
			v.z = rQ.z / fTheta;
		}
		else {
			v.x = v.y = v.z = 0.0f;
		}
		fC = (float)cos(fTheta);
		fS = (float)sin(fTheta);

		w = fMag*fC;
		x = fMag*fS*v.x;
		y = fMag*fS*v.y;
		z = fMag*fS*v.z;
	}
	/*!
	* @brief 単位クォータニオンを作成する。
	* @return  なし
	*/
	inline void MakeIdentity()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 1.0f;
	}
	/*!
	* @brief クォータニオンを共役して、再正規化し、セットする。
	* @param [in] rQ     クォータニオン
	* @return  なし
	*/
	inline void MakeInverse(const gt2Quaternion& rQ)
	{
		rQ.Normalize(this);

		x *= -1;
		y *= -1;
		z *= -1;
		//w = w;
	}
	/*!
	* @brief 初期化する
	* @return  なし
	*/
	inline void Init()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 1.0f;
	}
	/*!
	* @brief クォータニオンが単位クォータニオンであるかどうかを判定する。
	* @return  クォータニオンが単位クォータニオンの場合、true を返し,それ以外の場合は、falseを返す。
	*/
	inline bool IsIdentity() const
	{
		if (w == 1.0f && x == 0.0f && y == 0.0f && z == 0.0f)
			return true;

		return false;
	}
	/*!
	* @brief クォータニオンの長さを返す。
	* @return  クォータニオンの長さを返す。
	*/
	inline float Length() const
	{
		return (float)sqrt(x * x + y * y + z * z + w * w);
	}
	/*!
	* @brief クォータニオンの長さの 2 乗を返す
	* @return  クォータニオンの長さの 2 乗を返す。
	*/
	inline float LengthSq() const
	{
		float f = this->Length();
		return f*f;
	}
	/*!
	* @brief 自然対数を計算し、セットする。
	* @return  なし
	*/
	inline void MakeLn(const gt2Quaternion& rQ)
	{
		float fQm;
		//float fN;
		float fW;
		//fN = (float)Sqr(rQ.x * rQ.x + rQ.y * rQ.y + rQ.z * rQ.z + rQ.w * rQ.w)
		fQm = (float)sqrt(rQ.x * rQ.x + rQ.y * rQ.y + rQ.z * rQ.z);

		fW = (float)atan2(fQm, rQ.w) / fQm;
		x = fW * rQ.x;
		y = fW * rQ.y;
		z = fW * rQ.z;
		w = 0;	//Log(n)
	}
	/*!
	* @brief クォータニオンの共役を作成
	* @param [in] rQ     クォータニオン
	* @return  なし
	*/
	inline void MakeConjugate(const gt2Quaternion& rQ)
	{
		x = -rQ.x;
		y = -rQ.y;
		z = -rQ.z;
		w = rQ.w;
	}
	/*!
	* @brief 自身(this)のクォータニオンを正規化する。
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
		w *= fL;
	}
	/*!
	* @brief クォータニオンを正規化したクォータニオンを返します。
	* @param [out] pOut     クォータニオンのポインタ。
	* @return  クォータニオンを正規化したベクトルを返す。
	*/
	inline gt2Quaternion* Normalize(gt2Quaternion* pOut) const
	{
		float fL = this->Length();
		if (fL == 0.0f) {
			*pOut = gt2Quaternion(0.0f, 0.0f, 0.0f, 0.0f);
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
	* @brief 自身のクォータニオンを正規化する。
	* @param [out] rOut     クォータニオン
	* @return  なし
	*/
	inline void Normalize(gt2Quaternion& rOut) const
	{
		this->Normalize(&rOut);
	}
	/*!
	* @brief 自身(this) を rQPによって回転します。
	*   *pOut = (*this) * rQP * ~(*this);
	* @param [out] pOut    回転したクォータニオン
	* @param [in]  pQP     回転クォータニオン
	* @return  pOutと同じポインタ
	*/
	inline gt2Quaternion* Rotate(gt2Quaternion* pOut, const gt2Quaternion& rQP) const
	{
		*pOut = (*this) * rQP * ~(*this);
		return pOut;
	}
	/*!
	* @brief 自身(this) を rQPによって回転します。
	*   戻り値 = (*this) * rQP * ~(*this);
	* @param [in] pQP     クォータニオン
	* @return  rQPによって回転したクォータニオン
	*/
	inline gt2Quaternion Rotate(const gt2Quaternion& rQP) const
	{
		gt2Quaternion out;
		this->Rotate(&out, rQP);
		return out;
	}
	/*!
	* @brief ベクトルrV を 単位四元数(*this)によって回転します。
	*   戻り値 = (*this) * rV * ~(*this);
	* @param [out] pOut    単位四元数(*this)によって回転したベクトル
	* @param [in]  rV      ３要素ベクトル
	* @return  pOutと同じポインタ
	*/
	inline gt2Vector3* VecRotate(gt2Vector3* pOut, const gt2Vector3& rV) const
	{
		gt2Quaternion qTmp;

		qTmp = (*this) * rV * ~(*this);
		pOut->x = qTmp.x;
		pOut->y = qTmp.y;
		pOut->z = qTmp.z;
		return pOut;
	}
	/*!
	* @brief ベクトルrV を 単位四元数(*this)によって回転します。
	*   戻り値 = (*this) * rV * ~(*this);
	* @param [in]  rV      ３要素ベクトル
	* @return  位四元数(*this)によって回転したベクトル
	*/
	inline gt2Vector3 VecRotate(const gt2Vector3& rV) const
	{
		gt2Vector3 out;
		this->VecRotate(&out, rV);
		return out;
	}
	/*!
	* @brief ヨー・ピッチ・ロールを指定してクォータニオンを作成する。
	* @param [in]  fYaw	  y 軸を中心とするヨー (ラジアン単位)。
	* @param [in]  pitch x 軸を中心とするピッチ (ラジアン単位)。
	* @param [in]  fRoll  z 軸を中心とするロール (ラジアン単位)。
	* @return  なし
	*/
	inline void MakeRotationYawPitchRoll(float fYaw, float pitch, float fRoll)
	{
		float fCosY, fSinY, fCosR;
		float fSinR, fCosP, fSinP;

		fCosY = cosf(fYaw * 0.5f);
		fSinY = sinf(fYaw * 0.5f);
		fCosP = cosf(pitch * 0.5f);
		fSinP = sinf(pitch * 0.5f);
		fCosR = cosf(fRoll * 0.5f);
		fSinR = sinf(fRoll * 0.5f);

		x = fCosR * fSinP * fCosY + fSinR * fCosP * fSinY;
		y = fCosR * fCosP * fSinY - fSinR * fSinP * fCosY;
		z = fSinR * fCosP * fCosY - fCosR * fSinP * fSinY;
		w = fCosR * fCosP * fCosY + fSinR * fSinP * fSinY;
	}
	/*!
	* @brief 球面線形補間を使って、2 つのクォータニオン間を補間する。
	* @param [in]  rQ1	 1つめのクオータニオン
	* @param [in]  rQ2	 2つめのクオータニオン
	* @param [in]  totalTime	 補間するクォータニオン間の間隔を示すパラメータ。
	* @return  補完したクォータニオンを返す
	*/
	inline static gt2Quaternion Slerp(const gt2Quaternion& rQ1, const gt2Quaternion& rQ2, float t)
	{
		// Slerp(t; p, q) = { sin( (1-t)θ)p + sin(tθ)q } / sin(θ)
		gt2Quaternion qTmp2;
		float cosHalfTheta, halfTheta, sinHalfTheta, ratioA, ratioB, IsinT;

		if (t <= 0.0f)
			return rQ1;

		if (t >= 1.0f)
			return rQ2;

		// 内積をする
		cosHalfTheta = rQ1.Dot(rQ2);
		if (fabs(cosHalfTheta) >= 1.0f)
			return rQ1;

		qTmp2 = rQ2;

		// 一時変数作成.
		halfTheta = (float)acos(cosHalfTheta);
		sinHalfTheta = (float)sqrt(1.0f - cosHalfTheta*cosHalfTheta);

		if (cosHalfTheta < 0.0f) {
			qTmp2 = -qTmp2;
			cosHalfTheta *= -1.0f;
		}

		// theta = 180度の場合、その後、結果は完全には定義されない
		// rQ1またはrQ2に垂直な任意の軸のまわりで回転することができた
		if (fabs(sinHalfTheta) < Q_EPSILON) {//イプシロン値の設定により集約
			ratioA = ratioB = 0.5f;
		}
		else if (cosHalfTheta > 0.99999) { //イプシロン値の設定により集約
			ratioA = 1.0f - t;
			ratioB = t;
		}
		else {
			IsinT = 1.0f / sinHalfTheta;
			ratioA = (float)sin((1.0f - t) * halfTheta) * IsinT;
			ratioB = (float)sin(t * halfTheta) * IsinT;
		}
		// クォータニオンの計算
		return gt2Quaternion(
			(rQ1.x * ratioA + qTmp2.x * ratioB),
			(rQ1.y * ratioA + qTmp2.y * ratioB),
			(rQ1.z * ratioA + qTmp2.z * ratioB),
			(rQ1.w * ratioA + qTmp2.w * ratioB)
		);
	}
	/*!
	* @brief 球面線形補間を使って、2 つのクォータニオン間を補間する。
	* @param [in]  rQ1	 1つめのクオータニオン
	* @param [in]  rQ2	 2つめのクオータニオン
	* @param [in]  t	 補間するクォータニオン間の間隔を示すパラメータ。
	* @return  なし
	*/
	inline void MakeSlerp(const gt2Quaternion& rQ1, const gt2Quaternion& rQ2, float t)
	{
		*this = gt2Quaternion::Slerp(rQ1, rQ2, t);
	}
	/*!
	* @brief 球面線形補間を使って、クォータニオン間を補間する。
	* @param [in]  rQ  クォータニオンq
	* @param [in]  rA  クォータニオンA
	* @param [in]  rB  クォータニオンB
	* @param [in]  rC  クォータニオンC
	* @param [in]  t   補間するクォータニオン間の間隔を示すパラメータ。
	* @return  補完したクォータニオンを返す
	*/
	inline static gt2Quaternion Squad(
		const gt2Quaternion& rQ,
		const gt2Quaternion& rA,
		const gt2Quaternion& rB,
		const gt2Quaternion& rC,
		float totalTime
	)
	{
		gt2Quaternion tmp1;
		gt2Quaternion tmp2;
		gt2Quaternion out;

		tmp1.MakeSlerp(rQ, rC, totalTime);
		tmp2.MakeSlerp(rA, rB, totalTime);
		out.MakeSlerp(tmp1, tmp2, 2.0f * totalTime * (1.0f - totalTime));
		return out;
	}
	/*!
	* @brief 球面線形補間を使って、クォータニオン間を補間する。
	* @param [in]  rQ  クォータニオンq
	* @param [in]  rA  クォータニオンA
	* @param [in]  rB  クォータニオンB
	* @param [in]  rC  クォータニオンC
	* @param [in]  t   補間するクォータニオン間の間隔を示すパラメータ。
	* @return  なし
	*/
	inline void MakeSquad(
		const gt2Quaternion& rQ,
		const gt2Quaternion& rA,
		const gt2Quaternion& rB,
		const gt2Quaternion& rC,
		float t
	)
	{
		*this = gt2Quaternion::Squad(rQ, rA, rB, rC, t);
	}
	/*!
	* @brief 任意の軸を回転軸としてクォータニオンを回転させます。
	* @param [in]  rV     クォータニオンの回転軸を指定する、gt2Vector3 構造体へのポインタ。
	* @param [in]  fAngle 回転の角度 (ラジアン単位)。
	* @return  なし
	*/
	inline void MakeRotationAxis(const gt2Vector3& rV, float fAngle)
	{
		float fHalfAngle = 0.5f * fAngle;
		float fSin = (float)sin(fHalfAngle);
		w = (float)cos(fHalfAngle);
		x = fSin * rV.x;
		y = fSin * rV.y;
		z = fSin * rV.z;
	}
	/*!
	* @brief クォータニオン間の線形補間を実行する。
	* @param [in]  rQ1   第 1 番目のクォータニオン
	* @param [in]  rQ2   第 2 番目のクォータニオン
	* @param [in]  t     ベクトル間を線形補間するパラメータ。
	* @return  線形補間されたクォータニオンを返す。
	*/
	inline static gt2Quaternion Lerp(const gt2Quaternion& rQ1, const gt2Quaternion& rQ2, float t)
	{
		return (rQ1 + t * (rQ2 - rQ1));
	}
	/*!
	* @brief クォータニオン間の線形補間を実行する。
	*   第 1 番目のクォータニオンが、自身(this)です。
	* @param [in]  rQ2   第 2 番目のクォータニオン
	* @param [in]  t     ベクトル間を線形補間するパラメータ。
	* @return  線形補間されたクォータニオンを返す。
	*/
	inline gt2Quaternion Lerp(const gt2Quaternion& rQ2, float t) const
	{
		return gt2Quaternion::Lerp(*this, rQ2, t);
	}
	/*!
	* @brief 2 つの Quaternion を連結します。結果は、最初の回転とそれに続く 2 番目の回転を表します。
	* @param [in]  rQ1   シリーズ内の最初の Quaternion 回転。
	* @param [in]  rQ2   シリーズ内の 2 番目の Quaternion 回転。
	* @return  回転したクォータニオンを返す。
	*/
	inline static gt2Quaternion Concatenate(const gt2Quaternion& rQ1, const gt2Quaternion& rQ2)
	{
		return gt2Quaternion(
			(rQ1.w * rQ2.x) + (rQ1.x * rQ2.w) + (rQ1.y * rQ2.z) - (rQ1.z * rQ2.y),
			(rQ1.w * rQ2.y) + (rQ1.y * rQ2.w) + (rQ1.z * rQ2.x) - (rQ1.x * rQ2.z),
			(rQ1.w * rQ2.z) + (rQ1.z * rQ2.w) + (rQ1.x * rQ2.y) - (rQ1.y * rQ2.x),
			(rQ1.w * rQ2.w) - (rQ1.x * rQ2.x) - (rQ1.y * rQ2.y) - (rQ1.z * rQ2.z)
		);
	}


};

// エラー用
const gt2Quaternion g_QuaternionF_NaN = gt2Quaternion(NAN, NAN, NAN, NAN);

