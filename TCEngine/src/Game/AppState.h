#pragma once


#if defined(__ANDROID__)
#include <android_native_app_glue.h>
#endif

namespace Tce {

	// 应用状态类
	class AppState {
	public:
		AppState() = default;
#	if defined(__ANDROID__)
		AppState(android_app * pAndroidState) : m_pAndroidState(pAndroidState) {}
		android_app * GetAndroidState() const {
			return m_pAndroidState;
		}
#	endif
	private:
#   if defined(__ANDROID__)
		android_app * m_pAndroidState;		//安卓APP状态
#	endif
	};

}