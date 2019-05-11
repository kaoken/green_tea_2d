#include"systemInfo.h"

#ifndef _WIN
#  include <sys/times.h>
#  include <sys/vtimes.h>
#  include <sys/types.h>
#  include <sys/sysctl.h>
#else
#  include <pdh.h>
#  include <psapi.h>
#endif


bool GetSystemInfo(SystemInformation &out)
{
	out.cpuMHz = GetClockCPU();
#if defined(_WIN32) || defined(_WIN64)
	out.osType = OS_TYPE::WIN;
	//----------------------------
	// バージョン情報の取得 
	OSVERSIONINFOEX OSver;
	ULONGLONG condition = 0;
	OSver.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	OSver.dwMajorVersion = 6;
	OSver.dwMinorVersion = 1;

	VER_SET_CONDITION(condition, VER_MAJORVERSION, VER_EQUAL);
	VER_SET_CONDITION(condition, VER_MINORVERSION, VER_EQUAL);

	if (VerifyVersionInfo(&OSver, VER_MAJORVERSION | VER_MINORVERSION, condition))
	{
		out.osVersion[0] = OSver.dwMajorVersion;
		out.osVersion[1] = OSver.dwMinorVersion;
	}

	//----------------------------
	// 物理メモリサイズ
	MEMORYSTATUSEX ms = { sizeof(MEMORYSTATUSEX) };
	GlobalMemoryStatusEx(&ms);
	out.memory = ms.ullTotalPhys;
	//----------------------------
	// CPU 
	SYSTEM_INFO info;
	GetSystemInfo(&info);

	out.cpuCore = info.dwNumberOfProcessors;
#elif defined(MC_ANDROID)
	out.osType = AS_OS_TYPE::ANDROID;

	//----------------------------
	// 物理メモリサイズ
	out.memory = memInfo.totalram;
	//次のステートメントの右側に整数オーバーフローを避けるために乗算.
	out.memory *= memInfo.mem_unit;
#endif

	return true;
}

/**
	* @brief CPUのクロック周波数を返す。単位はMHz
	* @return  CPUのクロック周波数を返す。
	*/
int GetClockCPU(void)
{
#if defined(_WIN32) || defined(_WIN64)
	HKEY key;
	DWORD result;
	DWORD size = 4;

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0"), 0, KEY_READ, &key) != ERROR_SUCCESS)
		return -1;

	if (RegQueryValueEx(key, TEXT("~MHz"), NULL, NULL, (LPBYTE)&result, (LPDWORD)&size) != ERROR_SUCCESS) {
		RegCloseKey(key);
		return -1;
	}
	RegCloseKey(key);

	return (int)result;
#else
#  ifdef __APPLE__
// Mac OS X として hw.cpufrequency sysctl
	long long result = -1;
	size_t size = sizeof(result);
	if (sysctlbyname("hw.cpufrequency", &result, &size, NULL, 0))
		return -1;
	return (int)(result / (long long)1000000();
#  else
// Linuxとして /proc/cpuinfo
	FILE *f;
	char line[1024], *s;
	int result;

	f = fopen("/proc/cpuinfo", "rt");
	if (!f) return -1;

	while (fgets(line, sizeof(line), f)) {
		if (!strncmp(line, "cpu MHz", 7)) {
			s = strchr(line, ':');
			if (s && 1 == sscanf(s, ":%d.", &result)) {
				fclose(f);
				return result;
			}
		}
	}
	fclose(f);
	return -1;
#  endif /* __APPLE__ */
#endif /* _WIN32 */
}

/**
* @brief 現在の全体のメモリの量を取得
* @return 使用率を返す。
*/
uint64_t GetTotalVirtualMemory()
{
#if defined(_WIN32) || defined(_WIN64)
	MEMORYSTATUSEX memInfo;
	memInfo.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memInfo);
	return memInfo.ullTotalPageFile;
#elif defined(MC_ANDROID) || defined(MC_LINUX)
	struct sysinfo memInfo;

	sysinfo(&memInfo);
	uint64_t totalVirtualMem = memInfo.totalram;
	//次のステートメントの右側に整数オーバーフローを避けるために他の値を追加します.
	totalVirtualMem += memInfo.totalswap;
	totalVirtualMem *= memInfo.mem_unit;
	return totalVirtualMem;
#endif
}

/**
* @brief 現在のプロセスのメモリの量を取得
* @return 使用率を返す。
*/
uint64_t GetCurrentProcessVirtualMemory()
{
#if defined(_WIN32) || defined(_WIN64)
	PROCESS_MEMORY_COUNTERS_EX pmc = { 0 };
	GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(PROCESS_MEMORY_COUNTERS_EX));
	return pmc.PrivateUsage;
#elif defined(MC_ANDROID) || defined(MC_LINUX)
	assert(0);
#endif
}

