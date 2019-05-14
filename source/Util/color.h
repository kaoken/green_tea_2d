/*! @file  color.h
* @brief �F
* @author kaoken
* @date 2014/03/19 �쐬�J�n
*/
#pragma once

#include <Core/greenTea2D.h>


struct gt2ColorF
{
public:
	union
	{
		struct
		{
			float r;	//!< ���b�h
			float g;	//!< �O���[��
			float b;	//!< �u���[
			float a;	//!< �A���t�@
		};
		float v[4];		//!< �e�F��\���z��[0=���b�h, 1=�O���[��, 2=�u���[, 3=�A���t�@]
	};
public:
		

	//-------------------------------------------------------------------
	//! @brief �R���X�g���N�^ rgb=0,a=1.0
	//-------------------------------------------------------------------
	gt2ColorF()
	{
		r = g = b = 0.0f;
		a = 1.0f;
	}
	//-------------------------------------------------------------------
	//! @brief �R���X�g���N�^
	//! @param [in] dw �����Ȃ�32�r�b�g�����l�ŏ�����
	//-------------------------------------------------------------------
	gt2ColorF(uint32_t dw)
	{
		Set(dw);
	}

	//-------------------------------------------------------------------
	//! @brief �R���X�g���N�^
	//! @param [in] pf 32�r�b�g����������4�v�f���܂ރ|�C���^�ŏ�����
	//-------------------------------------------------------------------
	gt2ColorF(const float* pf)
	{
#ifdef MC_DEBUG
		if (!pf)
			return;
#endif
		Set(pf[0], pf[1], pf[2], pf[3]);
	}

	//-------------------------------------------------------------------
	//! @brief �R���X�g���N�^
	//! @param [in] fr 32�r�b�g���������� ���b�h
	//! @param [in] fg 32�r�b�g���������� �O���[��
	//! @param [in] fb 32�r�b�g���������� �u���[
	//! @param [in] fa 32�r�b�g���������� �A���t�@
	//-------------------------------------------------------------------
	inline gt2ColorF(float fr, float fg, float fb, float fa)
	{
		Set(fr,fg,fb,fa);
	}

	//-------------------------------------------------------------------
	//! @brief �R���X�g���N�^
	//! @param [in] fr 32�r�b�g���������� ���b�h
	//! @param [in] fg 32�r�b�g���������� �O���[��
	//! @param [in] fb 32�r�b�g���������� �u���[
	//! @param [in] fa 32�r�b�g���������� �A���t�@
	//-------------------------------------------------------------------
	inline gt2ColorF(const gt2ColorF& color)
	{
		this->Set(color);
	}

	//-------------------------------------------------------------------
	//! @brief �R���X�g���N�^
	//! @param [in] nR ����(0�`255)) ���b�h
	//! @param [in] nG ����(0�`255)) �O���[��
	//! @param [in] nB ����(0�`255)) �u���[
	//! @param [in] nA ����(0�`255)) �A���t�@
	//-------------------------------------------------------------------
	inline gt2ColorF(int red, int green, int blue, int alpha)
	{
		this->Set(red, green, blue, alpha);
	}

	//-------------------------------------------------------------------
	//! @brief gt2ColorF���Z�b�g����
	//! @param [in] color gt2ColorF
	//-------------------------------------------------------------------
	inline void Set(const gt2ColorF& color)
	{
		*this = color;
	}

