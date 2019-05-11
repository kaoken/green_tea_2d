/*!
Copyright (c) 2014 METAL CUBE

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

@file matrix.h
@brief 要素が2x2,3x3,4x4のマトリクス構造体
*/

#pragma once

#include <Math/plane.h>
#include <Math/quaternion.h>
//#include <Box2D/Common/b2Math.h>
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
#  include <DirectXMath.h>
#endif

//#include <OgreMatrix3.h>
//#include <OgreMatrix4.h>
//#include <LinearMath/btMatrix3x3.h>


#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
#  define MY_XMMATRIX ((DirectX::XMMATRIX)(*((DirectX::XMMATRIX*) this)))
#  define CAST_XMMATRIX(_ptr) ((DirectX::XMMATRIX)(*((DirectX::XMMATRIX*) _ptr)))
#endif

//======================================================================================
//! @brief 4×4 のマトリックス
//======================================================================================
struct gt2Matrix4x4
{
public:
	union {
		struct {
			float	_11, _12, _13, _14;
			float	_21, _22, _23, _24;
			float	_31, _32, _33, _34;
			float	_41, _42, _43, _44;
		};
		float m[4][4];
		float mm[16];
	};

public:
	//------------------------------------------------------------------------
	//
	//! @name コンストラクタ
	//
	//------------------------------------------------------------------------
	//@{
	gt2Matrix4x4()
	{
		this->MakeIdentity();
	}
	explicit gt2Matrix4x4(const float *pArray)
	{
		memcpy(mm, pArray, 16 * sizeof(float));
	}
	gt2Matrix4x4(const gt2Matrix4x4& rM) { *this = rM; }
	gt2Matrix4x4(
		float f11, float f12, float f13, float f14,
		float f21, float f22, float f23, float f24,
		float f31, float f32, float f33, float f34,
		float f41, float f42, float f43, float f44
	) :
		_11(f11), _12(f12), _13(f13), _14(f14),
		_21(f21), _22(f22), _23(f23), _24(f24),
		_31(f31), _32(f32), _33(f33), _34(f34),
		_41(f41), _42(f42), _43(f43), _44(f44) {}
	//@}



	inline float&
		operator () (unsigned int Row, unsigned int Col)
	{
		return m[Row][Col];
	}
	inline float
		operator () (unsigned int Row, unsigned int Col) const
	{
		return m[Row][Col];
	}
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
	gt2Matrix4x4&   operator= (const DirectX::XMMATRIX& vf) { memcpy(this, &vf, sizeof(gt2Matrix4x4)); return *this; }

#endif

	//------------------------------------------------------------------------
	//
	//! @name 型変換演算子
	//
	//------------------------------------------------------------------------
	//@{
	inline operator float* ()
	{
		return mm;
	}
	inline operator const float* () const
	{
		return mm;
	}
	//@}

	//------------------------------------------------------------------------
	//
	//! @name 代入演算子
	//
	//------------------------------------------------------------------------
	//@{
	//inline gt2Matrix4x4&   operator= (const btMatrix3x3& m) { memcpy(this, &m, sizeof(gt2Matrix4x4)); return *this; }
	//inline gt2Matrix4x4&   operator= (const Ogre::Matrix4& m) { memcpy(this, &m, sizeof(gt2Matrix4x4)); return *this; }

	inline gt2Matrix4x4& operator *= (const gt2Matrix4x4& rM)
	{
		*this = Multiply(*this, rM);
		return *this;
	}
	inline gt2Matrix4x4& operator += (const gt2Matrix4x4& rM)
	{
		_11 += rM._11; _12 += rM._12; _13 += rM._13; _14 += rM._14;
		_21 += rM._21; _22 += rM._22; _23 += rM._23; _24 += rM._24;
		_31 += rM._31; _32 += rM._32; _33 += rM._33; _34 += rM._34;
		_41 += rM._41; _42 += rM._42; _43 += rM._43; _44 += rM._44;
		return *this;
	}
	inline gt2Matrix4x4& operator -= (const gt2Matrix4x4& rM)
	{
		_11 -= rM._11; _12 -= rM._12; _13 -= rM._13; _14 -= rM._14;
		_21 -= rM._21; _22 -= rM._22; _23 -= rM._23; _24 -= rM._24;
		_31 -= rM._31; _32 -= rM._32; _33 -= rM._33; _34 -= rM._34;
		_41 -= rM._41; _42 -= rM._42; _43 -= rM._43; _44 -= rM._44;
		return *this;
	}
	inline gt2Matrix4x4& operator *= (float f)
	{
		_11 *= f; _12 *= f; _13 *= f; _14 *= f;
		_21 *= f; _22 *= f; _23 *= f; _24 *= f;
		_31 *= f; _32 *= f; _33 *= f; _34 *= f;
		_41 *= f; _42 *= f; _43 *= f; _44 *= f;
		return *this;
	}
	inline gt2Matrix4x4& operator /= (float f)
	{
		float fInv = 1.0f / f;
		_11 *= fInv; _12 *= fInv; _13 *= fInv; _14 *= fInv;
		_21 *= fInv; _22 *= fInv; _23 *= fInv; _24 *= fInv;
		_31 *= fInv; _32 *= fInv; _33 *= fInv; _34 *= fInv;
		_41 *= fInv; _42 *= fInv; _43 *= fInv; _44 *= fInv;
		return *this;
	}
	//@}
	//------------------------------------------------------------------------
	//
	//! @name 単項演算子
	//
	//------------------------------------------------------------------------
	//@{
	inline gt2Matrix4x4 operator + () const
	{
		return *this;
	}
	inline gt2Matrix4x4 operator - () const
	{
		return gt2Matrix4x4(-_11, -_12, -_13, -_14,
			-_21, -_22, -_23, -_24,
			-_31, -_32, -_33, -_34,
			-_41, -_42, -_43, -_44);
	}
	//@}

	//------------------------------------------------------------------------
	//
	//! @name 2 項演算子
	//
	//------------------------------------------------------------------------
	//@{
	inline gt2Matrix4x4 operator * (const gt2Matrix4x4& rM) const
	{
		return Multiply(*this, rM);
	}
	inline gt2Matrix4x4 operator + (const gt2Matrix4x4& rM) const
	{
		return gt2Matrix4x4(_11 + rM._11, _12 + rM._12, _13 + rM._13, _14 + rM._14,
			_21 + rM._21, _22 + rM._22, _23 + rM._23, _24 + rM._24,
			_31 + rM._31, _32 + rM._32, _33 + rM._33, _34 + rM._34,
			_41 + rM._41, _42 + rM._42, _43 + rM._43, _44 + rM._44);
	}
	inline gt2Matrix4x4 operator + (float f) const
	{
		return gt2Matrix4x4(
			_11 + f, _12 + f, _13 + f, _14 + f,
			_21 + f, _22 + f, _23 + f, _24 + f,
			_31 + f, _32 + f, _33 + f, _34 + f,
			_41 + f, _42 + f, _43 + f, _44 + f);
	}
	inline gt2Matrix4x4 operator - (const gt2Matrix4x4& rM) const
	{
		return gt2Matrix4x4(_11 - rM._11, _12 - rM._12, _13 - rM._13, _14 - rM._14,
			_21 - rM._21, _22 - rM._22, _23 - rM._23, _24 - rM._24,
			_31 - rM._31, _32 - rM._32, _33 - rM._33, _34 - rM._34,
			_41 - rM._41, _42 - rM._42, _43 - rM._43, _44 - rM._44);
	}
	inline gt2Matrix4x4 operator - (float f) const
	{
		return gt2Matrix4x4(
			_11 - f, _12 - f, _13 - f, _14 - f,
			_21 - f, _22 - f, _23 - f, _24 - f,
			_31 - f, _32 - f, _33 - f, _34 - f,
			_41 - f, _42 - f, _43 - f, _44 - f);
	}
	inline gt2Matrix4x4 operator * (float f) const
	{
		return gt2Matrix4x4(_11 * f, _12 * f, _13 * f, _14 * f,
			_21 * f, _22 * f, _23 * f, _24 * f,
			_31 * f, _32 * f, _33 * f, _34 * f,
			_41 * f, _42 * f, _43 * f, _44 * f);
	}
	inline gt2Matrix4x4 operator / (float f) const
	{
		float fInv = 1.0f / f;
		return gt2Matrix4x4(_11 * fInv, _12 * fInv, _13 * fInv, _14 * fInv,
			_21 * fInv, _22 * fInv, _23 * fInv, _24 * fInv,
			_31 * fInv, _32 * fInv, _33 * fInv, _34 * fInv,
			_41 * fInv, _42 * fInv, _43 * fInv, _44 * fInv);
	}
	inline gt2Matrix4x4 operator / (const gt2Matrix4x4& rM) const
	{
		return gt2Matrix4x4(
			_11 / rM._11, _12 / rM._12, _13 / rM._13, _14 / rM._14,
			_21 / rM._21, _22 / rM._22, _23 / rM._23, _24 / rM._24,
			_31 / rM._31, _32 / rM._32, _33 / rM._33, _34 / rM._34,
			_41 / rM._41, _42 / rM._42, _43 / rM._43, _44 / rM._44);
	}

	friend inline gt2Matrix4x4 operator * (float f, const gt2Matrix4x4& rM)
	{
		return gt2Matrix4x4(f * rM._11, f * rM._12, f * rM._13, f * rM._14,
			f * rM._21, f * rM._22, f * rM._23, f * rM._24,
			f * rM._31, f * rM._32, f * rM._33, f * rM._34,
			f * rM._41, f * rM._42, f * rM._43, f * rM._44);
	}
	//@}

	//------------------------------------------------------------------------
	//
	//! @name 比較演算子
	//
	//------------------------------------------------------------------------
	//@{
	inline bool operator == (const gt2Matrix4x4& rM) const
	{
		return 0 == memcmp(this, &rM, sizeof(gt2Matrix4x4));
	}
	inline bool operator != (const gt2Matrix4x4& rM) const
	{
		return !(*this == rM);
	}
	//@}

