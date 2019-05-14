#include <Math/circle.h>

//-----------------------------------------------------------------------------------
//! @brief ����r = p + td, |rvD| = 1���~s�ɑ΂��Č������Ă��邩�ǂ����B
//! @param [in]  rvP ��_
//! @param [in]  rvD �����x�N�g��
//! @param [in]  rS  �ΏۂƂ���~
//! @param [out] pT  0������Tmax
//! @param [out] pQ  ���������ʒu
//! @return �������Ă���ꍇ�A�������Ă���*pT�̒l����ь����_*pQ��Ԃ�
//-----------------------------------------------------------------------------------
bool GT2IntersectRayCircle(const gt2Vector2& rvP, const gt2Vector2& rvD, const gt2Circle2& rS, float *pT, gt2Vector2 *pQ)
{
	gt2Vector2 vM = rvP - rS.c;
	float fB = vM.Dot(rvD);
	float fC = vM.Dot() - rS.r * rS.r;
	// r�̌��_��*rS�̊O���ɂ���(c > 0)�Ar��*rS���痣��Ă����������w���Ă���ꍇ(fB > 0)�ɏI��
	if (fC > 0.0f && fB > 0.0f) return false;
	float fDiscr = fB*fB - fC;
	// ���̔��ʎ��͌������~���O��Ă��邱�ƂɈ�v
	if (fDiscr < 0.0f) return 0;
	// ����Ō����͉~�ƌ������Ă��邱�Ƃ�������A��������ŏ��̒l*pT���v�Z
	*pT = -fB - (float)sqrt(fDiscr);
	// *pT�����ł���ꍇ�A�����͉~�̓�������J�n���Ă���̂�*pT���[���ɃN�����v
	if (*pT < 0.0f) *pT = 0.0f;
	*pQ = rvP + *pT * rvD;
	return true;
}
//-----------------------------------------------------------------------------------
//! @brief ����r = p + td���~s�ƌ������Ă��邩�ǂ����𔻒�
//! @param [in]  rvP ��_
//! @param [in]  rvD �����x�N�g��
//! @param [in]  rS  �ΏۂƂ���~
//! @return �������Ă���ꍇ�Atrue�Ԃ�
//-----------------------------------------------------------------------------------
bool GT2RayCircle(const gt2Vector2& rvP, const gt2Vector2& rvD, const gt2Circle2& rS)
{
	gt2Vector2 vM = rvP - rS.c;
	float fC = vM.Dot() - rS.r * rS.r;
	// ���Ȃ��Ƃ�1�̎����������݂��Ă���ꍇ�A�������Ă���
	if (fC <= 0.0f) return true;
	float fB = vM.Dot(rvD);
	// �����̌��_���~�̊O���ɂ���������~���痣�ꂽ�������w���Ă���ꍇ�ɂ͑����ɏI��
	if (fB > 0.0f) return false;
	float fDiscr = fB*fB - fC;
	// ���̔��ʎ��͌������~���O��Ă��邱�ƂɈ�v
	if (fDiscr < 0.0f) return false;
	// ����Ō����͉~�ƌ������Ă���
	return true;
}
//-----------------------------------------------------------------------------------
//! @brief ����r = p + td���~s�ƌ������Ă��邩�ǂ����𔻒�(�Î~���Ă���~rS1�ɑ΂��Č���)
//! @param [in]  rS0 �~0
//! @param [in]  rS1 �~1
//! @param [in]  rvD �����x�N�g��
//! @param [in]  rS  �ΏۂƂ���~
//! @return true��Ԃ��ꍇ�A�������Ă��āA�Փ˂̎��Ԃ�*pfT�Ɋi�[�����
//-----------------------------------------------------------------------------------
bool GT2MovingCircleCircle(const gt2Circle2& rS0, const gt2Circle2 &rS1, const gt2Vector2 &rV0, const gt2Vector2 &rV1, float *pfT)
{
	// �~s1��s0�̔��a�ɂ܂Ŋg��
	gt2Circle2 S1Ex = rS1;
	S1Ex.r += rS0.r;
	// s0�����s1�̗�������s1�̉^���������Z���As1��Î~������
	gt2Vector2 v = rV0 - rV1;
	// ����ŁA�����̂������ s = s0.c + tv, v = (*pV0-*pV1)/||*pV0-*pV1|| ��
	// �g�������~�ɑ΂��Č��������邱�Ƃ��ł���
	gt2Vector2 vQ;
	float fVLen = v.Length();
	v /= fVLen;
	if (GT2IntersectRayCircle(rS0.c, v, S1Ex, pfT, &vQ)) {
		return *pfT <= fVLen;
	}
	return false;
}