	//-------------------------------------------------------------------
	//! @brief �����Ȃ�32�r�b�g�����l�ŐF���Z�b�g����
	//! @param [in] dw �����Ȃ�32�r�b�g�����l�ŏ�����
	//-------------------------------------------------------------------
	inline void Set(uint32_t dw)
	{
		const float f = 1.0f / 255.0f;
		r = f * (float)(uint8_t)(dw >> 16);
		g = f * (float)(uint8_t)(dw >> 8);
		b = f * (float)(uint8_t)(dw >> 0);
		a = f * (float)(uint8_t)(dw >> 24);
	}
	//-------------------------------------------------------------------
	//! @brief �F���Z�b�g
	//! @param [in] fr 32�r�b�g���������� ���b�h
	//! @param [in] fg 32�r�b�g���������� �O���[��
	//! @param [in] fb 32�r�b�g���������� �u���[
	//! @param [in] fa 32�r�b�g���������� �A���t�@
	//-------------------------------------------------------------------
	inline void Set(float fr, float fg, float fb, float fa)
	{
		r = fr;
		g = fg;
		b = fb;
		a = fa;
	}
	//-------------------------------------------------------------------
	//! @brief �F���Z�b�g
	//! @param [in] nR �����Ȃ�32�r�b�g������ ���b�h
	//! @param [in] nG �����Ȃ�32�r�b�g������ �O���[��
	//! @param [in] nB �����Ȃ�32�r�b�g������ �u���[
	//! @param [in] nA �����Ȃ�32�r�b�g������ �A���t�@
	//-------------------------------------------------------------------
	inline void Set(int nR, int nG, int nB, int nA)
	{
		a = (float)(nA & 0x00FF) / 255.0f;
		r = (float)(nR & 0x00FF) / 255.0f;
		g = (float)(nG & 0x00FF) / 255.0f;
		b = (float)(nB & 0x00FF) / 255.0f;
	}


	//-------------------------------------------------------------------
	//! @brief �����Ȃ�32�r�b�g�����̒l�ŐF��Ԃ��B
	//! @return �����Ȃ�32�r�b�g�����̒l�ŐF��Ԃ��B
	//-------------------------------------------------------------------
	inline uint32_t GetU32() const
	{
		uint32_t dwR = r >= 1.0f ? 0xff : r <= 0.0f ? 0x00 : (uint32_t)(r * 255.0f + 0.5f);
		uint32_t dwG = g >= 1.0f ? 0xff : g <= 0.0f ? 0x00 : (uint32_t)(g * 255.0f + 0.5f);
		uint32_t dwB = b >= 1.0f ? 0xff : b <= 0.0f ? 0x00 : (uint32_t)(b * 255.0f + 0.5f);
		uint32_t dwA = a >= 1.0f ? 0xff : a <= 0.0f ? 0x00 : (uint32_t)(a * 255.0f + 0.5f);

		return (dwA << 24) | (dwR << 16) | (dwG << 8) | dwB;
	}

	//++++++++++++++++++++++++++++++++++
	//! @name �L���X�g
	//++++++++++++++++++++++++++++++++++
	//@{
	//-------------------------------------------------------------------
	//! @brief �L���X�g�Fuint32_t
	//-------------------------------------------------------------------
	inline operator uint32_t () const
	{
		return GetU32();
	}
	//-------------------------------------------------------------------
	//! @brief �L���X�g�Ffloat
	//-------------------------------------------------------------------
	inline operator float * ()
	{
		return (float *)&r;
	}
	//-------------------------------------------------------------------
	//! @brief const �L���X�g�Ffloat
	//-------------------------------------------------------------------
	inline operator const float * () const
	{
		return (const float *)&r;
	}
	//@}


	//++++++++++++++++++++++++++++++++++
	//! @name ������Z�q
	//++++++++++++++++++++++++++++++++++
	//@{
	inline gt2ColorF& operator = (const gt2ColorF& c)
	{
		r = c.r;
		g = c.g;
		b = c.b;
		a = c.a;
		return *this;
	}
	inline gt2ColorF& operator = (const mcDWORD& c)
	{
		*this = gt2ColorF(c);
		return *this;
	}
	inline gt2ColorF& operator += (const gt2ColorF& c)
	{
		r += c.r;
		g += c.g;
		b += c.b;
		a += c.a;
		return *this;
	}

	inline gt2ColorF& operator -= (const gt2ColorF& c)
	{
		r -= c.r;
		g -= c.g;
		b -= c.b;
		a -= c.a;
		return *this;
	}

	inline gt2ColorF& operator *= (const gt2ColorF &rC)
	{
		r *= rC.r;
		g *= rC.g;
		b *= rC.b;
		a *= rC.a;
		return *this;
	}

	inline gt2ColorF& operator /= (const gt2ColorF& c)
	{
		if (c.r == 0.0f) r = 0.0f; else r /= c.r;
		if (c.g == 0.0f) g = 0.0f; else g /= c.g;
		if (c.b == 0.0f) b = 0.0f; else b /= c.b;
		if (c.a == 0.0f) a = 0.0f; else a /= c.a;
		return *this;
	}