	//-----------------------------------------------------------------------------------
	//! @brief 位置を取得する
	//! @return gt2Vector3を返す
	//-----------------------------------------------------------------------------------
	inline gt2Vector3 GetTranslation() const
	{
		gt2Vector3 out;
		out.x = _41;
		out.y = _42;
		out.z = _43;
		return out;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 位置をセットする
	//! @param [in] rV3 gt2Vector3 構造体へのポインタへ位置情報をセットする。
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void SetTranslation(const gt2Vector3& rV3)
	{
		_41 = rV3.x;
		_42 = rV3.y;
		_43 = rV3.z;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 位置を逆にセットする。各要素に-1を掛けている
	//! @param [in] rV3 gt2Vector3 構造体へのポインタへ位置情報をセットする。
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void SetInverseTranslation(const gt2Vector3& rV3)
	{
		_41 = -rV3.x;
		_42 = -rV3.y;
		_43 = -rV3.z;
	}
	//-----------------------------------------------------------------------------------
	//! @brief スケール値をセットする
	//! @param [in] rV3 gt2Vector3 構造体へのポインタへスケール値情報をセットする。
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void SetScale(const gt2Vector3& rV3)
	{
		_11 = rV3.x;
		_22 = rV3.y;
		_33 = rV3.z;
	}

	//-----------------------------------------------------------------------------------
	//! @brief スケール値をセットする
	//! @return gt2Vector3 で値を取得
	//-----------------------------------------------------------------------------------
	inline gt2Vector3 GetScale() const
	{
		gt2Vector3 out;
		out.x = _11;
		out.y = _22;
		out.z = _33;
		return out;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 軸指定回転の取得
	//! @param [out] pvAxis 回転軸を格納するベクトルへのポインタ
	//! @param [out] pRadian ラジアン単位での回転角度を格納するfloatへのポインタ
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void GetRotationRadians(gt2Vector3* pvAxis, float* pRadian) const
	{
		float radianResult = acosf(0.5f * ((_11 + _22 + _33) - 1.f));
		*pRadian = radianResult;
		if (radianResult > 0.f) {
			if (radianResult < GT2_PI) {
				*pvAxis = gt2Vector3(_32 - _23, _13 - _31, _21 - _12);
				pvAxis->Normalize();
			}
			else {
				if (_11 >= _22) {
					if (_11 >= _33) {
						pvAxis->x = 0.5f * sqrtf(_11 - _22 - _33 + 1.f);
						float halfInverse = 0.5f / pvAxis->x;
						pvAxis->y = halfInverse * _12;
						pvAxis->z = halfInverse * _13;
					}
					else {
						pvAxis->z = 0.5f * sqrtf(_33 - _11 - _22 + 1.f);
						float halfInverse = 0.5f / pvAxis->z;
						pvAxis->x = halfInverse * _13;
						pvAxis->y = halfInverse * _23;
					}
				}
				else {
					if (_22 >= _33) {
						pvAxis->y = 0.5f * sqrtf(_22 - _11 - _33 + 1.f);
						float halfInverse = 0.5f / pvAxis->y;
						pvAxis->x = halfInverse * _12;
						pvAxis->z = halfInverse * _23;
					}
					else {
						pvAxis->z = 0.5f * sqrtf(_33 - _11 - _22 + 1.f);
						float halfInverse = 0.5f / pvAxis->z;
						pvAxis->x = halfInverse * _13;
						pvAxis->y = halfInverse * _23;
					}
				}
			}
		}
		else {
			*pvAxis = gt2Vector3(1.f, 0.f, 0.f);
		}
	}
	//-----------------------------------------------------------------------------------
	//! @brief 軸指定回転の取得
	//! @param [out] rvAxis 回転軸を格納するベクトルへのポインタ
	//! @param [out] rRadian ラジアン単位での回転角度を格納するfloatへのポインタ
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void GetRotationRadians(gt2Vector3& rvAxis, float& rRadian) const
	{
		this->GetRotationRadians(&rvAxis, &rRadian);
	}


	//-----------------------------------------------------------------------------------
	//! @brief x,y,z に回転角度を入力し、このクラスのマトリックスにセットする
	//! @param [out] pOut gt2Vector3 構造体へのポインタへ角度値情報をセットする。
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void SetRotationDegrees(const gt2Vector3* pRot)
	{
		this->SetRotationRadians(&(*pRot * GT2_INV_RADIAN));
	}
	//-----------------------------------------------------------------------------------
	//! @brief x,y,z に回転角度を入力し、このクラスのマトリックスにセットする
	//! @param [in] rRot gt2Vector3 構造体へ角度値情報をセットする。
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void SetRotationDegrees(const gt2Vector3& rRot)
	{
		this->SetRotationDegrees(&rRot);
	}


	//-----------------------------------------------------------------------------------
	//! @brief x,y,z に回転角度を入力し、このクラスのマトリックスにセットする
	//!        ここでは転置されたマトリックスにセットする
	//! @param [out] pRot gt2Vector3 構造体へのポインタへ角度値情報をセットする。
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void SetInverseRotationDegrees(const gt2Vector3* pRot)
	{
		this->SetInverseRotationRadians(&(*pRot * GT2_INV_RADIAN));
	}
	//-----------------------------------------------------------------------------------
	//! @brief x,y,z に回転角度を入力し、このクラスのマトリックスにセットする
	//!        ここでは転置されたマトリックスにセットする
	//! @param [out] rRot gt2Vector3 構造体へ角度値情報をセットする。
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void SetInverseRotationDegrees(const gt2Vector3& rRot)
	{
		this->SetInverseRotationDegrees(&rRot);
	}


	//-----------------------------------------------------------------------------------
	//! @brief 各軸のラジアン値を返す
	//! @return ラジアン値情報を返す
	//-----------------------------------------------------------------------------------
	inline gt2Vector3 GetRotationRadians() const
	{
		gt2Vector3 out;
		out.x = asin(-_23);
		if (out.x < GT2_HALF_PI) {
			if (out.x > -GT2_HALF_PI) {
				out.y = atan2(_13, _33);
				out.z = atan2(_21, _22);
			}
			else {
				out.y = -atan2(-_12, _11);
				out.z = 0.0f;
			}
		}
		else {
			out.y = atan2(-_12, _11);
			out.z = 0.0f;
		}

		if (out.y < 0)
			out.y += GT2_PI2;

		if (out.x < 0)
			out.x += GT2_PI2;

		if (out.z < 0)
			out.z += GT2_PI2;
		return out;
	}

	//-----------------------------------------------------------------------------------
	//! @brief x,y,z にラジアン値を入力し、このクラスのマトリックスにセットする
	//! @param [in] pRot gt2Vector3 構造体へのポインタへラジアン値情報をセットする。
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void SetRotationRadians(const gt2Vector3* pRot)
	{
		double cr = cos(pRot->x);
		double sr = sin(pRot->x);
		double cp = cos(pRot->y);
		double sp = sin(pRot->y);
		double cy = cos(pRot->z);
		double sy = sin(pRot->z);

		_11 = (float)(cp*cy);
		_12 = (float)(cp*sy);
		_13 = (float)(-sp);

		float srsp = (float)(sr*sp);
		float crsp = (float)(cr*sp);

		_21 = (float)(srsp*cy - cr*sy);
		_22 = (float)(srsp*sy + cr*cy);
		_23 = (float)(sr*cp);

		_31 = (float)(crsp*cy + sr*sy);
		_32 = (float)(crsp*sy - sr*cy);
		_33 = (float)(cr*cp);
	}
	//-----------------------------------------------------------------------------------
	//! @brief x,y,z にラジアン値を入力し、このクラスのマトリックスにセットする
	//! @param [in] rRot gt2Vector3 構造体へラジアン値情報をセットする。
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void SetRotationRadians(const gt2Vector3& rRot)
	{
		this->SetRotationRadians(&rRot);
	}

	//-----------------------------------------------------------------------------------
	//! @brief XYZ軸回転の取得
	//! @return 各軸におけるラジアン単位での回転角度
	//-----------------------------------------------------------------------------------
	inline gt2Vector3 GetRotationDegrees() const
	{
		return GetRotationRadians() * GT2_RADIAN;
	}

	//-----------------------------------------------------------------------------------
	//! @brief 各軸の角度の値が入る
	//! @param [out] pvRadian gt2Vector3 構造体へのポインタへ角度値情報を取得する。
	//! @return 答えが単一であればtrue
	//-----------------------------------------------------------------------------------
	inline bool GetRotationXYZ(gt2Vector3* pvRadian) const
	{
		bool bRet;
		float yRadian = asin(-_31);
		pvRadian->y = yRadian;
		if (yRadian < GT2_HALF_PI) {
			if (yRadian > -GT2_HALF_PI) {
				pvRadian->x = atan2f(_32, _33);
				pvRadian->z = atan2f(_21, _11);
				bRet = true;
			}
			else {
				pvRadian->x = -atan2f(_12, _22);
				pvRadian->z = 0.f;
				bRet = false;
			}
		}
		else {
			pvRadian->x = atan2f(_12, _22);
			pvRadian->z = 0.f;
			bRet = false;
		}

		if (pvRadian->y < 0)
			pvRadian->y += GT2_PI2;
		if (pvRadian->x < 0)
			pvRadian->x += GT2_PI2;
		if (pvRadian->z < 0)
			pvRadian->z += GT2_PI2;

		return bRet;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 各軸の角度の値が入る
	//! @param [out] rvRadian gt2Vector3 構造体へ角度値情報を取得する。
	//! @return 答えが単一であればtrue
	//-----------------------------------------------------------------------------------
	inline bool GetRotationXYZ(gt2Vector3 &rvRadian) const
	{
		return this->GetRotationXYZ(&rvRadian);
	}

	//-----------------------------------------------------------------------------------
	//! @brief 各軸の角度の値が入る
	//! @param [out] pvRadian gt2Vector3 構造体へのポインタへ角度値情報を取得する。
	//! @return 答えが単一であればtrue
	//-----------------------------------------------------------------------------------
	inline bool GetRotationXZY(gt2Vector3* pvRadian) const
	{
		bool bRet;

		float zRadian = asinf(_21);
		pvRadian->z = zRadian;
		if (zRadian < GT2_HALF_PI) {
			if (zRadian > -GT2_HALF_PI) {
				pvRadian->x = atan2f(-_23, _22);
				pvRadian->y = atan2f(-_31, _11);
				bRet = true;
			}
			else {
				pvRadian->x = -atan2f(_13, _33);
				pvRadian->y = 0.f;
				bRet = false;
			}
		}
		else {
			pvRadian->x = atan2f(_13, _33);
			pvRadian->y = 0.f;
			bRet = false;
		}

		if (pvRadian->y < 0)
			pvRadian->y += GT2_PI2;
		if (pvRadian->x < 0)
			pvRadian->x += GT2_PI2;
		if (pvRadian->z < 0)
			pvRadian->z += GT2_PI2;

		return bRet;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 各軸の角度の値が入る
	//! @param [out] rvRadian gt2Vector3 構造体へ角度値情報を取得する。
	//! @return 答えが単一であればtrue
	//-----------------------------------------------------------------------------------
	inline bool GetRotationXZY(gt2Vector3 &rvRadian) const
	{
		return this->GetRotationXZY(&rvRadian);
	}

	//-----------------------------------------------------------------------------------
	//! @brief 各軸の角度の値が入る
	//! @param [out] pvRadian gt2Vector3 構造体へのポインタへ角度値情報を取得する。
	//! @return 答えが単一であればtrue
	//-----------------------------------------------------------------------------------
	inline bool GetRotationYXZ(gt2Vector3* pvRadian) const
	{
		bool bRet;
		float xRadian = asinf(_32);
		pvRadian->x = xRadian;
		if (xRadian < GT2_HALF_PI) {
			if (xRadian > -GT2_HALF_PI) {
				pvRadian->y = atan2f(-_31, _33);
				pvRadian->z = atan2f(-_12, _22);
				bRet = true;
			}
			else {
				pvRadian->y = -atan2f(-_21, _11);
				pvRadian->z = 0.f;
				bRet = false;
			}
		}
		else {
			pvRadian->y = atan2f(-_21, _11);
			pvRadian->z = 0.f;
			bRet = false;
		}

		if (pvRadian->y < 0)
			pvRadian->y += GT2_PI2;
		if (pvRadian->x < 0)
			pvRadian->x += GT2_PI2;
		if (pvRadian->z < 0)
			pvRadian->z += GT2_PI2;

		return bRet;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 各軸の角度の値が入る
	//! @param [out] rvRadian gt2Vector3 構造体へ角度値情報を取得する。
	//! @return 答えが単一であればtrue
	//-----------------------------------------------------------------------------------
	inline bool GetRotationYXZ(gt2Vector3 &rvRadian) const
	{
		return this->GetRotationYXZ(&rvRadian);
	}

	//-----------------------------------------------------------------------------------
	//! @brief 各軸の角度の値が入る
	//! @param [out] pvRadian gt2Vector3 構造体へのポインタへ角度値情報を取得する。
	//! @return 答えが単一であればtrue
	//-----------------------------------------------------------------------------------
	inline bool GetRotationYZX(gt2Vector3* pvRadian) const
	{
		bool bRet;
		float zRadian = asin(-_12);
		pvRadian->z = zRadian;
		if (zRadian < GT2_HALF_PI) {
			if (zRadian > -GT2_HALF_PI) {
				pvRadian->y = atan2(_13, _11);
				pvRadian->x = atan2(_32, _22);
				bRet = true;
			}
			else {
				pvRadian->y = -atan2(_23, _33);
				pvRadian->x = 0.f;
				bRet = false;
			}
		}
		else {
			pvRadian->y = atan2(_23, _33);
			pvRadian->x = 0.f;
			bRet = false;
		}

		if (pvRadian->y < 0)
			pvRadian->y += GT2_PI2;
		if (pvRadian->x < 0)
			pvRadian->x += GT2_PI2;
		if (pvRadian->z < 0)
			pvRadian->z += GT2_PI2;

		return bRet;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 各軸の角度の値が入る
	//! @param [out] rvRadian gt2Vector3 構造体へ角度値情報を取得する。
	//! @return 答えが単一であればtrue
	//-----------------------------------------------------------------------------------
	inline bool GetRotationYZX(gt2Vector3 &rvRadian) const
	{
		return this->GetRotationYZX(&rvRadian);
	}

	//-----------------------------------------------------------------------------------
	//! @brief 各軸の角度の値が入る
	//! @param [out] pvRadian gt2Vector3 構造体へのポインタへ角度値情報を取得する。
	//! @return 答えが単一であればtrue
	//-----------------------------------------------------------------------------------
	inline bool GetRotationZXY(gt2Vector3* pvRadian) const
	{
		bool bRet;
		float xRadian = asin(-_23);
		pvRadian->x = xRadian;
		if (xRadian < GT2_HALF_PI) {
			if (xRadian > -GT2_HALF_PI) {
				pvRadian->z = atan2(_21, _22);
				pvRadian->y = atan2(_13, _33);
				bRet = true;
			}
			else {
				pvRadian->z = -atan2(_31, _11);
				pvRadian->y = 0.f;
				bRet = false;
			}
		}
		else {
			pvRadian->z = atan2(_31, _11);
			pvRadian->y = 0.f;
			bRet = false;
		}

		if (pvRadian->y < 0)
			pvRadian->y += GT2_PI2;
		if (pvRadian->x < 0)
			pvRadian->x += GT2_PI2;
		if (pvRadian->z < 0)
			pvRadian->z += GT2_PI2;

		return bRet;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 各軸の角度の値が入る
	//! @param [out] rvRadian gt2Vector3 構造体へ角度値情報を取得する。
	//! @return 答えが単一であればtrue
	//-----------------------------------------------------------------------------------
	inline bool GetRotationZXY(gt2Vector3 &rvRadian) const
	{
		return this->GetRotationZXY(&rvRadian);
	}

	//-----------------------------------------------------------------------------------
	//! @brief 各軸の角度の値が入る
	//! @param [out] pvRadian gt2Vector3 構造体へのポインタへ角度値情報を取得する。
	//! @return 答えが単一であればtrue
	//-----------------------------------------------------------------------------------
	inline bool GetRotationZYX(gt2Vector3* pvRadian) const
	{
		bool bRet;
		float yRadian = asinf(_13);
		pvRadian->y = yRadian;
		if (yRadian < GT2_HALF_PI) {
			if (yRadian > -GT2_HALF_PI) {
				pvRadian->z = atan2f(-_12, _11);
				pvRadian->x = atan2f(-_23, _33);
				bRet = true;
			}
			else {
				pvRadian->z = -atan2f(-_21, _31);
				pvRadian->x = 0.f;
				bRet = false;
			}
		}
		else {
			pvRadian->z = atan2f(_21, -_31);
			pvRadian->x = 0.f;
			bRet = false;
		}

		if (pvRadian->y < 0)
			pvRadian->y += GT2_PI2;
		if (pvRadian->x < 0)
			pvRadian->x += GT2_PI2;
		if (pvRadian->z < 0)
			pvRadian->z += GT2_PI2;

		return bRet;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 各軸の角度の値が入る
	//! @param [out] rvRadian gt2Vector3 構造体へ角度値情報を取得する。
	//! @return 答えが単一であればtrue
	//-----------------------------------------------------------------------------------
	inline bool GetRotationZYX(gt2Vector3 &rvRadian) const
	{
		return this->GetRotationZYX(&rvRadian);
	}

	//-----------------------------------------------------------------------------------
	//! @brief x,y,z にラジアン値を入力し、このクラスのマトリックスにセットする。
	//!        ここでは転置されたマトリックスにセットする
	//! @param [in] pRot gt2Vector3 構造体へのポインタへラジアン値情報をセットする。
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void SetInverseRotationRadians(const gt2Vector3* pRot)
	{
		double cr = cos(pRot->x);
		double sr = sin(pRot->x);
		double cp = cos(pRot->y);
		double sp = sin(pRot->y);
		double cy = cos(pRot->z);
		double sy = sin(pRot->z);

		_11 = (float)(cp*cy);
		_21 = (float)(cp*sy);
		_31 = (float)(-sp);

		double srsp = sr*sp;
		double crsp = cr*sp;

		_12 = (float)(srsp*cy - cr*sy);
		_22 = (float)(srsp*sy + cr*cy);
		_32 = (float)(sr*cp);

		_13 = (float)(crsp*cy + sr*sy);
		_23 = (float)(crsp*sy - sr*cy);
		_33 = (float)(cr*cp);
	}
	//-----------------------------------------------------------------------------------
	//! @brief x,y,z にラジアン値を入力し、このクラスのマトリックスにセットする。
	//!        ここでは転置されたマトリックスにセットする
	//! @param [in] rRot gt2Vector3 構造体へラジアン値情報をセットする。
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void SetInverseRotationRadians(const gt2Vector3 &rRot)
	{
		this->SetInverseRotationRadians(&rRot);
	}

	//-----------------------------------------------------------------------------------
	//! @brief 単位行列を作成する。
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void MakeIdentity()
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixIdentity();
#else
		memset(mm, 0, 16 * sizeof(float));
		_11 = _22 = _33 = _44 = 1.0f;
#endif
	}
	//-----------------------------------------------------------------------------------
	//! @brief 行列が単位行列かどうかを判定する。
	//! @param [in] rRot gt2Vector3 構造体へラジアン値情報をセットする。
	//! @return 行列が単位行列である場合、この関数は true を返す。@n
	//! それ以外の場合は、false を返す。
	//-----------------------------------------------------------------------------------
	inline bool IsIdentity() const
	{
		for (int i = 0; i<4; ++i) {
			for (int j = 0; j<4; ++j)
				if (j != i)
				{
					if ((*this).m[i][j] < -0.0000001f ||
						(*this).m[i][j] > 0.0000001f)
						return false;
				}
				else
				{
					if ((*this).m[i][j] < 0.9999999f ||
						(*this).m[i][j] > 1.0000001f)
						return false;
				}
		}
		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 元となる位置（src)からこのマトリクスを元に回転した位置を返す
	//! @param [in]  src 元となる位置
	//! @return  回転した位置
	//-----------------------------------------------------------------------------------
	inline gt2Vector3 RotateVector3(const gt2Vector3& src) const
	{
		gt2Vector3 out;
		out.x = src.x*_11 + src.y*_21 + src.z*_31;
		out.y = src.x*_12 + src.y*_22 + src.z*_32;
		out.z = src.x*_13 + src.y*_23 + src.z*_33;
		return out;
	}

	//-----------------------------------------------------------------------------------
	//! @brief 元となる位置（src)からこの逆マトリクスを元に回転した位置を返す
	//! @param [in]  src 元となる位置
	//! @return  回転した位置
	//-----------------------------------------------------------------------------------
	inline gt2Vector3 InverseRotateVector3(const gt2Vector3& src) const
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		DirectX::XMVECTOR out;
		gt2Vector3 out2;
		DirectX::XMMatrixInverse(&out, (DirectX::FXMMATRIX)*this);
		out2 = out;
		return out2;
#else
		gt2Vector3 out;
		out.x = src.x*_11 + src.y*_12 + src.z*_13;
		out.y = src.x*_21 + src.y*_22 + src.z*_23;
		out.z = src.x*_31 + src.y*_32 + src.z*_33;
		return out;
#endif
	}

	//-----------------------------------------------------------------------------------
	//! @brief 元となる位置（src)からこのマトリクスを元に変形した位置を返す
	//! @param [in]  src 元となる位置
	//! @return  変形した位置
	//-----------------------------------------------------------------------------------
	inline gt2Vector3 TransformVector3(const gt2Vector3& src) const
	{
		gt2Vector3 out;
		out.x = src.x*_11 + src.y*_21 + src.z*_31 + _41;
		out.y = src.x*_12 + src.y*_22 + src.z*_32 + _42;
		out.z = src.x*_13 + src.y*_23 + src.z*_33 + _43;
		return out;
	}

	//-----------------------------------------------------------------------------------
	//! @brief 元となる位置（src)からこのマトリクスを元に逆に移動した位置を返す
	//! @param [in]  src 元となる位置
	//! @return  逆に移動した位置
	//-----------------------------------------------------------------------------------
	inline gt2Vector3 InverseTranslateVector3(const gt2Vector3& src) const
	{
		gt2Vector3 out;
		out.x = src.x - _41;
		out.y = src.y - _42;
		out.z = src.z - _43;
		return out;
	}

	//-----------------------------------------------------------------------------------
	//! @brief 元となる位置（src)からこの逆マトリクスを元に移動した位置を返す
	//! @param [in]  src 元となる位置
	//! @return  移動した位置
	//-----------------------------------------------------------------------------------
	inline gt2Vector3 TranslateVector3(const gt2Vector3& src) const
	{
		gt2Vector3 out;
		out.x = src.x + _41;
		out.y = src.y + _42;
		out.z = src.z + _43;
		return out;
	}

	//-----------------------------------------------------------------------------------
	//! @brief 行列の逆行列を計算する。
	//! @param [out]  pDeterminant 行列の行列式を含む float 値へのポインタ。
	//!                            行列式が不要の場合は、このパラメータに nullptr を設定する。
	//! @param [out]  pOut         演算結果である gt2Matrix4x4 構造体へのポインタ。
	//! @return  逆行列の計算が失敗した場合は、false を返す。
	//-----------------------------------------------------------------------------------
	inline bool GetInverse(float *pDeterminant, gt2Matrix4x4* pOut) const
	{
		float d;

		d = (_11 * _22 - _12 * _21) * (_33 * _44 - _34 * _43) -
			(_11 * _23 - _13 * _21) * (_32 * _44 - _34 * _42) +
			(_11 * _24 - _14 * _21) * (_32 * _43 - _33 * _42) +
			(_12 * _23 - _13 * _22) * (_31 * _44 - _34 * _41) -
			(_12 * _24 - _14 * _22) * (_31 * _43 - _33 * _41) +
			(_13 * _24 - _14 * _23) * (_31 * _42 - _32 * _41);

		if (d == 0.0f)
			return false;

		d = 1.0f / d;

		pOut->_11 = d * (_22 * (_33 * _44 - _34 * _43) + _23 * (_34 * _42 - _32 * _44) + _24 * (_32 * _43 - _33 * _42));
		pOut->_12 = d * (_32 * (_13 * _44 - _14 * _43) + _33 * (_14 * _42 - _12 * _44) + _34 * (_12 * _43 - _13 * _42));
		pOut->_13 = d * (_42 * (_13 * _24 - _14 * _23) + _43 * (_14 * _22 - _12 * _24) + _44 * (_12 * _23 - _13 * _22));
		pOut->_14 = d * (_12 * (_24 * _33 - _23 * _34) + _13 * (_22 * _34 - _24 * _32) + _14 * (_23 * _32 - _22 * _33));
		pOut->_21 = d * (_23 * (_31 * _44 - _34 * _41) + _24 * (_33 * _41 - _31 * _43) + _21 * (_34 * _43 - _33 * _44));
		pOut->_22 = d * (_33 * (_11 * _44 - _14 * _41) + _34 * (_13 * _41 - _11 * _43) + _31 * (_14 * _43 - _13 * _44));
		pOut->_23 = d * (_43 * (_11 * _24 - _14 * _21) + _44 * (_13 * _21 - _11 * _23) + _41 * (_14 * _23 - _13 * _24));
		pOut->_24 = d * (_13 * (_24 * _31 - _21 * _34) + _14 * (_21 * _33 - _23 * _31) + _11 * (_23 * _34 - _24 * _33));
		pOut->_31 = d * (_24 * (_31 * _42 - _32 * _41) + _21 * (_32 * _44 - _34 * _42) + _22 * (_34 * _41 - _31 * _44));
		pOut->_32 = d * (_34 * (_11 * _42 - _12 * _41) + _31 * (_12 * _44 - _14 * _42) + _32 * (_14 * _41 - _11 * _44));
		pOut->_33 = d * (_44 * (_11 * _22 - _12 * _21) + _41 * (_12 * _24 - _14 * _22) + _42 * (_14 * _21 - _11 * _24));
		pOut->_34 = d * (_14 * (_22 * _31 - _21 * _32) + _11 * (_24 * _32 - _22 * _34) + _12 * (_21 * _34 - _24 * _31));
		pOut->_41 = d * (_21 * (_33 * _42 - _32 * _43) + _22 * (_31 * _43 - _33 * _41) + _23 * (_32 * _41 - _31 * _42));
		pOut->_42 = d * (_31 * (_13 * _42 - _12 * _43) + _32 * (_11 * _43 - _13 * _41) + _33 * (_12 * _41 - _11 * _42));
		pOut->_43 = d * (_41 * (_13 * _22 - _12 * _23) + _42 * (_11 * _23 - _13 * _21) + _43 * (_12 * _21 - _11 * _22));
		pOut->_44 = d * (_11 * (_22 * _33 - _23 * _32) + _12 * (_23 * _31 - _21 * _33) + _13 * (_21 * _32 - _22 * _31));

		if (pDeterminant != nullptr) *pDeterminant = d;
		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 行列の逆行列を計算する。
	//! @param [out]  rDeterminant 行列の行列式を含む値
	//! @param [out]  rOut         演算結果である gt2Matrix4x4 構造体
	//! @return  逆行列の計算が失敗した場合は、false を返す。
	//-----------------------------------------------------------------------------------
	inline bool GetInverse(float &rDeterminant, gt2Matrix4x4& rOut) const
	{
		return this->GetInverse(&rDeterminant, &rOut);
	}

	//-----------------------------------------------------------------------------------
	//! @brief アフィン変換行列を作成します。
	//! @param [in] scaling            各次元のスケーリング係数のベクトル。
	//! @param [in] rotationOrigin     回転の中心を特定指す。
	//! @param [in] rotationQuaternion 回転要因。
	//! @param [in] translation        位置オフセット。
	//! @return  なし
	//-----------------------------------------------------------------------------------
	inline void MakeAffineTransformation(const gt2Vector3 &scaling, const gt2Vector3 &rotationOrigin, const gt2Quaternion &rotationQuaternion, const gt2Vector3 &translation)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		DirectX::XMVECTOR a, b, c, d;
		a = scaling.GetXMVECTOR();
		b = rotationOrigin.GetXMVECTOR();
		c = rotationQuaternion.GetXMVECTOR();
		d = translation.GetXMVECTOR();
		*this = DirectX::XMMatrixAffineTransformation(a, b, c, d);
#else
		// M = MScaling * Inverse(MRotationOrigin) * MRotation * MRotationOrigin * MTranslation;
		gt2Matrix4x4 mRotation;
		this->MakeScale(scaling);
		mRotation.MakeRotationQuaternion(rotationQuaternion);

		_41 -= rotationOrigin.x; _42 -= rotationOrigin.y; _43 -= rotationOrigin.z;

		*this *= mRotation;
		_41 += rotationOrigin.x; _42 += rotationOrigin.y; _43 += rotationOrigin.z;
		_41 += translation.x;    _42 += translation.y;    _43 += translation.z;
#endif
	}
	//-----------------------------------------------------------------------------------
	//! @brief 2D アフィン変換行列を作成します。
	//! @param [in] scaling            2次元のスケーリング係数のベクトル。
	//! @param [in] rotationOrigin     2次元の回転の中心を指す。
	//! @param [in] rotation           回転のラジアン角。
	//! @param [in] translation        2次元ベクトル変換オフセット。
	//! @return  なし
	//-----------------------------------------------------------------------------------
	inline void MakeAffineTransformation2D(const gt2Vector2 &scaling, const gt2Vector2 &rotationOrigin, const float rotation, const gt2Vector2 &translation)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		DirectX::XMVECTOR a, b, c;
		a = scaling.GetXMVECTOR();
		b = rotationOrigin.GetXMVECTOR();
		c = translation.GetXMVECTOR();
		*this = DirectX::XMMatrixAffineTransformation2D(a, b, rotation, c);
#else
		// M = MScaling * Inverse(MRotationOrigin) * MRotation * MRotationOrigin * MTranslation;
		gt2Matrix4x4 mRotation;
		this->MakeScale(gt2Vector3(scaling.x, scaling.y, 0));
		mRotation.MakeRotationZ(rotation);

		_41 -= rotationOrigin.x; _42 -= rotationOrigin.y;

		*this *= mRotation;
		_41 += rotationOrigin.x; _42 += rotationOrigin.y;;
		_41 += translation.x;    _42 += translation.y;
#endif
	}

	//-----------------------------------------------------------------------------------
	//! @brief 対角成分がpIn で与えられ，他の成分が0である行列を返す．
	//! @param [in]  pIn gt2Vector3 構造体へのポインタへ位置情報を取得する。
	//! @param [in]  k  k 番目の対角上のリストの要素の値．
	//! @return  なし
	//-----------------------------------------------------------------------------------
	inline void MakeDiagonal(const gt2Vector4* pIn, int k)
	{
		if (k < -3 || k > 3) return;

		_11 = _12 = _13 = 0.0f;
		_21 = _22 = _23 = 0.0f;
		_31 = _32 = _33 = 0.0f;

		if (k < 0) {
			k = abs(k) * 5;
		}
		mm[k] = pIn->x;
		if ((k += 5) > 15)return;
		mm[k] = pIn->y;
		if ((k += 5) > 15)return;
		mm[k] = pIn->z;
		if ((k += 5) > 15)return;
		mm[k] = pIn->w;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 対角成分がpIn で与えられ，他の成分が0である行列を返す．
	//! @param [in]  rIn gt2Vector3 構造体へ位置情報を取得する。
	//! @param [in]  k  k 番目の対角上のリストの要素の値．
	//! @return  なし
	//-----------------------------------------------------------------------------------
	inline void MakeDiagonal(const gt2Vector4 &rIn, int k)
	{
		this->MakeDiagonal(&rIn, k);
	}


	//-----------------------------------------------------------------------------------
	//! @brief 位置を指すベクトルから、自信のマトリクスを作り替える
	//! @param [in]  rV3 位置情報
	//! @return  なし
	//-----------------------------------------------------------------------------------
	inline void MakeTranslation(const gt2Vector3& rV3)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixTranslation(rV3.x, rV3.y, rV3.z);
#else
		this->MakeIdentity();
		this->SetTranslation(rV3);
#endif
	}
	//-----------------------------------------------------------------------------------
	//! @brief スケール値を指すベクトルから、自信のマトリクスを作り替える
	//! @param [in]  rV3 スケール値
	//! @return  なし
	//-----------------------------------------------------------------------------------
	inline void MakeScale(const gt2Vector3& rV3)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixScaling(rV3.x, rV3.y, rV3.z);
#else

		this->MakeIdentity();
		this->SetScale(rV3);
#endif
	}

	//-----------------------------------------------------------------------------------
	//! @brief 視野に基づいて、左手座標系遠近射影行列を作成する。
	//! @param [in]  fovy   方向の視野 (ラジアン単位)。
	//! @param [in]  aspect ビュー空間の幅を高さで乗算して定義したアスペクト比。
	//! @param [in]  zn     近いビュー平面の Z 値。
	//! @param [in]  zf     遠いビュー平面の Z 値。
	//! @return  なし
	//-----------------------------------------------------------------------------------
	inline void MakePerspectiveFovLH(float fovy, float aspect, float zn, float zf)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixPerspectiveFovLH(fovy, aspect, zn, zf);
#else

		//xScale     0          0               0
		//0        yScale       0               0
		//0          0       zf/(zf-zn)         1
		//0          0       -zn*zf/(zf-zn)     0
		//where:
		//yScale = cot(fovY/2)

		//xScale = aspect ratio * yScale

		float yScale = (float)(1.0 / tan(fovy*0.5f));
		float xScale = yScale / aspect;

		_11 = xScale;
		_12 = 0.0f;
		_13 = 0.0f;
		_14 = 0.0f;

		_21 = 0.0f;
		_22 = yScale;
		_23 = 0.0f;
		_24 = 0.0f;

		_31 = 0.0f;
		_32 = 0.0f;
		_33 = zf / (zf - zn); // DirectX バージョン
								//		_33 = zf+zn/(zn-zf); // OpenGL バージョン
		_34 = 1.0f;

		_41 = 0.0f;
		_42 = 0.0f;
		_43 = -zn*zf / (zf - zn); // DirectX バージョン
									//		_43 = 2.0f*zn*zf/(zn-zf); // OpenGL バージョン
		_44 = 0.0f;
#endif
	}
	//-----------------------------------------------------------------------------------
	//! @brief 視野に基づいて、右手座標系遠近射影行列を作成する。
	//! @param [in]  fovy   方向の視野 (ラジアン単位)。
	//! @param [in]  aspect ビュー空間の幅を高さで乗算して定義したアスペクト比。
	//! @param [in]  zn     近いビュー平面の Z 値。
	//! @param [in]  zf     遠いビュー平面の Z 値。
	//! @return  なし
	//-----------------------------------------------------------------------------------
	inline void MakePerspectiveFovRH(float fovy, float aspect, float zn, float zf)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixPerspectiveFovRH(fovy, aspect, zn, zf);
#else
		//xScale     0          0              0
		//0        yScale       0              0
		//0        0        zf/(zn-zf)        -1
		//0        0        zn*zf/(zn-zf)      0
		//where:
		//yScale = cot(fovY/2)

		//xScale = aspect ratio * yScale
		float yScale = (float)(1.0 / tan(fovy / 2.0));
		float xScale = yScale / aspect;

		_11 = xScale;
		_12 = 0.0f;
		_13 = 0.0f;
		_14 = 0.0f;

		_21 = 0.0f;
		_22 = yScale;
		_23 = 0.0f;
		_24 = 0.0f;

		_31 = 0.0f;
		_32 = 0.0f;
		_33 = zf / (zn - zf);
		_34 = -1.0f;

		_41 = 0.0f;
		_42 = 0.0f;
		_43 = zn*zf / (zn - zf);
		_44 = 0.0f;
#endif
	}

	//-----------------------------------------------------------------------------------
	//! @brief 左手座標系正射影行列を作成する。
	//! @param [in]  w  ビュー ボリュームの幅。
	//! @param [in]  h  ビュー ボリュームの高さ。
	//! @param [in]  zn ビュー ボリュームの最小 z 値。これを近 z と呼びます。
	//! @param [in]  zf ビュー ボリュームの最大 z 値。これを遠 z と呼びます。
	//! @return  なし
	//-----------------------------------------------------------------------------------
	inline void MakeOrthographicLH(float w, float h, float zn, float zf)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixOrthographicLH(w, h, zn, zf);
#else
		_11 = 2 / w;
		_12 = 0;
		_13 = 0;
		_14 = 0;

		_21 = 0;
		_22 = 2 / h;
		_23 = 0;
		_24 = 0;

		_31 = 0;
		_32 = 0;
		_33 = 1 / (zf - zn);
		_34 = 0;

		_41 = 0;
		_42 = 0;
		_43 = zn / (zn - zf);
		_44 = 1;
#endif
	}
	//-----------------------------------------------------------------------------------
	//! @brief 右手座標系正射影行列を作成する。
	//! @param [in]  w  ビュー ボリュームの幅。
	//! @param [in]  h  ビュー ボリュームの高さ。
	//! @param [in]  zn ビュー ボリュームの最小 z 値。これを近 z と呼びます。
	//! @param [in]  zf ビュー ボリュームの最大 z 値。これを遠 z と呼びます。
	//! @return  なし
	//-----------------------------------------------------------------------------------
	inline void MakeOrthographicRH(float w, float h, float zn, float zf)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixOrthographicRH(w, h, zn, zf);
#else
		_11 = 2 / w;
		_12 = 0;
		_13 = 0;
		_14 = 0;

		_21 = 0;
		_22 = 2 / h;
		_23 = 0;
		_24 = 0;

		_31 = 0;
		_32 = 0;
		_33 = 1 / (zn - zf);
		_34 = 0;

		_41 = 0;
		_42 = 0;
		_43 = zn / (zn - zf);
		_44 = -1;
#endif
	}
	//-----------------------------------------------------------------------------------
	//! @brief 左手座標系遠近射影行列を作成する。
	//! @param [in]  w  近いビュー平面でのビュー ボリュームの幅。
	//! @param [in]  h  近いビュー平面でのビュー ボリュームの高さ。
	//! @param [in]  zn 近いビュー平面の Z 値。
	//! @param [in]  zf 遠いビュー平面の Z 値。
	//! @return  なし
	//-----------------------------------------------------------------------------------
	inline void MakePerspectiveLH(float w, float h, float zn, float zf)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixPerspectiveLH(w, h, zn, zf);
#else
		_11 = 2 * zn / w;
		_12 = 0;
		_13 = 0;
		_14 = 0;

		_21 = 0;
		_22 = 2 * zn / h;
		_23 = 0;
		_24 = 0;

		_31 = 0;
		_32 = 0;
		_33 = zf / (zf - zn);
		_34 = 1;

		_41 = 0;
		_42 = 0;
		_43 = zn*zf / (zn - zf);
		_44 = 0;
#endif
	}
	//-----------------------------------------------------------------------------------
	//! @brief 右手座標系遠近射影行列を作成する。
	//! @param [in]  w  近いビュー平面でのビュー ボリュームの幅。
	//! @param [in]  h  近いビュー平面でのビュー ボリュームの高さ。
	//! @param [in]  zn 近いビュー平面の Z 値。
	//! @param [in]  zf 遠いビュー平面の Z 値。
	//! @return  なし
	//-----------------------------------------------------------------------------------
	inline void MakePerspectiveRH(float w, float h, float zn, float zf)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixPerspectiveRH(w, h, zn, zf);
#else
		_11 = 2 * zn / w;
		_12 = 0;
		_13 = 0;
		_14 = 0;

