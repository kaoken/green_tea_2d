/*! @file  gt2AABB2D.h
* @brief gt2AABB2D関連
* @author kaoken
* @date 2014/03/19 作成開始
*/
#pragma once

#include <Math/matrix.h>
#include <Math/Circle.h>
#include <Math/Sphere.h>
#include <Box2D/Box2D.h>


//---------------------------------------
//!@brief gt2AABB2D(Axis Aligned Bounding Box) 3D @n
//! 領域 R = { (x, y, z) | min.x<=x<=max.x, min.y<=y<=max.y, min.z<=z<=max.z }
//---------------------------------------
struct gt2AABB3D
{
	gt2Vector3 vMin;	//!< 最大値の要素
	gt2Vector3 vMax;	//!< 最小値の要素
	//-----------------------------------------------------------------------------------
	//! @brief コンストラクタ
	//-----------------------------------------------------------------------------------
	inline gt2AABB3D() { Init(); }
	//-----------------------------------------------------------------------------------
	//! @brief コンストラクタ
	//! @param [in] rMin 最大値の要素
	//! @param [in] rMax 最小値の要素
	//-----------------------------------------------------------------------------------
	inline gt2AABB3D(const gt2Vector3 &rMin, const gt2Vector3 &rMax){ Set(vMin, vMax); }
	//-----------------------------------------------------------------------------------
	//! @brief コンストラクタ
	//! @param [in] minX 最小値のXの値
	//! @param [in] minY 最小値のYの値
	//! @param [in] minZ 最小値のYの値
	//! @param [in] maxX 最大値のXの値
	//! @param [in] maxY 最大値のYの値
	//! @param [in] maxZ 最大値のYの値
	//-----------------------------------------------------------------------------------
	inline gt2AABB3D(float minX, float minY, float minZ, float maxX, float maxY, float maxZ){ Set(minX, minY, minZ, maxX, maxY, maxZ); }
	//-----------------------------------------------------------------------------------
	//! @brief コンストラクタ
	//! @param [in] minX 最小値のXの値
	//! @param [in] minY 最小値のYの値
	//! @param [in] minZ 最小値のYの値
	//! @param [in] maxX 最大値のXの値
	//! @param [in] maxY 最大値のYの値
	//! @param [in] maxZ 最大値のYの値
	//-----------------------------------------------------------------------------------
	inline gt2AABB3D(const gt2AABB3D& aabb){ Set(aabb); }

	//-----------------------------------------------------------------------------------
	//! @brief 値をセットする
	//! @param [in] rMin 最小値の要素
	//! @param [in] rMax 最大値の要素
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void Set(const gt2Vector3 &rMin, const gt2Vector3 &rMax) { vMin = rMin; vMax = rMax; }
	//-----------------------------------------------------------------------------------
	//! @brief 値をセットする
	//! @param [in] minX 最小値のXの値
	//! @param [in] minY 最小値のYの値
	//! @param [in] minZ 最小値のYの値
	//! @param [in] maxX 最大値のXの値
	//! @param [in] maxY 最大値のYの値
	//! @param [in] maxZ 最大値のYの値
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void Set(float minX, float minY, float minZ, float maxX, float maxY, float maxZ) { vMin = gt2Vector3(minX, minY, minZ); vMax = gt2Vector3(maxX, maxY, maxZ); }
	//-----------------------------------------------------------------------------------
	//! @brief 値をセットする
	//! @param [in] aabb gt2AABB3D
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void Set(const gt2AABB3D& aabb) { *this = aabb; }

	//! @name 代入演算子
	//@{
	inline gt2AABB3D& operator += (const gt2Vector3& v)
	{
		vMax += v;
		vMin += v;
		return *this;
	}

	inline gt2AABB3D& operator -= (const gt2Vector3& v)
	{
		vMax -= v;
		vMin -= v;
		return *this;
	}

	inline gt2AABB3D& operator *= (const gt2Vector3& v)
	{
		vMax.x *= v.x;
		vMax.y *= v.y;
		vMax.z *= v.z;
		vMin.x *= v.x;
		vMin.y *= v.y;
		vMin.z *= v.z;
		return *this;
	}

	inline gt2AABB3D& operator /= (const gt2Vector3& v)
	{
		vMax.x /= v.x;
		vMax.y /= v.y;
		vMax.z /= v.z;
		vMin.x /= v.x;
		vMin.y /= v.y;
		vMin.z /= v.z;
		return *this;
	}
	//@}

	//! @name 単演算子
	//@{
	inline gt2AABB3D operator + () const
	{
		return *this;
	}
	inline gt2AABB3D operator - () const
	{
		return gt2AABB3D(-vMin, -vMax);
	}
	//@}


	//! @name 二項演算子
	//@{
	inline gt2AABB3D operator + (const gt2Vector3& v) const
	{
		gt2AABB3D tmp;
		tmp.vMax = vMax + v;
		tmp.vMin = vMin + v;
		return tmp;
	}

	inline gt2AABB3D operator - (const gt2Vector3& v) const
	{
		gt2AABB3D tmp;
		tmp.vMax = vMax - v;
		tmp.vMin = vMin - v;
		return tmp;
	}

	inline gt2AABB3D operator * (const gt2Vector3& v) const
	{
		gt2AABB3D tmp;
		tmp.vMax.x = vMax.x * v.x;
		tmp.vMax.y = vMax.y * v.y;
		tmp.vMin.x = vMin.x * v.x;
		tmp.vMin.y = vMin.y * v.y;
		return tmp;
	}

	inline gt2AABB3D operator / (const gt2Vector3& v) const
	{
		gt2AABB3D tmp;
		tmp.vMax.x = vMax.x / v.x;
		tmp.vMax.y = vMax.y / v.y;
		tmp.vMin.x = vMin.x / v.x;
		tmp.vMin.y = vMin.y / v.y;
		return tmp;
	}
	//@}

	//! @name 比較演算子
	//@{
	inline bool operator == (const gt2AABB3D& v) const
	{
		return vMin == v.vMin && vMax == v.vMax;
	}
	inline bool operator != (const gt2AABB3D& v) const
	{
		return vMin != v.vMin || vMax != v.vMax;
	}
	//@}

