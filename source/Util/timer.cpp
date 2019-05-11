#include <Util/timer.h>

using namespace std::chrono;

//!< アプリを起動時に起動した時間を取得する
static system_clock::time_point g_startTimePoint = system_clock::now();

//-----------------------------------------------------------------------------------
//! @brief 静的なGT2Timerクラスポインタを返す
//! @return GT2Timerクラスポインタ
//-----------------------------------------------------------------------------------
GT2Timer* GT2GetGlobalTimer()
{
	static GT2Timer timer;
	return &timer;
}


//-----------------------------------------------------------------------------------
//! @brief コンストラクタ
//-----------------------------------------------------------------------------------
GT2Timer::GT2Timer()
{
	m_isUsingQPF = false;
	m_isTimerStopped = true;
	m_createdTime = system_clock::now();
	m_baseTime = 0;
	m_stopTime = 0;
	m_lastElapsedTime = 0;
}
//-----------------------------------------------------------------------------------
//! @brief デスストラクタ
//-----------------------------------------------------------------------------------
GT2Timer::~GT2Timer()
{
	if (!this->IsStopped()){
		this->Stop();
	}
}


//-----------------------------------------------------------------------------------
//! @brief アプリ起動後の経過時間、マイクロ秒精度で返す。
//! @return アプリ起動後の経過時間、マイクロ秒精度で返す。
//-----------------------------------------------------------------------------------
double GT2Timer::GetMicroSecondTime()
{
	return (duration_cast<microseconds>(system_clock::now() - m_createdTime).count()) * 1e-6;
}

//-----------------------------------------------------------------------------------
//! @brief タイマーをリセットする。
//! @return なし
//-----------------------------------------------------------------------------------
void GT2Timer::Reset()
{
	m_baseTime = this->GetAdjustedCurrentTime();
	m_lastElapsedTime = this->GetAdjustedCurrentTime();
	m_stopTime = 0;
	m_isTimerStopped = false;
}

//-----------------------------------------------------------------------------------
//! @brief タイマーをスタートする。
//! @return なし
//-----------------------------------------------------------------------------------
void GT2Timer::Start()
{
	// 現在の時刻を取得する
	double nowT = this->GetAdjustedCurrentTime();

	if (m_isTimerStopped)
		m_baseTime += nowT - m_stopTime;
	m_stopTime = 0;
	m_lastElapsedTime = nowT;
	m_isTimerStopped = false;
}

//-----------------------------------------------------------------------------------
//! @brief タイマーをストップする。
//! @return なし
//-----------------------------------------------------------------------------------
void GT2Timer::Stop()
{
	if (!m_isTimerStopped)
	{
		double nowT = this->GetAdjustedCurrentTime();
		m_stopTime = nowT;
		m_lastElapsedTime = nowT;
		m_isTimerStopped = true;
	}
}


//-----------------------------------------------------------------------------------
//! @brief 呼び出すごとに、0.1秒ずつタイマーを進める
//! @return なし
//-----------------------------------------------------------------------------------
void GT2Timer::Advance()
{
	m_stopTime += 0.1;
}


//-----------------------------------------------------------------------------------
//! @brief 絶対時間を取得する
//! @return 絶対時間を返す
//-----------------------------------------------------------------------------------
double GT2Timer::GetAbsoluteTime()
{
	return this->GetAdjustedCurrentTime();
}

//-----------------------------------------------------------------------------------
//! @brief 現在の時間を取得する
//! @return 現在の時間を返す
//-----------------------------------------------------------------------------------
double GT2Timer::GetTime()
{
	return this->GetAdjustedCurrentTime() - m_baseTime;
}

//-----------------------------------------------------------------------------------
//! @brief 時間の値をすべて取得する
//! @param [out] pfTime         現在の時間
//! @param [out] pfAbsoluteTime 絶対時間
//! @param [out] pfElapsedTime  最終のフレームからの経過した時間
//! @return なし
//-----------------------------------------------------------------------------------
void GT2Timer::GetTimeValues(double* pfTime, double* pfAbsoluteTime, float* pfElapsedTime)
{
	assert(pfTime && pfAbsoluteTime && pfElapsedTime);
	double nowT = this->GetAdjustedCurrentTime();

	float elapsedTime = (float)(nowT - m_lastElapsedTime);
	m_lastElapsedTime = nowT;
	if (elapsedTime < 0.0f)
		elapsedTime = 0.0f;

	*pfAbsoluteTime = nowT;
	*pfTime = nowT - m_baseTime;
	*pfElapsedTime = elapsedTime;
}