		_21 = 0;
		_22 = 2 * zn / h;
		_23 = 0;
		_24 = 0;

		_31 = 0;
		_32 = 0;
		_33 = zf / (zn - zf);
		_34 = -1;

		_41 = 0;
		_42 = 0;
		_43 = zn*zf / (zn - zf);
		_44 = 0;
#endif
	}
	//-----------------------------------------------------------------------------------
	//! @brief 左手座標系のカスタム直交射影行列を作成します。
	//! @param [in]  viewLeft   ニアクリッピング面でのクリッピング錐台の左側のx座標。
	//! @param [in]  viewRight  ニアクリッピング面でのクリッピング錐台の右側のx座標。
	//! @param [in]  viewBottom ニアクリッピング面でのクリッピング錐台の底面側のy座標。
	//! @param [in]  viewTop    ニアクリッピング面でクリッピング錐台の上側のY座標。
	//! @param [in]  nearZ      ニアクリップ面までの距離。
	//! @param [in]  farZ       ファークリッピング面までの距離。
	//! @return  なし
	//-----------------------------------------------------------------------------------
	inline void MakeOrthographicOffCenterLH(float viewLeft, float viewRight, float viewBottom, float viewTop, float nearZ, float farZ)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixOrthographicOffCenterLH(viewLeft, viewRight, viewBottom, viewTop, nearZ, farZ);