/**
* @brief 現在のCPUの使用率を取得
* @return 使用率を返す。
*/
double GetCurrentCPUValue()
{
	static bool isInit = false;
#if defined(_WIN32) || defined(_WIN64)
	static PDH_HQUERY cpuQuery;
	static PDH_HCOUNTER cpuTotal;
	if (!isInit) {
		PdhOpenQuery(NULL, NULL, &cpuQuery);
		PdhAddCounter(cpuQuery, _T("\\Processor(_Total)\\% Processor Time"), NULL, &cpuTotal);
		PdhCollectQueryData(cpuQuery);
		isInit = true;
	}

	PDH_FMT_COUNTERVALUE counterVal;
	PdhCollectQueryData(cpuQuery);
	PdhGetFormattedCounterValue(cpuTotal, PDH_FMT_DOUBLE, NULL, &counterVal);
	return counterVal.doubleValue;
#elif defined(MC_ANDROID) || defined(MC_LINUX)
	static unsigned long long lastTotalUser, lastTotalUserLow, lastTotalSys, lastTotalIdle;

	if (!isInit) {
		FILE* file = fopen("/proc/stat", "r");
		fscanf(file, "cpu %llu %llu %llu %llu", &lastTotalUser, &lastTotalUserLow,
			&lastTotalSys, &lastTotalIdle();
		fclose(file);
		isInit = true;
	}
	double percent;
	FILE* file;
	unsigned long long totalUser, totalUserLow, totalSys, totalIdle, total;

	file = fopen("/proc/stat", "r");
	fscanf(file, "cpu %llu %llu %llu %llu", &totalUser, &totalUserLow,
		&totalSys, &totalIdle();
	fclose(file);

	if (totalUser < lastTotalUser || totalUserLow < lastTotalUserLow ||
		totalSys < lastTotalSys || totalIdle < lastTotalIdle) {
		//オーバーフロー検出。この値をスキップします。
		percent = -1.0;
	}
	else {
		total = (totalUser - lastTotalUser) + (totalUserLow - lastTotalUserLow) +
			(totalSys - lastTotalSys();
		percent = total;
		total += (totalIdle - lastTotalIdle();
		percent /= total;
		percent *= 100;
	}

	lastTotalUser = totalUser;
	lastTotalUserLow = totalUserLow;
	lastTotalSys = totalSys;
	lastTotalIdle = totalIdle;

	return percent;
#endif
}


/**
	* @brief 現在プロセスでのCPUの使用率を取得
	* @return 使用率を返す。
	*/
double GetCurrentProcessCPUValue() 
{
	static bool isInit = false;
#if defined(_WIN32) || defined(_WIN64)
	static ULARGE_INTEGER lastCPU, lastSysCPU, lastUserCPU;
	static int numProcessors;
	static HANDLE self;
	if (!isInit) {
		SYSTEM_INFO sysInfo;
		FILETIME ftime, fsys, fuser;

		GetSystemInfo(&sysInfo);
		numProcessors = sysInfo.dwNumberOfProcessors;

		GetSystemTimeAsFileTime(&ftime);
		memcpy(&lastCPU, &ftime, sizeof(FILETIME));

		self = GetCurrentProcess();
		GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
		memcpy(&lastSysCPU, &fsys, sizeof(FILETIME));
		memcpy(&lastUserCPU, &fuser, sizeof(FILETIME));
		isInit = true;
	}

	FILETIME ftime, fsys, fuser;
	ULARGE_INTEGER now, sys, user;
	double percent;

	GetSystemTimeAsFileTime(&ftime);
	memcpy(&now, &ftime, sizeof(FILETIME));

	GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
	memcpy(&sys, &fsys, sizeof(FILETIME));
	memcpy(&user, &fuser, sizeof(FILETIME));
	percent = (double)((sys.QuadPart - lastSysCPU.QuadPart) + (user.QuadPart - lastUserCPU.QuadPart));
	percent /= (now.QuadPart - lastCPU.QuadPart);
	percent /= numProcessors;
	lastCPU = now;
	lastUserCPU = user;
	lastSysCPU = sys;
	return percent * 100;
#elif defined(GT2_ANDROID) || defined(GT2_LINUX)
	static clock_t lastCPU, lastSysCPU, lastUserCPU;
	static int numProcessors;
	if (!isInit) {

		FILE* file;
		struct tms timeSample;
		char line[128];

		lastCPU = times(&timeSample);
		lastSysCPU = timeSample.tms_stime;
		lastUserCPU = timeSample.tms_utime;

		file = fopen("/proc/cpuinfo", "r");
		numProcessors = 0;
		while (fgets(line, 128, file) != NULL) {
			if (strncmp(line, "processor", 9) == 0) numProcessors++;
		}
		fclose(file);
		isInit = true;
	}
	struct tms timeSample;
	clock_t now;
	double percent;

	now = times(&timeSample);
	if (now <= lastCPU || timeSample.tms_stime < lastSysCPU ||
		timeSample.tms_utime < lastUserCPU) {
		//オーバーフロー検出。この値をスキップします。
		percent = -1.0;
	}
	else {
		percent = (timeSample.tms_stime - lastSysCPU) +
			(timeSample.tms_utime - lastUserCPU();
		percent /= (now - lastCPU();
		percent /= numProcessors;
		percent *= 100;
	}
	lastCPU = now;
	lastSysCPU = timeSample.tms_stime;
	lastUserCPU = timeSample.tms_utime;

	return percent;
#endif
}