	inline gt2ColorF& operator *= (float f)
	{
		r *= f;
		g *= f;
		b *= f;
		a *= f;
		return *this;
	}

	inline gt2ColorF& operator /= (float f)
	{
		float fInv = f==0.0f ? 0.0f : (1.0f / f);
		r *= fInv;
		g *= fInv;
		b *= fInv;
		a *= fInv;
		return *this;
	}
	//@}


	//++++++++++++++++++++++++++++++++++
	//! @name �P�����Z�q
	//++++++++++++++++++++++++++++++++++
	//@{
	inline gt2ColorF operator + () const
	{
		return *this;
	}

	inline gt2ColorF operator - () const
	{
		return gt2ColorF(-r, -g, -b, -a);
	}
	//@}


	//++++++++++++++++++++++++++++++++++
	//! @name �񍀉��Z�q
	//++++++++++++++++++++++++++++++++++
	//@{
	inline gt2ColorF operator + (const gt2ColorF& c) const
	{
		return gt2ColorF(r + c.r, g + c.g, b + c.b, a + c.a);
	}

	inline gt2ColorF operator - (const gt2ColorF& c) const
	{
		return gt2ColorF(r - c.r, g - c.g, b - c.b, a - c.a);
	}
	inline gt2ColorF operator * (const gt2ColorF &rC) const
	{
		gt2ColorF t = *this;
		t *= rC;
		return t;
	}
	inline gt2ColorF operator / (const gt2ColorF& c) const
	{
		gt2ColorF t = *this;
		t /= c;
		return t;
	}
	inline gt2ColorF operator * (float f) const
	{
		return gt2ColorF(r * f, g * f, b * f, a * f);
	}
	inline gt2ColorF operator / (float f) const
	{
		float fInv = f == 0.0f ? 0.0f : (1.0f / f);
		return gt2ColorF(r * fInv, g * fInv, b * fInv, a * fInv);
	}
	inline friend gt2ColorF operator * (float f, const gt2ColorF& c)
	{
		return gt2ColorF(f * c.r, f * c.g, f * c.b, f * c.a);
	}
	//@}


	//++++++++++++++++++++++++++++++++++
	//! @name ��r���Z�q
	//++++++++++++++++++++++++++++++++++
	//@{
	inline bool operator == (const gt2ColorF& c) const
	{
		return r == c.r && g == c.g && b == c.b && a == c.a;
	}

	inline bool operator != (const gt2ColorF& c) const
	{
		return r != c.r || g != c.g || b != c.b || a != c.a;
	}
	//@}

	//-----------------------------------------------------------------------------------
	//! @brief �e�v�f��0�ŏ�����
	//! @return �Ȃ�
	//-----------------------------------------------------------------------------------
	inline void Init()
	{
		Set(0, 0, 0, 0);
	}
	//-------------------------------------------------------------------
	//! @brief �F(R,G,B,A)�Ԃ̐��`��Ԃ����s����B
	//! @param [in]  rC1   �� 1 �Ԗڂ̐F(R, G, B, A)
	//! @param [in]  rC2   �� 2 �Ԗڂ̐F(R, G, B, A)
	//! @param [in]  t     �F�Ԃ���`��Ԃ���p�����[�^�B
	//! @return  ���`��Ԃ��ꂽ�F(R,G,B,A)��Ԃ��B
	//-------------------------------------------------------------------
	inline static gt2ColorF Lerp(const gt2ColorF& rC1, const gt2ColorF& rC2, float t)
	{
		gt2ColorF out;
		out.r = rC1.r + t * (rC2.r - rC1.r);
		out.g = rC1.g + t * (rC2.g - rC1.g);
		out.b = rC1.b + t * (rC2.b - rC1.b);
		out.a = rC1.a + t * (rC2.a - rC1.a);
		return out;
	}
	//-------------------------------------------------------------------
	//! @brief �F(R,G,B,A)�Ԃ̐��`��Ԃ����s����B
	//!  �� 1 �Ԗڂ̐F���A���g(this)�ł��B
	//! @param [in]  rC2  �� 2 �Ԗڂ̐F(R, G, B, A)
	//! @param [in]  t    �F�Ԃ���`��Ԃ���p�����[�^�B
	//! @return  ���`��Ԃ��ꂽ�F(R,G,B,A)��Ԃ��B
	//-------------------------------------------------------------------
	inline gt2ColorF Lerp(const gt2ColorF& rC2, float t) const
	{
		return gt2ColorF::Lerp(*this, rC2, t);
	}