#else
		float reciprocalWidth = 1.0f / (viewRight - viewLeft);
		float reciprocalHeight = 1.0f / (viewTop - viewBottom);
		float fRange = 1.0f / (farZ - nearZ);

		_11 = reciprocalWidth + reciprocalWidth;
		_12 = 0.0f;
		_13 = 0.0f;
		_14 = 0.0f;

		_21 = 0.0f;
		_22 = reciprocalHeight + reciprocalHeight;
		_23 = 0.0f;
		_24 = 0.0f;

		_31 = 0.0f;
		_32 = 0.0f;
		_33 = fRange;
		_34 = 0.0f;

		_41 = -(viewLeft + viewRight) * reciprocalWidth;
		_42 = -(viewTop + viewBottom) * reciprocalHeight;
		_43 = -fRange * nearZ;
		_44 = 1.0f;
#endif
	}
	//-----------------------------------------------------------------------------------
	//! @brief 右手座標系のカスタム直交射影行列を作成します。
	//! @param [in]  viewLeft   ニアクリッピング面でのクリッピング錐台の左側のx座標。
	//! @param [in]  viewRight  ニアクリッピング面でのクリッピング錐台の右側のx座標。
	//! @param [in]  viewBottom ニアクリッピング面でのクリッピング錐台の底面側のy座標。
	//! @param [in]  viewTop    ニアクリッピング面でクリッピング錐台の上側のY座標。
	//! @param [in]  nearZ      ニアクリップ面までの距離。
	//! @param [in]  farZ       ファークリッピング面までの距離。
	//! @return  なし
	//-----------------------------------------------------------------------------------
	inline void MakeOrthographicOffCenterRH(float viewLeft, float viewRight, float viewBottom, float viewTop, float nearZ, float farZ)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixOrthographicOffCenterRH(viewLeft, viewRight, viewBottom, viewTop, nearZ, farZ);
#else
		float reciprocalWidth = 1.0f / (viewRight - viewLeft);
		float reciprocalHeight = 1.0f / (viewTop - viewBottom);
		float fRange = 1.0f / (nearZ - farZ);

		_11 = reciprocalWidth + reciprocalWidth;
		_12 = 0.0f;
		_13 = 0.0f;
		_14 = 0.0f;

		_21 = 0.0f;
		_22 = reciprocalHeight + reciprocalHeight;
		_23 = 0.0f;
		_24 = 0.0f;

		_31 = 0.0f;
		_32 = 0.0f;
		_33 = fRange;
		_34 = 0.0f;

		_41 = -(viewLeft + viewRight) * reciprocalWidth;
		_42 = -(viewTop + viewBottom) * reciprocalHeight;
		_43 = -fRange * nearZ;
		_44 = 1.0f;
#endif
	}

	//-----------------------------------------------------------------------------------
	//! @brief 左手座標系パースペクティブ射影行列のカスタムバージョンを構築します。
	//! @param [in]  viewLeft   ニアクリッピング面でのクリッピング錐台の左側のx座標。
	//! @param [in]  viewRight  ニアクリッピング面でのクリッピング錐台の右側のx座標。
	//! @param [in]  viewBottom ニアクリッピング面でのクリッピング錐台の底面側のy座標。
	//! @param [in]  viewTop    ニアクリッピング面でクリッピング錐台の上側のY座標。
	//! @param [in]  nearZ      ニアクリップ面までの距離。
	//! @param [in]  farZ       ファークリッピング面までの距離。
	//! @return  なし
	//-----------------------------------------------------------------------------------
	inline void MakePerspectiveOffCenterLH(float viewLeft, float viewRight, float viewBottom, float viewTop, float nearZ, float farZ)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixPerspectiveOffCenterLH(viewLeft, viewRight, viewBottom, viewTop, nearZ, farZ);
#else
		float twoNearZ = nearZ + nearZ;
		float reciprocalWidth = 1.0f / (viewRight - viewLeft);
		float reciprocalHeight = 1.0f / (viewTop - viewBottom);
		float fRange = farZ / (farZ - nearZ);

		_11 = twoNearZ * reciprocalWidth;
		_12 = 0.0f;
		_13 = 0.0f;
		_14 = 0.0f;

		_21 = 0.0f;
		_22 = twoNearZ * reciprocalHeight;
		_23 = 0.0f;
		_24 = 0.0f;

		_31 = -(viewLeft + viewRight) * reciprocalWidth;
		_32 = -(viewTop + viewBottom) * reciprocalHeight;
		_33 = fRange;
		_34 = 1.0f;

		_41 = 0.0f;
		_42 = 0.0f;
		_43 = -fRange * nearZ;
		_44 = 0.0f;
#endif
	}
	//-----------------------------------------------------------------------------------
	//! @brief 右手座標系パースペクティブ射影行列のカスタムバージョンを構築します。
	//! @param [in]  viewLeft   ニアクリッピング面でのクリッピング錐台の左側のx座標。
	//! @param [in]  viewRight  ニアクリッピング面でのクリッピング錐台の右側のx座標。
	//! @param [in]  viewBottom ニアクリッピング面でのクリッピング錐台の底面側のy座標。
	//! @param [in]  viewTop    ニアクリッピング面でクリッピング錐台の上側のY座標。
	//! @param [in]  nearZ      ニアクリップ面までの距離。
	//! @param [in]  farZ       ファークリッピング面までの距離。
	//! @return  なし
	//-----------------------------------------------------------------------------------
	inline void MakePerspectiveOffCenterRH(float viewLeft, float viewRight, float viewBottom, float viewTop, float nearZ, float farZ)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixPerspectiveOffCenterRH(viewLeft, viewRight, viewBottom, viewTop, nearZ, farZ);
#else
		float twoNearZ = nearZ + nearZ;
		float reciprocalWidth = 1.0f / (viewRight - viewLeft);
		float reciprocalHeight = 1.0f / (viewTop - viewBottom);
		float fRange = farZ / (nearZ - farZ);

		_11 = twoNearZ * reciprocalWidth;
		_12 = 0.0f;
		_13 = 0.0f;
		_14 = 0.0f;

		_21 = 0.0f;
		_22 = twoNearZ * reciprocalHeight;
		_23 = 0.0f;
		_24 = 0.0f;

		_31 = (viewLeft + viewRight) * reciprocalWidth;
		_32 = (viewTop + viewBottom) * reciprocalHeight;
		_33 = fRange;
		_34 = -1.0f;

		_41 = 0.0f;
		_42 = 0.0f;
		_43 = fRange * nearZ;
		_44 = 0.0f;
#endif
	}
	//-----------------------------------------------------------------------------------
	//! @brief ジオメトリを平面に射影するトランスフォーム行列を作成します。
	//! @param [in]  w  ライトの位置を記述する 4D ベクトル。ライトの w 要素が 0.0f の場合、
	//!                 原点からライトまでの光線はディレクショナル ライトを表します。
	//!                 ライトの w 要素が 1.0f の場合、ライトはポイントライト
	//! @param [in]  rPlane  基準面
	//! @return  なし
	//-----------------------------------------------------------------------------------
	inline void MakedShadowMatrix(const gt2Vector4& rLight, const gt2Plane3& rPlane)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixShadow(rPlane.GetXMVECTOR(), rLight.GetXMVECTOR());
#else
		gt2Vector3 vTmp(rLight.v);
		gt2Vector3 vN;
		rPlane.vNormal.Normalize(&vN);
		float d = vN.Dot(vTmp);

		_11 = vN.x * rLight.x + d;
		_12 = vN.x * rLight.y;
		_13 = vN.x * rLight.z;
		_14 = vN.x * rLight.w;

		_21 = vN.y * rLight.x;
		_22 = vN.y * rLight.y + d;
		_23 = vN.y * rLight.z;
		_24 = vN.y * rLight.w;

		_31 = vN.z * rLight.x;
		_32 = vN.z * rLight.y;
		_33 = vN.z * rLight.z + d;
		_34 = vN.z * rLight.w;

		_41 = rPlane.distance * rLight.x + d;
		_42 = rPlane.distance * rLight.y;
		_43 = rPlane.distance * rLight.z;
		_44 = rPlane.distance * rLight.w;
#endif
	}
	//-----------------------------------------------------------------------------------
	//! @brief XY平面内で2次元の変換行列を作成します。
	//! @param [in]  scalingOrigin   スケーリングの中心を記述し、2次元のベクトル。
	//! @param [in]  scalingOrientation  回転係数をスケーリングする。
	//! @param [in]  scaling         x軸、y軸のスケーリング因子を含む2Dベクター。
	//! @param [in]  rotationOrigin  回転の中心を記述し、2次元のベクトル。
	//! @param [in]  rotation        回転角度（ラジアン単位）。
	//! @param [in]  translation     x軸、y軸に沿った移動を記述する2Dベクター。
	//! @return  なし
	//-----------------------------------------------------------------------------------
	inline void MakeTransformation2D(
		const gt2Vector2 &scalingOrigin,
		const float scalingOrientation,
		const gt2Vector2 &scaling,
		const gt2Vector3 &rotationOrigin,
		const float rotation,
		const gt2Vector3 &translation
	)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixTransformation2D(
			scalingOrigin.GetXMVECTOR(),
			scalingOrientation,
			scaling.GetXMVECTOR(),
			rotationOrigin.GetXMVECTOR(),
			rotation,
			translation.GetXMVECTOR());
#else
		// M = Inverse(MScalingOrigin) * Transpose(MScalingOrientation) * MScaling * MScalingOrientation *
		//         MScalingOrigin * Inverse(MRotationOrigin) * MRotation * MRotationOrigin * MTranslation;

		gt2Matrix4x4 MScalingOriginI, MScalingOrientation, MScalingOrientationT, MScaling, MRotation;


		MScalingOriginI.MakeTranslation(gt2Vector3(scalingOrigin.x, scalingOrigin.y, 0.0)*-1);
		MScalingOrientation.MakeRotationZ(scalingOrientation);
		MScalingOrientationT = MScalingOrientation.GetTranspose();
		MScaling.MakeScale(gt2Vector3(scaling.x, scaling.y, 0.0));
		MRotation.MakeRotationZ(rotation);

		*this = MScalingOriginI * MScalingOrientationT;
		*this *= MScaling;
		*this *= MScalingOrientation;
		_31 = scalingOrigin.x;  _32 = scalingOrigin.y;
		_31 -= rotationOrigin.x; _32 -= rotationOrigin.y; _33;
		*this *= MRotation;
		_31 += rotationOrigin.x; _32 += rotationOrigin.y; _33 += rotationOrigin.z;
		_31 += translation.x;    _32 += translation.y;    _33 += translation.z;
#endif
	}
	//-----------------------------------------------------------------------------------
	//! @brief 変換行列を作成します。
	//! @param [in]  scalingOrigin      スケーリングの中心を記述する3Dベクトル。
	//! @param [in]  scalingOrientationQuaternion  スケーリングの向きを説明する四元。
	//! @param [in]  scaling            x軸、y軸、z軸のスケーリング因子を含む3Dベクター。
	//! @param [in]  rotationOrigin     回転の中心を記述する3Dベクトル。
	//! @param [in]  rotationQuaternion RotationOriginで示され、原点を中心とした回転を記述した四元。
	//! @param [in]  translation        x軸、y軸、z軸に沿った移動を記述する3Dベクター。
	//! @return  なし
	//-----------------------------------------------------------------------------------
	inline void MakeTransformation(
		const gt2Vector3 &scalingOrigin,
		const gt2Quaternion &scalingOrientationQuaternion,
		const gt2Vector3 &scaling,
		const gt2Vector3 &rotationOrigin,
		const gt2Quaternion &rotationQuaternion,
		const gt2Vector3 &translation
	)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixTransformation(
			scalingOrigin.GetXMVECTOR(),
			scalingOrientationQuaternion.GetXMVECTOR(),
			scaling.GetXMVECTOR(),
			rotationOrigin.GetXMVECTOR(),
			rotationQuaternion.GetXMVECTOR(),
			translation.GetXMVECTOR());
#else
		// M = Inverse(MScalingOrigin) * Transpose(MScalingOrientation) * MScaling * MScalingOrientation *
		//         MScalingOrigin * Inverse(MRotationOrigin) * MRotation * MRotationOrigin * MTranslation;

		gt2Matrix4x4 MScalingOriginI, MScalingOrientation, MScalingOrientationT, MScaling, MRotation;
		MScalingOriginI.MakeTranslation(scalingOrigin*-1);
		MScalingOrientation.MakeRotationQuaternion(scalingOrientationQuaternion);
		MScalingOrientationT = MScalingOrientation.GetTranspose();
		MScaling.MakeScale(scaling);
		MRotation.MakeRotationQuaternion(rotationQuaternion);


		*this = MScalingOriginI * MScalingOrientationT;
		*this *= MScaling;
		*this *= MScalingOrientation;
		_31 = scalingOrigin.x;  _32 = scalingOrigin.y;  _33 = scalingOrigin.z;
		_31 -= rotationOrigin.x; _32 -= rotationOrigin.y; _33 -= rotationOrigin.z;
		*this *= MRotation;
		_31 += rotationOrigin.x; _32 += rotationOrigin.y; _33 += rotationOrigin.z;
		_31 += translation.x;    _32 += translation.y;    _33 += translation.z;
