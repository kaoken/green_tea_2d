#pragma once
/*!
@file math.h
@brief �ʏ�g�����w�֐��Ȃ�
*/

#include <Core/greenTea2D.h>
#include <cfloat>




#define MC_3RANKDECOMPOSE(a, b, c, x, y, z)      \
	if((x) < (y))                   \
	{                               \
		if((y) < (z))               \
		{                           \
			(a) = 2;                \
			(b) = 1;                \
			(c) = 0;                \
		}                           \
		else                        \
		{                           \
			(a) = 1;                \
			\
			if((x) < (z))           \
			{                       \
				(b) = 2;            \
				(c) = 0;            \
			}                       \
			else                    \
			{                       \
				(b) = 0;            \
				(c) = 2;            \
			}                       \
		}                           \
	}                               \
	else                            \
	{                               \
		if((x) < (z))               \
		{                           \
			(a) = 2;                \
			(b) = 0;                \
			(c) = 1;                \
		}                           \
		else                        \
		{                           \
			(a) = 0;                \
			if((y) < (z))           \
			{                       \
				(b) = 2;            \
				(c) = 1;            \
			}                       \
			else                    \
			{                       \
				(b) = 1;            \
				(c) = 2;            \
			}                       \
		}                           \
	}
#define GT2_DECOMP_EPSILON	0.0001f			//!< 
#define GT2_PI				3.1415926536f	//!< 2��
#define GT2_HALF_PI			1.570796327f	//!< 1/2��
#define GT2_PI2				6.283185307f	//!< 2��
#define GT2_INV_PI			0.318309886f	//!< 1/��
#define GT2_INV_PI2			0.159154943f	//!< 1/2��
#define GT2_QUARTER_PI		0.785398163f	//!< ��/4
#define GT2_RADIAN			57.29577951f	//!< 1���W�A��(180/��)
#define GT2_INV_RADIAN		0.01745329252f	//!< ��/180���W�A�� = 1��
#define GT2_EXP				2.718281828f	//!< �l�C�s�A��


#include <Math/lambertW.h>
