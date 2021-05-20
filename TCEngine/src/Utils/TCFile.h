#pragma once

#include "TCUtils.h"
#include "TCArrayList.h"

#ifdef _TC_ANDROID
struct AAssetManager;
#endif

namespace Tce {

    // 文件系统
    class File {
    public:
#ifdef _TC_ANDROID
        // 写入asset管理器
        // @param pAssetManager 管理器
        static void SetAssetManager(AAssetManager *pAssetManager) {
            m_pAssetManager = pAssetManager;
        }
#endif

        // 打开指定路径的文件，将文件内容写入到buffer
        // @param path 文件路径
        // @param buffer 导出文件数据
        // @result 若读取成功返回true，否则返回false
        static bool Open(const String &path, ArrayList<uint8_t> &buffer);

        // 打开指定路径的文件，将文件内容写入到readContent
        // @param path 文件路径
        // @param readContent 导出文件字符串
        // @result 若读取成功返回true，否则返回false
        static bool Open(const String &path, String &readContent);

    private:
#ifdef _TC_ANDROID
        static AAssetManager *m_pAssetManager;
#endif
    };

}