#endif
	}
	//-----------------------------------------------------------------------------------
	//! @brief カメラの位置、上方向、およびカメラの向きを使用して左手座標系のビュー行列を作成します。
	//! @param [in]  rEye  カメラの位置。 
	//! @param [in]  rEyeDirection   カメラの向き。
	//! @param [in]  rUp   カメラの向きまで、一般的に<は0.0f、1.0fの、は0.0f>。
	//-----------------------------------------------------------------------------------
	inline void MakeCameraLookToLH(
		const gt2Vector3& rEye,
		const gt2Vector3& rEyeDirection,
		const gt2Vector3& rUp = gt2Vector3(0, 1, 0))
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		DirectX::XMVECTOR a, b, c;
		a = rEye.GetXMVECTOR();
		b = rEyeDirection.GetXMVECTOR();
		c = rUp.GetXMVECTOR();
		*this = DirectX::XMMatrixLookToLH(a, b, c);
#else
		//zaxis = normal(rEyeDirection)
		//xaxis = normal(cross(Up, zaxis))
		//yaxis = cross(zaxis, xaxis)

		// xaxis.x           yaxis.x           zaxis.x          0
		// xaxis.y           yaxis.y           zaxis.y          0
		// xaxis.z           yaxis.z           zaxis.z          0
		//-dot(xaxis, eye)  -dot(yaxis, eye)  -dot(zaxis, eye)  1

		gt2Vector3 zaxis = rEyeDirection;
		zaxis.Normalize();

		gt2Vector3 xaxis;
		xaxis = rUp.Cross(zaxis);
		xaxis.Normalize();

		gt2Vector3 yaxis;
		yaxis = zaxis.Cross(xaxis);

		_11 = xaxis.x;
		_12 = yaxis.x;
		_13 = zaxis.x;
		_14 = 0;

		_21 = xaxis.y;
		_22 = yaxis.y;
		_23 = zaxis.y;
		_24 = 0;

		_31 = xaxis.z;
		_32 = yaxis.z;
		_33 = zaxis.z;
		_34 = 0;

		_41 = -xaxis.Dot(rEye);
		_42 = -yaxis.Dot(rEye);
		_43 = -zaxis.Dot(rEye);
		_44 = 1.0f;
#endif
	}
	//-----------------------------------------------------------------------------------
	//! @brief カメラの位置、上方向、およびカメラの向きを使用して右手座標系のビュー行列を作成します。
	//! @param [in]  rEye  カメラの位置。 
	//! @param [in]  rEyeDirection   カメラの向き。
	//! @param [in]  rUp   カメラの向きまで、一般的に<は0.0f、1.0fの、は0.0f>。
	//! @return  なし
	//-----------------------------------------------------------------------------------
	inline void MakeCameraLookToRH(
		const gt2Vector3& rEye,
		const gt2Vector3& rEyeDirection,
		const gt2Vector3& rUp = gt2Vector3(0, 1, 0))
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		DirectX::XMVECTOR a, b, c;
		a = rEye.GetXMVECTOR();
		b = rEyeDirection.GetXMVECTOR();
		c = rUp.GetXMVECTOR();
		*this = DirectX::XMMatrixLookToRH(a, b, c);
#else
		this->MakeCameraLookToLH(rEye, rEyeDirection*-1, rUp);
#endif
	}

	//-----------------------------------------------------------------------------------
	//! @brief 左手座標系ビュー行列を作成する。
	//! @param [in]  rEye  カメラの位置。 
	//! @param [in]  rAt   焦点の位置。 
	//! @param [in]  rUp   カメラの向きまで、一般的に<は0.0f、1.0fの、は0.0f>。
	//-----------------------------------------------------------------------------------
	inline void MakeCameraLookAtLH(
		const gt2Vector3& rEye,
		const gt2Vector3& rAt,
		const gt2Vector3& rUp = gt2Vector3(0, 1, 0))
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		DirectX::XMVECTOR a, b, c;
		a = rEye.GetXMVECTOR();
		b = rAt.GetXMVECTOR();
		c = rUp.GetXMVECTOR();
		*this = DirectX::XMMatrixLookAtLH(a, b, c);
#else
		this->MakeCameraLookToLH(rEye, rAt - rEye, rUp);
#endif
	}
	//-----------------------------------------------------------------------------------
	//! @brief 右手座標系ビュー行列を作成する。
	//! @param [in]  rEye  カメラの位置。 
	//! @param [in]  rAt   焦点の位置。 
	//! @param [in]  rUp   カメラの向きまで、一般的に<は0.0f、1.0fの、は0.0f>。
	//! @return  なし
	//-----------------------------------------------------------------------------------
	inline void MakeCameraLookAtRH(
		const gt2Vector3& rEye,
		const gt2Vector3& rAt,
		const gt2Vector3& rUp = gt2Vector3(0, 1, 0))
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		DirectX::XMVECTOR a, b, c;
		a = rEye.GetXMVECTOR();
		b = rAt.GetXMVECTOR();
		c = rUp.GetXMVECTOR();
		*this = DirectX::XMMatrixLookAtRH(a, b, c);
#else
		this->MakeCameraLookToRH(rEye, rAt - rEye, rUp);
#endif
	}

	//-----------------------------------------------------------------------------------
	//! @brief 任意の法線ベクトルを中心に回転する行列を作成します。
	//! @param [in]  rV     回転軸を記述する法線ベクトル。
	//! @param [in]  fAngle 回転の角度 (ラジアン単位)。@n
	//!                     角度は、回転軸を中心にして原点方向を向いた時計回りで定義したものです
	//! @return  なし
	//-----------------------------------------------------------------------------------
	inline void MakeRotationNormal(const gt2Vector3& rV, float fAngle)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixRotationNormal(rV.GetXMVECTOR(), fAngle();
#else
		gt2Vector3 vTemp = rV;
		float fSina, fCosa, fOmca;

		fSina = (float)sin(fAngle);
		fCosa = (float)cos(fAngle);
		fOmca = 1.0f - fCosa;
		//vTemp.Normalize();

		this->MakeIdentity();

		_11 = fOmca * vTemp.x * vTemp.x + fCosa;
		_21 = fOmca * vTemp.x * vTemp.y - fSina * vTemp.z;
		_31 = fOmca * vTemp.x * vTemp.z + fSina * vTemp.y;
		_12 = fOmca * vTemp.y * vTemp.x + fSina * vTemp.z;
		_22 = fOmca * vTemp.y * vTemp.y + fCosa;
		_32 = fOmca * vTemp.y * vTemp.z - fSina * vTemp.x;
		_13 = fOmca * vTemp.z * vTemp.x - fSina * vTemp.y;
		_23 = fOmca * vTemp.z * vTemp.y + fSina * vTemp.x;
		_33 = fOmca * vTemp.z * vTemp.z + fCosa;
#endif
	}
	//-----------------------------------------------------------------------------------
	//! @brief 与えられた平面をベクトルを反映するように設計された変換行列を作成します。
	//! @param [in]  rP     反射平面
	//! @return  なし
	//-----------------------------------------------------------------------------------
	inline void MakeReflect(const gt2Plane3& rP)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixReflect(rP.GetXMVECTOR());
#else
		gt2Plane3 pl = rP;
		pl.Normalize();
		gt2Vector3 vS = pl.vNormal * -2.0f;
		_11 = (pl.a * vS.x) + 1; _12 = pl.a * vS.y;      _13 = pl.a * vS.z;      _14 = 0.0f;
		_21 = pl.b * vS.x;      _22 = (pl.b * vS.y) + 1; _23 = pl.b * vS.z;      _24 = 0.0f;
		_31 = pl.c * vS.x;      _32 = pl.c * vS.y;      _33 = (pl.c * vS.z) + 1; _34 = 0.0f;
		_41 = pl.d * vS.x;      _42 = pl.d * vS.y;      _43 = pl.d * vS.z;      _44 = 1.0f;
#endif
	}

	//-----------------------------------------------------------------------------------
	//! @brief 任意の軸を回転軸にして回転する行列を作成する。
	//! @param [in]  rV     回転軸を記述するベクトル
	//! @param [in]  fAngle 回転の角度 (ラジアン単位)。角度は、回転軸を基準とし、原点から時計回りの方向で指定します。
	//! @return  なし
	//-----------------------------------------------------------------------------------
	inline void MakeRotationAxis(const gt2Vector3& rV, float fAngle)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixRotationAxis(rV.GetXMVECTOR(), fAngle();
#else
		gt2Vector3 vTemp = rV;
		float fSina, fCosa, fOmca;

		fSina = (float)sin(fAngle);
		fCosa = (float)cos(fAngle);
		fOmca = 1.0f - fCosa;
		vTemp.Normalize();

		this->MakeIdentity();

		_11 = fOmca * vTemp.x * vTemp.x + fCosa;
		_21 = fOmca * vTemp.x * vTemp.y - fSina * vTemp.z;
		_31 = fOmca * vTemp.x * vTemp.z + fSina * vTemp.y;
		_12 = fOmca * vTemp.y * vTemp.x + fSina * vTemp.z;
		_22 = fOmca * vTemp.y * vTemp.y + fCosa;
		_32 = fOmca * vTemp.y * vTemp.z - fSina * vTemp.x;
		_13 = fOmca * vTemp.z * vTemp.x - fSina * vTemp.y;
		_23 = fOmca * vTemp.z * vTemp.y + fSina * vTemp.x;
		_33 = fOmca * vTemp.z * vTemp.z + fCosa;
#endif
	}


	//-----------------------------------------------------------------------------------
	//! @brief クォータニオンから回転行列を作成します。
	//! @param [in]  rQ       クォータニオン
	//! @param [in]  rvCenter アンカー位置
	//! @return  なし
	//-----------------------------------------------------------------------------------
	inline void MakeRotationQuaternion(const gt2Quaternion& rQ, const gt2Vector3& rvCenter)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixRotationQuaternion(rQ.GetXMVECTOR());

		float a1, a2, a3;
		a1 = rvCenter.x;
		a2 = rvCenter.y;
		a3 = rvCenter.z;

		_14 = a1 - a1 * _11 - a2 * _12 - a3 * _13;
		_24 = a2 - a1 * _21 - a2 * _22 - a3 * _23;
		_34 = a3 - a1 * _31 - a2 * _32 - a3 * _33;
#else
		float sqw = rQ.w*rQ.w;
		float sqx = rQ.x*rQ.x;
		float sqy = rQ.y*rQ.y;
		float sqz = rQ.z*rQ.z;
		_11 = sqx - sqy - sqz + sqw; // since sqw + sqx + sqy + sqz =1
		_22 = -sqx + sqy - sqz + sqw;
		_33 = -sqx - sqy + sqz + sqw;

		float tmp1 = rQ.x*rQ.y;
		float tmp2 = rQ.z*rQ.w;
		_12 = 2.0f * (tmp1 + tmp2);
		_21 = 2.0f * (tmp1 - tmp2);

		tmp1 = rQ.x*rQ.z;
		tmp2 = rQ.y*rQ.w;
		_13 = 2.0f * (tmp1 - tmp2);
		_31 = 2.0f * (tmp1 + tmp2);

		tmp1 = rQ.y*rQ.z;
		tmp2 = rQ.x*rQ.w;
		_23 = 2.0f * (tmp1 + tmp2);
		_32 = 2.0f * (tmp1 - tmp2);

		float a1, a2, a3;
		a1 = rvCenter.x;
		a2 = rvCenter.y;
		a3 = rvCenter.z;

		_14 = a1 - a1 * _11 - a2 * _12 - a3 * _13;
		_24 = a2 - a1 * _21 - a2 * _22 - a3 * _23;
		_34 = a3 - a1 * _31 - a2 * _32 - a3 * _33;
		_41 = _42 = _43 = 0.0f;
		_44 = 1.0f;
#endif
	}
	//-----------------------------------------------------------------------------------
	//! @brief クォータニオンから回転行列を作成します。
	//! @param [in]  rQ クォータニオン
	//! @return  なし
	//-----------------------------------------------------------------------------------
	inline void MakeRotationQuaternion(const gt2Quaternion& rQ)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixRotationQuaternion(rQ.GetXMVECTOR());
#else
		_11 = 1.0f - (rQ.y * rQ.y + rQ.z * rQ.z) * 2.0f;
		_12 = 2.0f * (rQ.x * rQ.y + rQ.z * rQ.w);
		_13 = 2.0f * (rQ.x * rQ.z - rQ.y * rQ.w);
		_21 = 2.0f * (rQ.x * rQ.y - rQ.z * rQ.w);
		_22 = 1.0f - (rQ.x * rQ.x + rQ.z * rQ.z) * 2.0f;
		_23 = 2.0f * (rQ.y * rQ.z + rQ.x * rQ.w);
		_31 = 2.0f * (rQ.x * rQ.z + rQ.y * rQ.w);
		_32 = 2.0f * (rQ.y * rQ.z - rQ.x * rQ.w);
		_33 = 1.0f - (rQ.x * rQ.x + rQ.y * rQ.y) * 2.0f;

		//float sqw = rQ.w*rQ.w;
		//float sqx = rQ.x*rQ.x;
		//float sqy = rQ.y*rQ.y;
		//float sqz = rQ.z*rQ.z;
		//   // invs (逆の平方長さ) クォータニオンがまだ正規化されない場合、単に要求されます。
		//float invs = 1.0f / (sqx + sqy + sqz + sqw);
		//_11 = ( sqx - sqy - sqz + sqw)*invs ; // since sqw + sqx + sqy + sqz =1/invs*invs
		//_22 = (-sqx + sqy - sqz + sqw)*invs ;
		//_33 = (-sqx - sqy + sqz + sqw)*invs ;
		//float tmp1 = rQ.x*rQ.y;
		//float tmp2 = rQ.z*rQ.w;
		//_12 = 2.0f * (tmp1 + tmp2)*invs ;
		//_21 = 2.0f * (tmp1 - tmp2)*invs ;
		//tmp1 = rQ.x*rQ.z;
		//tmp2 = rQ.y*rQ.w;
		//_13 = 2.0f * (tmp1 - tmp2)*invs ;
		//_31 = 2.0f * (tmp1 + tmp2)*invs ;
		//tmp1 = rQ.y*rQ.z;
		//tmp2 = rQ.x*rQ.w;
		//_23 = 2.0f * (tmp1 + tmp2)*invs ;
		//_32 = 2.0f * (tmp1 - tmp2)*invs ;

		_41 = _42 = _43 = 0.0f;
		_44 = 1.0f;
#endif
	}


	//-----------------------------------------------------------------------------------
	//! @brief x 軸を回転軸にして回転する行列を作成する。
	//! @param [in]  fAngle 回転の角度 (ラジアン単位)。@n
	//!                     角度は、回転軸を中心にして原点方向を向いた時計回りで定義したものです
	//! @return  なし
	//-----------------------------------------------------------------------------------
	inline void MakeRotationX(float fAngle)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixRotationX(fAngle);
#else
		float fCosa = cosf(fAngle);
		float fSina = sinf(fAngle);

		this->MakeIdentity();

		_22 = fCosa; _23 = fSina;
		_32 = -fSina; _33 = fCosa;
#endif
	}

	//-----------------------------------------------------------------------------------
	//! @brief XYZ軸回転の設定
	//! @param [in]  rvRadian radian 各軸におけるラジアン単位での回転角度
	//! @return  なし
	//-----------------------------------------------------------------------------------
	inline void MakeRotationXYZ(const gt2Vector3& rvRadian)
	{
		this->MakeIdentity();
		float sinX = sinf(rvRadian.x);
		float cosX = cosf(rvRadian.x);
		float sinY = sinf(rvRadian.y);
		float cosY = cosf(rvRadian.y);
		float sinZ = sinf(rvRadian.z);
		float cosZ = cosf(rvRadian.z);
		_11 = cosY * cosZ;
		_12 = sinX * sinY * cosZ - cosX * sinZ;
		_13 = cosX * sinY * cosZ + sinX * sinZ;

		_21 = cosY * sinZ;
		_22 = sinX * sinY * sinZ + cosX * cosZ;
		_23 = cosX * sinY * sinZ - sinX * cosZ;

		_31 = -sinY;
		_32 = sinX * cosY;
		_33 = cosX * cosY;
	}

	//-----------------------------------------------------------------------------------
	//! @brief XZY軸回転の設定
	//! @param [in]  rvRadian radian 各軸におけるラジアン単位での回転角度
	//! @return  なし
	//-----------------------------------------------------------------------------------
	inline void MakeRotationXZY(const gt2Vector3& rvRadian)
	{
		this->MakeIdentity();

		float sinX = sinf(rvRadian.x);
		float cosX = cosf(rvRadian.x);
		float sinY = sinf(rvRadian.y);
		float cosY = cosf(rvRadian.y);
		float sinZ = sinf(rvRadian.z);
		float cosZ = cosf(rvRadian.z);

		_11 = cosY * cosZ;
		_12 = -sinZ;
		_13 = cosZ * sinY;

		_21 = sinX * sinY + cosX * cosY * sinZ;
		_22 = cosX * cosZ;
		_23 = -cosY * sinX + cosX * sinY * sinZ;

		_31 = -cosX * sinY + cosY * sinX * sinZ;
		_32 = cosZ * sinX;
		_33 = cosX * cosY + sinX * sinY * sinZ;
	}

	//-----------------------------------------------------------------------------------
	//! @brief y 軸を回転軸にして回転する行列を作成する。
	//! @param [in]  fAngle 回転の角度 (ラジアン単位)。@n
	//!                     角度は、回転軸を中心にして原点方向を向いた時計回りで定義したものです
	//! @return  なし
	//-----------------------------------------------------------------------------------
	inline void MakeRotationY(float fAngle)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixRotationY(fAngle);
