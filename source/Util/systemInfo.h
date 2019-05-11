#pragma once
#include <Core/greenTea2D.h>


/**
*  OSの種類を表す。
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
	OS_TYPE		osType;			//!< OSの種類
	gtUINT		osVersion[4];	//!< OSのバージョン
	gtUINT		cpuMHz;			//!< このアプリのCPUのMhz単位
	gtUINT		cpuCore;		//!< このアプリのCPUのコア数
	uint64_t	memory;			//!< このアプリのメモリーB単位
	uint64_t	videoMemory;	//!< このアプリのビデオメモリーB単位

	SystemInformation()
	{
		GT2ZeroMemory(this, sizeof(SystemInformation));
	}
};

int GetClockCPU();
bool GetSystemInfo(SystemInformation &out);
double GetCurrentCPUValue();
double GetCurrentProcessCPUValue();

