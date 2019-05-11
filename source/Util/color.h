/*! @file  color.h
* @brief 色
* @author kaoken
* @date 2014/03/19 作成開始
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
			float r;	//!< レッド
			float g;	//!< グリーン
			float b;	//!< ブルー
			float a;	//!< アルファ
		};
		float v[4];		//!< 各色を表す配列[0=レッド, 1=グリーン, 2=ブルー, 3=アルファ]
	};
public:
		

	//-------------------------------------------------------------------
	//! @brief コンストラクタ rgb=0,a=1.0
	//-------------------------------------------------------------------
	gt2ColorF()
	{
		r = g = b = 0.0f;
		a = 1.0f;
	}
	//-------------------------------------------------------------------
	//! @brief コンストラクタ
	//! @param [in] dw 符号なし32ビット整数値で初期化
	//-------------------------------------------------------------------
	gt2ColorF(uint32_t dw)
	{
		Set(dw);
	}

	//-------------------------------------------------------------------
	//! @brief コンストラクタ
	//! @param [in] pf 32ビット浮動小数の4要素を含むポインタで初期化
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
	//! @brief コンストラクタ
	//! @param [in] fr 32ビット浮動小数で レッド
	//! @param [in] fg 32ビット浮動小数で グリーン
	//! @param [in] fb 32ビット浮動小数で ブルー
	//! @param [in] fa 32ビット浮動小数で アルファ
	//-------------------------------------------------------------------
	inline gt2ColorF(float fr, float fg, float fb, float fa)
	{
		Set(fr,fg,fb,fa);
	}

	//-------------------------------------------------------------------
	//! @brief コンストラクタ
	//! @param [in] fr 32ビット浮動小数で レッド
	//! @param [in] fg 32ビット浮動小数で グリーン
	//! @param [in] fb 32ビット浮動小数で ブルー
	//! @param [in] fa 32ビット浮動小数で アルファ
	//-------------------------------------------------------------------
	inline gt2ColorF(const gt2ColorF& color)
	{
		this->Set(color);
	}

	//-------------------------------------------------------------------
	//! @brief コンストラクタ
	//! @param [in] nR 整数(0～255)) レッド
	//! @param [in] nG 整数(0～255)) グリーン
	//! @param [in] nB 整数(0～255)) ブルー
	//! @param [in] nA 整数(0～255)) アルファ
	//-------------------------------------------------------------------
	inline gt2ColorF(int red, int green, int blue, int alpha)
	{
		this->Set(red, green, blue, alpha);
	}

	//-------------------------------------------------------------------
	//! @brief gt2ColorFをセットする
	//! @param [in] color gt2ColorF
	//-------------------------------------------------------------------
	inline void Set(const gt2ColorF& color)
	{
		*this = color;
	}

	//-------------------------------------------------------------------
	//! @brief 符号なし32ビット整数値で色をセットする
	//! @param [in] dw 符号なし32ビット整数値で初期化
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
	//! @brief 色をセット
	//! @param [in] fr 32ビット浮動小数で レッド
	//! @param [in] fg 32ビット浮動小数で グリーン
	//! @param [in] fb 32ビット浮動小数で ブルー
	//! @param [in] fa 32ビット浮動小数で アルファ
	//-------------------------------------------------------------------
	inline void Set(float fr, float fg, float fb, float fa)
	{
		r = fr;
		g = fg;
		b = fb;
		a = fa;
	}
	//-------------------------------------------------------------------
	//! @brief 色をセット
	//! @param [in] nR 符号なし32ビット整数の レッド
	//! @param [in] nG 符号なし32ビット整数の グリーン
	//! @param [in] nB 符号なし32ビット整数の ブルー
	//! @param [in] nA 符号なし32ビット整数の アルファ
	//-------------------------------------------------------------------
	inline void Set(int nR, int nG, int nB, int nA)
	{
		a = (float)(nA & 0x00FF) / 255.0f;
		r = (float)(nR & 0x00FF) / 255.0f;
		g = (float)(nG & 0x00FF) / 255.0f;
		b = (float)(nB & 0x00FF) / 255.0f;
	}


	//-------------------------------------------------------------------
	//! @brief 符号なし32ビット整数の値で色を返す。
	//! @return 符号なし32ビット整数の値で色を返す。
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
	//! @name キャスト
	//++++++++++++++++++++++++++++++++++
	//@{
	//-------------------------------------------------------------------
	//! @brief キャスト：uint32_t
	//-------------------------------------------------------------------
	inline operator uint32_t () const
	{
		return GetU32();
	}
	//-------------------------------------------------------------------
	//! @brief キャスト：float
	//-------------------------------------------------------------------
	inline operator float * ()
	{
		return (float *)&r;
	}
	//-------------------------------------------------------------------
	//! @brief const キャスト：float
	//-------------------------------------------------------------------
	inline operator const float * () const
	{
		return (const float *)&r;
	}
	//@}


	//++++++++++++++++++++++++++++++++++
	//! @name 代入演算子
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
	//! @name 単項演算子
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
	//! @name 二項演算子
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
	//! @name 比較演算子
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
	//! @brief 各要素を0で初期化
	//! @return なし
	//-----------------------------------------------------------------------------------
	inline void Init()
	{
		Set(0, 0, 0, 0);
	}
	//-------------------------------------------------------------------
	//! @brief 色(R,G,B,A)間の線形補間を実行する。
	//! @param [in]  rC1   第 1 番目の色(R, G, B, A)
	//! @param [in]  rC2   第 2 番目の色(R, G, B, A)
	//! @param [in]  t     色間を線形補間するパラメータ。
	//! @return  線形補間された色(R,G,B,A)を返す。
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
	//! @brief 色(R,G,B,A)間の線形補間を実行する。
	//!  第 1 番目の色が、自身(this)です。
	//! @param [in]  rC2  第 2 番目の色(R, G, B, A)
	//! @param [in]  t    色間を線形補間するパラメータ。
	//! @return  線形補間された色(R,G,B,A)を返す。
	//-------------------------------------------------------------------
	inline gt2ColorF Lerp(const gt2ColorF& rC2, float t) const
	{
		return gt2ColorF::Lerp(*this, rC2, t);
	}

	//-------------------------------------------------------------------
	//! @brief 0 ≦ t ≦ 1 の間でエルミート補間による滑らかな補間を行います。
	//! @param [in]  rC1  第 1 番目の色(R, G, B, A)
	//! @param [in]  rC2  第 2 番目の色(R, G, B, A)
	//! @param [in]  t    色間を線形補間するパラメータ。
	//! @return  線形補間された色(R,G,B,A)を返す。
	//-------------------------------------------------------------------
	inline static gt2ColorF SmoothStep(const gt2ColorF& rC1, const gt2ColorF& rC2, float t)
	{
		t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
		t = t*t*(3.f - 2.f*t);
		return gt2ColorF::Lerp(rC1, rC2, t);
	}

	//-------------------------------------------------------------------
	//! @brief 0 ≦ t ≦ 1 の間でエルミート補間による滑らかな補間を行います。
	//!  第 1 番目の色が、自身(this)です。
	//! @param [in]  rC2  第 2 番目の色(R, G, B, A)
	//! @param [in]  t    色間を線形補間するパラメータ。
	//! @return  線形補間された色(R,G,B,A)を返す。
	//-------------------------------------------------------------------
	inline gt2ColorF SmoothStep(const gt2ColorF& rC2, float t) const
	{
		return gt2ColorF::SmoothStep(*this, rC2, t);
	}

	//-------------------------------------------------------------------
	//! @brief 最適化する。
	//! 主に、0より小さい場合は０に、1より多き場合は１にする
	//! @return  なし
	//-------------------------------------------------------------------
	inline void Optimization()
	{
		if (r < 0) r = 0.0f; else if (r > 1.0f) r = 1.0f;
		if (g < 0) g = 0.0f; else if (g > 1.0f) g = 1.0f;
		if (b < 0) b = 0.0f; else if (b > 1.0f) b = 1.0f;
		if (a < 0) a = 0.0f; else if (a > 1.0f) a = 1.0f;
	}



public:
	const static uint32_t Transparent = 0x00000000;		//!< 透明
	const static uint32_t AliceBlue = 0xFFF0F8FF;			//!< アリスブルー
	const static uint32_t AntiqueWhite = 0xFFFAEBD7;		//!< アンティークホワイト
	const static uint32_t Aqua = 0xFF00FFFF;				//!< アクア
	const static uint32_t Aquamarine = 0xFF7FFFD4;			//!< アクアマリン
	const static uint32_t Azure = 0xFFF0FFFF;				//!< アズール
	const static uint32_t Beige = 0xFFF5F5DC;				//!< ベージュ
	const static uint32_t Bisque = 0xFFFFE4C4;				//!< ビスク
	const static uint32_t Black = 0xFF000000;				//!< ブラック
	const static uint32_t BlanchedAlmond = 0xFFFFEBCD;		//!< ブランチアーモンド
	const static uint32_t Blue = 0xFF0000FF;				//!< ブルー
	const static uint32_t BlueViolet = 0xFF8A2BE2;			//!< ブルーバイオレット
	const static uint32_t Brown = 0xFFA52A2A;				//!< ブラウン
	const static uint32_t BurlyWood = 0xFFDEB887;			//!< バーリー・ウッド
	const static uint32_t CadetBlue = 0xFF5F9EA0;			//!< カデットブルー
	const static uint32_t Chartreuse = 0xFF7FFF00;			//!< シャルトリューズ
	const static uint32_t Chocolate = 0xFFD2691E;			//!< チョコレート
	const static uint32_t Coral = 0xFFFF7F50;				//!< コーラル
	const static uint32_t CornflowerBlue = 0xFF6495ED;		//!< ヤグルマギクブルー
	const static uint32_t Cornsilk = 0xFFFFF8DC;			//!< コーンシルク
	const static uint32_t Crimson = 0xFFDC143C;			//!< クリムゾン
	const static uint32_t Cyan = 0xFF00FFFF;				//!< シアン
	const static uint32_t DarkBlue = 0xFF00008B;			//!< ダークブルー
	const static uint32_t DarkCyan = 0xFF008B8B;			//!< ダークシアン
	const static uint32_t DarkGoldenrod = 0xFFB8860B;		//!< ダークアキノキリンソウ
	const static uint32_t DarkGray = 0xFFA9A9A9;			//!< ダークグレー
	const static uint32_t DarkGreen = 0xFF006400;			//!< ダークグリーン
	const static uint32_t DarkKhaki = 0xFFBDB76B;			//!< ダークカーキ
	const static uint32_t DarkMagenta = 0xFF8B008B;		//!< ダークマゼンタ
	const static uint32_t DarkOliveGreen = 0xFF556B2F;		//!< ダークオリーブグリーン
	const static uint32_t DarkOrange = 0xFFFF8C00;			//!< ダークオレンジ
	const static uint32_t DarkOrchid = 0xFF9932CC;			//!< ダークオーキッド
	const static uint32_t DarkRed = 0xFF8B0000;			//!< ダークレッド
	const static uint32_t DarkSalmon = 0xFFE9967A;			//!< ダークサーモン
	const static uint32_t DarkSeaGreen = 0xFF8FBC8F;		//!< ダーク・シーグリーン 
	const static uint32_t DarkSlateBlue = 0xFF483D8B;		//!< ダークスレートブルー
	const static uint32_t DarkSlateGray = 0xFF2F4F4F;		//!< ダークスレートグレー
	const static uint32_t DarkTurquoise = 0xFF00CED1;		//!< ダークターコイズ
	const static uint32_t DarkViolet = 0xFF9400D3;			//!< ダークバイオレット
	const static uint32_t DeepPink = 0xFFFF1493;			//!< ディープピンク
	const static uint32_t DeepSkyBlue = 0xFF00BFFF;		//!< ディープスカイブルー
	const static uint32_t DimGray = 0xFF696969;			//!< ディム・グレイ
	const static uint32_t DodgerBlue = 0xFF1E90FF;			//!< ドジャーブルー
	const static uint32_t Firebrick = 0xFFB22222;			//!< ファイア・ブリック 
	const static uint32_t FloralWhite = 0xFFFFFAF0;		//!< フローラルホワイト
	const static uint32_t ForestGreen = 0xFF228B22;		//!< フォレストグリーン
	const static uint32_t Fuchsia = 0xFFFF00FF;			//!< フクシア
	const static uint32_t Gainsboro = 0xFFDCDCDC;			//!< ゲインズボロ
	const static uint32_t GhostWhite = 0xFFF8F8FF;			//!< ゴーストホワイト
	const static uint32_t Gold = 0xFFFFD700;				//!< ゴールド
	const static uint32_t Goldenrod = 0xFFDAA520;			//!< アキノキリンソウ
	const static uint32_t Gray = 0xFF808080;				//!< グレー
	const static uint32_t Green = 0xFF008000;				//!< グリーン
	const static uint32_t GreenYellow = 0xFFADFF2F;		//!< グリーンイエロー
	const static uint32_t Honeydew = 0xFFF0FFF0;			//!< ハニーデュー
	const static uint32_t HotPink = 0xFFFF69B4;			//!< ホットピンク
	const static uint32_t IndianRed = 0xFFCD5C5C;			//!< インディアンレッド
	const static uint32_t Indigo = 0xFF4B0082;				//!< インディゴ
	const static uint32_t Ivory = 0xFFFFFFF0;				//!< アイボリー
	const static uint32_t Khaki = 0xFFF0E68C;				//!< カーキ
	const static uint32_t Lavender = 0xFFE6E6FA;			//!< ラベンダー
	const static uint32_t LavenderBlush = 0xFFFFF0F5;		//!< ラベンダーブラッシュ
	const static uint32_t LawnGreen = 0xFF7CFC00;			//!< ローン・グリーン
	const static uint32_t LemonChiffon = 0xFFFFFACD;		//!< レモンシフォン
	const static uint32_t LightBlue = 0xFFADD8E6;			//!< ライトブルー
	const static uint32_t LightCoral = 0xFFF08080;			//!< ライトコーラル
	const static uint32_t LightCyan = 0xFFE0FFFF;			//!< ライトシアン
	const static uint32_t LightGoldenrodYellow = 0xFFFAFAD2;//!< ライト･ゴールデンロッド･イエロー
	const static uint32_t LightGreen = 0xFF90EE90;			//!< ライトグリーン
	const static uint32_t LightGray = 0xFFD3D3D3;			//!< ライトグレー
	const static uint32_t LightPink = 0xFFFFB6C1;			//!< ライトピンク
	const static uint32_t LightSalmon = 0xFFFFA07A;		//!< ライトサーモン
	const static uint32_t LightSeaGreen = 0xFF20B2AA;		//!< ライト・シーグリーン
	const static uint32_t LightSkyBlue = 0xFF87CEFA;		//!< ライトスカイブルー
	const static uint32_t LightSlateGray = 0xFF778899;		//!< ライトスレートグレー
	const static uint32_t LightSteelBlue = 0xFFB0C4DE;		//!< ライトスチールブルー
	const static uint32_t LightYellow = 0xFFFFFFE0;		//!< イエローライト
	const static uint32_t Lime = 0xFF00FF00;				//!< ライム
	const static uint32_t LimeGreen = 0xFF32CD32;			//!< ライムグリーン
	const static uint32_t Linen = 0xFFFAF0E6;				//!< リネン
	const static uint32_t Magenta = 0xFFFF00FF;			//!< マゼンタ
	const static uint32_t Maroon = 0xFF800000;				//!< マルーン
	const static uint32_t MediumAquamarine = 0xFF66CDAA;	//!< ミディアムアクアマリン
	const static uint32_t MediumBlue = 0xFF0000CD;			//!< ミディアムブルー
	const static uint32_t MediumOrchid = 0xFFBA55D3;		//!< ミディアムオーキッド
	const static uint32_t MediumPurple = 0xFF9370DB;		//!< ミディアムパープル
	const static uint32_t MediumSeaGreen = 0xFF3CB371;		//!< ミディアムシーグリーン
	const static uint32_t MediumSlateBlue = 0xFF7B68EE;	//!< ミディアムスレートブルー
	const static uint32_t MediumSpringGreen = 0xFF00FA9A;	//!< ミディアムスプリンググリーン
	const static uint32_t MediumTurquoise = 0xFF48D1CC;	//!< ミディアムターコイズ
	const static uint32_t MediumVioletRed = 0xFFC71585;	//!< ミディアムバイオレットレッド
	const static uint32_t MidnightBlue = 0xFF191970;		//!< ミッドナイトブルー
	const static uint32_t MintCream = 0xFFF5FFFA;			//!< ミントクリーム
	const static uint32_t MistyRose = 0xFFFFE4E1;			//!< ミスティローズ
	const static uint32_t Moccasin = 0xFFFFE4B5;			//!< モカシン
	const static uint32_t NavajoWhite = 0xFFFFDEAD;		//!< ナバホホワイト
	const static uint32_t Navy = 0xFF000080;				//!< ネイビー
	const static uint32_t OldLace = 0xFFFDF5E6;			//!< オールドレース
	const static uint32_t Olive = 0xFF808000;				//!< オリーブ
	const static uint32_t OliveDrab = 0xFF6B8E23;			//!< オリーブドラブ
	const static uint32_t Orange = 0xFFFFA500;				//!< オレンジ
	const static uint32_t OrangeRed = 0xFFFF4500;			//!< オレンジ・レッド
	const static uint32_t Orchid = 0xFFDA70D6;				//!< オーキッド
	const static uint32_t PaleGoldenrod = 0xFFEEE8AA;		//!< ペール・ゴールデンロッド
	const static uint32_t PaleGreen = 0xFF98FB98;			//!< ペール・グリーン
	const static uint32_t PaleTurquoise = 0xFFAFEEEE;		//!< ペールターコイズ
	const static uint32_t PaleVioletRed = 0xFFDB7093;		//!< ペールバイオレットレッド
	const static uint32_t PapayaWhip = 0xFFFFEFD5;			//!< パパイヤホイップ
	const static uint32_t PeachPuff = 0xFFFFDAB9;			//!< ピーチパフ
	const static uint32_t Peru = 0xFFCD853F;				//!< ペルー
	const static uint32_t Pink = 0xFFFFC0CB;				//!< ピンク
	const static uint32_t Plum = 0xFFDDA0DD;				//!< プラム
	const static uint32_t PowderBlue = 0xFFB0E0E6;			//!< パウダーブルー
	const static uint32_t Purple = 0xFF800080;				//!< パープル
	const static uint32_t Red = 0xFFFF0000;				//!< レッド
	const static uint32_t RosyBrown = 0xFFBC8F8F;			//!< ロージーブラウン
	const static uint32_t RoyalBlue = 0xFF4169E1;			//!< ロイヤルブルー
	const static uint32_t SaddleBrown = 0xFF8B4513;		//!< ブラウンサドル
	const static uint32_t Salmon = 0xFFFA8072;				//!< サーモン
	const static uint32_t SandyBrown = 0xFFF4A460;			//!< サンディーブラウン
	const static uint32_t SeaGreen = 0xFF2E8B57;			//!< シー・グリーン
	const static uint32_t SeaShell = 0xFFFFF5EE;			//!< シーシェル
	const static uint32_t Sienna = 0xFFA0522D;				//!< シエナ
	const static uint32_t Silver = 0xFFC0C0C0;				//!< シルバー
	const static uint32_t SkyBlue = 0xFF87CEEB;			//!< スカイブルー
	const static uint32_t SlateBlue = 0xFF6A5ACD;			//!< スレートブルー
	const static uint32_t SlateGray = 0xFF708090;			//!< スレートグレー
	const static uint32_t Snow = 0xFFFFFAFA;				//!< スノー
	const static uint32_t SpringGreen = 0xFF00FF7F;		//!< スプリンググリーン
	const static uint32_t SteelBlue = 0xFF4682B4;			//!< スチールブルー
	const static uint32_t Tan = 0xFFD2B48C;				//!< タン
	const static uint32_t Teal = 0xFF008080;				//!< ティール
	const static uint32_t Thistle = 0xFFD8BFD8;			//!< シスル
	const static uint32_t Tomato = 0xFFFF6347;				//!< トマト
	const static uint32_t Turquoise = 0xFF40E0D0;			//!< ターコイズ
	const static uint32_t Violet = 0xFFEE82EE;				//!< バイオレット
	const static uint32_t Wheat = 0xFFF5DEB3;				//!< ウィート
	const static uint32_t White = uint32_t_MAX;				//!< ホワイト
	const static uint32_t WhiteSmoke = 0xFFF5F5F5;			//!< ホワイトスモーク
	const static uint32_t Yellow = 0xFFFFFF00;				//!< イエロー
	const static uint32_t YellowGreen = 0xFF9ACD32;		//!< 黄緑色
};

// エラー
const gt2ColorF g_ColorF_NaN = gt2ColorF(NAN, NAN, NAN, NAN);