#else
		float fCosa;
		float fSina;
		fCosa = (float)cos(fAngle);
		fSina = (float)sin(fAngle);

		this->MakeIdentity();

		_11 = fCosa; _13 = -fSina;
		_31 = fSina; _33 = fCosa;
#endif
	}

	//-----------------------------------------------------------------------------------
	//! @brief YXZ軸回転の設定
	//! @param [in]  rvRadian 各軸におけるラジアン単位での回転角度
	//! @return  なし
	//-----------------------------------------------------------------------------------
	inline void MakeRotationYXZ(const gt2Vector3& rvRadian)
	{
		this->MakeIdentity();

		float sinX = sinf(rvRadian.x);
		float cosX = cosf(rvRadian.x);
		float sinY = sinf(rvRadian.y);
		float cosY = cosf(rvRadian.y);
		float sinZ = sinf(rvRadian.z);
		float cosZ = cosf(rvRadian.z);

		_11 = cosY * cosZ + sinX * sinY * sinZ;
		_12 = cosZ * sinX * sinY - cosY * sinZ;
		_13 = cosX * sinY;

		_21 = cosX * sinZ;
		_22 = cosX * cosZ;
		_23 = -sinX;

		_31 = -cosZ * sinY + cosY * sinX * sinZ;
		_32 = cosY * cosZ * sinX + sinY * sinZ;
		_33 = cosX * cosY;
	}

	//-----------------------------------------------------------------------------------
	//! @brief YZX軸回転の設定
	//! @param [in]  rvRadian 各軸におけるラジアン単位での回転角度
	//! @return  なし
	//-----------------------------------------------------------------------------------
	inline void MakeRotationYZX(const gt2Vector3& rvRadian)
	{
		this->MakeIdentity();

		float sinX = sinf(rvRadian.x);
		float cosX = cosf(rvRadian.x);
		float sinY = sinf(rvRadian.y);
		float cosY = cosf(rvRadian.y);
		float sinZ = sinf(rvRadian.z);
		float cosZ = cosf(rvRadian.z);


		_11 = cosY * cosZ;
		_12 = sinX * sinY - cosX * cosY * sinZ;
		_13 = cosX * sinY + cosY * sinX * sinZ;

		_21 = sinZ;
		_22 = cosX * cosZ;
		_23 = -cosZ * sinX;

		_31 = -cosZ * sinY;
		_32 = cosY * sinX + cosX * sinY * sinZ;
		_33 = cosX * cosY - sinX * sinY * sinZ;
	}
	//-----------------------------------------------------------------------------------
	//! @brief z 軸を回転軸にして回転する行列を作成する。
	//! @param [in]  fAngle 回転の角度 (ラジアン単位)。@n
	//!                     角度は、回転軸を中心にして原点方向を向いた時計回りで定義したものです
	//! @return  なし
	//-----------------------------------------------------------------------------------
	inline void MakeRotationZ(float fAngle)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixRotationZ(fAngle);
#else
		float fCosa;
		float fSina;
		fCosa = (float)cos(fAngle);
		fSina = (float)sin(fAngle);

		this->MakeIdentity();

		_11 = fCosa; _12 = fSina;
		_21 = -fSina; _22 = fCosa;
#endif
	}

	//-----------------------------------------------------------------------------------
	//! @brief ZXY軸回転の設定
	//! @param [in]  rvRadian 各軸におけるラジアン単位での回転角度
	//! @return  なし
	//-----------------------------------------------------------------------------------
	inline void MakeRotationZXY(const gt2Vector3& rvRadian)
	{
		this->MakeIdentity();

		float sinX = sinf(rvRadian.x);
		float cosX = cosf(rvRadian.x);
		float sinY = sinf(rvRadian.y);
		float cosY = cosf(rvRadian.y);
		float sinZ = sinf(rvRadian.z);
		float cosZ = cosf(rvRadian.z);

		_11 = cosY * cosZ - sinX * sinY * sinZ;
		_12 = -cosX * sinZ;
		_13 = cosZ * sinY + cosY * sinX * sinZ;

		_21 = cosZ * sinX * sinY + cosY * sinZ;
		_22 = cosX * cosZ;
		_23 = -cosY * cosZ * sinX + sinY * sinZ;

		_31 = -cosX * sinY;
		_32 = sinX;
		_33 = cosX * cosY;
	}

	//-----------------------------------------------------------------------------------
	//! @brief ZYX軸回転の設定
	//! @param [in]  rvRadian 各軸におけるラジアン単位での回転角度
	//! @return  なし
	//-----------------------------------------------------------------------------------
	inline void MakeRotationZYX(const gt2Vector3& rvRadian)
	{
		this->MakeIdentity();

		float sinX = sinf(rvRadian.x);
		float cosX = cosf(rvRadian.x);
		float sinY = sinf(rvRadian.y);
		float cosY = cosf(rvRadian.y);
		float sinZ = sinf(rvRadian.z);
		float cosZ = cosf(rvRadian.z);

		_11 = cosY * cosZ;
		_12 = cosX * cosZ + sinX * sinY * sinZ;
		_13 = cosX * cosZ * sinY + sinX * sinZ;

		_21 = cosY * sinZ;
		_22 = cosX * cosZ;
		_23 = -cosZ * sinX + cosX * sinY * sinZ;

		_31 = -sinY;
		_32 = cosY * sinX;
		_33 = cosX * cosY;
	}

	//-----------------------------------------------------------------------------------
	//! @brief ヨー、ピッチ、ロールを指定して行列を作成する。
	//! @param [in]  yaw   y 軸を中心とするヨー (ラジアン単位)。
	//! @param [in]  pitch x 軸を中心とするヨー (ラジアン単位)。
	//! @param [in]  roll  z 軸を中心とするヨー (ラジアン単位)。
	//! @return  なし
	//-----------------------------------------------------------------------------------
	inline void MakeRotationYawPitchRoll(float yaw, float pitch, float roll)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
#else
		float fCY = cosf(yaw);
		float fSY = sinf(yaw);
		float fCP = cosf(pitch);
		float fSP = sinf(pitch);
		float fCR = cosf(roll);
		float fSR = sinf(roll);
		_11 = fCY *  fCR;
		_12 = -fSP * -fSY *  fCR + fCP * fSR;
		_13 = fCP * -fSY *  fCR + fSP * fSR;

		_21 = fCY * -fSR;
		_22 = -fSP * -fSY * -fSR + fCP * fCR;
		_23 = fCP * -fSY * -fSR + fSP * fCR;

		_31 = fSY;
		_32 = -fSP *  fCY;
		_33 = fCP *  fCY;
#endif
	}
	//-----------------------------------------------------------------------------------
	//! @brief ヨー、ピッチ、ロールを指定して行列を作成する。
	//! @param [in]  v   x:Pitch, y:Yaw, z:Roll
	//! @return  なし
	//-----------------------------------------------------------------------------------
	inline void MakeRollPitchYawFromVector(const gt2Vector3 &v)
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		*this = DirectX::XMMatrixRotationRollPitchYawFromVector(v.GetXMVECTOR());
#else
		this->MakeRotationYawPitchRoll(v.y, v.x, v.z);
#endif
	}

	//-----------------------------------------------------------------------------------
	//! @brief 2 つの行列の積を計算し、結果を返す。
	//! @param [in]  rM   対象行列
	//! @return  演算結果を返す
	//-----------------------------------------------------------------------------------
	inline gt2Matrix4x4 Multiply(const gt2Matrix4x4& rM) const
	{
		return *this * rM;
	}

	//-----------------------------------------------------------------------------------
	//! @brief 2 つの行列の積を計算し、結果を返す。rM1×rM2
	//! @param [in]  rM1   対象行列 1
	//! @param [in]  rM2   対象行列 2
	//! @return  演算結果を返す
	//-----------------------------------------------------------------------------------
	inline static gt2Matrix4x4 Multiply(const gt2Matrix4x4& rM1, const gt2Matrix4x4& rM2)
	{
		gt2Matrix4x4 out;
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		out = DirectX::XMMatrixMultiply((DirectX::XMMATRIX)rM1, (DirectX::XMMATRIX)rM2();
#else
		out._11 = rM1._11*rM2._11 + rM1._12*rM2._21 + rM1._13*rM2._31 + rM1._14*rM2._41;
		out._12 = rM1._11*rM2._12 + rM1._12*rM2._22 + rM1._13*rM2._32 + rM1._14*rM2._42;
		out._13 = rM1._11*rM2._13 + rM1._12*rM2._23 + rM1._13*rM2._33 + rM1._14*rM2._43;
		out._14 = rM1._11*rM2._14 + rM1._12*rM2._24 + rM1._13*rM2._34 + rM1._14*rM2._44;

		out._21 = rM1._21*rM2._11 + rM1._22*rM2._21 + rM1._23*rM2._31 + rM1._24*rM2._41;
		out._22 = rM1._21*rM2._12 + rM1._22*rM2._22 + rM1._23*rM2._32 + rM1._24*rM2._42;
		out._23 = rM1._21*rM2._13 + rM1._22*rM2._23 + rM1._23*rM2._33 + rM1._24*rM2._43;
		out._24 = rM1._21*rM2._14 + rM1._22*rM2._24 + rM1._23*rM2._34 + rM1._24*rM2._44;

		out._31 = rM1._31*rM2._11 + rM1._32*rM2._21 + rM1._33*rM2._31 + rM1._34*rM2._41;
		out._32 = rM1._31*rM2._12 + rM1._32*rM2._22 + rM1._33*rM2._32 + rM1._34*rM2._42;
		out._33 = rM1._31*rM2._13 + rM1._32*rM2._23 + rM1._33*rM2._33 + rM1._34*rM2._43;
		out._34 = rM1._31*rM2._14 + rM1._32*rM2._24 + rM1._33*rM2._34 + rM1._34*rM2._44;

		out._41 = rM1._41*rM2._11 + rM1._42*rM2._21 + rM1._43*rM2._31 + rM1._44*rM2._41;
		out._42 = rM1._41*rM2._12 + rM1._42*rM2._22 + rM1._43*rM2._32 + rM1._44*rM2._42;
		out._43 = rM1._41*rM2._13 + rM1._42*rM2._23 + rM1._43*rM2._33 + rM1._44*rM2._43;
		out._44 = rM1._41*rM2._14 + rM1._42*rM2._24 + rM1._43*rM2._34 + rM1._44*rM2._44;
#endif
		return out;
	}

	//-----------------------------------------------------------------------------------
	//! @brief 2 つの行列の積の転置行列を計算します。
	//! @param [in]  rM1   対象行列 1
	//! @param [in]  rM2   対象行列 2
	//! @return  M1 と M2 の積の転置行列を返します。
	//-----------------------------------------------------------------------------------
	inline static gt2Matrix4x4 MultiplyTranspose(const gt2Matrix4x4& rM1, const gt2Matrix4x4& rM2)
	{
		gt2Matrix4x4 out;
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		out = DirectX::XMMatrixMultiplyTranspose((DirectX::XMMATRIX)rM1, (DirectX::XMMATRIX)rM2();
#else
		out = Multiply(rM1, rM2);
		out = out.GetTranspose();
#endif
		return out;
	}



	//-----------------------------------------------------------------------------------
	//! @brief 行列の転置行列を返す。
	//! @return  行列の転置行列を返す。
	//-----------------------------------------------------------------------------------
	inline gt2Matrix4x4 GetTranspose() const
	{
		gt2Matrix4x4 out;
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		out = DirectX::XMMatrixTranspose((DirectX::XMMATRIX)*this);
#else
		for (int c = 0; c<4; ++c)
			for (int r = 0; r<4; ++r)
				out.m[r][c] = m[c][r];
#endif
		return out;
	}


	//-----------------------------------------------------------------------------------
	//! @brief 回転行列からクォータニオンを作成する。
	//! @return  クォータニオンをを返す
	//-----------------------------------------------------------------------------------
	inline gt2Quaternion GetRotationQuaternion() const
	{
		gt2Quaternion out;
		float fS, fD;
		float fTrace = _11 + _22 + _33 + 1.0f;
		if (fTrace > 0.0f) {
			fS = 0.5f / sqrtf(fTrace);
			out.w = 0.25f / fS;
			out.x = (_32 - _23) * fS;
			out.y = (_13 - _31) * fS;
			out.z = (_21 - _12) * fS;
		}
		else {
			if (_11 > _22 && _11 > _33) {
				fS = 2.0f * sqrtf(1.0f + _11 - _22 - _33);
				fD = 1.0f / fS;
				out.w = (_23 - _32) * fD;
				out.x = 0.25f * fS;
				out.y = (_12 + _21) * fD;
				out.z = (_13 + _31) * fD;
			}
			else if (_22 > _33) {
				fS = 2.0f * sqrtf(1.0f + _22 - _11 - _33);
				fD = 1.0f / fS;
				out.w = (_13 - _31) * fD;
				out.x = (_12 + _21) * fD;
				out.y = 0.25f * fS;
				out.z = (_23 + _32) * fD;
			}
			else {
				fS = 2.0f * sqrtf(1.0f + _33 - _11 - _22);
				fD = 1.0f / fS;
				out.w = (_12 - _21) * fD;
				out.x = (_13 + _31) * fD;
				out.y = (_23 + _32) * fD;
				out.z = 0.25f * fS;
			}
		}

		return out;
	}

	//-----------------------------------------------------------------------------------
	//! @brief 標準の 3D 変換行列を、スカラー成分、回転成分、平行移動成分に分割する。
	//! @param [out] pOutScale       x、y、z 軸に沿って適用されるスケーリング係数を含む出力 gt2Vector3 へのポインタ。
	//! @param [out] pOutRotation    回転を記述する gt2Quaternion 構造体へのポインタ。
	//! @param [out] pOutPosition 平行移動を記述する MCXVECTOR3 ベクトルへのポインタ。
	//! @return  なし
	//-----------------------------------------------------------------------------------
	inline bool GetMatrixDecompose(
		gt2Vector3 *pOutScale,
		gt2Quaternion *pOutRotation,
		gt2Vector3 *pOutPosition
	) const
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		DirectX::XMVECTOR a, b, c;
		DirectX::XMMatrixDecompose(&a, &b, &c, (DirectX::FXMMATRIX)*this);
		*pOutScale = a;
		*pOutRotation = b;
		*pOutPosition = c;
#else
		//gt2Vector3 vCols1(_11, _12, _13);
		//gt2Vector3 vCols2(_21, _22, _23);
		//gt2Vector3 vCols3(_31, _32, _33);

		//pOutScale->x = vCols1.Length();
		//pOutScale->y = vCols2.Length();
		//pOutScale->z = vCols3.Length();

		//pOutPosition->x = _41 / (pOutScale->x == 0 ? 1 : pOutScale->x);
		//pOutPosition->y = _42 / (pOutScale->y == 0 ? 1 : pOutScale->y);
		//pOutPosition->z = _43 / (pOutScale->z == 0 ? 1 : pOutScale->z);

		//*pOutRotation = this->GetRotationQuaternion();
		//----------------------------------------------------
		static const gt2Vector3 *pvCanonicalBasis[3] = {
			&g_VF3IdentityR0,
			&g_VF3IdentityR1,
			&g_VF3IdentityR2
		};

		assert(pOutScale != nullptr);
		assert(pOutRotation != nullptr);
		assert(pOutPosition != nullptr);

		// 位置の取得
		pOutPosition->x = _41;
		pOutPosition->y = _42;
		pOutPosition->z = _43;

		gt2Vector3 *ppvBasis[3];
		gt2Matrix4x4 matTemp;
		ppvBasis[0] = (gt2Vector3*)matTemp.m[0];
		ppvBasis[1] = (gt2Vector3*)matTemp.m[1];
		ppvBasis[2] = (gt2Vector3*)matTemp.m[2];

		memcpy(matTemp.m[0], m[0], sizeof(gt2Vector4));
		memcpy(matTemp.m[1], m[1], sizeof(gt2Vector4));
		memcpy(matTemp.m[2], m[2], sizeof(gt2Vector4));
		memcpy(matTemp.m[3], g_VF4IdentityR3.v, sizeof(gt2Vector4));

		float *pfScales = pOutScale->v;

		size_t a, b, c;
		pfScales[0] = ppvBasis[0]->Length();
		pfScales[1] = ppvBasis[1]->Length();
		pfScales[2] = ppvBasis[2]->Length();

		MC_3RANKDECOMPOSE(a, b, c, pfScales[0], pfScales[1], pfScales[2]);

		if (pfScales[a] < GT2_DECOMP_EPSILON)
		{
			ppvBasis[a][0] = pvCanonicalBasis[a][0];
		}
		ppvBasis[a]->Normalize();

		if (pfScales[b] < GT2_DECOMP_EPSILON)
		{
			size_t aa, bb, cc;
			float fAbsX, fAbsY, fAbsZ;

			fAbsX = fabsf(ppvBasis[a]->x);
			fAbsY = fabsf(ppvBasis[a]->y);
			fAbsZ = fabsf(ppvBasis[a]->z);

			MC_3RANKDECOMPOSE(aa, bb, cc, fAbsX, fAbsY, fAbsZ);
			*ppvBasis[b] = ppvBasis[a]->Cross(*pvCanonicalBasis[cc]);
		}
		ppvBasis[b]->Normalize();

		if (pfScales[c] < GT2_DECOMP_EPSILON)
		{
			*ppvBasis[c] = ppvBasis[a]->Cross(*pvCanonicalBasis[b]);
		}
		ppvBasis[c]->Normalize();

		float fDet = matTemp.GetDeterminant();

		// 座標系の利き手をチェックするためにクレイマーのルールを使用しています。
		if (fDet < 0.0f)
		{
			// スケールを否定し、x軸上の基底ベクトルを反転させて座標系を切り替える
			pfScales[a] = -pfScales[a];
			*ppvBasis[a] *= -1;

			fDet = -fDet;
		}

		fDet -= 1.0f;
		fDet *= fDet;

		if (GT2_DECOMP_EPSILON < fDet)
		{
			// 発生した非SRT行列
			return false;
		}

		// 行列からクォータニオンを生成
		*pOutRotation = matTemp.GetRotationQuaternion();
#endif
		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 行列の行列式を計算します。
	//! @return  行列式を返します
	//-----------------------------------------------------------------------------------
	inline float GetDeterminant()
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		auto ret = DirectX::XMMatrixDeterminant((DirectX::FXMMATRIX)*this);

		return ret.m128_f32[0];
#else
		return (_11 * _22 - _12 * _21) * (_33 * _44 - _34 * _43) -
			(_11 * _23 - _13 * _21) * (_32 * _44 - _34 * _42) +
			(_11 * _24 - _14 * _21) * (_32 * _43 - _33 * _42) +
			(_12 * _23 - _13 * _22) * (_31 * _44 - _34 * _41) -
			(_12 * _24 - _14 * _22) * (_31 * _43 - _33 * _41) +
			(_13 * _24 - _14 * _23) * (_31 * _42 - _32 * _41);
#endif
	}
	//-----------------------------------------------------------------------------------
	//! @brief 行列は単位行列であるかどうかをテストします。
	//! @return  単位行列の場合true
	//-----------------------------------------------------------------------------------
	inline bool IsIdentity()
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		return DirectX::XMMatrixIsIdentity((DirectX::FXMMATRIX)*this);
#else
		return
			_11 == 1 && _12 == 0 && _13 == 0 && _14 == 0 &&
			_21 == 0 && _22 == 1 && _23 == 0 && _24 == 0 &&
			_31 == 0 && _32 == 1 && _33 == 0 && _34 == 0 &&
			_41 == 0 && _42 == 1 && _43 == 0 && _44 == 0;
#endif
	}
	//-----------------------------------------------------------------------------------
	//! @brief 行列の要素のいずれかが正または負の無限大であるかどうかをテストします。
	//! @return  無限大の場合true
	//-----------------------------------------------------------------------------------
	inline bool IsInfinite()
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		return DirectX::XMMatrixIsInfinite((DirectX::FXMMATRIX)*this);
#else
		size_t i = 16;
		const uint32_t *pWork = (const uint32_t *)(m[0]);
		do {
			// 整数ユニットに値をフェッチ
			uint32_t uTest = pWork[0];
			// 記号を削除
			uTest &= 0x7FFFFFFFU;
			// INF is 0x7F800000
			if (uTest == 0x7F800000U) {
				break;      // INFが見つかりました
			}
			++pWork;        // 次のエントリー
		} while (--i);
		return (i != 0);      // i == 0 の場合何もマッチしない