//-----------------------------------------------------------------------------------
//! @brief フレーム更新してない、呼び出し経過時間を取得します
//! @return フレーム更新してない、呼び出し経過時間を返す
//-----------------------------------------------------------------------------------
double GT2Timer::GetNotUpdateElapsedTime()
{
	double elapsedTime;
	elapsedTime = this->GetAdjustedCurrentTime() - m_lastElapsedTime;
	if (elapsedTime < 0.0)
		elapsedTime = 0.0;

	return elapsedTime;
}

//-----------------------------------------------------------------------------------
//! @brief 前回 GetElapsedTime()を呼び出した時の時間差を返す
//! @return 前回 GetElapsedTime()を呼び出した時の時間差を返す
//-----------------------------------------------------------------------------------
double GT2Timer::GetElapsedTime()
{
	double elapsedTime;
	double nowT = this->GetAdjustedCurrentTime();
	elapsedTime = nowT - m_lastElapsedTime;
	m_lastElapsedTime = nowT;

	if (elapsedTime < 0.0f)
		elapsedTime = 0.0f;

	return elapsedTime;
}

//-----------------------------------------------------------------------------------
//! @brief もし止められれば、止められた時間を返し、そうでなければ現在の時刻を返す。
//! @return 時間を返す
//-----------------------------------------------------------------------------------
double GT2Timer::GetAdjustedCurrentTime()
{
	if (m_stopTime != 0.0) return m_stopTime;
	return this->GetMicroSecondTime();
}

//-----------------------------------------------------------------------------------
//! @brief タイマーが止まっているか？
//! @return 止まっている場合はtrueを返す
//-----------------------------------------------------------------------------------
bool GT2Timer::IsStopped()
{
	return m_isTimerStopped;
}

//-----------------------------------------------------------------------------------
//! @brief このアプリの経過時間をミリ秒単位で返す。
//! @return このアプリの経過時間をミリ秒単位で返す。
//-----------------------------------------------------------------------------------
double GetAppSystemTime()
{
	return (duration_cast<milliseconds>(system_clock::now() - g_startTimePoint).count()) * 1e-3;
}

//-----------------------------------------------------------------------------------
//! @brief このアプリの経過時間をミリ秒単位で返す。
//! @return このアプリの経過時間をミリ秒単位で返す。
//-----------------------------------------------------------------------------------
uint32_t GetAppSystemTimeU32()
{
	return (uint32_t)(duration_cast<milliseconds>(system_clock::now() - g_startTimePoint).count());
}

//-----------------------------------------------------------------------------------
//! @brief このアプリの経過時間をミリ秒単位で返す。
//! @return このアプリの経過時間をミリ秒単位で返す。
//-----------------------------------------------------------------------------------
uint64_t GetAppSystemTimeU64()
{
	return (uint64_t)(duration_cast<milliseconds>(system_clock::now() - g_startTimePoint).count());
}

#if !defined(_WIN)
inline int __sleep(const struct timespec *req, struct timespec *rem)
{
	int ret = 1;
	int i;
	static const int sleepTries = 2;

	struct timespec req_tmp = { 0 }, rem_tmp = { 0 };

	rem_tmp = *req;
	for (i = 0; i < sleepTries; ++i)
	{
		req_tmp = rem_tmp;
		int ret = nanosleep(&req_tmp, &rem_tmp);
		if (ret == 0)
		{
			ret = 0;
			break;
		}
	}
	if (rem)
		*rem = rem_tmp;
	return ret;
}
int Sleep(mcULONG millisec)
{
	struct timespec req = { 0 }, rem = { 0 };
	time_t sec = (int)(millisec / 1000);

	millisec = millisec - (sec * 1000);
	req.tv_sec = sec;
	req.tv_nsec = millisec * 1000000L;
	return __sleep(&req, &rem);
}
#endif