#pragma once
#include <Core/greenTea2D.h>


/**
*  OS�̎�ނ�\���B
*/
enum OS_TYPE
{
	WIN = 0,	//!< Windows
	MAC,		//!< Mac	
	IOS,		//!< iOS
	ANDROID,	//!< Android
	LINUX		//!< Linux
};

struct SystemInformation {
public:
	OS_TYPE		osType;			//!< OS�̎��
	gtUINT		osVersion[4];	//!< OS�̃o�[�W����
	gtUINT		cpuMHz;			//!< ���̃A�v����CPU��Mhz�P��
	gtUINT		cpuCore;		//!< ���̃A�v����CPU�̃R�A��
	uint64_t	memory;			//!< ���̃A�v���̃������[B�P��
	uint64_t	videoMemory;	//!< ���̃A�v���̃r�f�I�������[B�P��

	SystemInformation()
	{
		GT2ZeroMemory(this, sizeof(SystemInformation));
	}
};

int GetClockCPU();
bool GetSystemInfo(SystemInformation &out);
double GetCurrentCPUValue();
double GetCurrentProcessCPUValue();

