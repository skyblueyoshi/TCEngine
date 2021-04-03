
#if defined(__unix__) || defined(__APPLE__) || defined(__HAIKU__) || defined(__ANDROID__)
#   define FileMapper_POSIX
#   if defined(__ANDROID__)
#       define FileMapper_AndroidExtras
#   endif
#elif _WIN32
#   define FileMapper_Windows
#else
#   error Unsupported operating system!
#endif

#ifdef __ANDROID__

#include <android_native_app_glue.h>
#include <jni.h>
#include "src/Game/Application.h"

#include "src/Utils/Log.h"

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <src/Game/AppState.h>

extern "C" {
void handle_cmd(android_app *pApp, int32_t cmd) {

}

void android_main(struct android_app *pApp) {
    pApp->onAppCmd = handle_cmd;

    TCE_LOG_INFO("Android Main Start.");

    Tce::AppState appState(pApp);
    Tce::Application application(&appState,Tce::Application::SOLUTION_CLIENT);

    TCE_LOG_INFO("Init Application.");

    if (application.Init()) {
        TCE_LOG_INFO("Start Running Application.");
        application.Run();
    }


    int events;
    android_poll_source *pSource;
    do {
        if (ALooper_pollAll(0, nullptr, &events, (void **) &pSource) >= 0) {
            if (pSource) {
                pSource->process(pApp, pSource);
            }
        }
    } while (!pApp->destroyRequested);
}
}

#endif