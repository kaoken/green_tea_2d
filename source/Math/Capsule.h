//-----------------------------------------------------------------------------------
// ファイル： gt2Capsule3D.h, gt2Capsule3D.inl
//
// 説　明　：
// 　カプセル関連
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

#include <Math/vector.h>
#include <Math/Segment.h>
#include <Math/Sphere.h>


struct gt2Capsule3D;


bool GT2SphereCapsule(const gt2Sphere& rSp, const gt2Capsule3D& rCp);
bool GT2CapsuleCapsule(const gt2Capsule3D& rCP1, const gt2Capsule3D& rCP2);
bool GT2PlaneCapsule(const gt2Plane3& rPlane, const gt2Capsule3D& rCapsule);

//---------------------------------------
// カプセル（球体を使用）
//---------------------------------------
// 領域 R = { x | (x - [s.a + (s.b - s.a)*t])^2 <= r }, 0 <= t <= 1
typedef struct gt2Capsule3D {
	union {
		struct {
			mcSegment3 segment;	// 中間部の線分
		};
		struct {
			gt2Vector3 vStart, vEnd;
		};
	};
	float r;		// 半径

public:
	gt2Capsule3D() {}

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
	inline gt2Capsule3D& operator = (const gt2Capsule3D& v)
	{
		r = v.r;
		segment = v.segment;
		return *this;
	}

	bool SphereCapsule(const gt2Sphere& rSp) const
	{
		return GT2SphereCapsule(rSp, *this);
	}
	bool CapsuleCapsule(const gt2Capsule3D& rCP2) const
	{
		return GT2CapsuleCapsule(*this, rCP2);
	}

}gt2Capsule3D;
