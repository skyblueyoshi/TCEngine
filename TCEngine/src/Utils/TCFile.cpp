
#include "TCFile.h"

#ifdef _TC_ANDROID
#include <android/asset_manager.h>
#endif

namespace Tce {

#ifdef _TC_ANDROID
    AAssetManager *File::m_pAssetManager = nullptr;
#endif

    bool File::Open(const String &path, ArrayList<uint8_t> &buffer) {
#ifdef _TC_ANDROID
        assert(m_pAssetManager);
        auto pAsset = AAssetManager_open(m_pAssetManager, path.Data(), AASSET_MODE_BUFFER);
        if (pAsset) {
            buffer.SetCount(AAsset_getLength(pAsset), '\0');
            AAsset_read(pAsset, &buffer[0], buffer.Count());
            AAsset_close(pAsset);
            return true;
        }
#endif
        return false;
    }

    bool File::Open(const String &path, String &readContent) {
        ArrayList<uint8_t> buffer;
        if (Open(path, buffer)) {
            size_t size = buffer.Count();
            readContent.SetCapacity(size + 1);
            for (size_t i = 0; i < size; i++)
                readContent[i] = (char) buffer[i];
            readContent[size] = '\0';
            return true;
        }
        return false;
    }
}