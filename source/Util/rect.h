/*!
* @brief MetalCube.h�t�@�C��������Ăяo�����̂ŁA�ق�����Ăяo���Ȃ��悤�ɁI
*  ����́A�Z�a�������\���̂��g�����߂̂���
* @author kaoken
* @date 2014/03/19 �쐬�J�n
*/
#pragma once
#if defined(_WIN32) || defined(_WIN64)
#include <windef.h>
#include <D2d1.h>
#endif


struct GT2RectF;

#define FLIP_HORIZONTAL	0x01	// ���E���]
#define FLIP_VERTICAL	0x02	// �㉺���]

//------------------------------------------------------------
//! @brief xxx�^��rect�\���̃e���v���[�g
//------------------------------------------------------------
template<typename _Type, class _Class>
struct mcRectTemplate
{
	_Type    left;		//!< ��
	_Type    top;		//!< ��
	_Type    right;		//!< ��
	_Type    bottom;	//!< ��

	//-----------------------------------------------------------------------------------
	//! @brief �R���X�g���N�^
	//-----------------------------------------------------------------------------------
	mcRectTemplate() { left = top = right = bottom = 0; }
	//-----------------------------------------------------------------------------------
	//! @brief �R���X�g���N�^
	//-----------------------------------------------------------------------------------
	mcRectTemplate(const _Class &rC) { Set(rC); }
	//-----------------------------------------------------------------------------------
	//! @brief �R���X�g���N�^
	//! left,top,right,bottom�̏��ԂŁA�ϐ����Z�b�g����
	//! @param [in]  l left
	//! @param [in]  t top
	//! @param [in]  r right
	//! @param [in]  b bottom
	//-----------------------------------------------------------------------------------
	mcRectTemplate(_Type l, _Type t, _Type r, _Type b) { Set(l, t, r, b); }
	//-----------------------------------------------------------------------------------
	//! @brief left,top,right,bottom�̏��ԂŁA�ϐ����Z�b�g����
	//! @param [in]  rC _Class
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void Set(const _Class &rC)
	{
		Set(rC.left, rC.top, rC.right, rC.bottom);
	}
	//-----------------------------------------------------------------------------------
	//! @brief left,top,right,bottom�̏��ԂŁA�ϐ����Z�b�g����
	//! @param [in]  l left
	//! @param [in]  t top
	//! @param [in]  r right
	//! @param [in]  b bottom
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void Set(_Type l, _Type t, _Type r, _Type b)
	{
		left = l;
		top = t;
		right = r;
		bottom = b;
	}
	//-----------------------------------------------------------------------------------
	//! @brief x,y,��,�����̏��ԂŁA�ϐ����Z�b�g����B�t���O�ɂ���č��E�㉺�t�ɂ��邱�Ƃ��ł���
	//! @param [in]  x    x���W
	//! @param [in]  y    y���p
	//! @param [in]  w    ��
	//! @param [in]  h    ����
	//! @param [in]  flg  �㉺���E���邩���肷��t���O�B�ȗ����Ȃɂ����Ȃ�
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void SetXYWH(_Type x, _Type y, _Type w, _Type h, int flg = 0)
	{
		int n;
		X(x); Y(y); Width(w); Heith(h);
		if (flg & FLIP_VERTICAL) {
			// �㉺���]
			n = top;
			top = bottom;
			bottom = n;
		}
		if (flg & FLIP_HORIZONTAL) {
			// ���E���]
			n = left;
			left = right;
			right = n;
		}
	}
	//-----------------------------------------------------------------------------------
	//! @brief �ʒu�ƕ�������AGT2Rect�\���ɕϊ�����A�t���O�ɂ���č��E�㉺�t�ɂ��邱�Ƃ��ł���
	//!  src�����ɃN���b�s���O������
	//! @param [out] rRc GT2Rect�̎Q�Ƒ́A�����ɕϊ����GT2Rect���i�[����
	//! @param [in]  x      ���WX
	//! @param [in]  y      ���WY
	//! @param [in]  width  ��
	//! @param [in]  height ����
	//! @param [in]  flg    �㉺���E���邩���肷��t���O
	//! @return �N���b�s���O���ꂽ�ꍇ��true��Ԃ��B
	//-----------------------------------------------------------------------------------
	inline bool GetClippingRect(_Class &rRc, _Type x, _Type y, _Type width, _Type height, int flg = 0) const
	{
		return GetClippingRect(&rRc, x, y, width, height, flg);
	}
	//-----------------------------------------------------------------------------------
	//! @brief �ʒu�ƕ�������AGT2Rect�\���ɕϊ�����A�t���O�ɂ���č��E�㉺�t�ɂ��邱�Ƃ��ł���
	//!  src�����ɃN���b�s���O������
	//! @param [out] pRc GT2Rect�̃|�C���^�A�����ɕϊ����GT2Rect���i�[����
	//! @param [in]  x      ���WX
	//! @param [in]  y      ���WY
	//! @param [in]  width  ��
	//! @param [in]  height ����
	//! @param [in]  flg    �㉺���E���邩���肷��t���O
	//! @return �N���b�s���O���ꂽ�ꍇ��true��Ԃ��B
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
			// �㉺���]
			n = pRc->top;
			pRc->top = pRc->bottom;
			pRc->bottom = n;
		}
		if (flg & FLIP_HORIZONTAL) {
			// ���E���]
			n = pRc->left;
			pRc->left = pRc->right;
			pRc->right = n;
		}

		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief �ʒu�ƕ�������AGT2Rect�\���ɕϊ�����A�t���O�ɂ���č��E�㉺�t�ɂ��邱�Ƃ��ł���
	//!  src�����ɃN���b�s���O������
	//! @param [in]  prcSrc �Ώ۔͈�
	//! @param [in,out] rRc    GT2Rect�̎Q�Ƒ́A�����ɕϊ����GT2Rect���i�[����
	//! @param [in,out] rRc2   GT2Rect�̎Q�Ƒ́A�����ɕϊ����GT2Rect���i�[����
	//! @param [in]  x      ���WX
	//! @param [in]  y      ���WY
	//! @param [in]  width  ��
	//! @param [in]  height ����
	//! @param [in]  flg    �㉺���E���邩���肷��t���O
	//! @return �N���b�s���O���ꂽ�ꍇ��true��Ԃ��B
	//-----------------------------------------------------------------------------------
	inline bool GetClippingRect2(const _Class &src, _Class &rRc, _Class &rRc2, _Type x, _Type y, _Type width, _Type height, int flg = 0) const
	{
		return GetClippingRect2(src, &rRc, &rRc2, x, y, width, height, flg);
	}
	//-----------------------------------------------------------------------------------
	//! @brief �ʒu�ƕ�������AGT2Rect�\���ɕϊ�����A�t���O�ɂ���č��E�㉺�t�ɂ��邱�Ƃ��ł���
	//!  src�����ɃN���b�s���O������
	//! @param [in]  prcSrc �Ώ۔͈�
	//! @param [out] pRc    GT2Rect�̃|�C���^�A�����ɕϊ����GT2Rect���i�[����
	//! @param [in,out] pRc2   GT2Rect�̃|�C���^�A�����ɕϊ����GT2Rect���i�[����
	//! @param [in]  x      ���WX
	//! @param [in]  y      ���WY
	//! @param [in]  width  ��
	//! @param [in]  height ����
	//! @param [in]  flg    �㉺���E���邩���肷��t���O
	//! @return �N���b�s���O���ꂽ�ꍇ��true��Ԃ��B
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
			// �㉺���]
			n = pRc->top;
			pRc->top = pRc->bottom;
			pRc->bottom = n;
		}
		if (flg & FLIP_HORIZONTAL) {
			// ���E���]
			n = pRc->left;
			pRc->left = pRc->right;
			pRc->right = n;
		}

		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief X���W��Ԃ�
	//! @return X���W��Ԃ�
	//-----------------------------------------------------------------------------------
	inline _Type X() const { return left; }
	//-----------------------------------------------------------------------------------
	//! @brief Y���W��Ԃ�
	//! @return Y���W��Ԃ�
	//-----------------------------------------------------------------------------------
	inline _Type Y() const { return top; }
	//-----------------------------------------------------------------------------------
	//! @brief ����Ԃ�
	//! @return ����Ԃ�
	//-----------------------------------------------------------------------------------
	inline _Type Width() const { return right - left + 1; }
	//-----------------------------------------------------------------------------------
	//! @brief ������Ԃ�
	//! @return ������Ԃ�
	//-----------------------------------------------------------------------------------
	inline _Type Heith() const { return bottom - top + 1; }
	//-----------------------------------------------------------------------------------
	//! @brief x���W���Z�b�g����
	//! @param [in]  x x���W
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void X(_Type x) { left = x; }
	//-----------------------------------------------------------------------------------
	//! @brief Y���W���Z�b�g����
	//! @param [in]  y Y���W
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void Y(_Type y) { top = y; }
	//-----------------------------------------------------------------------------------
	//! @brief �����Z�b�g����
	//! @param [in]  w ��
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void Width(_Type w) { right = w + left - 1; }
	//-----------------------------------------------------------------------------------
	//! @brief �������Z�b�g����
	//! @param [in]  h ����
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void Heith(_Type h) { bottom = h + top - 1; }

	//! @name ������Z�q
	//@{
	_Class &operator =(const _Class &other)
	{
		this->Set(other);
		return *this;
	}
	//@}

	//! @name ��r���Z�q
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
//! @brief long�^��rect�\����
//------------------------------------------------------------
struct GT2Rect : public mcRectTemplate<long, GT2Rect>
{
	GT2Rect() { mcRectTemplate<long, GT2Rect>(); }
	GT2Rect(long l, long t, long r, long b) { mcRectTemplate<long, GT2Rect>(l, t, r, b); }
	//! @name ������Z�q
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
//! @brief float�^��rect�\����
//------------------------------------------------------------
struct GT2RectF : public mcRectTemplate<float, GT2RectF>
{
	GT2RectF() { mcRectTemplate<float, GT2RectF>(); }
	GT2RectF(float l, float t, float r, float b) { mcRectTemplate<float, GT2RectF>(l, t, r, b); }
	//! @name ������Z�q
	//@{

	//-----------------------------------------------------------------------------------
	//! @brief ������Z�q�FGT2RectF��GT2Rect�ɕϊ����ēn��
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
//! @brief ������Z�q�FGT2RectF��GT2Rect�ɕϊ����ēn��
//-----------------------------------------------------------------------------------
inline GT2Rect& GT2Rect::operator = (const GT2RectF& v)
{
	this->bottom = (long)v.bottom;
	this->left = (long)v.left;
	this->right = (long)v.right;
	this->top = (long)v.top;
	return *this;
}
