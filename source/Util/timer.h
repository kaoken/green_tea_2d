/*
Copyright (c) 2013 kaoken

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software. If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.

3. This notice may not be removed or altered from any source
distribution.
*/
#pragma once


#include <Core/greenTea2D.h>
#include <ctime>
#include <chrono>

//--------------------------------------------------------------------------------------
//! @brief タイマー・オペレーションを行ないます。
//!        グローバルなインスタンスを得るためにGT2GetGlobalTimer()を使用する。
//--------------------------------------------------------------------------------------
class GT2Timer
{
public:
	GT2Timer();
	~GT2Timer();

	void Reset();
	void Start();
	void Stop();
	void Advance();
	double GetAbsoluteTime();
	double GetTime();
	double GetElapsedTime();
	double GetNotUpdateElapsedTime();
	void GetTimeValues(double* pfTime, double* pfAbsoluteTime, float* pfElapsedTime);
	bool IsStopped();

protected:

	double GetMicroSecondTime();
	double GetAdjustedCurrentTime();

	bool m_isUsingQPF;
	bool m_isTimerStopped;

	typedef std::chrono::time_point<std::chrono::system_clock> MC_SYS_CLOCK;
	MC_SYS_CLOCK m_createdTime;
	double m_baseTime;
	double m_stopTime;
	double m_lastElapsedTime;
};
double GetAppSystemTime();
uint32_t GetAppSystemTimeU32();
uint64_t GetAppSystemTimeU64();

GT2Timer* GT2GetGlobalTimer();
#if !defined(_WIN)
int Sleep(mcULONG millisec);
#endif