//-----------------------------------------------------------------------------------
// �t�@�C���F mcSegment.h, mcSegment.inl
//
// ���@���@�F
// �@������\��
//   
//�@
// ���@���@�F
// �@2007/03/08 Ver.0.1 ����J�n
//
//
// ��@��@�F
// �@Copyright(c)2006 METAL CUBE All rights reserved worldwide..
// �@
//-----------------------------------------------------------------------------------
#pragma once

#include <Math/vector.h>

// [min, max]�͈͓̔��܂�n���N�����v
inline float SegmentClamp(float n, float min, float max)
{
	if (n < min) return min;
	if (n > max) return max;
	return n;
}

//-----------------------------------------------------------------------------------
// [ ���� ] public
//  �_c�Ɛ���vAB�̊Ԃ̋����̕�����Ԃ�
// [ ���� ]
//  pvA	�F[in] ��_
//  pvB	�F[in] �I�_
//  pvC	�F[in] �_
// [ �߂�l ]
//   �֐��̌��ʂ�S1(*pfS)��S2(*pfT)�̊Ԃ̋����̕���
//-----------------------------------------------------------------------------------
template<typename T_VECTOR>
float SqDistPointSegment(const T_VECTOR& a, const T_VECTOR& rvB, const T_VECTOR& rvC)
{
	T_VECTOR vAB = rvB - a, vAC = rvC - a, vBC = rvC - rvB;
	float fE = vAC.Dot(vAB);
	// c��vAB�̊O���Ɏˉe�����ꍇ������
	if (fE <= 0.0f) return vAC.Dot();
	float fF = vAB.Dot();
	if (fE >= fF) return vBC.Dot();
	// c��vAB��Ɏˉe�����ꍇ������
	return vAC.Dot() - fE * fE / fF;
}
//-----------------------------------------------------------------------------------
// [ ���� ] public
//  S1(*pfS)=P1+*pfS*(Q1-P1)�����S2(*pfT)=P2+*pfT*(Q2-P2)��
//  S�����*pfT��Ԃ��B
// [ ���� ]
//  pvP1	�F[in] ��_1
//  pvQ1	�F[in] �I�_1
//  pvP2	�F[in] ��_2
//  pvQ2	�F[in] �I�_2
//  pfS		�F[out] 0 �� s �� 1
//  pfT		�F[out] 0 �� s �� 1
//  pvC1	�F[out] �ŋߐړ_ ��_
//  pvC2	�F[out] �ŋߐړ_ �I�_
// [ �߂�l ]
//   �֐��̌��ʂ�S1(*pfS)��S2(*pfT)�̊Ԃ̋����̕���
//-----------------------------------------------------------------------------------
template<typename T_VECTOR>
float ClosestPtSegmentSegment(const T_VECTOR& rvP1, const T_VECTOR& rvQ1, const T_VECTOR& rvP2, const T_VECTOR& rvQ2,
	float *pfS, float *pfT, T_VECTOR *pvC1 = nullptr, T_VECTOR *pvC2 = nullptr)
{
	T_VECTOR vD1 = rvQ1 - rvP1; // ����S1�̕����x�N�g��
	T_VECTOR vD2 = rvQ2 - rvP2; // ����S2�̕����x�N�g��
	T_VECTOR vR = rvP1 - rvP2;
	float fA = vD1.Dot(); // ����S1�̋����̕����A��ɔ�
	float fE = vD2.Dot(); // ����S2�̋����̕����A��ɔ�
	float fF = vD2.Dot(vR);

	// �Е����邢�͗����̐������_�ɏk�ނ��Ă��邩�ǂ����`�F�b�N
	if (fA <= 0.0001f && fE <= 0.0001f) {
		// �����̐������_�ɏk��
		*pfS = *pfT = 0.0f;
		if (pvC1) *pvC1 = rvP1;
		if (pvC2) *pvC2 = rvP2;
		return (rvP1 - rvP2).Dot((rvP1 - rvP2));
	}
	if (fA <= 0.0001f) {
		// �ŏ��̐������_�ɏk��
		*pfS = 0.0f;
		*pfT = fF / fE; // *pfS = 0 => *pfT = (fB**pfS + fF) / fE = fF / fE
		*pfT = SegmentClamp(*pfT, 0.0f, 1.0f);
	}
	else {
		float fC = vD1.Dot(vR);
		if (fE <= 0.0001f) {
			// 2�Ԗڂ̐������_�ɏk��
			*pfT = 0.0f;
			*pfS = SegmentClamp(-fC / fA, 0.0f, 1.0f); // *pfT = 0 => *pfS = (fB**pfT - fC) / fA = -fC / fA
		}
		else {
			// ���������ʓI�ȏk�ނ̏ꍇ���J�n
			float fB = vD1.Dot(vD2);
			float fDenom = fA*fE - fB*fB; // ��ɔ�

											// ���������s�łȂ��ꍇ�AL1���L2�ɑ΂���ŋߐړ_���v�Z�A������
											// ����S1�ɑ΂��ăN�����v�B�����łȂ��ꍇ�͔C��*pfS(�����ł�0)��I��
			if (fDenom != 0.0f) {
				*pfS = SegmentClamp((fB*fF - fC*fE) / fDenom, 0.0f, 1.0f);
			}
			else {
				*pfS = 0.0f;
			}

			//	// L2���S1(*pfS)�ɑ΂���ŋߐړ_���ȉ���p���Čv�Z
			//	// *pfT = Dot((P1+D1*(*pfS))-P2,D2) / Dot(D2,D2) = (fB**pfS + fF) / fE
			//	*pfT = (fB*(*pfS) + fF) / fE;

			//	// *pfT��[0,1]�̒��ɂ���ΏI���B�����łȂ����*pfT���N�����v�A*pfS��*pfT�̐V�����l�ɑ΂��Ĉȉ���p���čČv�Z
			//	// *pfS = Dot((P2+D2*(*pfT))-P1,D1) / Dot(D1,D1)= (*pfT*fB - fC) / fA
			//	// ������*pfS��[0, 1]�ɑ΂��ăN�����v
			//	if (*pfT < 0.0f) {
			//		*pfT = 0.0f;
			//		*pfS = SegmentClamp(-fC / fA, 0.0f, 1.0f);
			//	} else if (*pfT > 1.0f) {
			//		*pfT = 1.0f;
			//		*pfS = SegmentClamp((fB - fC) / fA, 0.0f, 1.0f);
			//	}
			//---------------------------------------------------------
			// ��L�̃R�����g�����̍œK��
			float fTnom = fB*(*pfS) + fF;
			if (fTnom < 0.0f) {
				*pfT = 0.0f;
				*pfS = SegmentClamp(-fC / fA, 0.0f, 1.0f);
			}
			else if (fTnom > fE) {
				*pfT = 1.0f;
				*pfS = SegmentClamp((fB - fC) / fA, 0.0f, 1.0f);
			}
			else {
				*pfT = fTnom / fE;
			}
		}

	}
	T_VECTOR vC1 = rvP1 + vD1 * *pfS;
	T_VECTOR vC2 = rvP2 + vD2 * *pfT;
	if (pvC1) *pvC1 = vC1;
	if (pvC2) *pvC2 = vC2;
	return (vC1 - vC2).Dot((vC1 - vC2));
}

