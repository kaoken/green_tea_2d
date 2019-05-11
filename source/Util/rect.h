/*!
* @brief MetalCube.hファイル内から呼び出されるので、ほかから呼び出さないように！
*  これは、短径を扱う構造体を使うためのもの
* @author kaoken
* @date 2014/03/19 作成開始
*/
#pragma once
#if defined(_WIN32) || defined(_WIN64)
#include <windef.h>
#include <D2d1.h>
#endif


struct GT2RectF;

#define FLIP_HORIZONTAL	0x01	// 左右反転
#define FLIP_VERTICAL	0x02	// 上下反転

//------------------------------------------------------------
//! @brief xxx型のrect構造体テンプレート
//------------------------------------------------------------
template<typename _Type, class _Class>
struct mcRectTemplate
{
	_Type    left;		//!< 左
	_Type    top;		//!< 上
	_Type    right;		//!< 左
	_Type    bottom;	//!< 下

	//-----------------------------------------------------------------------------------
	//! @brief コンストラクタ
	//-----------------------------------------------------------------------------------
	mcRectTemplate() { left = top = right = bottom = 0; }
	//-----------------------------------------------------------------------------------
	//! @brief コンストラクタ
	//-----------------------------------------------------------------------------------
	mcRectTemplate(const _Class &rC) { Set(rC); }
	//-----------------------------------------------------------------------------------
	//! @brief コンストラクタ
	//! left,top,right,bottomの順番で、変数をセットする
	//! @param [in]  l left
	//! @param [in]  t top
	//! @param [in]  r right
	//! @param [in]  b bottom
	//-----------------------------------------------------------------------------------
	mcRectTemplate(_Type l, _Type t, _Type r, _Type b) { Set(l, t, r, b); }
	//-----------------------------------------------------------------------------------
	//! @brief left,top,right,bottomの順番で、変数をセットする
	//! @param [in]  rC _Class
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void Set(const _Class &rC)
	{
		Set(rC.left, rC.top, rC.right, rC.bottom);
	}
	//-----------------------------------------------------------------------------------
	//! @brief left,top,right,bottomの順番で、変数をセットする
	//! @param [in]  l left
	//! @param [in]  t top
	//! @param [in]  r right
	//! @param [in]  b bottom
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void Set(_Type l, _Type t, _Type r, _Type b)
	{
		left = l;
		top = t;
		right = r;
		bottom = b;
	}
	//-----------------------------------------------------------------------------------
	//! @brief x,y,幅,高さの順番で、変数をセットする。フラグによって左右上下逆にすることもできる
	//! @param [in]  x    x座標
	//! @param [in]  y    y座用
	//! @param [in]  w    幅
	//! @param [in]  h    高さ
	//! @param [in]  flg  上下左右するか決定するフラグ。省略時なにもしない
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void SetXYWH(_Type x, _Type y, _Type w, _Type h, int flg = 0)
	{
		int n;
		X(x); Y(y); Width(w); Heith(h);
		if (flg & FLIP_VERTICAL) {
			// 上下反転
			n = top;
			top = bottom;
			bottom = n;
		}
		if (flg & FLIP_HORIZONTAL) {
			// 左右反転
			n = left;
			left = right;
			right = n;
		}
	}
	//-----------------------------------------------------------------------------------
	//! @brief 位置と幅高から、GT2Rect構造に変換する、フラグによって左右上下逆にすることもできる
	//!  srcを元にクリッピングをする
	//! @param [out] rRc GT2Rectの参照体、ここに変換後のGT2Rectを格納する
	//! @param [in]  x      座標X
	//! @param [in]  y      座標Y
	//! @param [in]  width  幅
	//! @param [in]  height 高さ
	//! @param [in]  flg    上下左右するか決定するフラグ
	//! @return クリッピングされた場合はtrueを返す。
	//-----------------------------------------------------------------------------------
	inline bool GetClippingRect(_Class &rRc, _Type x, _Type y, _Type width, _Type height, int flg = 0) const
	{
		return GetClippingRect(&rRc, x, y, width, height, flg);
	}
	//-----------------------------------------------------------------------------------
	//! @brief 位置と幅高から、GT2Rect構造に変換する、フラグによって左右上下逆にすることもできる
	//!  srcを元にクリッピングをする
	//! @param [out] pRc GT2Rectのポインタ、ここに変換後のGT2Rectを格納する
	//! @param [in]  x      座標X
	//! @param [in]  y      座標Y
	//! @param [in]  width  幅
	//! @param [in]  height 高さ
	//! @param [in]  flg    上下左右するか決定するフラグ
	//! @return クリッピングされた場合はtrueを返す。
	//-----------------------------------------------------------------------------------
	inline bool GetClippingRect(_Class *pRc, _Type x, _Type y, _Type width, _Type height, int flg = 0) const
	{
		_Type n;
		pRc->Set(x, y, x + width, y + height);

		if (left >= pRc->right) {
			pRc->Set(0, 0, 0, 0);
			return false;
		}
		else if (right <= pRc->left) {
			pRc->Set(0, 0, 0, 0);
			return false;
		}
		else if (top >= pRc->bottom) {
			pRc->Set(0, 0, 0, 0);
			return false;
		}
		else if (bottom <= pRc->top) {
			pRc->Set(0, 0, 0, 0);
			return false;
		}

		if (top > pRc->top)
			pRc->top += top - pRc->top;

		if (bottom < pRc->bottom)
			pRc->top -= pRc->bottom - bottom;

		if (left > pRc->left)
			pRc->left += left - pRc->left;

		if (right < pRc->right)
			pRc->right -= pRc->right - right;


		if (flg & FLIP_VERTICAL) {
			// 上下反転
			n = pRc->top;
			pRc->top = pRc->bottom;
			pRc->bottom = n;
		}
		if (flg & FLIP_HORIZONTAL) {
			// 左右反転
			n = pRc->left;
			pRc->left = pRc->right;
			pRc->right = n;
		}

		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 位置と幅高から、GT2Rect構造に変換する、フラグによって左右上下逆にすることもできる
	//!  srcを元にクリッピングをする
	//! @param [in]  prcSrc 対象範囲
	//! @param [in,out] rRc    GT2Rectの参照体、ここに変換後のGT2Rectを格納する
	//! @param [in,out] rRc2   GT2Rectの参照体、ここに変換後のGT2Rectを格納する
	//! @param [in]  x      座標X
	//! @param [in]  y      座標Y
	//! @param [in]  width  幅
	//! @param [in]  height 高さ
	//! @param [in]  flg    上下左右するか決定するフラグ
	//! @return クリッピングされた場合はtrueを返す。
	//-----------------------------------------------------------------------------------
	inline bool GetClippingRect2(const _Class &src, _Class &rRc, _Class &rRc2, _Type x, _Type y, _Type width, _Type height, int flg = 0) const
	{
		return GetClippingRect2(src, &rRc, &rRc2, x, y, width, height, flg);
	}
	//-----------------------------------------------------------------------------------
	//! @brief 位置と幅高から、GT2Rect構造に変換する、フラグによって左右上下逆にすることもできる
	//!  srcを元にクリッピングをする
	//! @param [in]  prcSrc 対象範囲
	//! @param [out] pRc    GT2Rectのポインタ、ここに変換後のGT2Rectを格納する
	//! @param [in,out] pRc2   GT2Rectのポインタ、ここに変換後のGT2Rectを格納する
	//! @param [in]  x      座標X
	//! @param [in]  y      座標Y
	//! @param [in]  width  幅
	//! @param [in]  height 高さ
	//! @param [in]  flg    上下左右するか決定するフラグ
	//! @return クリッピングされた場合はtrueを返す。
	//-----------------------------------------------------------------------------------
	inline bool GetClippingRect2(const _Class &src, _Class *pRc, _Class *pRc2, _Type x, _Type y, _Type width, _Type height, int flg = 0) const
	{
		_Type n;

		pRc->Set(x, y, x + width, y + height);

		if (left >= pRc->right) {
			pRc->Set(0, 0, 0, 0);
			return false;
		}
		else if (right <= pRc->left) {
			pRc->Set(0, 0, 0, 0);
			return false;
		}
		else if (top >= pRc->bottom) {
			pRc->Set(0, 0, 0, 0);
			return false;
		}
		else if (bottom <= pRc->top) {
			pRc->Set(0, 0, 0, 0);
			return false;
		}

		if (top > pRc->top) {
			n = top - pRc->top;
			pRc->top += n;
			pRc2->top += n;
		}
		if (bottom < pRc->bottom) {
			n = pRc->bottom - bottom;
			pRc->bottom -= n;
			pRc2->bottom -= n;
		}
		if (left > pRc->left) {
			n = left - pRc->left;
			pRc->left += n;
			pRc2->left += n;
		}
		if (right < pRc->right) {
			n = pRc->right - right;
			pRc->right -= n;
			pRc2->right -= n;
		}

		if (flg & FLIP_VERTICAL) {
			// 上下反転
			n = pRc->top;
			pRc->top = pRc->bottom;
			pRc->bottom = n;
		}
		if (flg & FLIP_HORIZONTAL) {
			// 左右反転
			n = pRc->left;
			pRc->left = pRc->right;
			pRc->right = n;
		}

		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief X座標を返す
	//! @return X座標を返す
	//-----------------------------------------------------------------------------------
	inline _Type X() const { return left; }
	//-----------------------------------------------------------------------------------
	//! @brief Y座標を返す
	//! @return Y座標を返す
	//-----------------------------------------------------------------------------------
	inline _Type Y() const { return top; }
	//-----------------------------------------------------------------------------------
	//! @brief 幅を返す
	//! @return 幅を返す
	//-----------------------------------------------------------------------------------
	inline _Type Width() const { return right - left + 1; }
	//-----------------------------------------------------------------------------------
	//! @brief 高さを返す
	//! @return 高さを返す
	//-----------------------------------------------------------------------------------
	inline _Type Heith() const { return bottom - top + 1; }
	//-----------------------------------------------------------------------------------
	//! @brief x座標をセットする
	//! @param [in]  x x座標
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void X(_Type x) { left = x; }
	//-----------------------------------------------------------------------------------
	//! @brief Y座標をセットする
	//! @param [in]  y Y座標
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void Y(_Type y) { top = y; }
	//-----------------------------------------------------------------------------------
	//! @brief 幅をセットする
	//! @param [in]  w 幅
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void Width(_Type w) { right = w + left - 1; }
	//-----------------------------------------------------------------------------------
	//! @brief 高さをセットする
	//! @param [in]  h 高さ
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void Heith(_Type h) { bottom = h + top - 1; }

	//! @name 代入演算子
	//@{
	_Class &operator =(const _Class &other)
	{
		this->Set(other);
		return *this;
	}
	//@}

	//! @name 比較演算子
	//@{
	inline bool operator == (const _Class& r) const
	{
		return left == r.left && right == r.right && top == r.top && bottom == r.bottom;
	}
	inline bool operator != (const _Class& r) const
	{
		return left != r.left || right != r.right || top != r.top || bottom != r.bottom;
	}
	//@}
};

//------------------------------------------------------------
//! @brief long型のrect構造体
//------------------------------------------------------------
struct GT2Rect : public mcRectTemplate<long, GT2Rect>
{
	GT2Rect() { mcRectTemplate<long, GT2Rect>(); }
	GT2Rect(long l, long t, long r, long b) { mcRectTemplate<long, GT2Rect>(l, t, r, b); }
	//! @name 代入演算子
	//@{

#if defined(_WIN32) || defined(_WIN64)
	inline D2D1_RECT_F GetD2D1_RECT_F() const
	{
		D2D1_RECT_F v;
		v.top = (FLOAT)this->top;
		v.left = (FLOAT)this->left;
		v.bottom = (FLOAT)this->bottom;
		v.right = (FLOAT)this->right;
		return v;
	}
	inline GT2Rect& operator = (const D2D1_RECT_F& v)
	{
		this->top = (long)v.top;
		this->left = (long)v.left;
		this->bottom = (long)v.bottom;
		this->right = (long)v.right;
		return *this;
	}
	inline GT2Rect& operator = (const RECT& v)
	{
		*this = *((GT2Rect*)&v);
		return *this;
	}
#endif
	inline GT2Rect& operator = (const GT2RectF& v);
	//@}
};
//------------------------------------------------------------
//! @brief float型のrect構造体
//------------------------------------------------------------
struct GT2RectF : public mcRectTemplate<float, GT2RectF>
{
	GT2RectF() { mcRectTemplate<float, GT2RectF>(); }
	GT2RectF(float l, float t, float r, float b) { mcRectTemplate<float, GT2RectF>(l, t, r, b); }
	//! @name 代入演算子
	//@{

	//-----------------------------------------------------------------------------------
	//! @brief 代入演算子：GT2RectFをGT2Rectに変換して渡す
	//-----------------------------------------------------------------------------------
#if defined(_WIN32) || defined(_WIN64)
	inline GT2RectF& operator = (const D2D1_RECT_F& v)
	{
		this->top = (FLOAT)v.top;
		this->left = (FLOAT)v.left;
		this->bottom = (FLOAT)v.bottom;
		this->right = (FLOAT)v.right;
		return *this;
	}
	inline GT2RectF& operator = (const RECT& v)
	{
		this->top = (FLOAT)v.top;
		this->left = (FLOAT)v.left;
		this->bottom = (FLOAT)v.bottom;
		this->right = (FLOAT)v.right;
		return *this;
	}
#endif
	inline GT2RectF& operator = (const GT2Rect& v)
	{
		this->bottom = (float)v.bottom;
		this->left = (float)v.left;
		this->right = (float)v.right;
		this->top = (float)v.top;
		return *this;
	}
	//@}
};

//-----------------------------------------------------------------------------------
//! @brief 代入演算子：GT2RectFをGT2Rectに変換して渡す
//-----------------------------------------------------------------------------------
inline GT2Rect& GT2Rect::operator = (const GT2RectF& v)
{
	this->bottom = (long)v.bottom;
	this->left = (long)v.left;
	this->right = (long)v.right;
	this->top = (long)v.top;
	return *this;
}