	//-------------------------------------------------------------------
	//! @brief 0 �� t �� 1 �̊ԂŃG���~�[�g��Ԃɂ�銊�炩�ȕ�Ԃ��s���܂��B
	//! @param [in]  rC1  �� 1 �Ԗڂ̐F(R, G, B, A)
	//! @param [in]  rC2  �� 2 �Ԗڂ̐F(R, G, B, A)
	//! @param [in]  t    �F�Ԃ���`��Ԃ���p�����[�^�B
	//! @return  ���`��Ԃ��ꂽ�F(R,G,B,A)��Ԃ��B
	//-------------------------------------------------------------------
	inline static gt2ColorF SmoothStep(const gt2ColorF& rC1, const gt2ColorF& rC2, float t)
	{
		t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
		t = t*t*(3.f - 2.f*t);
		return gt2ColorF::Lerp(rC1, rC2, t);
	}

	//-------------------------------------------------------------------
	//! @brief 0 �� t �� 1 �̊ԂŃG���~�[�g��Ԃɂ�銊�炩�ȕ�Ԃ��s���܂��B
	//!  �� 1 �Ԗڂ̐F���A���g(this)�ł��B
	//! @param [in]  rC2  �� 2 �Ԗڂ̐F(R, G, B, A)
	//! @param [in]  t    �F�Ԃ���`��Ԃ���p�����[�^�B
	//! @return  ���`��Ԃ��ꂽ�F(R,G,B,A)��Ԃ��B
	//-------------------------------------------------------------------
	inline gt2ColorF SmoothStep(const gt2ColorF& rC2, float t) const
	{
		return gt2ColorF::SmoothStep(*this, rC2, t);
	}