struct gt2Segment2
{
	gt2Vector2	vStart;	// �n�_
	gt2Vector2	vEnd;	// �I�_
public:
	// �������擾
	inline float GetHeight() const { return (vEnd - vStart).Length(); };
	// �������擾
	inline gt2Vector2* GetDirection(gt2Vector2* pOut) const {
		(vEnd - vStart).Normalize(pOut);
		return pOut;
	};
	inline gt2Vector2* GetCenterPoint(gt2Vector2* pOut) const {
		*pOut = (vEnd + vStart)*0.5f;
		return pOut;
	};
	//-----------------------------------------------------------------------------------
	// [ ���� ] public
	//  �_c�Ɛ���vAB�̊Ԃ̋����̕�����Ԃ�
	// [ ���� ]
	//  pvC	�F[in] �_
	// [ �߂�l ]
	//   �֐��̌��ʂ�S1(*pfS)��S2(*pfT)�̊Ԃ̋����̕���
	//-----------------------------------------------------------------------------------
	float SqDistPointSegment(const gt2Vector2& rvC) const
	{
		return ::SqDistPointSegment(vStart, vEnd, rvC);
	}

	//-----------------------------------------------------------------------------------
	// [ ���� ] public
	//  S1(*pfS)=P1+*pfS*(Q1-P1)�����S2(*pfT)=P2+*pfT*(Q2-P2)��
	//  �ŋߐړ_C1�����C2���v�Z�AS�����*pfT��Ԃ��B
	// [ ���� ]
	//  pvPQ2	�F[in] ����
	//  pfS		�F[out] 0 �� s �� 1
	//  pfT		�F[out] 0 �� s �� 1
	//  pvC1	�F[out] �ŋߐړ_ ��_
	//  pvC2	�F[out] �ŋߐړ_ �I�_
	// [ �߂�l ]
	//   �֐��̌��ʂ�S1(*pfS)��S2(*pfT)�̊Ԃ̋����̕���
	//-----------------------------------------------------------------------------------
	float ClosestPtSegmentSegment(
			const gt2Segment2 *pvPQ2,
			float *pfS, float *pfT, gt2Vector2 *pvC1, gt2Vector2 *pvC2) const
	{
		return ::ClosestPtSegmentSegment(vStart, vEnd, pvPQ2->vStart, pvPQ2->vEnd, pfS, pfT, pvC1, pvC2);
	}
	//-----------------------------------------------------------------------------------
	// [ ���� ]
	//  pvPQ2	�F[in] ����
	//  pfS		�F[out] 0 �� s �� 1
	//  pfT		�F[out] 0 �� s �� 1
	//  pvC		�F[out] �ŋߐړ_
	//-----------------------------------------------------------------------------------
	float ClosestPtSegmentSegment(const gt2Segment2 *pvPQ2,
			float *pfS, float *pfT, gt2Segment2 *pvC) const
	{
		return ::ClosestPtSegmentSegment(vStart, vEnd, pvPQ2->vStart, pvPQ2->vEnd, pfS, pfT, &pvC->vStart, &pvC->vEnd);
	}
	//-----------------------------------------------------------------------------------
	// [ ���� ]
	//  pvP2	�F[in] ��_2
	//  pvQ2	�F[in] �I�_2
	//  pfS		�F[out] 0 �� s �� 1
	//  pfT		�F[out] 0 �� s �� 1
	//  pvC1	�F[out] �ŋߐړ_ ��_
	//  pvC2	�F[out] �ŋߐړ_ �I�_
	//-----------------------------------------------------------------------------------
	float ClosestPtSegmentSegment(
			const gt2Vector2& rvP2, const gt2Vector2& rvQ2,
			float *pfS, float *pfT, gt2Vector2 *pvC1, gt2Vector2 *pvC2) const
	{
		return ::ClosestPtSegmentSegment(vStart, vEnd, rvP2, rvQ2, pfS, pfT, pvC1, pvC2);
	}


};


