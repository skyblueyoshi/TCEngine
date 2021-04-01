
#ifdef ANDROID

#include <android_native_app_glue.h>
#include <jni.h>

#include <android/log.h>

#define LOG_TAG "libTCEngine"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

extern "C" {
void handle_cmd(android_app *pApp, int32_t cmd) {

}

void android_main(struct android_app *pApp) {
    pApp->onAppCmd = handle_cmd;


    LOGI("KFC JUJU %d", 123);

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