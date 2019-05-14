#include <Util/timer.h>

using namespace std::chrono;

//!< �A�v�����N�����ɋN���������Ԃ��擾����
static system_clock::time_point g_startTimePoint = system_clock::now();

//-----------------------------------------------------------------------------------
//! @brief �ÓI��GT2Timer�N���X�|�C���^��Ԃ�
//! @return GT2Timer�N���X�|�C���^
//-----------------------------------------------------------------------------------
GT2Timer* GT2GetGlobalTimer()
{
	static GT2Timer timer;
	return &timer;
}


//-----------------------------------------------------------------------------------
//! @brief �R���X�g���N�^
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
//! @brief �f�X�X�g���N�^
//-----------------------------------------------------------------------------------
GT2Timer::~GT2Timer()
{
	if (!this->IsStopped()){
		this->Stop();
	}
}


//-----------------------------------------------------------------------------------
//! @brief �A�v���N����̌o�ߎ��ԁA�}�C�N���b���x�ŕԂ��B
//! @return �A�v���N����̌o�ߎ��ԁA�}�C�N���b���x�ŕԂ��B
//-----------------------------------------------------------------------------------
double GT2Timer::GetMicroSecondTime()
{
	return (duration_cast<microseconds>(system_clock::now() - m_createdTime).count()) * 1e-6;
}

//-----------------------------------------------------------------------------------
//! @brief �^�C�}�[�����Z�b�g����B
//! @return �Ȃ�
//-----------------------------------------------------------------------------------
void GT2Timer::Reset()
{
	m_baseTime = this->GetAdjustedCurrentTime();
	m_lastElapsedTime = this->GetAdjustedCurrentTime();
	m_stopTime = 0;
	m_isTimerStopped = false;
}

//-----------------------------------------------------------------------------------
//! @brief �^�C�}�[���X�^�[�g����B
//! @return �Ȃ�
//-----------------------------------------------------------------------------------
void GT2Timer::Start()
{
	// ���݂̎������擾����
	double nowT = this->GetAdjustedCurrentTime();

	if (m_isTimerStopped)
		m_baseTime += nowT - m_stopTime;
	m_stopTime = 0;
	m_lastElapsedTime = nowT;
	m_isTimerStopped = false;
}

//-----------------------------------------------------------------------------------
//! @brief �^�C�}�[���X�g�b�v����B
//! @return �Ȃ�
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
//! @brief �Ăяo�����ƂɁA0.1�b���^�C�}�[��i�߂�
//! @return �Ȃ�
//-----------------------------------------------------------------------------------
void GT2Timer::Advance()
{
	m_stopTime += 0.1;
}


//-----------------------------------------------------------------------------------
//! @brief ��Ύ��Ԃ��擾����
//! @return ��Ύ��Ԃ�Ԃ�
//-----------------------------------------------------------------------------------
double GT2Timer::GetAbsoluteTime()
{
	return this->GetAdjustedCurrentTime();
}

//-----------------------------------------------------------------------------------
//! @brief ���݂̎��Ԃ��擾����
//! @return ���݂̎��Ԃ�Ԃ�
//-----------------------------------------------------------------------------------
double GT2Timer::GetTime()
{
	return this->GetAdjustedCurrentTime() - m_baseTime;
}

//-----------------------------------------------------------------------------------
//! @brief ���Ԃ̒l�����ׂĎ擾����
//! @param [out] pfTime         ���݂̎���
//! @param [out] pfAbsoluteTime ��Ύ���
//! @param [out] pfElapsedTime  �ŏI�̃t���[������̌o�߂�������
//! @return �Ȃ�
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
//! @brief �t���[���X�V���ĂȂ��A�Ăяo���o�ߎ��Ԃ��擾���܂�
//! @return �t���[���X�V���ĂȂ��A�Ăяo���o�ߎ��Ԃ�Ԃ�
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
//! @brief �O�� GetElapsedTime()���Ăяo�������̎��ԍ���Ԃ�
//! @return �O�� GetElapsedTime()���Ăяo�������̎��ԍ���Ԃ�
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
//! @brief �����~�߂���΁A�~�߂�ꂽ���Ԃ�Ԃ��A�����łȂ���Ό��݂̎�����Ԃ��B
//! @return ���Ԃ�Ԃ�
//-----------------------------------------------------------------------------------
double GT2Timer::GetAdjustedCurrentTime()
{
	if (m_stopTime != 0.0) return m_stopTime;
	return this->GetMicroSecondTime();
}

//-----------------------------------------------------------------------------------
//! @brief �^�C�}�[���~�܂��Ă��邩�H
//! @return �~�܂��Ă���ꍇ��true��Ԃ�
//-----------------------------------------------------------------------------------
bool GT2Timer::IsStopped()
{
	return m_isTimerStopped;
}

//-----------------------------------------------------------------------------------
//! @brief ���̃A�v���̌o�ߎ��Ԃ��~���b�P�ʂŕԂ��B
//! @return ���̃A�v���̌o�ߎ��Ԃ��~���b�P�ʂŕԂ��B
//-----------------------------------------------------------------------------------
double GetAppSystemTime()
{
	return (duration_cast<milliseconds>(system_clock::now() - g_startTimePoint).count()) * 1e-3;
}

//-----------------------------------------------------------------------------------
//! @brief ���̃A�v���̌o�ߎ��Ԃ��~���b�P�ʂŕԂ��B
//! @return ���̃A�v���̌o�ߎ��Ԃ��~���b�P�ʂŕԂ��B
//-----------------------------------------------------------------------------------
uint32_t GetAppSystemTimeU32()
{
	return (uint32_t)(duration_cast<milliseconds>(system_clock::now() - g_startTimePoint).count());
}

//-----------------------------------------------------------------------------------
//! @brief ���̃A�v���̌o�ߎ��Ԃ��~���b�P�ʂŕԂ��B
//! @return ���̃A�v���̌o�ߎ��Ԃ��~���b�P�ʂŕԂ��B
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