#endif
	}
	//-----------------------------------------------------------------------------------
	//! @brief 行列の要素のいずれかがNaNかどうかをテストする。
	//! @return  NaNの場合true
	//-----------------------------------------------------------------------------------
	inline bool IsNaN()
	{
#if defined(MC_DIRECTX) && defined(MC_DIRECTX11)
		return DirectX::XMMatrixIsNaN((DirectX::FXMMATRIX)*this);
#else

		size_t i = 16;
		const uint32_t *pWork = (const uint32_t *)(m[0]);
		do {
			// 整数ユニットに値をフェッチ
			uint32_t uTest = pWork[0];
			// 記号を削除
			uTest &= 0x7FFFFFFFU;
			// NaN は 0x7FFFFFFF インクルーシブを介して 0x7F800001
			uTest -= 0x7F800001U;
			if (uTest<0x007FFFFFU) {
				break;      // NaNが見つかりました
			}
			++pWork;        // 次のエントリー
		} while (--i);
		return (i != 0);      // i == 0 の場合何もマッチしない
#endif
	}

	//-----------------------------------------------------------------------------------
	//! @brief 標準の 3D 変換行列を、スカラー成分、回転成分、平行移動成分に分割する。
	//! @param [out] rOutScale       x、y、z 軸に沿って適用されるスケーリング係数を含む出力 gt2Vector3 へのポインタ。
	//! @param [out] rOutRotation    回転を記述する gt2Quaternion 構造体へのポインタ。
	//! @param [out] rOutTranslation 平行移動を記述する MCXVECTOR3 ベクトルへのポインタ。
	//! @return  なし
	//-----------------------------------------------------------------------------------
	inline void GetMatrixDecompose(
		gt2Vector3& rOutScale,
		gt2Quaternion& rpOutRotation,
		gt2Vector3& rOutPosition
	) const
	{
		this->GetMatrixDecompose(&rOutScale, &rpOutRotation, &rOutPosition);
	}


	//-----------------------------------------------------------------------------------
	//! @brief カメラの向きのベクトルを取得する
	//! @return  カメラの向きのベクトルを取得する
	//-----------------------------------------------------------------------------------
	inline gt2Vector3 GetLookAt() const
	{
		gt2Vector3 ret = gt2Vector3(_13, _23, _33);
		ret.Normalize();
		return ret;
	}

	//-----------------------------------------------------------------------------------
	//! @brief 指定された行列によりベクトル (x, y, z) を座標変換する。
	//! @param [in]  rV3    3要素ベクトル
	//! @return  演算結果を返す
	//-----------------------------------------------------------------------------------
	inline gt2Vector4 Vec3Transform(const gt2Vector3& rV3) const
	{
		gt2Vector4 out;
		out.x = rV3.x * (_11)+rV3.y * (_21)+rV3.z * (_31)+(_41);
		out.y = rV3.x * (_12)+rV3.y * (_22)+rV3.z * (_32)+(_42);
		out.z = rV3.x * (_13)+rV3.y * (_23)+rV3.z * (_33)+(_43);
		out.w = rV3.x * (_14)+rV3.y * (_24)+rV3.z * (_34)+(_44);
		return out;
	}

	//-----------------------------------------------------------------------------------
	//! @brief 指定された行列により 4D ベクトルを座標変換する。
	//! @param [in]  rV4    4要素ベクトル
	//! @return  演算結果を返す
	//-----------------------------------------------------------------------------------
	inline gt2Vector4 Vec4Transform(const gt2Vector4& rV4) const
	{
		gt2Vector4 out;
		out.x = rV4.x * (_11)+rV4.y * (_21)+rV4.z * (_31)+rV4.w * (_41);
		out.y = rV4.x * (_12)+rV4.y * (_22)+rV4.z * (_32)+rV4.w * (_42);
		out.z = rV4.x * (_13)+rV4.y * (_23)+rV4.z * (_33)+rV4.w * (_43);
		out.w = rV4.x * (_14)+rV4.y * (_24)+rV4.z * (_34)+rV4.w * (_44);
		return out;
	}

	//-----------------------------------------------------------------------------------
	//! @brief 注視点座標を作る
	//! @param [in]  rvHear    視点ベクトル
	//! @param [in]  rvLookAt  視点先ベクトル
	//! @return  なし
	//-----------------------------------------------------------------------------------
	inline void MakeLookAt(const gt2Vector3& rvHear, const gt2Vector3& rvLookAt)
	{
		gt2Matrix4x4  matTemp, matTemp2, matRotX, matRotY;
		gt2Vector3  vDist;
		float     mag_xz, mag_xyz;
		float     cos_x, sin_x, cos_y, sin_y;

		vDist = rvLookAt - rvHear;
		mag_xyz = vDist.Length();
		vDist.y = 0.0f;
		mag_xz = vDist.Length();
		vDist = rvLookAt - rvHear;

		if (1e-6f > mag_xyz) mag_xyz = 0.0001f;
		if (1e-6f > mag_xz)  mag_xz = 0.0001f;

		cos_y = vDist.z / mag_xz;
		sin_y = vDist.x / mag_xz;
		cos_x = mag_xz / mag_xyz;
		sin_x = -vDist.y / mag_xyz;

		// MAKE MATRIX
		matTemp.SetTranslation(rvHear);

		matRotX.MakeIdentity();
		matRotX._22 = cos_x;
		matRotX._23 = sin_x;
		matRotX._32 = -sin_x;
		matRotX._33 = cos_x;

		matRotY.MakeIdentity();
		matRotY._11 = cos_y;
		matRotY._13 = -sin_y;
		matRotY._31 = sin_y;
		matRotY._33 = cos_y;

		matTemp2 = matRotX * matRotY;
		*this = matTemp2 * matTemp;
	}

	//-----------------------------------------------------------------------------------
	//! @brief ビルボードマトリックス作成。回転マトリックスは軸の任意のセットから作成@n
	//!        マトリックスの最初の3カラムにそれらの軸値を格納する。
	//! @param [in]  rRight    ベクトル
	//! @param [in]  rUp       アップベクトル
	//! @param [in]  rLook     視点ベクトル
	//! @param [in]  rPos      位置ベクトル
	//! @return  なし
	//-----------------------------------------------------------------------------------
	inline void MakeBillboardMatrix(const gt2Vector3& rRight, const gt2Vector3& rUp, const gt2Vector3& rLook, const gt2Vector3& rPos)
	{
		_11 = rRight.x;
		_12 = rRight.y;
		_13 = rRight.z;
		_14 = 0.0f;
		_21 = rUp.x;
		_22 = rUp.y;
		_23 = rUp.z;
		_24 = 0.0f;
		_31 = rLook.x;
		_32 = rLook.y;
		_33 = rLook.z;
		_34 = 0.0f;
		_41 = rPos.x;
		_42 = rPos.y;
		_43 = rPos.z;
		_44 = 1.0f;
	}
};


//======================================================================================
//! @brief 2×2 のマトリックス
//======================================================================================
struct gt2Matrix2x2 {
	union {
		struct {
			float _11, _12;
			float _21, _22;
		};
		float m[2][2];
		float mm[4];
	};

	//! @name コンストラクタ
	//@{
	inline gt2Matrix2x2()
	{
		this->MakeIdentity();
	}
	inline gt2Matrix2x2(const float * pF)
	{
		memcpy(this, pF, sizeof(gt2Matrix2x2));
	}
	inline gt2Matrix2x2(const gt2Matrix2x2& rM)
	{
		*this = rM;
	}
	inline gt2Matrix2x2(
		float f11, float f12,
		float f21, float f22
	) : _11(f11), _12(f12),
		_21(f21), _22(f22)
	{
	}
	//@}


	//gt2Matrix2x2& operator= (const b2Mat22& m22) { memcpy(this, &m22, sizeof(b2Mat22)); return *this; }

	//! @name  2 項演算子
	//@{
	inline gt2Matrix2x2
		operator * (const gt2Matrix2x2& tmp) const
	{
		gt2Matrix2x2 ret;
		ret._11 = _11*tmp._11 + _12*tmp._21;
		ret._12 = _11*tmp._12 + _12*tmp._22;

		ret._21 = _21*tmp._11 + _22*tmp._21;
		ret._22 = _21*tmp._12 + _22*tmp._22;


		return ret;
	}
	inline gt2Matrix2x2
		operator + (const gt2Matrix2x2& tmp) const
	{
		gt2Matrix2x2 ret;
		ret._11 = _11 + tmp._11;
		ret._12 = _12 + tmp._12;

		ret._21 = _21 + tmp._21;
		ret._22 = _22 + tmp._22;
		return ret;
	}
	inline gt2Matrix2x2
		operator - (const gt2Matrix2x2& tmp) const
	{
		gt2Matrix2x2 ret;
		ret._11 = _11 - tmp._11;
		ret._12 = _12 - tmp._12;

		ret._21 = _21 - tmp._21;
		ret._22 = _22 - tmp._22;
		return ret;
	}
	inline gt2Matrix2x2
		operator * (const float &tmp) const
	{
		gt2Matrix2x2 ret;
		ret._11 = _11*tmp;
		ret._12 = _12*tmp;

		ret._21 = _21*tmp;
		ret._22 = _22*tmp;

		return ret;
	}
	inline gt2Matrix2x2
		operator / (const float &tmp) const
	{
		gt2Matrix2x2 ret;
		float factor = 1.0f / tmp;

		ret._11 = _11*factor;
		ret._12 = _12*factor;

		ret._21 = _21*factor;
		ret._22 = _22*factor;
		return ret;
	}
	//@}

	//-----------------------------------------------------------------------------------
	//! @brief  行列の逆行列を計算する。
	//! @param [out]  pDeterminant 行列の行列式を含む float 値へのポインタ。@n
	//!                            行列式が不要の場合は、このパラメータに nullptr を設定する。
	//! @param [out]  pOut         演算結果である gt2Matrix4x4 構造体へのポインタ。
	//! @return 逆行列の計算が失敗した場合は、false を返す。
	//-----------------------------------------------------------------------------------
	inline bool GetInverse(float *pDeterminant, gt2Matrix2x2* pOut) const
	{
		float d;

		d = (_11 *_22) - (_21*_12);


		if (d == 0.0f)
			return false;

		d = 1.0f / d;


		pOut->_11 = d * _22;
		pOut->_12 = -d * _12;
		pOut->_21 = -d * _21;
		pOut->_22 = d * _11;


		if (pDeterminant != nullptr) *pDeterminant = d;

		return true;
	}

	//-----------------------------------------------------------------------------------
	//! @brief  4x4行列を2x2行列にクリップする
	//! @param [in]  rMX gt2Matrix4x4
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void ClipMCXMATRIX(const gt2Matrix4x4 &rMX) {
		m[0][0] = rMX._11; m[0][1] = rMX._12;
		m[1][0] = rMX._21; m[1][1] = rMX._22;
	}