	//-------------------------------------------------------------------
	//! @brief �œK������B
	//! ��ɁA0��菬�����ꍇ�͂O�ɁA1��葽���ꍇ�͂P�ɂ���
	//! @return  �Ȃ�
	//-------------------------------------------------------------------
	inline void Optimization()
	{
		if (r < 0) r = 0.0f; else if (r > 1.0f) r = 1.0f;
		if (g < 0) g = 0.0f; else if (g > 1.0f) g = 1.0f;
		if (b < 0) b = 0.0f; else if (b > 1.0f) b = 1.0f;
		if (a < 0) a = 0.0f; else if (a > 1.0f) a = 1.0f;
	}



public:
	const static uint32_t Transparent = 0x00000000;		//!< ����
	const static uint32_t AliceBlue = 0xFFF0F8FF;			//!< �A���X�u���[
	const static uint32_t AntiqueWhite = 0xFFFAEBD7;		//!< �A���e�B�[�N�z���C�g
	const static uint32_t Aqua = 0xFF00FFFF;				//!< �A�N�A
	const static uint32_t Aquamarine = 0xFF7FFFD4;			//!< �A�N�A�}����
	const static uint32_t Azure = 0xFFF0FFFF;				//!< �A�Y�[��
	const static uint32_t Beige = 0xFFF5F5DC;				//!< �x�[�W��
	const static uint32_t Bisque = 0xFFFFE4C4;				//!< �r�X�N
	const static uint32_t Black = 0xFF000000;				//!< �u���b�N
	const static uint32_t BlanchedAlmond = 0xFFFFEBCD;		//!< �u�����`�A�[�����h
	const static uint32_t Blue = 0xFF0000FF;				//!< �u���[
	const static uint32_t BlueViolet = 0xFF8A2BE2;			//!< �u���[�o�C�I���b�g
	const static uint32_t Brown = 0xFFA52A2A;				//!< �u���E��
	const static uint32_t BurlyWood = 0xFFDEB887;			//!< �o�[���[�E�E�b�h
	const static uint32_t CadetBlue = 0xFF5F9EA0;			//!< �J�f�b�g�u���[
	const static uint32_t Chartreuse = 0xFF7FFF00;			//!< �V�����g�����[�Y
	const static uint32_t Chocolate = 0xFFD2691E;			//!< �`���R���[�g
	const static uint32_t Coral = 0xFFFF7F50;				//!< �R�[����
	const static uint32_t CornflowerBlue = 0xFF6495ED;		//!< ���O���}�M�N�u���[
	const static uint32_t Cornsilk = 0xFFFFF8DC;			//!< �R�[���V���N
	const static uint32_t Crimson = 0xFFDC143C;			//!< �N�����]��
	const static uint32_t Cyan = 0xFF00FFFF;				//!< �V�A��
	const static uint32_t DarkBlue = 0xFF00008B;			//!< �_�[�N�u���[
	const static uint32_t DarkCyan = 0xFF008B8B;			//!< �_�[�N�V�A��
	const static uint32_t DarkGoldenrod = 0xFFB8860B;		//!< �_�[�N�A�L�m�L�����\�E
	const static uint32_t DarkGray = 0xFFA9A9A9;			//!< �_�[�N�O���[
	const static uint32_t DarkGreen = 0xFF006400;			//!< �_�[�N�O���[��
	const static uint32_t DarkKhaki = 0xFFBDB76B;			//!< �_�[�N�J�[�L
	const static uint32_t DarkMagenta = 0xFF8B008B;		//!< �_�[�N�}�[���^
	const static uint32_t DarkOliveGreen = 0xFF556B2F;		//!< �_�[�N�I���[�u�O���[��
	const static uint32_t DarkOrange = 0xFFFF8C00;			//!< �_�[�N�I�����W
	const static uint32_t DarkOrchid = 0xFF9932CC;			//!< �_�[�N�I�[�L�b�h
	const static uint32_t DarkRed = 0xFF8B0000;			//!< �_�[�N���b�h
	const static uint32_t DarkSalmon = 0xFFE9967A;			//!< �_�[�N�T�[����
	const static uint32_t DarkSeaGreen = 0xFF8FBC8F;		//!< �_�[�N�E�V�[�O���[�� 
	const static uint32_t DarkSlateBlue = 0xFF483D8B;		//!< �_�[�N�X���[�g�u���[
	const static uint32_t DarkSlateGray = 0xFF2F4F4F;		//!< �_�[�N�X���[�g�O���[
	const static uint32_t DarkTurquoise = 0xFF00CED1;		//!< �_�[�N�^�[�R�C�Y
	const static uint32_t DarkViolet = 0xFF9400D3;			//!< �_�[�N�o�C�I���b�g
	const static uint32_t DeepPink = 0xFFFF1493;			//!< �f�B�[�v�s���N
	const static uint32_t DeepSkyBlue = 0xFF00BFFF;		//!< �f�B�[�v�X�J�C�u���[
	const static uint32_t DimGray = 0xFF696969;			//!< �f�B���E�O���C
	const static uint32_t DodgerBlue = 0xFF1E90FF;			//!< �h�W���[�u���[
	const static uint32_t Firebrick = 0xFFB22222;			//!< �t�@�C�A�E�u���b�N 
	const static uint32_t FloralWhite = 0xFFFFFAF0;		//!< �t���[�����z���C�g
	const static uint32_t ForestGreen = 0xFF228B22;		//!< �t�H���X�g�O���[��
	const static uint32_t Fuchsia = 0xFFFF00FF;			//!< �t�N�V�A
	const static uint32_t Gainsboro = 0xFFDCDCDC;			//!< �Q�C���Y�{��
	const static uint32_t GhostWhite = 0xFFF8F8FF;			//!< �S�[�X�g�z���C�g
	const static uint32_t Gold = 0xFFFFD700;				//!< �S�[���h
	const static uint32_t Goldenrod = 0xFFDAA520;			//!< �A�L�m�L�����\�E
	const static uint32_t Gray = 0xFF808080;				//!< �O���[
	const static uint32_t Green = 0xFF008000;				//!< �O���[��
	const static uint32_t GreenYellow = 0xFFADFF2F;		//!< �O���[���C�G���[
	const static uint32_t Honeydew = 0xFFF0FFF0;			//!< �n�j�[�f���[
	const static uint32_t HotPink = 0xFFFF69B4;			//!< �z�b�g�s���N
	const static uint32_t IndianRed = 0xFFCD5C5C;			//!< �C���f�B�A�����b�h
	const static uint32_t Indigo = 0xFF4B0082;				//!< �C���f�B�S
	const static uint32_t Ivory = 0xFFFFFFF0;				//!< �A�C�{���[
	const static uint32_t Khaki = 0xFFF0E68C;				//!< �J�[�L
	const static uint32_t Lavender = 0xFFE6E6FA;			//!< ���x���_�[
	const static uint32_t LavenderBlush = 0xFFFFF0F5;		//!< ���x���_�[�u���b�V��
	const static uint32_t LawnGreen = 0xFF7CFC00;			//!< ���[���E�O���[��
	const static uint32_t LemonChiffon = 0xFFFFFACD;		//!< �������V�t�H��
	const static uint32_t LightBlue = 0xFFADD8E6;			//!< ���C�g�u���[
	const static uint32_t LightCoral = 0xFFF08080;			//!< ���C�g�R�[����
	const static uint32_t LightCyan = 0xFFE0FFFF;			//!< ���C�g�V�A��
	const static uint32_t LightGoldenrodYellow = 0xFFFAFAD2;//!< ���C�g��S�[���f�����b�h��C�G���[
	const static uint32_t LightGreen = 0xFF90EE90;			//!< ���C�g�O���[��
	const static uint32_t LightGray = 0xFFD3D3D3;			//!< ���C�g�O���[
	const static uint32_t LightPink = 0xFFFFB6C1;			//!< ���C�g�s���N
	const static uint32_t LightSalmon = 0xFFFFA07A;		//!< ���C�g�T�[����
	const static uint32_t LightSeaGreen = 0xFF20B2AA;		//!< ���C�g�E�V�[�O���[��
	const static uint32_t LightSkyBlue = 0xFF87CEFA;		//!< ���C�g�X�J�C�u���[
	const static uint32_t LightSlateGray = 0xFF778899;		//!< ���C�g�X���[�g�O���[
	const static uint32_t LightSteelBlue = 0xFFB0C4DE;		//!< ���C�g�X�`�[���u���[
	const static uint32_t LightYellow = 0xFFFFFFE0;		//!< �C�G���[���C�g
	const static uint32_t Lime = 0xFF00FF00;				//!< ���C��
	const static uint32_t LimeGreen = 0xFF32CD32;			//!< ���C���O���[��
	const static uint32_t Linen = 0xFFFAF0E6;				//!< ���l��
	const static uint32_t Magenta = 0xFFFF00FF;			//!< �}�[���^
	const static uint32_t Maroon = 0xFF800000;				//!< �}���[��
	const static uint32_t MediumAquamarine = 0xFF66CDAA;	//!< �~�f�B�A���A�N�A�}����
	const static uint32_t MediumBlue = 0xFF0000CD;			//!< �~�f�B�A���u���[
	const static uint32_t MediumOrchid = 0xFFBA55D3;		//!< �~�f�B�A���I�[�L�b�h
	const static uint32_t MediumPurple = 0xFF9370DB;		//!< �~�f�B�A���p�[�v��
	const static uint32_t MediumSeaGreen = 0xFF3CB371;		//!< �~�f�B�A���V�[�O���[��
	const static uint32_t MediumSlateBlue = 0xFF7B68EE;	//!< �~�f�B�A���X���[�g�u���[
	const static uint32_t MediumSpringGreen = 0xFF00FA9A;	//!< �~�f�B�A���X�v�����O�O���[��
	const static uint32_t MediumTurquoise = 0xFF48D1CC;	//!< �~�f�B�A���^�[�R�C�Y
	const static uint32_t MediumVioletRed = 0xFFC71585;	//!< �~�f�B�A���o�C�I���b�g���b�h
	const static uint32_t MidnightBlue = 0xFF191970;		//!< �~�b�h�i�C�g�u���[
	const static uint32_t MintCream = 0xFFF5FFFA;			//!< �~���g�N���[��
	const static uint32_t MistyRose = 0xFFFFE4E1;			//!< �~�X�e�B���[�Y
	const static uint32_t Moccasin = 0xFFFFE4B5;			//!< ���J�V��
	const static uint32_t NavajoWhite = 0xFFFFDEAD;		//!< �i�o�z�z���C�g
	const static uint32_t Navy = 0xFF000080;				//!< �l�C�r�[
	const static uint32_t OldLace = 0xFFFDF5E6;			//!< �I�[���h���[�X
	const static uint32_t Olive = 0xFF808000;				//!< �I���[�u
	const static uint32_t OliveDrab = 0xFF6B8E23;			//!< �I���[�u�h���u
	const static uint32_t Orange = 0xFFFFA500;				//!< �I�����W
	const static uint32_t OrangeRed = 0xFFFF4500;			//!< �I�����W�E���b�h
	const static uint32_t Orchid = 0xFFDA70D6;				//!< �I�[�L�b�h
	const static uint32_t PaleGoldenrod = 0xFFEEE8AA;		//!< �y�[���E�S�[���f�����b�h
	const static uint32_t PaleGreen = 0xFF98FB98;			//!< �y�[���E�O���[��
	const static uint32_t PaleTurquoise = 0xFFAFEEEE;		//!< �y�[���^�[�R�C�Y
	const static uint32_t PaleVioletRed = 0xFFDB7093;		//!< �y�[���o�C�I���b�g���b�h
	const static uint32_t PapayaWhip = 0xFFFFEFD5;			//!< �p�p�C���z�C�b�v
	const static uint32_t PeachPuff = 0xFFFFDAB9;			//!< �s�[�`�p�t
	const static uint32_t Peru = 0xFFCD853F;				//!< �y���[
	const static uint32_t Pink = 0xFFFFC0CB;				//!< �s���N
	const static uint32_t Plum = 0xFFDDA0DD;				//!< �v����
	const static uint32_t PowderBlue = 0xFFB0E0E6;			//!< �p�E�_�[�u���[
	const static uint32_t Purple = 0xFF800080;				//!< �p�[�v��
	const static uint32_t Red = 0xFFFF0000;				//!< ���b�h
	const static uint32_t RosyBrown = 0xFFBC8F8F;			//!< ���[�W�[�u���E��
	const static uint32_t RoyalBlue = 0xFF4169E1;			//!< ���C�����u���[
	const static uint32_t SaddleBrown = 0xFF8B4513;		//!< �u���E���T�h��
	const static uint32_t Salmon = 0xFFFA8072;				//!< �T�[����
	const static uint32_t SandyBrown = 0xFFF4A460;			//!< �T���f�B�[�u���E��
	const static uint32_t SeaGreen = 0xFF2E8B57;			//!< �V�[�E�O���[��
	const static uint32_t SeaShell = 0xFFFFF5EE;			//!< �V�[�V�F��
	const static uint32_t Sienna = 0xFFA0522D;				//!< �V�G�i
	const static uint32_t Silver = 0xFFC0C0C0;				//!< �V���o�[
	const static uint32_t SkyBlue = 0xFF87CEEB;			//!< �X�J�C�u���[
	const static uint32_t SlateBlue = 0xFF6A5ACD;			//!< �X���[�g�u���[
	const static uint32_t SlateGray = 0xFF708090;			//!< �X���[�g�O���[
	const static uint32_t Snow = 0xFFFFFAFA;				//!< �X�m�[
	const static uint32_t SpringGreen = 0xFF00FF7F;		//!< �X�v�����O�O���[��
	const static uint32_t SteelBlue = 0xFF4682B4;			//!< �X�`�[���u���[
	const static uint32_t Tan = 0xFFD2B48C;				//!< �^��
	const static uint32_t Teal = 0xFF008080;				//!< �e�B�[��
	const static uint32_t Thistle = 0xFFD8BFD8;			//!< �V�X��
	const static uint32_t Tomato = 0xFFFF6347;				//!< �g�}�g
	const static uint32_t Turquoise = 0xFF40E0D0;			//!< �^�[�R�C�Y
	const static uint32_t Violet = 0xFFEE82EE;				//!< �o�C�I���b�g
	const static uint32_t Wheat = 0xFFF5DEB3;				//!< �E�B�[�g
	const static uint32_t White = uint32_t_MAX;				//!< �z���C�g
	const static uint32_t WhiteSmoke = 0xFFF5F5F5;			//!< �z���C�g�X���[�N
	const static uint32_t Yellow = 0xFFFFFF00;				//!< �C�G���[
	const static uint32_t YellowGreen = 0xFF9ACD32;		//!< ���ΐF
};

// �G���[
const gt2ColorF g_ColorF_NaN = gt2ColorF(NAN, NAN, NAN, NAN);