struct mcSegment3
{
	gt2Vector3	vStart;	// �n�_
	gt2Vector3	vEnd;	// �I�_
public:
	mcSegment3() { Init(); }
	mcSegment3(const gt2Vector3 &s, const gt2Vector3 &e) {
		vStart = s;
		vEnd = e;
	}
	// �������擾
	inline float GetHeight() const { return (vEnd - vStart).Length(); };
	// �������擾
	inline gt2Vector3 GetDirection() const {
		gt2Vector3 out;
		(vEnd - vStart).Normalize(&out);
		return out;
	};
	inline gt2Vector3 GetCenterPoint() const {
		gt2Vector3 out = (vEnd + vStart)*0.5f;
		return out;
	};
	void Init() { vStart.Init(); vEnd.Init(); }
	//-----------------------------------------------------------------------------------
	// [ ���� ] public
	//  �_c�Ɛ���vAB�̊Ԃ̋����̕�����Ԃ�
	// [ ���� ]
	//  pvC	�F[in] �_
	// [ �߂�l ]
	//   �֐��̌��ʂ�S1(*pfS)��S2(*pfT)�̊Ԃ̋����̕���
	//-----------------------------------------------------------------------------------
	float SqDistPointSegment(const gt2Vector3& rvC) const
	{
		return ::SqDistPointSegment(vStart, vEnd, rvC);
	}

	//-----------------------------------------------------------------------------------
	// [ ���� ] public
	//  S1(*pfS)=P1+*pfS*(Q1-P1)�����S2(*pfT)=P2+*pfT*(Q2-P2)��
	//  �ŋߐړ_C1�����C2���v�Z�AS�����*pfT��Ԃ��B
	// [ ���� ]
	//  pvPQ2	�F[in] ����
	//  pfS		�F[out] 0 �� s �� 1
	//  pfT		�F[out] 0 �� s �� 1
	//  pvC1	�F[out] �ŋߐړ_ ��_
	//  pvC2	�F[out] �ŋߐړ_ �I�_
	// [ �߂�l ]
	//   �֐��̌��ʂ�S1(*pfS)��S2(*pfT)�̊Ԃ̋����̕���
	//-----------------------------------------------------------------------------------
	float ClosestPtSegmentSegment(
			const mcSegment3 *pvPQ2,
			float *pfS, float *pfT, gt2Vector3 *pvC1, gt2Vector3 *pvC2) const
	{
		return ::ClosestPtSegmentSegment(vStart, vEnd, pvPQ2->vStart, pvPQ2->vEnd, pfS, pfT, pvC1, pvC2);
	}
	//-----------------------------------------------------------------------------------
	// [ ���� ]
	//  pvPQ2	�F[in] ����
	//  pfS		�F[out] 0 �� s �� 1
	//  pfT		�F[out] 0 �� s �� 1
	//  pvC		�F[out] �ŋߐړ_
	//-----------------------------------------------------------------------------------
	float ClosestPtSegmentSegment(const mcSegment3 *pvPQ2,
			float *pfS, float *pfT, mcSegment3 *pvC) const
	{
		return ::ClosestPtSegmentSegment(vStart, vEnd, pvPQ2->vStart, pvPQ2->vEnd, pfS, pfT, &pvC->vStart, &pvC->vEnd);
	}
	//-----------------------------------------------------------------------------------
	// [ ���� ]
	//  pvP2	�F[in] ��_2
	//  pvQ2	�F[in] �I�_2
	//  pfS		�F[out] 0 �� s �� 1
	//  pfT		�F[out] 0 �� s �� 1
	//  pvC1	�F[out] �ŋߐړ_ ��_
	//  pvC2	�F[out] �ŋߐړ_ �I�_
	//-----------------------------------------------------------------------------------
	float ClosestPtSegmentSegment(
			const gt2Vector3& rvP2, const gt2Vector3& rvQ2,
			float *pfS, float *pfT, gt2Vector3 *pvC1, gt2Vector3 *pvC2) const
	{
		return ::ClosestPtSegmentSegment(vStart, vEnd, rvP2, rvQ2, pfS, pfT, pvC1, pvC2);
	}
};
