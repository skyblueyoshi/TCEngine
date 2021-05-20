#pragma once

#include "WarningConfig.h"
#include <cstddef>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <stdarg.h>
#include <vector>
#include <array>
#include <random>
#include <exception>
#include <assert.h>
#include <mutex>
#include <ctime>
#include <memory>
#include <new>
#include <type_traits>
#include <list>
#include <cwchar>

#if defined(_WIN32)
	#define _TC_WINDOWS
#elif defined(__ANDROID__)
	#define _TC_ANDROID
#endif

#ifdef _TC_WINDOWS
#include <windows.h>
#else
#include <unistd.h>
#define Sleep(x) usleep((x)*1000L)
#endif

#ifdef _TC_WINDOWS
	#define TceSocketHandler SOCKET
#else
	#define TceSocketHandler int
#endif

inline void TC_Sleep(unsigned long milliseconds) {
	Sleep(milliseconds);
}

inline uint64_t TC_GetTickCount() {

    // 每个平台的解决方案：
    // https://stackoverflow.com/a/56218976

#ifdef _TC_WINDOWS
	return GetTickCount64();
#else
	struct timespec up{};
	int err = clock_gettime(CLOCK_BOOTTIME, &up);
	if (err != 0) {
		assert(false);
		//TODO 异常处理
	}
	uint64_t msec = (uint64_t)up.tv_sec * 1000L + (uint64_t)up.tv_nsec / 1000000L;
	return msec;
#endif
}