	//-----------------------------------------------------------------------------------
	//! @brief  マトリックスと2要素のベクトルを掛ける
	//! @param [in]  rV 対象とするベクトル
	//! @return 演算結果を返す
	//-----------------------------------------------------------------------------------
	inline gt2Vector2 MultiplyD3DXVECTOR2(const gt2Vector2 &rV) const {
		gt2Vector2 out;
		int i;
		for (i = 0; i<2; ++i) {
			out.v[i] = (m[i][0] * rV.x) + (m[i][1] * rV.y);
		}
		return out;
	}

	//-----------------------------------------------------------------------------------
	//! @brief  対角成分がfA~fC で与えられ，他の成分が0である行列を返す．
	//! @param [in]  rIn gt2Vector2 構造体へのポインタへ位置情報を取得する。
	//! @param [in]  k  k 番目の対角上のリストの要素の値．
	//! @return 演算結果を返す
	//-----------------------------------------------------------------------------------
	inline void MakeDiagonal(const gt2Vector2 &rIn, int k)
	{
		if (k < -1 || k > 1) return;

		memset(this, 0, sizeof(gt2Matrix2x2));

		if (k < 0) {
			k = abs(k) * 2;
		}
		mm[k] = rIn.x;
		if ((k += 2) > 2)return;
		mm[k] = rIn.y;
	}

	//-----------------------------------------------------------------------------------
	//! @brief  単位行列を作成する。
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void MakeIdentity()
	{
		memset(mm, 0, sizeof(gt2Matrix2x2));
		_11 = _22 = 1.0f;
	}
};
#undef MY_XMMATRIX
#undef CAST_XMMATRIX


	
//======================================================================================
//! @brief 3×3 のマトリックス
//======================================================================================
struct gt2Matrix3x3
{
	union {
		struct {
			float _11, _12, _13;
			float _21, _22, _23;
			float _31, _32, _33;
		};
		float m[3][3];
		float mm[9];
	};

	//! @name コンストラクタ
	//@{
	gt2Matrix3x3()
	{
		this->MakeIdentity();
	}
	gt2Matrix3x3(const float * pF)
	{
		memcpy(this, pF, sizeof(gt2Matrix3x3));
	}
	gt2Matrix3x3(const gt2Matrix3x3& rM)
	{
		*this = rM;
	}
	gt2Matrix3x3(
		float f11, float f12, float f13,
		float f21, float f22, float f23,
		float f31, float f32, float f33
	) : _11(f11), _12(f12), _13(f13),
		_21(f21), _22(f22), _23(f23),
		_31(f31), _32(f32), _33(f33)
	{
	}
	//@}

	//------------------------------------------------------------------------
	//
	//! @name 代入演算子
	//
	//------------------------------------------------------------------------
	//@{
	//inline gt2Matrix3x3& operator= (const Ogre::Matrix3& m) { memcpy(this, &m, sizeof(Ogre::Matrix3)(); return *this; }
	//inline gt2Matrix3x3& operator= (const b2Mat33& m33) { memcpy(this, &m33, sizeof(b2Mat33)); return *this; }

	inline gt2Matrix3x3& operator *= (const gt2Matrix3x3& rM)
	{
		_11 = _11*rM._11 + _12*rM._21 + _13*rM._31;
		_12 = _11*rM._12 + _12*rM._22 + _13*rM._32;
		_13 = _11*rM._13 + _12*rM._23 + _13*rM._33;

		_21 = _21*rM._11 + _22*rM._21 + _23*rM._31;
		_22 = _21*rM._12 + _22*rM._22 + _23*rM._32;
		_23 = _21*rM._13 + _22*rM._23 + _23*rM._33;

		_31 = _31*rM._11 + _32*rM._21 + _33*rM._31;
		_32 = _31*rM._12 + _32*rM._22 + _33*rM._32;
		_33 = _31*rM._13 + _32*rM._23 + _33*rM._33;
		return *this;
	}
	inline gt2Matrix3x3& operator += (const gt2Matrix3x3& rM)
	{
		_11 += rM._11; _12 += rM._12; _13 += rM._13;
		_21 += rM._21; _22 += rM._22; _23 += rM._23;
		_31 += rM._31; _32 += rM._32; _33 += rM._33;
		return *this;
	}
	inline gt2Matrix3x3& operator -= (const gt2Matrix3x3& rM)
	{
		_11 -= rM._11; _12 -= rM._12; _13 -= rM._13;
		_21 -= rM._21; _22 -= rM._22; _23 -= rM._23;
		_31 -= rM._31; _32 -= rM._32; _33 -= rM._33;
		return *this;
	}
	inline gt2Matrix3x3& operator *= (float f)
	{
		_11 *= f; _12 *= f; _13 *= f;
		_21 *= f; _22 *= f; _23 *= f;
		_31 *= f; _32 *= f; _33 *= f;
		return *this;
	}
	inline gt2Matrix3x3& operator /= (float f)
	{
		float fInv = 1.0f / f;
		_11 *= fInv; _12 *= fInv; _13 *= fInv;
		_21 *= fInv; _22 *= fInv; _23 *= fInv;
		_31 *= fInv; _32 *= fInv; _33 *= fInv;
		return *this;
	}
	//@}

	//------------------------------------------------------------------------
	//
	//! @name 単項演算子
	//
	//------------------------------------------------------------------------
	//@{
	inline gt2Matrix3x3 operator + () const
	{
		return *this;
	}
	inline gt2Matrix3x3 operator - () const
	{
		return gt2Matrix3x3(-_11, -_12, -_13,
			-_21, -_22, -_23,
			-_31, -_32, -_33);
	}
	//@}

	//------------------------------------------------------------------------
	//
	//! @name 2 項演算子
	//
	//------------------------------------------------------------------------
	//@{
	inline gt2Matrix3x3
		operator * (const gt2Matrix3x3& tmp) const
	{
		gt2Matrix3x3 ret;
		ret._11 = _11*tmp._11 + _12*tmp._21 + _13*tmp._31;
		ret._12 = _11*tmp._12 + _12*tmp._22 + _13*tmp._32;
		ret._13 = _11*tmp._13 + _12*tmp._23 + _13*tmp._33;

		ret._21 = _21*tmp._11 + _22*tmp._21 + _23*tmp._31;
		ret._22 = _21*tmp._12 + _22*tmp._22 + _23*tmp._32;
		ret._23 = _21*tmp._13 + _22*tmp._23 + _23*tmp._33;

		ret._31 = _31*tmp._11 + _32*tmp._21 + _33*tmp._31;
		ret._32 = _31*tmp._12 + _32*tmp._22 + _33*tmp._32;
		ret._33 = _31*tmp._13 + _32*tmp._23 + _33*tmp._33;

		return ret;
	}
	inline gt2Matrix3x3
		operator + (const gt2Matrix3x3& tmp) const
	{
		gt2Matrix3x3 ret;
		ret._11 = _11 + tmp._11;
		ret._12 = _12 + tmp._12;
		ret._13 = _13 + tmp._13;

		ret._21 = _21 + tmp._21;
		ret._22 = _22 + tmp._22;
		ret._23 = _23 + tmp._23;

		ret._31 = _31 + tmp._31;
		ret._32 = _32 + tmp._32;
		ret._33 = _33 + tmp._33;
		return ret;
	}
	inline gt2Matrix3x3 operator - (const gt2Matrix3x3& rM) const
	{
		return gt2Matrix3x3(
			_11 - rM._11, _12 - rM._12, _13 - rM._13,
			_21 - rM._21, _22 - rM._22, _23 - rM._23,
			_31 - rM._31, _32 - rM._32, _33 - rM._33);
	}

	inline gt2Matrix3x3
		operator * (const float &tmp) const
	{
		gt2Matrix3x3 ret;
		ret._11 = _11*tmp;
		ret._12 = _12*tmp;
		ret._13 = _13*tmp;

		ret._21 = _21*tmp;
		ret._22 = _22*tmp;
		ret._23 = _23*tmp;

		ret._31 = _31*tmp;
		ret._32 = _32*tmp;
		ret._33 = _33*tmp;
		return ret;
	}
	inline gt2Matrix3x3
		operator / (const float &tmp) const
	{
		gt2Matrix3x3 ret;
		float factor = 1.0f / tmp;

		ret._11 = _11*factor;
		ret._12 = _12*factor;
		ret._13 = _13*factor;

		ret._21 = _21*factor;
		ret._22 = _22*factor;
		ret._23 = _23*factor;

		ret._31 = _31*factor;
		ret._32 = _32*factor;
		ret._33 = _33*factor;
		return ret;
	}
	inline gt2Matrix3x3 operator + (float f) const
	{
		return gt2Matrix3x3(
			_11 + f, _12 + f, _13 + f,
			_21 + f, _22 + f, _23 + f,
			_31 + f, _32 + f, _33 + f);
	}
	inline gt2Matrix3x3 operator - (float f) const
	{
		return gt2Matrix3x3(
			_11 - f, _12 - f, _13 - f,
			_21 - f, _22 - f, _23 - f,
			_31 - f, _32 - f, _33 - f);
	}
	inline gt2Matrix3x3 operator * (float f) const
	{
		return gt2Matrix3x3(
			_11 * f, _12 * f, _13 * f,
			_21 * f, _22 * f, _23 * f,
			_31 * f, _32 * f, _33 * f);
	}
	inline gt2Matrix3x3 operator / (float f) const
	{
		float fInv = 1.0f / f;
		return gt2Matrix3x3(
			_11 * fInv, _12 * fInv, _13 * fInv,
			_21 * fInv, _22 * fInv, _23 * fInv,
			_31 * fInv, _32 * fInv, _33 * fInv);
	}
	inline gt2Matrix3x3 operator / (const gt2Matrix3x3& rM) const
	{
		return gt2Matrix3x3(
			_11 / rM._11, _12 / rM._12, _13 / rM._13,
			_21 / rM._21, _22 / rM._22, _23 / rM._23,
			_31 / rM._31, _32 / rM._32, _33 / rM._33);
	}
	//@}

	//! @name 比較演算子
	//@{
	inline bool operator == (const gt2Matrix3x3& rM) const
	{
		return 0 == memcmp(this, &rM, sizeof(gt2Matrix3x3));
	}
	inline bool operator != (const gt2Matrix3x3& rM) const
	{
		return !(*this == rM);
	}
	//@}

	//-----------------------------------------------------------------------------------
	//! @brief 行列の逆行列を計算する。
	//! @param [out] pDeterminant  行列の行列式を含む float 値へのポインタ。@n
	//!                           行列式が不要の場合は、このパラメータに nullptr を設定する。
	//! @param [out] pOut          演算結果である gt2Matrix4x4 構造体へのポインタ。
	//! @return 逆行列の計算が失敗した場合は、false を返す。
	//-----------------------------------------------------------------------------------
	inline bool GetInverse(float *pDeterminant, gt2Matrix3x3* pOut) const
	{
		float d;

		d = _11*(_33 * _22 - _32 * _23) -
			_21*(_33 * _12 - _32 * _13) +
			_31*(_23 * _12 - _22 * _13);


		if (d == 0.0f)
			return false;

		d = 1.0f / d;


		pOut->_11 = d *  (_22*_33 - _23*_32);
		pOut->_12 = d * -(_12*_33 - _13*_32);
		pOut->_13 = d * -(_12*_33 - _13*_22);
		pOut->_21 = d * -(_21*_33 - _23*_31);
		pOut->_22 = d *  (_11*_33 - _13*_31);
		pOut->_23 = d * -(_11*_23 - _13*_21);
		pOut->_31 = d *  (_21*_32 - _22*_31);
		pOut->_32 = d * -(_11*_32 - _12*_31);
		pOut->_33 = d *  (_11*_22 - _12*_21);


		if (pDeterminant != nullptr) *pDeterminant = d;

		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 行列の逆行列を計算する。
	//! @param [out] rDeterminant  行列の行列式を含む float 値。@n
	//!                            行列式が不要の場合は、このパラメータに nullptr を設定する。
	//! @param [out] rOut          演算結果である gt2Matrix4x4 構造体。
	//! @return 逆行列の計算が失敗した場合は、false を返す。
	//-----------------------------------------------------------------------------------
	inline bool GetInverse(float &rDeterminant, gt2Matrix3x3& rOut) const
	{
		return this->GetInverse(&rDeterminant, &rOut);
	}
	//-----------------------------------------------------------------------------------
	//! @brief 4x4行列を3x3行列にクリップする
	//! @param [in] pMX  gt2Matrix4x4ポインタ
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void ClipMCXMATRIX(const gt2Matrix4x4 *pMX) {
		m[0][0] = pMX->_11; m[0][1] = pMX->_12; m[0][2] = pMX->_13;
		m[1][0] = pMX->_21; m[1][1] = pMX->_22; m[1][2] = pMX->_23;
		m[2][0] = pMX->_31; m[2][1] = pMX->_32; m[2][2] = pMX->_33;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 4x4行列を3x3行列にクリップする
	//! @param [in] rMX  gt2Matrix4x4
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void ClipMCXMATRIX(const gt2Matrix4x4 &rMX)
	{
		this->ClipMCXMATRIX(&rMX);
	}

	//-----------------------------------------------------------------------------------
	//! @brief マトリックスと3要素のベクトルを掛ける
	//! @param [in] rV  3要素のベクトル
	//! @return 演算結果を返す
	//-----------------------------------------------------------------------------------
	inline gt2Vector3 Multiply(const gt2Vector3& rV) const
	{
		gt2Vector3 out;
		out.x = (m[0][0] * rV.x) + (m[0][1] * rV.y) + (m[0][2] * rV.z);
		out.y = (m[1][0] * rV.x) + (m[1][1] * rV.y) + (m[1][2] * rV.z);
		out.z = (m[2][0] * rV.x) + (m[2][1] * rV.y) + (m[2][2] * rV.z);
		return out;
	}

	//-----------------------------------------------------------------------------------
	//! @brief 対角成分がfA~fC で与えられ，他の成分が0である行列を返す．
	//! @param [in] rV  3要素ベクトル
	//! @param [in] k   番目の対角上のリストの要素の値．
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void MakeDiagonal(const gt2Vector3& rIn, int k)
	{
		if (k < -2 || k > 2) return;

		memset(this, 0, sizeof(gt2Matrix3x3));

		if (k < 0) {
			k = abs(k) * 4;
		}
		mm[k] = rIn.x;
		if ((k += 4) > 8)return;
		mm[k] = rIn.y;
		if ((k += 4) > 8)return;
		mm[k] = rIn.z;
	}
	//-----------------------------------------------------------------------------------
	//! @brief クォータニオンから回転行列を作成します。
	//! @param [in] rQ  クオータニオン
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void MakeRotationQuaternion(const gt2Quaternion& rQ)
	{
		_11 = 1.0f - (rQ.y * rQ.y + rQ.z * rQ.z) * 2.0f;
		_12 = 2.0f * (rQ.x * rQ.y + rQ.z * rQ.w);
		_13 = 2.0f * (rQ.x * rQ.z - rQ.y * rQ.w);
		_21 = 2.0f * (rQ.x * rQ.y - rQ.z * rQ.w);
		_22 = 1.0f - (rQ.x * rQ.x + rQ.z * rQ.z) * 2.0f;
		_23 = 2.0f * (rQ.y * rQ.z + rQ.x * rQ.w);
		_31 = 2.0f * (rQ.x * rQ.z + rQ.y * rQ.w);
		_32 = 2.0f * (rQ.y * rQ.z - rQ.x * rQ.w);
		_33 = 1.0f - (rQ.x * rQ.x + rQ.y * rQ.y) * 2.0f;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 単位行列を作成する。
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void MakeIdentity()
	{
		memset(mm, 0, sizeof(gt2Matrix3x3));
		_11 = _22 = _33 = 1.0f;
	}
};
// エラー用
const gt2Matrix2x2 g_Matrix2x2_NaN = gt2Matrix2x2(NAN, NAN, NAN, NAN);
const gt2Matrix3x3 g_Matrix3x3_NaN = gt2Matrix3x3(NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN);
const gt2Matrix4x4 g_Matrix4x4_NaN = gt2Matrix4x4(NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN);


