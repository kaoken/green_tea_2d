#include <Math/UtilMath.h>
#include <cmath>
#include <random>


float fclamp(float x, float min, float max)
{
	if (x < min) {
		return min;
	}
	else if (x > max) {
		return max;
	}

	return x;
}
//-----------------------------------------------------------------------------------
// [ 説明 ] 
//  二次方程式を解き、最小値を返す。
// [ 引数 ]
//  fA		:[in] a
//  fB		:[in] b
//  fC		:[in] c
//  pTime	:[in,out] ０～１の範囲の時間の値をセットする
// [ 戻り値 ]
//  falseの場合解なし　trueの場合解あり
//-----------------------------------------------------------------------------------
bool FindLowestRootInInterval(float fA, float fB, float fC, float *pTime)
{
	// 判別式
	float fDeterminant = fB*fB - 4.0f*fA*fC;

	// これが負なら解は複素数．
	if (fDeterminant < 0.0f) return false;

	// これを基準化する方法はコンピュータに依存する
	//      -b ±√(-b^2-4ac)
	// x = -------------------
	//             2a
	// aが0近くである場合、上記の式は、安定しない。
	float fQ = -0.5f*(fB + (fB < 0.0f ? -1.0f : 1.0f) * sqrtf(fDeterminant));
	// 下記の二つは+INF、-INFあるいはNANを返すことができる。
	float x1 = fQ / fA;
	float x2 = fC / fQ;

	// 並び替えをするか？
	if (x1 > x2)
	{
		float temp = x2;
		x2 = x1;
		x1 = temp;
	}

	// 値が範囲内か:[0 pTime]
	if (x1 > 0.0f && x1 < *pTime)
	{
		*pTime = x1;
		return true;
	}

	// x2を使用することがある
	// if r1 < 0
	if (x2 > 0.0f && x2 < *pTime)
	{
		*pTime = x2;
		return true;
	}
	// 解がない
	return false;
}

//-----------------------------------------------------------------------------------
// [ 説明 ]
//  三角形ABCに対する点Pから 重心座標(*pvCenter)を取得する
//
// [ 引数 ]
//  vA	：[in] 点A
//  vB	：[in] 点B
//  vC	：[in] 点C
//  vP	：[in] 点P
//  pvCenter：[out] 重心座標
//
// [ 戻り値 ]
//  無し
//-----------------------------------------------------------------------------------
void Math3DBarycentric(gt2Vector3 vA, gt2Vector3 vB, gt2Vector3 vC,
	gt2Vector3 vP, gt2Vector3 *pvCenter)
{
	gt2Vector3 v0, v1, v2;
	float d00, d01, d11, d20, d21;
	float denom;

	v0 = vB - vA;
	v1 = vC - vA;
	v2 = vP - vA;

	d00 = v0.Dot(v0);
	d01 = v0.Dot(v1);
	d11 = v1.Dot(v1);
	d20 = v2.Dot(v0);
	d21 = v2.Dot(v1);

	denom = d00 * d11 - d01 * d01;

	pvCenter->y = (d11 * d20 - d01 * d21) / denom;
	pvCenter->z = (d00 * d21 - d01 * d20) / denom;
	pvCenter->x = 1.0f - pvCenter->y - pvCenter->z;


}

static std::mt19937 g_ASRandom;

//--------------------------------------------
//! @brief 数値を種としたランダム関数の初期化
//! @param [in] u ランダムの元となる数値
//! @return なし
//--------------------------------------------
void RandInit(uint32_t u)
{
	g_ASRandom = std::mt19937{ u };
}
//--------------------------------------------
//! @brief 時間を種としたランダム関数の初期化
//! @return なし
//--------------------------------------------
void RandInitNowTime()
{
	g_ASRandom = std::mt19937{ S_CAST(uint32_t, time(nullptr)) };
}
//--------------------------------------------
//! @brief デバイス値を種としたランダム関数の初期化
//! @return なし
//--------------------------------------------
void RandInitDevice()
{
	g_ASRandom = std::mt19937{ std::random_device()() };
}
//--------------------------------------------
//! @brief int型の乱数を取得
//! @return int型の乱数を返す
//--------------------------------------------
int RandInt()
{
	return S_CAST(int32_t, g_ASRandom());
}
//--------------------------------------------
//! @brief 範囲指定のint型の乱数を取得
//! @param [in] nMin 最小値
//! @param [in] nMax 最大値
//! @return 範囲指定のint型の乱数を返す
//--------------------------------------------
int RandRangeInt(int nMin, int nMax)
{
	std::uniform_int_distribution<int> dist(nMin, nMax);
	return dist(g_ASRandom);
}
//--------------------------------------------
//! @brief float型の乱数を取得
//! @return float型の乱数を返す
//--------------------------------------------
float RandFloat()
{
	return S_CAST(float, g_ASRandom());
}
//--------------------------------------------
//! @brief 範囲指定のfloat型の乱数を取得
//! @param [in] fMin 最小値
//! @param [in] fMax 最大値
//! @return 範囲指定のint型の乱数を返す
//--------------------------------------------
float RandRangeFloat(float fMin, float fMax)
{
	std::uniform_real_distribution<float> dist(fMin, fMax);
	return dist(g_ASRandom);
}
//--------------------------------------------
//! @brief float型の乱数を取得
//! @return float型の乱数を返す
//--------------------------------------------
double RandDouble()
{
	return S_CAST(double, g_ASRandom());
}
//--------------------------------------------
//! @brief 範囲指定のdouble型の乱数を取得
//! @param [in] fMin 最小値
//! @param [in] fMax 最大値
//! @return 範囲指定のint型の乱数を返す
//--------------------------------------------
double RandRangeDouble(double fMin, double fMax)
{
	std::uniform_real_distribution<double> dist(fMin, fMax);
	return dist(g_ASRandom);
}
