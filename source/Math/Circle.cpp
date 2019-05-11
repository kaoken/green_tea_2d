#include <Math/circle.h>

//-----------------------------------------------------------------------------------
//! @brief 光線r = p + td, |rvD| = 1が円sに対して交差しているかどうか。
//! @param [in]  rvP 基点
//! @param [in]  rvD 方向ベクトル
//! @param [in]  rS  対象とする円
//! @param [out] pT  0≦ｔ≦Tmax
//! @param [out] pQ  交差した位置
//! @return 交差している場合、交差している*pTの値および交差点*pQを返す
//-----------------------------------------------------------------------------------
bool GT2IntersectRayCircle(const gt2Vector2& rvP, const gt2Vector2& rvD, const gt2Circle2& rS, float *pT, gt2Vector2 *pQ)
{
	gt2Vector2 vM = rvP - rS.c;
	float fB = vM.Dot(rvD);
	float fC = vM.Dot() - rS.r * rS.r;
	// rの原点が*rSの外側にあり(c > 0)、rが*rSから離れていく方向を指している場合(fB > 0)に終了
	if (fC > 0.0f && fB > 0.0f) return false;
	float fDiscr = fB*fB - fC;
	// 負の判別式は光線が円を外れていることに一致
	if (fDiscr < 0.0f) return 0;
	// これで光線は円と交差していることが分かり、交差する最小の値*pTを計算
	*pT = -fB - (float)sqrt(fDiscr);
	// *pTが負である場合、光線は円の内側から開始しているので*pTをゼロにクランプ
	if (*pT < 0.0f) *pT = 0.0f;
	*pQ = rvP + *pT * rvD;
	return true;
}
//-----------------------------------------------------------------------------------
//! @brief 光線r = p + tdが円sと交差しているかどうかを判定
//! @param [in]  rvP 基点
//! @param [in]  rvD 方向ベクトル
//! @param [in]  rS  対象とする円
//! @return 交差している場合、true返す
//-----------------------------------------------------------------------------------
bool GT2RayCircle(const gt2Vector2& rvP, const gt2Vector2& rvD, const gt2Circle2& rS)
{
	gt2Vector2 vM = rvP - rS.c;
	float fC = vM.Dot() - rS.r * rS.r;
	// 少なくとも1つの実数解が存在している場合、交差している
	if (fC <= 0.0f) return true;
	float fB = vM.Dot(rvD);
	// 光線の原点が円の外側にあり光線が円から離れた方向を指している場合には早期に終了
	if (fB > 0.0f) return false;
	float fDiscr = fB*fB - fC;
	// 負の判別式は光線が円を外れていることに一致
	if (fDiscr < 0.0f) return false;
	// これで光線は円と交差している
	return true;
}
//-----------------------------------------------------------------------------------
//! @brief 光線r = p + tdが円sと交差しているかどうかを判定(静止している円rS1に対して交差)
//! @param [in]  rS0 円0
//! @param [in]  rS1 円1
//! @param [in]  rvD 方向ベクトル
//! @param [in]  rS  対象とする円
//! @return trueを返す場合、交差していて、衝突の時間が*pfTに格納される
//-----------------------------------------------------------------------------------
bool GT2MovingCircleCircle(const gt2Circle2& rS0, const gt2Circle2 &rS1, const gt2Vector2 &rV0, const gt2Vector2 &rV1, float *pfT)
{
	// 円s1をs0の半径にまで拡張
	gt2Circle2 S1Ex = rS1;
	S1Ex.r += rS0.r;
	// s0およびs1の両方からs1の運動を引き算し、s1を静止させる
	gt2Vector2 v = rV0 - rV1;
	// これで、方向のある線分 s = s0.c + tv, v = (*pV0-*pV1)/||*pV0-*pV1|| を
	// 拡張した円に対して交差させることができる
	gt2Vector2 vQ;
	float fVLen = v.Length();
	v /= fVLen;
	if (GT2IntersectRayCircle(rS0.c, v, S1Ex, pfT, &vQ)) {
		return *pfT <= fVLen;
	}
	return false;
}