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
// [ ���� ] 
//  �񎟕������������A�ŏ��l��Ԃ��B
// [ ���� ]
//  fA		:[in] a
//  fB		:[in] b
//  fC		:[in] c
//  pTime	:[in,out] �O�`�P�͈̔͂̎��Ԃ̒l���Z�b�g����
// [ �߂�l ]
//  false�̏ꍇ���Ȃ��@true�̏ꍇ������
//-----------------------------------------------------------------------------------
bool FindLowestRootInInterval(float fA, float fB, float fC, float *pTime)
{
	// ���ʎ�
	float fDeterminant = fB*fB - 4.0f*fA*fC;

	// ���ꂪ���Ȃ���͕��f���D
	if (fDeterminant < 0.0f) return false;

	// ��������������@�̓R���s���[�^�Ɉˑ�����
	//      -b �}��(-b^2-4ac)
	// x = -------------------
	//             2a
	// a��0�߂��ł���ꍇ�A��L�̎��́A���肵�Ȃ��B
	float fQ = -0.5f*(fB + (fB < 0.0f ? -1.0f : 1.0f) * sqrtf(fDeterminant));
	// ���L�̓��+INF�A-INF���邢��NAN��Ԃ����Ƃ��ł���B
	float x1 = fQ / fA;
	float x2 = fC / fQ;

	// ���ёւ������邩�H
	if (x1 > x2)
	{
		float temp = x2;
		x2 = x1;
		x1 = temp;
	}

	// �l���͈͓���:[0 pTime]
	if (x1 > 0.0f && x1 < *pTime)
	{
		*pTime = x1;
		return true;
	}

	// x2���g�p���邱�Ƃ�����
	// if r1 < 0
	if (x2 > 0.0f && x2 < *pTime)
	{
		*pTime = x2;
		return true;
	}
	// �����Ȃ�
	return false;
}

//-----------------------------------------------------------------------------------
// [ ���� ]
//  �O�p�`ABC�ɑ΂���_P���� �d�S���W(*pvCenter)���擾����
//
// [ ���� ]
//  vA	�F[in] �_A
//  vB	�F[in] �_B
//  vC	�F[in] �_C
//  vP	�F[in] �_P
//  pvCenter�F[out] �d�S���W
//
// [ �߂�l ]
//  ����
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
//! @brief ���l����Ƃ��������_���֐��̏�����
//! @param [in] u �����_���̌��ƂȂ鐔�l
//! @return �Ȃ�
//--------------------------------------------
void RandInit(uint32_t u)
{
	g_ASRandom = std::mt19937{ u };
}
//--------------------------------------------
//! @brief ���Ԃ���Ƃ��������_���֐��̏�����
//! @return �Ȃ�
//--------------------------------------------
void RandInitNowTime()
{
	g_ASRandom = std::mt19937{ S_CAST(uint32_t, time(nullptr)) };
}
//--------------------------------------------
//! @brief �f�o�C�X�l����Ƃ��������_���֐��̏�����
//! @return �Ȃ�
//--------------------------------------------
void RandInitDevice()
{
	g_ASRandom = std::mt19937{ std::random_device()() };
}
//--------------------------------------------
//! @brief int�^�̗������擾
//! @return int�^�̗�����Ԃ�
//--------------------------------------------
int RandInt()
{
	return S_CAST(int32_t, g_ASRandom());
}
//--------------------------------------------
//! @brief �͈͎w���int�^�̗������擾
//! @param [in] nMin �ŏ��l
//! @param [in] nMax �ő�l
//! @return �͈͎w���int�^�̗�����Ԃ�
//--------------------------------------------
int RandRangeInt(int nMin, int nMax)
{
	std::uniform_int_distribution<int> dist(nMin, nMax);
	return dist(g_ASRandom);
}
//--------------------------------------------
//! @brief float�^�̗������擾
//! @return float�^�̗�����Ԃ�
//--------------------------------------------
float RandFloat()
{
	return S_CAST(float, g_ASRandom());
}
//--------------------------------------------
//! @brief �͈͎w���float�^�̗������擾
//! @param [in] fMin �ŏ��l
//! @param [in] fMax �ő�l
//! @return �͈͎w���int�^�̗�����Ԃ�
//--------------------------------------------
float RandRangeFloat(float fMin, float fMax)
{
	std::uniform_real_distribution<float> dist(fMin, fMax);
	return dist(g_ASRandom);
}
//--------------------------------------------
//! @brief float�^�̗������擾
//! @return float�^�̗�����Ԃ�
//--------------------------------------------
double RandDouble()
{
	return S_CAST(double, g_ASRandom());
}
//--------------------------------------------
//! @brief �͈͎w���double�^�̗������擾
//! @param [in] fMin �ŏ��l
//! @param [in] fMax �ő�l
//! @return �͈͎w���int�^�̗�����Ԃ�
//--------------------------------------------
double RandRangeDouble(double fMin, double fMax)
{
	std::uniform_real_distribution<double> dist(fMin, fMax);
	return dist(g_ASRandom);
}