	//-----------------------------------------------------------------------------------
	//! @brief 各要素を0で初期化
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void Init()
	{
		vMin.Init();
		vMax.Init();
	}
	//-----------------------------------------------------------------------------------
	//! @brief vMaxは、FLT_MIN、vMinは、FLT_MAXで各要素を初期化
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void InitMinMax()
	{
		vMin.InitMax();
		vMax.InitMin();
	}
	//-----------------------------------------------------------------------------------
	//! @brief 自身のgt2AABB2D　と 対象のgt2AABB2Dによるブール演算のAND処理をする。@n
	//!  返値がtrueの場合、pOutに出力される。
	//! @param [in]  aabb 対象となるgt2AABB2D
	//! @param [out] pOut  新たに作られたgt2AABB2D
	//! @return 重なっている場合は trueを返し、 重なっていない場合はfalseを返す
	//-----------------------------------------------------------------------------------
	inline bool BooleanOperation_AND(const gt2AABB3D& aabb, gt2AABB3D *pOut)
	{
		//            @-++-----+--@
		// 1. @=====@ | ||     |  |
		// 2.     @===+=@|     |  |
		// 3.         |  @=====@  |
		// 4.         |        @==+==@
		// 5.         |           |  @=====@
		// 6.       @=+===========+==@
		//----------------------------
		// X軸
		if (vMin.x <= aabb.vMin.x){
			if (aabb.vMax.x <= vMax.x){
				// 6.
				pOut->vMin.x = aabb.vMin.x;
				pOut->vMax.x = aabb.vMax.x;
			}
			else if (aabb.vMin.x <= vMax.x){
				// 2.
				pOut->vMin.x = aabb.vMin.x;
				pOut->vMax.x = vMax.x;
			}
			else /*if( vMax.x < aabb.vMin.x )*/ {
				// 1.
				return false;
			}
		}
		else if (vMin.x <= aabb.vMax.x){
			if (vMax.x <= aabb.vMax.x){
				// 3.
				pOut->vMin.x = vMin.x;
				pOut->vMax.x = vMax.x;
			}
			else /*if( vMax.x > aabb.vMax.x )*/{
				// 4.
				pOut->vMin.x = vMin.x;
				pOut->vMax.x = aabb.vMax.x;
			}
		}
		else{
			// 5.
			return false;
		}
		//----------------------------
		// Y軸
		if (vMin.y <= aabb.vMin.y){
			if (aabb.vMax.y <= vMax.y){
				// 6.
				pOut->vMin.y = aabb.vMin.y;
				pOut->vMax.y = aabb.vMax.y;
			}
			else if (aabb.vMin.y <= vMax.y){
				// 2.
				pOut->vMin.y = aabb.vMin.y;
				pOut->vMax.y = vMax.y;
			}
			else /*if( vMax.y < aabb.vMin.y )*/ {
				// 1.
				return false;
			}
		}
		else if (vMin.y <= aabb.vMax.y){
			if (vMax.y <= aabb.vMax.y){
				// 3.
				pOut->vMin.y = vMin.y;
				pOut->vMax.y = vMax.y;
			}
			else /*if( vMax.y > aabb.vMax.y )*/{
				// 4.
				pOut->vMin.y = vMin.y;
				pOut->vMax.y = aabb.vMax.y;
			}
		}
		else{
			// 5.
			return false;
		}
		//----------------------------
		// Z軸
		if (vMin.z <= aabb.vMin.z){
			if (aabb.vMax.z <= vMax.z){
				// 6.
				pOut->vMin.z = aabb.vMin.z;
				pOut->vMax.z = aabb.vMax.z;
			}
			else if (aabb.vMin.z <= vMax.z){
				// 2.
				pOut->vMin.z = aabb.vMin.z;
				pOut->vMax.z = vMax.z;
			}
			else /*if( vMax.z < aabb.vMin.z )*/ {
				// 1.
				return false;
			}
		}
		else if (vMin.z <= aabb.vMax.z){
			if (vMax.z <= aabb.vMax.z){
				// 3.
				pOut->vMin.z = vMin.z;
				pOut->vMax.z = vMax.z;
			}
			else /*if( vMax.z > aabb.vMax.z )*/{
				// 4.
				pOut->vMin.z = vMin.z;
				pOut->vMax.z = aabb.vMax.z;
			}
		}
		else{
			// 5.
			return false;
		}
		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 自身のgt2AABB2D　と 対象のgt2AABB2Dによるブール演算のAND処理をする。@n
	//!  返値がtrueの場合、pOutに出力される。
	//! @param [in]  aabb 対象となるgt2AABB2D
	//! @param [out] rOut  新たに作られたgt2AABB2D
	//! @return 重なっている場合は trueを返し、 重なっていない場合はfalseを返す
	//-----------------------------------------------------------------------------------
	inline bool BooleanOperation_AND(const gt2AABB3D& aabb, gt2AABB3D &rOut)
	{
		return BooleanOperation_AND(aabb, &rOut);
	}
	//-----------------------------------------------------------------------------------
	//! @brief gt2AABB2D　と gt2AABB2Dによるあたり判定
	//! @param [in] aabb 対象とするgt2AABB2D
	//! @return 重なっている場合は trueを返し、 重なっていない場合はfalseを返す
	//-----------------------------------------------------------------------------------
	inline bool AABB_AABB(const gt2AABB3D& aabb) const
	{
		// ある軸に沿って分離している場合は交差がないものとして終了
		if (vMax.x < aabb.vMin.x || vMin.x > aabb.vMax.x) return false;
		if (vMax.y < aabb.vMin.y || vMin.y > aabb.vMax.y) return false;
		if (vMax.z < aabb.vMin.z || vMin.z > aabb.vMax.z) return false;
		// すべての軸に沿って重なっている場合にgt2AABB2Dは交差している
		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief gt2AABB2D　と 球体によるあたり判定
	//! @param [in] rS 対象とする球体
	//! @return 重なっている場合は trueを返し、 重なっていない場合はfalseを返す
	//-----------------------------------------------------------------------------------
	inline bool AABB_Sphere(const gt2Sphere& rS) const
	{
		gt2Vector3 v = this->ClosestPtPoint(rS.c);

		v -= rS.c;
		return v.Dot() <= rS.r * rS.r;
	}

	//-----------------------------------------------------------------------------------
	//! @brief 指定した点(rP)が、自身のgt2AABB2D内に存在するか？
	//! @param [in] rP 対象とする点
	//! @return 重なっている場合は trueを返し、 重なっていない場合はfalseを返す
	//-----------------------------------------------------------------------------------
	inline bool AABB_Point(const gt2Vector3& rP) const
	{
		// ある軸に沿って分離している場合は交差がないものとして終了
		if (vMax.x < rP.x || vMin.x > rP.x) return false;
		if (vMax.y < rP.y || vMin.y > rP.y) return false;
		if (vMax.y < rP.z || vMin.y > rP.z) return false;
		// すべての軸に沿って重なっている場合にgt2AABB2Dは交差している
		return true;
	}

	//-----------------------------------------------------------------------------------
	//! @brief 一定の速度rvMeおよびrvBでそれぞれ運動しているこの自身のgt2AABB2Dおよび'aabb'が交差するか? @n
	//!  交差する場合には、最初および最後の接触時間がpfTFirstおよびpfTLastに返る
	//! @param [in]  aabb    対象とするgt2AABB2D
	//! @param [in]  rvMe     自身のgt2AABB2Dの速度
	//! @param [in]  rvB      aabbの速度
	//! @param [out] pfTFirst 最初の接触時間が返される
	//! @param [out] pfTLast  最後の接触時間が返される
	//! @return 重なっている場合は trueを返し、 重なっていない場合はfalseを返す
	//-----------------------------------------------------------------------------------
	inline bool IntersectMovingAABBAABB(
		const gt2AABB3D& aabb,
		const gt2Vector3& rvMe, const gt2Vector3& rvB,
		float *pfTFirst, float *pfTLast
		) const
	{
		// 最初の時点で'pvMe'および'pvB'が重なっている場合，早期に終了
		if (this->AABB_AABB(aabb)) {
			*pfTFirst = *pfTLast = 0.0f;
			return true;
		}

		// 相対速度を利用し、実質的に'pvMe'を静止しているものとして扱う
		gt2Vector3 v = rvMe - rvB;

		// 最初および最後の接触時間を初期化
		*pfTFirst = 0.0f;
		*pfTLast = 1.0f;

		// 各軸に対して、最初および最後の接触時間を、もしあれば決定する
		//----------------
		// X軸に対して
		//----------------
		if (v.x < 0.0f) {
			if (aabb.vMax.x < vMin.x) return false; // 交差はなく離れて運動している
			if (vMax.x < aabb.vMin.x) *pfTFirst = std::max((vMax.x - aabb.vMin.x) / v.x, *pfTFirst);
			if (aabb.vMax.x > vMin.x) *pfTLast = std::min((vMin.x - aabb.vMax.x) / v.x, *pfTLast);
		}
		if (v.x > 0.0f) {
			if (aabb.vMin.x > vMax.x) return false; // 交差はなく離れて運動している
			if (aabb.vMax.x < vMin.x) *pfTFirst = std::max((vMin.x - aabb.vMax.x) / v.x, *pfTFirst);
			if (vMax.x > aabb.vMin.x) *pfTLast = std::min((vMax.x - aabb.vMin.x) / v.x, *pfTLast);
		}
		// 最初の接触が最後の接触の後に発生する場合は、交差はあり得ない
		if (*pfTFirst > *pfTLast) return false;
		//----------------
		// Y軸に対して
		//----------------
		if (v.y < 0.0f) {
			if (aabb.vMax.y < vMin.y) return false; // 交差はなく離れて運動している
			if (vMax.y < aabb.vMin.y) *pfTFirst = std::max((vMax.y - aabb.vMin.y) / v.y, *pfTFirst);
			if (aabb.vMax.y > vMin.y) *pfTLast = std::min((vMin.y - aabb.vMax.y) / v.y, *pfTLast);
		}
		if (v.y > 0.0f) {
			if (aabb.vMin.y > vMax.y) return false; // 交差はなく離れて運動している
			if (aabb.vMax.y < vMin.y) *pfTFirst = std::max((vMin.y - aabb.vMax.y) / v.y, *pfTFirst);
			if (vMax.y > aabb.vMin.y) *pfTLast = std::min((vMax.y - aabb.vMin.y) / v.y, *pfTLast);
		}
		// 最初の接触が最後の接触の後に発生する場合は、交差はあり得ない
		if (*pfTFirst > *pfTLast) return false;
		//----------------
		// Z軸に対して
		//----------------
		if (v.z < 0.0f) {
			if (aabb.vMax.z < vMin.z) return false; // 交差はなく離れて運動している
			if (vMax.z < aabb.vMin.z) *pfTFirst = std::max((vMax.z - aabb.vMin.z) / v.z, *pfTFirst);
			if (aabb.vMax.z > vMin.z) *pfTLast = std::min((vMin.z - aabb.vMax.z) / v.z, *pfTLast);
		}
		if (v.z > 0.0f) {
			if (aabb.vMin.z > vMax.z) return false; // 交差はなく離れて運動している
			if (aabb.vMax.z < vMin.z) *pfTFirst = std::max((vMin.z - aabb.vMax.z) / v.z, *pfTFirst);
			if (vMax.z > aabb.vMin.z) *pfTLast = std::min((vMax.z - aabb.vMin.z) / v.z, *pfTLast);
		}
		// 最初の接触が最後の接触の後に発生する場合は、交差はあり得ない
		if (*pfTFirst > *pfTLast) return false;

		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 一定の速度rvMeおよびrvBでそれぞれ運動しているこの自身のgt2AABB2Dおよび'aabb'が交差するか? @n
	//!  交差する場合には、最初および最後の接触時間がpfTFirstおよびpfTLastに返る
	//! @param [in]  aabb    対象とするgt2AABB2D
	//! @param [in]  rvMe     自身のgt2AABB2Dの速度
	//! @param [in]  rvB      aabbの速度
	//! @param [out] rTFirst 最初の接触時間が返される
	//! @param [out] pfTLast  最後の接触時間が返される
	//! @return 重なっている場合は trueを返し、 重なっていない場合はfalseを返す
	//-----------------------------------------------------------------------------------
	inline bool IntersectMovingAABBAABB(
		const gt2AABB3D& aabb,
		const gt2Vector3& rvMe, const gt2Vector3& rvB,
		float &rTFirst, float &rTLast) const
	{
		return IntersectMovingAABBAABB(aabb, rvMe, rvB, &rTFirst, &rTLast);
	}
	//-----------------------------------------------------------------------------------
	//! @brief gt2AABB2Dのアンカー位置を取得する
	//! @return gt2AABB2Dのアンカー位置を返す
	//-----------------------------------------------------------------------------------
	inline gt2Vector3 GetCenter() const
	{
		return (vMin + vMax) * 0.5f;
	}
	//-----------------------------------------------------------------------------------
	//! @brief gt2AABB2Dのアンカー位置を(0,0)としたときのgt2AABB2Dを返す
	//! @return gt2AABB2Dのアンカー位置を(0,0)としたときのgt2AABB2Dを返す
	//-----------------------------------------------------------------------------------
	inline gt2AABB3D GetCenterZeroBase() const
	{
		float x = (vMax.x - vMin.x) * 0.5f;
		float y = (vMax.y - vMin.y) * 0.5f;
		float z = (vMax.z - vMin.z) * 0.5f;

		return gt2AABB3D(gt2Vector3(-x, -y, -z), gt2Vector3(x, y, z));
	}

	//-----------------------------------------------------------------------------------
	//! @brief gt2AABB2Dのアンカー位置からの各長さを取得する
	//! @return gt2AABB2Dのアンカー位置からの各長さを返す
	//-----------------------------------------------------------------------------------
	inline gt2Vector3 GetLengthFromCenter() const
	{
		gt2Vector3 tmp;
		tmp = (vMin + vMax) * 0.5f;
		return vMax - tmp;
	}
	//-----------------------------------------------------------------------------------
	//! @brief gt2AABB2Dのアンカー位置からの各長さとアンカー位置取得する
	//! @param [out] pvOutLen    gt2AABB2Dのアンカー位置からの各長さ
	//! @param [out] pvOutCenter gt2AABB2Dのアンカー位置
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void GetLengthFromCenter(gt2Vector3* pvOutLen, gt2Vector3* pvOutCenter) const
	{
		*pvOutCenter = (vMin + vMax) * 0.5f;
		*pvOutLen = vMax - *pvOutCenter;
	}
	//-----------------------------------------------------------------------------------
	//! @brief gt2AABB2Dのアンカー位置からの各長さとアンカー位置取得する
	//! @param [out] pvOutLen    gt2AABB2Dのアンカー位置からの各長さ
	//! @param [out] pvOutCenter gt2AABB2Dのアンカー位置
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void GetLengthFromCenter(gt2Vector3 &rvOutLen, gt2Vector3 &rvOutCenter) const
	{
		GetLengthFromCenter(&rvOutLen, &rvOutCenter);
	}
	//-----------------------------------------------------------------------------------
	//! @brief gt2AABB2Dから8頂点に分解してpvOutにセットする
	//! @param [out] pvOut 8個分頂点データがあるポインタ
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void Get8Vertexs(gt2Vector3* pvOut) const
	{
		pvOut[0].x = vMin.x; pvOut[1].x = vMax.x; pvOut[2].x = vMax.x; pvOut[3].x = vMin.x;
		pvOut[0].y = vMin.y; pvOut[1].y = vMin.y; pvOut[2].y = vMin.y; pvOut[3].y = vMin.y;
		pvOut[0].z = vMin.z; pvOut[1].z = vMin.z; pvOut[2].z = vMax.z; pvOut[3].z = vMax.z;
		//----
		pvOut[4].x = vMin.x; pvOut[5].x = vMax.x; pvOut[6].x = vMax.x; pvOut[7].x = vMin.x;
		pvOut[4].y = vMax.y; pvOut[5].y = vMax.y; pvOut[6].y = vMax.y; pvOut[7].y = vMax.y;
		pvOut[4].z = vMin.z; pvOut[5].z = vMin.z; pvOut[6].z = vMax.z; pvOut[7].z = vMax.z;
	}

	//-----------------------------------------------------------------------------------
	//! @brief 与えられた点rPに対して、このgt2AABB2Dのうえもしくは中にあるrPの最近接点を返す
	//! @param [in] rP 与えられた点
	//! @return 最近接点
	//-----------------------------------------------------------------------------------
	inline gt2Vector3 ClosestPtPoint(const gt2Vector3 &rP) const
	{
		gt2Vector3 ret;
		if (rP.x < vMin.x) ret.x = vMin.x;
		if (rP.y < vMin.y) ret.y = vMin.y;
		if (rP.z < vMin.z) ret.z = vMin.z;
		if (rP.x > vMax.x) ret.x = vMax.x;
		if (rP.y > vMax.y) ret.y = vMax.y;
		if (rP.z > vMax.z) ret.z = vMax.z;
		return ret;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 点rPと、このgt2AABB2Dの間の距離の平方を計算
	//! @param [in] rP 与えられた点
	//! @return 距離の平方値
	//-----------------------------------------------------------------------------------
	inline float  SqDistPoint(const gt2Vector3 &rP) const
	{
		float sqDist = 0.0f;
		if (rP.x < vMin.x) sqDist += (vMin.x - rP.x) * (vMin.x - rP.x);
		if (rP.y < vMin.y) sqDist += (vMin.y - rP.y) * (vMin.x - rP.y);
		if (rP.z < vMin.z) sqDist += (vMin.z - rP.z) * (vMin.z - rP.z);
		if (rP.x > vMax.x) sqDist += (vMax.x - rP.x) * (vMax.x - rP.x);
		if (rP.y > vMax.y) sqDist += (vMax.y - rP.y) * (vMax.x - rP.y);
		if (rP.z > vMax.z) sqDist += (vMax.z - rP.z) * (vMax.z - rP.z);
		return sqDist;
	}

	//-----------------------------------------------------------------------------------
	//! @brief マトリクスを元にgt2AABB2Dを作り直す
	//! @param [in] rM マトリクス
	//! @return 変形後のgt2AABB2Dを返す
	//-----------------------------------------------------------------------------------
	inline gt2AABB3D GetReMakeAABB(const gt2Matrix4x4& rM) const
	{
		int i;
		gt2Vector3 aV[8], vMx, vMn;

		this->Get8Vertexs(aV);

		for (i = 0; i < 8; ++i){
			aV[i] = rM.TransformVector3(aV[i]);
			vMx.SetMax(aV[i]);
			vMn.SetMax(aV[i]);
		}
		return gt2AABB3D(vMn, vMx);
	}
	//-----------------------------------------------------------------------------------
	//! @brief  対象gt2AABB2Dに基本位置を足したgt2AABB2Dが移動した時のgt2AABB2Dを作る
	//! @param [in] rBase    元となるgt2AABB2D
	//! @param [in] rBasePos 元となる現在位置
	//! @param [in] rVel     rBasePosを原点とした運動ベクトル
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void MakeMoveAABB(const gt2AABB3D& rBase, const gt2Vector3 &rBasePos, const gt2Vector3 &rVel)
	{
		gt2AABB3D tmp;

		vMin = rBase.vMin + rBasePos;
		vMax = rBase.vMax + rBasePos;
		tmp = *this;
		tmp.vMin += rVel;
		tmp.vMax += rVel;
		vMin.SetMin(tmp.vMin);
		vMax.SetMax(tmp.vMax);
	}
	//-----------------------------------------------------------------------------------
	//! @brief  対象gt2AABB2Dに基本位置を足したgt2AABB2Dが移動した時のgt2AABB2Dを作る
	//! @param [in] rBase    元となる球体
	//! @param [in] rVel     rBasePosを原点とした運動ベクトル
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void MakeMoveAABB(const gt2Sphere& rBase, const gt2Vector3 &rVel)
	{
		gt2AABB3D tmp;

		vMin = rBase.c - rBase.r;
		vMax = rBase.c + rBase.r;
		tmp = *this;
		tmp.vMin += rVel;
		tmp.vMax += rVel;
		vMin.SetMin(tmp.vMin);
		vMax.SetMax(tmp.vMax);
	}
	//-----------------------------------------------------------------------------------
	//! @brief  対象位置に、各軸の長さだけのgt2AABB2Dから移動した時のgt2AABB2Dを作る
	//! @param [in] rSize    元となる各軸のサイズだけ使用するgt2AABB2D
	//! @param [in] rBasePos 元となる現在位置
	//! @param [in] rVel     rBasePosを原点とした運動ベクトル
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void MakeMovePoint(const gt2AABB3D& rSize, const gt2Vector3 &rBasePos, const gt2Vector3 &rVel)
	{
		this->MakeMovePoint((rSize.vMax - rSize.vMin) * 0.5f, rBasePos, rVel);
	}
	//-----------------------------------------------------------------------------------
	//! @brief 2つの頂点からgt2AABB2Dを作成
	//! @param [in] a 頂点A
	//! @param [in] rvB 頂点B
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void MakeFromeSegment(const gt2Vector3& a, const gt2Vector3& rvB)
	{
		vMin.InitMin();
		vMax.InitMax();
		vMin.SetMin(a); vMin.SetMin(rvB);
		vMax.SetMax(a); vMax.SetMax(rvB);
	}
	//-----------------------------------------------------------------------------------
	//! @brief   対象位置に、各軸の長さだけのgt2AABB2Dから移動した時のgt2AABB2Dを作る
	//! @param [in] rL       gt2AABB2Dの各軸の半分の長さ
	//! @param [in] rBasePos 元となる現在位置
	//! @param [in] rVel     rBasePosを原点とした運動ベクトル
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void MakeMovePoint(const gt2Vector3& rL, const gt2Vector3 &rBasePos, const gt2Vector3 &rVel)
	{
		this->InitMinMax();
		vMin.SetMin(rBasePos - rL);
		vMax.SetMax(rBasePos + rL);
		vMin.SetMin((rBasePos + rVel) - rL);
		vMax.SetMax((rBasePos + rVel) + rL);
	}
	//-----------------------------------------------------------------------------------
	//! @brief 3つの頂点からgt2AABB2Dを作成
	//! @param [in] a 頂点A
	//! @param [in] rvB 頂点B
	//! @param [in] rvC 頂点C
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void MakeFromeTriangle(const gt2Vector3& a, const gt2Vector3& rvB, const gt2Vector3& rvC)
	{
		vMin.InitMin();
		vMax.InitMax();
		vMin.SetMin(a); vMin.SetMin(rvB); vMin.SetMin(rvC);
		vMax.SetMax(a); vMax.SetMax(rvB); vMax.SetMax(rvC);
	}
	//-----------------------------------------------------------------------------------
	//! @brief 自身のgt2AABB2Dを新たなgt2AABB2Dの最大、最小の要素値を元に作り直す
	//! @param [in] aabb 対象とするgt2AABB2D
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void ReMakeMinMax(const gt2AABB3D& aabb)
	{
		vMin.SetMin(aabb.vMin);
		vMax.SetMax(aabb.vMax);
	}

	//-----------------------------------------------------------------------------------
	//! @brief 自身のgt2AABB2Dを新たなgt2AABB2Dを足して拡張させる
	//! @param [in] a 頂点A
	//! @param [in] rvB 頂点B
	//! @param [in] rvC 頂点C
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void ReMakeExtension(const gt2AABB3D& aabb)
	{
		vMin.SetMin(aabb.vMin); vMin.SetMin(aabb.vMax);
		vMax.SetMax(aabb.vMin); vMax.SetMax(aabb.vMax);
	}
	//-----------------------------------------------------------------------------------
	//! @brief 自身のgt2AABB2Dの8隅(頂点)を長さR分だけ拡張する
	//! @param [in] fR 半径
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void ReMakeExtension(float fR)
	{
		vMin.x -= fR; vMin.y -= fR;
		vMax.x += fR; vMax.y += fR;
	}
	//-----------------------------------------------------------------------------------
	//! @brief gt2AABB2Dが平面と交差しているか？
	//! @param [in] rPlane 対象平面
	//! @return 0の場合、交差している。-1の場合、裏側にある。1の場合、表側にある
	//-----------------------------------------------------------------------------------
	inline int  AABB_Plane(const gt2Plane3 &rPlane) const
	{
		gt2Vector3 vC = (vMax + vMin) * 0.5f;
		gt2Vector3 vE = vMax - vC;

		float fR = vE.x * fabs(rPlane.vNormal.x) + vE.y * fabs(rPlane.vNormal.y) + vE.z * fabs(rPlane.vNormal.z);
		float fS = rPlane.vNormal.Dot(vC) - rPlane.distance;

		if (fabs(fS) <= fR){
			// 交差している
			return 0;
		}
		else if (fS < 0){
			// 裏側にある
			return -1;
		}

		// 表側にある
		return 1;
	}
};



//---------------------------------------
//!@brief gt2AABB2D(Axis Aligned Bounding Box) 2D @n
//! 領域 R = { (x, y) | min.x<=x<=max.x, min.y<=y<=max.y }
//---------------------------------------
struct gt2AABB2D
{
	gt2Vector2 vMin;	//!< 最大値の要素
	gt2Vector2 vMax;	//!< 最小値の要素

	//-----------------------------------------------------------------------------------
	//! @brief コンストラクタ
	//-----------------------------------------------------------------------------------
	inline  gt2AABB2D()
	{
		this->Init();
	}

#ifdef B2_MATH_H
	inline  gt2AABB2D(const b2AABB &aabb) {
		vMin = aabb.lowerBound;
		vMax = aabb.upperBound;
	}
#endif

	//-----------------------------------------------------------------------------------
	//! @brief コンストラクタ
	//! @param [in] rMin 最小値の要素
	//! @param [in] rMax 最大値の要素
	//-----------------------------------------------------------------------------------
	inline  gt2AABB2D(const gt2Vector2 &rMin, const gt2Vector2 &rMax){ Set(rMin, rMax); }

	//-----------------------------------------------------------------------------------
	//! @brief コンストラクタ
	//! @param [in] minX 最小値のXの値
	//! @param [in] minY 最小値のYの値
	//! @param [in] maxX 最大値のXの値
	//! @param [in] maxY 最大値のYの値
	//-----------------------------------------------------------------------------------
	inline  gt2AABB2D(float minX, float minY, float maxX, float maxY){ Set(minX, minY, maxX, maxY); }

	//-----------------------------------------------------------------------------------
	//! @brief コンストラクタ
	//! @param [in] aabb gt2AABB2D
	//-----------------------------------------------------------------------------------
	inline  gt2AABB2D(const gt2AABB2D& aabb){ Set(aabb); }


#ifdef B2_MATH_H
	//-----------------------------------------------------------------------------------
	//! @brief 値をセットする
	//! @param [in] aabb b2AABB
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void Set(const b2AABB &aabb) {
		vMin = aabb.lowerBound;
		vMax = aabb.upperBound;
	}
#endif
	//-----------------------------------------------------------------------------------
	//! @brief 値をセットする
	//! @param [in] rMin 最小値の要素
	//! @param [in] rMax 最大値の要素
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void Set(const gt2Vector2 &rMin, const gt2Vector2 &rMax) { vMin = rMin; vMax = rMax; }
	//-----------------------------------------------------------------------------------
	//! @brief 値をセットする
	//! @param [in] minX 最小値のXの値
	//! @param [in] minY 最小値のYの値
	//! @param [in] maxX 最大値のXの値
	//! @param [in] maxY 最大値のYの値
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void Set(float minX, float minY, float maxX, float maxY) { vMin = gt2Vector2(minX, minY); vMax = gt2Vector2(maxX,maxY); }
	//-----------------------------------------------------------------------------------
	//! @brief 値をセットする
	//! @param [in] aabb gt2AABB2D
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void Set(const gt2AABB2D& aabb) { *this = aabb; }


	//! @name 代入演算子
	//@{
#ifdef B2_MATH_H
	inline gt2AABB2D& operator = (const b2AABB &aabb) {
		vMin = aabb.lowerBound;
		vMax = aabb.upperBound;
		return *this;
	}
#endif		
	inline gt2AABB2D& operator += (const gt2Vector2& v)
	{
		vMax += v;
		vMin += v;
		return *this;
	}
	inline gt2AABB2D& operator += (const gt2Vector3& v)
	{
		vMax.x += v.x;
		vMax.y += v.y;
		vMin.x += v.x;
		vMin.y += v.y;
		return *this;
	}

	inline gt2AABB2D& operator -= (const gt2Vector2& v)
	{
		vMax -= v;
		vMin -= v;
		return *this;
	}
	inline gt2AABB2D& operator -= (const gt2Vector3& v)
	{
		vMax.x -= v.x;
		vMax.y -= v.y;
		vMin.x -= v.x;
		vMin.y -= v.y;
		return *this;
	}

	inline gt2AABB2D& operator *= (const gt2Vector2& v)
	{
		vMax.x *= v.x;
		vMax.y *= v.y;
		vMin.x *= v.x;
		vMin.y *= v.y;
		return *this;
	}
	inline gt2AABB2D& operator *= (const gt2Vector3& v)
	{
		vMax.x *= v.x;
		vMax.y *= v.y;
		vMin.x *= v.x;
		vMin.y *= v.y;
		return *this;
	}

	inline gt2AABB2D& operator /= (const gt2Vector2& v)
	{
		vMax.x /= v.x;
		vMax.y /= v.y;
		vMin.x /= v.x;
		vMin.y /= v.y;
		return *this;
	}
	inline gt2AABB2D& operator /= (const gt2Vector3& v)
	{
		vMax.x /= v.x;
		vMax.y /= v.y;
		vMin.x /= v.x;
		vMin.y /= v.y;
		return *this;
	}
	//@}

	//! @name 単演算子
	//@{
	inline gt2AABB2D operator + () const
	{
		return *this;
	}
	inline gt2AABB2D operator - () const
	{
		return gt2AABB2D(-vMin, -vMax);
	}
	//@}


	//! @name 二項演算子
	//@{
	inline gt2AABB2D operator + (const gt2Vector2& v) const
	{
		gt2AABB2D tmp;
		tmp.vMax = vMax + v;
		tmp.vMin = vMin + v;
		return tmp;
	}
	inline gt2AABB2D operator + (const gt2Vector3& v) const
	{
		gt2AABB2D tmp;
		tmp.vMax.x = vMax.x + v.x;
		tmp.vMax.y = vMax.y + v.y;
		tmp.vMin.x = vMin.x + v.x;
		tmp.vMin.y = vMin.y + v.y;
		return tmp;
	}

	inline gt2AABB2D operator - (const gt2Vector2& v) const
	{
		gt2AABB2D tmp;
		tmp.vMax = vMax - v;
		tmp.vMin = vMin - v;
		return tmp;
	}
	inline gt2AABB2D operator - (const gt2Vector3& v) const
	{
		gt2AABB2D tmp;
		tmp.vMax.x = vMax.x - v.x;
		tmp.vMax.y = vMax.y - v.y;
		tmp.vMin.x = vMin.x - v.x;
		tmp.vMin.y = vMin.y - v.y;
		return tmp;
	}

	inline gt2AABB2D operator * (const gt2Vector2& v) const
	{
		gt2AABB2D tmp;
		tmp.vMax.x = vMax.x * v.x;
		tmp.vMax.y = vMax.y * v.y;
		tmp.vMin.x = vMin.x * v.x;
		tmp.vMin.y = vMin.y * v.y;
		return tmp;
	}
	inline gt2AABB2D operator * (const gt2Vector3& v) const
	{
		gt2AABB2D tmp;
		tmp.vMax.x = vMax.x * v.x;
		tmp.vMax.y = vMax.y * v.y;
		tmp.vMin.x = vMin.x * v.x;
		tmp.vMin.y = vMin.y * v.y;
		return tmp;
	}

	inline gt2AABB2D operator / (const gt2Vector2& v) const
	{
		gt2AABB2D tmp;
		tmp.vMax.x = vMax.x / v.x;
		tmp.vMax.y = vMax.y / v.y;
		tmp.vMin.x = vMin.x / v.x;
		tmp.vMin.y = vMin.y / v.y;
		return tmp;
	}
	inline gt2AABB2D operator / (const gt2Vector3& v) const
	{
		gt2AABB2D tmp;
		tmp.vMax.x = vMax.x / v.x;
		tmp.vMax.y = vMax.y / v.y;
		tmp.vMin.x = vMin.x / v.x;
		tmp.vMin.y = vMin.y / v.y;
		return tmp;
	}
	//@}

	//! @name 比較演算子
	//@{
	inline bool operator == (const gt2AABB2D& v) const
	{
		return vMin == v.vMin && vMax == v.vMax;
	}
	inline bool operator != (const gt2AABB2D& v) const
	{
		return vMin != v.vMin || vMax != v.vMax;
	}
	//@}

	//-----------------------------------------------------------------------------------
	//! @brief 各要素を0で初期化
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void Init()
	{
		vMin.Init();
		vMax.Init();
	}
	//-----------------------------------------------------------------------------------
	//! @brief vMaxは、FLT_MAX、vMinは、FLT_MINで各要素を初期化
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void InitMinMax()
	{
		vMin.InitMax();
		vMax.InitMin();
	}
	//-----------------------------------------------------------------------------------
	//! @brief　vMin(x, y - (h - 1)) 、vMax(x + (w - 1), y)のgt2AABB2Dを作る
	//! @param [in] x x座標
	//! @param [in] y y座標
	//! @param [in] w 幅
	//! @param [in] h 高さ
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void Set_X_Y_W_H(float x, float y, float w, float h)
	{
		vMin.x = x;
		vMin.y = y - (h - 1);
		vMax.x = x + (w - 1);
		vMax.y = y;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 自身のgt2AABB2D　と 対象のgt2AABB2Dによるブール演算のAND処理をする。@n
	//!  返値がtrueの場合、pOutに出力される。
	//! @param [out] rOut  新たに作られたgt2AABB2D
	//! @param [in]  aabb 対象となるgt2AABB2D
	//! @return 重なっている場合は trueを返し、 重なっていない場合はfalseを返す
	//-----------------------------------------------------------------------------------
	inline bool BooleanOperation_AND(const gt2AABB2D& aabb, gt2AABB2D &rOut)
	{
		return BooleanOperation_AND(aabb, &rOut);
	}
	//-----------------------------------------------------------------------------------
	//! @brief 自身のgt2AABB2D　と 対象のgt2AABB2Dによるブール演算のAND処理をする。@n
	//!  返値がtrueの場合、pOutに出力される。
	//! @param [in]  aabb 対象となるgt2AABB2D
	//! @param [out] pOut  新たに作られたgt2AABB2D
	//! @return 重なっている場合は trueを返し、 重なっていない場合はfalseを返す
	//-----------------------------------------------------------------------------------
	inline bool BooleanOperation_AND(const gt2AABB2D& aabb, gt2AABB2D *pOut)
	{
		//            @-++-----+--@
		// 1. @=====@ | ||     |  |
		// 2.     @===+=@|     |  |
		// 3.         |  @=====@  |
		// 4.         |        @==+==@
		// 5.         |           |  @=====@
		// 6.       @=+===========+==@
		//----------------------------
		// X軸
		if (vMin.x <= aabb.vMin.x){
			if (aabb.vMax.x <= vMax.x){
				// 6.
				pOut->vMin.x = aabb.vMin.x;
				pOut->vMax.x = aabb.vMax.x;
			}
			else if (aabb.vMin.x <= vMax.x){
				// 2.
				pOut->vMin.x = aabb.vMin.x;
				pOut->vMax.x = vMax.x;
			}
			else /*if( vMax.x < aabb.vMin.x )*/ {
				// 1.
				return false;
			}
		}
		else if (vMin.x <= aabb.vMax.x){
			if (vMax.x <= aabb.vMax.x){
				// 3.
				pOut->vMin.x = vMin.x;
				pOut->vMax.x = vMax.x;
			}
			else /*if( vMax.x > aabb.vMax.x )*/{
				// 4.
				pOut->vMin.x = vMin.x;
				pOut->vMax.x = aabb.vMax.x;
			}
		}
		else{
			// 5.
			return false;
		}
		//----------------------------
		// Y軸
		if (vMin.y <= aabb.vMin.y){
			if (aabb.vMax.y <= vMax.y){
				// 6.
				pOut->vMin.y = aabb.vMin.y;
				pOut->vMax.y = aabb.vMax.y;
			}
			else if (aabb.vMin.y <= vMax.y){
				// 2.
				pOut->vMin.y = aabb.vMin.y;
				pOut->vMax.y = vMax.y;
			}
			else /*if( vMax.y < aabb.vMin.y )*/ {
				// 1.
				return false;
			}
		}
		else if (vMin.y <= aabb.vMax.y){
			if (vMax.y <= aabb.vMax.y){
				// 3.
				pOut->vMin.y = vMin.y;
				pOut->vMax.y = vMax.y;
			}
			else /*if( vMax.y > aabb.vMax.y )*/{
				// 4.
				pOut->vMin.y = vMin.y;
				pOut->vMax.y = aabb.vMax.y;
			}
		}
		else{
			// 5.
			return false;
		}
		return true;
	}

	//-----------------------------------------------------------------------------------
	//! @brief gt2AABB2D　と gt2AABB2Dによるあたり判定
	//! @param [in] aabb 対象とするgt2AABB2D
	//! @return 重なっている場合は trueを返し、 重なっていない場合はfalseを返す
	//-----------------------------------------------------------------------------------
	inline bool AABB_AABB(const gt2AABB2D& aabb) const
	{
		// ある軸に沿って分離している場合は交差がないものとして終了
		if (vMax.x < aabb.vMin.x || vMin.x > aabb.vMax.x) return false;
		if (vMax.y < aabb.vMin.y || vMin.y > aabb.vMax.y) return false;
		// すべての軸に沿って重なっている場合にgt2AABB2Dは交差している
		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief gt2AABB2D　と 円によるあたり判定
	//! @param [in] rCIRCLE 対象とする円
	//! @return 重なっている場合は trueを返し、 重なっていない場合はfalseを返す
	//-----------------------------------------------------------------------------------
	inline bool AABB_CIRCLE(const gt2Circle2& rCIRCLE) const
	{
		gt2Vector2 v = this->ClosestPtPoint(rCIRCLE.c);

		v -= rCIRCLE.c;
		return v.Dot() <= rCIRCLE.r * rCIRCLE.r;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 指定した点(rP)が、自身のgt2AABB2D内に存在するか？
	//! @param [in] rP 対象とする点
	//! @return 重なっている場合は trueを返し、 重なっていない場合はfalseを返す
	//-----------------------------------------------------------------------------------
	inline bool AABB_Point(const gt2Vector2& rP) const
	{
		// ある軸に沿って分離している場合は交差がないものとして終了
		if (vMax.x < rP.x || vMin.x > rP.x) return false;
		if (vMax.y < rP.y || vMin.y > rP.y) return false;
		// すべての軸に沿って重なっている場合にgt2AABB2Dは交差している
		return true;
	}

	//-----------------------------------------------------------------------------------
	//! @brief 一定の速度rvMeおよびrvBでそれぞれ運動しているこの自身のgt2AABB2Dおよび'aabb'が交差するか? @n
	//!  交差する場合には、最初および最後の接触時間がpfTFirstおよびpfTLastに返る
	//! @param [in]  aabb    対象とするgt2AABB2D
	//! @param [in]  rvMe     自身のgt2AABB2Dの速度
	//! @param [in]  rvB      aabbの速度
	//! @param [out] rTFirst 最初の接触時間が返される
	//! @param [out] rTLast  最後の接触時間が返される
	//! @return 重なっている場合は trueを返し、 重なっていない場合はfalseを返す
	//-----------------------------------------------------------------------------------
	inline bool IntersectMovingAABBAABB(
		const gt2AABB2D& aabb,
		const gt2Vector2& rvMe, const gt2Vector2& rvB,
		float &rTFirst, float &rTLast
		) const
	{
		return IntersectMovingAABBAABB(aabb, rvMe, rvB, &rTFirst, &rTLast);
	}
	//-----------------------------------------------------------------------------------
	//! @brief 一定の速度rvMeおよびrvBでそれぞれ運動しているこの自身のgt2AABB2Dおよび'aabb'が交差するか? @n
	//!  交差する場合には、最初および最後の接触時間がpfTFirstおよびpfTLastに返る
	//! @param [in]  aabb    対象とするgt2AABB2D
	//! @param [in]  rvMe     自身のgt2AABB2Dの速度
	//! @param [in]  rvB      aabbの速度
	//! @param [out] pfTFirst 最初の接触時間が返される
	//! @param [out] pfTLast  最後の接触時間が返される
	//! @return 重なっている場合は trueを返し、 重なっていない場合はfalseを返す
	//-----------------------------------------------------------------------------------
	inline bool IntersectMovingAABBAABB(
		const gt2AABB2D& aabb,
		const gt2Vector2& rvMe, const gt2Vector2& rvB,
		float *pfTFirst, float *pfTLast
		) const
	{
		// 最初の時点で'pvMe'および'pvB'が重なっている場合，早期に終了
		if (this->AABB_AABB(aabb)) {
			*pfTFirst = *pfTLast = 0.0f;
			return true;
		}

		// 相対速度を利用し、実質的に'pvMe'を静止しているものとして扱う
		gt2Vector2 v = rvMe - rvB;

		// 最初および最後の接触時間を初期化
		*pfTFirst = 0.0f;
		*pfTLast = 1.0f;

		// 各軸に対して、最初および最後の接触時間を、もしあれば決定する
		//----------------
		// X軸に対して
		//----------------
		if (v.x < 0.0f) {
			if (aabb.vMax.x < vMin.x) return false; // 交差はなく離れて運動している
			if (vMax.x < aabb.vMin.x) *pfTFirst = std::max((vMax.x - aabb.vMin.x) / v.x, *pfTFirst);
			if (aabb.vMax.x > vMin.x) *pfTLast = std::min((vMin.x - aabb.vMax.x) / v.x, *pfTLast);
		}
		if (v.x > 0.0f) {
			if (aabb.vMin.x > vMax.x) return false; // 交差はなく離れて運動している
			if (aabb.vMax.x < vMin.x) *pfTFirst = std::max((vMin.x - aabb.vMax.x) / v.x, *pfTFirst);
			if (vMax.x > aabb.vMin.x) *pfTLast = std::min((vMax.x - aabb.vMin.x) / v.x, *pfTLast);
		}
		// 最初の接触が最後の接触の後に発生する場合は、交差はあり得ない
		if (*pfTFirst > *pfTLast) return false;
		//----------------
		// Y軸に対して
		//----------------
		if (v.y < 0.0f) {
			if (aabb.vMax.y < vMin.y) return false; // 交差はなく離れて運動している
			if (vMax.y < aabb.vMin.y) *pfTFirst = std::max((vMax.y - aabb.vMin.y) / v.y, *pfTFirst);
			if (aabb.vMax.y > vMin.y) *pfTLast = std::min((vMin.y - aabb.vMax.y) / v.y, *pfTLast);
		}
		if (v.y > 0.0f) {
			if (aabb.vMin.y > vMax.y) return false; // 交差はなく離れて運動している
			if (aabb.vMax.y < vMin.y) *pfTFirst = std::max((vMin.y - aabb.vMax.y) / v.y, *pfTFirst);
			if (vMax.y > aabb.vMin.y) *pfTLast = std::min((vMax.y - aabb.vMin.y) / v.y, *pfTLast);
		}
		// 最初の接触が最後の接触の後に発生する場合は、交差はあり得ない
		if (*pfTFirst > *pfTLast) return false;

		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief gt2AABB2Dのアンカー位置を取得する
	//! @param [out] x x座標
	//! @param [out] y y座標
	//! @param [out] w 幅
	//! @param [out] h 高さ
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void Get_X_Y_W_H(float &x, float &y, float &w, float &h) const
	{
		Get_X_Y_W_H(&x, &y, &w, &h);
	}
	//-----------------------------------------------------------------------------------
	//! @brief gt2AABB2Dのアンカー位置を取得する
	//! @param [out] px x座標
	//! @param [out] py y座標
	//! @param [out] pw 幅
	//! @param [out] ph 高さ
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void Get_X_Y_W_H(float *px, float *py, float *pw, float *ph) const
	{
		*px = vMin.x;
		*py = vMax.y;
		*pw = vMax.x - vMin.x + 1;
		*ph = vMax.y - vMin.y + 1;
	}
	//-----------------------------------------------------------------------------------
	//! @brief gt2AABB2Dのアンカー位置を取得する
	//! @return gt2AABB2Dのアンカー位置を返す
	//-----------------------------------------------------------------------------------
	inline gt2Vector2 GetCenter() const
	{
		return (vMin + vMax) * 0.5f;
	}
	//-----------------------------------------------------------------------------------
	//! @brief gt2AABB2Dのアンカー位置を(0,0)としたときのgt2AABB2Dを返す
	//! @return gt2AABB2Dのアンカー位置を(0,0)としたときのgt2AABB2Dを返す
	//-----------------------------------------------------------------------------------
	inline gt2AABB2D GetCenterZeroBase() const
	{
		float x = (vMax.x - vMin.x) * 0.5f;
		float y = (vMax.y - vMin.y) * 0.5f;

		return gt2AABB2D(gt2Vector2(-x, -y), gt2Vector2(x, y));
	}
	//-----------------------------------------------------------------------------------
	//! @brief gt2AABB2Dのアンカー位置からの各長さを取得する
	//! @return gt2AABB2Dのアンカー位置からの各長さを返す
	//-----------------------------------------------------------------------------------
	inline gt2Vector2 GetLengthFromCenter() const
	{
		gt2Vector2 tmp;
		tmp = (vMin + vMax) * 0.5f;
		return vMax - tmp;
	}
	//-----------------------------------------------------------------------------------
	//! @brief gt2AABB2Dのアンカー位置からの各長さとアンカー位置取得する
	//! @param [out] rvOutLen    gt2AABB2Dのアンカー位置からの各長さ
	//! @param [out] rvOutCenter gt2AABB2Dのアンカー位置
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void GetLengthFromCenter(gt2Vector2& rvOutLen, gt2Vector2& rvOutCenter) const
	{
		GetLengthFromCenter(&rvOutLen, &rvOutCenter);
	}
	//-----------------------------------------------------------------------------------
	//! @brief gt2AABB2Dのアンカー位置からの各長さとアンカー位置取得する
	//! @param [out] pvOutLen    gt2AABB2Dのアンカー位置からの各長さ
	//! @param [out] pvOutCenter gt2AABB2Dのアンカー位置
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void GetLengthFromCenter(gt2Vector2* pvOutLen, gt2Vector2* pvOutCenter) const
	{
		*pvOutCenter = (vMin + vMax) * 0.5f;
		*pvOutLen = vMax - *pvOutCenter;
	}
	//-----------------------------------------------------------------------------------
	//! @brief gt2AABB2Dから4頂点に分解してpvOutにセットする
	//! @param [out] pvOut 4個分頂点データがあるポインタ
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void Get4Vertexs(gt2Vector2* pvOut) const
	{
		pvOut[0].x = vMin.x; pvOut[1].x = vMax.x; pvOut[2].x = vMax.x; pvOut[3].x = vMin.x;
		pvOut[0].y = vMin.y; pvOut[1].y = vMin.y; pvOut[2].y = vMax.y; pvOut[3].y = vMax.y;
	}
	//-----------------------------------------------------------------------------------
	//! @brief gt2AABB2Dから4頂点に分解してpvOutにセットする
	//! @param [out] pvOut 4個分頂点データがあるポインタ
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void Get4Vertexs(gt2Vector3* pvOut) const
	{
		pvOut[0].x = vMin.x; pvOut[1].x = vMax.x; pvOut[2].x = vMax.x; pvOut[3].x = vMin.x;
		pvOut[0].y = vMin.y; pvOut[1].y = vMin.y; pvOut[2].y = vMax.y; pvOut[3].y = vMax.y;
		pvOut[0].z = 0.0f; pvOut[1].z = 0.0f; pvOut[2].z = 0.0f; pvOut[3].z = 0.0f;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 与えられた点rPに対して、このgt2AABB2Dのうえもしくは中にあるrPの最近接点を返す
	//! @param [in] rP 与えられた点
	//! @return 最近接点
	//-----------------------------------------------------------------------------------
	inline gt2Vector2 ClosestPtPoint(const gt2Vector2 &rP) const
	{
		gt2Vector2 ret;
		if (rP.x < vMin.x) ret.x = vMin.x;
		if (rP.x > vMax.x) ret.x = vMax.x;
		if (rP.y < vMin.y) ret.y = vMin.y;
		if (rP.y > vMax.y) ret.y = vMax.y;
		return ret;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 点rPと、このgt2AABB2Dの間の距離の平方を計算
	//! @param [in] rP 与えられた点
	//! @return 距離の平方値
	//-----------------------------------------------------------------------------------
	inline float  SqDistPoint(const gt2Vector2 &rP) const
	{
		float sqDist = 0.0f;
		if (rP.x < vMin.x) sqDist += (vMin.x - rP.x) * (vMin.x - rP.x);
		if (rP.x > vMax.x) sqDist += (vMax.x - rP.x) * (vMax.x - rP.x);
		if (rP.y < vMin.y) sqDist += (vMin.y - rP.y) * (vMin.x - rP.y);
		if (rP.y > vMax.y) sqDist += (vMax.y - rP.y) * (vMax.x - rP.y);
		return sqDist;
	}

	//-----------------------------------------------------------------------------------
	//! @brief マトリクスを元にgt2AABB2Dを作り直す
	//! @param [in] rM マトリクス
	//! @return 変形後のgt2AABB2Dを返す
	//-----------------------------------------------------------------------------------
	inline gt2AABB2D GetReMakeAABB(const gt2Matrix4x4& rM) const
	{
		int i;
		gt2Vector3 aV3[4];
		gt2Vector2 aV[4], vMx, vMn;

		for (i = 0; i<4; ++i){
			aV3[i] = aV[i];
		}

		this->Get4Vertexs(aV3);

		for (i = 0; i<4; ++i){
			aV3[i] = rM.TransformVector3(aV3[i]);
			vMx.SetMax(gt2Vector2(aV3[i].x, aV3[i].y));
			vMn.SetMax(gt2Vector2(aV3[i].x, aV3[i].y));
		}
		return gt2AABB2D(vMn, vMx);
	}
	//-----------------------------------------------------------------------------------
	//! @brief  自身のgt2AABB2DのX軸を起点とした左右反転のgt2AABB2Dを作る
	//! @param [in] fX    Xの値
	//! @return X軸を起点とした左右反転のgt2AABB2Dを返す
	//-----------------------------------------------------------------------------------
	inline gt2AABB2D MakeFlipHorizontal(float fX) const
	{
		gt2AABB2D ret = *this;
		ret.vMin.x = fX - vMax.x;
		ret.vMax.x = fX - vMin.x;
		return ret;
	}
	//-----------------------------------------------------------------------------------
	//! @brief  対象gt2AABB2Dに基本位置を足したgt2AABB2Dが移動した時のgt2AABB2Dを作る
	//! @param [in] rBase    元となるgt2AABB2D
	//! @param [in] rBasePos 元となる現在位置
	//! @param [in] rVel     rBasePosを原点とした運動ベクトル
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void MakeMoveAABB(const gt2AABB2D& rBase, const gt2Vector2 &rBasePos, const gt2Vector2 &rVel)
	{
		gt2AABB2D tmp;

		vMin = rBase.vMin + rBasePos;
		vMax = rBase.vMax + rBasePos;
		tmp = *this;
		tmp.vMin += rVel;
		tmp.vMax += rVel;
		vMin.SetMin(tmp.vMin);
		vMax.SetMax(tmp.vMax);
	}
	//-----------------------------------------------------------------------------------
	//! @brief 運動ベクトル入れた大きさがかわるgt2AABB2D
	//! @param [in] rBase    元となる円
	//! @param [in] rBasePos 元となる現在位置
	//! @param [in] rVel     rBasePosを原点とした運動ベクトル
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void MakeMoveAABB(const gt2Circle2& rBase, const gt2Vector2 &rBasePos, const gt2Vector2 &rVel)
	{
		gt2AABB2D tmp;

		tmp.vMax.x = rBase.c.x + rBase.r;
		tmp.vMax.y = rBase.c.y + rBase.r;
		tmp.vMin.x = rBase.c.x - rBase.r;
		tmp.vMin.y = rBase.c.y - rBase.r;

		this->MakeMoveAABB(tmp, rBasePos, rVel);
	}
	//-----------------------------------------------------------------------------------
	//! @brief  対象位置に、各軸の長さだけのgt2AABB2Dから移動した時のgt2AABB2Dを作る
	//! @param [in] rSize    元となる各軸のサイズだけ使用するgt2AABB2D
	//! @param [in] rBasePos 元となる現在位置
	//! @param [in] rVel     rBasePosを原点とした運動ベクトル
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void MakeMovePoint(const gt2AABB2D& rSize, const gt2Vector2 &rBasePos, const gt2Vector2 &rVel)
	{
		this->MakeMovePoint((rSize.vMax - rSize.vMin) * 0.5f, rBasePos, rVel);
	}
	//-----------------------------------------------------------------------------------
	//! @brief   対象位置に、各軸の長さだけのgt2AABB2Dから移動した時のgt2AABB2Dを作る
	//! @param [in] rL       gt2AABB2Dの各軸の半分の長さ
	//! @param [in] rBasePos 元となる現在位置
	//! @param [in] rVel     rBasePosを原点とした運動ベクトル
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void MakeMovePoint(const gt2Vector2& rL, const gt2Vector2 &rBasePos, const gt2Vector2 &rVel)
	{
		this->InitMinMax();
		vMin.SetMin(rBasePos - rL);
		vMax.SetMax(rBasePos + rL);
		vMin.SetMin((rBasePos + rVel) - rL);
		vMax.SetMax((rBasePos + rVel) + rL);
	}
	//-----------------------------------------------------------------------------------
	//! @brief 2つの頂点からgt2AABB2Dを作成
	//! @param [in] a 頂点A
	//! @param [in] rvB 頂点B
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void MakeFromeSegment(const gt2Vector2& a, const gt2Vector2& rvB)
	{
		vMin.InitMin();
		vMax.InitMax();
		vMin.SetMin(a); vMin.SetMin(rvB);
		vMax.SetMax(a); vMax.SetMax(rvB);
	}
	//-----------------------------------------------------------------------------------
	//! @brief 自身のgt2AABB2Dを新たなgt2AABB2Dの最大、最小の要素値を元に作り直す
	//! @param [in] aabb 対象とするgt2AABB2D
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void ReMakeMinMax(const gt2AABB2D& aabb)
	{
		vMin.SetMin(aabb.vMin);
		vMax.SetMax(aabb.vMax);
	}

	//-----------------------------------------------------------------------------------
	//! @brief 自身のgt2AABB2Dを新たなgt2AABB2Dを足して拡張させる
	//! @param [in] aabb 対象とするgt2AABB2D
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void ReMakeExtension(const gt2AABB2D& aabb)
	{
		gt2Vector2 vLen;
		vLen = aabb.GetLengthFromCenter();
		vMin.x -= vLen.x; vMin.y -= vLen.y;
		vMax.x += vLen.x; vMax.y += vLen.y;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 自身のgt2AABB2Dの四隅(頂点)を長さR分だけ拡張する
	//! @param [in] fR 半径
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void ReMakeExtension(float fR)
	{
		vMin.x -= fR; vMin.y -= fR;
		vMax.x += fR; vMax.y += fR;
	}
	//-----------------------------------------------------------------------------------
	//! @brief gt2AABB2Dが平面と交差しているか？
	//! @param [in] rPlane 対象平面
	//! @return 0の場合、交差している。-1の場合、裏側にある。1の場合、表側にある
	//-----------------------------------------------------------------------------------
	inline int  AABB_Plane(const gt2Plane2 &rPlane) const
	{
		gt2Vector2 vC = (vMax + vMin) * 0.5f;
		gt2Vector2 vE = vMax - vC;

		float fR = vE.x * fabs(rPlane.vNormal.x) + vE.y * fabs(rPlane.vNormal.y);
		float fS = rPlane.vNormal.Dot(vC) - rPlane.distance;

		if (fabs(fS) <= fR){
			// 交差している
			return 0;
		}
		else if (fS < 0){
			// 裏側にある
			return -1;
		}

		// 表側にある
		return 1;
	}
};

